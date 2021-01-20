#ifndef TFRSUNPACKPROCESSOR_H
#define TFRSUNPACKPROCESSOR_H

#include "TFRSBasicProc.h"
#include "TFRSUnpackEvent.h"
#include "TFRSParameter.h"

class TFRSUnpackEvent;
class TGo4MbsSubEvent;

class TFRSUnpackProc : public TFRSBasicProc {
public:
  TFRSUnpackProc() ;
  TFRSUnpackProc(const char* name);
  virtual ~TFRSUnpackProc();
   
  //void FRSUnpack(TFRSUnpackEvent* tgt);
  // event processing function, default name
  Bool_t BuildEvent(TGo4EventElement* output);
  Bool_t FillHistograms(TFRSUnpackEvent* event);

private:

  Bool_t Event_Extract(TFRSUnpackEvent* event_out, TGo4MbsSubEvent* rawsub, int type_event=1);
#ifdef USELESS
  void UnpackUserSubevent(TGo4MbsSubEvent* psubevt, TFRSUnpackEvent* tgt);
#endif
  TFRSParameter* frs ;
//  TModParameter* ModSetup;
    
  TH1I* hTrigger;         //!

  TH1I* hVME_MAIN_11[32];      //! 
  TH2I* hVME_MAIN_11All;  //!	  
  TH1I* hVME_MAIN_TDC_V1290[32];      //!
  
  TH1I* hVME_FRS_8[32];      //! FRS crate
  TH1I* hVME_FRS_9[32];      //!
  TH1I* hVME_FRS_3[32];     //!
  TH1I* hVME_FRS_12[32];     //!
  TH2I* hVME_FRS_8All ;  //!
  TH2I* hVME_FRS_9All ;  //!
  TH2I* hVME_FRS_3All;  //!
  TH2I* hVME_FRS_12All;  //!
        	
  TH1I* hVME_TPCS2_8[32];     //! TPCS2 crate
  TH1I* hVME_TPCS2_12[32];    //!
  TH1I* hVME_TPCS4_0[32];     //! TPCS4 crate
  TH1I* hVME_TPCS4_1[32];     //!
  TH2I* hVME_TPCS2_8All;  //!
  TH2I* hVME_TPCS2_12All;  //!
  TH2I* hVME_TPCS4_0All;  //!
  TH2I* hVME_TPCS4_1All;  //!

  TH1I* hVME_TRMU_ADC[16];//
  TH2I* hVME_TRMU_ADCAll;
  TH1I* hVME_TRMU_TDC[16];//
  TH2I* hVME_TRMU_TDCAll;
  
  TH2I* h_UnpackStatus; //!
  TH2I* h_TSFlagStatus; //!
  TH2I* h_Multiplicity; //!
 
  bool firstTS[3] ;
  Long64_t previousTimeStamp[3];
  Long64_t currentTimeStamp;
  
  ClassDef(TFRSUnpackProc,1)
};

#endif //TFRSUNPACKPROCESSOR_H

