// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIudIdkostyldIexperiment_march_2020dIANALYSISdIs474_s475_DKdIsrcdIG__FRSonline
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSBasicProc.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSUnpackProc.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSCalibrProc.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSAnlProc.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSUnpackEvent.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSUserEvent.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSAnalysis.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSAnlEvent.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSSortEvent.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSSortProc.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSParameter.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSCalibrEvent.h"
#include "/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/TFRSUserProc.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TFRSBasicProc(void *p = 0);
   static void *newArray_TFRSBasicProc(Long_t size, void *p);
   static void delete_TFRSBasicProc(void *p);
   static void deleteArray_TFRSBasicProc(void *p);
   static void destruct_TFRSBasicProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSBasicProc*)
   {
      ::TFRSBasicProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSBasicProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSBasicProc", ::TFRSBasicProc::Class_Version(), "TFRSBasicProc.h", 36,
                  typeid(::TFRSBasicProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSBasicProc::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSBasicProc) );
      instance.SetNew(&new_TFRSBasicProc);
      instance.SetNewArray(&newArray_TFRSBasicProc);
      instance.SetDelete(&delete_TFRSBasicProc);
      instance.SetDeleteArray(&deleteArray_TFRSBasicProc);
      instance.SetDestructor(&destruct_TFRSBasicProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSBasicProc*)
   {
      return GenerateInitInstanceLocal((::TFRSBasicProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSBasicProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSUnpackEvent(void *p = 0);
   static void *newArray_TFRSUnpackEvent(Long_t size, void *p);
   static void delete_TFRSUnpackEvent(void *p);
   static void deleteArray_TFRSUnpackEvent(void *p);
   static void destruct_TFRSUnpackEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSUnpackEvent*)
   {
      ::TFRSUnpackEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSUnpackEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSUnpackEvent", ::TFRSUnpackEvent::Class_Version(), "TFRSUnpackEvent.h", 11,
                  typeid(::TFRSUnpackEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSUnpackEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSUnpackEvent) );
      instance.SetNew(&new_TFRSUnpackEvent);
      instance.SetNewArray(&newArray_TFRSUnpackEvent);
      instance.SetDelete(&delete_TFRSUnpackEvent);
      instance.SetDeleteArray(&deleteArray_TFRSUnpackEvent);
      instance.SetDestructor(&destruct_TFRSUnpackEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSUnpackEvent*)
   {
      return GenerateInitInstanceLocal((::TFRSUnpackEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSUnpackEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSParameter(void *p = 0);
   static void *newArray_TFRSParameter(Long_t size, void *p);
   static void delete_TFRSParameter(void *p);
   static void deleteArray_TFRSParameter(void *p);
   static void destruct_TFRSParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSParameter*)
   {
      ::TFRSParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSParameter", ::TFRSParameter::Class_Version(), "TFRSParameter.h", 8,
                  typeid(::TFRSParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSParameter) );
      instance.SetNew(&new_TFRSParameter);
      instance.SetNewArray(&newArray_TFRSParameter);
      instance.SetDelete(&delete_TFRSParameter);
      instance.SetDeleteArray(&deleteArray_TFRSParameter);
      instance.SetDestructor(&destruct_TFRSParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSParameter*)
   {
      return GenerateInitInstanceLocal((::TFRSParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Map1(void *p = 0);
   static void *newArray_Map1(Long_t size, void *p);
   static void delete_Map1(void *p);
   static void deleteArray_Map1(void *p);
   static void destruct_Map1(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Map1*)
   {
      ::Map1 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Map1 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Map1", ::Map1::Class_Version(), "TFRSParameter.h", 68,
                  typeid(::Map1), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Map1::Dictionary, isa_proxy, 4,
                  sizeof(::Map1) );
      instance.SetNew(&new_Map1);
      instance.SetNewArray(&newArray_Map1);
      instance.SetDelete(&delete_Map1);
      instance.SetDeleteArray(&deleteArray_Map1);
      instance.SetDestructor(&destruct_Map1);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Map1*)
   {
      return GenerateInitInstanceLocal((::Map1*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Map1*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMWParameter(void *p = 0);
   static void *newArray_TMWParameter(Long_t size, void *p);
   static void delete_TMWParameter(void *p);
   static void deleteArray_TMWParameter(void *p);
   static void destruct_TMWParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMWParameter*)
   {
      ::TMWParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMWParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMWParameter", ::TMWParameter::Class_Version(), "TFRSParameter.h", 80,
                  typeid(::TMWParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMWParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TMWParameter) );
      instance.SetNew(&new_TMWParameter);
      instance.SetNewArray(&newArray_TMWParameter);
      instance.SetDelete(&delete_TMWParameter);
      instance.SetDeleteArray(&deleteArray_TMWParameter);
      instance.SetDestructor(&destruct_TMWParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMWParameter*)
   {
      return GenerateInitInstanceLocal((::TMWParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMWParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTPCParameter(void *p = 0);
   static void *newArray_TTPCParameter(Long_t size, void *p);
   static void delete_TTPCParameter(void *p);
   static void deleteArray_TTPCParameter(void *p);
   static void destruct_TTPCParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTPCParameter*)
   {
      ::TTPCParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTPCParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTPCParameter", ::TTPCParameter::Class_Version(), "TFRSParameter.h", 99,
                  typeid(::TTPCParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTPCParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TTPCParameter) );
      instance.SetNew(&new_TTPCParameter);
      instance.SetNewArray(&newArray_TTPCParameter);
      instance.SetDelete(&delete_TTPCParameter);
      instance.SetDeleteArray(&deleteArray_TTPCParameter);
      instance.SetDestructor(&destruct_TTPCParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTPCParameter*)
   {
      return GenerateInitInstanceLocal((::TTPCParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TTPCParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMUSICParameter(void *p = 0);
   static void *newArray_TMUSICParameter(Long_t size, void *p);
   static void delete_TMUSICParameter(void *p);
   static void deleteArray_TMUSICParameter(void *p);
   static void destruct_TMUSICParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMUSICParameter*)
   {
      ::TMUSICParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMUSICParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMUSICParameter", ::TMUSICParameter::Class_Version(), "TFRSParameter.h", 132,
                  typeid(::TMUSICParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMUSICParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TMUSICParameter) );
      instance.SetNew(&new_TMUSICParameter);
      instance.SetNewArray(&newArray_TMUSICParameter);
      instance.SetDelete(&delete_TMUSICParameter);
      instance.SetDeleteArray(&deleteArray_TMUSICParameter);
      instance.SetDestructor(&destruct_TMUSICParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMUSICParameter*)
   {
      return GenerateInitInstanceLocal((::TMUSICParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TSCIParameter(void *p = 0);
   static void *newArray_TSCIParameter(Long_t size, void *p);
   static void delete_TSCIParameter(void *p);
   static void deleteArray_TSCIParameter(void *p);
   static void destruct_TSCIParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TSCIParameter*)
   {
      ::TSCIParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TSCIParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TSCIParameter", ::TSCIParameter::Class_Version(), "TFRSParameter.h", 169,
                  typeid(::TSCIParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TSCIParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TSCIParameter) );
      instance.SetNew(&new_TSCIParameter);
      instance.SetNewArray(&newArray_TSCIParameter);
      instance.SetDelete(&delete_TSCIParameter);
      instance.SetDeleteArray(&deleteArray_TSCIParameter);
      instance.SetDestructor(&destruct_TSCIParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TSCIParameter*)
   {
      return GenerateInitInstanceLocal((::TSCIParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TSCIParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TIDParameter(void *p = 0);
   static void *newArray_TIDParameter(Long_t size, void *p);
   static void delete_TIDParameter(void *p);
   static void deleteArray_TIDParameter(void *p);
   static void destruct_TIDParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TIDParameter*)
   {
      ::TIDParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TIDParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TIDParameter", ::TIDParameter::Class_Version(), "TFRSParameter.h", 226,
                  typeid(::TIDParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TIDParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TIDParameter) );
      instance.SetNew(&new_TIDParameter);
      instance.SetNewArray(&newArray_TIDParameter);
      instance.SetDelete(&delete_TIDParameter);
      instance.SetDeleteArray(&deleteArray_TIDParameter);
      instance.SetDestructor(&destruct_TIDParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TIDParameter*)
   {
      return GenerateInitInstanceLocal((::TIDParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TIDParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TSIParameter(void *p = 0);
   static void *newArray_TSIParameter(Long_t size, void *p);
   static void delete_TSIParameter(void *p);
   static void deleteArray_TSIParameter(void *p);
   static void destruct_TSIParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TSIParameter*)
   {
      ::TSIParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TSIParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TSIParameter", ::TSIParameter::Class_Version(), "TFRSParameter.h", 305,
                  typeid(::TSIParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TSIParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TSIParameter) );
      instance.SetNew(&new_TSIParameter);
      instance.SetNewArray(&newArray_TSIParameter);
      instance.SetDelete(&delete_TSIParameter);
      instance.SetDeleteArray(&deleteArray_TSIParameter);
      instance.SetDestructor(&destruct_TSIParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TSIParameter*)
   {
      return GenerateInitInstanceLocal((::TSIParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TSIParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMRTOFMSParameter(void *p = 0);
   static void *newArray_TMRTOFMSParameter(Long_t size, void *p);
   static void delete_TMRTOFMSParameter(void *p);
   static void deleteArray_TMRTOFMSParameter(void *p);
   static void destruct_TMRTOFMSParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMRTOFMSParameter*)
   {
      ::TMRTOFMSParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMRTOFMSParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMRTOFMSParameter", ::TMRTOFMSParameter::Class_Version(), "TFRSParameter.h", 352,
                  typeid(::TMRTOFMSParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMRTOFMSParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TMRTOFMSParameter) );
      instance.SetNew(&new_TMRTOFMSParameter);
      instance.SetNewArray(&newArray_TMRTOFMSParameter);
      instance.SetDelete(&delete_TMRTOFMSParameter);
      instance.SetDeleteArray(&deleteArray_TMRTOFMSParameter);
      instance.SetDestructor(&destruct_TMRTOFMSParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMRTOFMSParameter*)
   {
      return GenerateInitInstanceLocal((::TMRTOFMSParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSUnpackProc(void *p = 0);
   static void *newArray_TFRSUnpackProc(Long_t size, void *p);
   static void delete_TFRSUnpackProc(void *p);
   static void deleteArray_TFRSUnpackProc(void *p);
   static void destruct_TFRSUnpackProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSUnpackProc*)
   {
      ::TFRSUnpackProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSUnpackProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSUnpackProc", ::TFRSUnpackProc::Class_Version(), "TFRSUnpackProc.h", 11,
                  typeid(::TFRSUnpackProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSUnpackProc::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSUnpackProc) );
      instance.SetNew(&new_TFRSUnpackProc);
      instance.SetNewArray(&newArray_TFRSUnpackProc);
      instance.SetDelete(&delete_TFRSUnpackProc);
      instance.SetDeleteArray(&deleteArray_TFRSUnpackProc);
      instance.SetDestructor(&destruct_TFRSUnpackProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSUnpackProc*)
   {
      return GenerateInitInstanceLocal((::TFRSUnpackProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSUnpackProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSCalibrEvent(void *p = 0);
   static void *newArray_TFRSCalibrEvent(Long_t size, void *p);
   static void delete_TFRSCalibrEvent(void *p);
   static void deleteArray_TFRSCalibrEvent(void *p);
   static void destruct_TFRSCalibrEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSCalibrEvent*)
   {
      ::TFRSCalibrEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSCalibrEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSCalibrEvent", ::TFRSCalibrEvent::Class_Version(), "TFRSCalibrEvent.h", 10,
                  typeid(::TFRSCalibrEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSCalibrEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSCalibrEvent) );
      instance.SetNew(&new_TFRSCalibrEvent);
      instance.SetNewArray(&newArray_TFRSCalibrEvent);
      instance.SetDelete(&delete_TFRSCalibrEvent);
      instance.SetDeleteArray(&deleteArray_TFRSCalibrEvent);
      instance.SetDestructor(&destruct_TFRSCalibrEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSCalibrEvent*)
   {
      return GenerateInitInstanceLocal((::TFRSCalibrEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSCalibrEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSCalibrProc(void *p = 0);
   static void *newArray_TFRSCalibrProc(Long_t size, void *p);
   static void delete_TFRSCalibrProc(void *p);
   static void deleteArray_TFRSCalibrProc(void *p);
   static void destruct_TFRSCalibrProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSCalibrProc*)
   {
      ::TFRSCalibrProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSCalibrProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSCalibrProc", ::TFRSCalibrProc::Class_Version(), "TFRSCalibrProc.h", 17,
                  typeid(::TFRSCalibrProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSCalibrProc::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSCalibrProc) );
      instance.SetNew(&new_TFRSCalibrProc);
      instance.SetNewArray(&newArray_TFRSCalibrProc);
      instance.SetDelete(&delete_TFRSCalibrProc);
      instance.SetDeleteArray(&deleteArray_TFRSCalibrProc);
      instance.SetDestructor(&destruct_TFRSCalibrProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSCalibrProc*)
   {
      return GenerateInitInstanceLocal((::TFRSCalibrProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSCalibrProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSAnlProc(void *p = 0);
   static void *newArray_TFRSAnlProc(Long_t size, void *p);
   static void delete_TFRSAnlProc(void *p);
   static void deleteArray_TFRSAnlProc(void *p);
   static void destruct_TFRSAnlProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSAnlProc*)
   {
      ::TFRSAnlProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSAnlProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSAnlProc", ::TFRSAnlProc::Class_Version(), "TFRSAnlProc.h", 14,
                  typeid(::TFRSAnlProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSAnlProc::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSAnlProc) );
      instance.SetNew(&new_TFRSAnlProc);
      instance.SetNewArray(&newArray_TFRSAnlProc);
      instance.SetDelete(&delete_TFRSAnlProc);
      instance.SetDeleteArray(&deleteArray_TFRSAnlProc);
      instance.SetDestructor(&destruct_TFRSAnlProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSAnlProc*)
   {
      return GenerateInitInstanceLocal((::TFRSAnlProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSAnlProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSUserEvent(void *p = 0);
   static void *newArray_TFRSUserEvent(Long_t size, void *p);
   static void delete_TFRSUserEvent(void *p);
   static void deleteArray_TFRSUserEvent(void *p);
   static void destruct_TFRSUserEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSUserEvent*)
   {
      ::TFRSUserEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSUserEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSUserEvent", ::TFRSUserEvent::Class_Version(), "TFRSUserEvent.h", 9,
                  typeid(::TFRSUserEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSUserEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSUserEvent) );
      instance.SetNew(&new_TFRSUserEvent);
      instance.SetNewArray(&newArray_TFRSUserEvent);
      instance.SetDelete(&delete_TFRSUserEvent);
      instance.SetDeleteArray(&deleteArray_TFRSUserEvent);
      instance.SetDestructor(&destruct_TFRSUserEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSUserEvent*)
   {
      return GenerateInitInstanceLocal((::TFRSUserEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSUserEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSAnalysis(void *p = 0);
   static void *newArray_TFRSAnalysis(Long_t size, void *p);
   static void delete_TFRSAnalysis(void *p);
   static void deleteArray_TFRSAnalysis(void *p);
   static void destruct_TFRSAnalysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSAnalysis*)
   {
      ::TFRSAnalysis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSAnalysis >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSAnalysis", ::TFRSAnalysis::Class_Version(), "TFRSAnalysis.h", 23,
                  typeid(::TFRSAnalysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSAnalysis::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSAnalysis) );
      instance.SetNew(&new_TFRSAnalysis);
      instance.SetNewArray(&newArray_TFRSAnalysis);
      instance.SetDelete(&delete_TFRSAnalysis);
      instance.SetDeleteArray(&deleteArray_TFRSAnalysis);
      instance.SetDestructor(&destruct_TFRSAnalysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSAnalysis*)
   {
      return GenerateInitInstanceLocal((::TFRSAnalysis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSAnalysis*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSAnlEvent(void *p = 0);
   static void *newArray_TFRSAnlEvent(Long_t size, void *p);
   static void delete_TFRSAnlEvent(void *p);
   static void deleteArray_TFRSAnlEvent(void *p);
   static void destruct_TFRSAnlEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSAnlEvent*)
   {
      ::TFRSAnlEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSAnlEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSAnlEvent", ::TFRSAnlEvent::Class_Version(), "TFRSAnlEvent.h", 9,
                  typeid(::TFRSAnlEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSAnlEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSAnlEvent) );
      instance.SetNew(&new_TFRSAnlEvent);
      instance.SetNewArray(&newArray_TFRSAnlEvent);
      instance.SetDelete(&delete_TFRSAnlEvent);
      instance.SetDeleteArray(&deleteArray_TFRSAnlEvent);
      instance.SetDestructor(&destruct_TFRSAnlEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSAnlEvent*)
   {
      return GenerateInitInstanceLocal((::TFRSAnlEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSAnlEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSSortEvent(void *p = 0);
   static void *newArray_TFRSSortEvent(Long_t size, void *p);
   static void delete_TFRSSortEvent(void *p);
   static void deleteArray_TFRSSortEvent(void *p);
   static void destruct_TFRSSortEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSSortEvent*)
   {
      ::TFRSSortEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSSortEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSSortEvent", ::TFRSSortEvent::Class_Version(), "TFRSSortEvent.h", 10,
                  typeid(::TFRSSortEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSSortEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSSortEvent) );
      instance.SetNew(&new_TFRSSortEvent);
      instance.SetNewArray(&newArray_TFRSSortEvent);
      instance.SetDelete(&delete_TFRSSortEvent);
      instance.SetDeleteArray(&deleteArray_TFRSSortEvent);
      instance.SetDestructor(&destruct_TFRSSortEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSSortEvent*)
   {
      return GenerateInitInstanceLocal((::TFRSSortEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSSortEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSSortProc(void *p = 0);
   static void *newArray_TFRSSortProc(Long_t size, void *p);
   static void delete_TFRSSortProc(void *p);
   static void deleteArray_TFRSSortProc(void *p);
   static void destruct_TFRSSortProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSSortProc*)
   {
      ::TFRSSortProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSSortProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSSortProc", ::TFRSSortProc::Class_Version(), "TFRSSortProc.h", 8,
                  typeid(::TFRSSortProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSSortProc::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSSortProc) );
      instance.SetNew(&new_TFRSSortProc);
      instance.SetNewArray(&newArray_TFRSSortProc);
      instance.SetDelete(&delete_TFRSSortProc);
      instance.SetDeleteArray(&deleteArray_TFRSSortProc);
      instance.SetDestructor(&destruct_TFRSSortProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSSortProc*)
   {
      return GenerateInitInstanceLocal((::TFRSSortProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSSortProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSUserProc(void *p = 0);
   static void *newArray_TFRSUserProc(Long_t size, void *p);
   static void delete_TFRSUserProc(void *p);
   static void deleteArray_TFRSUserProc(void *p);
   static void destruct_TFRSUserProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSUserProc*)
   {
      ::TFRSUserProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSUserProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSUserProc", ::TFRSUserProc::Class_Version(), "TFRSUserProc.h", 16,
                  typeid(::TFRSUserProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSUserProc::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSUserProc) );
      instance.SetNew(&new_TFRSUserProc);
      instance.SetNewArray(&newArray_TFRSUserProc);
      instance.SetDelete(&delete_TFRSUserProc);
      instance.SetDeleteArray(&deleteArray_TFRSUserProc);
      instance.SetDestructor(&destruct_TFRSUserProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSUserProc*)
   {
      return GenerateInitInstanceLocal((::TFRSUserProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSUserProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TFRSBasicProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSBasicProc::Class_Name()
{
   return "TFRSBasicProc";
}

//______________________________________________________________________________
const char *TFRSBasicProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSBasicProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSBasicProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSBasicProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSBasicProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSBasicProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSBasicProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSBasicProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSUnpackEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSUnpackEvent::Class_Name()
{
   return "TFRSUnpackEvent";
}

//______________________________________________________________________________
const char *TFRSUnpackEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSUnpackEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSUnpackEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSUnpackEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSParameter::Class_Name()
{
   return "TFRSParameter";
}

//______________________________________________________________________________
const char *TFRSParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Map1::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Map1::Class_Name()
{
   return "Map1";
}

//______________________________________________________________________________
const char *Map1::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Map1::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Map1::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Map1::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TMWParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMWParameter::Class_Name()
{
   return "TMWParameter";
}

//______________________________________________________________________________
const char *TMWParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMWParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMWParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMWParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TTPCParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TTPCParameter::Class_Name()
{
   return "TTPCParameter";
}

//______________________________________________________________________________
const char *TTPCParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TTPCParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TTPCParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TTPCParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TMUSICParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMUSICParameter::Class_Name()
{
   return "TMUSICParameter";
}

//______________________________________________________________________________
const char *TMUSICParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMUSICParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMUSICParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMUSICParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TSCIParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSCIParameter::Class_Name()
{
   return "TSCIParameter";
}

//______________________________________________________________________________
const char *TSCIParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSCIParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSCIParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSCIParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TIDParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TIDParameter::Class_Name()
{
   return "TIDParameter";
}

//______________________________________________________________________________
const char *TIDParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TIDParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TIDParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TIDParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TSIParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSIParameter::Class_Name()
{
   return "TSIParameter";
}

//______________________________________________________________________________
const char *TSIParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSIParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSIParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSIParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TMRTOFMSParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMRTOFMSParameter::Class_Name()
{
   return "TMRTOFMSParameter";
}

//______________________________________________________________________________
const char *TMRTOFMSParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMRTOFMSParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMRTOFMSParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMRTOFMSParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSUnpackProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSUnpackProc::Class_Name()
{
   return "TFRSUnpackProc";
}

//______________________________________________________________________________
const char *TFRSUnpackProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSUnpackProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSUnpackProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSUnpackProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUnpackProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSCalibrEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSCalibrEvent::Class_Name()
{
   return "TFRSCalibrEvent";
}

//______________________________________________________________________________
const char *TFRSCalibrEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSCalibrEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSCalibrEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSCalibrEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSCalibrProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSCalibrProc::Class_Name()
{
   return "TFRSCalibrProc";
}

//______________________________________________________________________________
const char *TFRSCalibrProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSCalibrProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSCalibrProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSCalibrProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSCalibrProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSAnlProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSAnlProc::Class_Name()
{
   return "TFRSAnlProc";
}

//______________________________________________________________________________
const char *TFRSAnlProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSAnlProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSAnlProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSAnlProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSUserEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSUserEvent::Class_Name()
{
   return "TFRSUserEvent";
}

//______________________________________________________________________________
const char *TFRSUserEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSUserEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSUserEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSUserEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSAnalysis::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSAnalysis::Class_Name()
{
   return "TFRSAnalysis";
}

//______________________________________________________________________________
const char *TFRSAnalysis::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnalysis*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSAnalysis::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnalysis*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSAnalysis::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnalysis*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSAnalysis::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnalysis*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSAnlEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSAnlEvent::Class_Name()
{
   return "TFRSAnlEvent";
}

//______________________________________________________________________________
const char *TFRSAnlEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSAnlEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSAnlEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSAnlEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSAnlEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSSortEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSSortEvent::Class_Name()
{
   return "TFRSSortEvent";
}

//______________________________________________________________________________
const char *TFRSSortEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSSortEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSSortEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSSortEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSSortProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSSortProc::Class_Name()
{
   return "TFRSSortProc";
}

//______________________________________________________________________________
const char *TFRSSortProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSSortProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSSortProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSSortProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSSortProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSUserProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSUserProc::Class_Name()
{
   return "TFRSUserProc";
}

//______________________________________________________________________________
const char *TFRSUserProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSUserProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSUserProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSUserProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSUserProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TFRSBasicProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSBasicProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSBasicProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSBasicProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSBasicProc(void *p) {
      return  p ? new(p) ::TFRSBasicProc : new ::TFRSBasicProc;
   }
   static void *newArray_TFRSBasicProc(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSBasicProc[nElements] : new ::TFRSBasicProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSBasicProc(void *p) {
      delete ((::TFRSBasicProc*)p);
   }
   static void deleteArray_TFRSBasicProc(void *p) {
      delete [] ((::TFRSBasicProc*)p);
   }
   static void destruct_TFRSBasicProc(void *p) {
      typedef ::TFRSBasicProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSBasicProc

//______________________________________________________________________________
void TFRSUnpackEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSUnpackEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSUnpackEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSUnpackEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSUnpackEvent(void *p) {
      return  p ? new(p) ::TFRSUnpackEvent : new ::TFRSUnpackEvent;
   }
   static void *newArray_TFRSUnpackEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSUnpackEvent[nElements] : new ::TFRSUnpackEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSUnpackEvent(void *p) {
      delete ((::TFRSUnpackEvent*)p);
   }
   static void deleteArray_TFRSUnpackEvent(void *p) {
      delete [] ((::TFRSUnpackEvent*)p);
   }
   static void destruct_TFRSUnpackEvent(void *p) {
      typedef ::TFRSUnpackEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSUnpackEvent

//______________________________________________________________________________
void TFRSParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSParameter(void *p) {
      return  p ? new(p) ::TFRSParameter : new ::TFRSParameter;
   }
   static void *newArray_TFRSParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSParameter[nElements] : new ::TFRSParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSParameter(void *p) {
      delete ((::TFRSParameter*)p);
   }
   static void deleteArray_TFRSParameter(void *p) {
      delete [] ((::TFRSParameter*)p);
   }
   static void destruct_TFRSParameter(void *p) {
      typedef ::TFRSParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSParameter

//______________________________________________________________________________
void Map1::Streamer(TBuffer &R__b)
{
   // Stream an object of class Map1.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Map1::Class(),this);
   } else {
      R__b.WriteClassBuffer(Map1::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Map1(void *p) {
      return  p ? new(p) ::Map1 : new ::Map1;
   }
   static void *newArray_Map1(Long_t nElements, void *p) {
      return p ? new(p) ::Map1[nElements] : new ::Map1[nElements];
   }
   // Wrapper around operator delete
   static void delete_Map1(void *p) {
      delete ((::Map1*)p);
   }
   static void deleteArray_Map1(void *p) {
      delete [] ((::Map1*)p);
   }
   static void destruct_Map1(void *p) {
      typedef ::Map1 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Map1

//______________________________________________________________________________
void TMWParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMWParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMWParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMWParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMWParameter(void *p) {
      return  p ? new(p) ::TMWParameter : new ::TMWParameter;
   }
   static void *newArray_TMWParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TMWParameter[nElements] : new ::TMWParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMWParameter(void *p) {
      delete ((::TMWParameter*)p);
   }
   static void deleteArray_TMWParameter(void *p) {
      delete [] ((::TMWParameter*)p);
   }
   static void destruct_TMWParameter(void *p) {
      typedef ::TMWParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMWParameter

//______________________________________________________________________________
void TTPCParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTPCParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTPCParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTPCParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TTPCParameter(void *p) {
      return  p ? new(p) ::TTPCParameter : new ::TTPCParameter;
   }
   static void *newArray_TTPCParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TTPCParameter[nElements] : new ::TTPCParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTPCParameter(void *p) {
      delete ((::TTPCParameter*)p);
   }
   static void deleteArray_TTPCParameter(void *p) {
      delete [] ((::TTPCParameter*)p);
   }
   static void destruct_TTPCParameter(void *p) {
      typedef ::TTPCParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTPCParameter

//______________________________________________________________________________
void TMUSICParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMUSICParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMUSICParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMUSICParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMUSICParameter(void *p) {
      return  p ? new(p) ::TMUSICParameter : new ::TMUSICParameter;
   }
   static void *newArray_TMUSICParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TMUSICParameter[nElements] : new ::TMUSICParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMUSICParameter(void *p) {
      delete ((::TMUSICParameter*)p);
   }
   static void deleteArray_TMUSICParameter(void *p) {
      delete [] ((::TMUSICParameter*)p);
   }
   static void destruct_TMUSICParameter(void *p) {
      typedef ::TMUSICParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMUSICParameter

//______________________________________________________________________________
void TSCIParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TSCIParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TSCIParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TSCIParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TSCIParameter(void *p) {
      return  p ? new(p) ::TSCIParameter : new ::TSCIParameter;
   }
   static void *newArray_TSCIParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TSCIParameter[nElements] : new ::TSCIParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TSCIParameter(void *p) {
      delete ((::TSCIParameter*)p);
   }
   static void deleteArray_TSCIParameter(void *p) {
      delete [] ((::TSCIParameter*)p);
   }
   static void destruct_TSCIParameter(void *p) {
      typedef ::TSCIParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TSCIParameter

//______________________________________________________________________________
void TIDParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TIDParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TIDParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TIDParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TIDParameter(void *p) {
      return  p ? new(p) ::TIDParameter : new ::TIDParameter;
   }
   static void *newArray_TIDParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TIDParameter[nElements] : new ::TIDParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TIDParameter(void *p) {
      delete ((::TIDParameter*)p);
   }
   static void deleteArray_TIDParameter(void *p) {
      delete [] ((::TIDParameter*)p);
   }
   static void destruct_TIDParameter(void *p) {
      typedef ::TIDParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TIDParameter

//______________________________________________________________________________
void TSIParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TSIParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TSIParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TSIParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TSIParameter(void *p) {
      return  p ? new(p) ::TSIParameter : new ::TSIParameter;
   }
   static void *newArray_TSIParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TSIParameter[nElements] : new ::TSIParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TSIParameter(void *p) {
      delete ((::TSIParameter*)p);
   }
   static void deleteArray_TSIParameter(void *p) {
      delete [] ((::TSIParameter*)p);
   }
   static void destruct_TSIParameter(void *p) {
      typedef ::TSIParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TSIParameter

//______________________________________________________________________________
void TMRTOFMSParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMRTOFMSParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMRTOFMSParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMRTOFMSParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMRTOFMSParameter(void *p) {
      return  p ? new(p) ::TMRTOFMSParameter : new ::TMRTOFMSParameter;
   }
   static void *newArray_TMRTOFMSParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TMRTOFMSParameter[nElements] : new ::TMRTOFMSParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMRTOFMSParameter(void *p) {
      delete ((::TMRTOFMSParameter*)p);
   }
   static void deleteArray_TMRTOFMSParameter(void *p) {
      delete [] ((::TMRTOFMSParameter*)p);
   }
   static void destruct_TMRTOFMSParameter(void *p) {
      typedef ::TMRTOFMSParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMRTOFMSParameter

//______________________________________________________________________________
void TFRSUnpackProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSUnpackProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSUnpackProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSUnpackProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSUnpackProc(void *p) {
      return  p ? new(p) ::TFRSUnpackProc : new ::TFRSUnpackProc;
   }
   static void *newArray_TFRSUnpackProc(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSUnpackProc[nElements] : new ::TFRSUnpackProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSUnpackProc(void *p) {
      delete ((::TFRSUnpackProc*)p);
   }
   static void deleteArray_TFRSUnpackProc(void *p) {
      delete [] ((::TFRSUnpackProc*)p);
   }
   static void destruct_TFRSUnpackProc(void *p) {
      typedef ::TFRSUnpackProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSUnpackProc

//______________________________________________________________________________
void TFRSCalibrEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSCalibrEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSCalibrEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSCalibrEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSCalibrEvent(void *p) {
      return  p ? new(p) ::TFRSCalibrEvent : new ::TFRSCalibrEvent;
   }
   static void *newArray_TFRSCalibrEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSCalibrEvent[nElements] : new ::TFRSCalibrEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSCalibrEvent(void *p) {
      delete ((::TFRSCalibrEvent*)p);
   }
   static void deleteArray_TFRSCalibrEvent(void *p) {
      delete [] ((::TFRSCalibrEvent*)p);
   }
   static void destruct_TFRSCalibrEvent(void *p) {
      typedef ::TFRSCalibrEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSCalibrEvent

//______________________________________________________________________________
void TFRSCalibrProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSCalibrProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSCalibrProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSCalibrProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSCalibrProc(void *p) {
      return  p ? new(p) ::TFRSCalibrProc : new ::TFRSCalibrProc;
   }
   static void *newArray_TFRSCalibrProc(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSCalibrProc[nElements] : new ::TFRSCalibrProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSCalibrProc(void *p) {
      delete ((::TFRSCalibrProc*)p);
   }
   static void deleteArray_TFRSCalibrProc(void *p) {
      delete [] ((::TFRSCalibrProc*)p);
   }
   static void destruct_TFRSCalibrProc(void *p) {
      typedef ::TFRSCalibrProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSCalibrProc

//______________________________________________________________________________
void TFRSAnlProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSAnlProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSAnlProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSAnlProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSAnlProc(void *p) {
      return  p ? new(p) ::TFRSAnlProc : new ::TFRSAnlProc;
   }
   static void *newArray_TFRSAnlProc(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSAnlProc[nElements] : new ::TFRSAnlProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSAnlProc(void *p) {
      delete ((::TFRSAnlProc*)p);
   }
   static void deleteArray_TFRSAnlProc(void *p) {
      delete [] ((::TFRSAnlProc*)p);
   }
   static void destruct_TFRSAnlProc(void *p) {
      typedef ::TFRSAnlProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSAnlProc

//______________________________________________________________________________
void TFRSUserEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSUserEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSUserEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSUserEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSUserEvent(void *p) {
      return  p ? new(p) ::TFRSUserEvent : new ::TFRSUserEvent;
   }
   static void *newArray_TFRSUserEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSUserEvent[nElements] : new ::TFRSUserEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSUserEvent(void *p) {
      delete ((::TFRSUserEvent*)p);
   }
   static void deleteArray_TFRSUserEvent(void *p) {
      delete [] ((::TFRSUserEvent*)p);
   }
   static void destruct_TFRSUserEvent(void *p) {
      typedef ::TFRSUserEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSUserEvent

//______________________________________________________________________________
void TFRSAnalysis::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSAnalysis.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSAnalysis::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSAnalysis::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSAnalysis(void *p) {
      return  p ? new(p) ::TFRSAnalysis : new ::TFRSAnalysis;
   }
   static void *newArray_TFRSAnalysis(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSAnalysis[nElements] : new ::TFRSAnalysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSAnalysis(void *p) {
      delete ((::TFRSAnalysis*)p);
   }
   static void deleteArray_TFRSAnalysis(void *p) {
      delete [] ((::TFRSAnalysis*)p);
   }
   static void destruct_TFRSAnalysis(void *p) {
      typedef ::TFRSAnalysis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSAnalysis

//______________________________________________________________________________
void TFRSAnlEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSAnlEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSAnlEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSAnlEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSAnlEvent(void *p) {
      return  p ? new(p) ::TFRSAnlEvent : new ::TFRSAnlEvent;
   }
   static void *newArray_TFRSAnlEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSAnlEvent[nElements] : new ::TFRSAnlEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSAnlEvent(void *p) {
      delete ((::TFRSAnlEvent*)p);
   }
   static void deleteArray_TFRSAnlEvent(void *p) {
      delete [] ((::TFRSAnlEvent*)p);
   }
   static void destruct_TFRSAnlEvent(void *p) {
      typedef ::TFRSAnlEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSAnlEvent

//______________________________________________________________________________
void TFRSSortEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSSortEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSSortEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSSortEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSSortEvent(void *p) {
      return  p ? new(p) ::TFRSSortEvent : new ::TFRSSortEvent;
   }
   static void *newArray_TFRSSortEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSSortEvent[nElements] : new ::TFRSSortEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSSortEvent(void *p) {
      delete ((::TFRSSortEvent*)p);
   }
   static void deleteArray_TFRSSortEvent(void *p) {
      delete [] ((::TFRSSortEvent*)p);
   }
   static void destruct_TFRSSortEvent(void *p) {
      typedef ::TFRSSortEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSSortEvent

//______________________________________________________________________________
void TFRSSortProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSSortProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSSortProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSSortProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSSortProc(void *p) {
      return  p ? new(p) ::TFRSSortProc : new ::TFRSSortProc;
   }
   static void *newArray_TFRSSortProc(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSSortProc[nElements] : new ::TFRSSortProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSSortProc(void *p) {
      delete ((::TFRSSortProc*)p);
   }
   static void deleteArray_TFRSSortProc(void *p) {
      delete [] ((::TFRSSortProc*)p);
   }
   static void destruct_TFRSSortProc(void *p) {
      typedef ::TFRSSortProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSSortProc

//______________________________________________________________________________
void TFRSUserProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSUserProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSUserProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSUserProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSUserProc(void *p) {
      return  p ? new(p) ::TFRSUserProc : new ::TFRSUserProc;
   }
   static void *newArray_TFRSUserProc(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSUserProc[nElements] : new ::TFRSUserProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSUserProc(void *p) {
      delete ((::TFRSUserProc*)p);
   }
   static void deleteArray_TFRSUserProc(void *p) {
      delete [] ((::TFRSUserProc*)p);
   }
   static void destruct_TFRSUserProc(void *p) {
      typedef ::TFRSUserProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSUserProc

namespace ROOT {
   static TClass *maplEintcOintgR_Dictionary();
   static void maplEintcOintgR_TClassManip(TClass*);
   static void *new_maplEintcOintgR(void *p = 0);
   static void *newArray_maplEintcOintgR(Long_t size, void *p);
   static void delete_maplEintcOintgR(void *p);
   static void deleteArray_maplEintcOintgR(void *p);
   static void destruct_maplEintcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,int>*)
   {
      map<int,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,int>", -2, "map", 96,
                  typeid(map<int,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,int>) );
      instance.SetNew(&new_maplEintcOintgR);
      instance.SetNewArray(&newArray_maplEintcOintgR);
      instance.SetDelete(&delete_maplEintcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOintgR);
      instance.SetDestructor(&destruct_maplEintcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,int>*)0x0)->GetClass();
      maplEintcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int> : new map<int,int>;
   }
   static void *newArray_maplEintcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int>[nElements] : new map<int,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOintgR(void *p) {
      delete ((map<int,int>*)p);
   }
   static void deleteArray_maplEintcOintgR(void *p) {
      delete [] ((map<int,int>*)p);
   }
   static void destruct_maplEintcOintgR(void *p) {
      typedef map<int,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,int>

namespace {
  void TriggerDictionaryInitialization_libGo4UserAnalysis_Impl() {
    static const char* headers[] = {
"TFRSBasicProc.h",
"TFRSUnpackProc.h",
"TFRSCalibrProc.h",
"TFRSAnlProc.h",
"TFRSUnpackEvent.h",
"TFRSUserEvent.h",
"TFRSAnalysis.h",
"TFRSAnlEvent.h",
"TFRSSortEvent.h",
"TFRSSortProc.h",
"TFRSParameter.h",
"TFRSCalibrEvent.h",
"TFRSUserProc.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/csee.gsi.de/go4/600-00/include",
"/cvmfs/csee.gsi.de/go4/600-00",
"/cvmfs/csee.gsi.de/hdf5/1.10.5//include",
"/cvmfs/csee.gsi.de/root/618-04/include",
"/u/dkostyl/experiment_march_2020/ANALYSIS/s474_s475_DK/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libGo4UserAnalysis dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TFRSBasicProc.h")))  TFRSBasicProc;
class __attribute__((annotate("$clingAutoload$TFRSUnpackEvent.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TFRSUnpackEvent;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TFRSParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  Map1;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TMWParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TTPCParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TMUSICParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TSCIParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TIDParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TSIParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TMRTOFMSParameter;
class __attribute__((annotate("$clingAutoload$TFRSUnpackProc.h")))  TFRSUnpackProc;
class __attribute__((annotate("$clingAutoload$TFRSCalibrEvent.h")))  __attribute__((annotate("$clingAutoload$TFRSCalibrProc.h")))  TFRSCalibrEvent;
class __attribute__((annotate("$clingAutoload$TFRSCalibrProc.h")))  TFRSCalibrProc;
class __attribute__((annotate("$clingAutoload$TFRSAnlProc.h")))  TFRSAnlProc;
class __attribute__((annotate("$clingAutoload$TFRSUserEvent.h")))  TFRSUserEvent;
class __attribute__((annotate("$clingAutoload$TFRSAnalysis.h")))  TFRSAnalysis;
class __attribute__((annotate("$clingAutoload$TFRSAnlEvent.h")))  TFRSAnlEvent;
class __attribute__((annotate("$clingAutoload$TFRSSortEvent.h")))  TFRSSortEvent;
class __attribute__((annotate("$clingAutoload$TFRSSortProc.h")))  TFRSSortProc;
class __attribute__((annotate("$clingAutoload$TFRSUserProc.h")))  TFRSUserProc;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libGo4UserAnalysis dictionary payload"

#ifndef Linux
  #define Linux 1
#endif
#ifndef __GO4HDF5__
  #define __GO4HDF5__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TFRSBasicProc.h"
#include "TFRSUnpackProc.h"
#include "TFRSCalibrProc.h"
#include "TFRSAnlProc.h"
#include "TFRSUnpackEvent.h"
#include "TFRSUserEvent.h"
#include "TFRSAnalysis.h"
#include "TFRSAnlEvent.h"
#include "TFRSSortEvent.h"
#include "TFRSSortProc.h"
#include "TFRSParameter.h"
#include "TFRSCalibrEvent.h"
#include "TFRSUserProc.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Map1", payloadCode, "@",
"TFRSAnalysis", payloadCode, "@",
"TFRSAnlEvent", payloadCode, "@",
"TFRSAnlProc", payloadCode, "@",
"TFRSBasicProc", payloadCode, "@",
"TFRSCalibrEvent", payloadCode, "@",
"TFRSCalibrProc", payloadCode, "@",
"TFRSParameter", payloadCode, "@",
"TFRSSortEvent", payloadCode, "@",
"TFRSSortProc", payloadCode, "@",
"TFRSUnpackEvent", payloadCode, "@",
"TFRSUnpackProc", payloadCode, "@",
"TFRSUserEvent", payloadCode, "@",
"TFRSUserProc", payloadCode, "@",
"TIDParameter", payloadCode, "@",
"TMRTOFMSParameter", payloadCode, "@",
"TMUSICParameter", payloadCode, "@",
"TMWParameter", payloadCode, "@",
"TSCIParameter", payloadCode, "@",
"TSIParameter", payloadCode, "@",
"TTPCParameter", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libGo4UserAnalysis",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libGo4UserAnalysis_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libGo4UserAnalysis() {
  TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
}
