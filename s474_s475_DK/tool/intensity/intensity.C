
//----------------------------------------------------------------------------------
// to test 2018July preparation (2018.07.07)

#define INPUTFILENAME "../../rootfile/sort_calibration_intensity_0205.root"            // TFRSSortProc output
//#define INPUTFILENAME "../../rootfile/sort_run0190_0199.root"
#define TREENAME      "SortxTree"
#define ARRAY1NAME    "FRSSortEvent.sc_long[64]"      //
#define ARRAY2NAME    "FRSSortEvent.sc_long2[32]"     //
#define DEBUG 0
#define FASTCLOCK_FREQ 100000                 //in Hz
#define FASTCLCOK_VARIABLE "FRSSortEvent.sc_long[38]" //must be src.sc_long[x] or src.sc_long2[x]
#define SLOWCLOCK_FREQ 10                    //in Hz
#define SLOWCLCOK_VARIABLE "FRSSortEvent.sc_long[36]" //
#define SPILLON_VARIABLE   "FRSSortEvent.sc_long[8]" //
#define SPILLOFF_VARIABLE  "FRSSortEvent.sc_long[9]" //
#define MAX_ANALYSIS_TIME 1800               //in sec
#define MAX_NUM_SPILL     1800               //only for max size of arrays
#define NBIN_1SEC         10                 //
//#define NUM_CH 5
//char ch_variable[NUM_CH][256] ={"FRSSortEvent.sc_long[2]","FRSSortEvent.sc_long[5]","FRSSortEvent.sc_long[6]","FRSSortEvent.sc_long[7]","FRSSortEvent.sc_long[0]"};
//char ch_name[NUM_CH][256]={"SEETRAM","SC00","SC01","SC02","IC01CurrDigt"};
//
#define NUM_CH 3
char ch_variable[NUM_CH][256] ={"FRSSortEvent.sc_long[2]","FRSSortEvent.sc_long[6]","FRSSortEvent.sc_long[0]"};
char ch_name[NUM_CH][256]={"SEETRAM","SC01","IC01CurrDigt"};
//----------------------------------------------------------------------------------



//----------------------------------------------------------------------------------
// to test with s437 data
/*
#define INPUTFILENAME "etaprime2014_0659.root" // 0653 can be also user (correlate SC02 and SC2H)
#define TREENAME      "UserxTree"
#define ARRAY1NAME    "FRSUserEvent.etap_scaler[64]"      //
#define ARRAY2NAME    "FRSUserEvent.mh_scaler[64]"     //
#define DEBUG 0
#define FASTCLOCK_FREQ 100000                 //in Hz
#define FASTCLCOK_VARIABLE "FRSUserEvent.etap_scaler[15]" //must be src.sc_long[x] or src.sc_long2[x]
#define SLOWCLOCK_FREQ 10                    //in Hz
#define SLOWCLCOK_VARIABLE "FRSUserEvent.etap_scaler[20]" //
#define SPILLON_VARIABLE   "FRSUserEvent.etap_scaler[18]" // [28] start spill has noise ?(sometimes increase by 2) use [18] spill counter
#define SPILLOFF_VARIABLE  "FRSUserEvent.etap_scaler[29]" //
#define MAX_ANALYSIS_TIME 1800               //in sec
#define MAX_NUM_SPILL     1800               //only for max size of arrays
#define NBIN_1SEC         10                 //
#define NUM_CH 5
char ch_variable[NUM_CH][256] ={"FRSUserEvent.etap_scaler[26]","FRSUserEvent.mh_scaler[14]","FRSUserEvent.mh_scaler[13]","FRSUserEvent.mh_scaler[15]","FRSUserEvent.mh_scaler[15]"};
char ch_name[NUM_CH][256]={"SEETRAM","SC00","SC01","SC02","SC2H"};
//----------------------------------------------------------------------------------
*/
//---------
// common
TChain *tc;
UInt_t *spillon_scaler;
UInt_t *spilloff_scaler;
UInt_t *fastclock_scaler;
UInt_t *slowclock_scaler;
UInt_t *ch_scaler[NUM_CH];
UInt_t array1[200];
UInt_t array2[200];
TCanvas *c1, *c2;
TH1F *rate_histo[NUM_CH];
TLine *l_on[NUM_CH][MAX_NUM_SPILL];
TLine *l_off[NUM_CH][MAX_NUM_SPILL];
TGraph *graph_simple[NUM_CH][NUM_CH];
TGraph *graph_bg_subtr[NUM_CH][NUM_CH];
double t_min, t_max; // histogram
UInt_t* getpointer(char *);
void printall(UInt_t);
void init();
bool reject_time_region(double, double);
void SetRangeAll(double, double);
void SetRangeAll(void);
void SetLogyAll(int);




void intensity(void){

  //-----
  init();

  //----
  Long64_t nentries = tc->GetEntries(); if(DEBUG){ printf("---\n nentries = %lld\n --- \n",nentries);}
  
  //----first loop-----
  UInt_t    fastclock_initial;
  UInt_t    fastclock_last;
  int       n_spillon = 0;
  int       n_spilloff = 0;
  UInt_t    spillon_last;
  UInt_t    spilloff_last;
  double spillon_time[MAX_NUM_SPILL];
  double spilloff_time[MAX_NUM_SPILL];
  
  for (Long64_t jentry=0; jentry<nentries; jentry++) {
    tc->GetEntry(jentry);
    if(DEBUG){ printall(jentry);}
    if(0==jentry){
      fastclock_initial = *fastclock_scaler;
      spillon_last      = *spillon_scaler;
      spilloff_last     = *spilloff_scaler;

    }
    if(1==(*spillon_scaler) - spillon_last){
      spillon_last = (*spillon_scaler);
      spillon_time[n_spillon] = ((double)((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ);
      n_spillon ++;
    }
    if(0<(*spilloff_scaler) - spilloff_last && (*spilloff_scaler) - spilloff_last <6){
      spilloff_last = (*spilloff_scaler);
      spilloff_time[n_spilloff] = ((double)((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ);
      n_spilloff ++;
    }
    fastclock_last = *fastclock_scaler;
    if(((double)((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ) > ((double)MAX_ANALYSIS_TIME)){
      printf("more than MAX_ANALYSIS_TIME passed from begging. analysis is done till this point.\n");
      break;
    }
  }// end of event-loop
  double total_time = ((double)(((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ));
  printf("Total Time = %f s, n_spillon = %d, n_spilloff = %d \n",total_time,n_spillon, n_spilloff);
  
  
  //----histogram bin definition----
  t_min  = -5.0;
  t_max  = ((double)((int)total_time))+5.0;
  int    t_nbin = ((int)(t_max - t_min)) * (NBIN_1SEC);
  for(int ii=0; ii<NUM_CH; ii++){
    char tempname[256]; sprintf(tempname,"h_%s",ch_name[ii]);
    rate_histo[ii] = new TH1F(tempname,tempname,t_nbin,t_min,t_max);
  }
  
  
  //----second loop-----
  UInt_t  ch_scaler_last[NUM_CH];
  double  current_time;
  int check_first_val[NUM_CH];
  for(int ii=0; ii<NUM_CH; ii++){ check_first_val[ii] = 0; }
  
  for (Long64_t jentry=0; jentry<nentries; jentry++){
    tc->GetEntry(jentry);
    //---start event loop
    current_time = ((double)((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ);
    for(int ii=0; ii<NUM_CH; ii++){
      UInt_t tempval = *(ch_scaler[ii]);
      if(0x00000000!=tempval && 0xFFFFFFFF!=tempval){ //sometimes irregular output from v830??
        //if first valid event
        if(0==check_first_val[ii]){
          ch_scaler_last[ii] = tempval; //only put current value -> last value, and set checked
          check_first_val[ii]=1;
        }else{
          if(tempval - ch_scaler_last[ii] < (UInt_t)10000000000){//skip irregular events(sometimes decrease is observed -> big number in unsigned number)
            rate_histo[ii]->Fill(current_time, tempval - ch_scaler_last[ii]);
            ch_scaler_last[ii] = tempval;
          }
        }
      }
    }
    if((double)(((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ) > ((double)MAX_ANALYSIS_TIME)){
      printf("more than MAX_ANALYSIS_TIME passed from begging. analysis is done till this point.\n");
      break;
    }
  }
  
  //------plot rate hitso-------
  double ymin_rate_pad[NUM_CH];
  double ymax_rate_pad[NUM_CH];
  for(int ii=0; ii<NUM_CH; ii++){
    c1->cd(ii+1);gPad->SetGridy(1); gPad->SetTicks(1,1);
    rate_histo[ii]->SetFillStyle(3001);
    rate_histo[ii]->SetFillColor(3);
    rate_histo[ii] ->SetXTitle("Time [s]");
    rate_histo[ii] ->GetXaxis()->CenterTitle(1);
    rate_histo[ii] ->GetXaxis()->SetLabelSize(0.07);
    rate_histo[ii] ->GetXaxis()->SetTitleSize(0.07);
    rate_histo[ii] ->GetXaxis()->SetTitleOffset(0.9);
    rate_histo[ii] ->SetYTitle(Form("Counts per (1/%d) s",NBIN_1SEC));
    rate_histo[ii] ->GetYaxis()->CenterTitle(1);
    rate_histo[ii] ->GetYaxis()->SetLabelSize(0.07);
    rate_histo[ii] ->GetYaxis()->SetTitleSize(0.07);
    rate_histo[ii] ->GetYaxis()->SetTitleOffset(0.5);
    rate_histo[ii]->Draw("HIST");
    gPad->Update();
    ymin_rate_pad[ii]=gPad->GetUymin();
    ymax_rate_pad[ii]=gPad->GetUymax();
  }

  //----plot spill on/off timing----
  for(int ii=0; ii<NUM_CH; ii++){
  c1->cd(ii+1);
    for(int j=0; j<n_spillon; j++){
      l_on[ii][j] = new TLine(spillon_time[j],ymin_rate_pad[ii],spillon_time[j],ymax_rate_pad[ii]);
      l_on[ii][j] ->SetLineWidth(1); l_on[ii][j] ->SetLineColor(2);
      l_on[ii][j] ->Draw();
    }
    for(int j=0; j<n_spillon; j++){
      l_off[ii][j] = new TLine(spilloff_time[j],ymin_rate_pad[ii],spilloff_time[j],ymax_rate_pad[ii]);
      l_off[ii][j] ->SetLineWidth(1); l_off[ii][j] ->SetLineColor(4);
      l_off[ii][j] ->Draw();
    }
  }
  
  //---------------------------------------
  int    num_ana = 0;
  double t0ana[MAX_NUM_SPILL]; // previous spill off
  double t1ana[MAX_NUM_SPILL]; //spill on of this spill
  double t2ana[MAX_NUM_SPILL]; //spill of of this spill
  double t3ana[MAX_NUM_SPILL]; //next spill on
  UInt_t integral_t0t1[NUM_CH][MAX_NUM_SPILL];
  UInt_t integral_t1t2[NUM_CH][MAX_NUM_SPILL];
  UInt_t integral_t2t3[NUM_CH][MAX_NUM_SPILL];
  double integral_simple[NUM_CH][MAX_NUM_SPILL];
  double integral_bg_subtr[NUM_CH][MAX_NUM_SPILL];
  double bg_estimated[NUM_CH][MAX_NUM_SPILL];
  double bg_rate[NUM_CH][MAX_NUM_SPILL];
  double bg_rate_graph[NUM_CH][MAX_NUM_SPILL];
  TLine  *l_bg[NUM_CH][MAX_NUM_SPILL];
  TBox   *box_main[NUM_CH][MAX_NUM_SPILL];
  
  
  if(n_spillon<4){
      printf("too small number of spills, skipp detailed analysis...\n");
      return ;
  }
  
  for(int j=1; j<n_spilloff; j++){
    if(spilloff_time[0]<spillon_time[0]){
      if(j>=n_spillon){break;}
      /*
      t0ana[num_ana] = spilloff_time[j-1];
      t2ana[num_ana] = spilloff_time[j];
      t1ana[num_ana] = spillon_time[j-1];
      t3ana[num_ana] = spillon_time[j];
      */
      t0ana[num_ana] = spilloff_time[j-1] +12./((double)(NBIN_1SEC));
      t2ana[num_ana] = spilloff_time[j]   +12./((double)(NBIN_1SEC));
      t1ana[num_ana] = spillon_time[j-1]  -1./((double)(NBIN_1SEC));
      t3ana[num_ana] = spillon_time[j]    -1./((double)(NBIN_1SEC));
    }else{
      if(j>=n_spillon-1){break;}
      t0ana[num_ana] = spilloff_time[j-1] +12./((double)(NBIN_1SEC));
      t2ana[num_ana] = spilloff_time[j]   +12./((double)(NBIN_1SEC));
      t1ana[num_ana] = spillon_time[j]    -1./((double)(NBIN_1SEC));
      t3ana[num_ana] = spillon_time[j+1]  -1./((double)(NBIN_1SEC));
    }
    for(int ii=0; ii<NUM_CH; ii++){
      box_main[ii][num_ana] = new TBox(t1ana[num_ana],ymin_rate_pad[ii],t2ana[num_ana],ymax_rate_pad[ii]);
      box_main[ii][num_ana] ->SetFillColor(5);
      box_main[ii][num_ana]->SetFillStyle(3001);
    }
    num_ana++;
  }
  if(DEBUG){
     for(int i_ana=0; i_ana<num_ana; i_ana++){
      printf("i_ana=%02d, t0,t1,t2,t3 = %f, %f, %f, %f\n",i_ana,t0ana[i_ana],t1ana[i_ana],t2ana[i_ana],t3ana[i_ana]);
    }
  }
  
  printf("start event loop again and calculate integrals.\n");
  int i0tmp = 0;
  int i1tmp = 0;
  int i2tmp = 0;
  for(int ii=0; ii<NUM_CH; ii++){
    for(int i_ana=0; i_ana<num_ana; i_ana++){
        integral_t0t1[ii][i_ana] = 0;
        integral_t1t2[ii][i_ana] = 0;
        integral_t2t3[ii][i_ana] = 0;
      }
  }
  
  for(int ii=0; ii<NUM_CH; ii++){ check_first_val[ii]=0; }
  for (Long64_t jentry=0; jentry<nentries; jentry++){
    tc->GetEntry(jentry);
    //---start event loop
    current_time = ((double)((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ);
    for(int ii=0; ii<NUM_CH; ii++){
      UInt_t tempval = *(ch_scaler[ii]);
      if(0x00000000!=tempval && 0xFFFFFFFF!=tempval){ //sometimes irregular output from v830??
        //if first valid event
        if(0==check_first_val[ii]){
          ch_scaler_last[ii] = tempval; //only put current value -> last value, and set checked
          check_first_val[ii]=1;
        }else{
          if(tempval - ch_scaler_last[ii] < (UInt_t)10000000000){//skip irregular events(sometimes decrease is observed -> big number in unsigned number)
            // now valid increase = (tempval - ch_scaler_last[ii])
            // at time = current_time
            if(t0ana[i0tmp]<=current_time && current_time<t1ana[i0tmp]){
               integral_t0t1[ii][i0tmp] += (tempval - ch_scaler_last[ii]);
               if(DEBUG)printf("time=%f, add  integral_t0t1[ii][i0tmp], i0tmp=%d, val_increase=%u\n",current_time,i0tmp,(tempval - ch_scaler_last[ii]));
            }else if(t1ana[i0tmp]<current_time && (i0tmp+1 < num_ana)){
              i0tmp++;
            }
            if(t1ana[i1tmp]<=current_time && current_time<t2ana[i1tmp]){
               integral_t1t2[ii][i1tmp] += (tempval - ch_scaler_last[ii]);
               if(DEBUG)printf("time=%f, add  integral_t1t2[ii][i1tmp], i1tmp=%d, val_increase=%u\n",current_time,i1tmp,(tempval - ch_scaler_last[ii]));
            }else if(t2ana[i1tmp]<current_time && (i1tmp+1 < num_ana)){
              i1tmp++;
            }
            
            if(t2ana[i2tmp]<=current_time && current_time<t3ana[i2tmp]){
               integral_t2t3[ii][i2tmp] += (tempval - ch_scaler_last[ii]);
              if(DEBUG)printf("time=%f, add  integral_t2t3[ii][i2tmp], i2tmp=%d, val_increase=%u\n",current_time,i2tmp,(tempval - ch_scaler_last[ii]));
            }else if(t3ana[i2tmp]<current_time && (i2tmp+1 < num_ana)){
              i2tmp++;
            }
            ch_scaler_last[ii] = tempval;
          }
        }
      }
    }
    if((double)(((*fastclock_scaler) - fastclock_initial))/((double)FASTCLOCK_FREQ) > ((double)MAX_ANALYSIS_TIME)){
      printf("more than MAX_ANALYSIS_TIME passed from begging. analysis is done till this point.\n");
      break;
    }
  }
  
  
  //----calculate-----
  for(int ii=0; ii<NUM_CH; ii++){
    for(int i_ana=0; i_ana<num_ana; i_ana++){
        integral_simple[ii][i_ana] = (double)(integral_t1t2[ii][i_ana]);
        double rate_tmp_before = ((double)integral_t0t1[ii][i_ana])/(t1ana[i_ana]-t0ana[i_ana]);
        double rate_tmp_after  = ((double)integral_t2t3[ii][i_ana])/(t3ana[i_ana]-t2ana[i_ana]);
        bg_rate[ii][i_ana]       = 0.5*(rate_tmp_before + rate_tmp_after) ;    // per second
        bg_rate_graph[ii][i_ana] = bg_rate[ii][i_ana] / ((double)(NBIN_1SEC)); // per (1/nbin) second
        integral_bg_subtr[ii][i_ana] = integral_simple[ii][i_ana] - (bg_rate[ii][i_ana] * (t2ana[i_ana]-t1ana[i_ana]));
        l_bg[ii][i_ana]  = new TLine(t1ana[i_ana],bg_rate_graph[ii][i_ana],t2ana[i_ana],bg_rate_graph[ii][i_ana]);
        l_bg[ii][i_ana]->SetLineColor(6);
        l_bg[ii][i_ana]->SetLineWidth(1);
    }
  }
  
  
  //----plot----
  for(int ii=0; ii<NUM_CH; ii++){
    c1->cd(ii+1);
    for(int i_ana=0; i_ana<num_ana; i_ana++){
      box_main[ii][i_ana]->Draw();
    }
    // overwrite main histogram
    rate_histo[ii]->Draw("same HIST");
    // again timing line
    for(int j=0; j<n_spillon; j++){
        l_on[ii][j] ->Draw();
    }
    for(int j=0; j<n_spillon; j++){
      l_off[ii][j] ->Draw();
    }
    for(int i_ana=0; i_ana<num_ana; i_ana++){
      l_bg[ii][i_ana]->Draw();
    }
  }

  //--------graphs---------
  // count valid points
  int n_count = 0;
  for(int i_ana=0; i_ana<num_ana; i_ana++){
    if(reject_time_region(t1ana[i_ana],t2ana[i_ana])){
      n_count ++;
    }
  }
  // define
  for(int i_gr=0; i_gr<NUM_CH; i_gr++){
    for(int j_gr=0; j_gr<NUM_CH; j_gr++){
      graph_simple[i_gr][j_gr] = new TGraph(n_count);
      graph_bg_subtr[i_gr][j_gr] = new TGraph(n_count);
      graph_simple[i_gr][j_gr] ->SetMarkerColor(1);
      graph_simple[i_gr][j_gr] ->SetLineColor(1);
      graph_simple[i_gr][j_gr] ->SetMarkerStyle(8);
      graph_simple[i_gr][j_gr] ->SetMarkerSize(0.6);

      graph_bg_subtr[i_gr][j_gr] ->SetMarkerColor(2);
      graph_bg_subtr[i_gr][j_gr] ->SetLineColor(2);
      graph_bg_subtr[i_gr][j_gr] ->SetMarkerStyle(4);
      graph_bg_subtr[i_gr][j_gr] ->SetMarkerSize(0.6);
    }
  }
  // fill
  n_count = 0;
  for(int i_ana=0; i_ana<num_ana; i_ana++){
    if(reject_time_region(t1ana[i_ana],t2ana[i_ana])){
      for(int i_gr=0; i_gr<NUM_CH; i_gr++){
        for(int j_gr=0; j_gr<NUM_CH; j_gr++){
            graph_simple[i_gr][j_gr]->SetPoint(n_count,integral_simple[i_gr][i_ana],integral_simple[j_gr][i_ana]);
            graph_bg_subtr[i_gr][j_gr]->SetPoint(n_count,integral_bg_subtr[i_gr][i_ana],integral_bg_subtr[j_gr][i_ana]);
        }
      }
      n_count ++;
    }
  }
  //----draw----
  for(int i_gr=0; i_gr<NUM_CH; i_gr++){
      for(int j_gr=0; j_gr<NUM_CH; j_gr++){
        c2->cd(1+i_gr+NUM_CH*j_gr); gPad->SetTicks(1,1);
        graph_simple[i_gr][j_gr]->SetTitle(0);
        graph_simple[i_gr][j_gr]->GetXaxis()->SetTitle(Form("%s / spill",ch_name[i_gr]));
        graph_simple[i_gr][j_gr]->GetXaxis()->CenterTitle(1);
        graph_simple[i_gr][j_gr]->GetYaxis()->SetTitle(Form("%s / spill",ch_name[j_gr]));
        graph_simple[i_gr][j_gr]->GetYaxis()->CenterTitle(1);
        graph_bg_subtr[i_gr][j_gr]->SetTitle(0);
        graph_bg_subtr[i_gr][j_gr]->GetXaxis()->SetTitle(Form("%s / spill",ch_name[i_gr]));
        graph_bg_subtr[i_gr][j_gr]->GetXaxis()->CenterTitle(1);
        graph_bg_subtr[i_gr][j_gr]->GetYaxis()->SetTitle(Form("%s / spill",ch_name[j_gr]));
        graph_bg_subtr[i_gr][j_gr]->GetYaxis()->CenterTitle(1);
        if(i_gr!=j_gr){
          graph_simple[i_gr][j_gr]->Draw("AP");
          c2->Update();
          double xmaxtemp = graph_simple[i_gr][j_gr]->GetXaxis()->GetXmax();
          double ymaxtemp = graph_simple[i_gr][j_gr]->GetYaxis()->GetXmax();
          graph_simple[i_gr][j_gr]->GetXaxis()->SetLimits(0,xmaxtemp*1.1);
          graph_simple[i_gr][j_gr]->GetXaxis()->SetRangeUser(0,xmaxtemp*1.1);
          graph_simple[i_gr][j_gr]->GetYaxis()->SetLimits(0,ymaxtemp*1.1);
          graph_simple[i_gr][j_gr]->GetYaxis()->SetRangeUser(0,ymaxtemp*1.1);
          graph_simple[i_gr][j_gr]->Draw("AP");
          graph_bg_subtr[i_gr][j_gr]->Draw("P");
        }
    }
  }

  //----output-----
  TFile fout("intensity_out.root","RECREATE");
    c1->Write();
    c2->Write();
    for(int ii=0; ii<NUM_CH; ii++){
      rate_histo[ii]->Write();
    }
    for(int i_gr=0; i_gr<NUM_CH; i_gr++){
      for(int j_gr=0; j_gr<NUM_CH; j_gr++){
        graph_simple[i_gr][j_gr]->Write(Form("graph_simple_%s_%s",ch_name[i_gr],ch_name[j_gr]));
        graph_bg_subtr[i_gr][j_gr]->Write(Form("graph_subtr_%s_%s",ch_name[i_gr],ch_name[j_gr]));
      }
    }
  fout.Close();
  c1->Print("c1.pdf");
  c2->Print("c2.pdf");
  return ;
}



UInt_t* getpointer(char *variable_input){
    char str[256]; strcpy(str,variable_input);
    char str1[256]; sprintf(str1,"%s",ARRAY1NAME);
    char str2[256]; sprintf(str2,"%s",ARRAY2NAME);
    char* tmp;
    tmp = strtok(str,"[");
    tmp = strtok(NULL,"]");
    strtok(str1,"[");
    strtok(str2,"[");
    printf("str, tmp, str1, str2 = %s %s %s %s\n",str, tmp, str1, str2 );
    if(0==strcmp(str,str1)){
      return array1+atoi(tmp);
    }else if(0==strcmp(str,str2)){
      return array2+atoi(tmp);
    }else{
      printf("ERROR in UInt_t* getpointer()\n");
      exit(-1);
    }
    return 0;
}

void printall(Long64_t iev){
      printf("iev=%lld: (", iev);
      for(int jj=0; jj<NUM_CH; jj++){
        printf("%s ",ch_variable[jj]);
      }
      printf(")\n = (");
      for(int jj=0; jj<NUM_CH; jj++){
        printf("%u ",*(ch_scaler[jj]));
      }
      printf("%u ",*(spillon_scaler));
      printf("%u ",*(spilloff_scaler));
      printf("%u ",*(fastclock_scaler));
      printf(")\n");
      return;
}

void init(){
  gStyle->SetOptStat(0);
  gStyle->SetTextSize(14);
  gStyle->SetTitleFontSize(0.07);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadBottomMargin(0.15);
  
  tc = new TChain(TREENAME);
  tc->Add(INPUTFILENAME);
  tc->SetMakeClass(1);
  tc->SetBranchAddress(ARRAY1NAME, array1); //
  tc->SetBranchAddress(ARRAY2NAME, array2); //
  spillon_scaler  = getpointer((char*)SPILLON_VARIABLE);
  spilloff_scaler = getpointer((char*)SPILLOFF_VARIABLE);
  fastclock_scaler = getpointer((char*)FASTCLCOK_VARIABLE);
  slowclock_scaler = getpointer((char*)SLOWCLCOK_VARIABLE);
  for(int ii=0; ii< NUM_CH ; ii++){
    ch_scaler[ii] = getpointer(ch_variable[ii]);
  }
  c2 = new TCanvas("c2","c2",0,0,1200,900);
  c2->Divide(NUM_CH,NUM_CH,0.002,0.002);
  c1 = new TCanvas("c1","c1",0,0,900,900);
  c1->Divide(1,NUM_CH,0.002,0.002);
  return;
}

void SetLogyAll(int val){
  for(int ii=0; ii<NUM_CH; ii++){
    c1->cd(ii+1);
    gPad->SetLogy(val);
  }
  c1->Update();
  return;
}

void SetRangeAll(void){
  return SetRangeAll(t_min, t_max);
}

void SetRangeAll(double valmin, double valmax){
  for(int ii=0; ii<NUM_CH; ii++){
    c1->cd(ii+1);
    rate_histo[ii]->GetXaxis()->SetRangeUser(valmin,valmax);
    c1->Modified();
    c1->Update();
    gPad->Modified();
    gPad->Update();
  }
  return;
}

bool reject_time_region(double spill_start_time, double spill_end_time){
  // if we need to reject certain time-region in the middle of the file, write here.
  // c1 (histograms, preparation of data) will be anyway done for whole region
  // this condition will be considered in c2 (graph) anaysis.
  return true;
}


