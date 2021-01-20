#include "TFRSAnlProc.h"

#include "TH1.h"
#include "TH2.h"
#include "Go4ConditionsBase/TGo4WinCond.h"
#include "Go4ConditionsBase/TGo4PolyCond.h"
#include "Go4ConditionsBase/TGo4CondArray.h"

#include "TFRSAnlEvent.h"
#include "TFRSSortEvent.h"
#include "TFRSCalibrEvent.h"

#include "TFRSParameter.h"

#include <stdlib.h>

//#include "Go4Analysis/TGo4Analysis.h"


TFRSAnlProc::TFRSAnlProc() : TFRSBasicProc("FRSAnlProc")
{
  music = dynamic_cast<TMUSICParameter*>(GetParameter("MUSICPar"));
  sci   = dynamic_cast<TSCIParameter*>(GetParameter("SCIPar"));
  frs   = dynamic_cast<TFRSParameter*>(GetParameter("FRSPar"));
  id    = dynamic_cast<TIDParameter*>(GetParameter("IDPar"));
  mrtof = dynamic_cast<TMRTOFMSParameter*>(GetParameter("MRTOFMSPar"));
}

TFRSAnlProc::TFRSAnlProc(const char* name): TFRSBasicProc(name)
{

  music = dynamic_cast<TMUSICParameter*> (GetParameter("MUSICPar"));
  sci   = dynamic_cast<TSCIParameter*>(GetParameter("SCIPar"));
  frs   = dynamic_cast<TFRSParameter*>(GetParameter("FRSPar"));
  id    = dynamic_cast<TIDParameter*>(GetParameter("IDPar"));
  mrtof = dynamic_cast<TMRTOFMSParameter*>(GetParameter("MRTOFMSPar"));

  bDrawHist=kTRUE;
  Create_SCI_Hist();
  Create_MUSIC_Hist();
  Create_ID_Hist();
  Create_Gated_Hist();
  Create_MultiHitTDC_Hist();
  Create_MRTOF_Hist();

  TGo4CondArray* conarr = MakeCondArray(0, "Integral", 5);
  if (ObjWasCreated())
    {
      ((*conarr)[0])->SetValues(0,10);
      ((*conarr)[1])->SetValues(20,30);
      ((*conarr)[2])->SetValues(40,50);
      ((*conarr)[3])->SetValues(60,70);
      ((*conarr)[4])->SetValues(80,90);
    }

}

TFRSAnlProc::~TFRSAnlProc()
{ }


Float_t TFRSAnlProc::rand3(){ //by using TRandom3 , which uses Mersenne Twister Method.
  return random3.Uniform(-0.5,0.5);
}


//void TFRSAnlProc::FRSEventAnalysis(TFRSAnlEvent* poutevt)
Bool_t TFRSAnlProc::BuildEvent(TGo4EventElement* output)
{

  TFRSAnlEvent* poutevt = dynamic_cast<TFRSAnlEvent*>(output);
  if(poutevt==nullptr)
    return kFALSE;

  poutevt->SetValid(kTRUE);  // events always accepted

  bDrawHist=kTRUE;

  TFRSSortEvent *srt = dynamic_cast<TFRSSortEvent*> (GetInputEvent("Calibr"));
  TFRSCalibrEvent *clb = dynamic_cast<TFRSCalibrEvent*> (GetInputEvent());

  if ((srt==nullptr) || (clb==nullptr))
    return kFALSE;

  if(srt->EventFlag != clb->EventFlag)
    std::cout<<"E> AnlProc BuildEvent : EventFlag miss matched between Sort and Calib ! "<<srt->EventFlag <<" != "<< clb->EventFlag <<"\n";

  poutevt->EventFlag = srt->EventFlag;
  Process_MUSIC_Analysis(*srt, *clb, *poutevt);
  Process_SCI_Analysis(*srt, *clb, *poutevt);
  Process_MultiHitTDC_Analysis(*srt, *clb, *poutevt);
  Process_ID_Analysis(*srt, *clb, *poutevt);
  Process_ID_MultiHitTDC_Analysis(*srt, *clb, *poutevt);
  Process_MRTOF_Analysis(*srt, *clb, *poutevt);
  Process_Gated_Analysis(*srt, *clb, *poutevt);
  return kTRUE;
}

void TFRSAnlProc::Create_MRTOF_Hist()
{

  h_MRtof_Start = MakeH1F("MRTOF/Time","mrtof_start",1000,0,50,"microsec",2,6);
  h_MRtof_StopDelay = MakeH1F("MRTOF/Time","mrtof_stopDelay",1000,0,50,"microsec",2,6);
  h_MRtof_Stop = MakeH1F("MRTOF/Time","mrtof_stop",1000,0,50,"microsec",2,6);
  h_MRtof_tof = MakeH1F("MRTOF/Time","mrtof_tof",200000,0,200,"microsec",2,6);
  h_MRtof_status = MakeH1F("MRTOF/Time","mrtof_TimeStatus",10,0,10,"",2,6);

}

void TFRSAnlProc::Create_MUSIC_Hist()
{
  // All of these music histograms (range, xtitle) will be reset via setup.C + TFRSAnalysis.cxx
  // because we need to change xmax according to setup parameters (TUM=4096, Travel=larger number depending on resolution)

   char name[80], xtitle[80];
   for(int i=0;i<8;i++)
     {
       sprintf(name,"MUSIC1_E(%d)",i);
       sprintf(xtitle,"dE MUSIC1(%d)",i);
       hMUSIC1_E[i] = MakeH1I("MUSIC/MUSIC(1)/E",name,4096,0,4096,xtitle,2,6);

       sprintf(name,"MUSIC2_E(%d)",i);
       sprintf(xtitle,"dE MUSIC2(%d)",i);
       hMUSIC2_E[i] = MakeH1I("MUSIC/MUSIC(2)/E",name,4096,0,4096,xtitle,2,6);//travel music, adcmax depends on mdpp resolution parameters

       sprintf(name,"MUSIC3_E(%d)",i);
       sprintf(xtitle,"dE MUSIC3(%d)",i);
       hMUSIC3_E[i] = MakeH1I("MUSIC/MUSIC(3)/E",name,4096,0,4096,xtitle,2,6);

       sprintf(name,"MUSIC1_T(%d)",i);
       sprintf(xtitle,"dT MUSIC1(%d) ",i);
       hMUSIC1_T[i] = MakeH1I("MUSIC/MUSIC(1)/T",name,4096,0, 4096,xtitle,2,6);

       sprintf(name,"MUSIC2_T(%d)",i);
       sprintf(xtitle,"dT MUSIC2(%d) ",i);
       hMUSIC2_T[i] = MakeH1I("MUSIC/MUSIC(2)/T",name,4096,0, 4096-10, xtitle,2,6); //travel music, tdcmax = 0x10000

       sprintf(name,"MUSIC3_T(%d)",i);
       sprintf(xtitle,"dT MUSIC3(%d) ",i);
       hMUSIC3_T[i] = MakeH1I("MUSIC/MUSIC(3)/T",name,4096,0, 4096-10, xtitle,2,6);

       // basic cut conditions
       sprintf(name,"cMusic1_E(%d)",i);
       cMusic1_E[i] = MakeWindowCond("MUSIC/MUSIC(1)/E",name, 10, 4096-10, hMUSIC1_E[i]->GetName());

       sprintf(name,"cMusic1_T(%d)",i);
       cMusic1_T[i] = MakeWindowCond("MUSIC/MUSIC(1)/T",name, 10, 4096-10, hMUSIC1_T[i]->GetName());

       sprintf(name,"cMusic2_E(%d)",i);
       cMusic2_E[i] = MakeWindowCond("MUSIC/MUSIC(2)/E",name, 10, 4096-10, hMUSIC2_E[i]->GetName());

       sprintf(name,"cMusic2_T(%d)",i);
       cMusic2_T[i] = MakeWindowCond("MUSIC/MUSIC(2)/T",name, 10, 4096-10, hMUSIC2_T[i]->GetName());

       sprintf(name,"cMusic3_E(%d)",i);
       cMusic3_E[i] = MakeWindowCond("MUSIC/MUSIC(3)/E",name, 10, 4096-10, hMUSIC3_E[i]->GetName());

       sprintf(name,"cMusic3_T(%d)",i);
       cMusic3_T[i] = MakeWindowCond("MUSIC/MUSIC(3)/T",name, 10,4096-10, hMUSIC3_T[i]->GetName());
   }

   hMUSIC1_dE = MakeH1I("MUSIC/MUSIC(1)/E","MUSIC1_dE",4096,0.0,4096,"Average dE MUSIC41 (root)",2,6);
   hMUSIC2_dE = MakeH1I("MUSIC/MUSIC(2)/E","MUSIC2_dE",4096,0.0,4096,"Average dE MUSIC42 (root)",2,6);
   hMUSIC3_dE = MakeH1I("MUSIC/MUSIC(3)/E","MUSIC3_dE",4096,0.0,4096,"Average dE MUSIC43 (root)",2,6);
   hMUSIC_dE1dE2 = MakeH2I("MUSIC/Correlation","dE1_dE2",1024,0,4096,1024,0,4096,"dE MUSIC41","dE MUSIC42",2);
   hMUSIC_dE1dE3 = MakeH2I("MUSIC/Correlation","dE1_dE3",1024,0,4096,1024,0,4096,"dE MUSIC41","dE MUSIC43",2);
   hMUSIC_dE2dE3 = MakeH2I("MUSIC/Correlation","dE2_dE3",1024,0,4096,1024,0,4096,"dE MUSIC42","dE MUSIC43",2);
   hMUSIC1_dE_x = MakeH2I("MUSIC/MUSIC(1)/E","MUSIC1_dE_x",100,-100,100,200,0,4096,"Average x position in MUSIC41","dE MUSIC41 [channels]",2);
   hMUSIC2_dE_x = MakeH2I("MUSIC/MUSIC(2)/E","MUSIC2_dE_x",100,-100,100,200,0,4096,"Average x position in MUSIC42","dE MUSIC42 [channels]",2);
   hMUSIC3_dE_x = MakeH2I("MUSIC/MUSIC(3)/E","MUSIC3_dE_x",100,-100,100,200,0,4096,"Average x position in MUSIC43","dE MUSIC43 [channels]",2);
   hMUSIC1_dECOR   = MakeH1I("MUSIC/MUSIC(1)/E","MUSIC1_dECOR",4096,0,4096,"dE MUSIC41 corrected for position (ch)",2,6);
   hMUSIC2_dECOR   = MakeH1I("MUSIC/MUSIC(2)/E","MUSIC2_dECOR",4096,0,4096,"dE MUSIC42 corrected for position (ch)",2,6);
   hMUSIC3_dECOR   = MakeH1I("MUSIC/MUSIC(3)/E","MUSIC3_dECOR",4096,0,4096,"dE MUSIC43 corrected for position (ch)",2,6);
   hMUSIC1_dECOR_x = MakeH2I("MUSIC/MUSIC(1)/E","MUSIC1_dECOR_x",100,-100,+100,200,0,4096,"Average x position in MUSIC41", "dE MUSIC41 corrected for position  (ch)", 2);
   hMUSIC2_dECOR_x = MakeH2I("MUSIC/MUSIC(2)/E","MUSIC2_dECOR_x",100,-100,+100,200,0,4096,"Average x position in MUSIC42", "dE MUSIC42 corrected for position  (ch)", 2);
   hMUSIC3_dECOR_x = MakeH2I("MUSIC/MUSIC(3)/E","MUSIC3_dECOR_x",100,-100,+100,200,0,4096,"Average x position in MUSIC43", "dE MUSIC43 corrected for position  (ch)", 2);

   // for(int i=0;i<8;i++){
   //    for(int k=0;k<5;++k){
   // 	        sprintf(name,"MUSIC3_E%d_gate%d",i,k);
   // 		//   hMUSIC3_E_s4gate_Z_AoQ[i][k] = MakeH1I(Form("S4gate/gate_%d/MUSIC3",i),name,4096,0,4096,"dE [channel]",2,6);
   //    }
   // }

}


void TFRSAnlProc::Create_MultiHitTDC_Hist()
{
  char fname[50], name[50], title[60];//, title2[60];

  // ---------- For SCI_X from TL-TR ------------ //
  hMultiHitTDC_21l_21r       = MakeH1I("MultiHitTDC/SCIX/SC21","Sc21L_Sc21R_MHTDC",     800,-20,20,"T(21L) - T(21R) [ns]",2,3);
  hMultiHitTDC_21l_21r_TPCX  = MakeH2I("MultiHitTDC/SCIX/SC21","Sc21L_Sc21R_MHTDC_TPCX", 800,-20,20, 200,-100,100,"T(21L) - T(21R) [ns]","X deduced from TPC [mm]",1);
  hMultiHitTDC_SC21X         = MakeH1I("MultiHitTDC/SCIX/SC21","Sc21X_MHTDC",           200,-100,100,"SC21X from SC21 time diff (L-R) [mm]",2,3);
  hMultiHitTDC_SC21X_TPCX    = MakeH2I("MultiHitTDC/SCIX/SC21","Sc21X_MHTDC_TPCX",       200,-100,100,200,-100,100,"SC21X from SC21 time diff (L-R) [mm]","X deduced from TPC [mm]",1);

  hMultiHitTDC_41l_41r       = MakeH1I("MultiHitTDC/SCIX/SC41","Sc41L_Sc41R_MHTDC",     800,-20,20,"T(41L) - T(41R) [ns]",2,3);
  hMultiHitTDC_41l_41r_TPCX  = MakeH2I("MultiHitTDC/SCIX/SC41","Sc41L_Sc41R_MHTDC_TPCX", 800,-20,20, 200,-100,100,"T(41L) - T(41R) [ns]","X deduced from TPC [mm]",1);
  hMultiHitTDC_SC41X         = MakeH1I("MultiHitTDC/SCIX/SC41","Sc41X_MHTDC",           200,-100,100,"SC41X from SC41 time diff (L-R) [mm]",2,3);
  hMultiHitTDC_SC41X_TPCX    = MakeH2I("MultiHitTDC/SCIX/SC41","Sc41X_MHTDC_TPCX",       200,-100,100,200,-100,100,"SC41X from SC41 time diff (L-R) [mm]","X deduced from TPC [mm]",1);

  hMultiHitTDC_42l_42r       = MakeH1I("MultiHitTDC/SCIX/SC42","Sc42L_Sc42R_MHTDC",     800,-20,20,"T(42L) - T(42R) [ns]",2,3);
  hMultiHitTDC_42l_42r_TPCX  = MakeH2I("MultiHitTDC/SCIX/SC42","Sc42L_Sc42R_MHTDC_TPCX", 800,-20,20, 200,-100,100,"T(42L) - T(42R) [ns]","X deduced from TPC [mm]",1);
  hMultiHitTDC_SC42X         = MakeH1I("MultiHitTDC/SCIX/SC42","Sc42X_MHTDC",           200,-100,100,"SC42X from SC42 time diff (L-R) [mm]",2,3);
  hMultiHitTDC_SC42X_TPCX    = MakeH2I("MultiHitTDC/SCIX/SC42","Sc42X_MHTDC_TPCX",       200,-100,100,200,-100,100,"SC42X from SC42 time diff (L-R) [mm]","X deduced from TPC [mm]",1);

  hMultiHitTDC_43l_43r       = MakeH1I("MultiHitTDC/SCIX/SC43","Sc43L_Sc43R_MHTDC",     800,-20,20,"T(43L) - T(43R) [ns]",2,3);
  hMultiHitTDC_43l_43r_TPCX  = MakeH2I("MultiHitTDC/SCIX/SC43","Sc43L_Sc43R_MHTDC_TPCX", 800,-20,20, 200,-100,100,"T(43L) - T(43R) [ns]","X deduced from TPC [mm]",1);
  hMultiHitTDC_SC43X         = MakeH1I("MultiHitTDC/SCIX/SC43","Sc43X_MHTDC",           200,-100,100,"SC43X from SC43 time diff (L-R) [mm]",2,3);
  hMultiHitTDC_SC43X_TPCX    = MakeH2I("MultiHitTDC/SCIX/SC43","Sc43X_MHTDC_TPCX",       200,-100,100,200,-100,100,"SC43X from SC43 time diff (L-R) [mm]","X deduced from TPC [mm]",1);

  hMultiHitTDC_31l_31r       = MakeH1I("MultiHitTDC/SCIX/SC31","Sc31L_Sc31R_MHTDC",     800,-20,20,"T(31L) - T(31R) [ns]",2,3);
  hMultiHitTDC_31l_31r_TPCX  = MakeH2I("MultiHitTDC/SCIX/SC31","Sc31L_Sc31R_MHTDC_TPCX", 800,-20,20, 200,-100,100,"T(31L) - T(31R) [ns]","X deduced from TPC [mm]",1);
  hMultiHitTDC_SC31X         = MakeH1I("MultiHitTDC/SCIX/SC31","Sc31X_MHTDC",           200,-100,100,"SC31X from SC31 time diff (L-R) [mm]",2,3);
  hMultiHitTDC_SC31X_TPCX    = MakeH2I("MultiHitTDC/SCIX/SC31","Sc31X_MHTDC_TPCX",       200,-100,100,200,-100,100,"SC31X from SC31 time diff (L-R) [mm]","X deduced from TPC [mm]",1);

  hMultiHitTDC_81l_81r       = MakeH1I("MultiHitTDC/SCIX/SC81","Sc81L_Sc81R_MHTDC",     800,-20,20,"T(81L) - T(81R) [ns]",2,3);
  hMultiHitTDC_SC81X         = MakeH1I("MultiHitTDC/SCIX/SC81","Sc81X_MHTDC",           200,-100,100,"SC81X from SC81 time diff (L-R) [mm]",2,3);
  // TPC does not exist in S8


  //---------- for TOF and Beta ----------//
  hMultiHitTDC_TOF_41_21  = MakeH1I("MultiHitTDC/TOF", "TOF_SC41_SC21",4000,100,200,"T(41) - T(21) [ns]",2,3);
  hMultiHitTDC_BETA_41_21 = MakeH1I("MultiHitTDC/TOF", "BETA_SC41_SC21",4000,0.5,0.9,"Beta (SC21-SC41)",2,3);
  hMultiHitTDC_TOF_42_21  = MakeH1I("MultiHitTDC/TOF", "TOF_SC42_SC21",4000,100,200,"T(42) - T(21) [ns]",2,3);
  hMultiHitTDC_BETA_42_21 = MakeH1I("MultiHitTDC/TOF", "BETA_SC42_SC21",4000,0.5,0.9,"Beta (SC21-SC42)",2,3);
  hMultiHitTDC_TOF_43_21  = MakeH1I("MultiHitTDC/TOF", "TOF_SC43_SC21",4000,100,200,"T(43) - T(21) [ns]",2,3);
  hMultiHitTDC_BETA_43_21 = MakeH1I("MultiHitTDC/TOF", "BETA_SC43_SC21",4000,0.5,0.9,"Beta (SC21-SC43)",2,3);
  hMultiHitTDC_TOF_31_21  = MakeH1I("MultiHitTDC/TOF", "TOF_SC31_SC21",4000,50,100,"T(31) - T(21) [ns]",2,3);
  hMultiHitTDC_BETA_31_21 = MakeH1I("MultiHitTDC/TOF", "BETA_SC31_SC21",4000,0.5,0.9,"Beta (SC21-SC31)",2,3);
  hMultiHitTDC_TOF_81_21  = MakeH1I("MultiHitTDC/TOF", "TOF_SC81_SC21",4000,100,400,"T(81) - T(21) [ns]",2,3);
  hMultiHitTDC_BETA_81_21 = MakeH1I("MultiHitTDC/TOF", "BETA_SC81_SC21",4000,0.5,0.9,"Beta (SC21-SC81)",2,3);

  float dummy1=0.0; float dummy2=1.0; // should be set via setup.C => TFRSAnalysis.cxx
  hID_MHTDCS2S8_DELTA =  MakeH1I("MultiHitTDC/ID_S2S8","delta_S2-S8",1000,-0.015,0.015,"delta S2-S8",2,3);
  hID_MHTDCS2S8_BETA  =  MakeH1I("MultiHitTDC/ID_S2S8","beta_S2-S8",1000,0.65,0.85,"beta S2-S8",2,3);
  hID_MHTDCS2S8_AOQ   =  MakeH1I("MultiHitTDC/ID_S2S8","AoQ_S2-S8",1000,dummy1,dummy2,"AoQ S2-S8",2,3);
  hID_MHTDCS2S8_DELTA_BETA = MakeH2I("MultiHitTDC/ID_S2S8","delta_vs_beta_S2-S8",600,-0.015,0.015,600,0.74,0.78,"delta S2-S8","beta S2-S8",1);
  hID_MHTDCS2S8_AOQ_BETA   = MakeH2I("MultiHitTDC/ID_S2S8","aoq_vs_beta_S2-S8",600,dummy1,dummy2,600,0.74,0.78,"aoq S2-S8","beta S2-S8",1);
  hID_MHTDCS2S8_dES2TPC        = MakeH1I("MultiHitTDC/ID_S2S8","dE(s2tpc)",1000,0,1000,"dE(s2tpc)",2,3);
  hID_MHTDCS2S8_dES2TPC_BETA   = MakeH2I("MultiHitTDC/ID_S2S8","dE(s2tpc)_vs_beta(S2-S8)",400,0.65,0.85,500,0,3000,"beta S2-S8","dE(s2tpc)",1);
  hID_MHTDCS2S8_dES2TPC_AOQ    = MakeH2I("MultiHitTDC/ID_S2S8","dE(s2tpc)_vs_aoq(S2-S8)",400,dummy1,dummy2,500,0,3000,"AoQ S2-S8","dE(s2tpc)",1);
  hID_MHTDCS2S8_ZS2TPC         = MakeH1I("MultiHitTDC/ID_S2S8","Z(s2tpc)",400,dummy1,dummy2,"Z(s2tpc)",2,3);
  hID_MHTDCS2S8_ZS2TPC_AOQ    = MakeH2I("MultiHitTDC/ID_S2S8","Z(s2tpc)_vs_aoq(S2-S8)",400,dummy1,dummy2,400,dummy1,dummy2,"AoQ S2-S8","Z(s2tpc)",1);
  hID_MHTDCS2S8_dESC81_BETA   = MakeH2I("MultiHitTDC/ID_S2S8","dE(sc81)_vs_beta(S2-S8)",400,0.65,0.85,500,0,3000,"beta S2-S8","dE(sc81)",1);
  hID_MHTDCS2S8_dESC81_AOQ    = MakeH2I("MultiHitTDC/ID_S2S8","dE(sc81)_vs_aoq(S2-S8)",400,dummy1,dummy2,500,0,3000,"AoQ S2-S8","dE(sc81)",1);
  hID_MHTDCS2S8_ZSC81         = MakeH1I("MultiHitTDC/ID_S2S8","Z(sc81)",1000,dummy1,dummy2,"Z(sc81)",2,3);
  hID_MHTDCS2S8_ZSC81_AOQ    = MakeH2I("MultiHitTDC/ID_S2S8","Z(sc81)_vs_aoq(S2-S8)",400,dummy1,dummy2,400,dummy1,dummy2,"AoQ S2-S8","Z(sc81)",1);

  hID_MHTDCS2S4_DELTA =  MakeH1I("MultiHitTDC/ID_S2S4","delta_S2-S4",1000,-0.015,0.015,"delta S2-S4",2,3);
  hID_MHTDCS2S4_BETA  =  MakeH1I("MultiHitTDC/ID_S2S4","beta_S2-S4",1000,0.65,0.85,"beta S2-S4",2,3);
  hID_MHTDCS2S4_AOQ   =  MakeH1I("MultiHitTDC/ID_S2S4","AoQ_S2-S4",1000,dummy1,dummy2,"AoQ S2-S4",2,3);
  hID_MHTDCS2S4_DELTA_BETA = MakeH2I("MultiHitTDC/ID_S2S4","delta_vs_beta_S2-S4",600,-0.015,0.015,600,0.74,0.78,"delta S2-S4","beta S2-S4",1);
  hID_MHTDCS2S4_AOQ_BETA   = MakeH2I("MultiHitTDC/ID_S2S4","aoq_vs_beta_S2-S4",600,dummy1,dummy2,600,0.74,0.78,"aoq S2-S4","beta S2-S4",1);
  hID_MHTDCS2S4_dE41_BETA   = MakeH2I("MultiHitTDC/ID_S2S4","dE(music41)_vs_beta(S2-S4)",400,0.65,0.85,500,0,3000,"beta S2-S4","dE(music41)",1);
  hID_MHTDCS2S4_dE41_AOQ    = MakeH2I("MultiHitTDC/ID_S2S4","dE(music41)_vs_aoq(S2-S4)",400,dummy1,dummy2,500,0,3000,"AoQ S2-S4","dE(music41)",1);
  hID_MHTDCS2S4_Z41         = MakeH1I("MultiHitTDC/ID_S2S4","Z(music41)",400,dummy1,dummy2,"Z(music41)",2,3);
  hID_MHTDCS2S4_Z41_AOQ     = MakeH2I("MultiHitTDC/ID_S2S4","Z(music41)_vs_aoq(S2-S4)",400,dummy1,dummy2,400,dummy1,dummy2,"AoQ S2-S4","Z(music41)",1);
  hID_MHTDCS2S4_dE42_BETA   = MakeH2I("MultiHitTDC/ID_S2S4","dE(music42)_vs_beta(S2-S4)",400,0.65,0.85,500,0,3000,"beta S2-S4","dE(music42)",1);
  hID_MHTDCS2S4_dE42_AOQ    = MakeH2I("MultiHitTDC/ID_S2S4","dE(music42)_vs_aoq(S2-S4)",400,dummy1,dummy2,500,0,3000,"AoQ S2-S4","dE(music42)",1);
  hID_MHTDCS2S4_Z42         = MakeH1I("MultiHitTDC/ID_S2S4","Z(music42)",400,dummy1,dummy2,"Z(music42)",2,3);
  hID_MHTDCS2S4_Z42_AOQ     = MakeH2I("MultiHitTDC/ID_S2S4","Z(music42)_vs_aoq(S2-S4)",400,dummy1,dummy2,400,dummy1,dummy2,"AoQ S2-S4","Z(music42)",1);
}


void TFRSAnlProc::Create_SCI_Hist()
{
  char fname[50], name[50], title[60], title2[60];

  const char *count_title1[12]={"(0:1)", "(1:1)", "(2:1)",
				"(2:2)", "(3:1)", "(4:1)",
				"(4:2)", "(4:3)", "(6:1)",
				"(6:2)", "(8:1)"};
  const char *fext1[12]={"0", "1", "2", "2", "3", "4", "4", "4", "6", "6", "8", "8"};
  const char *fext2[12]={"01", "11", "21", "22","31", "41",
			 "42", "43", "61",
			 "62", "81", "82"};

  for (int cnt = 0; cnt<7; cnt++) //changed from 3 to 6 04.07.2018
    {
      int index = 0;
      switch(cnt)
	{
        case 0: index = 2; break;
        case 1: index = 4; break; //modified from 3 to 4 // 2019Nov18 YT
        case 2: index = 5; break;
      	case 3: index = 6; break;
       	case 4: index = 7; break;
       	case 5: index = 10; break;
	case 6: index = 3; break; // SC22 added 2020/feb/20
	}
      sprintf(fname,"SCI/SCI%s/SCI%s",fext1[index],fext2[index]);
      sprintf(name, "SCI%s_L", count_title1[index]);
      sprintf(title, "Sc%s L dE [ch]", count_title1[index]);
      hSCI_L[index] = MakeH1I(fname,name,4096,0,4096,title,2,3);

      sprintf(name, "SCI%s_R", count_title1[index]);
      sprintf(title, "Sc%s R dE [ch]", count_title1[index]);
      hSCI_R[index] = MakeH1I(fname,name,4096,0,4096,title,2,3);

      sprintf(name, "SCI%s_E", count_title1[index]);
      sprintf(title, "Sc%s Energy [ch]", count_title1[index]);
      hSCI_E[index] = MakeH1I(fname,name,4096,0,4096,title,2,3);

      sprintf(name, "SCI%s_Tx", count_title1[index]);
      sprintf(title, "Sc%s t_lr [ch] TAC", count_title1[index]);
      hSCI_Tx[index] = MakeH1I(fname,name,4096,0,4096,title,2,3);

      sprintf(name, "SCI%s_Tx_XfromTPC", count_title1[index]);
      sprintf(title, "Sc%s t_lr [ch] TAC", count_title1[index]);
      sprintf(title2, "X from TPC [mm]");
      hSCI_Tx_XTPC[index] = MakeH2I(fname,name,1024,0,4096,240,-120,120,title,title2,2);

      sprintf(name, "SCI%s_X", count_title1[index]);
      sprintf(title, "Sc%s x-pos [mm]", count_title1[index]);
      hSCI_X[index] = MakeH1I(fname,name,240,-120,120,title,2,3);

      sprintf(name, "SCI%s_X_XfromTPC", count_title1[index]);
      sprintf(title, "Sc%s x-pos [mm]", count_title1[index]);
      sprintf(title2, "X from TPC [mm]");
      hSCI_X_XTPC[index] = MakeH2I(fname,name,240,-120,120,240,-120,120,title,title2,2);

      sprintf(name, "cSCI%s_L", count_title1[index]);
      cSCI_L[index] = MakeWindowCond(fname,name, 10, 4000, hSCI_L[index]->GetName());

      sprintf(name, "cSCI%s_R", count_title1[index]);
      cSCI_R[index] = MakeWindowCond(fname,name, 10, 4000, hSCI_R[index]->GetName());

      sprintf(name, "cSCI%s_E", count_title1[index]);
      cSCI_E[index] = MakeWindowCond(fname,name, 10, 4000, hSCI_E[index]->GetName());

      sprintf(name, "cSCI%s_Tx", count_title1[index]);
      cSCI_Tx[index] = MakeWindowCond(fname,name,200,4000, hSCI_Tx[index]->GetName());

      sprintf(name, "cSCI%s_X", count_title1[index]);
      cSCI_X[index] = MakeWindowCond(fname,name,-100,100, hSCI_X[index]->GetName());

    }


  // ToF SC21-SC41
  sprintf(fname,"SCI/TOF/TOF(%d)",2);
  sprintf(name,"SCI_21_41_TofLL");
  hSCI_TofLL2 = MakeH1I(fname,name,2000,0,100000,"TAC SC41L-SC21L [ps]",2,3);

  sprintf(name,"SCI_21_41_TofRR");
  hSCI_TofRR2 = MakeH1I(fname,name,2000,0,100000,"TAC SC41R-SC21R [ps]",2,3);

  sprintf(name,"SCI_21_41_Tof2");
  hSCI_Tof2 = MakeH1I(fname,name,2000,0,100000,"TAC SC41-SC21 [ps] (pos.corr.)",2,3);

  sprintf(name,"SCI_21_41_Tof2calib");
  hSCI_Tof2calib = MakeH1I(fname,name,100000,0,1500000,"TOF SC41-SC21 [ps]",2,3);

  sprintf(name, "cSCI%d_TofLL", 2);
  cSCI_TofLL2 = MakeWindowCond(fname,name, 2500, 100000, hSCI_TofLL2->GetName());

  sprintf(name, "cSCI%d_TofRR", 2);
  cSCI_TofRR2 = MakeWindowCond(fname,name, 2500, 100000, hSCI_TofRR2->GetName());

  // ToF SC21-SC42 changed on 03.07.2018 SB
  sprintf(fname,"SCI/TOF/TOF(%d)",3);
  sprintf(name,"SCI_21_42_TofLL");
  hSCI_TofLL3 = MakeH1I(fname,name,2000,0,100000,"TAC SC42L-SC21L [ps]",2,3);

  sprintf(name,"SCI_21_42_TofRR");
  hSCI_TofRR3 = MakeH1I(fname,name,2000,0,100000,"TAC SC42R-SC21R [ps]",2,3);

  sprintf(name,"SCI_21_42_Tof3");
  hSCI_Tof3 = MakeH1I(fname,name,2000,0,100000,"TAC SC42-SC21 [ps] (pos.corr.)",2,3);

  sprintf(name,"SCI_21_42_Tof3calib");
  hSCI_Tof3calib = MakeH1I(fname,name,100000,0,180000,"TOF SC42-SC21 [ps]",2,3);

  sprintf(name, "cSCI%d_TofLL", 3);
  cSCI_TofLL3 = MakeWindowCond(fname,name, 2500, 100000, hSCI_TofLL3->GetName());

  sprintf(name, "cSCI%d_TofRR", 3);
  cSCI_TofRR3 = MakeWindowCond(fname,name, 2500, 100000, hSCI_TofRR3->GetName());


  // ToF SC21-SC81 changed on 03.07.2018 SB
  sprintf(fname,"SCI/TOF/TOF(%d)",4);
  sprintf(name,"SCI_21_81_TofLL");
  hSCI_TofLL4 = MakeH1I(fname,name,2000,0,100000,"TAC SC81L-SC21L [ps]",2,3);

  sprintf(name,"SCI_21_81_TofRR");
  hSCI_TofRR4 = MakeH1I(fname,name,2000,0,100000,"TAC SC81R-SC21R [ps]",2,3);

  sprintf(name,"SCI_21_81_Tof4");
  hSCI_Tof4 = MakeH1I(fname,name,2000,0,100000,"TAC SC81-SC21 [ps] (pos.corr.)",2,3);

  sprintf(name,"SCI_21_81_Tof4calib");
  hSCI_Tof4calib = MakeH1I(fname,name,250000,0,400000,"TOF SC81-SC21 [ps]",2,3);

  sprintf(name, "cSCI%d_TofLL", 4);
  cSCI_TofLL4 = MakeWindowCond(fname,name, 2500, 80000, hSCI_TofLL4->GetName());

  sprintf(name, "cSCI%d_TofRR", 4);
  cSCI_TofRR4 = MakeWindowCond(fname,name, 2500, 80000, hSCI_TofRR4->GetName());

  // ToF SC22-SC41 
  sprintf(fname,"SCI/TOF/TOF(%d)",5);
  sprintf(name,"SCI_22_41_TofLL");
  hSCI_TofLL5 = MakeH1I(fname,name,2000,0,100000,"TAC SC41L-SC22L [ps]",2,3);

  sprintf(name,"SCI_22_41_TofRR");
  hSCI_TofRR5 = MakeH1I(fname,name,2000,0,100000,"TAC SC41R-SC22R [ps]",2,3);

  sprintf(name,"SCI_22_41_Tof5");
  hSCI_Tof5 = MakeH1I(fname,name,2000,0,100000,"TAC SC41-SC22 [ps] (pos.corr.)",2,3);

  sprintf(name,"SCI_22_41_Tof5calib");
  hSCI_Tof5calib = MakeH1I(fname,name,250000,0,400000,"TOF SC41-SC22 [ps]",2,3);

  sprintf(name, "cSCI%d_TofLL", 5);
  cSCI_TofLL5 = MakeWindowCond(fname,name, 2500, 80000, hSCI_TofLL5->GetName());

  sprintf(name, "cSCI%d_TofRR", 5);
  cSCI_TofRR5 = MakeWindowCond(fname,name, 2500, 80000, hSCI_TofRR5->GetName());


   // ToF SC22-SC81 
  sprintf(fname,"SCI/TOF/TOF(%d)",6);
  sprintf(name,"SCI_22_81_TofLL");
  hSCI_TofLL6 = MakeH1I(fname,name,2000,0,100000,"TAC SC81L-SC22L [ps]",2,3);

  sprintf(name,"SCI_22_81_TofRR");
  hSCI_TofRR6 = MakeH1I(fname,name,2000,0,100000,"TAC SC81R-SC22R [ps]",2,3);

  sprintf(name,"SCI_22_81_Tof6");
  hSCI_Tof6 = MakeH1I(fname,name,2000,0,100000,"TAC SC81-SC22 [ps] (pos.corr.)",2,3);

  sprintf(name,"SCI_22_81_Tof6calib");
  hSCI_Tof6calib = MakeH1I(fname,name,250000,0,400000,"TOF SC81-SC22 [ps]",2,3);

  sprintf(name, "cSCI%d_TofLL", 6);
  cSCI_TofLL6 = MakeWindowCond(fname,name, 2500, 80000, hSCI_TofLL6->GetName());

  sprintf(name, "cSCI%d_TofRR", 6);
  cSCI_TofRR6 = MakeWindowCond(fname,name, 2500, 80000, hSCI_TofRR6->GetName());
}

void TFRSAnlProc::Create_ID_Hist()
{
  //TMUSICParameter* music = (TMUSICParameter*) GetParameter("MUSICPar");
  //TFRSParameter* frs = (TFRSParameter*) GetParameter("FRSPar");

  char name[50], title[100];

  // Histogram ranges will be reset by setup file (setup_xxxx.C)
  hID_BRho[0]   = MakeH1I("ID/ID_S4","ID_BRho_TAS2",5000,2.5,14.5,"BRho of 1. Stage (TA-S2) [Tm]",2,6);
  hID_BRho[1]   = MakeH1I("ID/ID_S4","ID_BRho_S2S4",5000,2.5,14.5,"BRho of 2. Stage (S2-S4) [Tm]",2,6);
  //hID_ToF       = MakeH2I("ID/ID_S4","ID_ToF", 2000, 00000.,70000.,400,0,4000,"tof S2-S4 Sci.Tof(2) [ps]", "Music_dE(1)", 2);
  hID_beta      = MakeH1I("ID/ID_S4","ID_beta_S2S4",2000,0,2000,"beta(S2-S4)*1000",2,6);
  hID_dEToF     = MakeH2I("ID/ID_S4","ID_dEToF", 2000, 00000.,70000.,400,0,4000,"tof S2-S4 Sci.Tof(2) [ps]", "Music_dE(1)", 2);
  hID_AoQ       = MakeH1I("ID/ID_S4","ID_AoQ_S2S4",2000,1.3,2.8,"A/Q S2-S4",2,6);
  hID_AoQcorr   = MakeH1I("ID/ID_S4","ID_AoQ_corr_S2S4",2000,1.3,2.8,"A/Q S2-S4",2,6);
  hID_Z1        = MakeH1I("ID/ID_S4","ID_Z",1000,1,30,"Z from MUSIC41",2,6);
  hID_Z2        = MakeH1I("ID/ID_S4","ID_Z2",1000,1,30,"Z from MUSIC42",2,6);
  hID_Z3        = MakeH1I("ID/ID_S4","ID_Z3",1000,1,30,"Z from MUSIC43",2,6);
  hID_DeltaBrho_AoQ     = MakeH2I("ID/ID_S4","ID_DBrho_AoQ",300,1.3,2.8,500,0.,2.5,"A/Q s2-s4", "Brho(ta-s2) - Brho(s2-s4) [Tm]",2);
  hID_x2AoQ             = MakeH2I("ID/ID_S4","ID_x2AoQ", 300,1.3,2.8, 200,-100.,100.,"A/Q s2-s4", "X at S2 [mm]", 2);
  hID_Z1_AoQ            = MakeH2I("ID/ID_S4","ID_Z_AoQ", 300,1.3,2.8, 400,1,30,"A/Q s2-s4", "Z from MUSIC41", 2);
  hID_Z1_AoQcorr = MakeH2I("ID/ID_S4","ID_Z_AoQcorr", 300,1.3,2.8, 300,1,30,"A/Q s2-s4 with correction", "Z from MUSIC41", 2);
  hID_Z1_AoQ_zsame      = MakeH2I("ID/ID_S4","ID_Z_AoQ_zsame (Z1==Z2)", 600,1.3,2.8, 600,1,30,"A/Q s2-s4", "Z from MUSIC41", 2);
  hID_x2x4              = MakeH2I("ID/ID_S4","ID_x2_x4",200,-100,100,200,-100,100,"X at S2 [mm]","X at S4 [mm]",2);
  hID_Z2_AoQ            = MakeH2I("ID/ID_S4","ID_Z2_AoQ", 300,1.3,2.8, 400,1,30,"A/Q s2-s4", "Z from MUSIC42", 2);
  hID_Z2_AoQcorr        = MakeH2I("ID/ID_S4","ID_Z2_AoQcorr", 300,1.3,2.8, 300,1,30,"A/Q s2-s4 with correction", "Z from MUSIC42", 2);
  hID_Z1_Z2 = MakeH2I("ID/ID_S4","ID_Z_Z2", 350,1,30, 350,1,30,"Z", "Z2", 2);
  hID_Z1_Z3 = MakeH2I("ID/ID_S4","ID_Z_Z3", 250,1,30, 250,1,30,"Z", "Z3 'MUSIC'", 2);
  hID_Z2_Z3 = MakeH2I("ID/ID_S4","ID_Z2_Z3", 250,1,30, 250,1,30,"Z", "Z3 'MUSIC'", 2);
  hID_Z1_Sc21E = MakeH2I("ID/ID_S4","ID_Z_Sc21E", 300, 1,30 ,400,0,4000.,"Z from MUSIC41", "sqrt(Sc21_L*sC21_R)", 2);
  hID_x4AoQ = MakeH2I("ID/ID_S4","ID_x4AoQ", 100,1.3,2.8, 100,-100.,100.,"A/Q s2-s4", "X at S4 [mm]", 2);
  hID_x4z = MakeH2I("ID/ID_S4","ID_x4z", 300,1,30, 200,-100.,100., "Z from MUSIC41", "X at S4 [mm]", 2);
  hID_x2z = MakeH2I("ID/ID_S4","ID_x2z", 300,1,30, 200,-100.,100., "Z from MUSIC41", "X at S2 [mm]", 2);

  // Histogram ranges will be reset by setup file (setup_xxxx.C)
  hID_BRho[2]   = MakeH1I("ID/ID_S8","ID_BRho_S2S8",5000,2.5,14.5,"BRho (S2-S8) [Tm]",2,6);
  hID_tof_s2s8  = MakeH1I("ID/ID_S8","ID_tof_S2S8",2000,200000,400000,"TOF (S2-S8) [ps]",2,6);
  hID_beta_s2s8 = MakeH1I("ID/ID_S8","ID_beta_S2S8",2000,0,2000,"beta(S2-S8)*1000",2,6);
  hID_Z_sc81    = MakeH1I("ID/ID_S8","ID_Z_sc81" ,1000,1,30,"Z from Sc81",2,6);
  hID_dE_s2tpc  = MakeH1I("ID/ID_S8","ID_dE_s2tpc",2000,0,2000,"dE from S2TPC",2,6);
  hID_Z_s2tpc   = MakeH1I("ID/ID_S8","ID_Z_s2tpc",1000,1,30,"Z from S2TPC",2,6);
  hID_AoQ_s2s8  = MakeH1I("ID/ID_S8","ID_AoQ_S2S8",2000,1.3,2.8,"A/Q S2-S8",2,6);
  hID_Z_sc81_AoQ_s2s8 = MakeH2I("ID/ID_S8","ID_Z(sc81)_AoQ(s2s8)", 300,1.3,2.8, 400,1,30,"A/Q s2-s8", "Z from sc81", 2);
  hID_dE_sc81_AoQ_s2s8= MakeH2I("ID/ID_S8","ID_dE(sc81)_AoQ(s2s8)", 300,1.3,2.8, 400,1,2000,"A/Q s2-s8", "dE from sc81", 2);
  hID_Z_s2tpc_AoQ_s2s8= MakeH2I("ID/ID_S8","ID_Z(s2tpc)_AoQ(s2s8)", 300,1.3,2.8, 400,1,30,"A/Q s2-s8", "Z from s2tpc", 2);
  hID_dE_s2tpc_AoQ_s2s8= MakeH2I("ID/ID_S8","ID_dE(s2tpc)_AoQ(s2s8)", 300,1.3,2.8, 400,1,2000,"A/Q s2-s8", "dE from s2tpc", 2);
  // conditions
  cID_x2 = MakeWindowCond("ID","cID_x2", -100.0, 100.0);
  cID_x4 = MakeWindowCond("ID","cID_x4", -100.0, 100.0);
  cID_x8 = MakeWindowCond("ID","cID_x8", -100.0, 100.0);

  Float_t cID_dEToF_points[4][2] =
    {{    0.,    0.},
     {    0., 4000.},
     {40000., 4000.},
     {40000.,    0.}};
  cID_dEToF = MakePolyCond("ID","cID_dEToF",4, cID_dEToF_points, hID_dEToF->GetName());

  // ========================================
  //  z vs AoQ plot (main PID gate at S4)
  int num_ID_Z_AoQ[5] = {5, 5, 5, 5, 5};
  Float_t init_ID_Z_AoQ[5][5][2] =
     {
       // ID_Z_AOQ(1)
       /* 213Fr setting */
       {{2.45205,        86.7875},
        {2.46124,        86.7458},
        {2.46202,        88.1625},
        {2.4496,        88.1417},
        {2.45205,        86.7875}},

       // ID_Z_AOQ(2)
       /* 70 Ni @ 70Ni setting shifted by 10*/
       {{2.482,        38.0000},
        {2.508,        38.5000},
        {2.522,        38.0000},
        {2.489,        37.5000},
        {2.488,        37.5000}},

       // ID_Z_AOQ(3)
       {{2.25029,      51.22740},
        {2.27401,      50.88124},
        {2.30980,      51.80895},
        {2.28475,      51.93358},
        {2.25208,      52.07204}},

       //ID_Z_AOQ(4)
       {{2.25222,      49.96984},
        {2.24048,      49.85215},
        {2.24764,      49.28444},
        {2.25967,      49.38137},
        {2.26654,      49.68599}},

       // ID_Z_AOQ(5)
       {{2.55977,      52.6315},
        {2.55247,      52.293},
        {2.57298,      51.8529},
        {2.58529,      52.1914},
        {2.57936,      52.6315}}
     };

  for(int i=0;i<5;i++){
    sprintf(name,"cID_ZAoQ(%d)",i);
    cID_Z1_AoQ[i] = MakePolyCond("ID", name, num_ID_Z_AoQ[i], init_ID_Z_AoQ[i], hID_Z1_AoQ->GetName());
  }


  // ========================================
  //  X2 vs AoQ plot
  int num_ID_x2AoQ[6] = {5, 5, 5, 5, 5}; // num of points for polygon
  Float_t init_ID_x2AoQ[6][5][2] =
     {
       {{  2.009 ,   87.121 },
	{  2.0113,  -82.0475},
	{  2.3872,  -82.3590},
	{  2.3872,  -82.3590},
	{  2.3886,   85.8756}
       },
       {{  2.009 ,   87.121 },
	{  2.0113,  -82.0475},
	{  2.3872,  -82.3590},
	{  2.3872,  -82.3590},
	{  2.3886,   85.8756}
       },
       {{  2.009 ,   87.121 },
	{  2.0113,  -82.0475},
	{  2.3872,  -82.3590},
	{  2.3872,  -82.3590},
	{  2.3886,   85.8756}
       },
       {{  2.009 ,   87.121 },
	{  2.0113,  -82.0475},
	{  2.3872,  -82.3590},
	{  2.3872,  -82.3590},
	{  2.3886,   85.8756}
       },
       {{  2.009 ,   87.121 },
	{  2.0113,  -82.0475},
	{  2.3872,  -82.3590},
	{  2.3872,  -82.3590},
	{  2.3886,   85.8756}
       }
     };

  for(int i=0;i<5;++i)
    {
      sprintf(name,"cID_x2AoQ(%d)",i);
      cID_x2AoQ[i] = MakePolyCond("ID",name,num_ID_x2AoQ[i],init_ID_x2AoQ[i], hID_x2AoQ->GetName());
    }




  // ========================================
  //  X4 vs AoQ plot
  int num_ID_x4AoQ[5] = {5, 5, 5, 5, 5}; // num of points for polygon
  Float_t init_ID_X4_AoQ[5][5][2] =
     {
       // ID_X4_AOQ(0)
       {{2.1, -90},
	 {2.1,  90},
	 {2.5,  90},
	 {2.5, -90},
	 {2.1, -90},
       },

       // ID_X4_AOQ(1)
       {{2.1, -90},
	 {2.1,  90},
	 {2.5,  90},
	 {2.5, -90},
	 {2.1, -90},
       },

       // ID_X4_AOQ(2)
       {{2.1, -90},
	 {2.1,  90},
	 {2.5,  90},
	 {2.5, -90},
	 {2.1, -90},
       },

       // ID_X4_AOQ(3)
       {{2.1, -90},
	 {2.1,  90},
	 {2.5,  90},
	 {2.5, -90},
	 {2.1, -90},
       },

       // ID_X4_AOQ(4)
       {{2.1, -90},
	 {2.1,  90},
	 {2.5,  90},
	 {2.5, -90},
	 {2.1, -90},
       }
     };

  for(int i=0;i<5;++i)
    {
      sprintf(name,"cID_x4AoQ(%d)",i);
      cID_x4AoQ[i] = MakePolyCond("ID",name, num_ID_x4AoQ[i], init_ID_X4_AoQ[i], hID_x4AoQ->GetName());
    }
 }

void TFRSAnlProc::Create_Gated_Hist()
{
  //  order should be cID_Z1_AoQ[5], cID_x2AoQ[5],  cID_x4AoQ[5]
  char gate_name[256];
  int tpcid[7]={21,22,23,24,41,42,31};

  for(int igate=0; igate<15; igate++){
    if(0 <=igate && igate<5){  sprintf(gate_name,cID_Z1_AoQ[igate]  ->GetName()); }
    if(5 <=igate && igate<10){ sprintf(gate_name,cID_x2AoQ[igate-5] ->GetName()); }
    if(10<=igate && igate<15){ sprintf(gate_name,cID_x4AoQ[igate-10]->GetName()); }

    for(int itpc=0; itpc<7; itpc++){
      hTPC_X_gate[itpc][igate] = MakeH1I(Form("Gated/%s/TPC%d",gate_name,tpcid[itpc]),Form("TPC%dX_%s",tpcid[itpc],gate_name),2000,0,100000,"TAC SC81R-SC21R [ps]",2,3);
      hTPC_Y_gate[itpc][igate] = MakeH1I(Form("Gated/%s/TPC%d",gate_name,tpcid[itpc]),Form("TPC%dY_%s",tpcid[itpc],gate_name),2000,0,100000,"TAC SC81R-SC21R [ps]",2,3);
    }
    hTPC_S2X_gate[igate] = MakeH1I(Form("Gated/%s/S2",gate_name),Form("TPC_S2focusX_%s",gate_name),200,-120,120,"S2X [mm]",2,3);
    hTPC_S2A_gate[igate] = MakeH1I(Form("Gated/%s/S2",gate_name),Form("TPC_S2focusA_%s",gate_name),200, -40, 40,"S2A [mrad]",2,3);
    hTPC_S2Y_gate[igate] = MakeH1I(Form("Gated/%s/S2",gate_name),Form("TPC_S2focusY_%s",gate_name),200,-120,120,"S2Y [mm]",2,3);
    hTPC_S2B_gate[igate] = MakeH1I(Form("Gated/%s/S2",gate_name),Form("TPC_S2focusB_%s",gate_name),200, -40, 40,"S2B [mrad]",2,3);
    hTPC_S4X_gate[igate] = MakeH1I(Form("Gated/%s/S4",gate_name),Form("TPC_S4focusX_%s",gate_name),200,-120,120,"S4X [mm]",2,3);
    hTPC_S4A_gate[igate] = MakeH1I(Form("Gated/%s/S4",gate_name),Form("TPC_S4focusA_%s",gate_name),200, -40, 40,"S4A [mrad]",2,3);
    hTPC_S4Y_gate[igate] = MakeH1I(Form("Gated/%s/S4",gate_name),Form("TPC_S4focusY_%s",gate_name),200,-120,120,"S4Y [mm]",2,3);
    hTPC_S4B_gate[igate] = MakeH1I(Form("Gated/%s/S4",gate_name),Form("TPC_S4focusB_%s",gate_name),200, -40, 40,"S4B [mrad]",2,3);
    hTPC_S2TargetX_gate[igate] = MakeH1I(Form("Gated/%s/S2",gate_name),Form("TPC_S2targetX_%s",gate_name),200,-120,120,"X at S2 target [mm]",2,3);
    hTPC_S2TargetY_gate[igate] = MakeH1I(Form("Gated/%s/S2",gate_name),Form("TPC_S2targetY_%s",gate_name),200,-120,120,"Y at S2 target [mm]",2,3);
    hTPC_S4TargetX_gate[igate] = MakeH1I(Form("Gated/%s/S4",gate_name),Form("TPC_S4targetX_%s",gate_name),200,-120,120,"X at S4 target [mm]",2,3);
    hTPC_S4TargetY_gate[igate] = MakeH1I(Form("Gated/%s/S4",gate_name),Form("TPC_S4targetY_%s",gate_name),200,-120,120,"Y at S4 target [mm]",2,3);
    for(int ch=0; ch<8; ch++){
      hMUSIC1_E_gate[ch][igate] = MakeH1I(Form("Gated/%s/MUSIC1",gate_name),Form("MUSIC1dE_%d_%s",ch,gate_name),4096,0,4096,"MUSIC dE [channel]",2,3);
      hMUSIC2_E_gate[ch][igate] = MakeH1I(Form("Gated/%s/MUSIC2",gate_name),Form("MUSIC2dE_%d_%s",ch,gate_name),4096,0,4096,"MUSIC dE [channel]",2,3);
      hMUSIC3_E_gate[ch][igate] = MakeH1I(Form("Gated/%s/MUSIC3",gate_name),Form("MUSIC3dE_%d_%s",ch,gate_name),4096,0,4096,"MUSIC dE [channel]",2,3);
    }
  }
  return;
}



void TFRSAnlProc::Process_Gated_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt)
{
  for(int igate=0; igate<15; igate++){
    bool b_this_gate = false;
    //  order should be cID_z_AoQ[5], cID_x2AoQ[5],  cID_x4AoQ[5]
    if(0 <=igate && igate<5){  b_this_gate = tgt.id_b_z_AoQ[igate] ;}
    if(5 <=igate && igate<10){ b_this_gate = tgt.id_b_x2AoQ[igate-5];}
    if(10<=igate && igate<15){ b_this_gate = tgt.id_b_x4AoQ[igate-10];}

    if(true==b_this_gate){
      for(int itpc=0; itpc<7; itpc++){
	if(clb.b_tpc_xy[itpc]) hTPC_X_gate[itpc][igate] ->Fill(clb.tpc_x[itpc]);
	if(clb.b_tpc_xy[itpc]) hTPC_Y_gate[itpc][igate] ->Fill(clb.tpc_y[itpc]);
      }

      if(clb.b_tpc_xy[2] && clb.b_tpc_xy[3]){//tpc2324
	hTPC_S2X_gate[igate]->Fill(clb.tpc_x_s2_foc_23_24);
	hTPC_S2Y_gate[igate]->Fill(clb.tpc_y_s2_foc_23_24);
	hTPC_S2A_gate[igate]->Fill(clb.tpc_angle_x_s2_foc_23_24);
	hTPC_S2B_gate[igate]->Fill(clb.tpc_angle_y_s2_foc_23_24);
	hTPC_S2TargetX_gate[igate]->Fill(clb.tpc23_24_s2target_x);
	hTPC_S2TargetY_gate[igate]->Fill(clb.tpc23_24_s2target_y);
      }else if (clb.b_tpc_xy[1] && clb.b_tpc_xy[3]){//tpc2224
	hTPC_S2X_gate[igate]->Fill(clb.tpc_x_s2_foc_22_24);
	hTPC_S2Y_gate[igate]->Fill(clb.tpc_y_s2_foc_22_24);
	hTPC_S2A_gate[igate]->Fill(clb.tpc_angle_x_s2_foc_22_24);
	hTPC_S2B_gate[igate]->Fill(clb.tpc_angle_y_s2_foc_22_24);
	hTPC_S2TargetX_gate[igate]->Fill(clb.tpc22_24_s2target_x);
	hTPC_S2TargetY_gate[igate]->Fill(clb.tpc22_24_s2target_y);
      }else if (clb.b_tpc_xy[0] && clb.b_tpc_xy[1]){//tpc2122
	hTPC_S2X_gate[igate]->Fill(clb.tpc_x_s2_foc_21_22);
	hTPC_S2Y_gate[igate]->Fill(clb.tpc_y_s2_foc_21_22);
	hTPC_S2A_gate[igate]->Fill(clb.tpc_angle_x_s2_foc_21_22);
	hTPC_S2B_gate[igate]->Fill(clb.tpc_angle_y_s2_foc_21_22);
	hTPC_S2TargetX_gate[igate]->Fill(clb.tpc21_22_s2target_x);
	hTPC_S2TargetY_gate[igate]->Fill(clb.tpc21_22_s2target_y);
      }
      // S4 only 1 possibility =  TPC4142
      if(clb.b_tpc_xy[4] && clb.b_tpc_xy[5]){
	hTPC_S4X_gate[igate]->Fill(clb.tpc_x_s4);
	hTPC_S4A_gate[igate]->Fill(clb.tpc_angle_x_s4);
	hTPC_S4Y_gate[igate]->Fill(clb.tpc_y_s4);
	hTPC_S4B_gate[igate]->Fill(clb.tpc_angle_y_s4);
	hTPC_S4TargetX_gate[igate]->Fill(clb.tpc_s4target_x);
	hTPC_S4TargetY_gate[igate]->Fill(clb.tpc_s4target_y);
      }

      for(int ch=0; ch<8; ch++){
	hMUSIC1_E_gate[ch][igate] ->Fill(srt.music_e1[ch]);
	hMUSIC2_E_gate[ch][igate] ->Fill(srt.music_e2[ch]);
	hMUSIC3_E_gate[ch][igate] ->Fill(srt.music_e3[ch]);
      }

    }//if b_this_gate
  }//i-gate
  return;

}

void TFRSAnlProc::Process_MUSIC_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt)
{

  tgt.music1_anodes_cnt = 0;
  tgt.music2_anodes_cnt = 0;
  tgt.music3_anodes_cnt = 0;


   // Munich MUSIC

  for (int i=0;i<8;i++)
    {
      /* 8 anodes of TUM MUSIC and Travelling MUSIC */
      /****** first MUSIC ***** threshold changed to 5, 9/8/2012 **/
      if ( srt.music_e1[i] > 5){
	if(bDrawHist){
	    hMUSIC1_E[i]->Fill(srt.music_e1[i]);
	}
	tgt.music_b_e1[i] = cMusic1_E[i]->Test(srt.music_e1[i]);
	if (tgt.music_b_e1[i]){
	  tgt.music1_anodes_cnt++;
	}
      }

      if (srt.music_t1[i] > 0){
	if(bDrawHist){
	  hMUSIC1_T[i]->Fill(srt.music_t1[i]);
	}
	tgt.music_b_t1[i] = cMusic1_T[i]->Test(srt.music_t1[i]);
      }

      /****** second MUSIC = TUM *****/
      if ( srt.music_e2[i] > 5){
	if(bDrawHist){
	    hMUSIC2_E[i]->Fill(srt.music_e2[i]);
	}
	tgt.music_b_e2[i] = cMusic2_E[i]->Test(srt.music_e2[i]);
	if (tgt.music_b_e2[i]){ tgt.music2_anodes_cnt++; }
      }

      if (srt.music_t2[i] > 0){
	if(bDrawHist){
	    hMUSIC2_T[i]->Fill(srt.music_t2[i]);
	}
	tgt.music_b_t2[i] = cMusic2_T[i]->Test(srt.music_t2[i]);
      }

      /****** third MUSIC = Travelling *****/
      if ( srt.music_e3[i] > 5){
	if(bDrawHist){
	  hMUSIC3_E[i]->Fill(srt.music_e3[i]);
	}
	tgt.music_b_e3[i] = cMusic3_E[i]->Test(srt.music_e3[i]);
	if (tgt.music_b_e3[i]){
	    tgt.music3_anodes_cnt++;
	}
      }
      if (srt.music_t3[i] > 0){
	if(bDrawHist){
	    hMUSIC3_T[i]->Fill(srt.music_t3[i]);
	}
	tgt.music_b_t3[i] = cMusic3_T[i]->Test(srt.music_t3[i]);
      }
    }// end of i-loop




  // calculate truncated dE from 8 anodes, Munich MUSIC

  if (8 == tgt.music1_anodes_cnt)
    {
      /* "quick-n-dirty solution according to Klaus:   */
      //      Float_t r1 = (srt.music_e1[0] - music->e1_off[0])*(srt.music_e1[1] - music->e1_off[1]);
      //      Float_t r2 = (srt.music_e1[2] - music->e1_off[2])*(srt.music_e1[3] - music->e1_off[3]);
      //      Float_t r3 = (srt.music_e1[4] - music->e1_off[4])*(srt.music_e1[5] - music->e1_off[5]);
      //      Float_t r4 = (srt.music_e1[6] - music->e1_off[6])*(srt.music_e1[7] - music->e1_off[7]);

      Float_t r1 = ((srt.music_e1[0])*music->e1_gain[0] + music->e1_off[0])*((srt.music_e1[1])*music->e1_gain[1] + music->e1_off[1]);
      Float_t r2 = ((srt.music_e1[2])*music->e1_gain[2] + music->e1_off[2])*((srt.music_e1[3])*music->e1_gain[3] + music->e1_off[3]);
      Float_t r3 = ((srt.music_e1[4])*music->e1_gain[4] + music->e1_off[4])*((srt.music_e1[5])*music->e1_gain[5] + music->e1_off[5]);
      Float_t r4 = ((srt.music_e1[6])*music->e1_gain[6] + music->e1_off[6])*((srt.music_e1[7])*music->e1_gain[7] + music->e1_off[7]);

      if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) )
	{
	  tgt.b_de1 = kTRUE;
	  tgt.de[0] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );
	  tgt.de_cor[0] = tgt.de[0];
	  if(bDrawHist){
	    hMUSIC1_dE->Fill(tgt.de[0]);
	  }
	}
    }


  if (8 == tgt.music2_anodes_cnt)
    {

      Float_t r1 = ((srt.music_e2[0])*music->e2_gain[0] + music->e2_off[0])*((srt.music_e2[1])*music->e2_gain[1] + music->e2_off[1]);
      Float_t r2 = ((srt.music_e2[2])*music->e2_gain[2] + music->e2_off[2])*((srt.music_e2[3])*music->e2_gain[3] + music->e2_off[3]);
      Float_t r3 = ((srt.music_e2[4])*music->e2_gain[4] + music->e2_off[4])*((srt.music_e2[5])*music->e2_gain[5] + music->e2_off[5]);
      Float_t r4 = ((srt.music_e2[6])*music->e2_gain[6] + music->e2_off[6])*((srt.music_e2[7])*music->e2_gain[7] + music->e2_off[7]);

      if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) )
	{
	  tgt.b_de2 = kTRUE;
	  tgt.de[1] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );
	  tgt.de_cor[1] = tgt.de[1];
	  if(bDrawHist){
	    hMUSIC2_dE->Fill(tgt.de[1]);
	  }
	}
    }


  if (8 == tgt.music3_anodes_cnt)
    {
      Float_t r1 = ((srt.music_e3[0])*music->e3_gain[0] + music->e3_off[0])*((srt.music_e3[1])*music->e3_gain[1] + music->e3_off[1]);
      Float_t r2 = ((srt.music_e3[2])*music->e3_gain[2] + music->e3_off[2])*((srt.music_e3[3])*music->e3_gain[3] + music->e3_off[3]);
      Float_t r3 = ((srt.music_e3[4])*music->e3_gain[4] + music->e3_off[4])*((srt.music_e3[5])*music->e3_gain[5] + music->e3_off[5]);
      Float_t r4 = ((srt.music_e3[6])*music->e3_gain[6] + music->e3_off[6])*((srt.music_e3[7])*music->e3_gain[7] + music->e3_off[7]);

      if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) )
	{
	  tgt.b_de3 = kTRUE;
	  tgt.de[2] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );
	  tgt.de_cor[2] = tgt.de[2];
	  if(bDrawHist){
	    hMUSIC3_dE->Fill(tgt.de[2]);
	  }
	}

      if (tgt.music_b_t3[0] && tgt.music_b_t3[1] && tgt.music_b_t3[2] && tgt.music_b_t3[3]){
	tgt.b_dt3 = kTRUE;
      }
    }


  if(bDrawHist){
    if(tgt.b_de1 && tgt.b_de2){ hMUSIC_dE1dE2->Fill(tgt.de[0],tgt.de[1]); }
    if(tgt.b_de1 && tgt.b_de3){ hMUSIC_dE1dE3->Fill(tgt.de[0],tgt.de[2]); }
    if(tgt.b_de2 && tgt.b_de3){ hMUSIC_dE2dE3->Fill(tgt.de[1],tgt.de[2]); }
  }


  /* Position (X) correction by TPC */

  if(clb.b_tpc_xy[4]&&clb.b_tpc_xy[5]){

    tgt.music1_x_mean = clb.tpc_music41_x;
    tgt.music2_x_mean = clb.tpc_music42_x;
    tgt.music3_x_mean = clb.tpc_music43_x;

    Float_t power, Corr;
    // correction for MUSIC41
    if(tgt.b_de1){
      power = 1., Corr = 0.;
      for(int i=0;i<4;i++) {
	Corr += music->pos_a1[i] * power;
	power *= tgt.music1_x_mean;
      }
      if (Corr!=0) {
	Corr = music->pos_a1[0] / Corr;
	tgt.de_cor[0] = tgt.de[0] * Corr;
      }
      if(bDrawHist){
	hMUSIC1_dE_x   ->Fill(tgt.music1_x_mean, tgt.de[0]);
	hMUSIC1_dECOR_x->Fill(tgt.music1_x_mean, tgt.de_cor[0]);
	hMUSIC1_dECOR  ->Fill(tgt.de_cor[0]);
      }
    }

    // correction for MUSIC42
    if(tgt.b_de2){
      power = 1., Corr = 0.;
      for(int i=0;i<4;i++) {
	Corr += music->pos_a2[i] * power;
	power *= tgt.music2_x_mean;
      }
      if (Corr!=0) {
	Corr = music->pos_a2[0] / Corr;
	tgt.de_cor[1] = tgt.de[1] * Corr;
      }
      if(bDrawHist){
	hMUSIC2_dE_x   ->Fill(tgt.music2_x_mean, tgt.de[1]);
	hMUSIC2_dECOR_x->Fill(tgt.music2_x_mean, tgt.de_cor[1]);
	hMUSIC2_dECOR  ->Fill(tgt.de_cor[1]);
      }
    }
    // correction for MUSIC43
    if(tgt.b_de3){
      power = 1., Corr = 0.;
      for(int i=0;i<4;i++) {
	Corr += music->pos_a3[i] * power;
	power *= tgt.music3_x_mean;
      }
      if (Corr!=0) {
	Corr = music->pos_a3[0] / Corr;
	tgt.de_cor[2] = tgt.de[2] * Corr;
      }
      if(bDrawHist){
	hMUSIC3_dE_x   ->Fill(tgt.music3_x_mean, tgt.de[2]);
	hMUSIC3_dECOR_x->Fill(tgt.music3_x_mean, tgt.de_cor[2]);
	hMUSIC3_dECOR  ->Fill(tgt.de_cor[2]);
      }
    }
  } //end-of-if-for-tpc41-42-data
}


void TFRSAnlProc::Process_MultiHitTDC_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt){
   
  if(0!=srt.tdc_sc21l[0] && 0!=srt.tdc_sc21r[0]){
    tgt.mhtdc_sc21lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + srt.tdc_sc21l[0]  -  srt.tdc_sc21r[0] );
    tgt.mhtdc_sc21lr_x  = tgt.mhtdc_sc21lr_dt * sci->mhtdc_factor_21l_21r + sci->mhtdc_offset_21l_21r;
    float sc21pos_from_tpc    = -999.9;
    if(clb.b_tpc_xy[0]&&clb.b_tpc_xy[1]){
      sc21pos_from_tpc =  clb.tpc21_22_sc21_x ;
    }else if(clb.b_tpc_xy[2]&&clb.b_tpc_xy[3]){
      sc21pos_from_tpc =  clb.tpc23_24_sc21_x ;
    }
    if(bDrawHist) hMultiHitTDC_21l_21r     ->Fill(tgt.mhtdc_sc21lr_dt);
    if(bDrawHist) hMultiHitTDC_SC21X       ->Fill(tgt.mhtdc_sc21lr_x);
    if(bDrawHist) hMultiHitTDC_21l_21r_TPCX->Fill(tgt.mhtdc_sc21lr_dt, sc21pos_from_tpc);
    if(bDrawHist) hMultiHitTDC_SC21X_TPCX  ->Fill(tgt.mhtdc_sc21lr_x, sc21pos_from_tpc);
  }

  if(0!=srt.tdc_sc41l[0] && 0!=srt.tdc_sc41r[0]){
    tgt.mhtdc_sc41lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + srt.tdc_sc41l[0]  -  srt.tdc_sc41r[0] );
    tgt.mhtdc_sc41lr_x  = tgt.mhtdc_sc41lr_dt * sci->mhtdc_factor_41l_41r + sci->mhtdc_offset_41l_41r;
    if(bDrawHist) hMultiHitTDC_41l_41r     ->Fill(tgt.mhtdc_sc41lr_dt);
    if(bDrawHist) hMultiHitTDC_SC41X       ->Fill(tgt.mhtdc_sc41lr_x);
    if(bDrawHist) hMultiHitTDC_41l_41r_TPCX->Fill(tgt.mhtdc_sc41lr_dt, clb.tpc_sc41_x);
    if(bDrawHist) hMultiHitTDC_SC41X_TPCX  ->Fill(tgt.mhtdc_sc41lr_x, clb.tpc_sc41_x);
  }

  if(0!=srt.tdc_sc42l[0] && 0!=srt.tdc_sc42r[0]){
    tgt.mhtdc_sc42lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + srt.tdc_sc42l[0]  -  srt.tdc_sc42r[0] );
    tgt.mhtdc_sc42lr_x  = tgt.mhtdc_sc42lr_dt * sci->mhtdc_factor_42l_42r + sci->mhtdc_offset_42l_42r;
    if(bDrawHist) hMultiHitTDC_42l_42r     ->Fill(tgt.mhtdc_sc42lr_dt);
    if(bDrawHist) hMultiHitTDC_SC42X       ->Fill(tgt.mhtdc_sc42lr_x);
    if(bDrawHist) hMultiHitTDC_42l_42r_TPCX->Fill(tgt.mhtdc_sc42lr_dt, clb.tpc_sc42_x);
    if(bDrawHist) hMultiHitTDC_SC42X_TPCX  ->Fill(tgt.mhtdc_sc42lr_x, clb.tpc_sc42_x);
  }

  if(0!=srt.tdc_sc43l[0] && 0!=srt.tdc_sc43r[0]){
    tgt.mhtdc_sc43lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + srt.tdc_sc43l[0]  -  srt.tdc_sc43r[0] );
    tgt.mhtdc_sc43lr_x  = tgt.mhtdc_sc43lr_dt * sci->mhtdc_factor_43l_43r + sci->mhtdc_offset_43l_43r;
    if(bDrawHist) hMultiHitTDC_43l_43r     ->Fill(tgt.mhtdc_sc43lr_dt);
    if(bDrawHist) hMultiHitTDC_SC43X       ->Fill(tgt.mhtdc_sc43lr_x);
    if(bDrawHist) hMultiHitTDC_43l_43r_TPCX->Fill(tgt.mhtdc_sc43lr_dt, clb.tpc_sc43_x);
    if(bDrawHist) hMultiHitTDC_SC43X_TPCX  ->Fill(tgt.mhtdc_sc43lr_x, clb.tpc_sc43_x);
  }

  if(0!=srt.tdc_sc31l[0] && 0!=srt.tdc_sc31r[0]){
    tgt.mhtdc_sc31lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + srt.tdc_sc31l[0]  -  srt.tdc_sc31r[0] );
    tgt.mhtdc_sc31lr_x  = tgt.mhtdc_sc31lr_dt * sci->mhtdc_factor_31l_31r + sci->mhtdc_offset_31l_31r;
    if(bDrawHist) hMultiHitTDC_31l_31r     ->Fill(tgt.mhtdc_sc31lr_dt);
    if(bDrawHist) hMultiHitTDC_SC31X       ->Fill(tgt.mhtdc_sc31lr_x);
    if(bDrawHist) hMultiHitTDC_31l_31r_TPCX->Fill(tgt.mhtdc_sc31lr_dt, clb.tpc_x[6]); //only 1 tpc
    if(bDrawHist) hMultiHitTDC_SC31X_TPCX  ->Fill(tgt.mhtdc_sc31lr_x, clb.tpc_x[6]);//only 1 tpc
  }

  if(0!=srt.tdc_sc81l[0] && 0!=srt.tdc_sc81r[0]){
    tgt.mhtdc_sc81lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + srt.tdc_sc81l[0]  -  srt.tdc_sc81r[0] );
    tgt.mhtdc_sc81lr_x  = tgt.mhtdc_sc81lr_dt * sci->mhtdc_factor_81l_81r + sci->mhtdc_offset_81l_81r;
    if(bDrawHist) hMultiHitTDC_81l_81r     ->Fill(tgt.mhtdc_sc81lr_dt);
    if(bDrawHist) hMultiHitTDC_SC81X       ->Fill(tgt.mhtdc_sc81lr_x);
    // no tpc is available at S8
  }

  if(0!=srt.tdc_sc21l[0] && 0!=srt.tdc_sc21r[0] && 0!=srt.tdc_sc41l[0] && 0!=srt.tdc_sc41r[0]){
    tgt.mhtdc_tof4121 = sci->mhtdc_factor_ch_to_ns*( 0.5*(srt.tdc_sc41l[0]+srt.tdc_sc41r[0])  - 0.5*(srt.tdc_sc21l[0]+srt.tdc_sc21r[0]) ) + sci->mhtdc_offset_41_21;
    if(bDrawHist) hMultiHitTDC_TOF_41_21->Fill(tgt.mhtdc_tof4121);
  }
  if(0!=srt.tdc_sc21l[0] && 0!=srt.tdc_sc21r[0] && 0!=srt.tdc_sc42l[0] && 0!=srt.tdc_sc42r[0]){
    tgt.mhtdc_tof4221 = sci->mhtdc_factor_ch_to_ns*( 0.5*(srt.tdc_sc42l[0]+srt.tdc_sc42r[0])  - 0.5*(srt.tdc_sc21l[0]+srt.tdc_sc21r[0]) ) + sci->mhtdc_offset_42_21;
    if(bDrawHist) hMultiHitTDC_TOF_42_21->Fill(tgt.mhtdc_tof4221);
  }
  if(0!=srt.tdc_sc21l[0] && 0!=srt.tdc_sc21r[0] && 0!=srt.tdc_sc43l[0] && 0!=srt.tdc_sc43r[0]){
    tgt.mhtdc_tof4321 = sci->mhtdc_factor_ch_to_ns*( 0.5*(srt.tdc_sc43l[0]+srt.tdc_sc43r[0])  - 0.5*(srt.tdc_sc21l[0]+srt.tdc_sc21r[0]) ) + sci->mhtdc_offset_43_21;
    if(bDrawHist) hMultiHitTDC_TOF_43_21->Fill(tgt.mhtdc_tof4321);
  }
  if(0!=srt.tdc_sc21l[0] && 0!=srt.tdc_sc21r[0] && 0!=srt.tdc_sc31l[0] && 0!=srt.tdc_sc31r[0]){
    tgt.mhtdc_tof3121 = sci->mhtdc_factor_ch_to_ns*( 0.5*(srt.tdc_sc31l[0]+srt.tdc_sc31r[0])  - 0.5*(srt.tdc_sc21l[0]+srt.tdc_sc21r[0]) ) + sci->mhtdc_offset_31_21;
    if(bDrawHist) hMultiHitTDC_TOF_31_21->Fill(tgt.mhtdc_tof3121);
  }
  if(0!=srt.tdc_sc21l[0] && 0!=srt.tdc_sc21r[0] && 0!=srt.tdc_sc81l[0] && 0!=srt.tdc_sc81r[0]){
    tgt.mhtdc_tof8121 = sci->mhtdc_factor_ch_to_ns*( 0.5*(srt.tdc_sc81l[0]+srt.tdc_sc81r[0])  - 0.5*(srt.tdc_sc21l[0]+srt.tdc_sc21r[0]) ) + sci->mhtdc_offset_81_21;
    if(bDrawHist) hMultiHitTDC_TOF_81_21->Fill(tgt.mhtdc_tof8121);
  }
  return ;

}


void TFRSAnlProc::Process_SCI_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt)
{
        /*-------------------------------------------------------------------------*/
 	/* focus index: detector number                  tof index  tof path       */
 	/*       0:     Sc01                                0:     TA - S1         */
 	/*       1:     Sc11                                1:     S1 - S2         */
 	/*       2:     Sc21                                2:     S2 - S41        */
 	/*       3:     Sc22                                3:     S2 - S42        */
 	/*       4:     Sc31                                4:     S2 - 81         */
 	/*       5:     Sc41                                5:     S2 - E1         */
	/*                                                                         */
 	/*       6:     Sc42                              tof index not used up to */
 	/*       7:     Sc43 (previously Sc51)             now, only separate      */
 	/*       8:     Sc61                              variables for S2-S41 and */
 	/*       9:     ScE1 (ESR)                                S2-S42           */
 	/*      10:     Sc81                                                       */
 	/*      11:     Sc82                                                       */
 	/*-------------------------------------------------------------------------*/



  /*  Raw data  */
   tgt.sci_l[2] = srt.de_21l;  /* 21L         */
   tgt.sci_r[2] = srt.de_21r;  /* 21R         */
   tgt.sci_tx[2] = srt.dt_21l_21r + rand3();

   tgt.sci_l[4] = srt.de_31l;  /* 31L         */
   tgt.sci_r[4] = srt.de_31r;  /* 31R         */

   tgt.sci_l[5] = srt.de_41l;  /* 41L         */
   tgt.sci_r[5] = srt.de_41r;  /* 41R         */
   tgt.sci_tx[5] = srt.dt_41l_41r + rand3();

   tgt.sci_l[6] = srt.de_42l;  /* 42L         */
   tgt.sci_r[6] = srt.de_42r;  /* 42R         */
   tgt.sci_tx[6] = srt.dt_42l_42r + rand3();

   tgt.sci_l[7] = srt.de_43l;  /* 43L         */
   tgt.sci_r[7] = srt.de_43r;  /* 43R         */
   tgt.sci_tx[7] = srt.dt_43l_43r + rand3();

   tgt.sci_l[10] = srt.de_81l; /* 81L         */
   tgt.sci_r[10] = srt.de_81r; /* 81R         */
   tgt.sci_tx[10] = srt.dt_81l_81r + rand3();

   tgt.sci_tx[3] = srt.dt_22l_22r + rand3();

   for (int cnt=0;cnt<7;cnt++) //
     {
       int idx = 0 ;
       float posref = -999;
       //int mw_idx = 0;
       //Float_t mwx = 0;
       switch(cnt)
	 {
	 case 0:        /* SC21 */
	   idx = 2;
	   // posref from tpc
	   if(clb.b_tpc_xy[2]&&clb.b_tpc_xy[3]){
	     posref =  clb.tpc23_24_sc21_x ;
	   }else if(clb.b_tpc_xy[0]&&clb.b_tpc_xy[1]){
	     posref =  clb.tpc21_22_sc21_x ;
	   }
	   //mw_idx = 2;
	   //mwx = clb.sc21_x;
	   break;
	 case 1:        /* SC31 */
	   idx = 4;
	   if(clb.b_tpc_xy[6]){ posref = clb.tpc_x[6]; }
	   break;
	 case 2:        /* SC41 */
	   idx = 5;
	   if(clb.b_tpc_xy[4]&&clb.b_tpc_xy[5]){
	     posref =  clb.tpc_sc41_x ;
	   }
	   //mw_idx = 5;
	   //mwx = clb.tpc_sc41_x;
	   break;
	 case 3:        /* SC42 */
           idx = 6;
	   if(clb.b_tpc_xy[4]&&clb.b_tpc_xy[5]){
	     posref =  clb.tpc_sc42_x ;
	   }
	   break;
	 case 4:
	   idx = 7;     /* SC43 */
	   if(clb.b_tpc_xy[4]&&clb.b_tpc_xy[5]){
	     posref =  clb.tpc_sc43_x ;
	   }
	   break;
	 case 5:
	   idx = 10;    /* SC81 */
	   // no position reference from tpc
	   break;
	 case 6:
	   idx = 3;    /* SC22 */
	   if(clb.b_tpc_xy[2]&&clb.b_tpc_xy[3]){
	     posref =  clb.tpc23_24_sc22_x ;
	   }else if(clb.b_tpc_xy[0]&&clb.b_tpc_xy[1]){
	     posref =  clb.tpc21_22_sc22_x ;
	   }
	   break;
	 default: idx = 2;
	 }

       // raw spectra
       tgt.sci_b_l[idx] = cSCI_L[idx]->Test(tgt.sci_l[idx]);
       tgt.sci_b_r[idx] = cSCI_R[idx]->Test(tgt.sci_r[idx]);

       if(bDrawHist)
	 {
	   hSCI_L[idx]->Fill(tgt.sci_l[idx]);
	   hSCI_R[idx]->Fill(tgt.sci_r[idx]);
	 }

       if(tgt.sci_b_l[idx] && tgt.sci_b_r[idx])
	 {
	   
	   // tgt.sci_e[idx] = sqrt( (tgt.sci_l[idx] - sci->le_a[0][idx]) * sci->le_a[1][idx]
	   //			  * (tgt.sci_r[idx] - sci->re_a[0][idx]) * sci->re_a[1][idx]);
	   tgt.sci_e[idx] = (tgt.sci_r[idx] - sci->re_a[0][idx]);
	   
	   tgt.sci_b_e[idx] = cSCI_E[idx]->Test(tgt.sci_e[idx]);
	   if(bDrawHist)
	     hSCI_E[idx]->Fill(tgt.sci_e[idx]);
	 }


       /*   Position in X direction:   */
       tgt.sci_b_tx[idx] = cSCI_Tx[idx]->Test(tgt.sci_tx[idx]);
       if (tgt.sci_b_tx[idx])
	 {
	   if(bDrawHist)
	     hSCI_Tx[idx]->Fill(tgt.sci_tx[idx]);

	   /* mm-calibrated     */
	   Float_t R = tgt.sci_tx[idx] ;//+ rand3();

	   Float_t power = 1., sum = 0.;
	   for(int i=0;i<7;i++)
	     {
	       sum += sci->x_a[i][idx] * power;
	       power *= R;
	     }

	   tgt.sci_x[idx] = sum;
	   tgt.sci_b_x[idx] = cSCI_X[idx]->Test(tgt.sci_x[idx]);
	   if(bDrawHist){
	     hSCI_X[idx]->Fill(tgt.sci_x[idx]);
	     hSCI_Tx_XTPC[idx]->Fill(tgt.sci_tx[idx],posref);
	     hSCI_X_XTPC[idx]->Fill(tgt.sci_x[idx],posref);
	   }
	 }

     } // end of loop for indices 2,3,4,5,6,7,10


   /***  Scintillator Tof  spectra ***/
   /*   S21 - S41 Calibrated tof  */
   tgt.sci_tofll2 = srt.dt_21l_41l*sci->tac_factor[2] - sci->tac_off[2] ;   /* S41L- S21L */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_tofrr2 = srt.dt_21r_41r*sci->tac_factor[3] - sci->tac_off[3] ;   /* S41R- S21R */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_b_tofll2 = cSCI_TofLL2->Test(tgt.sci_tofll2);
   tgt.sci_b_tofrr2 = cSCI_TofRR2->Test(tgt.sci_tofrr2);
   if(tgt.sci_b_tofll2 && tgt.sci_b_tofrr2){
     tgt.sci_tof2        =   (sci->tof_bll2 * tgt.sci_tofll2 + sci->tof_a2 + sci->tof_brr2 * tgt.sci_tofrr2)/2.0 ;  // tof_a2  is essentially unnecessary (even confusing) = 0
     tgt.sci_tof2_calib   =  -1.0*tgt.sci_tof2 + id->id_tofoff2;
   }
   if(bDrawHist){
       hSCI_TofLL2->Fill(tgt.sci_tofll2);
       hSCI_TofRR2->Fill(tgt.sci_tofrr2);
       hSCI_Tof2->Fill(tgt.sci_tof2);
       hSCI_Tof2calib->Fill(tgt.sci_tof2_calib);
    }

   /*   S21 - S42 Calibrated tof  */
   tgt.sci_tofll3 = srt.dt_42l_21l*sci->tac_factor[5] - sci->tac_off[5] ;   /* S42L- S21L */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_tofrr3 = srt.dt_42r_21r*sci->tac_factor[6] - sci->tac_off[6] ;   /* S42R- S21R */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_b_tofll3 = cSCI_TofLL3->Test(tgt.sci_tofll3);
   tgt.sci_b_tofrr3 = cSCI_TofRR3->Test(tgt.sci_tofrr3);
   if(tgt.sci_b_tofll3 && tgt.sci_b_tofrr3){
     tgt.sci_tof3        =   (sci->tof_bll3 * tgt.sci_tofll3 + sci->tof_a3 + sci->tof_brr3 * tgt.sci_tofrr3)/2.0 ;  // tof_a3  is essentially unnecessary (even confusing) = 0
     tgt.sci_tof3_calib   =  -1.0*tgt.sci_tof3 + id->id_tofoff3;
   }
   if(bDrawHist){
       hSCI_TofLL3->Fill(tgt.sci_tofll3);
       hSCI_TofRR3->Fill(tgt.sci_tofrr3);
       hSCI_Tof3->Fill(tgt.sci_tof3);
       hSCI_Tof3calib->Fill(tgt.sci_tof3_calib);
    }

   /*   S21 - S81 Calibrated tof  */
   tgt.sci_tofll4 = srt.dt_21l_81l*sci->tac_factor[9] - sci->tac_off[9] ;     /* S81L- S21L */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_tofrr4 = srt.dt_21r_81r*sci->tac_factor[10] - sci->tac_off[10] ;   /* S82R- S21R */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_b_tofll4 = cSCI_TofLL4->Test(tgt.sci_tofll4);
   tgt.sci_b_tofrr4 = cSCI_TofRR4->Test(tgt.sci_tofrr4);
   if(tgt.sci_b_tofll4 && tgt.sci_b_tofrr4){
     tgt.sci_tof4        =   (sci->tof_bll4 * tgt.sci_tofll4 + sci->tof_a4 + sci->tof_brr4 * tgt.sci_tofrr4)/2.0 ;  // tof_a4  is essentially unnecessary (even confusing) = 0
     tgt.sci_tof4_calib   =  -1.0*tgt.sci_tof4 + id->id_tofoff4;
   }
   if(bDrawHist){
       hSCI_TofLL4->Fill(tgt.sci_tofll4);
       hSCI_TofRR4->Fill(tgt.sci_tofrr4);
       hSCI_Tof4->Fill(tgt.sci_tof4);
       hSCI_Tof4calib->Fill(tgt.sci_tof4_calib);
    }

   /*   S22 - S41 Calibrated tof  */
   tgt.sci_tofll5 = srt.dt_22l_41l*sci->tac_factor[12] - sci->tac_off[12] ;     /* S41L- S22L */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_tofrr5 = srt.dt_22r_41r*sci->tac_factor[13] - sci->tac_off[13] ;     /* S41R- S22R */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_b_tofll5 = cSCI_TofLL5->Test(tgt.sci_tofll5);
   tgt.sci_b_tofrr5 = cSCI_TofRR5->Test(tgt.sci_tofrr5);
   if(tgt.sci_b_tofll5 && tgt.sci_b_tofrr5){
     tgt.sci_tof5        =   (sci->tof_bll5 * tgt.sci_tofll5 + sci->tof_a5 + sci->tof_brr5 * tgt.sci_tofrr5)/2.0 ;  // tof_a5  is essentially unnecessary (even confusing) = 0
     tgt.sci_tof5_calib   =  -1.0*tgt.sci_tof5 + id->id_tofoff5;
   }
   if(bDrawHist){
       hSCI_TofLL5->Fill(tgt.sci_tofll5);
       hSCI_TofRR5->Fill(tgt.sci_tofrr5);
       hSCI_Tof5->Fill(tgt.sci_tof5);
       hSCI_Tof5calib->Fill(tgt.sci_tof5_calib);
    }


   /*   S22 - S81 Calibrated tof  */
   tgt.sci_tofll6 = srt.dt_22l_81l*sci->tac_factor[14] - sci->tac_off[14] ;     /* S81L- S22L */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_tofrr6 = srt.dt_22r_81r*sci->tac_factor[15] - sci->tac_off[15] ;     /* S81R- S22R */  // tac_off is essentially unnecessary (even confusing)
   tgt.sci_b_tofll6 = cSCI_TofLL6->Test(tgt.sci_tofll6);
   tgt.sci_b_tofrr6 = cSCI_TofRR6->Test(tgt.sci_tofrr6);
   if(tgt.sci_b_tofll6 && tgt.sci_b_tofrr6){
     tgt.sci_tof6        =   (sci->tof_bll6 * tgt.sci_tofll6 + sci->tof_a6 + sci->tof_brr6 * tgt.sci_tofrr6)/2.0 ;  // tof_a6  is essentially unnecessary (even confusing) = 0
     tgt.sci_tof6_calib   =  -1.0*tgt.sci_tof6 + id->id_tofoff6;
   }
   if(bDrawHist){
       hSCI_TofLL6->Fill(tgt.sci_tofll6);
       hSCI_TofRR6->Fill(tgt.sci_tofrr6);
       hSCI_Tof6->Fill(tgt.sci_tof6);
       hSCI_Tof6calib->Fill(tgt.sci_tof6_calib);
    }
   


}


void TFRSAnlProc::Process_ID_MultiHitTDC_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt)
{
  
  float speed_light = 0.299792458; //m/ns
  float temp_tm_to_MeV = 299.792458;
  float temp_mu = 931.4940954; //MeV
  
  // Extraction of position to be used for momentum analysis
  float temp_s8x = tgt.mhtdc_sc81lr_x;
  float temp_s4x = -999.;
  if(clb.b_tpc_xy[4] && clb.b_tpc_xy[5]){
    temp_s4x = clb.tpc_x_s4 ;
  }
  float temp_s2x = -999.; //fill in the next if part
  if(1== id->mhtdc_s2pos_option){//SC21X from multihit tdc is used for S2X
    temp_s2x = tgt.mhtdc_sc21lr_x;
  }
  if(2== id->mhtdc_s2pos_option){//TPCX is used
    if(clb.b_tpc_xy[2] && clb.b_tpc_xy[3]){//tpc2324
      temp_s2x = clb.tpc_x_s2_foc_23_24;
    }else if(clb.b_tpc_xy[1] && clb.b_tpc_xy[3]){//tpc2224
      temp_s2x = clb.tpc_x_s2_foc_22_24;
    }else if (clb.b_tpc_xy[0] && clb.b_tpc_xy[1]){//tpc2122
      temp_s2x = clb.tpc_x_s2_foc_21_22;
    }
  }
  
  ////=======================================
  ////   S2S8 MultihitTDC ID analysis
  
  // Calculation of velocity beta and gamma
  tgt.id_mhtdc_beta_s2s8   =  ( id->mhtdc_length_s2s8 / tgt.mhtdc_tof8121) / speed_light;
  tgt.id_mhtdc_gamma_s2s8  = 1./sqrt(1. - tgt.id_mhtdc_beta_s2s8*tgt.id_mhtdc_beta_s2s8);
  
  // calculation of delta(momentum_deviation) and AoQ
  float mean_brho_s2s8 = 0.5*( frs->bfield[2] + frs->bfield[5] );
  if( -200<temp_s8x && temp_s8x<200. && -200.< temp_s2x && temp_s2x<200.){
    tgt.id_mhtdc_delta_s2s8 = (  (temp_s8x - id->pos_offset_sc81x) - (temp_s2x * frs->magnification[2] ))/(-1.0 * frs->dispersion[2] *1000.0 ) ; //1000 is dispertsion from meter to mm. -1.0 is sign definition.
    if(0.0 < tgt.id_mhtdc_beta_s2s8 && tgt.id_mhtdc_beta_s2s8 < 1.0){
	tgt.id_mhtdc_aoq_s2s8 = mean_brho_s2s8 *( 1. + tgt.id_mhtdc_delta_s2s8   ) * temp_tm_to_MeV / (temp_mu * tgt.id_mhtdc_beta_s2s8 * tgt.id_mhtdc_gamma_s2s8);
    }
  }
  // sc81x = 0 (deterined by slit) may not aggree with the optical reference.
  // for example, sc81x = 0 is adjusted by slit.
  // but tof calibration  was performed or good transmission was obtained with sc81x = 7 mm.
  // then x=7mm should correspond to delta_p = 0. 
  // this does not happen at s2 and s4
  // this is why the additional parameter (id->pos_offset_sc81x) is prepared for s8 here. 


  // calculation of dE and Z
  // use dE from tgt.id_de_s2tpc (tpcdE) and tgt.id_de_sc81
  // from S2TPC
  if(tgt.id_b_de_s2tpc && (tgt.id_mhtdc_beta_s2s8>0.0) && (tgt.id_mhtdc_beta_s2s8<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->mhtdc_vel_a_s2tpc[i];
      power *= tgt.id_mhtdc_beta_s2s8;
    }
    tgt.id_mhtdc_v_cor_s2tpc = sum;
    if (tgt.id_mhtdc_v_cor_s2tpc > 0.0){
      tgt.id_mhtdc_z_s2tpc = frs->primary_z * sqrt( tgt.id_de_s2tpc/tgt.id_mhtdc_v_cor_s2tpc ) + id->mhtdc_offset_z_s2tpc;
    }
  }

  // from SC81 
  if( (tgt.sci_e[10]>0.0)  && (tgt.id_mhtdc_beta_s2s8>0.0) && (tgt.id_mhtdc_beta_s2s8<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->mhtdc_vel_a_sc81[i];
      power *= tgt.id_mhtdc_beta_s2s8;
    }
    tgt.id_mhtdc_v_cor_sc81 = sum;
    if (tgt.id_mhtdc_v_cor_sc81 > 0.0){
      tgt.id_mhtdc_z_sc81 = frs->primary_z * sqrt(tgt.sci_e[10]/tgt.id_mhtdc_v_cor_sc81 ) + id->mhtdc_offset_z_sc81;
    }
  }

  if(bDrawHist){
    hID_MHTDCS2S8_DELTA ->Fill(tgt.id_mhtdc_delta_s2s8);
    hID_MHTDCS2S8_BETA  ->Fill(tgt.id_mhtdc_beta_s2s8);
    hID_MHTDCS2S8_AOQ   ->Fill(tgt.id_mhtdc_aoq_s2s8);
    hID_MHTDCS2S8_DELTA_BETA ->Fill(tgt.id_mhtdc_delta_s2s8, tgt.id_mhtdc_beta_s2s8);
    hID_MHTDCS2S8_AOQ_BETA   ->Fill(tgt.id_mhtdc_aoq_s2s8, tgt.id_mhtdc_beta_s2s8);
    hID_MHTDCS2S8_dES2TPC     ->Fill( tgt.id_de_s2tpc);
    hID_MHTDCS2S8_dES2TPC_BETA->Fill( tgt.id_de_s2tpc, tgt.id_mhtdc_beta_s2s8);
    hID_MHTDCS2S8_dES2TPC_AOQ ->Fill(tgt.id_mhtdc_aoq_s2s8,  tgt.id_de_s2tpc);
    hID_MHTDCS2S8_ZS2TPC      ->Fill(tgt.id_mhtdc_z_s2tpc);
    hID_MHTDCS2S8_ZS2TPC_AOQ  ->Fill(tgt.id_mhtdc_aoq_s2s8, tgt.id_mhtdc_z_s2tpc);
    hID_MHTDCS2S8_dESC81_BETA->Fill(tgt.id_mhtdc_beta_s2s8,tgt.sci_e[10]);
    hID_MHTDCS2S8_dESC81_AOQ ->Fill(tgt.id_mhtdc_aoq_s2s8, tgt.sci_e[10]);
    hID_MHTDCS2S8_ZSC81      ->Fill(tgt.id_mhtdc_z_sc81);
    hID_MHTDCS2S8_ZSC81_AOQ  ->Fill(tgt.id_mhtdc_aoq_s2s8, tgt.id_mhtdc_z_sc81);
  }


  ////=======================================
  ////   S2S4 MultihitTDC ID analysis
  
   // Calculation of velocity beta and gamma
  tgt.id_mhtdc_beta_s2s4   =  ( id->mhtdc_length_s2s4 / tgt.mhtdc_tof4121) / speed_light;
  tgt.id_mhtdc_gamma_s2s4  = 1./sqrt(1. - tgt.id_mhtdc_beta_s2s4*tgt.id_mhtdc_beta_s2s4);
  
  // calculation of delta(momentum_deviation) and AoQ
  float mean_brho_s2s4 = 0.5*( frs->bfield[2] + frs->bfield[3] );
  if( -200<temp_s4x && temp_s4x<200. && -200.< temp_s2x && temp_s2x<200.){
    tgt.id_mhtdc_delta_s2s4 = ( temp_s4x - (temp_s2x * frs->magnification[1] ))/(-1.0 * frs->dispersion[1] *1000.0 ) ; 
    if(0.0 < tgt.id_mhtdc_beta_s2s4 && tgt.id_mhtdc_beta_s2s4 < 1.0){
	tgt.id_mhtdc_aoq_s2s4 = mean_brho_s2s4 *( 1. + tgt.id_mhtdc_delta_s2s4   ) * temp_tm_to_MeV / (temp_mu * tgt.id_mhtdc_beta_s2s4 * tgt.id_mhtdc_gamma_s2s4);
    }
  }

  // calculation of dE and Z
  // from MUSIC41
  float temp_music41_de = tgt.de[0]>0.0;
  if( (temp_music41_de>0.0)  && (tgt.id_mhtdc_beta_s2s4>0.0) && (tgt.id_mhtdc_beta_s2s4<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->mhtdc_vel_a_music41[i];
      power *= tgt.id_mhtdc_beta_s2s4;
    }
    tgt.id_mhtdc_v_cor_music41 = sum;
    if (tgt.id_mhtdc_v_cor_music41 > 0.0){
      tgt.id_mhtdc_z_music41 = frs->primary_z * sqrt(temp_music41_de/tgt.id_mhtdc_v_cor_music41 ) + id->mhtdc_offset_z_music41;
    }
  }

  float temp_music42_de = tgt.de[1]>0.0;
  if( (temp_music42_de>0.0)  && (tgt.id_mhtdc_beta_s2s4>0.0) && (tgt.id_mhtdc_beta_s2s4<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->mhtdc_vel_a_music42[i];
      power *= tgt.id_mhtdc_beta_s2s4;
    }
    tgt.id_mhtdc_v_cor_music42 = sum;
    if (tgt.id_mhtdc_v_cor_music42 > 0.0){
      tgt.id_mhtdc_z_music42 = frs->primary_z * sqrt(temp_music42_de/tgt.id_mhtdc_v_cor_music42 ) + id->mhtdc_offset_z_music42;
    }
  }

  if(bDrawHist){
    hID_MHTDCS2S4_DELTA ->Fill(tgt.id_mhtdc_delta_s2s4);
    hID_MHTDCS2S4_BETA  ->Fill(tgt.id_mhtdc_beta_s2s4);
    hID_MHTDCS2S4_AOQ   ->Fill(tgt.id_mhtdc_aoq_s2s4);
    hID_MHTDCS2S4_DELTA_BETA ->Fill(tgt.id_mhtdc_delta_s2s4, tgt.id_mhtdc_beta_s2s4);
    hID_MHTDCS2S4_AOQ_BETA   ->Fill(tgt.id_mhtdc_aoq_s2s4, tgt.id_mhtdc_beta_s2s4);
    hID_MHTDCS2S4_dE41_BETA->Fill(temp_music41_de, tgt.id_mhtdc_beta_s2s4);
    hID_MHTDCS2S4_dE41_AOQ ->Fill(temp_music41_de, tgt.id_mhtdc_aoq_s2s4);
    hID_MHTDCS2S4_Z41      ->Fill(tgt.id_mhtdc_z_music41);
    hID_MHTDCS2S4_Z41_AOQ  ->Fill(tgt.id_mhtdc_aoq_s2s4, tgt.id_mhtdc_z_music41);
    hID_MHTDCS2S4_dE42_BETA->Fill(temp_music42_de, tgt.id_mhtdc_beta_s2s4);
    hID_MHTDCS2S4_dE42_AOQ ->Fill(temp_music42_de, tgt.id_mhtdc_aoq_s2s4);
    hID_MHTDCS2S4_Z42      ->Fill(tgt.id_mhtdc_z_music42);
    hID_MHTDCS2S4_Z42_AOQ  ->Fill(tgt.id_mhtdc_aoq_s2s4, tgt.id_mhtdc_z_music42);
  }
  
}


void TFRSAnlProc::Process_ID_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt)
{

  tgt.id_trigger=srt.trigger;
  if(tgt.id_trigger!=1){
    return;
  }

  /* accumulate raw detof spectrum  */
  if(bDrawHist){
    hID_dEToF->Fill(tgt.sci_tof2, tgt.de[0]);// changed to Music1. YT. 2016Jun.13 19:00
  }

  // focal plane informaiton
  // 1: (tpc2324 -> tpc2224 -> tpc2122),  2:  sc21,  3: sc22
  if(1 == id->x_s2_select){
    if(clb.b_tpc_xy[2] && clb.b_tpc_xy[3]){//tpc2324
      tgt.id_x2 = clb.tpc_x_s2_foc_23_24;
      tgt.id_y2 = clb.tpc_y_s2_foc_23_24;
      tgt.id_a2 = clb.tpc_angle_x_s2_foc_23_24;
      tgt.id_b2 = clb.tpc_angle_y_s2_foc_23_24;
    }else if (clb.b_tpc_xy[1] && clb.b_tpc_xy[3]){//tpc2224
      tgt.id_x2 = clb.tpc_x_s2_foc_22_24;
      tgt.id_y2 = clb.tpc_y_s2_foc_22_24;
      tgt.id_a2 = clb.tpc_angle_x_s2_foc_22_24;
      tgt.id_b2 = clb.tpc_angle_y_s2_foc_22_24;
    }else if (clb.b_tpc_xy[0] && clb.b_tpc_xy[1]){//tpc2122
      tgt.id_x2 = clb.tpc_x_s2_foc_21_22;
      tgt.id_y2 = clb.tpc_y_s2_foc_21_22;
    tgt.id_a2 = clb.tpc_angle_x_s2_foc_21_22;
    tgt.id_b2 = clb.tpc_angle_y_s2_foc_21_22;
    }
  }else if (2 == id->x_s2_select){
    if (tgt.sci_b_x[2]){//sc21
      tgt.id_x2 = tgt.sci_x[2];
      tgt.id_y2 = 0.0;
      tgt.id_a2 = 0.0;
      tgt.id_b2 = 0.0;
    }
  }else if(3 == id->x_s2_select){
    if (tgt.sci_b_x[3]){//sc22
      tgt.id_x2 = tgt.sci_x[3];
      tgt.id_y2 = 0.0;
      tgt.id_a2 = 0.0;
      tgt.id_b2 = 0.0;
    }
  }

  // S4 only 1 possibility =  TPC4142
  if(clb.b_tpc_xy[4] && clb.b_tpc_xy[5]){
    tgt.id_x4 = clb.tpc_x_s4;
    tgt.id_a4 = clb.tpc_angle_x_s4;
    tgt.id_y4 = clb.tpc_y_s4;
    tgt.id_b4 = clb.tpc_angle_y_s4;
  }

  // S8 only 1 possibility =  SC81x
  if( tgt.sci_b_x[10]){
    tgt.id_x8 = tgt.sci_x[10];
    tgt.id_a8 = 0.0;
    tgt.id_y8 = 0.0;
    tgt.id_b8 = 0.0;
  }

  /*  check that the positions are OK   */
  tgt.id_b_x2 = cID_x2->Test(tgt.id_x2);
  tgt.id_b_x4 = cID_x4->Test(tgt.id_x4);
  tgt.id_b_x8 = cID_x8->Test(tgt.id_x8);

  // remove temporarily
  // hID_E_Xs4->Fill(tgt.id_x4,tgt.de[0]);// added by 2016Jun.16
  // hID_E_Xs2->Fill(tgt.id_x2,tgt.de[0]);// added by 2016Jun.16

  /*----------------------------------------------------------*/
  /* Determination of beta                                    */
  /* ID.TofOff(i)                   Flight time offset [ps]   */
  /* ID.Path(i)                     Flight path/c [ps]        */
  /* TOF(i)        BIN FLOAT(24),   Flight time  [ps]         */
  /*----------------------------------------------------------*/

  //SC21-SC41
  if(1 == id->tof_s4_select){ //SC21-SC41
    if (tgt.sci_b_tofll2 && tgt.sci_b_tofrr2){
      //// tgt.id_beta = id->id_path2 /(id->id_tofoff2 - tgt.sci_tof2);
      tgt.id_beta = id->id_path2 /  tgt.sci_tof2_calib ;// calculate non-inverted "real" tof already in sci analysis.
      if(bDrawHist){
	hID_beta->Fill(tgt.id_beta*1000.);
      }
    }
  }else if(2 == id->tof_s4_select){ //SC21-SC42
    if (tgt.sci_b_tofll3 && tgt.sci_b_tofrr3){
      tgt.id_beta = id->id_path3 /  tgt.sci_tof3_calib ;// calculate non-inverted "real" tof already in sci analysis.
      if(bDrawHist){
	hID_beta->Fill(tgt.id_beta*1000.);
      }
    }
  }else if(3 == id->tof_s4_select){ //SC22-SC41
    if (tgt.sci_b_tofll5 && tgt.sci_b_tofrr5){
      tgt.id_beta = id->id_path5 /  tgt.sci_tof5_calib ;// calculate non-inverted "real" tof already in sci analysis.
      if(bDrawHist){
	hID_beta->Fill(tgt.id_beta*1000.);
      }
    }
  }

  //S8 TOF
  if(1 == id->tof_s8_select){ //SC21-SC81
    if (tgt.sci_b_tofll4 && tgt.sci_b_tofrr4){
      tgt.id_beta_s2s8 = id->id_path4 /  tgt.sci_tof4_calib ;// calculate non-inverted "real" tof already in sci analysis.
      if(bDrawHist){
	hID_beta_s2s8->Fill(tgt.id_beta_s2s8*1000.);
      }
    }
  }else if(2 == id->tof_s8_select){ //SC22-SC81
    if (tgt.sci_b_tofll6 && tgt.sci_b_tofrr6){
      tgt.id_beta_s2s8 = id->id_path6 /  tgt.sci_tof6_calib ;// calculate non-inverted "real" tof already in sci analysis.
      if(bDrawHist){
	hID_beta_s2s8->Fill(tgt.id_beta_s2s8*1000.);
      }
    }
  }


  // /*------------------------------------------------------*/
  // /* Determination of Brho                                */
  // /* Dispersion and magnification are still the same      */
  // /* variable for S41-S21 and S42-S41, adjust in setup.C  */
  // /*------------------------------------------------------*/

  // first half of FRS, TA-S2
  if (tgt.id_b_x2){
      tgt.id_rho[0]  = frs->rho0[0] * (1. - tgt.id_x2/1000./frs->dispersion[0]);
      tgt.id_brho[0] = (fabs(frs->bfield[0]) + fabs(frs->bfield[1]))/ 2. * tgt.id_rho[0];
      if(bDrawHist){  hID_BRho[0]->Fill(tgt.id_brho[0]); }
  }
  // second half S2-S4
  if (tgt.id_b_x2 && tgt.id_b_x4){      
      tgt.id_rho[1] = frs->rho0[1] * (1. - (tgt.id_x4 - frs->magnification[1] * tgt.id_x2) / 1000. / frs->dispersion[1]) ;
      tgt.id_brho[1] = (fabs(frs->bfield[2]) + fabs(frs->bfield[3]))/ 2. * tgt.id_rho[1];
      if(bDrawHist){  hID_BRho[1]->Fill(tgt.id_brho[1]); }
  }

   // to Cave-C S2-S8
  if (tgt.id_b_x2 && tgt.id_b_x8){
      tgt.id_rho[2] = frs->rho0[2] * (1. - (tgt.id_x8 - id->pos_offset_sc81x - frs->magnification[2] * tgt.id_x2) / 1000. / frs->dispersion[2]) ;
      tgt.id_brho[2] = (fabs(frs->bfield[2]) + fabs(frs->bfield[5]))/ 2. * tgt.id_rho[2];
      if(bDrawHist){  hID_BRho[2]->Fill(tgt.id_brho[2]); }
  }
  // sc81x = 0 (deterined by slit) may not aggree with the optical reference.
  // for example, sc81x = 0 is adjusted by slit.
  // but tof calibration  was performed or good transmission was obtained with sc81x = 7 mm.
  // then x=7mm should correspond to delta_p = 0.
  // this does not happen at s2 and s4
  // this is why the additional parameter (id->pos_offset_sc81x) is prepared for s8 here.
  

  /*--------------------------------------------------------------*/
  /* Determination of A/Q                                         */
  /*--------------------------------------------------------------*/
  /* Beta(i)       BIN FLOAT(24),   Beta = v/c                    */
  /* Gamma(i)      BIN FLOAT(24),   Gamma= sqrt(1/1-beta**2)      */
  /*--------------------------------------------------------------*/
  Float_t f = 931.4940 / 299.792458 ;    /* factor needed for aoq calculation.. the u/(c*10^-6) factor  */


  
  /* for S2-S4 */
  if (tgt.sci_b_tofll2 && tgt.sci_b_tofrr2 && tgt.id_b_x2 && tgt.id_b_x4){
      if ((tgt.id_beta>0.0) && (tgt.id_beta<1.0)){
  	  tgt.id_gamma = 1./sqrt(1. - tgt.id_beta * tgt.id_beta);
  	  tgt.id_AoQ   = tgt.id_brho[1]/tgt.id_beta/tgt.id_gamma/ f ;
  	  tgt.id_AoQ_corr = tgt.id_AoQ - id->a2AoQCorr * tgt.id_a2;  //correction for id_a2, JK 16.9.11
  	  // if (!clb.b_tpc_xy[4] || !clb.b_tpc_xy[5]) // no sense to do "if TPC4142 dont work, correct with S4 angle ... "
  	  //   tgt.id_AoQ_corr = tgt.id_AoQ - id->a4AoQCorr * tgt.id_a4;
	  //std::cout<< "brho, beta, aoq"<< tgt.id_brho[1] << "   " << tgt.id_beta << "   "  << 	  tgt.id_AoQ << std::endl;
	   if(bDrawHist)
  	    {
  	      hID_AoQ->Fill(tgt.id_AoQ);
  	      hID_AoQcorr->Fill(tgt.id_AoQ_corr);
	      hID_DeltaBrho_AoQ->Fill(tgt.id_AoQ,tgt.id_brho[0]-tgt.id_brho[1]);
  	    }
  	  tgt.id_b_AoQ = kTRUE;
      }
  }

  /* for S2-S8  */
  bool check_b_tof = false;
  if(1 == id->tof_s8_select){ //SC21-SC81
    check_b_tof = tgt.sci_b_tofll4 && tgt.sci_b_tofrr4;
  }else if(2== id->tof_s8_select){ //SC22-SC81
    check_b_tof = tgt.sci_b_tofll6 && tgt.sci_b_tofrr6;
  }
    
  if (check_b_tof && tgt.id_b_x2 && tgt.id_b_x8){
    if ((tgt.id_beta_s2s8>0.0) && (tgt.id_beta_s2s8<1.0)){
      tgt.id_gamma_s2s8 = 1./sqrt(1. - tgt.id_beta_s2s8 * tgt.id_beta_s2s8);
      tgt.id_AoQ_s2s8      = tgt.id_brho[2]/tgt.id_beta_s2s8/tgt.id_gamma_s2s8/ f ;
      if(bDrawHist)
	{
	  hID_AoQ_s2s8->Fill(tgt.id_AoQ_s2s8);
	}
      tgt.id_b_AoQ_s2s8 = kTRUE;
    }
  }
//printf("AAA %f tgt.sci_e[10] , %f tgt.id_beta_s2s8\n",tgt.sci_e[10], tgt.id_beta_s2s8);

  /*------------------------------------------------*/
  /* Determination of Z                             */
  /*------------------------------------------------*/
  /****  S4  (MUSIC 1)   */
  //  if((tgt.de_cor[0]>0.0) && (tgt.id_beta>0.0) && (tgt.id_beta<1.0)) {

  if((tgt.de[0]>0.0) && (tgt.id_beta>0.0) && (tgt.id_beta<1.0))
    {
      Double_t power = 1., sum = 0.;
      for (int i=0;i<4;i++){
  	  sum += power * id->vel_a[i];
  	  power *= tgt.id_beta;
      }
      tgt.id_v_cor = sum;
      if (tgt.id_v_cor > 0.0){
  	tgt.id_z = frs->primary_z * sqrt(tgt.de[0]/tgt.id_v_cor) + id->offset_z;
      }
      if ((tgt.id_z>0.0) && (tgt.id_z<100.0)){
	tgt.id_b_z = kTRUE;
      }
    }


  /****  S4  (MUSIC 2)   */
  if((tgt.de[1]>0.0) && (tgt.id_beta>0.0) && (tgt.id_beta<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++)
      {
	sum += power * id->vel_a2[i];
	power *= tgt.id_beta;
      }
    tgt.id_v_cor2 = sum;

    if (tgt.id_v_cor2 > 0.0){
      tgt.id_z2 = frs->primary_z * sqrt(tgt.de[1]/tgt.id_v_cor2) + id->offset_z2;
    }
    if ((tgt.id_z2>0.0) && (tgt.id_z2<100.0)){
      tgt.id_b_z2 = kTRUE;
    }
  }


  /****  S4  (MUSIC)   */
  if((tgt.de[2]>0.0) && (tgt.id_beta>0.0) && (tgt.id_beta<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->vel_a3[i];
      power *= tgt.id_beta;
    }
    tgt.id_v_cor3 = sum;
    if (tgt.id_v_cor3 > 0.0){
      tgt.id_z3 = frs->primary_z * sqrt(tgt.de[2]/tgt.id_v_cor3) + id->offset_z3;
    }

    if ((tgt.id_z3>0.0) && (tgt.id_z3<100.0)){
      tgt.id_b_z3 = kTRUE;
    }
  }

  /// plot Z1,Z2,Z3 ...
  if(bDrawHist){
    if(tgt.id_b_z){  hID_Z1->Fill(tgt.id_z);}
    if(tgt.id_b_z2){ hID_Z2->Fill(tgt.id_z2);}
    if(tgt.id_b_z3){ hID_Z3->Fill(tgt.id_z3);}
    if(tgt.id_b_z && tgt.id_b_z2){ hID_Z1_Z2->Fill(tgt.id_z,tgt.id_z2);}
    if(tgt.id_b_z && tgt.id_b_z3){ hID_Z1_Z3->Fill(tgt.id_z,tgt.id_z3);}
    if(tgt.id_b_z2 && tgt.id_b_z3){ hID_Z2_Z3->Fill(tgt.id_z2,tgt.id_z3);}
  }


  //printf("%f tgt.sci_e[10] , %f tgt.id_beta_s2s8\n",tgt.sci_e[10], tgt.id_beta_s2s8);

  //Z from sc81
  if((tgt.sci_e[10]>0.0) && (tgt.id_beta_s2s8>0.0) && (tgt.id_beta_s2s8<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->vel_a_sc81[i];
      power *= tgt.id_beta_s2s8;
    }
    tgt.id_v_cor_sc81 = sum;
    //printf("%f tgt.id_v_cor_sc81\n",tgt.id_v_cor_sc81);
    if (tgt.id_v_cor_sc81 > 0.0){
      tgt.id_z_sc81 = frs->primary_z * sqrt(tgt.sci_e[10]/tgt.id_v_cor_sc81) + id->offset_z_sc81;
    }

    if ((tgt.id_z_sc81>0.0) && (tgt.id_z_sc81<100.0)){
      tgt.id_b_z_sc81 = kTRUE;
    }
  }

  //Z from tpc21222324
  double temp_s2tpc_de=1.0; int temp_s2tpc_de_count=0;
  for(int ii=0; ii<4; ii++){
    if(clb.b_tpc_de[ii]){
      temp_s2tpc_de *=clb.tpc_de[ii]; temp_s2tpc_de_count++;
    }
  }
  if(temp_s2tpc_de_count == 2){
    tgt.id_de_s2tpc = pow(temp_s2tpc_de, 1./temp_s2tpc_de_count);
    tgt.id_b_de_s2tpc = kTRUE;
  }

  if(tgt.id_b_de_s2tpc && (tgt.id_beta_s2s8>0.0) && (tgt.id_beta_s2s8<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->vel_a_s2tpc[i];
      power *= tgt.id_beta_s2s8;
    }
    tgt.id_v_cor_s2tpc = sum;
    if (tgt.id_v_cor_s2tpc > 0.0){
      tgt.id_z_s2tpc = frs->primary_z * sqrt( tgt.id_de_s2tpc/tgt.id_v_cor_s2tpc ) + id->offset_z_s2tpc;
      //printf("tgt.id_de_s2tpc = %f, v_cor = %f, z_s2tpc = %f\n",tgt.id_de_s2tpc, tgt.id_v_cor_s2tpc, tgt.id_z_s2tpc);
    }

    if ((tgt.id_z_s2tpc>0.0) && (tgt.id_z_s2tpc<100.0)){
      tgt.id_b_z_s2tpc = kTRUE;
    }
  }



  //     static const double anode_width = 10.;//cm
  //     double music_dX = anode_width*sqrt(tgt.id_a4*tgt.id_a4+tgt.id_b4*tgt.id_b4+1.);
  //     h_dEdx_betagammaAll->Fill(tgt.id_beta*tgt.id_gamma,tgt.de[2]/music_dX);
  //     h_dEdx_betagammaAllZoom->Fill(tgt.id_beta*tgt.id_gamma,tgt.de[2]/music_dX);
  //     //double music_dEtemp0 = srt.music_e3[0]*music->e3_gain[0] + music->e3_off[0];
  //     //for(int i=0;i<8;++i)
  // 	//{
  // 	  //double music_dEtemp = srt.music_e3[i]*music->e3_gain[i] + music->e3_off[i];
  // 	  //h_dEdx_betagamma[i]->Fill(tgt.id_beta*tgt.id_gamma,music_dEtemp/music_dX);
  // 	  //if(i>0)
  // 	    //h_DiffdEdx_betagamma[i]->Fill(tgt.id_beta*tgt.id_gamma,(music_dEtemp-music_dEtemp0)/music_dX);
  // 	//}
  //   }

   /*------------------------------------------------*/
   /* Identification Plots                           */
   /*------------------------------------------------*/

   /****  for S2-S4  ****/

   if(tgt.id_b_AoQ)
     {
       if(bDrawHist)
   	{
   	  hID_x2AoQ->Fill(tgt.id_AoQ, tgt.id_x2);
   	  hID_x4AoQ->Fill(tgt.id_AoQ, tgt.id_x4);
	  hID_Z1_AoQ->Fill(tgt.id_AoQ, tgt.id_z);
	  hID_Z1_AoQcorr->Fill(tgt.id_AoQ_corr, tgt.id_z);
	  hID_Z2_AoQ->Fill(tgt.id_AoQ, tgt.id_z2);
	  hID_Z2_AoQcorr->Fill(tgt.id_AoQ_corr, tgt.id_z2);
   	  // hID_Z3_AoQ->Fill(tgt.id_AoQ, tgt.id_z3);
   	  hID_x2x4->Fill(tgt.id_x2,tgt.id_x4);
   	  //hID_SC41dE_AoQ->Fill(tgt.id_AoQ, tgt.sci_e[5]);
	  if(tgt.id_b_z && tgt.id_b_z2 && fabs(tgt.id_z2-tgt.id_z)<0.4){
	    hID_Z1_AoQ_zsame->Fill(tgt.id_AoQ, tgt.id_z);
	  }
  	}
     }

   if(bDrawHist){
     if(tgt.id_b_z){
       hID_x4z ->Fill(tgt.id_z, tgt.id_x4);
       hID_x2z ->Fill(tgt.id_z, tgt.id_x2);
       hID_Z1_Sc21E->Fill(tgt.id_z, sqrt(tgt.sci_l[2]*tgt.sci_r[2]));
     }
   }

   for (int i=0;i<5;i++){
     tgt.id_b_x4AoQ[i] = cID_x4AoQ[i]->Test(tgt.id_AoQ, tgt.id_x4);
     tgt.id_b_x2AoQ[i] = cID_x2AoQ[i]->Test(tgt.id_AoQ, tgt.id_x2);
     tgt.id_b_z_AoQ[i] = cID_Z1_AoQ[i]->Test(tgt.id_AoQ, tgt.id_z);
   }

   /// plot S8 related histograms.
   if(bDrawHist){
     //Brho[2],  hID_beta_s2s8,  hID_AoQ_s2s8   were already filled.
     if(tgt.id_b_z_sc81){ hID_Z_sc81->Fill(tgt.id_z_sc81); }
     if(tgt.id_b_de_s2tpc){ hID_dE_s2tpc->Fill(tgt.id_de_s2tpc); }
     if(tgt.id_b_z_s2tpc){ hID_Z_s2tpc->Fill(tgt.id_z_s2tpc); }
     if(tgt.id_b_z_sc81 && tgt.id_b_AoQ_s2s8){  hID_Z_sc81_AoQ_s2s8->Fill(tgt.id_AoQ_s2s8, tgt.id_z_sc81); }
     if(tgt.id_b_z_s2tpc && tgt.id_b_AoQ_s2s8){  hID_Z_s2tpc_AoQ_s2s8->Fill(tgt.id_AoQ_s2s8, tgt.id_z_s2tpc); }
     if(tgt.id_b_de_s2tpc && tgt.id_b_AoQ_s2s8){  hID_dE_s2tpc_AoQ_s2s8->Fill(tgt.id_AoQ_s2s8, tgt.id_de_s2tpc); }
     if(tgt.sci_e[10]>0.0 && tgt.id_b_AoQ_s2s8){  hID_dE_sc81_AoQ_s2s8->Fill(tgt.id_AoQ_s2s8, tgt.sci_e[10]); }
   }
   return ;
}


void TFRSAnlProc::Process_MRTOF_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt)
{

  if(srt.EventFlag==0x200 && srt.trigger==1)
    {
      tgt.mrtof_start = srt.mrtof_start*25./1000000.; // ch to microsec

      double tempStop1 = srt.mrtof_stopDelay*25./1000000. ;
      double tempStop2 = srt.mrtof_stop*25./1000000. ;

      h_MRtof_Start->Fill(tgt.mrtof_start);
      h_MRtof_StopDelay->Fill(tempStop1);
      h_MRtof_Stop->Fill(tempStop2);

      int stop_status=0;

      if(tempStop1<=0.)
	{
	  if(tempStop2>0.)
	    {
	      tgt.mrtof_stop  = tempStop2;
	      h_MRtof_status->Fill("GoodStop2",1);
	      stop_status=1;
	    }
	  else
	    {
	      tgt.mrtof_stop = -9999.;
	      //std::cout<<"E> MRTOF Anal : both stop signal "<<
	      if(tgt.mrtof_start>1)
		h_MRtof_status->Fill("NoGoodStop",1);
	      else
		h_MRtof_status->Fill("NoData",1);
	    }
	}
      else
	{
	  if(tempStop2<=0.)
	    {
	      tgt.mrtof_stop = tempStop1-45.;
	      h_MRtof_status->Fill("GoodStop1",1);
	      stop_status=1;
	    }
	  else
	    {
	      double diff_stop = tempStop1-tempStop2;
	      if(TMath::Abs(diff_stop-45)<1.)
		{
		  tgt.mrtof_stop = tempStop1-45.;
		  h_MRtof_status->Fill("GoodStop1&2",1);
		  stop_status=1;
		}
	      else
		{
		  h_MRtof_status->Fill("Stop1&2BadOverlap",1);
		  std::cout<<"E> MRtof diff stop too big from 45 microsec !"<<diff_stop<< "sorted : D="<<srt.mrtof_stopDelay <<" "<< srt.mrtof_stop <<" | in microsec: D="<< tempStop1 <<" "<<tempStop2<<"\n";
		}
	    }
	}

      //int diff_stopdelay = 1891482-54830;

      if(stop_status==1)
	{
	  tgt.mrtof_tof = 100 - ( tgt.mrtof_start - tgt.mrtof_stop); // add 100 microsec from mrtof trigger system
	  h_MRtof_tof->Fill(tgt.mrtof_tof);
	  h_MRtof_status->Fill("GoodTOF",1);
	}
      else
	h_MRtof_status->Fill("BadTOF",1);


    }

  tgt.mrtof_si_e1=clb.si_e1;
  tgt.mrtof_si_e2=clb.si_e2;
  tgt.mrtof_si_e3=clb.si_e3;
  tgt.mrtof_si_e4=clb.si_e4;
  tgt.mrtof_si_e5=clb.si_e5;

}

ClassImp(TFRSAnlProc)
