void drawResults(TString fileName, TString treeName, Int_t nEvents) {
  
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

  TGraph *g_sigma1 = new TGraph("./result/s_graph_1.txt");
  g_sigma1->SetTitle("SST1E_gsi06;strip;sigma");

  TGraph *g_sigma2 = new TGraph("./result/s_graph_2.txt");
  g_sigma2->SetTitle("SST2E_gsi04;strip;sigma");

  TGraph *g_sigma3 = new TGraph("./result/s_graph_3.txt");
  g_sigma3->SetTitle("SST3E_gsi08;strip;sigma");

  TGraph *g_mean1 = new TGraph("./result/m_graph_1.txt");
  g_mean1->SetTitle("SST1E_gsi06;strip;deposit");

  TGraph *g_mean2 = new TGraph("./result/m_graph_2.txt");
  g_mean2->SetTitle("SST2E_gsi04;strip;deposit");

  TGraph *g_mean3 = new TGraph("./result/m_graph_3.txt");
  g_mean3->SetTitle("SST3E_gsi08;strip;deposit");

  TCanvas *c1 = new TCanvas("c1","analysis window",1800,1000);
  c1->Divide(3,3);

  c1->cd(1);
  g_mean1->Draw("AL");
  c1->cd(4);
  g_mean2->Draw("AL");
  c1->cd(7);
  g_mean3->Draw("AL");

  c1->cd(2);
  g_sigma1->Draw("AL");
  c1->cd(5);
  g_sigma2->Draw("AL");
  c1->cd(8);
  g_sigma3->Draw("AL");

  c1->cd(3);
  TH2I * amp1= new TH2I("amp1","SST1E_gsi06;strip num;deposit",1024,0,1024,4096,0,4096 );
  t->Draw("SST1E:SST1I >> amp1","","col", nEvents, 0);
  c1->cd(6);
  TH2I * amp2= new TH2I("amp2","SST2E_gsi04;strip num;deposit",1024,0,1024,4096,0,4096 );
  t->Draw("SST2E:SST2I >> amp2","","col", nEvents, 0);
  c1->cd(9);
  TH2I * amp3= new TH2I("amp3","SST3E_gsi08;strip num;deposit",1024,0,1024,4096,0,4096 );
  t->Draw("SST3E:SST3I >> amp3","","col", nEvents, 0);

  c1->Print("./figures/fig.png");

  return;
}
