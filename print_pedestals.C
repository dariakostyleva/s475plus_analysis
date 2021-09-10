#include<iostream>
#include<fstream>

using namespace std;

void print_pedestals(){

  TFile *file = new TFile("/data.local2/s475plus_data/root/converted/pedestaL_after_exp_cmp_3946_ucesb.root");
  // take tree from file with FRS data                                                   
  TTree *tree = (TTree*)file->Get("h101");
 
  // create file to save data in
  //TFile *out = new TFile(file3.Data(),"RECREATE");

  //some trick needed to read the tree
  tree->SetMakeClass(1);

  // *** defining variables and arrays ***

  // arrays to hold strip number and energy
  Int_t SST1I[1024], SST1E[1024]; // 1 - detector gsi06 (double-check the numbering!)
  Int_t SST2I[1024], SST2E[1024]; // 2 - detector gsi04
  Int_t SST3I[1024], SST3E[1024]; // 3 - detector gsi08
  Int_t sum[1024] = {0};
  Float_t mean_SST2E[1024];

  // *****************************************

  // *** reading out the tree in the above defined variables and arrays ***
  tree->SetBranchAddress("SST1I",SST1I);
  tree->SetBranchAddress("SST1E",SST1E);
  tree->SetBranchAddress("SST2I",SST2I);
  tree->SetBranchAddress("SST2E",SST2E);
  tree->SetBranchAddress("SST3I",SST3I);
  tree->SetBranchAddress("SST3E",SST3E);
  //TH1I *h1 = new TH1I("h1", "h1 title", 100, 0, 2000);
  TH1F* h1[1024]; TH1F* h2[1024]; TH1F* h3[1024];
  char hname1[20], hname2[20], hname3[20];
  TH2F* h_sst1 = new TH2F("h_sst1","GSI06",1024,0,1023,100,0,1000);
  TH2F* h_sst2 = new TH2F("h_sst2","GSI04",1024,0,1023,100,0,1000);
  TH2F* h_sst3 = new TH2F("h_sst3","GSI08",1024,0,1023,100,0,1000);

  Int_t nentries = tree->GetEntries();
  cout << "Number of entries in file: " << nentries << endl;
  for (Int_t i=0; i<15; i++) {
    if(i%10000 == 0) printf("Event: %i\n",i);
    tree->GetEntry(i);
    //TGraph* gr = new TGraph(1024,SST2I,SST2E);
    //gr->Draw();
    for (Int_t j=0; j<1024; j++) {
      sprintf(hname1,"h1_%d_%d",j,i);
      sprintf(hname2,"h2_%d_%d",j,i);
      sprintf(hname3,"h3_%d_%d",j,i);
      sum[j] += SST2E[j];
      h1[j] = new TH1F(hname1,"",100,0,2000);
      h2[j] = new TH1F(hname2,"",100,0,2000);
      h3[j] = new TH1F(hname3,"",100,0,2000);
      h1[j]->Fill(SST1E[j]);
      h2[j]->Fill(SST2E[j]);
      h3[j]->Fill(SST3E[j]);
    }
  }

  for (Int_t j=0; j<1024; j++) {

      //mean_SST2E[j] = sum[j]/5000;
  	  //printf("Detector SST2, strip %d, pedestal %f\n",j,mean_SST2E[j]);
      printf("%d %f\n",j,h2[j]->GetMean());     
      h_sst1->Fill(SST1I[j],h1[j]->GetMean());
      h_sst2->Fill(SST2I[j],h2[j]->GetMean());
      h_sst3->Fill(SST3I[j],h3[j]->GetMean());
  }
  
  TCanvas *c = new TCanvas();
  c->Divide(1,3);
  c->cd(1);
  h_sst2->GetXaxis()->SetTitleSize(0.05);
  h_sst2->GetXaxis()->SetTitle("Strip number");
  h_sst2->GetXaxis()->CenterTitle();
  h_sst2->GetYaxis()->SetTitleSize(0.05); 
  h_sst2->GetYaxis()->CenterTitle();   
  h_sst2->GetYaxis()->SetTitle("Energy deposit (ADC units)");   
  h_sst2->SetMarkerSize(7);  
  h_sst2->Draw();
  c->cd(2);
  h_sst3->GetXaxis()->SetTitleSize(0.05);
  h_sst3->GetXaxis()->SetTitle("Strip number");
  h_sst3->GetXaxis()->CenterTitle();
  h_sst3->GetYaxis()->SetTitleSize(0.05); 
  h_sst3->GetYaxis()->CenterTitle();   
  h_sst3->GetYaxis()->SetTitle("Energy deposit (ADC units)"); 
  h_sst3->SetMarkerSize(7);
  h_sst3->Draw();
  c->cd(3);
  h_sst1->GetXaxis()->SetTitleSize(0.05);
  h_sst1->GetXaxis()->SetTitle("Strip number");
  h_sst1->GetXaxis()->CenterTitle();
  h_sst1->GetYaxis()->SetTitleSize(0.05); 
  h_sst1->GetYaxis()->CenterTitle();   
  h_sst1->GetYaxis()->SetTitle("Energy deposit (ADC units)"); 
  h_sst1->SetMarkerSize(7);
  h_sst1->Draw();
  
}