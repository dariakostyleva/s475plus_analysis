#ifndef TFRSUNPACKEVENT_H
#define TFRSUNPACKEVENT_H


#include "Go4Event/TGo4EventElement.h"


class TFRSUnpackProc;
class TGo4FileSource;

class TFRSUnpackEvent : public TGo4EventElement {
public:
  TFRSUnpackEvent();
  TFRSUnpackEvent(const char* name);
  virtual ~TFRSUnpackEvent();
  // /**
  //  * Method called by the event owner (analysis step) to fill the
  //  * event element from the set event source. Event source can
  //  * be the source of the analysis step (if this is a raw event) 
  //  * or the event processor (if this is a reduced event).
  //  */
  // virtual Int_t Fill();

  /**
   * Method called by the event owner (analysis step) to clear the
   * event element.
   */
  virtual void Clear(Option_t *t="");  
      
  virtual Int_t Init();  

//  Int_t EventFlag;
  
  //------------
  UInt_t vme_main[21][32];          // Main crate 
  UInt_t timestamp_main[32];        // Time stamp in main crate 
  UInt_t scaler_main[32];           // VME scaler in main crate
  UInt_t nhit_v1290_main[32][2];    // multi-hit TDC in main crate [ch][leading or trailing]
  UInt_t leading_v1290_main[32][10];     // leading timing V1290 in main crate 
  UInt_t trailing_v1290_main[32][10];    // trailing timing V1290 in main crate
  UInt_t tpat_main[32];
  
  UInt_t vme_frs[21][32];           // FRS crate
  UInt_t scaler_frs[32];            // VME scaler in frs crate

  UInt_t vme_tpcs2[21][32];         // TPC crate (S2 TPC)
  UInt_t vme_tpcs4[21][32];         // TPC crate (S4/S3 TPC)
  UInt_t vme_trmu_adc[16];              // Travel Music crate
  UInt_t vme_trmu_tdc[16];              // Travel Music crate
  //------------
  
  Int_t         qlength;         /* From event header     */
  Int_t         qtype;           /*                       */
  Int_t         qsubtype;        /*                       */
  Int_t         qdummy;          /*                       */
  Int_t         qtrigger;        /*                       */
  Int_t         qevent_nr;       /*                       */

private:
  //      TFRSUnpackProc *fxProc;     //! This is processor
  //      TGo4FileSource *fxFileSrc;  //! This is file source

  ClassDef(TFRSUnpackEvent,1)         
};
#endif //TFRSUNPACKEVENT_H
