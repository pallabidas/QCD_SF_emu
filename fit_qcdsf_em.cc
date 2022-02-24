#include <TLatex.h>
#include <TGraph.h>

#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TMatrixD.h"
#include "TMinuit.h"

double square(double x)
{
    return x*x;
}

void makeBinsInteger(TH1* histogram_pass, TH1* histogram_fail)
{
    assert(histogram_pass->GetNbinsX() == histogram_fail->GetNbinsX());
    int numBins = histogram_pass->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
        if (histogram_pass->GetBinContent(iBin)<0){ histogram_pass->SetBinContent(iBin,0); histogram_pass->SetBinError(iBin,0);}
        if (histogram_fail->GetBinContent(iBin)<0){ histogram_fail->SetBinContent(iBin,0); histogram_fail->SetBinError(iBin,0);}
        double binContent_sum = histogram_pass->GetBinContent(iBin) + histogram_fail->GetBinContent(iBin);
        double binError2_sum = square(histogram_pass->GetBinError(iBin)) + square(histogram_fail->GetBinError(iBin));
        double binError_sum = TMath::Sqrt(binError2_sum);
        if ( binContent_sum > 0. && binError_sum > 0. ) {
            double nEff = square(binContent_sum/binError_sum);
            double avWeight = binContent_sum/nEff;
            double binContent_pass = TMath::Nint(histogram_pass->GetBinContent(iBin)/avWeight);
            double binError_pass = TMath::Sqrt(binContent_pass);
            histogram_pass->SetBinContent(iBin, binContent_pass);
            histogram_pass->SetBinError(iBin, binError_pass);
            double binContent_fail = TMath::Nint(histogram_fail->GetBinContent(iBin)/avWeight);
            double binError_fail = TMath::Sqrt(binContent_fail);
            histogram_fail->SetBinContent(iBin, binContent_fail);
            histogram_fail->SetBinError(iBin, binError_fail);
        }
    }
}

double fitFunction(double x, double par0, double par1) {
    return par0 + par1 *(x-40);
}

Double_t fitFunc_Exp3Par(Double_t *x, Double_t *par) {
    return par[0] + par[1]* (x[0]-3.0);
}

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    return par[0] + par[1] * (x[0]-2.5) ;
}

Double_t fitFunc_Line2Par2(Double_t *x, Double_t *par) {
    //return par[0] + par[1] * (x[0]-4.) ;//+ par[2] * x[0]* x[0] + par[3] * x[0]* x[0] *x[0];
    //return par[0] + par[1]*(TMath::Exp(par[2] * x[0]-par[3]));
    //return par[0] + par[1]*(TMath::Landau((x[0]-1),par[2],par[3],0));
    return par[0] + par[1]*x[0]+par[2]*x[0]*x[0]+par[3]*x[0]*x[0]*x[0];
}

Double_t fitFunc_Landau(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Landau((x[0]-30),par[2],par[3],0));
}

Double_t reflect(Double_t *x, Double_t *par) {
    return 2*(par[0] + par[1]*x[0]+par[2]*x[0]*x[0]+par[3]*x[0]*x[0]*x[0])-(par[4] + par[5]* (x[0]-3.0));
}

TF1 *M_FR(std::string type, std::string files, std::string num, std::string denum, std::string name, Double_t fMin, Double_t fMax, int year) {
    
    TFile *inputFile = new TFile(files.c_str());
    
    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());
    
    TH1D *histogram_pass = (TH1D*) Numerator->Rebin(1);
    TH1D *histogram_fail = (TH1D*) Denumerator->Rebin(1);
    
    makeBinsInteger(histogram_pass, histogram_fail);
    
    TGraphAsymmErrors* TGraph_FR = new TGraphAsymmErrors(26);
    TGraph_FR->Divide(histogram_pass, histogram_fail, "pois");
    
    TF1 * theFit = new TF1("theFit", fitFunc_Line2Par2, fMin, fMax, 4);
    TF1 * theFit2 = new TF1("theFit2", fitFunc_Exp3Par, fMin, fMax, 2);
    
    theFit2->SetParameter(0, 0.1);
    theFit2->SetParameter(1, -0.01); 
    if (type.find("Line2Par2") < 140){
        theFit->SetParameter(0, 2.0);
        theFit->SetParameter(1, -0.3);
        theFit->SetParameter(2, -0.3);
        theFit->SetParameter(3, -0.3);
        //theFit->SetParameter(4, -0.3);
    }
    if (name.find("0bjet") < 140){
        theFit->SetParameter(0, 2.5);
        theFit->SetParameter(1, -0.2);
        theFit->SetParameter(2, 0.006);
        theFit->SetParameter(3, -0.002);
        //theFit->SetParameter(4, -0.002);
    }
    
    TGraph_FR->Fit("theFit", "R0");
    TGraph_FR->Fit("theFit2", "R0");
    
    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    
    TGraph_FR->GetYaxis()->SetRangeUser(0,4);
    TGraph_FR->GetYaxis()->SetTitle("OS-to-SS scale factor");
    TGraph_FR->GetXaxis()->SetRangeUser(0,5);
    TGraph_FR->GetXaxis()->SetTitle("#DeltaR(e,#mu)");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "out_2016/fit2016_" + name + ".png";
    if (year==2017) outNaming = "out_2017/fit2017_" + name + ".png";
    if (year==2018) outNaming = "out_2018/fit2018_" + name + ".png";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.04);
    if (year==2016) t.DrawLatex(0.55, .96, "2016, 36.3 fb^{-1} (13 TeV)");
    if (year==2017) t.DrawLatex(0.55, .96, "2017, 41.5 fb^{-1} (13 TeV)");
    if (year==2018) t.DrawLatex(0.55, .96, "2018, 59.7 fb^{-1} (13 TeV)");
/*
    Double_t TauLegParameters[2];
    theFit2->GetParameters(TauLegParameters);

    Double_t matrix[2][2];
    gMinuit->mnemat(&matrix[0][0],2);
    TMatrixD mat_D(2,2);
    for (int i=0; i<2; ++i){
        for (int j=0; j<2; ++j){
             mat_D[i][j]=matrix[i][j];
        }
    }
    TMatrixDEigen mat_sym=TMatrixDEigen (mat_D);
    TMatrixD eigenValues=mat_sym.GetEigenValues();
    TMatrixD eigenVectors=mat_sym.GetEigenVectors();
    TMatrixD eigenVectorsInverted=mat_sym.GetEigenVectors();
    float aup = TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bup = TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
    float adown = TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bdown = TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

    float au1=TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
    float bu1=TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
    float ad1=TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
    float bd1=TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
    float au2=TauLegParameters[0]+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bu2=TauLegParameters[1]+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
    float ad2=TauLegParameters[0]-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bd2=TauLegParameters[1]-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

    TF1 * theFitup1 = new TF1("theFit2", fitFunc_Exp3Par, fMin, fMax, 2);
    theFitup1->SetParameter(0, au1);
    theFitup1->SetParameter(1, bu1);
    theFitup1->SetLineColor(kViolet+1);
    theFitup1->Draw("same");
    TF1 * theFitup2 = new TF1("theFit2", fitFunc_Exp3Par, fMin, fMax, 2);
    theFitup2->SetParameter(0, au2);
    theFitup2->SetParameter(1, bu2);
    theFitup2->SetLineColor(kGreen-3);
    theFitup2->Draw("same");
    TF1 * theFitdown1 = new TF1("theFit2", fitFunc_Exp3Par, fMin, fMax, 2);
    theFitdown1->SetParameter(0, ad1);
    theFitdown1->SetParameter(1, bd1);
    theFitdown1->SetLineColor(kViolet+1);
    theFitdown1->Draw("same");
    TF1 * theFitdown2 = new TF1("theFit2", fitFunc_Exp3Par, fMin, fMax, 2);
    theFitdown2->SetParameter(0, ad2);
    theFitdown2->SetParameter(1, bd2);
    theFitdown2->SetLineColor(kGreen-3);
    theFitdown2->Draw("same");
    TLegend *l = new TLegend(0.55, 0.74, 0.7, 0.89, NULL, "brNDC");
    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.03);
    l->SetFillColor(0);
    l->AddEntry(theFit, "Best fit", "l");
    l->AddEntry(theFitup1, "1st uncertainty #pm 1#sigma", "l");
    l->AddEntry(theFitup2, "2nd uncertainty #pm 1#sigma", "l");
    l->Draw("same");*/

    TF1 * theFit2sym = new TF1("theFit2sym", reflect, fMin, fMax, 6);
    Double_t fitpar[4];
    theFit->GetParameters(fitpar);
    Double_t fitpar2[2];
    theFit2->GetParameters(fitpar2);
    theFit2sym->SetParameter(0,fitpar[0]);
    theFit2sym->SetParameter(1,fitpar[1]);
    theFit2sym->SetParameter(2,fitpar[2]);
    theFit2sym->SetParameter(3,fitpar[3]);
    theFit2sym->SetParameter(4,fitpar2[0]);
    theFit2sym->SetParameter(5,fitpar2[1]);
    

    theFit->Draw("SAME");
    theFit->SetLineColor(2);
    theFit2->Draw("SAME");
    theFit2->SetLineColor(kGreen-3);
    theFit2sym->Draw("SAME");
    theFit2sym->SetLineColor(kViolet+1);
   
    TLegend *l = new TLegend(0.35, 0.74, 0.7, 0.89, NULL, "brNDC");
    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.03);
    l->SetFillColor(0);
    l->AddEntry(theFit, "Best fit (3rd order polynomial)", "l");
    l->AddEntry(theFit2, "Uncertainty 1#sigma up (linear fit)", "l");
    l->AddEntry(theFit2sym, "Uncertainty 1#sigma down (up shape wrt best fit)", "l");
    l->Draw("same");

    canvas->SaveAs(outNaming.c_str());
    
    std::string osssfilename = "out_2016/osss_em_2016.root";
    if (year==2017) osssfilename = "out_2017/osss_em_2017.root";
    if (year==2018) osssfilename = "out_2018/osss_em_2018.root";
    TFile *FR_H = new TFile(osssfilename.c_str(), "UPDATE");
    FR_H->cd();
    theFit->SetName(TString(name));
    theFit->Write();
    theFit2->SetName(TString(name)+TString("_up"));
    theFit2->Write();
    theFit2sym->SetName(TString(name)+TString("_down"));
    theFit2sym->Write();
/*
    theFitup1->SetName(TString(name)+TString("_up1"));
    theFitup1->Write();
    theFitup2->SetName(TString(name)+TString("_up2"));
    theFitup2->Write();
    theFitdown1->SetName(TString(name)+TString("_down1"));
    theFitdown1->Write();
    theFitdown2->SetName(TString(name)+TString("_down2"));
    theFitdown2->Write();*/
    FR_H->Close();
    
    return theFit;
}

void fit_qcdsf_em(int year) {
    
    //gStyle->SetOptFit(1111);
    
    Double_t fMin = 0.3;
    Double_t fMax = 5.05;
    
    std::string datafile="out_2016/Sub2016.root";
    if (year==2017) datafile="out_2017/Sub2017.root";
    if (year==2018) datafile="out_2018/Sub2018.root";
    
    TF1* m11 = M_FR("Line2Par2", datafile, "INOS_h0", "INSS_h0", "OSSS_qcd_0bjet", fMin, fMax, year);
    TF1* m12 = M_FR("Line2Par2", datafile, "INOS_h1", "INSS_h1", "OSSS_qcd_bjet", fMin, fMax, year);
    
}



