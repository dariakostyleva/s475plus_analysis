#ifndef TFRSANLPROC_H
#define TFRSANLPROC_H

#include "TFRSBasicProc.h"
#include "TFRSParameter.h"
#include <TRandom3.h>

class TFRSAnlEvent;
class TFRSSortEvent;
class TFRSCalibrEvent;

class TFRSUnpackEvent;

class TFRSAnlProc : public TFRSBasicProc {
public:
  TFRSAnlProc();
  TFRSAnlProc(const char* name);
  //void FRSEventAnalysis(TFRSAnlEvent* target);
  Bool_t BuildEvent(TGo4EventElement* output);

  virtual ~TFRSAnlProc() ;

  Bool_t bDrawHist;

private:
  void Create_MUSIC_Hist();
  void Create_SCI_Hist();
  void Create_MultiHitTDC_Hist();
  void Create_ID_Hist();
  void Create_MRTOF_Hist();
  void Create_Gated_Hist();
  // void Create_SI_Hist();
  // void Create_CT_Hist();

  void Process_MUSIC_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt);
  void Process_SCI_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt);
  void Process_ID_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent&  clb, TFRSAnlEvent& tgt);
  void Process_MRTOF_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt);
  void Process_MultiHitTDC_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt);
  void Process_ID_MultiHitTDC_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt);
    void Process_Gated_Analysis(TFRSSortEvent& srt, TFRSCalibrEvent& clb, TFRSAnlEvent& tgt);
  TMUSICParameter* music;
  TSCIParameter* sci;
  TFRSParameter* frs;
  TIDParameter* id;
  TMRTOFMSParameter* mrtof;

  //MRTOF data

  TH1F* h_MRtof_Start;
  TH1F* h_MRtof_StopDelay;
  TH1F* h_MRtof_Stop;
  TH1F* h_MRtof_tof;
  TH1F* h_MRtof_status;


  // MUSIC data
  TH1I          *hMUSIC1_E[8];
  TH1I          *hMUSIC1_T[8];
  TH1I          *hMUSIC1_dE;
  TH2I          *hMUSIC1_dE_x;
  TH1I          *hMUSIC1_dECOR;
  TH2I          *hMUSIC1_dECOR_x;

  TH1I          *hMUSIC2_E[8];
  TH1I          *hMUSIC2_T[8];
  TH1I          *hMUSIC2_dE;
  TH2I          *hMUSIC2_dE_x;
  TH1I          *hMUSIC2_dECOR;
  TH2I          *hMUSIC2_dECOR_x;

  TH1I          *hMUSIC3_E[8];
  TH1I          *hMUSIC3_T[8];
  TH1I          *hMUSIC3_dE;
  TH2I          *hMUSIC3_dE_x;
  TH1I          *hMUSIC3_dECOR;
  TH2I          *hMUSIC3_dECOR_x;
  //  TH1I          *hMUSIC3_E_s4gate_Z_AoQ[8][5]; //for range scan

  // correlation between MUSICs
  TH2I          *hMUSIC_dE1dE2;
  TH2I          *hMUSIC_dE1dE3;
  TH2I          *hMUSIC_dE2dE3;

  TGo4WinCond   *cMusic1_E[8];
  TGo4WinCond   *cMusic1_T[8];
  TGo4WinCond   *cMusic2_E[8];
  TGo4WinCond   *cMusic2_T[8];
  TGo4WinCond   *cMusic3_T[8];
  TGo4WinCond   *cMusic3_E[8];


  // Multi-hit TDC SCI timing
  TH1I *hMultiHitTDC_21l_21r;
  TH1I *hMultiHitTDC_41l_41r;
  TH1I *hMultiHitTDC_42l_42r;
  TH1I *hMultiHitTDC_43l_43r;
  TH1I *hMultiHitTDC_31l_31r;
  TH1I *hMultiHitTDC_81l_81r;

  TH2I *hMultiHitTDC_21l_21r_TPCX;
  TH2I *hMultiHitTDC_41l_41r_TPCX;
  TH2I *hMultiHitTDC_42l_42r_TPCX;
  TH2I *hMultiHitTDC_43l_43r_TPCX;
  TH2I *hMultiHitTDC_31l_31r_TPCX;
  //  TH2I *hMultiHitTDC_81l_81r_TPCX;

  TH1I *hMultiHitTDC_SC21X;
  TH1I *hMultiHitTDC_SC41X;
  TH1I *hMultiHitTDC_SC42X;
  TH1I *hMultiHitTDC_SC43X;
  TH1I *hMultiHitTDC_SC31X;
  TH1I *hMultiHitTDC_SC81X;

  TH2I *hMultiHitTDC_SC21X_TPCX;
  TH2I *hMultiHitTDC_SC41X_TPCX;
  TH2I *hMultiHitTDC_SC42X_TPCX;
  TH2I *hMultiHitTDC_SC43X_TPCX;
  TH2I *hMultiHitTDC_SC31X_TPCX;
  //  TH2I *hMultiHitTDC_81l_81r_TPCX;

  TH1I *hMultiHitTDC_TOF_41_21;
  TH1I *hMultiHitTDC_TOF_42_21;
  TH1I *hMultiHitTDC_TOF_43_21;
  TH1I *hMultiHitTDC_TOF_31_21;
  TH1I *hMultiHitTDC_TOF_81_21;

  TH1I *hMultiHitTDC_BETA_41_21;
  TH1I *hMultiHitTDC_BETA_42_21;
  TH1I *hMultiHitTDC_BETA_43_21;
  TH1I *hMultiHitTDC_BETA_31_21;
  TH1I *hMultiHitTDC_BETA_81_21;

  TH1I *hID_MHTDCS2S8_DELTA;
  TH1I *hID_MHTDCS2S8_BETA;
  TH1I *hID_MHTDCS2S8_AOQ; 
  TH2I *hID_MHTDCS2S8_DELTA_BETA;
  TH2I *hID_MHTDCS2S8_AOQ_BETA;
  TH1I *hID_MHTDCS2S8_dES2TPC  ;  
  TH2I *hID_MHTDCS2S8_dES2TPC_BETA;
  TH2I *hID_MHTDCS2S8_dES2TPC_AOQ ;
  TH1I *hID_MHTDCS2S8_ZS2TPC    ; 
  TH2I *hID_MHTDCS2S8_ZS2TPC_AOQ ;
  TH2I *hID_MHTDCS2S8_dESC81_BETA;
  TH2I *hID_MHTDCS2S8_dESC81_AOQ;
  TH1I *hID_MHTDCS2S8_ZSC81     ;
  TH2I *hID_MHTDCS2S8_ZSC81_AOQ ;

  TH1I *hID_MHTDCS2S4_DELTA; 
  TH1I *hID_MHTDCS2S4_BETA; 
  TH1I *hID_MHTDCS2S4_AOQ;
  TH2I *hID_MHTDCS2S4_DELTA_BETA;
  TH2I *hID_MHTDCS2S4_AOQ_BETA;
  TH2I *hID_MHTDCS2S4_dE41_BETA;
  TH2I *hID_MHTDCS2S4_dE41_AOQ;
  TH1I *hID_MHTDCS2S4_Z41;
  TH2I *hID_MHTDCS2S4_Z41_AOQ ;
  TH2I *hID_MHTDCS2S4_dE42_BETA;
  TH2I *hID_MHTDCS2S4_dE42_AOQ ;
  TH1I *hID_MHTDCS2S4_Z42;
  TH2I *hID_MHTDCS2S4_Z42_AOQ;
  
  // SCI data
  TH1I          *hSCI_L[15];
  TH1I          *hSCI_R[15];
  TH1I          *hSCI_E[15];
  TH1I          *hSCI_Tx[15];
  TH1I          *hSCI_X[15];
  TH2I          *hSCI_Tx_XTPC[15];
  TH2I          *hSCI_X_XTPC[15];

  TH1I          *hSCI_TofLL2;
  TH1I          *hSCI_TofRR2;
  TH1I          *hSCI_Tof2;
  TH1I          *hSCI_Tof2calib;

  TH1I          *hSCI_TofLL3;
  TH1I          *hSCI_TofRR3;
  TH1I          *hSCI_Tof3;
  TH1I          *hSCI_Tof3calib;

  TH1I          *hSCI_TofLL4;
  TH1I          *hSCI_TofRR4;
  TH1I          *hSCI_Tof4;
  TH1I          *hSCI_Tof4calib;

  TH1I          *hSCI_TofLL5;
  TH1I          *hSCI_TofRR5;
  TH1I          *hSCI_Tof5;
  TH1I          *hSCI_Tof5calib;

  TH1I          *hSCI_TofLL6;
  TH1I          *hSCI_TofRR6;
  TH1I          *hSCI_Tof6;
  TH1I          *hSCI_Tof6calib;

  TH2I          *hSCI_dETof2;
  TH2I          *hSCI_dETof3;
  TH2I          *hSCI_dETof4;
  TH2I          *hSCI_dETof5;
  TH2I          *hSCI_dETof6;

  TGo4WinCond   *cSCI_L[12];
  TGo4WinCond   *cSCI_R[12];
  TGo4WinCond   *cSCI_E[12];
  TGo4WinCond   *cSCI_Tx[12];
  TGo4WinCond   *cSCI_X[12];

  TGo4WinCond   *cSCI_TofLL2;
  TGo4WinCond   *cSCI_TofRR2;
  TGo4WinCond   *cSCI_TofLL3;
  TGo4WinCond   *cSCI_TofRR3;
  TGo4WinCond   *cSCI_TofLL4;
  TGo4WinCond   *cSCI_TofRR4;
  TGo4WinCond   *cSCI_TofLL5;
  TGo4WinCond   *cSCI_TofRR5;
  TGo4WinCond   *cSCI_TofLL6;
  TGo4WinCond   *cSCI_TofRR6;

  /* TH2I          *hSCI_dE24; */
  /* TH2I          *hSCI_dEx2; */
  /* TH2I          *hSCI_dEx2del; */
  /* TH2I          *hSCI_dEx5; */
  /* TGo4PolyCond  *cSCI_detof;  */


  // ID data

  // ID_S4
  TH1I          *hID_BRho[3]; // 0: TA-S2, 1: S2-S4, 2: S2-S8
  TH1I          *hID_beta;    // S2S4
  TH2I          *hID_dEToF;
  TH1I          *hID_AoQ;
  TH1I          *hID_AoQcorr;
  TH1I          *hID_Z1;
  TH1I          *hID_Z2;
  TH1I          *hID_Z3;
  TH2I          *hID_DeltaBrho_AoQ;
  TH2I          *hID_x2AoQ;
  TH2I          *hID_Z1_AoQ;
  TH2I		*hID_Z1_AoQ_zsame;
  TH2I          *hID_Z1_AoQcorr;
  TH2I          *hID_x2x4;
  TH2I          *hID_Z2_AoQ;
  TH2I          *hID_Z2_AoQcorr;
  TH2I          *hID_Z1_Z2;
  TH2I          *hID_Z1_Z3;
  TH2I          *hID_Z2_Z3;
  TH2I          *hID_x4AoQ;
  TH2I          *hID_x2z;
  TH2I          *hID_x4z;
  TH2I          *hID_Z1_Sc21E;

  // ID_S8
  TH1I *hID_tof_s2s8;
  TH1I *hID_beta_s2s8;
  TH1I *hID_dE_sc81; // z from sc81
  TH1I *hID_Z_sc81; // z from sc81
  TH1I *hID_dE_s2tpc; // z from tpc21222324
  TH1I *hID_Z_s2tpc; // z from tpc21222324
  TH1I *hID_AoQ_s2s8; //
  TH2I *hID_Z_sc81_AoQ_s2s8;
  TH2I *hID_Z_s2tpc_AoQ_s2s8;
  TH2I *hID_dE_s2tpc_AoQ_s2s8;
  TH2I *hID_dE_sc81_AoQ_s2s8;
  
  // Gated Histograms
  TH1I *hTPC_X_gate[7][15];
  TH1I *hTPC_Y_gate[7][15];
  TH1I *hTPC_S2X_gate[15];
  TH1I *hTPC_S2Y_gate[15];
  TH1I *hTPC_S2A_gate[15];
  TH1I *hTPC_S2B_gate[15];
  TH1I *hTPC_S4X_gate[15];
  TH1I *hTPC_S4Y_gate[15];
  TH1I *hTPC_S4A_gate[15];
  TH1I *hTPC_S4B_gate[15];
  TH1I *hTPC_S2TargetX_gate[15];
  TH1I *hTPC_S2TargetY_gate[15];
  TH1I *hTPC_S4TargetX_gate[15];
  TH1I *hTPC_S4TargetY_gate[15];
  TH1I *hMUSIC1_E_gate[8][15];
  TH1I *hMUSIC2_E_gate[8][15];
  TH1I *hMUSIC3_E_gate[8][15];

  TGo4WinCond   *cID_x2;
  TGo4WinCond   *cID_x4;
  TGo4WinCond   *cID_x8;
  TGo4PolyCond  *cID_dEToF;
  TGo4PolyCond  *cID_x2AoQ[5];
  TGo4PolyCond  *cID_Z1_AoQ[5];
  TGo4PolyCond  *cID_x4AoQ[5];

  Float_t rand3(void);
  TRandom3 random3;

  ClassDef(TFRSAnlProc,1)
};

#endif //--------------- TFRSANLPROC_H
