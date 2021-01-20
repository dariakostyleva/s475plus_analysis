void sigma(TString fileName, TString treeName, Int_t nEvents , Int_t nDet){

  // SET THIS VALUES: input file, treeName, num of the processing events
  // TString fileName("/media/ivan/data/gsi_2020/data/file_030320_raw_ucesb.root");
  // TString treeName("h101");
  // Int_t nEvents = 100;

  TFile *inFile = new TFile(fileName.Data(),"READ");
  if(inFile->IsZombie()) {
    cerr << "No input file: " << fileName.Data() << endl;
    return;
  }

  TTree *t = (TTree*)inFile->Get(treeName.Data());
  if(t->IsZombie()) {
    cerr << "No tree with name: " << treeName.Data() << " in the file: " << fileName.Data() << endl;
    return;
  }

  TH1F *htemp;  
  TF1 *f;

  TCanvas *c1 = new TCanvas("c1","sigma distribution",1000,1000);
  c1->cd();

  TString hdraw,hcut;

  TString textout;
  textout.Form("result/s_graph_%d.txt",nDet);
  ofstream fout;
  fout.open(textout.Data());

  for(Int_t nCh=0;nCh<1024;nCh++) {

    if (nCh%100==0 && nDet==1) cout << nCh/10 << "%" << endl;

    hdraw.Form("SST%dE",nDet);
    hcut.Form("SST%dI==%d",nDet,nCh+1);
    t->Draw(hdraw.Data(),hcut.Data(),"",nEvents,0);
    htemp = (TH1F*)gPad->GetPrimitive("htemp");

    fout << nCh << " " << htemp->GetRMS() << endl;
  }

  fout.close();

}