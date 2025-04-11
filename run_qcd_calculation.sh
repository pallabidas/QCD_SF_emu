year=$1
rm qcdfiles_em_$year/qcd_em_$year.root
hadd -f qcdfiles_em_$year/qcd_em_$year.root qcdfiles_em_$year/*.root
python3 compute_osss.py --year=$year
rm out_$year/osss_em_$year.root
yearint=2018
if [ "$year" = "2016preVFP" ]; then
	yearint=20161
fi
if [ "$year" = "2016postVFP" ]; then
        yearint=20162
fi
if [ "$year" = "2017" ]; then
	yearint=2017
fi
root -l -b -q "fit_qcdsf_em.cc(${yearint})"
