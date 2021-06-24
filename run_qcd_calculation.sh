year=$1
rm qcdfiles_em_$year/qcd_em_$year.root
hadd -f qcdfiles_em_$year/qcd_em_$year.root qcdfiles_em_$year/*.root
python compute_osss.py --year=$year
rm out_$year/osss_em_$year.root
root -l -b -q "fit_qcdsf_em.cc(${year})"
