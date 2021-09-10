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
  frs_tree->AddFriend("h101",file2.Data()); 
  // now all data is in FRS tree

  // create file to save merged data in
  TFile *out = new TFile(file3.Data(),"RECREATE");
  // copy tree together with its new friend
  TTree *merged_tree = frs_tree->CloneTree();
  // write a file
  out->Write();
}
