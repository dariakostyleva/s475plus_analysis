#include "TFRSUnpackEvent.h"

#include "Riostream.h"
#include "TFRSUnpackProc.h"
#include "Go4EventServer/TGo4FileSource.h"


TFRSUnpackEvent::TFRSUnpackEvent() : TGo4EventElement("FRSUnpackEvent")
				     //  fxProc(0),fxFileSrc(0)
{  }

TFRSUnpackEvent::TFRSUnpackEvent(const char* name) 
  :TGo4EventElement(name)
   //fxProc(0), fxFileSrc(0)
{  }

TFRSUnpackEvent::~TFRSUnpackEvent()
{  }

Int_t TFRSUnpackEvent::Init() 
{ 
  Int_t rev=0;
  Clear();
  // if(CheckEventSource("TFRSUnpackProc")){
  //   fxProc = (TFRSUnpackProc*)GetEventSource();
  //   std::cout << "**** " << GetName() << " will be filled by " << fxProc->GetName() << " ****" << std::endl;
  // } else
  // if(CheckEventSource("TGo4FileSource")) {
  //   fxFileSrc = (TGo4FileSource*)GetEventSource();
  //   std::cout << "**** " << GetName() << " will be filled by File Source ****"<< std::endl;
  // } else rev=1;
  return rev;
}

// Int_t TFRSUnpackEvent::Fill()
// { 
//   Int_t rev=0;
//   Clear();
//   if(fxProc)fxProc->FRSUnpack(this); else  // user event processing method
//   if(fxFileSrc)fxFileSrc->BuildEvent(this); // method from framework to restore event from file
//   return rev;
// }

void TFRSUnpackEvent::Clear(Option_t *t)
{
  
//  EventFlag = -1;
  
  for(int i=0;i<21;i++)
    {
      for(int j=0;j<32;j++)
	{
	  vme_frs[i][j] = 0;  
	  vme_tpcs2[i][j] = 0;
	  vme_tpcs4[i][j] = 0;  
	  vme_main[i][j] = 0;	       
	}
    }
  for(int j=0;j<32;j++)
    {
      scaler_frs[j]=0;
      scaler_main[j]=0;
      timestamp_main[j]=0;
      tpat_main[j]=0;
      nhit_v1290_main[j][0]=0; nhit_v1290_main[j][1]=0;
      for(int kk=0; kk<10; kk++){
        leading_v1290_main[j][kk] = 0;
     	  trailing_v1290_main[j][kk] = 0;
      }
    }

  for(int j=0;j<16;j++)
    {
      vme_trmu_adc[j] = 0;
      vme_trmu_tdc[j] = 0;
    }
   
   qlength = 0;
   qtype = 0;
   qsubtype = 0;
   qdummy = 0;
   qtrigger = 0;
   qevent_nr = 0;
}

ClassImp(TFRSUnpackEvent)
