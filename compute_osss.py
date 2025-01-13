if __name__ == "__main__":

    import ROOT
    import argparse
    
    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default=None, help="year")
    options = parser.parse_args()

    lowX=0.5
    if options.year=="2016":
        #lowX=0.35
        lowX=0.34
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.04)
    lumi.SetTextFont (   42 )
    if options.year=="2018":
        lumi.AddText("2018, 59.8 fb^{-1} (13 TeV)")
    if options.year=="2017":
        lumi.AddText("2017, 41.5 fb^{-1} (13 TeV)")
    if options.year=="2016":
        #lumi.AddText("2016 pre-VFP, 19.5 fb^{-1} (13 TeV)")
        lumi.AddText("2016 post-VFP, 16.8 fb^{-1} (13 TeV)")

    lowX=0.18
    lowY=0.70
    lumi2  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi2.SetTextFont(61)
    lumi2.SetTextSize(0.04)
    lumi2.SetBorderSize(   0 )
    lumi2.SetFillStyle(    0 )
    lumi2.SetTextAlign(   12 )
    lumi2.SetTextColor(    1 )
    lumi2.AddText("CMS Preliminary")
    
    file=ROOT.TFile("qcdfiles_em_"+options.year+"/qcd_em_"+options.year+".root","r")
    
    ######OS-to-SS 0bjet
    h0_INOS=file.Get("h0_INOS").Get("data_obs").Clone()
    h0_INOS.Add(file.Get("h0_INOS").Get("MC"),-1)
    INOS_h0=h0_INOS.Clone()
    
    h0_INSS=file.Get("h0_INSS").Get("data_obs").Clone()
    h0_INSS.Add(file.Get("h0_INSS").Get("MC"),-1)
    INSS_h0=h0_INSS.Clone()
    
    #h0_INOS.Divide(h0_INSS)
    
    ######OS-to-SS bjet
    h1_INOS=file.Get("h1_INOS").Get("data_obs").Clone()
    h1_INOS.Add(file.Get("h1_INOS").Get("MC"),-1)
    INOS_h1=h1_INOS.Clone()
    
    h1_INSS=file.Get("h1_INSS").Get("data_obs").Clone()
    h1_INSS.Add(file.Get("h1_INSS").Get("MC"),-1)
    INSS_h1=h1_INSS.Clone()
    
    #h1_INOS.Divide(h1_INSS)
    
    ######closure
    h_closureOS=file.Get("closureOS").Get("data_obs").Clone()
    h_closureOS.Add(file.Get("closureOS").Get("MC"),-1)
    
    h_closureSS=file.Get("closureSS").Get("data_obs").Clone()
    h_closureSS.Add(file.Get("closureSS").Get("MC"),-1)

    h_closureOS.Divide(h_closureSS)

    ######correction
    h_NIOS=file.Get("h_NIOS").Get("data_obs").Clone()
    h_NIOS.Add(file.Get("h_NIOS").Get("MC"),-1)
    h_NISS=file.Get("h_NISS").Get("data_obs").Clone()
    h_NISS.Add(file.Get("h_NISS").Get("MC"),-1)
    h_NIOS.Divide(h_NISS)

    h_NNOS=file.Get("h_NNOS").Get("data_obs").Clone()
    h_NNOS.Add(file.Get("h_NNOS").Get("MC"),-1)
    h_NNSS=file.Get("h_NNSS").Get("data_obs").Clone()
    h_NNSS.Add(file.Get("h_NNSS").Get("MC"),-1)
    h_NNOS.Divide(h_NNSS)

    h_correction=h_NIOS.Clone()
    h_correction.Divide(h_NNOS)

    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetOptFit(1111)
    
    c=ROOT.TCanvas("canvas","",0,0,600,600)
    c.cd()
    
    '''
    h0_INOS.SetMinimum(0)
    h0_INOS.SetMaximum(5)
    h0_INOS.SetTitle("")
    h0_INOS.GetXaxis().SetTitle("#DeltaR(e,#mu)")
    h0_INOS.GetYaxis().SetTitle("OS-to-SS scale factor")
    h0_INOS.Draw("e")
    h0_INOS.Fit("pol1")
    lumi.Draw("same")
    lumi2.Draw("same")
    c.SaveAs("out_"+options.year+"/"+options.year+"OSSSSF_0bjet.pdf")

    h1_INOS.SetTitle("")
    h1_INOS.SetMinimum(0)
    h1_INOS.SetMaximum(5)
    h1_INOS.GetXaxis().SetTitle("#DeltaR(e,#mu)")
    h1_INOS.GetYaxis().SetTitle("OS-to-SS scale factor")
    h1_INOS.Draw("e")
    h1_INOS.Fit("pol1")
    lumi.Draw("same")
    lumi2.Draw("same")
    c.SaveAs("out_"+options.year+"/"+options.year+"OSSSSF_bjet.pdf")
    '''
    h_closureOS.SetTitle("")
    h_closureOS.SetMinimum(0.0)
    h_closureOS.SetMaximum(2.0)
    h_closureOS.GetXaxis().SetTitle("p_{T}(#mu) (GeV)")
    h_closureOS.GetYaxis().SetTitle("p_{T}(e) (GeV)")
    h_closureOS.GetYaxis().SetTitleOffset(1.1)
    h_closureOS.Draw("col")
    h_closureOS.Draw("TEXT45 same")
    lumi.Draw("same")
    c.SaveAs("out_"+options.year+"/"+options.year+"closure.pdf")

    h_correction.SetTitle("")
    h_correction.SetMinimum(0.0)
    h_correction.SetMaximum(2.0)
    h_correction.GetXaxis().SetTitle("p_{T}(#mu) (GeV)")
    h_correction.GetYaxis().SetTitle("p_{T}(e) (GeV)")
    h_correction.GetYaxis().SetTitleOffset(1.1)
    h_correction.Draw("col")
    h_correction.Draw("TEXT45 same")
    lumi.Draw("same")
    c.SaveAs("out_"+options.year+"/"+options.year+"correction.pdf")

    fout=ROOT.TFile("out_"+options.year+"/closure_em_"+options.year+".root","recreate")
    fout.cd()
    h_closureOS.SetName("closureOS")
    h_correction.SetName("correction")
    h_closureOS.Write()
    h_correction.Write()
    fout.Close()

    fSub=ROOT.TFile("out_"+options.year+"/Sub"+options.year+".root","recreate")
    fSub.cd()
    INOS_h0.SetName("INOS_h0")
    INOS_h0.Write()
    INSS_h0.SetName("INSS_h0")
    INSS_h0.Write()
    INOS_h1.SetName("INOS_h1")
    INOS_h1.Write()
    INSS_h1.SetName("INSS_h1")
    INSS_h1.Write()
    fSub.Close()




