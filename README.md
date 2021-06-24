# QCD_SF

Measurement of QCD scale factors for haabbtt e+mu final state

- Run the selection_qcd_em code on the same samples used in analysis
- Run compute_osss.py to do data/MC subtraction and to make closure and correction plots
- Run root -l -b -q "fit_qcdsf_em.cc(${year})" to do fitting of the OS-to-SS rates
- Everytime OS-to-SS rate is updated, one needs to rerun the selection and fitting again since the 2D closure has the OS-to-SS rate applied
