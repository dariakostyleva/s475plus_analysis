#ifndef TFRSCALIBRPROCESSOR_H
#define TFRSCALIBRPROCESSOR_H

#include "TFRSBasicProc.h"
#include  <iostream>

#include  "TMath.h"
#include  "TRandom3.h"

#include "TFRSCalibrEvent.h"

#include "TFRSParameter.h"

class TFRSCalibrEvent;
class TFRSSortEvent;

class TFRSCalibrProc : public TFRSBasicProc {
public:
  TFRSCalibrProc() ;
  TFRSCalibrProc(const char* name);
  virtual ~TFRSCalibrProc() ;

  // event processing function, default name
  Bool_t BuildEvent(TGo4EventElement* output);
  void InitProcessor();
  Bool_t bDrawHist;

private:
  void Create_Scaler_Hist();
  void Create_MW_Hist();
  void Create_TPC_Hist();
  void Create_SI_Hist();
  void Create_CT_Hist();
  void Create_ElCurrent_Hist();
      
  void Process_Scaler_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt);
  void Process_MW_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt);
  void Process_TPC_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt);
  void Process_SI_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt);
  void Process_CT_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt);
  void Process_ElCurrent_Analysis(const TFRSSortEvent& src, TFRSCalibrEvent& tgt);

  TFRSParameter* frs ;
  TMWParameter* mw ;
  TTPCParameter* tpc;
  TSIParameter* si;
  TMUSICParameter* music;

  //--------Scaler Graphs----------
  TH1I          *hScaler_per_s[64];
  TH1I          *hScaler_per_100ms[64];
  TH1I          *hScaler_per_spill[64];  
  int            scaler_ch_1kHz=0;
  int            scaler_ch_spillstart=0;
  UInt_t         scaler_initial[64];
  UInt_t         scaler_previous[64];
  int            scaler_check_first_event = 1;
  
  //**** Raw spectra
  TH1I          *hMW_AN[13];
  TH1I          *hMW_XL[13];  
  TH1I          *hMW_XR[13];
  TH1I          *hMW_YU[13];
  TH1I          *hMW_YD[13];

  //**** Sum spectra
  TH1I          *hMW_XSUM[13];
  TH1I          *hMW_YSUM[13];
      
  //**** Position spectra
  TH1I          *hMW_X[13];   
  TH1I          *hMW_Y[13];
      
  TH2I          *hMW_XY[13];
      
  TH1I          *hMW_SC21x;
  TH1I          *hMW_SC22x;
  TH1I          *hitag_stopper_x;
  TH1I          *hMW_MUSICx;
 
  TH2I          *hMW21x_Time;
      
      
  //**** Focal spectra S2
  TH1I          *hMW_xAngS2;  
  TH1I          *hMW_yAngS2;
  TH1I          *hMW_xFocS2;
  TH1I          *hMW_yFocS2;
  TH1I          *hMW_zxS2;
  TH1I          *hMW_zyS2;
  TH2I          *hMW_FocS2;
 
      
  TGo4WinCond   *cMW_XSUM[13];
  TGo4WinCond   *cMW_YSUM[13];
      

  // TPC part
  // rawdata
  TH1I *hTPC_L0[7];
  TH1I *hTPC_R0[7];
  TH1I *hTPC_LT0[7];
  TH1I *hTPC_RT0[7];
  TH1I *hTPC_L1[7];
  TH1I *hTPC_R1[7];
  TH1I *hTPC_LT1[7];
  TH1I *hTPC_RT1[7];
  TH1I *hTPC_DT[7][4];// [index][anode_no]
  TH1I *hTPC_A[7][4];
  
  

  /// positions and control sum
  TH1I *hTPC_XRAW0[7];
  TH1I *hTPC_XRAW1[7];
  TH1I *hTPC_YRAW[7];
  TH1I *hTPC_X[7];
  TH1I *hTPC_Y[7];
  TH2I *hTPC_X_extr[7];
  TH2I *hTPC_Y_extr[7];
  TH2I *hcTPC_XY[7];
  TH2I *hTPC_LTRT[7];
  TH1I *hTPC_DELTAX[7];
  TH1I *hTPC_dE[7];
  // CSUM[index][anode_no]
  TH1I *hTPC_CSUM[7][4];

TH1I *hTPC_SC_TIMEREF[8];//last 4 channels in V775 in S4TPC crate 

  
  /* TH1I *hTPC_X_S2;            //Positions @ S2 focus */
  /* TH1I *hTPC_Y_S2; */
  /* TH1I *hTPC_AX_S2;           //Angles @ S2 focus */
  /* TH1I *hTPC_AY_S2; */
  /* TH2I *hTPC_S2X_time; //YT20Jun */
  /* TH2I *hTPC_S2A_time; //YT20Jun */

  // S2 focal plane
  TH1I *hTPC_X_S2_TPC_21_22;  //Positions @ S2 focus using TPCs in Vaccum (TPC21 & TPC22)
  TH1I *hTPC_Y_S2_TPC_21_22;
  TH1I *hTPC_AX_S2_TPC_21_22; //Angles @ S2 focus using TPCs in Vaccum (TPC21 & TPC 22)
  TH1I *hTPC_AY_S2_TPC_21_22;
  TH2I *hTPC_X_AX_S2_TPC_21_22;
  TH2I *hTPC_Y_AY_S2_TPC_21_22;
  TH2I *hTPC_S2X_TPC21_22_time; //SB21Jun
  TH2I *hTPC_S2A_TPC21_22_time; //SB21Jun
  
  TH1I *hTPC_X_S2_TPC_23_24;     //Positions @ S2 focus using TPCs in air (TPC23 & TPC24)
  TH1I *hTPC_Y_S2_TPC_23_24;
  TH1I *hTPC_AX_S2_TPC_23_24;    //Angles @ S2 focus using TPCs in air (TPC23 & TPC24)
  TH1I *hTPC_AY_S2_TPC_23_24;
  TH2I *hTPC_X_AX_S2_TPC_23_24;
  TH2I *hTPC_Y_AY_S2_TPC_23_24;
  TH2I *hTPC_S2X_TPC23_24_time; //SB21Jun
  TH2I *hTPC_S2A_TPC23_24_time; //SB21Jun
  
  TH1I *hTPC_X_S2_TPC_22_24;      //Positions @ S2 focus using TPC22 & TPC24
  TH1I *hTPC_Y_S2_TPC_22_24;
  TH1I *hTPC_AX_S2_TPC_22_24;     //Angles @ S2 focus using TPC22 & TPC24
  TH1I *hTPC_AY_S2_TPC_22_24;
  TH2I *hTPC_X_AX_S2_TPC_22_24;
  TH2I *hTPC_Y_AY_S2_TPC_22_24;
  TH2I *hTPC_S2X_TPC22_24_time; //SB21Jun
  TH2I *hTPC_S2A_TPC22_24_time; //SB21Jun

  // S4 focal plane
  TH1I *hTPC_X_S4;                //Positions @ S4 focus
  TH1I *hTPC_Y_S4;
  TH1I *hTPC_AX_S4;               //Angles @ S4 focus
  TH1I *hTPC_AY_S4;
  TH2I *hTPC_XAX_S4;
  TH2I *hTPC_YAY_S4;
  TH2I *hTPC_S4X_time; //YT20Jun
  TH2I *hTPC_S4A_time; //YT20Jun
  
  // S4X-vs-S2A
  TH2I *hTPC_XS4_AXS2_TPC_21_22;
  TH2I *hTPC_XS4_AXS2_TPC_23_24;
  TH2I *hTPC_XS4_AXS2_TPC_22_24;
  TH2I *hTPC_YS4_AYS2_TPC_21_22;
  TH2I *hTPC_YS4_AYS2_TPC_23_24;
  TH2I *hTPC_YS4_AYS2_TPC_22_24;
  
  /// At_Target and At_Detector
  TH1I *hTPC21_22_SC21x;
  TH1I *hTPC21_22_SC21y;
  TH1I *hTPC23_24_SC21x;
  TH1I *hTPC23_24_SC21y;
  TH1I *hTPC22_24_SC21x;
  TH1I *hTPC22_24_SC21y;
  TH1I *hTPC21_22_SC22x;
  TH1I *hTPC21_22_SC22y;
  TH1I *hTPC23_24_SC22x;
  TH1I *hTPC23_24_SC22y;
  TH1I *hTPC22_24_SC22x;
  TH1I *hTPC22_24_SC22y;
  TH1I *hTPC21_22_S2target_x;
  TH1I *hTPC21_22_S2target_y;
  TH1I *hTPC23_24_S2target_x;
  TH1I *hTPC23_24_S2target_y;
  TH1I *hTPC22_24_S2target_x;
  TH1I *hTPC22_24_S2target_y;
  TH1I *hTPC_SC41x;
  TH1I *hTPC_SC41y;
  TH1I *hTPC_SC42x;
  TH1I *hTPC_SC42y;
  TH1I *hTPC_SC43x;
  TH1I *hTPC_SC43y;
  TH1I *hTPC_MUSIC41x;
  TH1I *hTPC_MUSIC41y;
  TH1I *hTPC_MUSIC42x;
  TH1I *hTPC_MUSIC42y;
  TH1I *hTPC_MUSIC43x;
  TH1I *hTPC_MUSIC43y;
  TH1I *hTPC_S4target_x;
  TH1I *hTPC_S4target_y;

  ////condtition for control sum
  TGo4WinCond *cTPC_CSUM[7][4];
  TGo4PolyCond *cTPC_XY[7];

  //**** keep values from previous event
  Float_t       focx_s2m;
  Float_t       focy_s2m;
  Float_t       angle_x_s2m;
  Float_t       angle_y_s2m;


  //Si detector
  TH1I *hsi_e1;
  TH1I *hsi_e2;
  TH1I *hsi_e3;
  TH1I *hsi_e4;

  TH1I *hsi_e1Trig;
  TH1I *hsi_e2Trig;
  TH1I *hsi_e3Trig;
  TH1I *hsi_e4Trig;

  TH1I *hdssd_e_det1[32];
  TH1I *hdssd_e_det2[32];
  TH1I *hdssd_e_det3[32];
  TH1I *hdssd_e_det4[32];
  TH1I *hdssd_e_det5[32];
  TH1I *hdssd_e_det6[32];
  
  TH1I *hdssd_xmaxenergy; 
  TH1I *hdssd_xmaxindex;
  TH1I *hdssd_ymaxenergy; 
  TH1I *hdssd_ymaxindex;

  TH1I *hdssd_e_det1_dec[32];
  TH1I *hdssd_e_det2_dec[32];
  TH1I *hdssd_e_det3_dec[32];
  TH1I *hdssd_e_det4_dec[32];
  TH1I *hdssd_e_det5_dec[32];
  TH1I *hdssd_e_det6_dec[32];
  TH1I *hdssd_xmaxenergy_dec; 
  TH1I *hdssd_xmaxindex_dec;
  TH1I *hdssd_ymaxenergy_dec; 
  TH1I *hdssd_ymaxindex_dec;

  TH2I *hdssd_xymaxindex;
  TH2I *hdssd_xymaxindex_dec;

  //Channeltron detector
  TH1I 	*hct_all;
  TH1I 	*hct_trigger_DU;
  TH1I 	*hct_trigger_SY;
  TH1I 	*hct_DU;
  TH1I 	*hct_SY;

  //Electron Current
  TH1I 	*helcurrent;

  ClassDef(TFRSCalibrProc,1)
};

#endif //TFRSCALIBRPROCESSOR_H
