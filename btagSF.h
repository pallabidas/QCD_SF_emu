double GetSF_2016(int WP, float x, int flavour, int syst){

   if (WP==1){
      if (fabs(flavour)==4 or fabs(flavour)==5){
        if (syst==0){
	   return 0.922748*((1.+(0.0241884*x))/(1.+(0.0223119*x)));
        }
      }
      else {
        if (syst==0) return 1.09149+3.31851e-05*x+2.34826e-07*x*x+-0.888846/x;
     }
   }
   else return 0;
}

double GetSF_2017(int WP, float x, int flavour, int syst){

   if (WP==1){
      if (fabs(flavour)==4 or fabs(flavour)==5){
        if (syst==0){
           return 0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x)));
        }
      }
      else {
        if (syst==0) return 1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x;
     }
   }
   else return 0;
}


double GetSF_2018(int WP, float x, int flavour, int syst){
   if (WP==1){
      if (fabs(flavour)==4 or fabs(flavour)==5){
        if (syst==0){
           return 1.0097+(-(2.89663e-06*(log(x+19)*(log(x+18)*(3-(-(110.381*log(x+18))))))));
        }
      }
      else {
        if (syst==0) return 1.59373+-0.00113028*x+8.66631e-07*x*x+-1.10505/x;
     }
   }
   else return 0;
}



double bTagEventWeight(int nBtaggedJets, float bjetpt_1, int bjetflavour_1, float bjetpt_2, int bjetflavour_2, int WP, int syst, int nBTags, int year)
{
  if (nBtaggedJets > 2) return -10000;
  if( nBTags > 2 ) return -10000;

  /*
    ##################################################################
    Event weight matrix:
    ------------------------------------------------------------------
    nBTags\b-tagged jets  |    0        1             2
    ------------------------------------------------------------------
      0                   |    1      1-SF      (1-SF1)(1-SF2)
                          |
      1                   |    0       SF    SF1(1-SF2)+(1-SF1)SF2
                          |
      2                   |    0        0           SF1SF2
    ##################################################################
  */
  
  if( nBTags > nBtaggedJets) return 0;
  if( nBTags==0 && nBtaggedJets==0) return 1;

  double weight = 0;
  if(nBtaggedJets==1){
    double SF = GetSF_2016(WP,bjetpt_1,bjetflavour_1,syst);
    if (year==2017) SF = GetSF_2017(WP,bjetpt_1,bjetflavour_1,syst);
    if (year==2018) SF = GetSF_2018(WP,bjetpt_1,bjetflavour_1,syst);
    for( unsigned int i=0; i<=1; ++i ){
      if( i != nBTags ) continue;
      weight += pow(SF,i)*pow(1-SF,1-i);
    }
  }
  else if(nBtaggedJets==2 ){
    double SF1 = GetSF_2016(WP,bjetpt_1,bjetflavour_1,syst);
    double SF2 = GetSF_2016(WP,bjetpt_2,bjetflavour_2,syst);
    if (year==2017){
       SF1 = GetSF_2017(WP,bjetpt_1,bjetflavour_1,syst);
       SF2 = GetSF_2017(WP,bjetpt_2,bjetflavour_2,syst);
    }
    if (year==2018){
       SF1 = GetSF_2018(WP,bjetpt_1,bjetflavour_1,syst);
       SF2 = GetSF_2018(WP,bjetpt_2,bjetflavour_2,syst);
    }
    
    for( unsigned int i=0; i<=1; ++i ){
      for( unsigned int j=0; j<=1; ++j ){
        if( (i+j) != nBTags ) continue;
        weight += pow(SF1,i)*pow(1-SF1,1-i)*pow(SF2,j)*pow(1-SF2,1-j);
      }
    }
  }
  return weight;
}

