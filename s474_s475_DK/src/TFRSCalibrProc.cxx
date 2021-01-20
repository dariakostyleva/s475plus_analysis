#include "TFRSCalibrProc.h"

#include "TH1.h"
#include "TH2.h"
#include "Go4StatusBase/TGo4Picture.h"	//mik
#include "Go4ConditionsBase/TGo4WinCond.h"

#include "TFRSCalibrEvent.h"
#include "TFRSSortEvent.h"
#include "TFRSParameter.h"
#include "TFRSAnalysis.h"


TFRSCalibrProc::TFRSCalibrProc() : TFRSBasicProc("FRSCalibrProc")
{
  frs = dynamic_cast<TFRSParameter*>(GetParameter("FRSPar"));
  mw  = dynamic_cast<TMWParameter*>(GetParameter("MWPar"));
  music  = dynamic_cast<TMUSICParameter*>(GetParameter("MUSICPar"));
  tpc = dynamic_cast<TTPCParameter*>(GetParameter("TPCPar"));
  si  = dynamic_cast<TSIParameter*>(GetParameter("SIPar"));
  InitProcessor();
}

TFRSCalibrProc::TFRSCalibrProc(const char* name) : TFRSBasicProc(name)
{ 

  //TFRSAnalysis *myAnalysis = (TFRSAnalysis*) GetObject("FRSanalysis");

  frs = dynamic_cast<TFRSParameter*>(GetParameter("FRSPar"));
  mw = dynamic_cast<TMWParameter*>(GetParameter("MWPar"));
  music  = dynamic_cast<TMUSICParameter*>(GetParameter("MUSICPar"));
  tpc = dynamic_cast<TTPCParameter*>(GetParameter("TPCPar"));
  si  = dynamic_cast<TSIParameter*>(GetParameter("SIPar"));

  bDrawHist=kTRUE;

  //  Create_MON_Hist();
  Create_Scaler_Hist();
  Create_MW_Hist();
  Create_TPC_Hist();
  Create_SI_Hist();
  //  Create_CT_Hist();
  //  Create_ElCurrent_Hist();

  InitProcessor();
}

TFRSCalibrProc::~TFRSCalibrProc()
{ }

//void TFRSCalibrProc::FRSCalibr(TFRSCalibrEvent* tgt)
Bool_t TFRSCalibrProc::BuildEvent(TGo4EventElement* output)
{
  TFRSCalibrEvent* tgt = dynamic_cast<TFRSCalibrEvent*> (output);
  if (tgt==nullptr)
    return kFALSE;

  tgt->SetValid(kTRUE);  // output event always accepted

  TFRSSortEvent *src = dynamic_cast<TFRSSortEvent*> (GetInputEvent());
  if (src==nullptr)
    return kFALSE;
  
  /*
    if (src->pattern>500){
    }
  */
  tgt->EventFlag = src->EventFlag;
  
  Process_Scaler_Analysis(*src, *tgt);  
  //  Process_MON_Analysis(*src, *tgt);
  Process_TPC_Analysis(*src, *tgt);
  Process_MW_Analysis(*src, *tgt);
  Process_SI_Analysis(*src, *tgt);
  //  Process_CT_Analysis(*src, *tgt);
  //  Process_ElCurrent_Analysis(*src, *tgt);

  return kTRUE;
}


void TFRSCalibrProc::Create_Scaler_Hist() 
{
  bool scaler_enable_hist[64];
  char scaler_name[64][256];
  scaler_ch_1kHz=39; //ch7 of 2nd scaler
  scaler_ch_spillstart=8; //ch8 of 1st scaler 
  scaler_check_first_event=1;
  
  for(int ii=0; ii<64; ii++){
    sprintf(scaler_name[ii],"scaler_ch%d",ii);//default name
    scaler_enable_hist[ii]=false;
  }
  sprintf(scaler_name[0],"IC01curr-new"); 
  sprintf(scaler_name[1],"SEETRAM-old");
  sprintf(scaler_name[2],"SEETRAM-new");
  sprintf(scaler_name[3],"IC01curr-old");
  sprintf(scaler_name[4],"IC01 count");
  sprintf(scaler_name[5],"SCI00");
  sprintf(scaler_name[6],"SCI01");
  sprintf(scaler_name[7],"SCI02");
  sprintf(scaler_name[8],"Start Extr");
  sprintf(scaler_name[9],"Stop Extr");
  sprintf(scaler_name[10],"Beam Transformer");
  
  sprintf(scaler_name[32],"Free Trigger");
  sprintf(scaler_name[33],"Accept Trigger");
  sprintf(scaler_name[34],"Spill Counter");
  sprintf(scaler_name[35],"1 Hz clock");
  sprintf(scaler_name[36],"10 Hz clock");
  sprintf(scaler_name[37],"100 kHz X veto dead-time");
  sprintf(scaler_name[38],"100 kHz clock");
  sprintf(scaler_name[39],"1 kHz clock");
  
  sprintf(scaler_name[48],"SCI21L");
  sprintf(scaler_name[49],"SCI41L");
  sprintf(scaler_name[50],"SCI42L");
  sprintf(scaler_name[51],"SCI43L");
  sprintf(scaler_name[52],"SCI42R");  //  sprintf(scaler_name[52],"SCI81L"); // found that the connection to NIM-ECL was not as intended. 2020-03-10.
  sprintf(scaler_name[53],"SCI21R");
  sprintf(scaler_name[54],"SCI41R");
  sprintf(scaler_name[55],"SCI21L_b");// to avoid same name  //  sprintf(scaler_name[55],"SCI42R");
  sprintf(scaler_name[56],"SCI43R");
  sprintf(scaler_name[57],"SCI42R_b");// to avoid same name  // sprintf(scaler_name[57],"SCI81R");
  sprintf(scaler_name[58],"SCI31L");
  sprintf(scaler_name[59],"SCI31R");
  sprintf(scaler_name[60],"SCI11");
  sprintf(scaler_name[61],"SCI22L");
  sprintf(scaler_name[62],"SCI22R");
  sprintf(scaler_name[63],"SCI51");
  

  for(int ii=0; ii<64; ii++){
    /// Do not change bin settings. It will affect analysis.
    hScaler_per_s[ii]     = MakeH1I("Scaler/Scaler_per_1s",Form("%s_per_1s",scaler_name[ii]),1000,0,1000,"Time (s)", 2,5, "Count per second");
    hScaler_per_100ms[ii] = MakeH1I("Scaler/Scaler_per_0.1s",Form("%s_per_0.1s",scaler_name[ii]),4000,0,400,"Time (s)", 2,5, "Count per 0.1 second");
    hScaler_per_spill[ii] = MakeH1I("Scaler/Scaler_per_spill",Form("%s_per_spill",scaler_name[ii]),1000,0,1000,"Spill", 2,5, "Count per spill");
  }
  return ;
}


void TFRSCalibrProc::Create_MW_Hist() 
{
  Float_t lim_xsum[13][2] = {
    {1,8000},  // MW11
    {1,8000},  // MW21
    {1,8000},  // MW22
    {1,8000},  // MW31
    {1,8000},  // MW41
    {1,8000},  // MW42
    {1,8000},  // MW51
    {1,8000},  // MW61
    {1,8000},  // MW71
    {1,8000},  // MW81
    {1,8000},  // MW82
    {1,8000},  // MWB1
    {1,8000}};  // MWB2

  Float_t lim_ysum[13][2] = {
    {2,8000},  // MW11
    {2,8000},  // MW21
    {2,8000},  // MW22
    {2,8000},  // MW31
    {2,8000},  // MW41
    {2,8000},  // MW42
    {2,8000},  // MW51
    {2,8000},  // MW61
    {2,8000},  // MW71
    {2,8000},  // MW81
    {2,8000},  // MW82
    {2,8000},  // MWB1
    {2,8000}};  // MWB2

  for(int i=0;i<13;i++)
    {  // up to MW31
       //up to MWB2 (09.07.2018)
      char fname[100]; 
      sprintf(fname,"MW/MW%s/MW%s", mw_folder_ext1[i],mw_folder_ext2[i]); 

      hMW_AN[i] = MakeH1I_MW(fname,"MW_an",i,1000,1,4096,"Anode (channels)",2,3);
      hMW_XL[i] = MakeH1I_MW(fname,"MW_XL",i,1000,1,4096,"X-left (channels)",2,3);
      hMW_XR[i] = MakeH1I_MW(fname,"MW_XR",i,1000,1,4096,"X-right (channels)",2,3);
      hMW_YU[i] = MakeH1I_MW(fname,"MW_YU",i,1000,1,4096,"Y-up (channels)",2,3);
      hMW_YD[i] = MakeH1I_MW(fname,"MW_YD",i,1000,1,4096,"Y-down (channels)",2,3);

      hMW_XSUM[i] = MakeH1I_MW(fname,"MW_XSUM",i,800,5,8005,"Sum XL+XR (channels)",2,5);
      hMW_YSUM[i] = MakeH1I_MW(fname,"MW_YSUM",i,800,5,8005,"Sum YU+YD (channels)",2,5);

      char title[100];
      //if((i==0) || (i>3))
      //sprintf(title,"(stiff) X at MW%s [mm] (soft)", mw_folder_ext2[i]);
      //else
      //sprintf(title,"(soft) X at MW%s [mm] (stiff)", mw_folder_ext2[i]);
      
      sprintf(title,"X at MW%s [mm]", mw_folder_ext2[i]);
      hMW_X[i] = MakeH1I_MW(fname,"MW_X",i,201,-100.5,+100.5,title,2,7);

      sprintf(title,"Y at MW%s [mm]", mw_folder_ext2[i]);
      hMW_Y[i] = MakeH1I_MW(fname,"MW_Y",i,201,-100.5,+100.5,title,2,7);

      char xyname[100];
      sprintf(xyname,"MW_XY%s", mw_name_ext[i]);
      hMW_XY[i] = MakeH2I(fname,xyname,40,-100,100,40,-100,100,"x [mm]","y [mm]",2);

      char condname[40];
      sprintf(condname,"XSUM%s",mw_name_ext[i]);
      cMW_XSUM[i] = MakeWindowCond("MW/XSUM", condname, lim_xsum[i][0], lim_xsum[i][1], hMW_XSUM[i]->GetName());

      sprintf(condname,"YSUM%s",mw_name_ext[i]);
      cMW_YSUM[i] = MakeWindowCond("MW/YSUM", condname, lim_ysum[i][0], lim_ysum[i][1], hMW_YSUM[i]->GetName());
    }

  hMW_SC21x  = MakeH1I("MW","MW_SC21x", 221,-110.5,110.5,"X tracked at SC21 [mm]",2,7);
  hMW_SC22x  = MakeH1I("MW","MW_SC22x", 221,-110.5,110.5,"X tracked at SC22 [mm]",2,7);

  hMW_xAngS2 = MakeH1I("MW/S2/Ang","MW_xAngS2",201,-100.5,100.5,"X-Angles at S2 [mrad]",2,7); 
  hMW_yAngS2 = MakeH1I("MW/S2/Ang","MW_yAngS2",201,-100.5,100.5,"Y-Angles at S2 [mrad]",2,7);
  hMW_xFocS2 = MakeH1I("MW/S2/Foc","MW_xFocS2",201,-100.5,100.5,"X-Position at S2 Focus [mm]",2,7);
  hMW_yFocS2 = MakeH1I("MW/S2/Foc","MW_yFocS2",201,-100.5,100.5,"Y-Position at S2 Focus [mm]",2,7);
  hMW_zxS2   = MakeH1I("MW/S2/Pos","MW_zxS2",350,-100,600,"Distance from TS3QT33 at S2 Focus [cm]",2,7);
  hMW_zyS2   = MakeH1I("MW/S2/Pos","MW_zyS2",350,-100,600,"Distance from TS3QT33 at S2 Focus [cm]",2,7);
  hMW_FocS2  = MakeH2I("MW/S2/Foc","MW_FocS2", 240,-120.,120.,  240,-120.,120.,
		       "X [mm] tracked to S2 focus","Y [mm] tracked to S2 focus", 2);

  for (int i=0;i<13;i++)
    {  // up to MW31
       //up to MWB2 (09.07.2018)
      char fname[100], pname[100];
      sprintf(fname,"MW/MW%s", mw_folder_ext1[i]);
      sprintf(pname,"MW%s", mw_folder_ext2[i]);
      MakePic(fname,pname,2,2,hMW_XL[i],hMW_XR[i],hMW_YU[i],hMW_YD[i]);
    }   
}


//Creation of TPC data & histograms
void TFRSCalibrProc::Create_TPC_Hist()
{
  

  for(int i=0;i<7;i++)
    {        
      char fname[100];
      char name[100];
      sprintf(fname,"TPC/%s",tpc_folder_ext1[i]);
      //(HAPOL-25/03/06) Duplicated histograms for double delay line (0 and 1) in new TPCs

      hTPC_L0[i]=MakeH1I_TPC(fname,"L0",i,4000,5,4005,"Left DL0 ADC (channels)",2,3);
      hTPC_R0[i]=MakeH1I_TPC(fname,"R0",i,4000,5,4005,"Right DL0 ADc (channels)",2,3);
      hTPC_LT0[i]=MakeH1I_TPC(fname,"LT0",i,4000,5,4005,"Left DL0 time (channels)",2,3);
      hTPC_RT0[i]=MakeH1I_TPC(fname,"RT0",i,4000,5,4005,"Right DL0 time(channels)",2,3);
      hTPC_L1[i]=MakeH1I_TPC(fname,"L1",i,4000,5,4005,"Left DL1 ADC (channels)",2,3);
      hTPC_R1[i]=MakeH1I_TPC(fname,"R1",i,4000,5,4005,"Right DL1 ADC (channels)",2,3);
      hTPC_LT1[i]=MakeH1I_TPC(fname,"LT1",i,4000,5,4005,"Left DL1 time (channels)",2,3);
      hTPC_RT1[i]=MakeH1I_TPC(fname,"RT1",i,4000,5,4005,"Right DL1 time(channels)",2,3);
      hTPC_DT[i][0]=MakeH1I_TPC(fname,"DT1",i,4000,5,4005,"drift time 1 (channels)",2,3);
      hTPC_DT[i][1]=MakeH1I_TPC(fname,"DT2",i,4000,5,4005,"drift time 2(channels)",2,3);
      hTPC_DT[i][2]=MakeH1I_TPC(fname,"DT3",i,4000,5,4005,"drift time 3(channels)",2,3);
      hTPC_DT[i][3]=MakeH1I_TPC(fname,"DT4",i,4000,5,4005,"drift time 4(channels)",2,3);
      hTPC_A[i][0]=MakeH1I_TPC(fname,"A1",i,4000,5,4005,"anode 1 ADC(channels)",2,3);
      hTPC_A[i][1]=MakeH1I_TPC(fname,"A2",i,4000,5,4005,"anode 2 ADC(channels)",2,3);
      hTPC_A[i][2]=MakeH1I_TPC(fname,"A3",i,4000,5,4005, "anode 3 ADC(channels)",2,3);
      hTPC_A[i][3]=MakeH1I_TPC(fname,"A4",i,4000,5,4005,"anode 4 ADC(channels)",2,3);
      hTPC_CSUM[i][0]=MakeH1I_TPC(fname,"CSUM1",i,4000,-2000,4005,"control sum 1(channels)",2,3);
      hTPC_CSUM[i][1]=MakeH1I_TPC(fname,"CSUM2",i,4000,-2000,4005,"control sum 2(channels)",2,3);
      hTPC_CSUM[i][2]=MakeH1I_TPC(fname,"CSUM3",i,4000,-2000,4005, "control sum 3(channels)",2,3);
      hTPC_CSUM[i][3]=MakeH1I_TPC(fname,"CSUM4",i,4000,-2000,4005, "control sum 4(channels)",2,3);
      hTPC_XRAW0[i]=MakeH1I_TPC(fname,"Xraw0",i,1000,-2000,2000,"First delay line  x(ch)",2,3);
      hTPC_XRAW1[i]=MakeH1I_TPC(fname,"Xraw1",i,1000,-2000,2000,"Second delay line x(ch)",2,3);
      hTPC_YRAW[i]=MakeH1I_TPC(fname,"Yraw",i,4000,0.0,4000.,"y(ch)",2,3);
      hTPC_X[i]=MakeH1I_TPC(fname,"X",i,800,-100.,100.,"x[mm]",2,3);
      hTPC_Y[i]=MakeH1I_TPC(fname,"Y",i,800,-100.,100.,"y[mm]",2,3);

      sprintf(name,"%s%s",tpc_name_ext1[i],"X_extr.time");
      hTPC_X_extr[i]=MakeH2I(fname,name, 120, -120, 120, 120,0.,12000., "X [mm] ","Extraction Time [ms] ", 2);
      sprintf(name,"%s%s",tpc_name_ext1[i],"Y_extr.time");
      hTPC_Y_extr[i]=MakeH2I(fname,name, 120, -120, 120, 120,0.,12000., "Y [mm] ","Extraction Time [ms] ", 2);
      sprintf(name,"%s%s",tpc_name_ext1[i],"XY");
      hcTPC_XY[i]=MakeH2I(fname,name, 120,-120.,120., 120,-120.,120., "X [mm] ","Y [mm] ", 2);
      sprintf(name,"%s%s",tpc_name_ext1[i],"LTRT");
      hTPC_LTRT[i]=MakeH2I(fname,name, 2048,0,4095, 2048,0,4095, "LT [ch]","RT[ch] ", 2);			
      hTPC_DELTAX[i]=MakeH1I_TPC(fname,"x0-x1",i,100,-10.,10.,"x0-x1[mm]",2,3);
      hTPC_dE[i] = MakeH1I_TPC(fname,"dE_anode",i,4000,5,4005.,"TPC Anode d E [ch]",2,3);
    }

for(int i=0;i<8;i++){
    hTPC_SC_TIMEREF[i] = MakeH1I("TPC/TPC_SC_TimeRef",Form("timeref_%d",i),4000,5,4005,"timeref TDC (channels)",2,3);
  }

  
  // These will be updated in setup.C + TFRSAnalysis.cxx
  // Do not change them here!!!
  Float_t tmp_lim_csum1[7][2]={{30,1800},{30,30},{30,1800},{30,1700},{30,2000},{30,2000},{30,2000}};
  Float_t tmp_lim_csum2[7][2]={{30,1800},{30,30},{30,1800},{30,1700},{30,2000},{30,2000},{30,2000}};
  Float_t tmp_lim_csum3[7][2]={{30,1800},{30,1840},{30,1800},{30,1700},{30,2000},{30,2000},{30,2000}};
  Float_t tmp_lim_csum4[7][2]={{30,1880},{30,1810},{30,1800},{30,1700},{30,2000},{30,2000},{30,2000}};
  
  for(int i=0;i<7;i++)
    { 
      // It seems that cname(2nd) should be different from histoname(last) YT-2020/Jan/24. (if they are same, no error, but no picture shows up in go4)
      cTPC_CSUM[i][0]=MakeWindowCond(Form("TPC/%sCSUM",tpc_name_ext1[i]),Form("CSUM1_%s",tpc_name_ext1[i]), tmp_lim_csum1[i][0], tmp_lim_csum1[i][1],  hTPC_CSUM[i][0]->GetName());
      cTPC_CSUM[i][1]=MakeWindowCond(Form("TPC/%sCSUM",tpc_name_ext1[i]),Form("CSUM2_%s",tpc_name_ext1[i]), tmp_lim_csum2[i][0], tmp_lim_csum2[i][1],  hTPC_CSUM[i][1]->GetName());
      cTPC_CSUM[i][2]=MakeWindowCond(Form("TPC/%sCSUM",tpc_name_ext1[i]),Form("CSUM3_%s",tpc_name_ext1[i]), tmp_lim_csum3[i][0], tmp_lim_csum3[i][1],  hTPC_CSUM[i][2]->GetName());
      cTPC_CSUM[i][3]=MakeWindowCond(Form("TPC/%sCSUM",tpc_name_ext1[i]),Form("CSUM4_%s",tpc_name_ext1[i]), tmp_lim_csum4[i][0], tmp_lim_csum4[i][1],  hTPC_CSUM[i][3]->GetName());
    }      

  // At S2 focal plane
  hTPC_X_S2_TPC_21_22=MakeH1I_TPC("TPC/S2_focus/TPC_21_22","S2_X_TPC_21_22",-1,1000,-100.,100.,"x at S2 focus [mm]",2,3);
  hTPC_Y_S2_TPC_21_22=MakeH1I_TPC("TPC/S2_focus/TPC_21_22","S2_Y_TPC_21_22",-1,1000,-100.,100.,"y at S2 focus [mm]",2,3);
  hTPC_AX_S2_TPC_21_22=MakeH1I_TPC("TPC/S2_focus/TPC_21_22","S2_AX_TPC_21_22",-1,1000,-100.5,100.5,"angl_x at S2 focus [mrad]",2,3);
  hTPC_AY_S2_TPC_21_22=MakeH1I_TPC("TPC/S2_focus/TPC_21_22","S2_AY_TPC_21_22",-1,1000,-100.5,100.5,"angl_y at S2 focus [mrad]",2,3);
  hTPC_X_AX_S2_TPC_21_22 =MakeH2I("TPC/S2_focus/TPC_21_22","S2_X_AX (TPC21_22)", 400,-100.,100., 200,-50.0, 50.0,"X at S2 [mm] ","Angle-X [mrad] ", 2);
  hTPC_Y_AY_S2_TPC_21_22 =MakeH2I("TPC/S2_focus/TPC_21_22","S2_Y_AY (TPC21_22)", 400,-100.,100., 200,-50.0, 50.0,"Y at S2 [mm] ","Angle-Y [mrad] ", 2); 
  hTPC_S2X_TPC21_22_time =MakeH2I("TPC/S2_focus/TPC_21_22","extr. time vs x_S2 (TPC21_22)", 400,-100.,100., 200,-1000.0,6000.0,"X at S2 [mm] ","extr. time [ms] ", 2); 
  hTPC_S2A_TPC21_22_time =MakeH2I("TPC/S2_focus/TPC_21_22","extr. time vs a_S2 (TPC21_22)", 400,-50.,50., 200,-1000.0,6000.0,"A at S2 [mrad] ","extr. time [ms] ", 2); 
  
  hTPC_X_S2_TPC_23_24=MakeH1I_TPC("TPC/S2_focus/TPC_23_24","S2_X_TPC_23_24",-1,1000,-100.,100.,"x at S2 focus [mm]",2,3);
  hTPC_Y_S2_TPC_23_24=MakeH1I_TPC("TPC/S2_focus/TPC_23_24","S2_Y_TPC_23_24",-1,1000,-100.,100.,"y at S2 focus [mm]",2,3);
  hTPC_AX_S2_TPC_23_24=MakeH1I_TPC("TPC/S2_focus/TPC_23_24","S2_AX_TPC_23_24",-1,1000,-100.5,100.5,"angl_x at S2 focus [mrad]",2,3);
  hTPC_AY_S2_TPC_23_24=MakeH1I_TPC("TPC/S2_focus/TPC_23_24","S2_AY_TPC_23_24",-1,1000,-100.5,100.5,"angl_y at S2 focus [mrad]",2,3);
  hTPC_X_AX_S2_TPC_23_24 =MakeH2I("TPC/S2_focus/TPC_23_24","S2_X_AX (TPC23_24)", 400,-100.,100., 200,-50.0, 50.0,"X at S2 [mm] ","Angle-X [mrad] ", 2);
  hTPC_Y_AY_S2_TPC_23_24 =MakeH2I("TPC/S2_focus/TPC_23_24","S2_Y_AY (TPC23_24)", 400,-100.,100., 200,-50.0, 50.0,"Y at S2 [mm] ","Angle-Y [mrad] ", 2);
  hTPC_S2X_TPC23_24_time =MakeH2I("TPC/S2_focus/TPC_23_24","extr. time vs x_S2 (TPC23_24)", 400,-100.,100., 200,-1000.0,6000.0,"X at S2 [mm] ","extr. time [ms] ", 2); //SB21Jun
  hTPC_S2A_TPC23_24_time =MakeH2I("TPC/S2_focus/TPC_23_24","extr. time vs a_S2 (TPC23_24)", 400,-50.,50., 200,-1000.0,6000.0,"A at S2 [mrad] ","extr. time [ms] ", 2); //SB21Jun

  hTPC_X_S2_TPC_22_24=MakeH1I_TPC("TPC/S2_focus/TPC_22_24","S2_X_TPC_22_24",-1,1000,-100.,100.,"x at S2 focus [mm]",2,3);
  hTPC_Y_S2_TPC_22_24=MakeH1I_TPC("TPC/S2_focus/TPC_22_24","S2_Y_TPC_22_24",-1,1000,-100.,100.,"y at S2 focus [mm]",2,3);
  hTPC_AX_S2_TPC_22_24=MakeH1I_TPC("TPC/S2_focus/TPC_22_24","S2_AX_TPC_22_24",-1,1000,-100.5,100.5,"angl_x at S2 focus [mrad]",2,3);
  hTPC_AY_S2_TPC_22_24=MakeH1I_TPC("TPC/S2_focus/TPC_22_24","S2_AY_TPC_22_24",-1,1000,-100.5,100.5,"angl_y at S2 focus [mrad]",2,3);
  hTPC_X_AX_S2_TPC_22_24 =MakeH2I("TPC/S2_focus/TPC_22_24","S2_X_AX (TPC22_24)", 400,-100.,100., 200,-50.0, 50.0,"X at S2 [mm] ","Angle-X [mrad] ", 2);
  hTPC_Y_AY_S2_TPC_22_24 =MakeH2I("TPC/S2_focus/TPC_22_24","S2_Y_AY (TPC22_24)", 400,-100.,100., 200,-50.0, 50.0,"Y at S2 [mm] ","Angle-Y [mrad] ", 2);
  hTPC_S2X_TPC22_24_time =MakeH2I("TPC/S2_focus/TPC_22_24","extr. time vs x_S2 (TPC22_24)", 400,-100.,100., 200,-1000.0,6000.0,"X at S2 [mm] ","extr. time [ms] ", 2); //SB21Jun
  hTPC_S2A_TPC22_24_time =MakeH2I("TPC/S2_focus/TPC_22_24","extr. time vs a_S2 (TPC22_24)", 400,-50.,50., 200,-1000.0,6000.0,"A at S2 [mrad] ","extr. time [ms] ", 2); //SB21Jun

  // At S4 focal plane
  hTPC_X_S4=MakeH1I_TPC("TPC/S4_focus","S4_X",-1,1000,-100.5,100.5,"x at S4 focus [mm]",2,3);
  hTPC_Y_S4=MakeH1I_TPC("TPC/S4_focus","S4_Y",-1,1000,-100.5,100.5,"y at S4 focus [mm]",2,3);
  hTPC_AX_S4=MakeH1I_TPC("TPC/S4_focus","S4_AX",-1,1000,-100.5,100.5, "angl_x at S4 [mrad]",2,3);
  hTPC_AY_S4=MakeH1I_TPC("TPC/S4_focus","S4_AY",-1,1000,-100.5,100.5, "angl_y at S4 [mrad]",2,3);
  hTPC_XAX_S4=MakeH2I("TPC/S4_focus","S4_X_angleX", 400,-100.,100., 250,-50.0,50.0,"X at S4 [mm] ","x angle [mrad] ", 2);
  hTPC_YAY_S4=MakeH2I("TPC/S4_focus","S4_Y_angleY", 400,-100.,100., 250,-50.0,50.0,"Y at S4 [mm] ","y angle [mrad] ", 2);  
  hTPC_S4X_time =MakeH2I("TPC/S4_focus","extr. time vs x_S4", 400,-100.,100., 200,-1000.0,6000.0,"X at S4 [mm] ","extr. time [ms] ", 2); //YT20Jun
  hTPC_S4A_time =MakeH2I("TPC/S4_focus","extr. time vs a_S4", 400,-50.,50., 200,-1000.0,6000.0,"A at S4 [mrad] ","extr. time [ms] ", 2); //YT20Jun

  // S4-vs-S2
  hTPC_XS4_AXS2_TPC_21_22 = MakeH2I("TPC/S4_vs_S2","XS4_AXS2_TPC_21_22", 400,-100.,100., 250,-25.0,25.0,"X at S4 [mm] ","angle(x) at S2 [mrad] ", 2);
  hTPC_XS4_AXS2_TPC_23_24 = MakeH2I("TPC/S4_vs_S2","XS4_AXS2_TPC_23_24", 400,-100.,100., 250,-25.0,25.0,"X at S4 [mm] ","angle(x) at S2 [mrad] ", 2);
  hTPC_XS4_AXS2_TPC_22_24 = MakeH2I("TPC/S4_vs_S2","XS4_AXS2_TPC_22_24", 400,-100.,100., 250,-25.0,25.0,"X at S4 [mm] ","angle(x) at S2 [mrad] ", 2);
  hTPC_YS4_AYS2_TPC_21_22 = MakeH2I("TPC/S4_vs_S2","YS4_AYS2_TPC_21_22", 400,-100.,100., 250,-25.0,25.0,"Y at S4 [mm] ","angle(y) at S2 [mrad] ", 2);
  hTPC_YS4_AYS2_TPC_23_24 = MakeH2I("TPC/S4_vs_S2","YS4_AYS2_TPC_23_24", 400,-100.,100., 250,-25.0,25.0,"Y at S4 [mm] ","angle(y) at S2 [mrad] ", 2);
  hTPC_YS4_AYS2_TPC_22_24 = MakeH2I("TPC/S4_vs_S2","YS4_AYS2_TPC_22_24", 400,-100.,100., 250,-25.0,25.0,"Y at S4 [mm] ","angle(y) at S2 [mrad] ", 2);
  
  // At detector and At target
  hTPC21_22_SC21x= MakeH1I_TPC("TPC/At_Detector","TPC21_22_SC21x",-1, 221,-110.5,110.5,"X tracked at SC21 [mm]",2,3);
  hTPC21_22_SC21y= MakeH1I_TPC("TPC/At_Detector","TPC21_22_SC21y",-1, 221,-110.5,110.5,"Y tracked at SC21 [mm]",2,3);
  hTPC23_24_SC21x= MakeH1I_TPC("TPC/At_Detector","TPC23_24_SC21x",-1, 221,-110.5,110.5,"X tracked at SC21 [mm]",2,3);
  hTPC23_24_SC21y= MakeH1I_TPC("TPC/At_Detector","TPC23_24_SC21y",-1, 221,-110.5,110.5,"Y tracked at SC21 [mm]",2,3);
  hTPC22_24_SC21x= MakeH1I_TPC("TPC/At_Detector","TPC22_24_SC21x",-1, 221,-110.5,110.5,"X tracked at SC21 [mm]",2,3);
  hTPC22_24_SC21y= MakeH1I_TPC("TPC/At_Detector","TPC22_24_SC21y",-1, 221,-110.5,110.5,"Y tracked at SC21 [mm]",2,3);
  
  hTPC21_22_SC22x= MakeH1I_TPC("TPC/At_Detector","TPC21_22_SC22x",-1, 221,-110.5,110.5,"X tracked at SC22 [mm]",2,3);
  hTPC21_22_SC22y= MakeH1I_TPC("TPC/At_Detector","TPC21_22_SC22y",-1, 221,-110.5,110.5,"Y tracked at SC22 [mm]",2,3);
  hTPC23_24_SC22x= MakeH1I_TPC("TPC/At_Detector","TPC23_24_SC22x",-1, 221,-110.5,110.5,"X tracked at SC22 [mm]",2,3);
  hTPC23_24_SC22y= MakeH1I_TPC("TPC/At_Detector","TPC23_24_SC22y",-1, 221,-110.5,110.5,"Y tracked at SC22 [mm]",2,3);
  hTPC22_24_SC22x= MakeH1I_TPC("TPC/At_Detector","TPC22_24_SC22x",-1, 221,-110.5,110.5,"X tracked at SC22 [mm]",2,3);
  hTPC22_24_SC22y= MakeH1I_TPC("TPC/At_Detector","TPC22_24_SC22y",-1, 221,-110.5,110.5,"Y tracked at SC22 [mm]",2,3);

  hTPC21_22_S2target_x = MakeH1I_TPC("TPC/At_Target","TPC21_22_S2target_x",-1, 221,-110.5,110.5,"X tracked at S2target [mm]",2,3);
  hTPC21_22_S2target_y = MakeH1I_TPC("TPC/At_Target","TPC21_22_S2target_y",-1, 221,-110.5,110.5,"Y tracked at S2target [mm]",2,3);
  hTPC23_24_S2target_x = MakeH1I_TPC("TPC/At_Target","TPC23_24_S2target_x",-1, 221,-110.5,110.5,"X tracked at S2target [mm]",2,3);
  hTPC23_24_S2target_y = MakeH1I_TPC("TPC/At_Target","TPC23_24_S2target_y",-1, 221,-110.5,110.5,"Y tracked at S2target [mm]",2,3);
  hTPC22_24_S2target_x = MakeH1I_TPC("TPC/At_Target","TPC22_24_S2target_x",-1, 221,-110.5,110.5,"X tracked at S2target [mm]",2,3);
  hTPC22_24_S2target_y = MakeH1I_TPC("TPC/At_Target","TPC22_24_S2target_y",-1, 221,-110.5,110.5,"Y tracked at S2target [mm]",2,3);
  
  hTPC_SC41x     = MakeH1I_TPC("TPC/At_Detector","TPC_SC41x",-1, 221,-110.5,110.5,"X tracked at SC41 [mm]",2,3);
  hTPC_SC41y     = MakeH1I_TPC("TPC/At_Detector","TPC_SC41y",-1, 221,-110.5,110.5,"Y tracked at SC41 [mm]",2,3);
  hTPC_SC42x     = MakeH1I_TPC("TPC/At_Detector","TPC_SC42x",-1, 221,-110.5,110.5,"X tracked at SC42 [mm]",2,3);
  hTPC_SC42y     = MakeH1I_TPC("TPC/At_Detector","TPC_SC42y",-1, 221,-110.5,110.5,"Y tracked at SC42 [mm]",2,3);
  hTPC_SC43x     = MakeH1I_TPC("TPC/At_Detector","TPC_SC43x",-1, 221,-110.5,110.5,"X tracked at SC43 [mm]",2,3);
  hTPC_SC43y     = MakeH1I_TPC("TPC/At_Detector","TPC_SC43y",-1, 221,-110.5,110.5,"Y tracked at SC43 [mm]",2,3);

  hTPC_MUSIC41x     = MakeH1I_TPC("TPC/At_Detector","TPC_MUSIC41x",-1, 221,-110.5,110.5,"X tracked at MUSIC41 [mm]",2,3);
  hTPC_MUSIC41y     = MakeH1I_TPC("TPC/At_Detector","TPC_MUSIC41y",-1, 221,-110.5,110.5,"Y tracked at MUSIC41 [mm]",2,3);
  hTPC_MUSIC42x     = MakeH1I_TPC("TPC/At_Detector","TPC_MUSIC42x",-1, 221,-110.5,110.5,"X tracked at MUSIC42 [mm]",2,3);
  hTPC_MUSIC42y     = MakeH1I_TPC("TPC/At_Detector","TPC_MUSIC42y",-1, 221,-110.5,110.5,"Y tracked at MUSIC42 [mm]",2,3);
  hTPC_MUSIC43x     = MakeH1I_TPC("TPC/At_Detector","TPC_MUSIC43x",-1, 221,-110.5,110.5,"X tracked at MUSIC43 [mm]",2,3);
  hTPC_MUSIC43y     = MakeH1I_TPC("TPC/At_Detector","TPC_MUSIC43y",-1, 221,-110.5,110.5,"Y tracked at MUSIC43 [mm]",2,3);

  hTPC_S4target_x = MakeH1I_TPC("TPC/At_Target","S4target_x",-1, 221,-110.5,110.5,"X tracked at S4target [mm]",2,3);
  hTPC_S4target_y = MakeH1I_TPC("TPC/At_Target","S4target_y",-1, 221,-110.5,110.5,"Y tracked at S4target [mm]",2,3);
 
  for(int i=0;i<7;i++){
    char name[100];  
    //    sprintf(name,"TPC/TPC%d",i+1);
    sprintf(name,"TPC/%s",tpc_folder_ext1[i]);
    MakePic(name,"Amplitudes",4,2,hTPC_A[i][0],hTPC_A[i][1],hTPC_A[i][2],hTPC_A[i][3],hTPC_L0[i],hTPC_R0[i],hTPC_L1[i],hTPC_R1[i]);
    MakePic(name,"RawTimes",4,2,hTPC_DT[i][0],hTPC_DT[i][1],hTPC_DT[i][2],hTPC_DT[i][3],hTPC_LT0[i],hTPC_RT0[i],hTPC_LT1[i],hTPC_RT1[i]);
    MakePic(name,"CSums",2,2,hTPC_CSUM[i][0],hTPC_CSUM[i][1],hTPC_CSUM[i][2],hTPC_CSUM[i][3]);
  }
}

// Creation of Si data & histograms
void TFRSCalibrProc::Create_SI_Hist()
{

  char name1[100];
  char name2[100];
  char name3[100];
  char name4[100];
  char name5[100];
  char name6[100];
  for(int i=0;i<32;i++){
    sprintf(name1,"dssd_e_det1_%d",i);
    sprintf(name2,"dssd_e_det2_%d",i);
    sprintf(name3,"dssd_e_det3_%d",i);
    sprintf(name4,"dssd_e_det4_%d",i);
    sprintf(name5,"dssd_e_det5_%d",i);
    sprintf(name6,"dssd_e_det6_%d",i);
    hdssd_e_det1[i] = MakeH1I("DSSD/Detector1/energy",name1,1000,0,10000,"",2,3);
    hdssd_e_det2[i] = MakeH1I("DSSD/Detector2/energy",name2,1000,0,10000,"",2,3);
    hdssd_e_det3[i] = MakeH1I("DSSD/Detector3/energy",name3,1000,0,10000,"",2,3);
    hdssd_e_det4[i] = MakeH1I("DSSD/Detector4/energy",name4,1000,0,10000,"",2,3);
    hdssd_e_det5[i] = MakeH1I("DSSD/Detector5/energy",name5,1000,0,10000,"",2,3);
    hdssd_e_det6[i] = MakeH1I("DSSD/Detector6/energy",name6,1000,0,10000,"",2,3); 

    sprintf(name1,"dssd_e_det1_%d_decay",i);
    sprintf(name2,"dssd_e_det2_%d_decay",i);
    sprintf(name3,"dssd_e_det3_%d_decay",i);
    sprintf(name4,"dssd_e_det4_%d_decay",i);
    sprintf(name5,"dssd_e_det5_%d_decay",i);
    sprintf(name6,"dssd_e_det6_%d_decay",i);
    hdssd_e_det1_dec[i] = MakeH1I("DSSD/Detector1/energy",name1,1000,0,10000,"",2,3);
    hdssd_e_det2_dec[i] = MakeH1I("DSSD/Detector2/energy",name2,1000,0,10000,"",2,3);
    hdssd_e_det3_dec[i] = MakeH1I("DSSD/Detector3/energy",name3,1000,0,10000,"",2,3);
    hdssd_e_det4_dec[i] = MakeH1I("DSSD/Detector4/energy",name4,1000,0,10000,"",2,3);
    hdssd_e_det5_dec[i] = MakeH1I("DSSD/Detector5/energy",name5,1000,0,10000,"",2,3);
    hdssd_e_det6_dec[i] = MakeH1I("DSSD/Detector6/energy",name6,1000,0,10000,"",2,3);

  }
  /*
  hdssd_xmaxenergy = MakeH1I("DSSD","X dssd max energy (impl.) ",10000,0,20000);
  hdssd_xmaxindex = MakeH1I("DSSD","X max energy index (impl.) ",16,-0.5,15.5);
  hdssd_ymaxenergy = MakeH1I("DSSD","Y dssd max energy  (impl.) ",10000,0,20000);
  hdssd_ymaxindex = MakeH1I("DSSD","Y max energy index (impl.) ",16,-0.5,15.5);
  hdssd_xymaxindex=MakeH2I("DSSD","XY_maxindex (impl.) ",16,0,16,16,0,16, "X max energy index (impl.) ","y max energy index",2);  

  hdssd_xmaxenergy_dec = MakeH1I("DSSD","X dssd max energy (decay)",5000,0,10000);
  hdssd_xmaxindex_dec = MakeH1I("DSSD","X max energy index (decay)",16,-0.5,15.5);
  hdssd_ymaxenergy_dec = MakeH1I("DSSD","Y dssd max energy (decay)",5000,0,10000);
  hdssd_ymaxindex_dec = MakeH1I("DSSD","Y max energy index (decay)",16,-0.5,15.5);
  hdssd_xymaxindex_dec = MakeH2I("DSSD","XY_maxindex (decay)",16,-0.5,15.5,16,-0.5,15.5,"X max energy index (decay)","y max energy index",2);
  */
  
  hsi_e1 = MakeH1I("Si/e1","Si_1 DU energy [keV]",5000,0,10000);
  hsi_e2 = MakeH1I("Si/e2","Si_2 DU energy [keV]",5000,0,10000);
  hsi_e3 = MakeH1I("Si/e3","Si_3 gate energy [keV]",5000,0,10000);
  hsi_e4 = MakeH1I("Si/e4","Si_4 sled energy [keV]",5000,0,10000);

  hsi_e1Trig = MakeH1I("Si/e1Trig","Si_1 DU energy with self trigger  [keV]",5000,0,10000);
  hsi_e2Trig = MakeH1I("Si/e2Trig","Si_2 DU energy  with self trigger [keV]",5000,0,10000);
  hsi_e3Trig = MakeH1I("Si/e3Trig","Si_3 gate energy with self trigger [keV]",5000,0,10000);
  hsi_e4Trig = MakeH1I("Si/e4Trig","Si_4 sled energy  with self trigger [keV]",5000,0,10000);
}

// Creation of Channeltron data & histograms
void TFRSCalibrProc::Create_CT_Hist()
{
  hct_all = MakeH1I("Ct","Ct_all",5000,0,10000);
  hct_trigger_DU = MakeH1I("Ct","Ct_trigger_DU",5,0,5);
  hct_trigger_SY = MakeH1I("Ct","Ct_trigger_SY",5,0,5);
  hct_DU = MakeH1I("Ct","Ct_DU",5000,0,10000);
  hct_SY = MakeH1I("Ct","Ct_SY",5000,0,10000);
}

// Creation of Electron Current data & histograms
void TFRSCalibrProc::Create_ElCurrent_Hist()
{
  helcurrent = MakeH1I("El Current","El Current",5000,0,10000);
}

void TFRSCalibrProc::InitProcessor()
{
  focx_s2m = 0.;
  focy_s2m = 0.;
  angle_x_s2m = 0.;
  angle_y_s2m = 0.;
}


void TFRSCalibrProc::Process_Scaler_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt){

  // TFRSCalibrProc::scaler_ch_1kHz and
  // TFRSCalibrProc::scaler_ch_spillstart should be filled in Create_Scaler_Hist();
  if(13 == src.trigger || 12 == src.trigger) return; // skip spill trigger

  if(1==scaler_check_first_event){
    for(int ii=0; ii<64; ii++){
       scaler_initial[ii] = src.sc_long[ii];
       scaler_previous[ii] = src.sc_long[ii];
    }
    scaler_check_first_event = 0;
  }

  int time_in_ms  = src.sc_long[scaler_ch_1kHz]  - scaler_initial[scaler_ch_1kHz];
  int spill_count = src.sc_long[scaler_ch_spillstart] - scaler_initial[scaler_ch_spillstart];
  int ibin_for_s      = ((time_in_ms / 1000) % 1000) + 1;
  int ibin_for_100ms  = ((time_in_ms / 100) % 4000) + 1;
  int ibin_for_spill  = (spill_count % 1000) +1; 
  tgt.extraction_time_ms += src.sc_long[scaler_ch_1kHz] - scaler_previous[scaler_ch_1kHz];
  if(0 != src.sc_long[scaler_ch_spillstart] - scaler_previous[scaler_ch_spillstart]){
    tgt.extraction_time_ms = 0; 
  }
    
  //now fill histograms
  for(int ii=0; ii<64; ii++){
    UInt_t increase_scaler_temp =  src.sc_long[ii]  - scaler_previous[ii];
    //    printf("ch %d: this event = %lld, increase =%lld\n",ii,src.sc_long[ii],increase_scaler_temp);
    hScaler_per_s[ii]->AddBinContent(ibin_for_s, increase_scaler_temp);
    hScaler_per_100ms[ii]->AddBinContent(ibin_for_100ms, increase_scaler_temp);
    hScaler_per_spill[ii]->AddBinContent(ibin_for_spill, increase_scaler_temp);    
  }
  
  int ibin_clean_for_s      = (((time_in_ms / 1000) +20) % 1000) + 1; // 
  int ibin_clean_for_100ms  = (((time_in_ms / 100) +200 ) % 4000) + 1; //
  int ibin_clean_for_spill  = ((spill_count + 990 )% 20) +1; // 
  for(int ii=0; ii<64; ii++){
    hScaler_per_s[ii]->SetBinContent(ibin_clean_for_s, 0);
    hScaler_per_100ms[ii]->SetBinContent(ibin_clean_for_100ms, 0);
    hScaler_per_spill[ii]->SetBinContent(ibin_clean_for_spill, 0);
  }
  
  // put current data into _previous for the next event
  for(int ii=0; ii<64; ii++){
    scaler_previous[ii] = src.sc_long[ii];
  }
  
  return ;
}
  


void TFRSCalibrProc::Process_MW_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt)
{

  /*   Naming conventions:  index     detector                      		 */
  /*                         0         MW11                                 */
  /*                         1         MW21                                 */
  /*                         2         MW22                                  */
  /*                         3         MW31                                 */
  /*                         4         MW51                                  */
  /*                         5         MW71                                  */
  /*                         6         MW81                                  */
  /*                         7         MW82                                  */
  /////////////////////////////////////////////////////////////////////////////
 // int max_index = 13; //upto MWB2 (09.07.2018) /*  up to S3 */
  int max_index = 8; // MW11, 21,22,31,51,71,81,82 (15.11.19)

  for(int i=0;i<max_index;i++)
    {	
      /***************/
      /* Raw Spectra */
      /***************/
      hMW_AN[i]->Fill(src.mw_an[i]);
      hMW_XL[i]->Fill(src.mw_xl[i]);
      hMW_XR[i]->Fill(src.mw_xr[i]);
      hMW_YU[i]->Fill(src.mw_yu[i]);
      hMW_YD[i]->Fill(src.mw_yd[i]);
      
      /********************************************/
      /* Calculate the sum spectra and conditions */
      /********************************************/
      
      /* better test first existence of xl, xr, an before filling of xsum */
      
      if(src.mw_an[i] && src.mw_xl[i] && src.mw_xr[i])
	{
	  // if(src.mw_xl[i]&&src.mw_xr[i]) {
	  tgt.mw_xsum[i] = 1000+(src.mw_xl[i] - src.mw_an[i]) + (src.mw_xr[i] - src.mw_an[i]);
      
	  // tgt.mw_xsum[i] = (src.mw_xl[i]) + (src.mw_xr[i]); //when an doesn't work
	  hMW_XSUM[i]->Fill(tgt.mw_xsum[i]);
	}

      tgt.b_mw_xsum[i] = cMW_XSUM[i]->Test(tgt.mw_xsum[i]);
      
      
      /* better test first existence of yu, yd, an before filling of ysum */
      
      if(src.mw_an[i] && src.mw_yu[i] && src.mw_yd[i])
	{
	   
	  //if(src.mw_yu[i]&&src.mw_yd[i]) {
	  tgt.mw_ysum[i] = 1000+(src.mw_yu[i] - src.mw_an[i]) + (src.mw_yd[i] - src.mw_an[i]);	  
	  
	  //tgt.mw_ysum[i] = (src.mw_yu[i]) + (src.mw_yd[i]); //when an doesn't work			
	  hMW_YSUM[i]->Fill(tgt.mw_ysum[i]);          
	}
      
      tgt.b_mw_ysum[i] = cMW_YSUM[i]->Test(tgt.mw_ysum[i]);
      
    
      /*******************************************************************/
      /* If the signals in x and y are valid, calculate position spectra */
      /*******************************************************************/
      
      if (tgt.b_mw_xsum[i])
	{
	  //      Int_t r_x = src.mw_xl[i] - src.mw_xr[i];
	  Float_t r_x = src.mw_xl[i] *  mw->gain_tdc[1][i] - src.mw_xr[i] *  mw->gain_tdc[2][i]; //14.09.05 CN+AM
	  tgt.mw_x[i] = mw->x_factor[i] * r_x + mw->x_offset[i];
	  hMW_X[i]->Fill(tgt.mw_x[i]);
	}
    
      if (tgt.b_mw_ysum[i])
	{
	  //      Int_t r_y = src.mw_yd[i] - src.mw_yu[i];
	  Float_t r_y = src.mw_yd[i] *  mw->gain_tdc[4][i] - src.mw_yu[i] *  mw->gain_tdc[3][i]; //14.09.05 CN+AM
	  tgt.mw_y[i] = mw->y_factor[i] * r_y + mw->y_offset[i];
	  hMW_Y[i]->Fill(tgt.mw_y[i]);
	}

    
      if(tgt.b_mw_xsum[i] && tgt.b_mw_ysum[i])
	{
	  hMW_XY[i]->Fill(tgt.mw_x[i], tgt.mw_y[i]);  
	}
      
    } // for(int i=0;i<max_index;i++)


  /*********************************************/
  /* S2 Angle and transformed position spectra */
  /*********************************************/
  
  Float_t  dist_MW21_MW22  = frs->dist_MW22  - frs->dist_MW21;
  Float_t  dist_MW22_focS2 = frs->dist_focS2 - frs->dist_MW22;
  Float_t  dist_MW22_SC21  = frs->dist_SC21  - frs->dist_MW22;
  Float_t  dist_MW22_SC22  = frs->dist_SC22  - frs->dist_MW22;
  

  if (tgt.b_mw_xsum[1] && tgt.b_mw_xsum[2])
    {
      /* MW21 and MW22 X okay */
      /*  X angle at S2  [mrad]:  */
      tgt.angle_x_s2 = (tgt.mw_x[2]-tgt.mw_x[1])/dist_MW21_MW22*1000.;
      hMW_xAngS2->Fill(tgt.angle_x_s2);

      /*  X at nominal S2 focus:  */
      tgt.focx_s2 = tgt.mw_x[2] + dist_MW22_focS2 * tgt.angle_x_s2/1000.;
      hMW_xFocS2->Fill(tgt.focx_s2);
      
      /*  X at SC21 position:    */
      tgt.mw_sc21_x = tgt.mw_x[2] + dist_MW22_SC21 * tgt.angle_x_s2/1000.;
      hMW_SC21x->Fill(tgt.mw_sc21_x);

      /*  X at SC22 position:    */
      tgt.mw_sc22_x = tgt.mw_x[2] + dist_MW22_SC22 * tgt.angle_x_s2/1000.;
      hMW_SC22x->Fill(tgt.mw_sc22_x);
      

      /* 'real' z-position of S2 X focus (cm) */
      Float_t rh = (tgt.angle_x_s2 - angle_x_s2m);
      if(fabs(rh)>1e-4)
	{
	  tgt.z_x_s2 = ((focx_s2m - tgt.focx_s2)/rh)*100. + frs->dist_focS2/10.;  
	  hMW_zxS2->Fill(tgt.z_x_s2);
	}
    
      /* keep values for next event */
      focx_s2m = tgt.focx_s2; 
      angle_x_s2m = tgt.angle_x_s2;
    }
  
  if (tgt.b_mw_ysum[1] && tgt.b_mw_ysum[2])
    {
      /* MW21 and MW22 Y okay */
      /*  Y angle at S2 [mrad]:   */
      tgt.angle_y_s2 = (tgt.mw_y[2] - tgt.mw_y[1])/dist_MW21_MW22*1000.;
      hMW_yAngS2->Fill(tgt.angle_y_s2);
      
      /*  Y at nominal S2 focus:  */
      tgt.focy_s2 = tgt.mw_y[2] + dist_MW22_focS2 * tgt.angle_y_s2/1000.;
      hMW_yFocS2->Fill(tgt.focy_s2);

      /* 'real' z-position of S2 Y focus (cm) */
      Float_t rh = (tgt.angle_y_s2 - angle_y_s2m);
      if(fabs(rh)>1.e-4)
	{
	  tgt.z_y_s2 = ((focy_s2m - tgt.focy_s2)/rh)*100. + frs->dist_focS2/10.;  
	  hMW_zyS2->Fill(tgt.z_y_s2);
	}
      
      /* keep values for next event */
      focy_s2m = tgt.focy_s2; 
      angle_y_s2m = tgt.angle_y_s2; 
    }
  
  if (tgt.b_mw_ysum[1] && tgt.b_mw_ysum[2] && tgt.b_mw_xsum[1] && tgt.b_mw_xsum[2])
    hMW_FocS2->Fill(tgt.focx_s2,tgt.focy_s2); 

}


//////////////////////////////////////////////////////////////////
///  ***********TPC Analysis*************************** //////////
void TFRSCalibrProc::Process_TPC_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt)
{

 //================================
  // Nomenclature for TPCs
  //================================
  // TPCs at S2
  // TPC 1 = TPC 21 (in vaccum) [i=0]
  // TPC 2 = TPC 22 (in vaccum) [i=1]
  // TPC 3 = TPC 23 (in air)    [i=2]
  // TPC 4 = TPC 24 (in air)    [i=3]

  // TPCs at S4
  // TPC 5 = TPC 41 (in air)    [i=4]
  // TPC 6 = TPC 42 (in air)    [i=5]

  // TPC at S3
  // TPC 7 = TPC 31             [i=6]
  for(int i=0;i<8;i++)
    {  
      hTPC_SC_TIMEREF[i] ->Fill(src.tpc_timeref[i]);
    }
  
  for(int i=0;i<7;i++)
    {  
      if (bDrawHist)
	{
	  hTPC_L0[i]->Fill(src.tpc_l[i][0]);
	  hTPC_R0[i]->Fill(src.tpc_r[i][0]);
	  hTPC_L1[i]->Fill(src.tpc_l[i][1]);
	  hTPC_R1[i]->Fill(src.tpc_r[i][1]);
	  hTPC_LT0[i]->Fill(src.tpc_lt[i][0]);
	  hTPC_RT0[i]->Fill(src.tpc_rt[i][0]);
	  hTPC_LT1[i]->Fill(src.tpc_lt[i][1]);
	  hTPC_RT1[i]->Fill(src.tpc_rt[i][1]);
	  
	  hTPC_LTRT[i]->Fill(src.tpc_lt[i][0],src.tpc_rt[i][1]);
	}
      int count =0;
      Int_t r_y = 0;
      
      int countx =0;
      Int_t r_x0 = 0;
      Int_t r_x1 = 0;
      
      tgt.tpc_y[i] = 0;
      tgt.tpc_x[i] = 9999;

      double temp_de = 1.0;int temp_count = 0;
      for(int j=0;j<4;j++)
	{
	  if (bDrawHist)
	    {
	      hTPC_DT[i][j]->Fill(src.tpc_dt[i][j]);
	      hTPC_A[i][j]->Fill(src.tpc_a[i][j]);
	    }

	  if( src.tpc_a[i][j] - tpc->a_offset[i][j] >5.0){
	    temp_de *= (src.tpc_a[i][j] - tpc->a_offset[i][j]);  temp_count++;
	  }
	  

	  //// calculate control sums
	  if(j < 2)
	    tgt.tpc_csum[i][j] = (src.tpc_lt[i][0] + src.tpc_rt[i][0]- 2*src.tpc_dt[i][j]);
	  else
	    tgt.tpc_csum[i][j] = (src.tpc_lt[i][1] + src.tpc_rt[i][1]- 2*src.tpc_dt[i][j]);


	  //      if((src.de_42l>230&&src.de_42l<450)||(src.de_42r>540&&src.de_42r<750)){
	  if (bDrawHist) 
	    hTPC_CSUM[i][j]->Fill(tgt.tpc_csum[i][j]);
	  tgt.b_tpc_csum[i][j] = cTPC_CSUM[i][j]->Test(tgt.tpc_csum[i][j]);
	  //      }
	  
	  if(src.tpc_lt[i][0]==0 && src.tpc_rt[i][0]==0 && j<2)
	    tgt.b_tpc_csum[i][j]=0;
      
	  if(src.tpc_lt[i][1]==0 && src.tpc_rt[i][1]==0 && j>1)
	    tgt.b_tpc_csum[i][j]=0;
      
	  if (tgt.b_tpc_csum[i][j])
	    {
	      r_y += src.tpc_dt[i][j];
	      //  tgt.tpc_y[i] += tpc->y_factor[i][j]*src.tpc_dt[i][j] + tpc->y_offset[i][j];
	      int id_tpc_sc_timeref = tpc->id_tpc_timeref[i];
	      // printf("i=%d, j=%d, (dt - timeref + timerefcalib) tpcdt=%d, timeref = %d, timerefcalib=%f \n",i,j,src.tpc_dt[i][j] ,src.tpc_timeref[id_tpc_sc_timeref] , tpc->timeref_calibrun[i]);
	      tgt.tpc_y[i] += tpc->y_factor[i][j]*(src.tpc_dt[i][j] - src.tpc_timeref[id_tpc_sc_timeref] + tpc->timeref_calibrun[i])+ tpc->y_offset[i][j];
	      count++;
	    }
	}

      if(4==temp_count){
	tgt.tpc_de[i] = sqrt(sqrt( temp_de ));
	tgt.b_tpc_de[i] = kTRUE;
	if(bDrawHist){ hTPC_dE[i]->Fill(tgt.tpc_de[i]); }
      }

      if (tgt.b_tpc_csum[i][0] || tgt.b_tpc_csum[i][1])
	{
	  r_x0 =  src.tpc_lt[i][0]-src.tpc_rt[i][0];
	  //          r_x0 =  src.tpc_lt[i][0];
	  
	  tgt.tpc_x[i]=tpc->x_factor[i][0]*r_x0 + tpc->x_offset[i][0];
	  countx++;
	}
      
      if (tgt.b_tpc_csum[i][2] || tgt.b_tpc_csum[i][3])
	{
	  r_x1 =  src.tpc_lt[i][1]-src.tpc_rt[i][1];
	  if (countx == 0)
	    tgt.tpc_x[i]=tpc->x_factor[i][1]*r_x1 + tpc->x_offset[i][1];
	  else
	    tgt.tpc_x[i]+=tpc->x_factor[i][1]*r_x1 + tpc->x_offset[i][1];
	  countx++;
	}

      tgt.b_tpc_xy[i] = kFALSE;  // HWE

      if (countx > 0)
	{
	  tgt.tpc_y[i] = tgt.tpc_y[i]/count;
	  tgt.tpc_x[i] = tgt.tpc_x[i]/countx;
	  //Int_t r_x=src.tpc_lt[i]-src.tpc_rt[i];
	  //tgt.tpc_x[i]=tpc->x_factor[i]*r_x + tpc->x_offset[i];
	  
	  //      if(r_x0<-40)
	  
	  if (bDrawHist)
	    {
	      hTPC_XRAW0[i]->Fill(r_x0);
	      hTPC_XRAW1[i]->Fill(r_x1);
	      hTPC_YRAW[i]->Fill(r_y/count); 
	      hTPC_X[i]->Fill(tgt.tpc_x[i]);
	      hTPC_Y[i]->Fill(tgt.tpc_y[i]);
	      hcTPC_XY[i]->Fill(tgt.tpc_x[i],tgt.tpc_y[i]);
	      hTPC_X_extr[i]->Fill(tgt.tpc_x[i],tgt.extraction_time_ms);
	      hTPC_Y_extr[i]->Fill(tgt.tpc_y[i],tgt.extraction_time_ms);
	      //    	 }
	    }
	  tgt.b_tpc_xy[i] = kTRUE;
	}
       
      if(countx>1)
	{
	  float x0=tpc->x_factor[i][0]*r_x0 + tpc->x_offset[i][0];
	  float x1=tpc->x_factor[i][1]*r_x1 + tpc->x_offset[i][1];
	  if (bDrawHist)
	    hTPC_DELTAX[i]->Fill(x0-x1);
	}    
    }


  //==========================
  // Distances of TPCs at S2
  //==========================

  Float_t dist_TPC21_TPC22 = frs->dist_TPC22 - frs->dist_TPC21; 
  Float_t dist_TPC23_TPC24 = frs->dist_TPC24 - frs->dist_TPC23; 
  Float_t dist_TPC22_TPC24 = frs->dist_TPC24 - frs->dist_TPC22; 
  Float_t dist_TPC21_focS2 = frs->dist_TPC21 - frs->dist_focS2; 
  Float_t dist_TPC22_focS2 = frs->dist_TPC22 - frs->dist_focS2; 
  Float_t dist_TPC23_focS2 = frs->dist_TPC23 - frs->dist_focS2; 
  Float_t dist_TPC41_TPC42 = frs->dist_TPC42 - frs->dist_TPC41; 
  Float_t dist_TPC42_focS4 = frs->dist_focS4 - frs->dist_TPC42; 

 
  //=================================
  // Tracking with TPC 21 and TPC 22 
  //=================================
  
  if (tgt.b_tpc_xy[0]&&tgt.b_tpc_xy[1])
    {
      tgt.tpc_angle_x_s2_foc_21_22 = (tgt.tpc_x[1] - tgt.tpc_x[0])/dist_TPC21_TPC22*1000.;
      tgt.tpc_angle_y_s2_foc_21_22 = (tgt.tpc_y[1] - tgt.tpc_y[0])/dist_TPC21_TPC22*1000.;
      tgt.tpc_x_s2_foc_21_22 = -tgt.tpc_angle_x_s2_foc_21_22 * dist_TPC21_focS2/1000. + tgt.tpc_x[0]; //check
      tgt.tpc_y_s2_foc_21_22 = -tgt.tpc_angle_y_s2_foc_21_22 * dist_TPC21_focS2/1000. + tgt.tpc_y[0]; //check

      Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;   
      tgt.tpc21_22_sc21_x = (tgt.tpc_angle_x_s2_foc_21_22/1000.*dist_SC21_focS2)+tgt.tpc_x_s2_foc_21_22;
      tgt.tpc21_22_sc21_y = (tgt.tpc_angle_y_s2_foc_21_22/1000.*dist_SC21_focS2)+tgt.tpc_y_s2_foc_21_22;
      Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;   
      tgt.tpc21_22_sc22_x = (tgt.tpc_angle_x_s2_foc_21_22/1000.*dist_SC22_focS2)+tgt.tpc_x_s2_foc_21_22;
      tgt.tpc21_22_sc22_y = (tgt.tpc_angle_y_s2_foc_21_22/1000.*dist_SC22_focS2)+tgt.tpc_y_s2_foc_21_22;     
      Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;   
      tgt.tpc21_22_s2target_x = (tgt.tpc_angle_x_s2_foc_21_22/1000.*dist_S2target_focS2)+tgt.tpc_x_s2_foc_21_22;
      tgt.tpc21_22_s2target_y = (tgt.tpc_angle_y_s2_foc_21_22/1000.*dist_S2target_focS2)+tgt.tpc_y_s2_foc_21_22;     
    
      if (bDrawHist)
	{
	  hTPC_X_S2_TPC_21_22->Fill(tgt.tpc_x_s2_foc_21_22);
	  hTPC_Y_S2_TPC_21_22->Fill(tgt.tpc_y_s2_foc_21_22);
	  hTPC_AX_S2_TPC_21_22->Fill(tgt.tpc_angle_x_s2_foc_21_22);
	  hTPC_AY_S2_TPC_21_22->Fill(tgt.tpc_angle_y_s2_foc_21_22);
	  hTPC_X_AX_S2_TPC_21_22->Fill(tgt.tpc_x_s2_foc_21_22, tgt.tpc_angle_x_s2_foc_21_22);
	  hTPC_Y_AY_S2_TPC_21_22->Fill(tgt.tpc_y_s2_foc_21_22, tgt.tpc_angle_y_s2_foc_21_22);
	  hTPC_S2X_TPC21_22_time->Fill(tgt.tpc_x_s2_foc_21_22,  tgt.extraction_time_ms);
	  hTPC_S2A_TPC21_22_time->Fill(tgt.tpc_angle_x_s2_foc_21_22,  tgt.extraction_time_ms);
	  hTPC21_22_SC21x->Fill(tgt.tpc21_22_sc21_x);
	  hTPC21_22_SC21y->Fill(tgt.tpc21_22_sc21_y);
	  hTPC21_22_SC22x->Fill(tgt.tpc21_22_sc22_x);
	  hTPC21_22_SC22y->Fill(tgt.tpc21_22_sc22_y);
	  hTPC21_22_S2target_x->Fill(tgt.tpc21_22_s2target_x);
	  hTPC21_22_S2target_y->Fill(tgt.tpc21_22_s2target_y);	   
      	}
    }

  //=================================
  // Tracking with TPC 23 and TPC 24 
  //=================================
  
   if (tgt.b_tpc_xy[2]&&tgt.b_tpc_xy[3])
     {
       tgt.tpc_angle_x_s2_foc_23_24 = (tgt.tpc_x[3] - tgt.tpc_x[2])/dist_TPC23_TPC24*1000.;
       tgt.tpc_angle_y_s2_foc_23_24 = (tgt.tpc_y[3] - tgt.tpc_y[2])/dist_TPC23_TPC24*1000.;
       tgt.tpc_x_s2_foc_23_24 = -tgt.tpc_angle_x_s2_foc_23_24 * dist_TPC23_focS2/1000. + tgt.tpc_x[2]; //check
       tgt.tpc_y_s2_foc_23_24 = -tgt.tpc_angle_y_s2_foc_23_24 * dist_TPC23_focS2/1000. + tgt.tpc_y[2]; //check
       
       Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;
       tgt.tpc23_24_sc21_x = (tgt.tpc_angle_x_s2_foc_23_24/1000.*dist_SC21_focS2)+tgt.tpc_x_s2_foc_23_24;
       tgt.tpc23_24_sc21_y = (tgt.tpc_angle_y_s2_foc_23_24/1000.*dist_SC21_focS2)+tgt.tpc_y_s2_foc_23_24;
       Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;
       tgt.tpc23_24_sc22_x = (tgt.tpc_angle_x_s2_foc_23_24/1000.*dist_SC22_focS2)+tgt.tpc_x_s2_foc_23_24;
       tgt.tpc23_24_sc22_y = (tgt.tpc_angle_y_s2_foc_23_24/1000.*dist_SC22_focS2)+tgt.tpc_y_s2_foc_23_24;
       Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;   
       tgt.tpc23_24_s2target_x = (tgt.tpc_angle_x_s2_foc_23_24/1000.*dist_S2target_focS2)+tgt.tpc_x_s2_foc_23_24;
       tgt.tpc23_24_s2target_y = (tgt.tpc_angle_y_s2_foc_23_24/1000.*dist_S2target_focS2)+tgt.tpc_y_s2_foc_23_24;     
    
      if (bDrawHist)
  	{
  	  hTPC_X_S2_TPC_23_24->Fill(tgt.tpc_x_s2_foc_23_24);
  	  hTPC_Y_S2_TPC_23_24->Fill(tgt.tpc_y_s2_foc_23_24);
  	  hTPC_AX_S2_TPC_23_24->Fill(tgt.tpc_angle_x_s2_foc_23_24);
  	  hTPC_AY_S2_TPC_23_24->Fill(tgt.tpc_angle_y_s2_foc_23_24);
	  hTPC_X_AX_S2_TPC_23_24->Fill(tgt.tpc_x_s2_foc_23_24, tgt.tpc_angle_x_s2_foc_23_24);
	  hTPC_Y_AY_S2_TPC_23_24->Fill(tgt.tpc_y_s2_foc_23_24, tgt.tpc_angle_y_s2_foc_23_24);
	  hTPC_S2X_TPC23_24_time->Fill(tgt.tpc_x_s2_foc_23_24,  tgt.extraction_time_ms);
	  hTPC_S2A_TPC23_24_time->Fill(tgt.tpc_angle_x_s2_foc_23_24, tgt.extraction_time_ms);
	  hTPC23_24_SC21x->Fill(tgt.tpc23_24_sc21_x);
	  hTPC23_24_SC21y->Fill(tgt.tpc23_24_sc21_y);
	  hTPC23_24_SC22x->Fill(tgt.tpc23_24_sc22_x);
	  hTPC23_24_SC22y->Fill(tgt.tpc23_24_sc22_y);
	  hTPC23_24_S2target_x->Fill(tgt.tpc23_24_s2target_x);
	  hTPC23_24_S2target_y->Fill(tgt.tpc23_24_s2target_y);
	}
     }


  //=================================
  // Tracking with TPC 22 and TPC 24 
  //=================================
  
  if (tgt.b_tpc_xy[1]&&tgt.b_tpc_xy[3])
    {
      tgt.tpc_angle_x_s2_foc_22_24 = (tgt.tpc_x[3] - tgt.tpc_x[1])/dist_TPC22_TPC24*1000.;
      tgt.tpc_angle_y_s2_foc_22_24 = (tgt.tpc_y[3] - tgt.tpc_y[1])/dist_TPC22_TPC24*1000.;
      tgt.tpc_x_s2_foc_22_24 = -tgt.tpc_angle_x_s2_foc_22_24 * dist_TPC22_focS2/1000. + tgt.tpc_x[1]; //check
      tgt.tpc_y_s2_foc_22_24 = -tgt.tpc_angle_y_s2_foc_22_24 * dist_TPC22_focS2/1000. + tgt.tpc_y[1]; //check

      Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;   
      tgt.tpc22_24_sc21_x = (tgt.tpc_angle_x_s2_foc_22_24/1000.*dist_SC21_focS2)+tgt.tpc_x_s2_foc_22_24;
      tgt.tpc22_24_sc21_y = (tgt.tpc_angle_y_s2_foc_22_24/1000.*dist_SC21_focS2)+tgt.tpc_y_s2_foc_22_24;
      Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;   
      tgt.tpc22_24_sc22_x = (tgt.tpc_angle_x_s2_foc_22_24/1000.*dist_SC22_focS2)+tgt.tpc_x_s2_foc_22_24;
      tgt.tpc22_24_sc22_y = (tgt.tpc_angle_y_s2_foc_22_24/1000.*dist_SC22_focS2)+tgt.tpc_y_s2_foc_22_24;     
      Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;   
      tgt.tpc22_24_s2target_x = (tgt.tpc_angle_x_s2_foc_22_24/1000.*dist_S2target_focS2)+tgt.tpc_x_s2_foc_22_24;
      tgt.tpc22_24_s2target_y = (tgt.tpc_angle_y_s2_foc_22_24/1000.*dist_S2target_focS2)+tgt.tpc_y_s2_foc_22_24;     
    
      if (bDrawHist)
	{
	  hTPC_X_S2_TPC_22_24->Fill(tgt.tpc_x_s2_foc_22_24);
	  hTPC_Y_S2_TPC_22_24->Fill(tgt.tpc_y_s2_foc_22_24);
	  hTPC_AX_S2_TPC_22_24->Fill(tgt.tpc_angle_x_s2_foc_22_24);
	  hTPC_AY_S2_TPC_22_24->Fill(tgt.tpc_angle_y_s2_foc_22_24);
	  hTPC_X_AX_S2_TPC_22_24->Fill(tgt.tpc_x_s2_foc_22_24, tgt.tpc_angle_x_s2_foc_22_24);
	  hTPC_Y_AY_S2_TPC_22_24->Fill(tgt.tpc_y_s2_foc_22_24, tgt.tpc_angle_y_s2_foc_22_24);
	  hTPC_S2X_TPC22_24_time->Fill(tgt.tpc_x_s2_foc_22_24,  tgt.extraction_time_ms);
	  hTPC_S2A_TPC22_24_time->Fill(tgt.tpc_angle_x_s2_foc_22_24,  tgt.extraction_time_ms);
	  hTPC22_24_SC21x->Fill(tgt.tpc22_24_sc21_x);
	  hTPC22_24_SC21y->Fill(tgt.tpc22_24_sc21_y);
	  hTPC22_24_SC22x->Fill(tgt.tpc22_24_sc22_x);
	  hTPC22_24_SC22y->Fill(tgt.tpc22_24_sc22_y);
	  hTPC22_24_S2target_x->Fill(tgt.tpc22_24_s2target_x);
	  hTPC22_24_S2target_y->Fill(tgt.tpc22_24_s2target_y);	   
      	}
    }
   
  
  //=====================================================
  // Tracking with TPC 41 and TPC 42 (TPC 5 and 6) at S4  
  //=====================================================
  if (tgt.b_tpc_xy[4]&&tgt.b_tpc_xy[5])
    {
      
      tgt.tpc_angle_x_s4 = (tgt.tpc_x[5] - tgt.tpc_x[4])/dist_TPC41_TPC42*1000.;
      tgt.tpc_angle_y_s4 = (tgt.tpc_y[5] - tgt.tpc_y[4])/dist_TPC41_TPC42*1000.;
      tgt.tpc_x_s4 = tgt.tpc_angle_x_s4 * dist_TPC42_focS4/1000. + tgt.tpc_x[5];
      tgt.tpc_y_s4 = tgt.tpc_angle_y_s4 * dist_TPC42_focS4/1000. + tgt.tpc_y[5];      

       Float_t dist_SC41_focS4 = frs->dist_SC41 - frs->dist_focS4;
       tgt.tpc_sc41_x = (tgt.tpc_angle_x_s4/1000.*dist_SC41_focS4)+tgt.tpc_x_s4;
       tgt.tpc_sc41_y = (tgt.tpc_angle_y_s4/1000.*dist_SC41_focS4)+tgt.tpc_y_s4;
       Float_t dist_SC42_focS4 = frs->dist_SC42 - frs->dist_focS4;
       tgt.tpc_sc42_x = (tgt.tpc_angle_x_s4/1000.*dist_SC42_focS4)+tgt.tpc_x_s4;
       tgt.tpc_sc42_y = (tgt.tpc_angle_y_s4/1000.*dist_SC42_focS4)+tgt.tpc_y_s4;
       Float_t dist_SC43_focS4 = frs->dist_SC43 - frs->dist_focS4;
       tgt.tpc_sc43_x = (tgt.tpc_angle_x_s4/1000.*dist_SC43_focS4)+tgt.tpc_x_s4;
       tgt.tpc_sc43_y = (tgt.tpc_angle_y_s4/1000.*dist_SC43_focS4)+tgt.tpc_y_s4;
       Float_t dist_MUSIC41_focS4 = frs->dist_MUSIC41 - frs->dist_focS4;
       tgt.tpc_music41_x = (tgt.tpc_angle_x_s4/1000.*dist_MUSIC41_focS4)+tgt.tpc_x_s4;
       tgt.tpc_music41_y = (tgt.tpc_angle_y_s4/1000.*dist_MUSIC41_focS4)+tgt.tpc_y_s4;
       Float_t dist_MUSIC42_focS4 = frs->dist_MUSIC42 - frs->dist_focS4;
       tgt.tpc_music42_x = (tgt.tpc_angle_x_s4/1000.*dist_MUSIC42_focS4)+tgt.tpc_x_s4;
       tgt.tpc_music42_y = (tgt.tpc_angle_y_s4/1000.*dist_MUSIC42_focS4)+tgt.tpc_y_s4;
       Float_t dist_MUSIC43_focS4 = frs->dist_MUSIC43 - frs->dist_focS4;
       tgt.tpc_music43_x = (tgt.tpc_angle_x_s4/1000.*dist_MUSIC43_focS4)+tgt.tpc_x_s4;
       tgt.tpc_music43_y = (tgt.tpc_angle_y_s4/1000.*dist_MUSIC43_focS4)+tgt.tpc_y_s4;
       Float_t dist_S4target_focS4 = frs->dist_S4target - frs->dist_focS4;
       tgt.tpc_s4target_x = (tgt.tpc_angle_x_s4/1000.* dist_S4target_focS4)+tgt.tpc_x_s4;
       tgt.tpc_s4target_y = (tgt.tpc_angle_y_s4/1000.* dist_S4target_focS4)+tgt.tpc_y_s4;

      if (bDrawHist)
	{
	  hTPC_X_S4->Fill(tgt.tpc_x_s4);
	  hTPC_Y_S4->Fill(tgt.tpc_y_s4);
	  hTPC_AX_S4->Fill(tgt.tpc_angle_x_s4);
	  hTPC_AY_S4->Fill(tgt.tpc_angle_y_s4);
	  hTPC_XAX_S4->Fill(tgt.tpc_x_s4,tgt.tpc_angle_x_s4);
	  hTPC_YAY_S4->Fill(tgt.tpc_y_s4,tgt.tpc_angle_y_s4);
	  hTPC_S4X_time->Fill(tgt.tpc_x_s4, tgt.extraction_time_ms);
	  hTPC_S4A_time->Fill(tgt.tpc_angle_x_s4, tgt.extraction_time_ms);

	  hTPC_SC41x -> Fill(tgt.tpc_sc41_x);
	  hTPC_SC41y -> Fill(tgt.tpc_sc41_y);
	  hTPC_SC42x -> Fill(tgt.tpc_sc42_x);
	  hTPC_SC42y -> Fill(tgt.tpc_sc42_y);
	  hTPC_SC43x -> Fill(tgt.tpc_sc43_x);
	  hTPC_SC43y -> Fill(tgt.tpc_sc43_y);
	  hTPC_MUSIC41x -> Fill(tgt.tpc_music41_x);
	  hTPC_MUSIC41y -> Fill(tgt.tpc_music41_y);
	  hTPC_MUSIC42x -> Fill(tgt.tpc_music42_x);
	  hTPC_MUSIC42y -> Fill(tgt.tpc_music42_y);
	  hTPC_MUSIC43x -> Fill(tgt.tpc_music43_x);
	  hTPC_MUSIC43y -> Fill(tgt.tpc_music43_y);
	  hTPC_S4target_x -> Fill(tgt.tpc_s4target_x);
	  hTPC_S4target_y -> Fill(tgt.tpc_s4target_y);

	  hTPC_XS4_AXS2_TPC_21_22 -> Fill(tgt.tpc_x_s4, tgt.tpc_angle_x_s2_foc_21_22);
	  hTPC_YS4_AYS2_TPC_21_22 -> Fill(tgt.tpc_y_s4, tgt.tpc_angle_y_s2_foc_21_22);
	  hTPC_XS4_AXS2_TPC_23_24 -> Fill(tgt.tpc_x_s4, tgt.tpc_angle_x_s2_foc_23_24);
	  hTPC_YS4_AYS2_TPC_23_24 -> Fill(tgt.tpc_y_s4, tgt.tpc_angle_y_s2_foc_23_24);
	  hTPC_XS4_AXS2_TPC_22_24 -> Fill(tgt.tpc_x_s4, tgt.tpc_angle_x_s2_foc_22_24);
	  hTPC_YS4_AYS2_TPC_22_24 -> Fill(tgt.tpc_y_s4, tgt.tpc_angle_y_s2_foc_22_24);
	}
    }
}
//////////////////////////////////////////////////////////////////
///  ***********Si Analysis**************************** //////////


void TFRSCalibrProc::Process_SI_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt)
{

  // Si alpha
  tgt.si_e1 = (si->si_factor1*src.si_adc1)+si->si_offset1;
  tgt.si_e2 = (si->si_factor2*src.si_adc2)+si->si_offset2;
  tgt.si_e3 = (si->si_factor3*src.si_adc3)+si->si_offset3;
  tgt.si_e4 = (si->si_factor4*src.si_adc4)+si->si_offset4;
  tgt.si_e5 = (si->si_factor5*src.si_adc5)+si->si_offset5;

  // fill histogram for first si detector trigger ==3

  hsi_e1->Fill(tgt.si_e1);
  if(src.trigger==3)
    hsi_e1Trig->Fill(tgt.si_e1);

  // fill histogram for second si detector trigger ==4
  //if(src.trigger==3)
  hsi_e2->Fill(tgt.si_e2);
  if(src.trigger==4)
    hsi_e2Trig->Fill(tgt.si_e2);
  // fill histogram for first si detector trigger ==5
  //if(src.trigger==2)
  hsi_e3->Fill(tgt.si_e3);
  if(src.trigger==5)
    hsi_e3Trig->Fill(tgt.si_e3);
  // fill histogram for first si detector trigger ==6
  //if(src.trigger==2)
  hsi_e4->Fill(tgt.si_e4);
  if(src.trigger==6)
    hsi_e4Trig->Fill(tgt.si_e4);


  //========================
  //Active Stopper Analysis
  //========================
  /*
  tgt.dssd_xmaxindex=-10;
  tgt.dssd_xmaxenergy=1000;
  */
  
  //for(int i=0;i<16;i++){
  //tgt.dssd_e[15-i] = (si->dssd_factor[15-i]*(src.dssd_adc[i]+gRandom->Rndm()-0.5))+si->dssd_offset[15-i];	  	  }
  
  for(int i=0;i<16;i++){
   //tgt.dssd_e[i] = src.dssd_adc[i];
     tgt.dssd_e_det1[i] = (si->dssd_factor_det1[i]*src.dssd_adc_det1[i])+si->dssd_offset_det1[i];
     tgt.dssd_e_det2[i] = (si->dssd_factor_det2[i]*src.dssd_adc_det2[i])+si->dssd_offset_det2[i];
     tgt.dssd_e_det3[i] = (si->dssd_factor_det3[i]*src.dssd_adc_det3[i])+si->dssd_offset_det3[i];
     tgt.dssd_e_det4[i] = (si->dssd_factor_det4[i]*src.dssd_adc_det4[i])+si->dssd_offset_det4[i];
     tgt.dssd_e_det5[i] = (si->dssd_factor_det5[i]*src.dssd_adc_det5[i])+si->dssd_offset_det5[i];
     tgt.dssd_e_det6[i] = (si->dssd_factor_det6[i]*src.dssd_adc_det6[i])+si->dssd_offset_det6[i];
  }

  /*
  for (int i=0 ; i<16 ; i++)
      {
        if (tgt.dssd_xmaxenergy<tgt.dssd_e[i])
           {
	     tgt.dssd_xmaxenergy=tgt.dssd_e[i];
	     tgt.dssd_xmaxindex= i;
	   }
      }
  
	
  tgt.dssd_ymaxindex=-10;
  tgt.dssd_ymaxenergy=1000;
  */
  
  //for(int i=16;i<24;i++){
  //tgt.dssd_e[i+8] = (si->dssd_factor[i+8]*(src.dssd_adc[i]+gRandom->Rndm()-0.5))+si->dssd_offset[i+8];
  //}
	
  //for(int i=24;i<32;i++){
  //tgt.dssd_e[i-8] = (si->dssd_factor[i-8]*(src.dssd_adc[i]+gRandom->Rndm()-0.5))+si->dssd_offset[i-8];
  //}	
   

   for(int i=16;i<32;i++){
      // tgt.dssd_e[i] = src.dssd_adc[i];
     tgt.dssd_e_det1[i] = (si->dssd_factor_det1[i]*src.dssd_adc_det1[i])+si->dssd_offset_det1[i];
     tgt.dssd_e_det2[i] = (si->dssd_factor_det2[i]*src.dssd_adc_det2[i])+si->dssd_offset_det2[i];
     tgt.dssd_e_det3[i] = (si->dssd_factor_det3[i]*src.dssd_adc_det3[i])+si->dssd_offset_det3[i];
     tgt.dssd_e_det4[i] = (si->dssd_factor_det4[i]*src.dssd_adc_det4[i])+si->dssd_offset_det4[i];
     tgt.dssd_e_det5[i] = (si->dssd_factor_det5[i]*src.dssd_adc_det5[i])+si->dssd_offset_det5[i];
     tgt.dssd_e_det6[i] = (si->dssd_factor_det6[i]*src.dssd_adc_det6[i])+si->dssd_offset_det6[i];
   }

   /*
   for (int i=16 ; i<32 ; i++){
     if(tgt.dssd_ymaxenergy<tgt.dssd_e[i])
       {
	 tgt.dssd_ymaxenergy=tgt.dssd_e[i];
	 tgt.dssd_ymaxindex= i-16;
       }	
   }
   */	
	
  // filling histograms for different triggers, decay == 3, implantation ==1
   /*
	for(int i=0;i<32;i++){
	  if(src.trigger==1)hdssd_e[i]->Fill(tgt.dssd_e[i]);
	  if(src.trigger==2)hdssd_e_dec[i]->Fill(tgt.dssd_e[i]);
	}
	if(src.trigger==1){
	  hdssd_xmaxenergy->Fill(tgt.dssd_xmaxenergy);
	  hdssd_xmaxindex->Fill(tgt.dssd_xmaxindex);
	  hdssd_ymaxenergy->Fill(tgt.dssd_ymaxenergy);
	  hdssd_ymaxindex->Fill(tgt.dssd_ymaxindex);
	  hdssd_xymaxindex->Fill(tgt.dssd_xmaxindex,tgt.dssd_ymaxindex);
	}

	if(src.trigger==2){
	  hdssd_xmaxenergy_dec->Fill(tgt.dssd_xmaxenergy);
	  hdssd_xmaxindex_dec->Fill(tgt.dssd_xmaxindex);
	  hdssd_ymaxenergy_dec->Fill(tgt.dssd_ymaxenergy);
	  hdssd_ymaxindex_dec->Fill(tgt.dssd_ymaxindex);
	  hdssd_xymaxindex_dec->Fill(tgt.dssd_xmaxindex,tgt.dssd_ymaxindex);
	}
   */

   for(int i=0;i<32;i++){
     hdssd_e_det1[i]->Fill(tgt.dssd_e_det1[i]);
     hdssd_e_det2[i]->Fill(tgt.dssd_e_det2[i]);
     hdssd_e_det3[i]->Fill(tgt.dssd_e_det3[i]);
     hdssd_e_det4[i]->Fill(tgt.dssd_e_det4[i]);
     hdssd_e_det5[i]->Fill(tgt.dssd_e_det5[i]);
     hdssd_e_det6[i]->Fill(tgt.dssd_e_det6[i]);
   }

   /*
   hdssd_xmaxenergy->Fill(tgt.dssd_xmaxenergy);
   hdssd_xmaxindex->Fill(tgt.dssd_xmaxindex);
   hdssd_ymaxenergy->Fill(tgt.dssd_ymaxenergy);
   hdssd_ymaxindex->Fill(tgt.dssd_ymaxindex);
   hdssd_xymaxindex->Fill(tgt.dssd_xmaxindex,tgt.dssd_ymaxindex);
   */
}

//////////////////////////////////////////////////////////////////
///  ***********Channeltron Analysis********************//////////
void TFRSCalibrProc::Process_CT_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt)
{
  hct_all->Fill(src.ct_signal);

  hct_trigger_DU->Fill(src.ct_trigger_DU);
  hct_trigger_SY->Fill(src.ct_trigger_SY);

  if(src.ct_trigger_DU==kTRUE)
    hct_DU->Fill(src.ct_signal);

  if(src.ct_trigger_SY==kTRUE)
    hct_SY->Fill(src.ct_signal);
  
}

//////////////////////////////////////////////////////////////////
///  ***********Electron Current Analysis********************//////////
void TFRSCalibrProc::Process_ElCurrent_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt)
{
  helcurrent->Fill(src.ec_signal);
}


ClassImp(TFRSCalibrProc)
