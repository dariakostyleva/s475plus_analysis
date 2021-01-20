void mean(TString fileName, TString treeName, Int_t nEvents , Int_t nDet){

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

  TCanvas *c1 = new TCanvas("c1","mean distribution",1000,1000);
  c1->cd();

  TString hdraw,hcut;

  TString textout;
  textout.Form("result/m_graph_%d.txt",nDet);
  ofstream fout;
  fout.open(textout.Data());

  for(Int_t nCh=0;nCh<1024;nCh++) {

    hdraw.Form("SST%dE",nDet);
    hcut.Form("SST%dI==%d",nDet,nCh+1);
    t->Draw(hdraw.Data(),hcut.Data(),"",nEvents,0);
    htemp = (TH1F*)gPad->GetPrimitive("htemp");

    fout << nCh << " " << htemp->GetMean() << endl;
  }

  fout.close();

}