for sample in data_obs embedded VBFHTT DY DYlow ST_tW_top DY2 DY1 ST_tW_antitop DY3 DY4 TTTo2L2Nu TTToHadronic WZTo2Q2L VVTo2L2Nu ST_t_antitop WZTo3LNu ST_t_top TTToSemiLeptonic ZZTo2Q2L ZZTo4L W W1 W2 W3 W4 GGHTT GGHWW GGZHWW WplusHWW WminusHTT WminusHWW VBFHWW ZHWW WplusHTT ZHTT ttHnonbb ttHbb; do

echo ${sample}

./selection_qcd_em.exe /eos/user/p/pdas/HAA_emuSF/skim/all/${sample}.root  qcdfiles_em_2018/${sample}.root ${sample} 2018

done

exit 0

