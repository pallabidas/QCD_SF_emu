#include <TH2.h>
#include "btagSF.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "tr_Tree.h"
#include "LumiReweightingStandAlone.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "BTagCalibrationStandalone.h"
#include "BTagCalibrationStandalone.cpp"

using namespace std;

int main(int argc, char** argv) {
    
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    
    int year=2016;
    if (argc > 1) {
        year = atof(argv[5]);
    }
    
    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("emu_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float N = nbevt->GetBinContent(2);
    
    float xs=1.0; float weight=1.0; float luminosity=36330.0;
    if (year==2017) luminosity=41530.0;
    if (year==2018) luminosity=59740.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "embedded"){weight = 1.0;}
    else if(sample == "DY"){weight = 1.0;}
    else if(sample == "DY1"){weight = 1.0;}
    else if(sample == "DY2"){weight = 1.0;}
    else if(sample == "DY3"){weight = 1.0;}
    else if(sample == "DY4"){weight = 1.0;}
    else if(sample == "DYlow"){weight = 1.0;}
    else if(sample == "DY1low"){weight = 1.0;}
    else if(sample == "DY2low"){weight = 1.0;}
    else if(sample == "DY3low"){weight = 1.0;}
    else if(sample == "DY4low"){weight = 1.0;}
    else if(sample == "GGHTT"){xs = 48.58*0.0627; weight = luminosity*xs/N;}
    else if(sample == "GGHWW"){xs = 48.58*0.2137*0.3258*0.3258; weight = luminosity*xs/N;}
    else if(sample == "GGZHLLTT"){xs = 0.1227*0.0627*3*0.033658; weight = luminosity*xs/N;}
    else if(sample == "GGZHNNTT"){xs = 0.1227*0.0627*0.2000; weight = luminosity*xs/N;}
    else if(sample == "GGZHQQTT"){xs = 0.1227*0.0627*0.6991; weight = luminosity*xs/N;}
    else if(sample == "GGZHWW"){xs = 0.1227*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_antitop"){xs = 35.85; if(year==2016) xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_top"){xs = 35.85; if(year==2016) xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_t_antitop"){xs = 80.94; if(year==2016) xs = 26.23; weight = luminosity*xs/N;}
    else if(sample == "ST_t_top"){xs = 136.02; if(year==2016) xs = 44.07; weight = luminosity*xs/N;}
    else if(sample == "TTTo2L2Nu"){xs = 88.29; weight = luminosity*xs/N;}
    else if(sample == "TTToHadronic"){xs = 377.96; weight = luminosity*xs/N;}
    else if(sample == "TTToSemiLeptonic"){xs = 365.35; weight = luminosity*xs/N;}
    else if(sample == "VBFHTT"){xs = 3.782*0.0627; weight = luminosity*xs/N;}
    else if(sample == "VBFHWW"){xs = 3.782*0.2137*0.3258*0.3258; weight = luminosity*xs/N;}
    else if(sample == "VV2L2Nu"){xs = 13.84; weight = luminosity*xs/N;}//11.95
    else if(sample == "W"){weight = 1.0;}
    else if(sample == "W1"){weight = 1.0;}
    else if(sample == "W2"){weight = 1.0;}
    else if(sample == "W3"){weight = 1.0;}
    else if(sample == "W4"){weight = 1.0;}
    else if(sample == "WZ2L2Q"){xs = 5.52; weight = luminosity*xs/N;}//5.595
    else if(sample == "WZ3L1Nu"){xs = 4.43; weight = luminosity*xs/N;}//4.708
    else if(sample == "WminusHTT"){xs = 0.5328*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WminusHWW"){xs = 0.5328*0.2137; weight = luminosity*xs/N;}
    else if(sample == "WplusHTT"){xs = 0.840*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WplusHWW"){xs = 0.840*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ZHTT"){xs = 0.7612*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZHWW"){xs = 0.7612*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ZZ2L2Q"){xs = 3.38; weight = luminosity*xs/N;}//3.22
    else if(sample == "ZZ4L"){xs = 1.212; weight = luminosity*xs/N;}
    else if(sample == "ttHnonbb"){xs = 0.5071*(1-0.5824); weight = luminosity*xs/N;}
    else if(sample == "ttHbb"){xs = 0.5071*0.5824; weight = luminosity*xs/N;}
    else {cout << "Missing sample cross section!!!" << endl; return 0;}
    
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);
    
    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("zptmass_weight_nom", &zptmass_weight_nom);
    arbre->SetBranchAddress("e_trk_ratio", &e_trk_ratio);
    arbre->SetBranchAddress("e_idiso_ic_ratio", &e_idiso_ic_ratio);
    arbre->SetBranchAddress("e_trk_embed_ratio", &e_trk_embed_ratio);
    arbre->SetBranchAddress("e_idiso_ic_embed_ratio", &e_idiso_ic_embed_ratio);
    arbre->SetBranchAddress("m_trk_ratio", &m_trk_ratio);
    arbre->SetBranchAddress("m_idiso_ic_ratio", &m_idiso_ic_ratio);
    arbre->SetBranchAddress("m_idiso_ic_embed_ratio", &m_idiso_ic_embed_ratio);
    arbre->SetBranchAddress("m_sel_trg_ic_ratio", &m_sel_trg_ic_ratio);
    arbre->SetBranchAddress("m_sel_id_ic_ratio_1", &m_sel_id_ic_ratio_1);
    arbre->SetBranchAddress("m_sel_id_ic_ratio_2", &m_sel_id_ic_ratio_2);
    arbre->SetBranchAddress("m_trg_8_ic_data", &m_trg_8_ic_data);
    arbre->SetBranchAddress("e_trg_23_ic_data", &e_trg_23_ic_data);
    arbre->SetBranchAddress("m_trg_23_ic_data", &m_trg_23_ic_data);
    arbre->SetBranchAddress("e_trg_12_ic_data", &e_trg_12_ic_data);
    arbre->SetBranchAddress("m_trg_8_ic_mc", &m_trg_8_ic_mc);
    arbre->SetBranchAddress("e_trg_23_ic_mc", &e_trg_23_ic_mc);
    arbre->SetBranchAddress("m_trg_23_ic_mc", &m_trg_23_ic_mc);
    arbre->SetBranchAddress("e_trg_12_ic_mc", &e_trg_12_ic_mc);
    arbre->SetBranchAddress("m_trg_8_ic_embed", &m_trg_8_ic_embed);
    arbre->SetBranchAddress("e_trg_23_ic_embed", &e_trg_23_ic_embed);
    arbre->SetBranchAddress("m_trg_23_ic_embed", &m_trg_23_ic_embed);
    arbre->SetBranchAddress("e_trg_12_ic_embed", &e_trg_12_ic_embed);
    arbre->SetBranchAddress("passMu8E23", &passMu8E23);
    arbre->SetBranchAddress("passMu23E12", &passMu23E12);
    arbre->SetBranchAddress("matchMu8E23_1", &matchMu8E23_1);
    arbre->SetBranchAddress("matchMu23E12_1", &matchMu23E12_1);
    arbre->SetBranchAddress("filterMu8E23_1", &filterMu8E23_1);
    arbre->SetBranchAddress("filterMu23E12_1", &filterMu23E12_1);
    arbre->SetBranchAddress("matchMu8E23_2", &matchMu8E23_2);
    arbre->SetBranchAddress("matchMu23E12_2", &matchMu23E12_2);
    arbre->SetBranchAddress("filterMu8E23_2", &filterMu8E23_2);
    arbre->SetBranchAddress("filterMu23E12_2", &filterMu23E12_2);
    arbre->SetBranchAddress("passMu8E23DZ", &passMu8E23DZ);
    arbre->SetBranchAddress("passMu23E12DZ", &passMu23E12DZ);
    arbre->SetBranchAddress("matchMu8E23DZ_1", &matchMu8E23DZ_1);
    arbre->SetBranchAddress("matchMu23E12DZ_1", &matchMu23E12DZ_1);
    arbre->SetBranchAddress("filterMu8E23DZ_1", &filterMu8E23DZ_1);
    arbre->SetBranchAddress("filterMu23E12DZ_1", &filterMu23E12DZ_1);
    arbre->SetBranchAddress("matchMu8E23DZ_2", &matchMu8E23DZ_2);
    arbre->SetBranchAddress("matchMu23E12DZ_2", &matchMu23E12DZ_2);
    arbre->SetBranchAddress("filterMu8E23DZ_2", &filterMu8E23DZ_2);
    arbre->SetBranchAddress("filterMu23E12DZ_2", &filterMu23E12DZ_2);
    arbre->SetBranchAddress("npu", &npu);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("e_1", &e_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("e_2", &e_2);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("iso_2", &iso_2);
    arbre->SetBranchAddress("numGenJets", &numGenJets);
    arbre->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter", &Flag_ecalBadCalibReducedMINIAODFilter);
    arbre->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices);
    arbre->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter);
    arbre->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter);
    arbre->SetBranchAddress("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter);
    arbre->SetBranchAddress("Flag_badMuons", &Flag_badMuons);
    arbre->SetBranchAddress("Flag_duplicateMuons", &Flag_duplicateMuons);
    arbre->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter);
    arbre->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter);
    arbre->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter);
    arbre->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter);
    arbre->SetBranchAddress("Flag_BadChargedCandidateFilter", &Flag_BadChargedCandidateFilter);
    arbre->SetBranchAddress("gen_match_1", &gen_match_1);
    arbre->SetBranchAddress("gen_match_2", &gen_match_2);
    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("bpt_deepflavour_1", &bpt_deepflavour_1);
    arbre->SetBranchAddress("bflavour_deepflavour_1", &bflavour_deepflavour_1);
    arbre->SetBranchAddress("beta_deepflavour_1", &beta_deepflavour_1);
    arbre->SetBranchAddress("bphi_deepflavour_1", &bphi_deepflavour_1);
    arbre->SetBranchAddress("bm_deepflavour_1", &bm_deepflavour_1);
    arbre->SetBranchAddress("bscore_deepflavour_1", &bscore_deepflavour_1);
    arbre->SetBranchAddress("bpt_deepflavour_2", &bpt_deepflavour_2);
    arbre->SetBranchAddress("bflavour_deepflavour_2", &bflavour_deepflavour_2);
    arbre->SetBranchAddress("beta_deepflavour_2", &beta_deepflavour_2);
    arbre->SetBranchAddress("bphi_deepflavour_2", &bphi_deepflavour_2);
    arbre->SetBranchAddress("bm_deepflavour_2", &bm_deepflavour_2);
    arbre->SetBranchAddress("bscore_deepflavour_2", &bscore_deepflavour_2);
    arbre->SetBranchAddress("pt_top1", &pt_top1);
    arbre->SetBranchAddress("pt_top2", &pt_top2);
    arbre->SetBranchAddress("genweight", &genweight);
    arbre->SetBranchAddress("prefiring_weight", &prefiring_weight);
    
    // default: 11,0.4,5.9
    // dR>0.3: 11,0.3,5.8
    TH1F* h0_INOS = new TH1F ("","",11,0.3,5.8); h0_INOS->Sumw2();
    TH1F* h0_INSS = new TH1F ("","",11,0.3,5.8); h0_INSS->Sumw2();
    TH1F* h1_INOS = new TH1F ("","",11,0.3,5.8); h1_INOS->Sumw2();
    TH1F* h1_INSS = new TH1F ("","",11,0.3,5.8); h1_INSS->Sumw2();
    
    float bins_pte[] = {13,20,24,30,60};
    int  binnum_pte = sizeof(bins_pte)/sizeof(Float_t) - 1;
    float bins_ptm[] = {13,20,24,30,60};
    int  binnum_ptm = sizeof(bins_ptm)/sizeof(Float_t) - 1;
    
    TH2F* closureOS = new TH2F("closureOS","closureOS",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureOS->Sumw2();
    TH2F* closureSS = new TH2F("closureSS","closureSS",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureSS->Sumw2();
    
    float bins_1[] = {13,20,24,35,100};
    int  binnum_1 = sizeof(bins_1)/sizeof(Float_t) - 1;
    float bins_2[] = {13,20,24,35,100};
    int  binnum_2 = sizeof(bins_2)/sizeof(Float_t) - 1;
    
    TH2F* h_NIOS = new TH2F ("","",binnum_1,bins_1,binnum_2,bins_2); h_NIOS->Sumw2();
    TH2F* h_NISS = new TH2F ("","",binnum_1,bins_1,binnum_2,bins_2); h_NISS->Sumw2();
    TH2F* h_NNOS = new TH2F ("","",binnum_1,bins_1,binnum_2,bins_2); h_NNOS->Sumw2();
    TH2F* h_NNSS = new TH2F ("","",binnum_1,bins_1,binnum_2,bins_2); h_NNSS->Sumw2();
    
    std::string osssfilename = "out_2016/osss_em_2016.root";
    if (year==2017) osssfilename = "out_2017/osss_em_2017.root";
    if (year==2018) osssfilename = "out_2018/osss_em_2018.root";
    TFile *fosss= new TFile(osssfilename.c_str(),"r");
    TF1 *osss_0bjet=(TF1*) fosss->Get("OSSS_qcd_0bjet");
    TF1 *osss_bjet=(TF1*) fosss->Get("OSSS_qcd_bjet");
    
    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");
    if (year==2017){
        LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        if (sample=="W1") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
        else if (sample=="W2") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v5#MINIAODSIM", "pileup");
        else if (sample=="ST_t_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
        else if (sample=="W") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
        else if (sample=="DY") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="WW") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WW_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="WplusHTT") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WplusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="WZ") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WZ_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="ST_tW_top") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
        else if (sample=="WminusHTT") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WminusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="ST_tW_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
        else if (sample=="W3") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="ZHTT") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ZHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="TTToSemiLeptonic")  LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="TTTo2L2Nu") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    }
    if (year==2016) LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");
    
    //btagging SF reader
    std::string btagSFfile = "DeepJet_102XSF_V2_JESreduced";
    if (year==2017) btagSFfile = "DeepFlavour_94XSF_V4_B_F_JESreduced";
    if (year==2016) btagSFfile = "DeepJet_2016LegacySF_V1_TuneCP5_JESreduced";
    std::string btagSFfilecsv = btagSFfile + ".csv";
    
    BTagCalibration calib(btagSFfile, btagSFfilecsv);
    BTagCalibrationReader reader(BTagEntry::OP_RESHAPING, "central", {});
    reader.load(calib, BTagEntry::FLAV_B, "iterativefit");
    reader.load(calib, BTagEntry::FLAV_C, "iterativefit");
    reader.load(calib, BTagEntry::FLAV_UDSG, "iterativefit");
    
    
    Int_t nentries_wtn = (Int_t) arbre->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 100 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if ((year==2017 or year==2018) && Flag_ecalBadCalibReducedMINIAODFilter) continue;
        
        //Trigger
        bool triggerMu8E23=(passMu8E23 && matchMu8E23_1 && matchMu8E23_2 && pt_1>24 && pt_2>9);
        bool triggerMu23E12=(passMu23E12 && matchMu23E12_1 && matchMu23E12_2 && pt_1>13 && pt_2>24);
        if (year==2018 or year==2017 or (year==2016 and sample=="data_obs" && run>=278820)){
            triggerMu8E23=(passMu8E23DZ && matchMu8E23DZ_1 && matchMu8E23DZ_2 && pt_1>24 && pt_2>9);
            triggerMu23E12=(passMu23E12DZ && matchMu23E12DZ_1 && matchMu23E12DZ_2 && pt_1>13 && pt_2>24);
        }
        if (!triggerMu8E23 && !triggerMu23E12) continue;
        
        if (fabs(eta_1)>2.4 or fabs(eta_2)>2.4) continue;
        
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        if (mymu.DeltaR(myele)<0.3) continue;
        
        //bool isII=(iso_1<0.15 && iso_2<0.15);
        bool isIN=(iso_1<0.15 && iso_2>0.15 && iso_2<0.50);
        bool isNI=(iso_1>0.15 && iso_1<0.50 && iso_2<0.15);
        bool isNN=(iso_1>0.15 && iso_1<0.50 && iso_2>0.15 && iso_2<0.50);
        
        if (name=="ZJ"){
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                if (numGenJets==0){
                    weight = 3.630;
                    if (year==2017) weight = 2.583;
                    if (year==2016) weight = 1.509;
                }
                else if (numGenJets==1){
                    weight = 0.6304;
                    if (year==2017) weight = 0.3269;
                    if (year==2016) weight = 0.4814;
                }
                else if (numGenJets==2){
                    weight = 0.5528;
                    if (year==2017) weight = 0.5667;
                    if (year==2016) weight = 0.4987;
                }
                else if (numGenJets==3){
                    weight = 0.6009;
                    if (year==2017) weight = 0.5228;
                    if (year==2016) weight = 0.5113;
                }
                else if (numGenJets==4){
                    weight = 0.8314;
                    if (year==2017) weight = 0.2199;
                    if (year==2016) weight = 0.4194;
                }
            }
            if (sample=="DYlow" or sample=="DY1low" or sample=="DY2low" or sample=="DY3low" or sample=="DY4low"){
                if (year==2016){
                    if (numGenJets==0) weight = 20.64;
                    else if (numGenJets==1) weight = 0.7822;
                    else if (numGenJets==2) weight = 0.8491;
                    else if (numGenJets==3) weight = 0.8178;
                    else if (numGenJets==4) weight = 0.7536;
                }
                if (year==2017) weight = 9.416;
                if (year==2018) weight = 12.45;
            }
        }
        
        if (name=="WJ"){
            if (numGenJets==0){
                weight = 51.81;
                if (year==2017) weight = 23.74;
                if (year==2016) weight = 25.72;
            }
            else if (numGenJets==1){
                weight = 9.091;
                if (year==2017) weight = 3.116;
                if (year==2016) weight = 5.840;
            }
            else if (numGenJets==2){
                weight = 4.516;
                if (year==2017) weight = 3.024;
                if (year==2016) weight = 1.814;
            }
            else if (numGenJets==3){
                weight = 3.090;
                if (year==2017) weight = 1.355;
                if (year==2016) weight = 0.6878;
            }
            else if (numGenJets==4){
                weight = 3.227;
                if (year==2017) weight = 1.119;
                if (year==2016) weight = 0.7453;
            }
        }       
 
        //if (sample=="embedded" && (gen_match_1==6 or gen_match_2==6)) continue;
        bool is_includedInEmbedded=false;
        if ((sample!="data_obs" && sample!="embedded" && name!="ggh_htt" && name!="ggh_hww" && name!="qqh_htt" && name!="qqh_hww" && name!="Zh_htt" && name!="Zh_hww" && name!="Wh_htt" && name!="Wh_hww" && name!="tth") && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) is_includedInEmbedded = true; // remove overlap with embedded samples
        if (is_includedInEmbedded) continue;
        
        float sf_MC = 1.0;
        
        if (sample!="data_obs" && sample!="embedded"){
            
            sf_MC *= e_trk_ratio * e_idiso_ic_ratio * m_trk_ratio * m_idiso_ic_ratio;
            
            float probData = m_trg_8_ic_data*e_trg_23_ic_data*int(triggerMu8E23)+m_trg_23_ic_data*e_trg_12_ic_data*int(triggerMu23E12)-e_trg_23_ic_data*m_trg_23_ic_data*int(triggerMu8E23 && triggerMu23E12);
            float probMC = m_trg_8_ic_mc*e_trg_23_ic_mc*int(triggerMu8E23)+m_trg_23_ic_mc*e_trg_12_ic_mc*int(triggerMu23E12)-e_trg_23_ic_mc*m_trg_23_ic_mc*int(triggerMu8E23 && triggerMu23E12);
            float sf_trg = 1.0;
            if (probMC==0) sf_trg = 1.0;
            else sf_trg = probData/probMC;
            sf_MC *= sf_trg;
            
            if (name=="ZJ") sf_MC *= zptmass_weight_nom;
            
            if (name=="ttbar"){
                float pttop1=pt_top1;
                if (pttop1>472) pttop1=472;
                float pttop2=pt_top2;
                if (pttop2>472) pttop2=472;
                float topfactor = sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
                sf_MC *= topfactor;
            }
            
            sf_MC *= genweight;
            sf_MC *= LumiWeights_12->weight(npu);
            if (year!=2018) sf_MC *= prefiring_weight;
            
        }
        
        float sf_emb = 1.0;
        
        if (sample=="embedded"){
            
            if (year==2016 && genweight>1.0) continue;
            sf_emb *= e_trk_embed_ratio * e_idiso_ic_embed_ratio * m_trk_ratio * m_idiso_ic_embed_ratio;
            sf_emb *= genweight;
            sf_emb *= m_sel_trg_ic_ratio * m_sel_id_ic_ratio_1 * m_sel_id_ic_ratio_2;
            
            float probData = m_trg_8_ic_data*e_trg_23_ic_data*int(triggerMu8E23)+m_trg_23_ic_data*e_trg_12_ic_data*int(triggerMu23E12)-e_trg_23_ic_data*m_trg_23_ic_data*int(triggerMu8E23 && triggerMu23E12);
            float probEmbedded = m_trg_8_ic_embed*e_trg_23_ic_embed*int(triggerMu8E23)+m_trg_23_ic_embed*e_trg_12_ic_embed*int(triggerMu23E12)-e_trg_23_ic_embed*m_trg_23_ic_embed*int(triggerMu8E23 && triggerMu23E12);
            if (year==2017){
                probData = e_trg_23_ic_data*int(triggerMu8E23)+m_trg_23_ic_data*e_trg_12_ic_data*int(triggerMu23E12)-e_trg_23_ic_data*m_trg_23_ic_data*int(triggerMu8E23 && triggerMu23E12);
                probEmbedded = e_trg_23_ic_embed*int(triggerMu8E23)+m_trg_23_ic_embed*e_trg_12_ic_embed*int(triggerMu23E12)-e_trg_23_ic_embed*m_trg_23_ic_embed*int(triggerMu8E23 && triggerMu23E12);
            }
            float sf_trg = 1.0;
            if (probEmbedded==0) sf_trg=1.0;
            else sf_trg = probData/probEmbedded;
            sf_emb *= sf_trg;
            
        }
        
        float weight_corr = weight * sf_MC * sf_emb;
        
        int nbtag20 = 0;
        float bMpt_1 = 0;
        float bMflavor_1 = 0;
        float bMpt_2 = 0;
        float bMflavor_2 = 0;
        float bscore_thres = 0.2770;
        if (year==2017) bscore_thres = 0.3033;
        if (year==2016) bscore_thres = 0.3093;
        if (bpt_deepflavour_1>20 && bscore_deepflavour_1>bscore_thres && fabs(beta_deepflavour_1)<2.4){
            bMpt_1 = bpt_deepflavour_1;
            bMflavor_1 = bflavour_deepflavour_1;
            nbtag20++;
        }
        if (bpt_deepflavour_2>20 && bscore_deepflavour_2>bscore_thres && fabs(beta_deepflavour_2)<2.4){
            bMpt_2 = bpt_deepflavour_2;
            bMflavor_2 = bflavour_deepflavour_2;
            nbtag20++;
        }
        //b-tagged jet true flavour to be passed to btag SF reader
        auto btagflavour_1 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_1==5) btagflavour_1 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_1==4) btagflavour_1 = BTagEntry::FLAV_C;
        if (bflavour_deepflavour_1==0) btagflavour_1 = BTagEntry::FLAV_UDSG;
        auto btagflavour_2 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_2==5) btagflavour_2 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_2==4) btagflavour_2 = BTagEntry::FLAV_C;
        if (bflavour_deepflavour_2==0) btagflavour_2 = BTagEntry::FLAV_UDSG;
        
        float weight_btag = 1.0;//no correction if requiring 0 btag
        if (sample!="data_obs" && sample!="embedded"){
            /*
            if (nbtag20==1){
                if (year==2016) weight_btag = GetSF_2016(1, bMpt_1, bMflavor_1, 0);
                if (year==2017) weight_btag = GetSF_2017(1, bMpt_1, bMflavor_1, 0);
                if (year==2018) weight_btag = GetSF_2018(1, bMpt_1, bMflavor_1, 0);
            }
            if (nbtag20==2){
                if (year==2016) weight_btag = GetSF_2016(1, bMpt_1, bMflavor_1, 0)*GetSF_2016(1, bMpt_2, bMflavor_2, 0);
                if (year==2017) weight_btag = GetSF_2017(1, bMpt_1, bMflavor_1, 0)*GetSF_2017(1, bMpt_2, bMflavor_2, 0);
                if (year==2018) weight_btag = GetSF_2018(1, bMpt_1, bMflavor_1, 0)*GetSF_2018(1, bMpt_2, bMflavor_2, 0);
            }
            weight_0btag = bTagEventWeight(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0,year);
            */
            
            if (nbtag20==1) weight_btag = reader.eval_auto_bounds("central", btagflavour_1, fabs(beta_deepflavour_1), bMpt_1, bscore_deepflavour_1);
            if (nbtag20==2) weight_btag = reader.eval_auto_bounds("central", btagflavour_1, fabs(beta_deepflavour_1), bMpt_1, bscore_deepflavour_1)*reader.eval_auto_bounds("central", btagflavour_2, fabs(beta_deepflavour_2), bMpt_2, bscore_deepflavour_2);
        }
        
        float sssf=2.5;
        if (nbtag20==0) sssf = osss_0bjet->Eval(myele.DeltaR(mymu));
        else sssf = osss_bjet->Eval(myele.DeltaR(mymu));
        if (sssf<0 or sssf>10) sssf = 0;
        
        if (nbtag20==0){
            if (isIN && q_1*q_2<0)
                h0_INOS->Fill(myele.DeltaR(mymu),weight_corr);
            if (isIN && q_1*q_2>0)
                h0_INSS->Fill(myele.DeltaR(mymu),weight_corr);
        }
        if (nbtag20>=1){
            if (isIN && q_1*q_2<0)
                h1_INOS->Fill(myele.DeltaR(mymu),weight_corr*weight_btag);
            if (isIN && q_1*q_2>0)
                h1_INSS->Fill(myele.DeltaR(mymu),weight_corr*weight_btag);
        }
        if (njets>-1){
            float mupt=mymu.Pt();
            if (mupt>100) mupt=99;
            float ept=myele.Pt();
            if (ept>100) ept=99;
            
            if (isIN && q_1*q_2<0){
                closureOS->Fill(mupt,ept,weight_corr);
            }
            if (isIN && q_1*q_2>0){
                closureSS->Fill(mupt,ept,weight_corr*sssf);// need OS-to-SS SF applied
            }
            
            if (isNI && q_1*q_2<0){
                h_NIOS->Fill(mupt,ept,weight_corr);
            }
            if (isNI && q_1*q_2>0){
                h_NISS->Fill(mupt,ept,weight_corr);
            }
            if (isNN && q_1*q_2<0){
                h_NNOS->Fill(mupt,ept,weight_corr);
            }
            if (isNN && q_1*q_2>0){
                h_NNSS->Fill(mupt,ept,weight_corr);
            }
        }
    } // end of loop over events
    
    TString setname = "data_obs";
    if (sample!="data_obs") setname = "MC";
    
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    
    TDirectory *d_h0_INOS = fout->mkdir("h0_INOS");
    d_h0_INOS->cd();
    h0_INOS->SetName(setname);
    h0_INOS->Write();
    TDirectory *d_h0_INSS = fout->mkdir("h0_INSS");
    d_h0_INSS->cd();
    h0_INSS->SetName(setname);
    h0_INSS->Write();
    
    TDirectory *d_h1_INOS = fout->mkdir("h1_INOS");
    d_h1_INOS->cd();
    h1_INOS->SetName(setname);
    h1_INOS->Write();
    TDirectory *d_h1_INSS = fout->mkdir("h1_INSS");
    d_h1_INSS->cd();
    h1_INSS->SetName(setname);
    h1_INSS->Write();
    
    TDirectory *d_closureOS = fout->mkdir("closureOS");
    d_closureOS->cd();
    closureOS->SetName(setname);
    closureOS->Write();
    TDirectory *d_closureSS = fout->mkdir("closureSS");
    d_closureSS->cd();
    closureSS->SetName(setname);
    closureSS->Write();
    
    TDirectory *d_h_NIOS = fout->mkdir("h_NIOS");
    d_h_NIOS->cd();
    h_NIOS->SetName(setname);
    h_NIOS->Write();
    TDirectory *d_h_NISS = fout->mkdir("h_NISS");
    d_h_NISS->cd();
    h_NISS->SetName(setname);
    h_NISS->Write();
    TDirectory *d_h_NNOS = fout->mkdir("h_NNOS");
    d_h_NNOS->cd();
    h_NNOS->SetName(setname);
    h_NNOS->Write();
    TDirectory *d_h_NNSS = fout->mkdir("h_NNSS");
    d_h_NNSS->cd();
    h_NNSS->SetName(setname);
    h_NNSS->Write();
    
    fout->Close();
    
} 




