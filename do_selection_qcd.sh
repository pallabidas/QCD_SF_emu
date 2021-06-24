year=$1
dataset=$2
inpath="/hdfs/store/user/htsoi/haabbtt_rerunBtag_selection/haabbtt_em${year}_rerunBtag"
outpath="qcdfiles_em_${year}"
exe="selection_qcd_em.exe"

if [ $dataset == "data" ]
then
  ./$exe $inpath/data_obs.root $outpath/data_obs.root data_obs data_obs $year
fi

if [ $dataset == "emb" ]
then
  ./$exe $inpath/embedded.root $outpath/embedded.root embedded embedded $year
fi

if [ $dataset == "ttbar" ]
then
  ./$exe $inpath/TTTo2L2Nu.root $outpath/TTTo2L2Nu.root TTTo2L2Nu ttbar $year
  ./$exe $inpath/TTToHadronic.root $outpath/TTToHadronic.root TTToHadronic ttbar $year
  ./$exe $inpath/TTToSemiLeptonic.root $outpath/TTToSemiLeptonic.root TTToSemiLeptonic ttbar $year
fi

if [ $dataset == "other" ]
then
  ./$exe $inpath/DY.root $outpath/DY.root DY ZJ $year
  ./$exe $inpath/DY1.root $outpath/DY1.root DY1 ZJ $year
  ./$exe $inpath/DY2.root $outpath/DY2.root DY2 ZJ $year
  ./$exe $inpath/DY3.root $outpath/DY3.root DY3 ZJ $year
  ./$exe $inpath/DY4.root $outpath/DY4.root DY4 ZJ $year
  if [ $year == "2017" ] || [ $year == "2018" ]
  then
    ./$exe $inpath/DYlow.root $outpath/DYlow.root DYlow ZJ $year
  fi
  if [ $year == "2016" ]
  then
    ./$exe $inpath/DYlow.root $outpath/DYlow.root DYlow ZJ $year
    ./$exe $inpath/DY1low.root $outpath/DY1low.root DY1low ZJ $year
    ./$exe $inpath/DY2low.root $outpath/DY2low.root DY2low ZJ $year
    ./$exe $inpath/DY3low.root $outpath/DY3low.root DY3low ZJ $year
    ./$exe $inpath/DY4low.root $outpath/DY4low.root DY4low ZJ $year
  fi
  ./$exe $inpath/GGHTT.root $outpath/GGHTT.root GGHTT ggh_htt $year
  ./$exe $inpath/GGHWW.root $outpath/GGHWW.root GGHWW ggh_hww $year
  ./$exe $inpath/GGZHLLTT.root $outpath/GGZHLLTT.root GGZHLLTT Zh_htt $year
  ./$exe $inpath/GGZHNNTT.root $outpath/GGZHNNTT.root GGZHNNTT Zh_htt $year
  ./$exe $inpath/GGZHQQTT.root $outpath/GGZHQQTT.root GGZHQQTT Zh_htt $year
  ./$exe $inpath/GGZHWW.root $outpath/GGZHWW.root GGZHWW Zh_hww $year
  ./$exe $inpath/ST_tW_antitop.root $outpath/ST_tW_antitop.root ST_tW_antitop ST $year
  ./$exe $inpath/ST_tW_top.root $outpath/ST_tW_top.root ST_tW_top ST $year
  ./$exe $inpath/ST_t_antitop.root $outpath/ST_t_antitop.root ST_t_antitop ST $year
  ./$exe $inpath/ST_t_top.root $outpath/ST_t_top.root ST_t_top ST $year
  ./$exe $inpath/VBFHTT.root $outpath/VBFHTT.root VBFHTT qqh_htt $year
  ./$exe $inpath/VBFHWW.root $outpath/VBFHWW.root VBFHWW qqh_hww $year
  ./$exe $inpath/VV2L2Nu.root $outpath/VV2L2Nu.root VV2L2Nu VV $year
  ./$exe $inpath/WZ2L2Q.root $outpath/WZ2L2Q.root WZ2L2Q VV $year
  ./$exe $inpath/WZ3L1Nu.root $outpath/WZ3L1Nu.root WZ3L1Nu VV $year
  ./$exe $inpath/WminusHTT.root $outpath/WminusHTT.root WminusHTT Wh_htt $year
  ./$exe $inpath/WminusHWW.root $outpath/WminusHWW.root WminusHWW Wh_hww $year
  ./$exe $inpath/WplusHTT.root $outpath/WplusHTT.root WplusHTT Wh_htt $year
  ./$exe $inpath/WplusHWW.root $outpath/WplusHWW.root WplusHWW Wh_hww $year
  ./$exe $inpath/ZHTT.root $outpath/ZHTT.root ZHTT Zh_htt $year
  ./$exe $inpath/ZHWW.root $outpath/ZHWW.root ZHWW Zh_hww $year
  ./$exe $inpath/ZZ2L2Q.root $outpath/ZZ2L2Q.root ZZ2L2Q VV $year
  ./$exe $inpath/ZZ4L.root $outpath/ZZ4L.root ZZ4L VV $year
  ./$exe $inpath/ttHnonbb.root $outpath/ttHnonbb.root ttHnonbb tth $year
  ./$exe $inpath/ttHbb.root $outpath/ttHbb.root ttHbb tth $year
  ./$exe $inpath/W.root $outpath/W.root W WJ $year
  ./$exe $inpath/W1.root $outpath/W1.root W1 WJ $year
  ./$exe $inpath/W2.root $outpath/W2.root W2 WJ $year
  ./$exe $inpath/W3.root $outpath/W3.root W3 WJ $year
  ./$exe $inpath/W4.root $outpath/W4.root W4 WJ $year
fi

#hadd -f $outpath/qcd_em_$year.root $outpath/*.root
