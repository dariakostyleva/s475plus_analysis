//
// Script writen by H. Toernqvist and S. Pietri
//with expert advice from Ziga
{
		  auto f = new TFile("export.root");
		  for (int j = 0; j < 32; ++j) {
					 std::ostringstream oss;
					 oss << "Analysis/Histograms/Unpack/VME_FRS/12/newVME01_12_" << std::setfill('0') << std::setw(2) << j;
					 auto h = (TH1F *)f->Get(oss.str().c_str());
					 if (!h) {continue; }
					 h->GetXaxis()->SetRangeUser(2000,4000);
					 auto max = h->GetMaximum();
					 if (max < 10) {
					 	continue;
					 }
					 Double_t peak_array[20];
					 size_t peak_i = 0;
					 for (int i = h->GetNbinsX(); i > 300; --i) {
								if (abs(h->GetBinContent(i) - max) < max*0.8) {
										  int ioups = i ; 
										  h->GetXaxis()->SetRangeUser(ioups-20,ioups+20);
										  auto max_bin = h->GetMaximumBin();
										  h->GetXaxis()->SetRangeUser(max_bin-3,max_bin+3);
										  peak_array[peak_i++] = h->GetMean();
										  i -= 20;
								}
					 }
					 if (peak_i <= 1) {
					 	continue;
					 }
					 Double_t dt_mean_acc = 0;
					 int dt_denom = 0;
//					 for (size_t i = 1; i < peak_i - 1; ++i) {
					 for (size_t i = 1; i < peak_i - 2; ++i) {
								auto dt = peak_array[i] - peak_array[i + 1];
								dt_mean_acc += dt;
								++dt_denom;
					 }
					 auto dt_mean = dt_mean_acc / dt_denom;
					 Double_t dt_var_acc = 0;
					 for (size_t i = 1; i < peak_i - 2; ++i) {
								auto dt = peak_array[i] - peak_array[i + 1];
								dt_var_acc += pow(dt - dt_mean, 2);
					 }
					 auto dt_std = sqrt(dt_var_acc / (dt_denom - 1));
					 auto ps_per_ch = 10e3 / dt_mean;
					 cout << "newVME01_12_" << std::setfill('0') << std::setw(2) << j << std::setfill(' ') <<
					 	": Mean=" << std::setw(9) << dt_mean <<
						"   Std=" << std::setw(9) << dt_std <<
						"   Ps/ch=" << std::setw(9) << ps_per_ch << '\n';
		  }
}
