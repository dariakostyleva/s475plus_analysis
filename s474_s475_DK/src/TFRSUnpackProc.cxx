#include "TFRSUnpackProc.h"

#include "Go4StatusBase/TGo4Picture.h"
#include "Go4EventServer/TGo4MbsEvent.h"

#include "TFRSAnalysis.h"
#include "TFRSUnpackEvent.h"

#include "TH1.h"
#include "TH2.h"

#include <iostream>
#include <bitset>
//#include  <stdio.h>

//#define DEBUG



TFRSUnpackProc::TFRSUnpackProc() : TFRSBasicProc("FRSUnpackProc")
{
  frs = dynamic_cast<TFRSParameter*>(GetParameter("FRSPar")); 
}


TFRSUnpackProc::TFRSUnpackProc(const char* name) :  TFRSBasicProc(name) 
{ 
  hTrigger = MakeH1I("Unpack", "newTrigger", 16, 0.5, 16.5); 

  frs = dynamic_cast<TFRSParameter*>(GetParameter("FRSPar"));
  //ModSetup = dynamic_cast<TModParameter*>(GetParameter("ModPar"));
  if(frs == nullptr)
    {
      std::cout<<"E> FRS parameters not set properly, it is nullptr !"<<std::endl;
      std::exit(-1);
    }
  previousTimeStamp[0] = 0;
  previousTimeStamp[1] = 0;
  previousTimeStamp[2] = 0;
  currentTimeStamp = 0;
  
  bool remove_histos = (frs!=nullptr) && (!frs->fill_raw_histos);
  
  for(int n=0;n<32;n++){
      hVME_MAIN_11[n]         = MakeH1ISeries("Unpack/VME_MAIN", 11, 0, n, remove_histos);
      hVME_MAIN_TDC_V1290[n]  = MakeH1ISeriesV1290raw("Unpack/VME_MAIN/TDC_V1290", 0, 0, n, remove_histos);
      hVME_FRS_8[n]  = MakeH1ISeries("Unpack/VME_FRS",  8, 1, n, remove_histos);
      hVME_FRS_9[n]  = MakeH1ISeries("Unpack/VME_FRS",  9, 1, n, remove_histos);
      hVME_FRS_3[n]  = MakeH1ISeries("Unpack/VME_FRS",  3, 1, n, remove_histos);
      hVME_FRS_12[n] = MakeH1ISeries("Unpack/VME_FRS", 12, 1, n, remove_histos);
      hVME_TPCS2_8[n]   = MakeH1ISeries("Unpack/VME_TPCS2", 8,  2, n, remove_histos);
      hVME_TPCS2_12[n]  = MakeH1ISeries("Unpack/VME_TPCS2", 12, 2, n, remove_histos);
      hVME_TPCS4_0[n]   = MakeH1ISeries("Unpack/VME_TPCS4", 0,  3, n, remove_histos);
      hVME_TPCS4_1[n]   = MakeH1ISeries("Unpack/VME_TPCS4", 1,  3, n, remove_histos);
  }

  for(int n=0; n<16; n++){
    hVME_TRMU_ADC[n] = MakeH1I("Unpack/VME_TRMU/ADC", Form("newVME_TRMU_ADC_%d",n), 4096, 0,  0x2000, "channels", 2, 3, "");
    hVME_TRMU_TDC[n] = MakeH1I("Unpack/VME_TRMU/TDC", Form("newVME_TRMU_TDC_%d",n), 4096, 0, 0x10000, "channels", 2, 3, "");
  }
  
  hVME_MAIN_11All = MakeH2I("Unpack/VME_MAIN","VME_MAIN_11_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_FRS_8All  = MakeH2I("Unpack/VME_FRS","VME_FRS_08_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_FRS_9All  = MakeH2I("Unpack/VME_FRS","VME_FRS_09_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_FRS_3All  = MakeH2I("Unpack/VME_FRS","VME_FRS_03_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_FRS_12All = MakeH2I("Unpack/VME_FRS","VME_FRS_12_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_TPCS2_8All  = MakeH2I("Unpack/VME_TPCS2","VME_TPCS2_08_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_TPCS2_12All = MakeH2I("Unpack/VME_TPCS2","VME_TPCS2_12_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_TPCS4_0All  = MakeH2I("Unpack/VME_TPCS4","VME_TPCS4_00_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_TPCS4_1All  = MakeH2I("Unpack/VME_TPCS4","VME_TPCS4_01_AllCh",32,0,32,512,0,4096,"#Ch","",1);
  hVME_TRMU_ADCAll = MakeH2I("Unpack/VME_TRMU", "VME_TRMU_ADC_Allch",16,0,16,512,0,0x2000,"#Ch","",1);
  hVME_TRMU_TDCAll = MakeH2I("Unpack/VME_TRMU", "VME_TRMU_TDC_Allch",16,0,16,512,0,0x10000,"#Ch","",1);
  h_UnpackStatus = MakeH2I("Unpack","Status",2*21*32,0.,2*21*32,10,0.,10.,"#Ch","Status",1);
  h_TSFlagStatus = MakeH2I("Unpack","TS_flagStatus",1000,0,1000,10,0,10,"Diff_TS","Status",1);
  
}

TFRSUnpackProc::~TFRSUnpackProc()
{ }



Int_t getbits(Int_t value, int nword, int start, int length)
{
  UInt_t buf = (UInt_t) value;
  buf = buf >> ((nword-1)*16 + start - 1);
  buf = buf & ((1 << length) - 1);
  return buf;
}

Int_t get2bits(Int_t value, int nword, int start, int length)
{
  UInt_t buf = (UInt_t) value;
  buf = buf >> ((nword-1)*32 + start - 1);
  buf = buf & ((1 << length) - 1);
  return buf;
}

Bool_t TFRSUnpackProc::BuildEvent(TGo4EventElement* output) 
{
  
  TFRSUnpackEvent* tgt = dynamic_cast<TFRSUnpackEvent*> (output);
  if (tgt==nullptr)
    return kFALSE;
  tgt->SetValid(kFALSE);  // by default output event rejected

  TGo4MbsEvent *fInput = dynamic_cast<TGo4MbsEvent*> (GetInputEvent());
  if (fInput==nullptr)
    return kFALSE;

  /*  Put the event header stuff into output event  */
  tgt->qlength   = fInput->GetDlen()   ;
  tgt->qtype     = fInput->GetType()   ;
  tgt->qsubtype  = fInput->GetSubtype();
  tgt->qdummy    = fInput->GetDummy()  ;
  tgt->qtrigger  = fInput->GetTrigger();
  tgt->qevent_nr = fInput->GetCount()  ;


  // If trigger 12 or 13 or 14 or 15, event fully can be skipped
  if( (fInput->GetTrigger()==12) || (fInput->GetTrigger()==13) || (fInput->GetTrigger()==14) || (fInput->GetTrigger()==15))
    {
      //std::cout << "Trigger = " << fInput->GetTrigger() << ", event skipped" << std::endl;
      return kFALSE;
    }
  
  
  // Special event
  if(fInput->GetCount()!=0)
    {
      // std::cout << "qtype : " << fInput->GetType() << std::endl;  
      // std::cout << "qlength(=GetDLen) : " << tgt->qlength  << std::endl;
      // std::cout << "qsubtype : " <<  tgt->qsubtype << std::endl;
      /*  Check event length: if it's <= 4 it is empty or screwed up! */
      if(fInput->GetDlen()<=4)
	{
	  std::cout << "Wrong event length: " << fInput->GetDlen() << " =< 4" << std::endl;
	  return kFALSE;
	}
  
      /*  Event OK, now assign pointer to local subevent header! */
      //std::cout << "trigger = " << fInput->GetTrigger() << std::endl;    
      fInput->ResetIterator();
      TGo4MbsSubEvent *psubevt = nullptr;

      while ((psubevt=fInput->NextSubEvent())!= nullptr)
	{
	  // start subevents loop
#ifdef DEBUG
	  psubevt->PrintEvent();
#endif

	  // print data in a similar style as type ev -v
	  if(0){
	    int temp_procid = psubevt->GetProcid();
	    int temp_type   = psubevt->GetType() ;
	    int temp_subtype = (psubevt->GetSubtype());
	    int temp_len     = (psubevt->GetDlen()-2)/2;
	    int *temp_pdata = psubevt->GetDataField();
	    printf("\nprocid=%d, type=%d, subtype=%d\n",temp_procid,temp_type,temp_subtype);
	    for(int ii=0; ii<100; ii++){
	      for(int jj=0; jj<5; jj++){
		if(jj+5*ii < temp_len){
		  printf("%08x ",*(temp_pdata+jj+5*ii));
		  if(4==jj){ printf("\n"); fflush(stdout);
		  }
		}
	      }
	    }
	  }


	  //------check Type and SubType-------//
	  // this part is still hard-coded.    //
	  // 3700 and 3800 are rejected. (spill end?) //
	  if( !( (psubevt->GetType() == 10) && (psubevt->GetSubtype() == 1))  &&  //(t,s)=(12,1)->(10,1) modified on 2019/11/13
	      !( (psubevt->GetType() == 12) && (psubevt->GetSubtype() == 1))  &&  //(t,s)=(12,1)->(10,1) modified on 2019/11/13
	      !( (psubevt->GetType() == 36) && (psubevt->GetSubtype() == 3600) ) &&
	      !( (psubevt->GetType() == 88) && (psubevt->GetSubtype() == 8800) ) )
	    {  // for all data 
	      std::cout << "getprocid  " << psubevt->GetProcid()  << std::endl;
	      std::cout << "getsubtype " << psubevt->GetSubtype() << std::endl;
	      std::cout << "gettype " << psubevt->GetType() << std::endl;
	      std::cout << "Wrong subevent type " << psubevt->GetType() << std::endl;
	      if( 3700==psubevt->GetSubtype() || 3800== psubevt->GetSubtype() ){//blacklist	
		std::cout << "bad event, skip this event for moment" << std::endl;
		return kFALSE;
 	      }
	      continue; // skip subevent SL
	    }
	  
	  if( (psubevt->GetType() == 36) && (psubevt->GetSubtype() == 3600) ) //tpat
	    {
	      Int_t *pdata = psubevt->GetDataField();
	      int tpat_len = 0xFF & (*pdata) ;
	      pdata++;
	      for(int ii=0; (ii<tpat_len && ii<32) ; ii++){
		tgt->tpat_main[ii] = *pdata;
		//  printf("write tpat data %d = 0x%08x\n",ii,tgt->tpat_main[ii]);
		pdata++;
	      }
	      continue;
	    }

         
	  /************************************************************************/
	  /* Here we go for the different triggers.....                           */
	  /************************************************************************/

	  switch(fInput->GetTrigger())
	    { // trigger value
	    case 1: //FRS trigger box
	    case 2: //Ion catcher Si 1
	    case 3: //Ion catcher Si 2
	    case 4: //Ion catcher Si 3 (not used)
	    case 5: //trigger 10 Hz for scaler readout
	    case 6:
	    case 7:
	    case 8:
	    case 9:
	    case 10: 
	    case 11:
	      Event_Extract(tgt,psubevt);
	      break;
	      
	    // here do not need to put skip fir trig=12-15, because these are skipped already in the beginning of Unpack.
	      
	    default:
	      { 
		     std::cout << "Invalid trigger " << fInput->GetTrigger() << std::endl;
		     return kFALSE; 
	      }
      
	    }  // switch on trigger value
	
	} // end subevents loop
	

    } // end special event

  FillHistograms(tgt); // fill histograms from output event

  
  tgt->SetValid(kTRUE); // accept event
  return kTRUE;
} // close unpack proc



Bool_t TFRSUnpackProc::Event_Extract(TFRSUnpackEvent* event_out, TGo4MbsSubEvent* psubevt, int)
{

  Int_t *pdata = psubevt->GetDataField();
  Int_t len = 0;	  
  Int_t vme_chn;
  Int_t lenMax = (psubevt->GetDlen()-2)/2;
  Int_t event_flag = *pdata++;  len++; // 0x200 or 0x000 etc. 20200123MERGE
    
  switch(psubevt->GetProcid())
  {   
    //===========
      case 30:  // now 30 is FRS CRATE (06.07.2018)

	{ // start of v830 (do not remove this bracket)
	    Int_t vme_geo = getbits(*pdata,2,12,5);
	    Int_t vme_type = getbits(*pdata,2,9,3);
	    Int_t vme_nlw =  getbits(*pdata,2,3,6);
	    pdata++; len++;
	    if(vme_type!=4){   std::cout<<"E> Scaler type missed match ! GEO"<<vme_geo<<" "<<" type 4 =/="<<vme_type<<std::endl; }
	    for(int i_ch=0; i_ch<vme_nlw; i_ch++){
	      event_out->scaler_frs[i_ch] = *pdata;
	      ////               printf("scaler_frs[ch=%d] = %d\n",i_ch,*pdata);
	      pdata++; len++;
	    }
	} //end of V830

	//----- v775 TDC/V785 ADC -----//
	while (len < lenMax){	       
	  /* read the header longword and extract slot, type & length  */
	  Int_t vme_chn = 0;
	  Int_t vme_geo = getbits(*pdata,2,12,5);
	  Int_t vme_type = getbits(*pdata,2,9,3);
	  Int_t vme_nlw =  getbits(*pdata,1,9,6); 
	  pdata++; len++;
 
	  /* read the data */
	  if ((vme_type == 2) && (vme_nlw > 0)) {
	    for(int i=0;i<vme_nlw;i++) {  
	      vme_geo = getbits(*pdata,2,12,5);
	      vme_type = getbits(*pdata,2,9,3);
	      vme_chn = getbits(*pdata,2,1,5);
	      event_out->vme_frs[vme_geo][vme_chn] = getbits(*pdata,1,1,16);
	      ////	      printf("vme_frs[geo=%d][ch=%d] = %d\n",vme_geo,vme_chn,getbits(*pdata,1,1,16));
	      pdata++; len++;
	    }
	  }

	  /* read and ignore the expected "end-of-block" longword */
	  pdata++; len++;
	}  /* end of the while... loop  */

	break;
      
     //================  
      case 10:	// Main crate
	
	if((psubevt->GetType() == 10) && (psubevt->GetSubtype() == 1) && lenMax < 15) // in this case, time stamp data.
	  {
	    int ii =0;
	    while(len < lenMax){
	      event_out->timestamp_main[ii] = *pdata;
	      pdata++; len++; ii++;
	    }
	    break;
	  }


      // 1st babababa
      if(*pdata != 0xbabababa){ std::cout<<"E> ProcID 10 : Barrier-1 missed !" << *pdata << std::endl; }
      pdata++; len++;
      
      // next there are 2 words (time stamp) but these are redundant  skip 2 words;
      //     pdata++; len++;
      /// pdata++; len++;

      // addional babababa request by JoseLuis
      // if(*pdata != 0xbabababa){ std::cout<<"E> ProcID 10 : Barrier-2 missed !" << *pdata  << std::endl; }
      //  pdata++; len++;

      // next should be v1290 TDC  
      if (len < lenMax){
	Int_t vme_geo = getbits(*pdata,1,1,5);
	Int_t vme_type = getbits(*pdata,2,12,5);
	pdata++; len++;
	Int_t multihit = 0;//, counter = 0;

#ifdef DEBUG
	std::cout<<"mTDC geo = "<<vme_geo<<", type = "<<vme_type<<std::endl;
#endif  
    
	if (vme_type == 8)
	  {
	    while (len < lenMax) 
	      {
#ifdef DEBUG
		std::cout<<"word : "<<std::bitset<32>(*pdata)<<" ";
#endif
		vme_type = getbits(*pdata,2,12,5);
		if(vme_type==1) // headerTDC
		  { 
		    pdata++; len++;
		  }
		//multihit = 0;
#ifdef DEBUG
		std::cout<<"reading :"<<vme_type<<std::endl;
#endif
		vme_type = getbits(*pdata,2,12,5);
#ifdef DEBUG
		std::cout<<"word : "<<std::bitset<32>(*pdata)<<" type:"<<vme_type<<" ";
#endif
		if(vme_type == 0)
		  {
		    // this indicates a TDC measurement
		    Int_t vme_chn = getbits(*pdata,2,6,5);
		    Int_t LeadingOrTrailing = getbits(*pdata,2,11,1);
		    Int_t value = getbits(*pdata,1,1,21);
		    
		    multihit = event_out->nhit_v1290_main[vme_chn][LeadingOrTrailing];
#ifdef DEBUG
		    std::cout << "     tdc vme_chn = " << vme_chn;
		    std::cout << " multihit: " << multihit << " ";
#endif
		    
		    if (multihit >= 10)
		      {
			pdata++; len++;
			continue;
		      }
		    if(LeadingOrTrailing == 0)
		      {
#ifdef DEBUG
			std::cout << " +-> tdc L value = " << value << std::endl;
#endif
			if (value > 0)
			  {
			    event_out->leading_v1290_main[vme_chn][multihit] = value;
			    hVME_MAIN_TDC_V1290[vme_chn]->Fill(value); //
			  }
		      }
		    else
		      {
#ifdef DEBUG
			std::cout << " +-> tdc T value = " << value << std::endl;
#endif
			if (value > 0)
			  event_out->trailing_v1290_main[vme_chn][multihit] = value;
		      }
		    event_out->nhit_v1290_main[vme_chn][LeadingOrTrailing]++;
		    
		    pdata++; len++;
		  }
		else
		  {
		    // TDC trailer vme_type == 3 
#ifdef DEBUG
		    std::cout<<"\n";
#endif
		    if(vme_type != 3 && vme_type !=16)
		      std::cout<<"E> MTDC strange type :"<<vme_type<<std::endl;
		    if(vme_type==16)
		      {
			Int_t vme_geoEnd = getbits(*pdata,1,1,5);
			if(vme_geo!=vme_geoEnd)
			  std::cout<<"E> MTDC strange end buffer header :"<<vme_type<<" "<<vme_geo<<" != "<<vme_geoEnd<<std::endl;
			pdata++; len++;
			break;
		      }
		    pdata++; len++;
		  }
	      } //while len loop
	  }//if type==8
      }//end if len more due to strange logic // end of V1290


      //---- 3rd barrier ---
      if(*pdata != 0xbabababa){ std::cout<<"E> ProcID 10 : Barrier-3 missed !" << std::endl; }
      pdata++; len++;
      
      //----- Next is V830 Scaler-----
      { // start of v830 (do not remove this bracket)
	Int_t vme_geo = getbits(*pdata,2,12,5);
	Int_t vme_type = getbits(*pdata,2,9,3);
	Int_t vme_nlw =  getbits(*pdata,2,3,6);
	pdata++; len++;
	if(vme_type!=4){   std::cout<<"E> Scaler type missed match ! GEO"<<vme_geo<<" "<<" type 4 =/="<<vme_type<<std::endl; }
	for(int i_ch=0; i_ch<vme_nlw; i_ch++){
	  event_out->scaler_main[i_ch] = *pdata;
	  //printf("scaler_main[ch=%d] = %d\n",i_ch,*pdata);
	  pdata++; len++;
	}
      } //end of V830
      
      
      //--------the rest of the unpacking...V792--------
      while (len < (psubevt->GetDlen()-2)/2)
	{
	  Int_t vme_chn = 0;
	  Int_t vme_geo = getbits(*pdata,2,12,5);
	  Int_t vme_type = getbits(*pdata,2,9,3);
	  Int_t vme_nlw =  getbits(*pdata,1,9,6); 
	  pdata++; len++;
	  
#ifdef DEBUG
	  std::cout<<"data "<<vme_geo<<" "<<vme_type<<" "<<vme_nlw<<" idmod:"<<IdMod<<std::endl;
#endif
	  // read the data
	  if(vme_type == 6){
	      // not valid data !
	  }
	  if ((vme_type == 2) && (vme_nlw > 0)){
	    for(int i=0;i<vme_nlw;i++){  
	      vme_geo = getbits(*pdata,2,12,5);
	      vme_type = getbits(*pdata,2,9,3);
	      vme_chn = getbits(*pdata,2,1,5);
	      event_out->vme_main[vme_geo][vme_chn] = getbits(*pdata,1,1,16);
	      pdata++; len++;
	    }
	    // read and ignore the expected "end-of-block" longword 
	    pdata++; len++;
	  }
	}  // end of the while... loop  

   
      break; // proc ID 10
    
      
      //=========	    
    case 20:
    case 25:
 
      //=============================== (Added on 07.07.2018)
      /* v775 TDC/V785 ADC */
      
      while (len < lenMax){
	
	/* read the header longword and extract slot, type & length  */
	Int_t vme_chn = 0;
	Int_t vme_geo = getbits(*pdata,2,12,5);
	Int_t vme_type = getbits(*pdata,2,9,3);
	Int_t vme_nlw =  getbits(*pdata,1,9,6); 
	// printf("pdata=0x%08x\n",*pdata); fflush(stdout);
	//std::cout<< vme_geo << std::endl;
	pdata++; len++;
	
	/* read the data */
	if ((vme_type == 2) && (vme_nlw > 0)) {
	  for(int i=0;i<vme_nlw;i++) {  
	    vme_geo = getbits(*pdata,2,12,5);
	    vme_type = getbits(*pdata,2,9,3);
	    vme_chn = getbits(*pdata,2,1,5);
	    //printf("pdata=0x%08x\n",*pdata); fflush(stdout);
	    if(20 == psubevt->GetProcid()) event_out->vme_tpcs4[vme_geo][vme_chn] = getbits(*pdata,1,1,16);
	    if(25 == psubevt->GetProcid()) event_out->vme_tpcs2[vme_geo][vme_chn] = getbits(*pdata,1,1,16);
	    pdata++; len++;
	  }   
	}

	/* read and ignore the expected "end-of-block" longword */
	pdata++; len++;
      }  /* end of the while... loop  */
      
      //===============================      
      //All the TDCs/ADCs are read with the code just above..(07.07.2018)
      
      /* rest of the unpacking */
      while (len < (psubevt->GetDlen()-2)/2)
	{
	  /* read the header longword and extract slot, type & length  */
	  Int_t vme_chn = 0;
	  Int_t vme_geo = getbits(*pdata,2,12,5);
	  Int_t vme_type = getbits(*pdata,2,9,3);
	  Int_t vme_nlw =  getbits(*pdata,1,9,6);
	  pdata++; len++;
#ifdef DEBUG
	  std::cout<<"data "<<vme_geo<<" "<<vme_type<<" "<<vme_nlw;
#endif      
	}  /* end of the while... loop  */

      break;
      
     //=========	    
     case 40: // Travel music crate (2020/Jan/23)
       
       { //-----MDPP module----- (do not remove this bracket)

	 // header
	 Int_t header = *pdata;
	 Int_t nword_mdpp = (0x3FF & header);
	 pdata++;
       
	 // main data (data or time information or end counter)
	 for(int ii=0; ii<nword_mdpp; ii++){
	   int tmp_data = *pdata;
	   if( 1 == (0xF & (tmp_data>>28))   ){
	     //	     printf("real data 0x%08x\n",tmp_data);
	     int ch = 0x3F & (tmp_data >> 16);
	     if(0<=ch && ch<=15){
	       int adc_data = 0xFFFF & tmp_data;
	       //    printf("ADC data !!! ch = %2d, ADC = %d \n",ch, adc_data);
	       if( (event_out->vme_trmu_adc[ch]) <= 0 ){ //first-come-first-served, for detailed multi-hit analysis, investigation needed.
		 event_out->vme_trmu_adc[ch] = adc_data;
		 //// printf("event_out->vme_trmu_adc[%d] = 0x%08x; \n",ch,adc_data);
	       }
	     }else if(16<=ch && ch<=31){
	       int tdc_data = 0xFFFF & tmp_data;
	       //printf("TDC data !!! ch = %2d, TDC = %d \n",ch-16, tdc_data);
	       if( (event_out->vme_trmu_tdc[ch-16]) <= 0 ){//first-come-first-served, for detailed multi-hit analysis, investigation needed.
		 event_out->vme_trmu_tdc[ch-16] = tdc_data;
		 //////        	 printf("event_out->vme_trmu_tdc[%d] = 0x%08x; \n",ch-16,tdc_data);
	       }
	     }	       
	   }else if( 2 == (0xF & (tmp_data>>28))){
	     // printf("ext time stamp 0x%08x\n",tmp_data);
	   }else if(0x0 == tmp_data ){
	     // printf("dummy 0x%08x\n",tmp_data);
	   }else if( 3 == (0x3 & (tmp_data>>30))){
	     // printf("end counter 0x%08x\n",tmp_data);
	   }else{
	     // printf("unknown data0x%08x\n",tmp_data);
	   } 
	   pdata++;
	 }
       }//---end of MDPP module ---
       
       break;
     
     //=========
     default :
       break;
       
  } // end switch prodID

  return kTRUE;

}


Bool_t TFRSUnpackProc::FillHistograms(TFRSUnpackEvent* event)
{
  
  hTrigger->Fill(event->qtrigger);

  if(frs->fill_raw_histos)
    {
        
      for(int i=0;i<32;i++)
	{
	  if(hVME_MAIN_11[i])  hVME_MAIN_11[i]->Fill(event->vme_main[11][i] & 0xfff);
	  if(hVME_MAIN_11All)  hVME_MAIN_11All->Fill(i,event->vme_main[11][i] & 0xfff);
	  // TDC time is filled in the eventbuild, to put all multi-hits in the histograms
	}
      for(int i=0;i<32;i++)
	{
	  if(hVME_FRS_8[i])  hVME_FRS_8[i]->Fill(event->vme_frs[8][i] & 0xfff);
	  if(hVME_FRS_9[i])  hVME_FRS_9[i]->Fill(event->vme_frs[9][i] & 0xfff);
	  if(hVME_FRS_3[i])  hVME_FRS_3[i]->Fill(event->vme_frs[3][i] & 0xfff);
	  if(hVME_FRS_12[i]) hVME_FRS_12[i]->Fill(event->vme_frs[12][i] & 0xfff);
	  if(hVME_FRS_8All)  hVME_FRS_8All->Fill(i,event->vme_frs[8][i] & 0xfff);
	  if(hVME_FRS_9All)  hVME_FRS_9All->Fill(i,event->vme_frs[9][i] & 0xfff);
	  if(hVME_FRS_3All)  hVME_FRS_3All->Fill(i,event->vme_frs[3][i] & 0xfff);
	  if(hVME_FRS_12All) hVME_FRS_12All->Fill(i,event->vme_frs[12][i] & 0xfff);
	}

      
      for(int i=0;i<32;i++)
	{
	  if (hVME_TPCS2_8[i] ) hVME_TPCS2_8[i] ->Fill(event->vme_tpcs2[8][i] & 0xfff);
	  if (hVME_TPCS2_12[i]) hVME_TPCS2_12[i]->Fill(event->vme_tpcs2[12][i] & 0xfff);
	  if (hVME_TPCS4_0[i] ) hVME_TPCS4_0[i] ->Fill(event->vme_tpcs4[0][i] & 0xfff);
	  if (hVME_TPCS4_1[i] ) hVME_TPCS4_1[i] ->Fill(event->vme_tpcs4[1][i] & 0xfff);
	  if (hVME_TPCS2_8All ) hVME_TPCS2_8All ->Fill(i,event->vme_tpcs2[8][i] & 0xfff);
	  if (hVME_TPCS2_12All) hVME_TPCS2_12All->Fill(i,event->vme_tpcs2[12][i] & 0xfff);
	  if (hVME_TPCS4_0All ) hVME_TPCS4_0All ->Fill(i,event->vme_tpcs4[0][i] & 0xfff);
	  if (hVME_TPCS4_1All ) hVME_TPCS4_1All ->Fill(i,event->vme_tpcs4[1][i] & 0xfff);
	}

        for(int i=0;i<16;i++)
	{
	  if(hVME_TRMU_ADC[i]) hVME_TRMU_ADC[i]->Fill(event->vme_trmu_adc[i]);
	  if(hVME_TRMU_ADCAll) hVME_TRMU_ADCAll->Fill(i, event->vme_trmu_adc[i]);
	  if(hVME_TRMU_TDC[i]) hVME_TRMU_TDC[i]->Fill(event->vme_trmu_tdc[i]);
	  if(hVME_TRMU_TDCAll) hVME_TRMU_TDCAll->Fill(i, event->vme_trmu_tdc[i]);
	}
    }

  return kTRUE;
}
 
ClassImp(TFRSUnpackProc)

