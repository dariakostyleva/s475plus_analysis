// *** Author: Daria, Jan 2021 *** //
// *** Macro to combine data from standard FRS detectors with data from silicon micro-strip detectors (DSSD) *** //
// *** Use with ROOT 6 *** //

#include<iostream>
#include<fstream>

using namespace std;

void friend_trees(TString file1, TString file2, TString file3){

  // open file with FRS data (upacked using go4)
  TFile *frs_file = new TFile(file1.Data());
  // take tree from file with FRS data                                                   
  TTree *frs_tree = (TTree*)frs_file->Get("AnalysisxTree");
  // friend tree with FRS data with the tree with DSSD data (DSSD data unpacked using ucesb)
  TFriendElement *ucesb = frs_tree->AddFriend("h101",file2.Data()); 
  // now all data is in FRS tree

  // create file to save data in
  TFile *out = new TFile(file3.Data(),"RECREATE");

  //some trick needed to read the tree
  frs_tree->SetMakeClass(1);

  // *** defining variables and arrays ***
  // data for identification of isotope 
  Float_t AoQ, z2; 
  // arrays to hold strip number and energy
  Int_t SST1I[1024], SST1E[1024]; // 1 - detector gsi06 (double-check the numbering!)
  Int_t SST2I[1024], SST2E[1024]; // 2 - detector gsi04
  Int_t SST3I[1024], SST3E[1024]; // 3 - detector gsi08
  // vector to hold event numbers aftering gating on ID plot
  vector <Int_t> sel_ev;
  std::fill(sel_ev.begin(), sel_ev.end(), 0.0);
  // *****************************************

  // *** reading out the tree in the above defined variables and arrays ***
  frs_tree->SetBranchAddress("FRSAnlEvent.id_AoQ",&AoQ);
  frs_tree->SetBranchAddress("FRSAnlEvent.id_z2",&z2);
  frs_tree->SetBranchAddress("SST1I",SST1I);
  frs_tree->SetBranchAddress("SST1E",SST1E);
  frs_tree->SetBranchAddress("SST2I",SST2I);
  frs_tree->SetBranchAddress("SST2E",SST2E);
  frs_tree->SetBranchAddress("SST3I",SST3I);
  frs_tree->SetBranchAddress("SST3E",SST3E);
  // *****************************************

  // *** creating some histos ***
  TH1F *h_AoQ   = new TH1F("h_AoQ","Mass-over-charge ratio",100,0,4);
  TH1F *h_z2   = new TH1F("h_z2","Atomic number",100,30,40);
  TH2F *h_id   = new TH2F("h_id","ID plot",500,1.9,2.4,500,30,40);
  TH2F *h_det1   = new TH2F("h_det1","Detector 1 (gsi06), all events",1024,0,1024,1000,-1000,3500);
  TH2F *h_det1_cut   = new TH2F("h_det1_cut","Detector 1 (gsi06) after selection ",1024,0,1024,1000,-1000,3500);
  TH2F *h_id_cut   = new TH2F("h_id_cut","ID plot after selection ",500,1.9,2.4,500,30,40);
  

  // ****************************

  // *** loop over entries to the tree (i.e. loop over events)
  Int_t nentries = frs_tree->GetEntries();
  cout << "Number of entries in combined file: " << nentries << endl;
  for (Int_t i=0; i<100000; i++) {
    if(i%10000 == 0) printf("Event: %i\n",i);
    frs_tree->GetEntry(i);
    h_AoQ->Fill(AoQ);
    h_z2->Fill(z2);
    h_id->Fill(AoQ,z2);
    
    // loop over strip number
    for (Int_t j=0; j<1024; j++) {
        h_det1->Fill(SST1I[j],SST1E[j]); // histo filled with all events
        //cout << "for event " << i << " SST1I[j] = " << SST1I[j] << ", SST1E[j] = " << SST1E[j] << endl;
    }

    // selection of one isotope in ID plot, may be 68Se, to be checked
    if(AoQ > 1.98 && AoQ < 2.01 && z2 > 35.4 && z2 < 36.5) {
      sel_ev.push_back(i); // filling vector with number of strips fallen into selection
      for (Int_t j=0; j<1024; j++) {
        h_det1_cut->Fill(SST1I[j],SST1E[j]); // histo filled with selected events
      }
      h_id_cut->Fill(AoQ,z2);
    }
  }
  // *** end of loop over entries **************************
  cout << "Number of selected ions is " << sel_ev.size() << endl;

  // *** drawing histograms in canvas ***
  TCanvas *c = new TCanvas("c","Identification",0,0,1400,1100);
  c->Divide(2,3);
  c->cd(1);
  h_AoQ->GetXaxis()->SetTitleSize(0.05);
  h_AoQ->GetXaxis()->CenterTitle();
  h_AoQ->GetXaxis()->SetTitle("A/Q");
  h_AoQ->Draw();
  c->cd(2);
  h_det1->GetXaxis()->SetTitleSize(0.05);
  h_det1->GetXaxis()->CenterTitle();
  h_det1->GetXaxis()->SetTitle("Strip number"); 
  h_det1->GetYaxis()->SetTitleSize(0.05);
  h_det1->GetYaxis()->CenterTitle();
  h_det1->GetYaxis()->SetTitle("Energy deposit (ADC units)");   
  h_det1->Draw("col");
  c->cd(3);
  h_z2->GetXaxis()->SetTitleSize(0.05);
  h_z2->GetXaxis()->CenterTitle();
  h_z2->GetXaxis()->SetTitle("Z");
  h_z2->Draw();
  c->cd(4);
  h_id->GetXaxis()->SetTitleSize(0.05);
  h_id->GetXaxis()->CenterTitle();
  h_id->GetXaxis()->SetTitle("A/Q");
  h_id->GetYaxis()->SetTitleSize(0.05);
  h_id->GetYaxis()->CenterTitle();
  h_id->GetYaxis()->SetTitle("Z");
  h_id->Draw("col");
  c->cd(5);
  h_det1_cut->GetXaxis()->SetTitleSize(0.05);
  h_det1_cut->GetXaxis()->CenterTitle();
  h_det1_cut->GetXaxis()->SetTitle("Strip number"); 
  h_det1_cut->GetYaxis()->SetTitleSize(0.05);
  h_det1_cut->GetYaxis()->CenterTitle();
  h_det1_cut->GetYaxis()->SetTitle("Energy deposit (ADC units)");   
  h_det1_cut->Draw("col");
  c->cd(6);
  h_id_cut->Draw("col");
  // ************************************

  // just some printout of the strips fired for the selected isotope
  for (Int_t i = 0; i < sel_ev.size() ; i++) {
    //cout << "Selected event " << sel_ev[i] << endl; 
  }

  // *** creating graphs to draw num selected events in event-by-event mode***
  Int_t num = 12;
  // *** drawing graphs in canvas ***
  TCanvas *c1 = new TCanvas("c1","Detector 1 (gsi06)",1100,0,1400,1400);
  c1->Divide(3,4);
  TGraph** g1 = new TGraph*[num];
  for(Int_t i = 0; i < num; i++) {
    frs_tree->GetEntry(sel_ev[i]);
    g1[i] = new TGraph(1024,SST1I,SST1E);
    g1[i]->SetTitle(TString::Format("Detector 1 (gsi06), event %d for selected ion", i));
    g1[i]->GetXaxis()->SetTitleSize(0.05);
    g1[i]->GetXaxis()->SetTitle("Strip number");
    g1[i]->GetXaxis()->CenterTitle();
    g1[i]->GetYaxis()->SetTitleSize(0.05); 
    g1[i]->GetYaxis()->CenterTitle();   
    g1[i]->GetYaxis()->SetTitle("Energy deposit (ADC units)");     
    c1->cd(i+1);
    g1[i]->Draw();
  }

  TCanvas *c2 = new TCanvas("c2","Detector 2 (gsi04)",1100,0,1400,1400);
  c2->Divide(3,4);
  TGraph** g2 = new TGraph*[num];
  for(Int_t i = 0; i < num; i++) {
    frs_tree->GetEntry(sel_ev[i]);
    g2[i] = new TGraph(1024,SST2I,SST2E);
    g2[i]->SetTitle(TString::Format("Detector 2 (gsi04), event %d for selected ion", i));
    g2[i]->GetXaxis()->SetTitleSize(0.05);
    g2[i]->GetXaxis()->SetTitle("Strip number");
    g2[i]->GetXaxis()->CenterTitle();
    g2[i]->GetYaxis()->SetTitleSize(0.05); 
    g2[i]->GetYaxis()->CenterTitle();   
    g2[i]->GetYaxis()->SetTitle("Energy deposit (ADC units)");     
    c2->cd(i+1);
    g2[i]->Draw();
  }

  TCanvas *c3 = new TCanvas("c3","Detector 3 (gsi08)",1100,0,1400,1400);
  c3->Divide(3,4);
  TGraph** g3 = new TGraph*[num];
  for(Int_t i = 0; i < num; i++) {
    frs_tree->GetEntry(sel_ev[i]);
    g3[i] = new TGraph(1024,SST3I,SST3E);
    g3[i]->SetTitle(TString::Format("Detector 3 (gsi08), event %d for selected ion", i));
    g3[i]->GetXaxis()->SetTitleSize(0.05);
    g3[i]->GetXaxis()->SetTitle("Strip number");
    g3[i]->GetXaxis()->CenterTitle();
    g3[i]->GetYaxis()->SetTitleSize(0.05); 
    g3[i]->GetYaxis()->CenterTitle();   
    g3[i]->GetYaxis()->SetTitle("Energy deposit (ADC units)");     
    c3->cd(i+1);
    g3[i]->Draw();
  }
  // ************************************
  c->Write();
  c1->Write();
  c2->Write();
  c3->Write();
  frs_file->Close();
  out->Close();
}
