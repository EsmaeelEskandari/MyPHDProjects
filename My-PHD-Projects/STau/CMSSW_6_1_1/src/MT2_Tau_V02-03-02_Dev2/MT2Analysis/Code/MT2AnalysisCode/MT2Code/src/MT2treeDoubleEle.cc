#include "MT2tree.hh"
#include "helper/Utilities.hh"
//grep MT2DoubleMuon include/*.hh src/*.cc dict/*.hh
  
void  MT2tree::FillDoubleEle(){

  TVector2 pmiss_vector2;
  TLorentzVector downstream(0.,0.,0.,0.); // no particles are downstream, i.e. not selected jets are upstream. 

  doubleEle[0].Reset();

  for (int i=0 ; i < NEles ; i++){

    if  (ele[i].PassE0_EE) 
      {
        doubleEle[0].Ele0Ind = i ;
	break;
      }
  }
  for (int j = doubleEle[0].Ele0Ind+1 ; j < NEles ; j++){

    if  (ele[j].PassE1_EE) 
      {
	doubleEle[0].Ele1Ind = j ;
	break;
      }
       
  }    
  if( doubleEle[0].Ele0Ind != -1 && doubleEle[0].Ele1Ind != -1 ){
    doubleEle[0].Isolated=1;
    doubleEle[0].MT2 = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, pfmet[0]);
    doubleEle[0].DPhi =(fabs(Util::DeltaPhi(ele[doubleEle[0].Ele0Ind].lv.Phi(),ele[doubleEle[0].Ele1Ind].lv.Phi())));
    doubleEle[0].lv = ele[doubleEle[0].Ele0Ind].lv + ele[doubleEle[0].Ele1Ind].lv;

    doubleEle[0].MT2Imbalanced = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, -(doubleEle[0].lv));

    doubleEle[0].PairCharge = ele[doubleEle[0].Ele0Ind].Charge + ele[doubleEle[0].Ele1Ind].Charge;

    doubleEle[0].Ele0IdIsoSF  = ele[doubleEle[0].Ele0Ind].EleIDIsoSFEleEle;
    doubleEle[0].Ele1IdIsoSF  = ele[doubleEle[0].Ele1Ind].EleIDIsoSFEleEle;
    doubleEle[0].DiEleTrgSF   = GetDoubleEleTrgSF();
    doubleEle[0].PZetaVisible = GetPVisibleZetaEE();
    doubleEle[0].PZeta        = GetPZetaEE();
    doubleEle[0].PZetaImb     = GetPZetaImbEE();
    doubleEle[0].DiLepPtRatio =  GetDiLepPtRatioEE();
    doubleEle[0].PositveLepAngInZFrame     = GetPositiveChargedLeptonDecayAngleinZframeEE();
    doubleEle[0].PositveLepAngwithZBeamPlane =GetPositiveChargedLepWithZBeamPlaneEE();
    doubleEle[0].MinMetLepDPhi= GetMinMetLepDPhiEE();

    pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
    doubleEle[0].MCTcorr = GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);
    pmiss_vector2.Set(-doubleEle[0].lv.Px(), -doubleEle[0].lv.Py());
    doubleEle[0].MCTImbalanced= GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);


    if(fVerbose > 3){
      std::cout<<"EleIndex0: "<< doubleEle[0].Ele0Ind << endl <<"EleIndex1: "<< doubleEle[0].Ele1Ind << endl;
      std::cout<<"Pair Charge1: "<< doubleEle[0].PairCharge <<endl;
      std::cout<<" ChargeEle0: "<< ele[doubleEle[0].Ele0Ind].Charge <<" ChargeEle1: "<<ele[doubleEle[0].Ele1Ind].Charge<<endl;
      std::cout<<"MT2: "<< doubleEle[0].MT2 <<endl;
      std::cout<<"MT2 Imbalanced: "<< doubleEle[0].MT2Imbalanced <<endl;
    }
    
   
  } else {
    doubleEle[0].Ele0Ind =-1;
    doubleEle[0].Ele1Ind =-1;
    for (int i=0 ; i < NEles ; i++){

      if  (ele[i].PassQCDMediumE0_EE) 
	{
	  doubleEle[0].Ele0Ind = i ;
        
	  break;
	}
    }
    for (int j = doubleEle[0].Ele0Ind+1 ; j < NEles ; j++){

      if  (ele[j].PassQCDMediumE1_EE) 
	{
	  doubleEle[0].Ele1Ind = j ;
	  break;
	}
       
    }
 

    if( doubleEle[0].Ele0Ind != -1 && doubleEle[0].Ele1Ind != -1 ){
      doubleEle[0].Isolated=0;
      doubleEle[0].MT2 = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, pfmet[0]);
      doubleEle[0].DPhi =(fabs(Util::DeltaPhi(ele[doubleEle[0].Ele0Ind].lv.Phi(),ele[doubleEle[0].Ele1Ind].lv.Phi())));
      doubleEle[0].lv = ele[doubleEle[0].Ele0Ind].lv + ele[doubleEle[0].Ele1Ind].lv;

      doubleEle[0].MT2Imbalanced = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, -(doubleEle[0].lv));

      doubleEle[0].PairCharge = ele[doubleEle[0].Ele0Ind].Charge + ele[doubleEle[0].Ele1Ind].Charge;

      doubleEle[0].Ele0IdIsoSF  = ele[doubleEle[0].Ele0Ind].EleIDIsoSFEleEle;
      doubleEle[0].Ele1IdIsoSF  = ele[doubleEle[0].Ele1Ind].EleIDIsoSFEleEle;
      doubleEle[0].DiEleTrgSF   = GetDoubleEleTrgSF();
      doubleEle[0].PZetaVisible = GetPVisibleZetaEE();
      doubleEle[0].PZeta        = GetPZetaEE();
      doubleEle[0].PZetaImb     = GetPZetaImbEE();
      doubleEle[0].DiLepPtRatio =  GetDiLepPtRatioEE();
      doubleEle[0].PositveLepAngInZFrame     = GetPositiveChargedLeptonDecayAngleinZframeEE();
      doubleEle[0].PositveLepAngwithZBeamPlane =GetPositiveChargedLepWithZBeamPlaneEE();
      doubleEle[0].MinMetLepDPhi= GetMinMetLepDPhiEE();

      pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
      doubleEle[0].MCTcorr = GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);
      pmiss_vector2.Set(-doubleEle[0].lv.Px(), -doubleEle[0].lv.Py());
      doubleEle[0].MCTImbalanced= GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);


      if(fVerbose > 3){
         
      
	std::cout<<"EleIndex0: "<< doubleEle[0].Ele0Ind << endl <<"EleIndex1: "<< doubleEle[0].Ele1Ind << endl;
	std::cout<<"Pair Charge2: "<< doubleEle[0].PairCharge <<endl;
	std::cout<<" ChargeEle0: "<< ele[doubleEle[0].Ele0Ind].Charge <<" ChargeEle1: "<<ele[doubleEle[0].Ele1Ind].Charge<<endl;
	std::cout<<"MT2: "<< doubleEle[0].MT2 <<endl;
	std::cout<<"MT2 Imbalanced: "<< doubleEle[0].MT2Imbalanced <<endl;
      }
    }
    else {
      doubleEle[0].Ele0Ind =-1;
      doubleEle[0].Ele1Ind =-1;         
      for (int i=0 ; i < NEles ; i++){

	if  (ele[i].PassQCDNonIsoE0_EE) 
	  {
	    doubleEle[0].Ele0Ind = i ;
        
	    break;
	  }
      }
      for (int j = doubleEle[0].Ele0Ind+1 ; j < NEles ; j++){

	if  (ele[j].PassQCDNonIsoE1_EE) 
	  {
	    doubleEle[0].Ele1Ind = j ;
	    break;
	  }
       
      }
   

      if( doubleEle[0].Ele0Ind != -1 && doubleEle[0].Ele1Ind != -1 ){
	doubleEle[0].Isolated=-1;
    
	doubleEle[0].MT2 = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, pfmet[0]);
	doubleEle[0].DPhi =(fabs(Util::DeltaPhi(ele[doubleEle[0].Ele0Ind].lv.Phi(),ele[doubleEle[0].Ele1Ind].lv.Phi())));
	doubleEle[0].lv = ele[doubleEle[0].Ele0Ind].lv + ele[doubleEle[0].Ele1Ind].lv;

	doubleEle[0].MT2Imbalanced = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, -(doubleEle[0].lv));

	doubleEle[0].PairCharge = ele[doubleEle[0].Ele0Ind].Charge + ele[doubleEle[0].Ele1Ind].Charge;

	doubleEle[0].Ele0IdIsoSF  = ele[doubleEle[0].Ele0Ind].EleIDIsoSFEleEle;
	doubleEle[0].Ele1IdIsoSF  = ele[doubleEle[0].Ele1Ind].EleIDIsoSFEleEle;
	doubleEle[0].DiEleTrgSF   = GetDoubleEleTrgSF();
	doubleEle[0].PZetaVisible = GetPVisibleZetaEE();
	doubleEle[0].PZeta        = GetPZetaEE();
	doubleEle[0].PZetaImb     = GetPZetaImbEE();
	doubleEle[0].DiLepPtRatio =  GetDiLepPtRatioEE();
	doubleEle[0].PositveLepAngInZFrame     = GetPositiveChargedLeptonDecayAngleinZframeEE();
	doubleEle[0].PositveLepAngwithZBeamPlane =GetPositiveChargedLepWithZBeamPlaneEE();
	doubleEle[0].MinMetLepDPhi= GetMinMetLepDPhiEE();

        pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
        doubleEle[0].MCTcorr = GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);
        pmiss_vector2.Set(-doubleEle[0].lv.Px(), -doubleEle[0].lv.Py());
        doubleEle[0].MCTImbalanced= GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);


	if(fVerbose > 3){
	  std::cout<<"EleIndex0: "<< doubleEle[0].Ele0Ind << endl <<"EleIndex1: "<< doubleEle[0].Ele1Ind << endl;
	  std::cout<<"Pair Charge3: "<< doubleEle[0].PairCharge <<endl;
	  std::cout<<" ChargeEle0: "<< ele[doubleEle[0].Ele0Ind].Charge <<" ChargeEle1: "<<ele[doubleEle[0].Ele1Ind].Charge<<endl;
	  std::cout<<"MT2: "<< doubleEle[0].MT2 <<endl;
	  std::cout<<"MT2 Imbalanced: "<< doubleEle[0].MT2Imbalanced <<endl;
	}
      } } }

}


 void  MT2tree::FillLooseTightEleFakeRateforEE(){

  TVector2 pmiss_vector2;
  TLorentzVector downstream(0.,0.,0.,0.); // no particles are downstream, i.e. not selected jets are upstream. 

  doubleEle[0].Reset();

  for (int i=0 ; i < NEles ; i++){

    if  (ele[i].PassE0_EE)
      {
        doubleEle[0].Ele0Ind = i ;
        break;
      }
  }
      
      for (int j = 0 ; j < NEles ; j++){

	if  (ele[j].PassLooseIdforQCD) 
	  {
	    doubleEle[0].Ele1Ind = j ;
	    break;
	  }
       

      }

      if( doubleEle[0].Ele0Ind != -1 && doubleEle[0].Ele1Ind != -1 ){
	doubleEle[0].Isolated=-2;
    
	doubleEle[0].MT2 = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, pfmet[0]);
	doubleEle[0].DPhi =(fabs(Util::DeltaPhi(ele[doubleEle[0].Ele0Ind].lv.Phi(),ele[doubleEle[0].Ele1Ind].lv.Phi())));
	doubleEle[0].lv = ele[doubleEle[0].Ele0Ind].lv + ele[doubleEle[0].Ele1Ind].lv;

	doubleEle[0].MT2Imbalanced = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, -(doubleEle[0].lv));

	doubleEle[0].PairCharge = ele[doubleEle[0].Ele0Ind].Charge + ele[doubleEle[0].Ele1Ind].Charge;

	doubleEle[0].Ele0IdIsoSF  = ele[doubleEle[0].Ele0Ind].EleIDIsoSFEleEle;
	doubleEle[0].Ele1IdIsoSF  = ele[doubleEle[0].Ele1Ind].EleIDIsoSFEleEle;
	doubleEle[0].DiEleTrgSF   = GetDoubleEleTrgSF();
	doubleEle[0].PZetaVisible = GetPVisibleZetaEE();
	doubleEle[0].PZeta        = GetPZetaEE();
	doubleEle[0].PZetaImb     = GetPZetaImbEE();
	doubleEle[0].DiLepPtRatio =  GetDiLepPtRatioEE();
	doubleEle[0].PositveLepAngInZFrame     = GetPositiveChargedLeptonDecayAngleinZframeEE();
	doubleEle[0].PositveLepAngwithZBeamPlane =GetPositiveChargedLepWithZBeamPlaneEE();
	doubleEle[0].MinMetLepDPhi= GetMinMetLepDPhiEE();

        pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
        doubleEle[0].MCTcorr = GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);
        pmiss_vector2.Set(-doubleEle[0].lv.Px(), -doubleEle[0].lv.Py());
        doubleEle[0].MCTImbalanced= GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);


	if(fVerbose > 3){
	  std::cout<<"EleIndex0: "<< doubleEle[0].Ele0Ind << endl <<"EleIndex1: "<< doubleEle[0].Ele1Ind << endl;
	  std::cout<<"Pair Charge3: "<< doubleEle[0].PairCharge <<endl;
	  std::cout<<" ChargeEle0: "<< ele[doubleEle[0].Ele0Ind].Charge <<" ChargeEle1: "<<ele[doubleEle[0].Ele1Ind].Charge<<endl;
	  std::cout<<"MT2: "<< doubleEle[0].MT2 <<endl;
	  std::cout<<"MT2 Imbalanced: "<< doubleEle[0].MT2Imbalanced <<endl;

	}}
	  }


void  MT2tree::FillQCDSyst03forEE(){

  TVector2 pmiss_vector2;
  TLorentzVector downstream(0.,0.,0.,0.); // no particles are downstream, i.e. not selected jets are upstream. 

      doubleEle[0].Ele0Ind =-1;
      doubleEle[0].Ele1Ind =-1;         
      for (int i=0 ; i < NEles ; i++){

	if  (ele[i].QCDSyst03E0_EE) 
	  {
	    doubleEle[0].Ele0Ind = i ;
        
	    break;
	  }
      }
      for (int j = doubleEle[0].Ele0Ind+1 ; j < NEles ; j++){

	if  (ele[j].QCDSyst03E1_EE) 
	  {
	    doubleEle[0].Ele1Ind = j ;
	    break;
	  }
       
      }
   

      if( doubleEle[0].Ele0Ind != -1 && doubleEle[0].Ele1Ind != -1 ){
	doubleEle[0].Isolated=-1;
    
	doubleEle[0].MT2 = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, pfmet[0]);
	doubleEle[0].DPhi =(fabs(Util::DeltaPhi(ele[doubleEle[0].Ele0Ind].lv.Phi(),ele[doubleEle[0].Ele1Ind].lv.Phi())));
	doubleEle[0].lv = ele[doubleEle[0].Ele0Ind].lv + ele[doubleEle[0].Ele1Ind].lv;

	doubleEle[0].MT2Imbalanced = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, -(doubleEle[0].lv));

	doubleEle[0].PairCharge = ele[doubleEle[0].Ele0Ind].Charge + ele[doubleEle[0].Ele1Ind].Charge;

	doubleEle[0].Ele0IdIsoSF  = ele[doubleEle[0].Ele0Ind].EleIDIsoSFEleEle;
	doubleEle[0].Ele1IdIsoSF  = ele[doubleEle[0].Ele1Ind].EleIDIsoSFEleEle;
	doubleEle[0].DiEleTrgSF   = GetDoubleEleTrgSF();
	doubleEle[0].PZetaVisible = GetPVisibleZetaEE();
	doubleEle[0].PZeta        = GetPZetaEE();
	doubleEle[0].PZetaImb     = GetPZetaImbEE();
	doubleEle[0].DiLepPtRatio =  GetDiLepPtRatioEE();
	doubleEle[0].PositveLepAngInZFrame     = GetPositiveChargedLeptonDecayAngleinZframeEE();
	doubleEle[0].PositveLepAngwithZBeamPlane =GetPositiveChargedLepWithZBeamPlaneEE();
	doubleEle[0].MinMetLepDPhi= GetMinMetLepDPhiEE();

        pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
        doubleEle[0].MCTcorr = GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);
        pmiss_vector2.Set(-doubleEle[0].lv.Px(), -doubleEle[0].lv.Py());
        doubleEle[0].MCTImbalanced= GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);



	if(fVerbose > 3){
	  std::cout<<"EleIndex0: "<< doubleEle[0].Ele0Ind << endl <<"EleIndex1: "<< doubleEle[0].Ele1Ind << endl;
	  std::cout<<"Pair Charge3: "<< doubleEle[0].PairCharge <<endl;
	  std::cout<<" ChargeEle0: "<< ele[doubleEle[0].Ele0Ind].Charge <<" ChargeEle1: "<<ele[doubleEle[0].Ele1Ind].Charge<<endl;
	  std::cout<<"MT2: "<< doubleEle[0].MT2 <<endl;
	  std::cout<<"MT2 Imbalanced: "<< doubleEle[0].MT2Imbalanced <<endl;
	}
      } 
}

void  MT2tree::FillQCDSyst07forEE(){

  TVector2 pmiss_vector2;
  TLorentzVector downstream(0.,0.,0.,0.); // no particles are downstream, i.e. not selected jets are upstream. 

      doubleEle[0].Ele0Ind =-1;
      doubleEle[0].Ele1Ind =-1;         
      for (int i=0 ; i < NEles ; i++){

	if  (ele[i].QCDSyst07E0_EE) 
	  {
	    doubleEle[0].Ele0Ind = i ;
        
	    break;
	  }
      }
      for (int j = doubleEle[0].Ele0Ind+1 ; j < NEles ; j++){

	if  (ele[j].QCDSyst07E1_EE) 
	  {
	    doubleEle[0].Ele1Ind = j ;
	    break;
	  }
       
      }
   

      if( doubleEle[0].Ele0Ind != -1 && doubleEle[0].Ele1Ind != -1 ){
	doubleEle[0].Isolated=-1;
    
	doubleEle[0].MT2 = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, pfmet[0]);
	doubleEle[0].DPhi =(fabs(Util::DeltaPhi(ele[doubleEle[0].Ele0Ind].lv.Phi(),ele[doubleEle[0].Ele1Ind].lv.Phi())));
	doubleEle[0].lv = ele[doubleEle[0].Ele0Ind].lv + ele[doubleEle[0].Ele1Ind].lv;

	doubleEle[0].MT2Imbalanced = CalcMT2(0, 0,ele[doubleEle[0].Ele0Ind].lv,ele[doubleEle[0].Ele1Ind].lv, -(doubleEle[0].lv));

	doubleEle[0].PairCharge = ele[doubleEle[0].Ele0Ind].Charge + ele[doubleEle[0].Ele1Ind].Charge;

	doubleEle[0].Ele0IdIsoSF  = ele[doubleEle[0].Ele0Ind].EleIDIsoSFEleEle;
	doubleEle[0].Ele1IdIsoSF  = ele[doubleEle[0].Ele1Ind].EleIDIsoSFEleEle;
	doubleEle[0].DiEleTrgSF   = GetDoubleEleTrgSF();
	doubleEle[0].PZetaVisible = GetPVisibleZetaEE();
	doubleEle[0].PZeta        = GetPZetaEE();
	doubleEle[0].PZetaImb     = GetPZetaImbEE();
	doubleEle[0].DiLepPtRatio =  GetDiLepPtRatioEE();
	doubleEle[0].PositveLepAngInZFrame     = GetPositiveChargedLeptonDecayAngleinZframeEE();
	doubleEle[0].PositveLepAngwithZBeamPlane =GetPositiveChargedLepWithZBeamPlaneEE();
	doubleEle[0].MinMetLepDPhi= GetMinMetLepDPhiEE();

        pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
        doubleEle[0].MCTcorr = GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);
        pmiss_vector2.Set(-doubleEle[0].lv.Px(), -doubleEle[0].lv.Py());
        doubleEle[0].MCTImbalanced= GetMCTcorr(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, downstream, pmiss_vector2);


	if(fVerbose > 3){
	  std::cout<<"EleIndex0: "<< doubleEle[0].Ele0Ind << endl <<"EleIndex1: "<< doubleEle[0].Ele1Ind << endl;
	  std::cout<<"Pair Charge3: "<< doubleEle[0].PairCharge <<endl;
	  std::cout<<" ChargeEle0: "<< ele[doubleEle[0].Ele0Ind].Charge <<" ChargeEle1: "<<ele[doubleEle[0].Ele1Ind].Charge<<endl;
	  std::cout<<"MT2: "<< doubleEle[0].MT2 <<endl;
	  std::cout<<"MT2 Imbalanced: "<< doubleEle[0].MT2Imbalanced <<endl;
	}
      }
}

double MT2tree::VetoExtraEleforEE(){
	int nVeto = 0;
	for(int i = 0; i < NEles; i++){
		if(ele[i].RejE2_EE){
			nVeto++;
		}
	}
	if(nVeto == 0)
		return true;
	return false;
}

double MT2tree::VetoMuforEE(){

        int nVeto = 0;
        for(int i = 0; i < NMuons; i++){ 
                if(muo[i].RejMu_EE){
			nVeto++;
                }
        }
	if(nVeto == 0)
		return true;
	return false;
}



double MT2tree::GetDoubleEleTrgSF(){
    return ((ele[doubleEle[0].Ele0Ind].GetEleTrigSFleg17() * ele[doubleEle[0].Ele1Ind].GetEleTrigSFleg8()) + (ele[doubleEle[0].Ele0Ind].GetEleTrigSFleg8()  * ele[doubleEle[0].Ele1Ind].GetEleTrigSFleg17()) - (ele[doubleEle[0].Ele0Ind].GetEleTrigSFleg17() * ele[doubleEle[0].Ele1Ind].GetEleTrigSFleg17())) ;}

   

double MT2tree::GetDiLepPtRatioEE(){
  return(DiLepPtRatio(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv));
}

double MT2tree::GetPositiveChargedLeptonDecayAngleinZframeEE(){
  if (ele[doubleEle[0].Ele0Ind].Charge == 1){
  return(PositiveChargedLeptonDecayAngleinZframe(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv));
   }
  else if (ele[doubleEle[0].Ele1Ind].Charge == 1){
    return(PositiveChargedLeptonDecayAngleinZframe(ele[doubleEle[0].Ele1Ind].lv, ele[doubleEle[0].Ele0Ind].lv));
  }
}


double MT2tree::GetMinMetLepDPhiEE(){
return(MinMetLepDPhi(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv));
}

double MT2tree::GetPositiveChargedLepWithZBeamPlaneEE() {
  if (ele[doubleEle[0].Ele0Ind].Charge == 1){
  return(PositiveChargedLepWithZBeamPlane(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv));
   }
  else if (ele[doubleEle[0].Ele1Ind].Charge == 1){
    return(PositiveChargedLepWithZBeamPlane(ele[doubleEle[0].Ele1Ind].lv, ele[doubleEle[0].Ele0Ind].lv));
  }
}
 
double MT2tree::GetPVisibleZetaEE(){
 return(PVisibleZeta(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv));
}

double MT2tree::GetPZetaEE(){
  return(PZeta(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, pfmet[0]));
}

double MT2tree::GetPZetaImbEE(){
  return(PZeta(ele[doubleEle[0].Ele0Ind].lv, ele[doubleEle[0].Ele1Ind].lv, -(doubleEle[0].lv)));
}

