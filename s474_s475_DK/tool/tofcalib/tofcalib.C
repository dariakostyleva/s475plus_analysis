#include <stdio.h>
#include <time.h>

Double_t f_pol1 (Double_t *x, Double_t *par){
    return par[0] + par[1]*x[0];
}

const int maxpoint = 10;
double beta_in[maxpoint];
double tofraw_in[maxpoint];

void tofcalib(){
    printf("\n");
    printf("============================================\n");
    printf("     TOF calib parameters for FRS Go4   \n");
    printf("============================================\n");
    printf("Formulae:\n");
    printf("    TOF [ps] = - TAC_ps + offset \n");
    printf("    beta     = L_per_c_ps / TOF [ps] \n");
    printf("============================================\n");
    printf("In the TOF calibrations, (beta, TAC_ps)\n");
    printf("are obtained for several settings, and\n");
    printf("the goal is to determine free parameters\n");
    printf("(offset and L_per_c_ps). L_per_c_ps should \n");
    printf(" be ~120000 ps (S2-S4 ~36m) \n");
    printf(" or ~xx0000 ps (S2-S8 ~xxxm).\n");
    printf("============================================\n");
    int npoint = 0;
    TGraph *gr = new TGraph();

    while(npoint<maxpoint){
        double temp_beta = 0.0;
        double temp_tofraw = 0.0;
        printf("Type beta and TAC_ps.  (if no more input, give just 0 0)\n");
        printf("example:  x.xxxx ttttt.ttt \n");
        scanf("%lf %lf", &temp_beta, &temp_tofraw);
        printf("check = %f %f\n", temp_beta, temp_tofraw);
        beta_in[npoint] = temp_beta;
        tofraw_in[npoint] = temp_tofraw;
        printf("-------------------------\n");
        if(0==temp_beta){ break; }
        // [beta * TAC_ps] = offset [beta]  - L_per_c_ps
        // Xpoint = beta,
        // Ypoint = beta * TAC_ps,
        // p1 = offset
        // p0 = -L_per_c_ps
        gr->SetPoint(npoint,temp_beta,temp_tofraw*temp_beta);
        npoint++;
    }

    // irregular case
    if(npoint>=maxpoint){  printf("Too many input points.... Increase maxpoint in the code\n");  exit(0); }
    if(npoint<2){  printf("Too little input points.... Try again\n"); exit(0); }
    
    TCanvas *c1 = new TCanvas("c1","c1",0,0,600,800);
    TLatex *text = new TLatex();
    text->SetTextFont(43);
    text->SetTextSize(16);
    
    c1->Divide(1,2);
    c1->cd(1);
    gPad->SetTicks(1,1);
    gPad->SetGrid(1,1);
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(1.4);
    gr->SetMarkerColor(4);
    gr->Draw("AP");
    TF1 *f1 = new TF1("f1",f_pol1,-999999,999999,2);
    // if you want fix parameter
    // f1->FixParameter(0,-284296.68); //fix length (ipar=0, value= - length_in_ps)

    gr->Fit(f1);
    f1 -> SetLineColor(2);
    f1 -> SetLineWidth(2);
    double offset     = f1->GetParameter(1);
    double L_per_c_ps = -1.0 * (f1->GetParameter(0));
    gr->GetXaxis()->SetTitle("beta_reference");
    gr->GetYaxis()->SetTitle("beta_reference * TAC_ps");
    gr->GetXaxis()->CenterTitle(1);
    gr->GetYaxis()->CenterTitle(1);
    text->DrawTextNDC(0.14, 0.8, "p1(slope) = offset");
    text->DrawLatexNDC(0.14, 0.75, "p0        = #minus L_per_c_ps");

    // information about date
    time_t timer;
    struct tm *local;
    int year, month, day, hour, minute, second;
    timer = time(NULL);
    local = localtime(&timer);
    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    day = local->tm_mday;
    hour = local->tm_hour;
    minute = local->tm_min;
    second = local->tm_sec;
     
    c1->cd(2);
    text->DrawTextNDC(0.14, 0.9, Form("---- TOF calibration (%04d/%02d/%02d %02d:%02d) ----",year, month, day, hour, minute));
    text->DrawTextNDC(0.14, 0.85, Form("offset     = %.1f ; //ps",offset));
    text->DrawTextNDC(0.14, 0.80, Form("L_per_c_ps = %.1f ; //ps",L_per_c_ps));

    text->DrawTextNDC(0.14, 0.70, "Input points (beta, tac_ps) are ");
    for(int ii=0; ii<npoint; ii++){
        text->DrawTextNDC(0.14, 0.65-((double)ii)*0.05, Form("  (%.5f,  %.3f)",beta_in[ii],tofraw_in[ii]));
    }
    c1->Print(Form("c1_%04d%02d%02d_%02d%02d.pdf",year, month, day, hour, minute));
    return;
}
