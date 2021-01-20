void pedAnalyse(TString inputFile, TString outputFile, TString treeName, Int_t nEvents) {
    
  TString t;
  Int_t counter;
  TString s_ped1[1024],s_ped2[1024],s_ped3[1024];
  Int_t ped1[1024],ped2[1024],ped3[1024];

    ifstream input("sidped_daq.txt");
    if (input.is_open()) {
      while (!input.eof()) {
        input >> t;
        if (t=="40120000") { // 2 DETECTOR NAME
          cout << "40120000" << endl;
          for (Int_t i=0;i<1024;i++) {
            input >> s_ped2[i];
            sscanf(s_ped2[i], "%x", ped2+i);
          }
        }

        if (t=="40220000") { // 3 DETECTOR NAME
          cout << "40220000" << endl;
          for (Int_t i=0;i<1024;i++) {
            input >> s_ped3[i];
            sscanf(s_ped3[i], "%x", ped3+i);
          } 
        } 
       
        if (t=="41120000") { // 1 DETECTOR NAME
          cout << "41120000" << endl;
          for (Int_t i=0;i<1024;i++) {
            input >> s_ped1[i];
            sscanf(s_ped1[i], "%x", ped1+i);
          } 
        } 
           
      }
    }

    ofstream out_ped1,out_ped2,out_ped3;
    out_ped1.open("result/ped1.txt");
    out_ped2.open("result/ped2.txt");
    out_ped3.open("result/ped3.txt");

    for (Int_t i=0;i<1024;i++) {
      out_ped1 << i << " " << ped1[i] << endl;
      out_ped2 << i << " " << ped2[i] << endl;
      out_ped3 << i << " " << ped3[i] << endl;
    }

    out_ped1.close();
    out_ped2.close();
    out_ped3.close();

    TFile *fin = new TFile(inputFile.Data());
    TTree *inTree = (TTree*)fin->Get(treeName.Data());

    Int_t SST1I[1024], SST1E[1024];
    Int_t SST2I[1024], SST2E[1024];
    Int_t SST3I[1024], SST3E[1024];

    inTree->SetBranchAddress("SST1I",&SST1I);
    inTree->SetBranchAddress("SST1E",&SST1E);
    inTree->SetBranchAddress("SST2I",&SST2I);
    inTree->SetBranchAddress("SST2E",&SST2E);
    inTree->SetBranchAddress("SST3I",&SST3I);
    inTree->SetBranchAddress("SST3E",&SST3E);

    TFile *fout = new TFile(outputFile.Data(),"RECREATE");
    TTree *outTree = new TTree(treeName.Data(),"data deduced by pedestals");

    outTree->Branch("SST1I.",&SST1I,"SST1I[1024]/I");
    outTree->Branch("SST1E.",&SST1E,"SST1E[1024]/I");
    outTree->Branch("SST2I.",&SST2I,"SST2I[1024]/I");
    outTree->Branch("SST2E.",&SST2E,"SST2E[1024]/I");
    outTree->Branch("SST3I.",&SST3I,"SST3I[1024]/I");
    outTree->Branch("SST3E.",&SST3E,"SST3E[1024]/I");

    for (Int_t i=0;i<nEvents;i++) {
      inTree->GetEntry(i);

      for (Int_t i=0;i<1024;i++) {
        SST1E[i] = SST1E[i]-ped1[i]/10;
        SST2E[i] = SST2E[i]-ped2[i]/10;
        SST3E[i] = SST3E[i]-ped3[i]/10;
      }

      outTree->Fill();
    }

    fout->cd();
    outTree->Write();
    fout->Close();

}   