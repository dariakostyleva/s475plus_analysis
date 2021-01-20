#include "TFRSSortProc.h"
#include "TFRSSortEvent.h"
#include "TFRSUnpackEvent.h"

#include "TFRSParameter.h"

//#include  <iostream.h>
#include  <stdio.h>

TFRSSortProc::TFRSSortProc() : TFRSBasicProc("FRSSortProc") 
{
  StartOfSpilTime = -1;
  PreviousTS = -1;
}

TFRSSortProc::TFRSSortProc(const char* name) : TFRSBasicProc(name) 
{ 
  StartOfSpilTime = -1;
  PreviousTS = -1;
  counter = 0;
}

TFRSSortProc::~TFRSSortProc() {
}

Bool_t TFRSSortProc::BuildEvent(TGo4EventElement* output)
{

  TFRSSortEvent* tgt = dynamic_cast<TFRSSortEvent*> (output);
  if (tgt==nullptr)
    return kFALSE;

  tgt->SetValid(kTRUE);  // all events after unpack always accepted

  TFRSUnpackEvent *src = dynamic_cast<TFRSUnpackEvent*> (GetInputEvent());
  if (src==nullptr)
    return kFALSE;
  
  /* now we can assign the parameters according to cabling:  */

  /* ### timestamp: */
  tgt->ts_word[0] = src->timestamp_main[0];
  tgt->ts_word[1] = src->timestamp_main[1];
  tgt->ts_word[2] = src->timestamp_main[2];
  tgt->ts_word[3] = src->timestamp_main[3];


  tgt->timestamp = Long64_t(1)*tgt->ts_word[0] + Long64_t(0x10000)*tgt->ts_word[1] + Long64_t(0x100000000)*tgt->ts_word[2] + Long64_t(0x1000000000000)*tgt->ts_word[3];
  // printf("qtrigger=%d timestamp=%ld \n",src->qtrigger,tgt->timestamp);
  tgt->tsys_word[0] = Long64_t(1)*tgt->ts_word[0] + Long64_t(0x10000)*tgt->ts_word[1] ; //s time low word
  tgt->tsys_word[1] = Long64_t(0x100000000)*tgt->ts_word[2] + Long64_t(0x1000000000000)*tgt->ts_word[3] ; //s time high worid... we do not use it
  if(PreviousTS < 0)
    tgt->tsys_word[2] = 0;
  else
    tgt->tsys_word[2] = (tgt->timestamp - PreviousTS)*1.e-5 ; //ms time since the previous s time (ftime routine)
  tgt->systemtime_s = tgt->tsys_word[2]*1e-3; //tgt->tsys_word[0] ; 
  tgt->systemtime_ms= tgt->tsys_word[2] ; 


  if (src->qtrigger==12)
    {
      StartOfSpilTime = tgt->timestamp; 
      //StartOfSpilTime = 0; 
      StartOfSpilTime2 = tgt->timestamp;
      //StartOfSpilTime2 = 0;  
      // printf("12 spill start at %ld ",StartOfSpilTime);
    }   
  else if (src->qtrigger==13)
    {
      StartOfSpilTime = -1;
    }
  //else                         //changed 170309
  // rest are interesting only if trigger == 1
  //if (src->qtrigger!=1 ) return;             
  
  // calculate time from spill start in sec
  if (StartOfSpilTime>=0) 
    { 
      tgt->timespill = (tgt->timestamp - StartOfSpilTime) * 1e-2;// microsec // 50000000.;
      //tgt->timespill = 1;
      //printf("timespill= %f \n",tgt->timespill);    
    }
  
  tgt->timespill2 = (tgt->timestamp - StartOfSpilTime2) * 1e-2; //microsec  // 50000000.;
  //tgt->timespill2 = 1; 

  /* ### Pattern ###*/
  // tgt->pattern = src->vme0[5][0];
  tgt->trigger = src->qtrigger;
  

  /* ### scalers:  */
  /* these are treated as 32-bit integers directly  */
  for(int i=0;i<32;i++)
    {
      tgt->sc_long[i]    = src->scaler_frs[i]; //frs crate
      tgt->sc_long[32+i] = src->scaler_main[i]; //main crate
    }

  //std::cout<<"1Hz sort,"<<src->vme0[6][3]<<std::endl;       
 
  /* ### TA Ionization Chamber dE:  */
  //  tgt->ic_de = src->vme0[13][16] & 0xfff;
   /* ### MW anodes:  MWPC 11, 31, 21, 22, 51, 71, 81, 82 */
 // only 8 MW are used, but keep index of the array 13 as it was
  for(int i=0;i<13;i++){
    tgt->mw_an[i] = src->vme_frs[8][i] & 0xfff;
  }
  /* ### MW cathodes:  */
  // from MW11 then MW21 then MW22 then MW31 
  for(int i=0;i<4;++i)
    { 
      tgt->mw_xl[i] = src->vme_frs[8][16+i*4] & 0xfff;
      tgt->mw_xr[i] = src->vme_frs[8][17+i*4] & 0xfff;
      tgt->mw_yu[i] = src->vme_frs[8][18+i*4] & 0xfff;
      tgt->mw_yd[i] = src->vme_frs[8][19+i*4] & 0xfff;
    }
  // from MW51 then MW71 then MW81 then MW82
  for(int i=0;i<4;++i)
    {
      tgt->mw_xl[i+4] = src->vme_frs[9][0+i*4] & 0xfff;
      tgt->mw_xr[i+4] = src->vme_frs[9][1+i*4] & 0xfff;
      tgt->mw_yu[i+4] = src->vme_frs[9][2+i*4] & 0xfff;
      tgt->mw_yd[i+4] = src->vme_frs[9][3+i*4] & 0xfff;
    }

 /*   
  // ### MW anodes: 
  for(int i=0;i<13;i++)
    tgt->mw_an[i] = src->vme_frs[8][i] & 0xfff;
    
  // ### MW cathodes: 
  // from MW11 -> MW31
  for(int i=0;i<4;++i)
    {  
      tgt->mw_xr[i] = src->vme_frs[8][16+i*4] & 0xfff;
      tgt->mw_xl[i] = src->vme_frs[8][17+i*4] & 0xfff;
      tgt->mw_yu[i] = src->vme_frs[8][18+i*4] & 0xfff;
      tgt->mw_yd[i] = src->vme_frs[8][19+i*4] & 0xfff;
    }
  // from MW41 -> MW51
  for(int i=0;i<3;++i)
    {
      tgt->mw_xr[i+4] = src->vme_frs[9][0+i*4] & 0xfff;
      tgt->mw_xl[i+4] = src->vme_frs[9][1+i*4] & 0xfff;
      tgt->mw_yu[i+4] = src->vme_frs[9][2+i*4] & 0xfff;
      tgt->mw_yd[i+4] = src->vme_frs[9][3+i*4] & 0xfff;
    }
  // skip MW61
  //putting MW61 all to zero (09.07.2018)
      tgt->mw_xr[7] = 0;
      tgt->mw_xl[7] = 0;
      tgt->mw_yu[7] = 0;
      tgt->mw_yd[7] = 0;
     
  // from MW71 -> MWB2
  for(int i=0;i<5;++i)
    {
      tgt->mw_xr[i+8] = src->vme_frs[9][12+i*4] & 0xfff;
      tgt->mw_xl[i+8] = src->vme_frs[9][13+i*4] & 0xfff;
      tgt->mw_yu[i+8] = src->vme_frs[9][14+i*4] & 0xfff;
      tgt->mw_yd[i+8] = src->vme_frs[9][15+i*4] & 0xfff;
    }
 */


  //////////////////////////////////////
  // TPC part                         //
  //                                  //
  //////////////////////////////////////
  
  //ADC

  //TPC 1 at S2 (TPC 21) in vaccuum
  tgt->tpc_a[0][0]=src->vme_tpcs2[12][0] & 0xfff;
  tgt->tpc_a[0][1]=src->vme_tpcs2[12][1] & 0xfff;
  tgt->tpc_a[0][2]=src->vme_tpcs2[12][2] & 0xfff;
  tgt->tpc_a[0][3]=src->vme_tpcs2[12][3] & 0xfff;
  tgt->tpc_l[0][0]=src->vme_tpcs2[12][4] & 0xfff;
  tgt->tpc_r[0][0]=src->vme_tpcs2[12][5] & 0xfff;
  tgt->tpc_l[0][1]=src->vme_tpcs2[12][6] & 0xfff;
  tgt->tpc_r[0][1]=src->vme_tpcs2[12][7] & 0xfff;

  //TPC 2 at S2 (TPC 22) in vaccuum
  tgt->tpc_a[1][0]=src->vme_tpcs2[12][8] & 0xfff;
  tgt->tpc_a[1][1]=src->vme_tpcs2[12][9] & 0xfff;
  tgt->tpc_a[1][2]=src->vme_tpcs2[12][10] & 0xfff;
  tgt->tpc_a[1][3]=src->vme_tpcs2[12][11] & 0xfff;
  tgt->tpc_l[1][0]=src->vme_tpcs2[12][12] & 0xfff;
  tgt->tpc_r[1][0]=src->vme_tpcs2[12][13] & 0xfff;
  tgt->tpc_l[1][1]=src->vme_tpcs2[12][14] & 0xfff;
  tgt->tpc_r[1][1]=src->vme_tpcs2[12][15] & 0xfff;

  //TPC 3 at S2 (TPC 23) in air
  tgt->tpc_a[2][0]=src->vme_tpcs2[12][16] & 0xfff;
  tgt->tpc_a[2][1]=src->vme_tpcs2[12][17] & 0xfff;
  tgt->tpc_a[2][2]=src->vme_tpcs2[12][18] & 0xfff;
  tgt->tpc_a[2][3]=src->vme_tpcs2[12][19] & 0xfff;
  tgt->tpc_l[2][0]=src->vme_tpcs2[12][20] & 0xfff;
  tgt->tpc_r[2][0]=src->vme_tpcs2[12][21] & 0xfff;
  tgt->tpc_l[2][1]=src->vme_tpcs2[12][22] & 0xfff;
  tgt->tpc_r[2][1]=src->vme_tpcs2[12][23] & 0xfff;
  
  //TPC 4 at S2 (TPC 24) in air
  tgt->tpc_a[3][0]=src->vme_tpcs2[12][24] & 0xfff;
  tgt->tpc_a[3][1]=src->vme_tpcs2[12][25] & 0xfff;
  tgt->tpc_a[3][2]=src->vme_tpcs2[12][26] & 0xfff;
  tgt->tpc_a[3][3]=src->vme_tpcs2[12][27] & 0xfff;
  tgt->tpc_l[3][0]=src->vme_tpcs2[12][28] & 0xfff;
  tgt->tpc_r[3][0]=src->vme_tpcs2[12][29] & 0xfff;
  tgt->tpc_l[3][1]=src->vme_tpcs2[12][30] & 0xfff;
  tgt->tpc_r[3][1]=src->vme_tpcs2[12][31] & 0xfff;
  
  //TPC 5  at S4 (TPC 41) in air
  tgt->tpc_a[4][0]=src->vme_tpcs4[1][0] & 0xfff;
  tgt->tpc_a[4][1]=src->vme_tpcs4[1][1] & 0xfff;
  tgt->tpc_a[4][2]=src->vme_tpcs4[1][2] & 0xfff;
  tgt->tpc_a[4][3]=src->vme_tpcs4[1][3] & 0xfff;
  tgt->tpc_l[4][0]=src->vme_tpcs4[1][4] & 0xfff;
  tgt->tpc_r[4][0]=src->vme_tpcs4[1][5] & 0xfff;
  tgt->tpc_l[4][1]=src->vme_tpcs4[1][6] & 0xfff;
  tgt->tpc_r[4][1]=src->vme_tpcs4[1][7] & 0xfff;

  //TPC 6 at S4 (TPC 42) in air
  tgt->tpc_a[5][0]=src->vme_tpcs4[1][8] & 0xfff;
  tgt->tpc_a[5][1]=src->vme_tpcs4[1][9] & 0xfff;
  tgt->tpc_a[5][2]=src->vme_tpcs4[1][10] & 0xfff;
  tgt->tpc_a[5][3]=src->vme_tpcs4[1][11] & 0xfff;
  tgt->tpc_l[5][0]=src->vme_tpcs4[1][12] & 0xfff;
  tgt->tpc_r[5][0]=src->vme_tpcs4[1][13] & 0xfff;
  tgt->tpc_l[5][1]=src->vme_tpcs4[1][14] & 0xfff;
  tgt->tpc_r[5][1]=src->vme_tpcs4[1][15] & 0xfff;

  //TPC at S3 (TPC 31) (checkSB)
  tgt->tpc_a[6][0]=src->vme_tpcs4[1][16] & 0xfff;
  tgt->tpc_a[6][1]=src->vme_tpcs4[1][17] & 0xfff;
  tgt->tpc_a[6][2]=src->vme_tpcs4[1][18] & 0xfff;
  tgt->tpc_a[6][3]=src->vme_tpcs4[1][19] & 0xfff;
  tgt->tpc_l[6][0]=src->vme_tpcs4[1][20] & 0xfff;
  tgt->tpc_r[6][0]=src->vme_tpcs4[1][21] & 0xfff;
  tgt->tpc_l[6][1]=src->vme_tpcs4[1][22] & 0xfff;
  tgt->tpc_r[6][1]=src->vme_tpcs4[1][23] & 0xfff;
  
 
  //TDC

  //TPC 1 at S2 (TPC 21) in vaccuum
  tgt->tpc_dt[0][0]=src->vme_tpcs2[8][0] & 0xfff;
  tgt->tpc_dt[0][1]=src->vme_tpcs2[8][1] & 0xfff;
  tgt->tpc_dt[0][2]=src->vme_tpcs2[8][2] & 0xfff;
  tgt->tpc_dt[0][3]=src->vme_tpcs2[8][3] & 0xfff;
  tgt->tpc_lt[0][0]=src->vme_tpcs2[8][4] & 0xfff;
  tgt->tpc_rt[0][0]=src->vme_tpcs2[8][5] & 0xfff;
  tgt->tpc_lt[0][1]=src->vme_tpcs2[8][6] & 0xfff;
  tgt->tpc_rt[0][1]=src->vme_tpcs2[8][7] & 0xfff;

  //TPC 2 at S2 (TPC 22) in vaccuum
  tgt->tpc_dt[1][0]=src->vme_tpcs2[8][8] & 0xfff;
  tgt->tpc_dt[1][1]=src->vme_tpcs2[8][9] & 0xfff;
  tgt->tpc_dt[1][2]=src->vme_tpcs2[8][10] & 0xfff;
  tgt->tpc_dt[1][3]=src->vme_tpcs2[8][11] & 0xfff;
  tgt->tpc_lt[1][0]=src->vme_tpcs2[8][12] & 0xfff;
  tgt->tpc_rt[1][0]=src->vme_tpcs2[8][13] & 0xfff;
  tgt->tpc_lt[1][1]=src->vme_tpcs2[8][14] & 0xfff;
  tgt->tpc_rt[1][1]=src->vme_tpcs2[8][15] & 0xfff;

  //TPC 3 at S2 (TPC 23) in air
  tgt->tpc_dt[2][0]=src->vme_tpcs2[8][16] & 0xfff;
  tgt->tpc_dt[2][1]=src->vme_tpcs2[8][17] & 0xfff;
  tgt->tpc_dt[2][2]=src->vme_tpcs2[8][18] & 0xfff;
  tgt->tpc_dt[2][3]=src->vme_tpcs2[8][19] & 0xfff;
  tgt->tpc_lt[2][0]=src->vme_tpcs2[8][20] & 0xfff;
  tgt->tpc_rt[2][0]=src->vme_tpcs2[8][21] & 0xfff;
  tgt->tpc_lt[2][1]=src->vme_tpcs2[8][22] & 0xfff;
  tgt->tpc_rt[2][1]=src->vme_tpcs2[8][23] & 0xfff;

  //TPC 4 at S2 (TPC 24) in air
  tgt->tpc_dt[3][0]=src->vme_tpcs2[8][24] & 0xfff;
  tgt->tpc_dt[3][1]=src->vme_tpcs2[8][25] & 0xfff;
  tgt->tpc_dt[3][2]=src->vme_tpcs2[8][26] & 0xfff;
  tgt->tpc_dt[3][3]=src->vme_tpcs2[8][27] & 0xfff;
  tgt->tpc_lt[3][0]=src->vme_tpcs2[8][28] & 0xfff;
  tgt->tpc_rt[3][0]=src->vme_tpcs2[8][29] & 0xfff;
  tgt->tpc_lt[3][1]=src->vme_tpcs2[8][30] & 0xfff;
  tgt->tpc_rt[3][1]=src->vme_tpcs2[8][31] & 0xfff;

  //TPC 5 at S4 (TPC 41) in air  
  tgt->tpc_dt[4][0]=src->vme_tpcs4[0][0] & 0xfff;
  tgt->tpc_dt[4][1]=src->vme_tpcs4[0][1] & 0xfff;
  tgt->tpc_dt[4][2]=src->vme_tpcs4[0][2] & 0xfff;
  tgt->tpc_dt[4][3]=src->vme_tpcs4[0][3] & 0xfff;
  tgt->tpc_lt[4][0]=src->vme_tpcs4[0][4] & 0xfff;
  tgt->tpc_rt[4][0]=src->vme_tpcs4[0][5] & 0xfff;
  tgt->tpc_lt[4][1]=src->vme_tpcs4[0][6] & 0xfff;
  tgt->tpc_rt[4][1]=src->vme_tpcs4[0][7] & 0xfff;

  //TPC 6 at S4 (TPC 42) in air
  tgt->tpc_dt[5][0]=src->vme_tpcs4[0][8] & 0xfff;
  tgt->tpc_dt[5][1]=src->vme_tpcs4[0][9] & 0xfff;
  tgt->tpc_dt[5][2]=src->vme_tpcs4[0][10] & 0xfff;
  tgt->tpc_dt[5][3]=src->vme_tpcs4[0][11] & 0xfff;
  tgt->tpc_lt[5][0]=src->vme_tpcs4[0][12] & 0xfff;
  tgt->tpc_rt[5][0]=src->vme_tpcs4[0][13] & 0xfff;
  tgt->tpc_lt[5][1]=src->vme_tpcs4[0][14] & 0xfff;
  tgt->tpc_rt[5][1]=src->vme_tpcs4[0][15] & 0xfff;

  //TPC at S3 (TPC 31) (checkSB)
  tgt->tpc_dt[6][0]=src->vme_tpcs4[0][16] & 0xfff;
  tgt->tpc_dt[6][1]=src->vme_tpcs4[0][17] & 0xfff;
  tgt->tpc_dt[6][2]=src->vme_tpcs4[0][18] & 0xfff;
  tgt->tpc_dt[6][3]=src->vme_tpcs4[0][19] & 0xfff;
  tgt->tpc_lt[6][0]=src->vme_tpcs4[0][20] & 0xfff;
  tgt->tpc_rt[6][0]=src->vme_tpcs4[0][21] & 0xfff;
  tgt->tpc_lt[6][1]=src->vme_tpcs4[0][22] & 0xfff;
  tgt->tpc_rt[6][1]=src->vme_tpcs4[0][23] & 0xfff;

  for(int i=0; i<5; i++){
    //sc41, 21,31,accrtrig, 22
    if(0!= src->vme_tpcs4[0][24+i] & 0xfff){
      tgt->tpc_timeref[i] = src->vme_tpcs4[0][24+i] & 0xfff; //sc41
    }else{
      tgt->tpc_timeref[i] = -99999;
    }
  }
  
  /* ### SCI dE:  */
  tgt->de_41l = src->vme_main[11][0] & 0xfff;
  tgt->de_41r = src->vme_main[11][1] & 0xfff;
  tgt->de_21l = src->vme_main[11][2] & 0xfff;
  tgt->de_21r = src->vme_main[11][3] & 0xfff;
  tgt->de_42l = src->vme_main[11][4] & 0xfff; 
  tgt->de_42r = src->vme_main[11][5] & 0xfff;

  tgt->de_31l = src->vme_main[11][6] & 0xfff;
  tgt->de_31r = src->vme_main[11][7] & 0xfff;
  tgt->de_43l = src->vme_main[11][11] & 0xfff;
  tgt->de_43r = src->vme_main[11][12] & 0xfff;  
  //  tgt->de_81l = src->vme_main[11][13] & 0xfff; // changed on 21/Feb/2020 23:00
  tgt->de_81l = src->vme_main[11][15] & 0xfff; // changed on 21/Feb/2020 23:00
  tgt->de_81r = src->vme_main[11][14] & 0xfff;
  
    
  /* ### SCI times:  */
  tgt->dt_21l_21r = src->vme_frs[12][0] & 0xfff;
  tgt->dt_41l_41r = src->vme_frs[12][1] & 0xfff;
  tgt->dt_42l_42r = src->vme_frs[12][2] & 0xfff;
  tgt->dt_43l_43r = src->vme_frs[12][3] & 0xfff; 
  tgt->dt_81l_81r = src->vme_frs[12][4] & 0xfff;
  tgt->dt_21l_41l = src->vme_frs[12][5] & 0xfff;
  tgt->dt_21r_41r = src->vme_frs[12][6] & 0xfff;
  tgt->dt_42r_21r = src->vme_frs[12][7] & 0xfff;//swapped recently 28/02/2020  
  tgt->dt_42l_21l = src->vme_frs[12][8] & 0xfff;//swapped recently 28/02/2020  
  tgt->dt_21l_81l = src->vme_frs[12][9] & 0xfff;
  tgt->dt_21r_81r = src->vme_frs[12][10] & 0xfff;
  tgt->dt_22l_22r = src->vme_frs[12][11] & 0xfff;
  tgt->dt_22l_41l = src->vme_frs[12][12] & 0xfff;
  tgt->dt_22r_41r = src->vme_frs[12][13] & 0xfff;
  tgt->dt_22l_81l = src->vme_frs[12][14] & 0xfff;
  tgt->dt_22r_81r = src->vme_frs[12][15] & 0xfff;

  tgt->hall_probe_adc[0] = src->vme_frs[12][16] & 0xfff;
  tgt->hall_probe_adc[1] = src->vme_frs[12][17] & 0xfff;
  tgt->hall_probe_adc[2] = src->vme_frs[12][18] & 0xfff;
  tgt->hall_probe_adc[3] = src->vme_frs[12][19] & 0xfff;
  tgt->hall_probe_adc[4] = src->vme_frs[12][20] & 0xfff;
  tgt->hall_probe_adc[5] = src->vme_frs[12][21] & 0xfff;
 
  /* ### SCI Multihit TDC time:  */
  for(int i=0;i<10;i++){  
    tgt->tdc_sc41l[i] = src->leading_v1290_main[0][i];
    tgt->tdc_sc41r[i] = src->leading_v1290_main[1][i];
    tgt->tdc_sc21l[i] = src->leading_v1290_main[2][i];
    tgt->tdc_sc21r[i] = src->leading_v1290_main[3][i];
    tgt->tdc_sc42l[i] = src->leading_v1290_main[4][i];
    tgt->tdc_sc42r[i] = src->leading_v1290_main[5][i];
    tgt->tdc_sc43l[i] = src->leading_v1290_main[6][i];
    tgt->tdc_sc43r[i] = src->leading_v1290_main[7][i];
    tgt->tdc_sc81l[i] = src->leading_v1290_main[8][i];
    tgt->tdc_sc81r[i] = src->leading_v1290_main[9][i];
    tgt->tdc_sc31l[i] = src->leading_v1290_main[10][i];
    tgt->tdc_sc31r[i] = src->leading_v1290_main[11][i];
    tgt->tdc_sc11[i]  = src->leading_v1290_main[12][i];
  }
  

   //---MUSIC configuration. 2x TUM-MUSIC from FRS crate and 1 TRavel-MUsic from TRMU crate (2020/Jan/23, YT)
   for(int i=0;i<8;i++)
    {
      tgt->music_e1[i] = (src->vme_frs[3][i]) & 0xfff;   // 
      tgt->music_e2[i] = (src->vme_frs[3][8+i]) & 0xfff; //
      tgt->music_e3[i] = (src->vme_trmu_adc[i])        ; // Travel-MUSIC (from special VME crate)
      
      tgt->music_t1[i] = src->leading_v1290_main[16+i][0] & 0xfff; //TUM-MUSIC
      tgt->music_t2[i] = src->leading_v1290_main[24+i][0] & 0xfff; //TUM-MUSIC
      tgt->music_t3[i] = (src->vme_trmu_tdc[i]);                   //Travel-MUSIC (from special VME crate)
      
    }
    
  /* ### MUSIC temp & pressure:  */
  // tgt->music_pres[0] = 0; 
  // tgt->music_temp[0] = 0;
  // tgt->music_pres[1] = 0;
  // tgt->music_temp[1] = 0;
  // tgt->music_pres[2] = 0;
  // tgt->music_temp[2] = 0;

  // //Channeltron detectors (vme must be adjusted)
  // tgt->ct_time = src->vme3s_MT[2][0] & 0xfff;
  // tgt->ct_signal = src->vme2scaler[20] & 0xfff; 
  // tgt->ct_trigger_DU = src->vme2scaler[5]& 0xfff;
  // tgt->ct_trigger_SY = src->vme2scaler[6]& 0xfff;

  // //Electron current measurement (vme must be adjused)
  // tgt->ec_signal = src->vme0[10][1]& 0xfff;
  
  // // mrtof
  // tgt->mrtof_start = src->vme3s_MT[0][0] ;//& 0x7ffff;
  // tgt->mrtof_stopDelay = src->vme3s_MT[1][0];// & 0x7ffff;
  // tgt->mrtof_stop = src->vme3s_MT[2][0] ;//& 0x7ffff;
  
  
  return kTRUE;
}

ClassImp(TFRSSortProc)
