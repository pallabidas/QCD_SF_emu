year=$1
./Make.sh selection_qcd_em.cc
rm -rf qcdfiles_em_${year}/*.root
#for sample in data_obs embedded VBFHTT DY DYlow ST_tW_top DY2 DY1 ST_tW_antitop DY3 DY4 TTTo2L2Nu TTToHadronic WZTo2Q2L VVTo2L2Nu ST_t_antitop WZTo3LNu ST_t_top TTToSemiLeptonic ZZTo2Q2L ZZTo4L W W1 W2 W3 W4 GGHTT GGHWW WplusHWW WminusHTT WminusHWW VBFHWW ZHWW WplusHTT ZHTT ttHnonbb ttHbb; do
for sample in data_obs embedded VBFHTT DY DYlow ST_tW_top DY2 DY1 ST_tW_antitop DY3 DY4 TTTo2L2Nu TTToHadronic WZTo2Q2L VVTo2L2Nu ST_t_antitop WZTo3LNu ST_t_top TTToSemiLeptonic ZZTo2Q2L ZZTo4L W GGHTT GGHWW WplusHWW WminusHTT WminusHWW VBFHWW ZHWW WplusHTT ZHTT ttHnonbb ttHbb; do

echo ${sample}

./selection_qcd_em.exe /eos/user/p/pdas/HAA_emuSF/skim_${year}/all/${sample}.root qcdfiles_em_${year}/${sample}.root ${sample} ${year}

done

exit 0

