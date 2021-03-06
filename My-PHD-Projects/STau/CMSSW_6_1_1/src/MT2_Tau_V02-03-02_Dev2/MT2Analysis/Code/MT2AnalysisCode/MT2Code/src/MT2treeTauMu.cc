#include "MT2tree.hh"
#include "helper/Utilities.hh"
std::pair<int,int> MT2tree::MuTauParing(std::vector<int> GoodTau0, std::vector<int> GoodMu0){
  std::pair<int,int> ret = make_pair(-1,-1);
  std::vector<std::pair <double, std::pair<int,int> > > allPairs;
  for(unsigned int i0 = 0; i0 < GoodTau0.size(); i0++){
    int index0 = GoodTau0[i0];
    for(unsigned int i1 = 0; i1 < GoodMu0.size(); i1++){
      int index1 = GoodMu0[i1];
      allPairs.push_back(make_pair((tau[index0].lv.Pt()+ muo[index1].lv.Pt()), make_pair(index0,index1)));
    }
  }	
  PtSumSort mySort;
  std::sort(allPairs.begin(),allPairs.end(),mySort);
  if(allPairs.size() != 0)  
    ret = allPairs[0].second;
  return ret;
}

std::pair<int,int> MT2tree::GetTauMu(){
  std::vector<int> GoodTau0;
  std::vector<int> GoodMu0;

  for(int i=0; i<NTaus; ++i){ 
    if(tau[i].PassTau_MuTau)
      GoodTau0.push_back(i);
  }
  for(int i=0; i<NMuons; ++i){
    if(muo[i].PassMu0_TauMu)
      GoodMu0.push_back(i);
  }
  return (MuTauParing(GoodTau0,GoodMu0));  	
}

std::pair<int,int> MT2tree::GetTauMuFakeRate(){
  std::vector<int> GoodTau0;
  std::vector<int> GoodMu0;

  for(int i=0; i<NTaus; ++i){ 
    if(tau[i].PassQCDTau_MuTau)
      GoodTau0.push_back(i);
  }
  for(int i=0; i<NMuons; ++i){
    if(muo[i].PassMu0_TauMu)
      GoodMu0.push_back(i);
  }
  return (MuTauParing(GoodTau0,GoodMu0));  	
}

std::pair<int,int> MT2tree::GetTauMuQCD(){
  std::vector<int> GoodTau0;
  std::vector<int> GoodMu0;

  for(int i=0; i<NTaus; ++i){ 
    if(tau[i].PassQCDTau_MuTau)
      GoodTau0.push_back(i);
  }
  for(int i=0; i<NMuons; ++i){
    if(muo[i].PassQCDMu0_MuMu)
      GoodMu0.push_back(i);
  }
  return (MuTauParing(GoodTau0,GoodMu0));  	
}




bool MT2tree::HasNoVetoElecForMuTau(){
  int nVeto = 0;
  for(int i = 0; i < NEles; i++){
    if(ele[i].IDVetoMuTau){
      nVeto++;
    }
  }
  if(nVeto == 0)
    return true;
  return false;
}

bool MT2tree::HasNoVetoMuForMuTau(int signalIndex){
  int nVeto = 0;
  for(int i = 0; i < NMuons; i++){
    if(i == signalIndex)
      continue;
    if(muo[i].RejMu1_TauMu){
      nVeto++;
    }
  }
  if(nVeto == 0)
    return true;
  return false;
}

bool MT2tree::HasNoVetoMuForMuTau(){
  int nVeto = 0;
  for(int i = 0; i < NMuons; i++){
    if(i == muTau[0].GetMuIndex0())
      continue;
    if(muo[i].RejMu_TauTau){//decreasing the pt threshold from 15 to 10.
      nVeto++;
    }
  }
  if(nVeto == 0)
    return true;
  return false;
}

void MT2tree::FillMuTau(){
  muTau[0].Reset();	

  TVector2 pmiss_vector2;
  TLorentzVector downstream(0.,0.,0.,0.); // no particles are downstream, i.e. not selected jets are upstream. 
  


  std::pair<int,int> indecies = this->GetTauMu();
  if(this->fVerbose > 3 )
    std::cout<<"muTau[0]: tau index: "<<indecies.first<<", mu index: "<<indecies.second<<endl;
  if(indecies.first != -1 && indecies.second != -1){
    muTau[0].SetIsolated(1);
    muTau[0].SetTauIndex0(indecies.first);
    muTau[0].SetMuIndex0(indecies.second);
    muTau[0].SetSumCharge(tau[indecies.first].Charge + muo[indecies.second].Charge);
    muTau[0].SetMT2(this->CalcMT2(0, false, tau[indecies.first].lv, muo[indecies.second].lv, pfmet[0]));
    muTau[0].SetLV(tau[indecies.first].lv + muo[indecies.second].lv);
    muTau[0].SetMT2Imbalanced(this->CalcMT2(0, false, tau[indecies.first].lv, muo[indecies.second].lv, (-muTau[0].GetLV())));
    pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
    muTau[0].SetMCT(this->GetMCTcorr(muo[muTau[0].GetMuIndex0()].lv, tau[muTau[0].GetTauIndex0()].lv, downstream, pmiss_vector2));
    pmiss_vector2.Set(-muTau[0].GetLV().Px(), -muTau[0].GetLV().Py());
    muTau[0].SetMCTImbalanced(this->GetMCTcorr(muo[muTau[0].GetMuIndex0()].lv, tau[muTau[0].GetTauIndex0()].lv, downstream, pmiss_vector2));
    muTau[0].SetDPhi(fabs(Util::DeltaPhi(tau[indecies.first].lv.Phi(), muo[indecies.second].lv.Phi())));
    muTau[0].SetElecVeto(this->HasNoVetoElecForMuTau());
    muTau[0].SetMuVeto(this->HasNoVetoMuForMuTau(indecies.second));
    muTau[0].SetBeingSignal((muTau[0].isDesirableEvent() && muTau[0].GetSumCharge() == 0));
    muTau[0].SetBeingQCD((muTau[0].isDesirableEvent() && muTau[0].GetSumCharge() != 0));
    muTau[0].SetPVisibleZeta(PVisibleZeta(tau[indecies.first].lv, muo[indecies.second].lv));
    muTau[0].SetPZeta(PZeta(tau[indecies.first].lv, muo[indecies.second].lv, pfmet[0])); 
    muTau[0].SetPZetaImbalanced(PZeta(tau[indecies.first].lv, muo[indecies.second].lv, (-muTau[0].GetLV()))); 
    muTau[0].SetTauTrgSF(tau[indecies.first].trgSFmuTau);
    muTau[0].SetMuTrgSF(muo[indecies.second].trgSFmuTau);
    muTau[0].SetMuIdSF(muo[indecies.second].idSFmuTau);
    muTau[0].SetMuIsoSF(muo[indecies.second].isoSFmuTau);
    muTau[0].SetTauWjetsSF(tau[indecies.first].WjetsSFTauPlusX);
    muTau[0].SetTauEnergySF(tau[indecies.first].energySF);
    muTau[0].SetDiLepPtRatio(DiLepPtRatio(tau[indecies.first].lv, muo[indecies.second].lv));
    if(muo[indecies.second].Charge >= tau[indecies.first].Charge){
      muTau[0].SetPlusLepZAngle(PositiveChargedLeptonDecayAngleinZframe(muo[indecies.second].lv, tau[indecies.first].lv));
      muTau[0].SetPlusLepZBeamAngle(PositiveChargedLepWithZBeamPlane(muo[indecies.second].lv, tau[indecies.first].lv));
    }else{
      muTau[0].SetPlusLepZAngle(PositiveChargedLeptonDecayAngleinZframe(tau[indecies.first].lv, muo[indecies.second].lv));
      muTau[0].SetPlusLepZBeamAngle(PositiveChargedLepWithZBeamPlane(tau[indecies.first].lv, muo[indecies.second].lv));
    }
    muTau[0].SetMinMetLepDPhi(MinMetLepDPhi(tau[indecies.first].lv, muo[indecies.second].lv));
    if(this->fVerbose > 3 )
      muTau[0].printObject();
  }
  else{//Fake Rate method, Iso Mu and NonIso Tau
    muTau[0].Reset();	
    std::pair<int,int> indecies = this->GetTauMuFakeRate();
    if(this->fVerbose > 3 )
      std::cout<<"muTauFakeRate[0]: tau index: "<<indecies.first<<", mu index: "<<indecies.second<<endl;
    if(indecies.first != -1 && indecies.second != -1){
      muTau[0].SetIsolated(0);
      muTau[0].SetTauIndex0(indecies.first);
      muTau[0].SetMuIndex0(indecies.second);
      muTau[0].SetSumCharge(tau[indecies.first].Charge + muo[indecies.second].Charge);
      muTau[0].SetMT2(this->CalcMT2(0, false, tau[indecies.first].lv, muo[indecies.second].lv, pfmet[0]));
      muTau[0].SetLV(tau[indecies.first].lv + muo[indecies.second].lv);
      muTau[0].SetMT2Imbalanced(this->CalcMT2(0, false, tau[indecies.first].lv, muo[indecies.second].lv, (-muTau[0].GetLV())));
      pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
      muTau[0].SetMCT(this->GetMCTcorr(muo[muTau[0].GetMuIndex0()].lv, tau[muTau[0].GetTauIndex0()].lv, downstream, pmiss_vector2));
      pmiss_vector2.Set(-muTau[0].GetLV().Px(), -muTau[0].GetLV().Py());
      muTau[0].SetMCTImbalanced(this->GetMCTcorr(muo[muTau[0].GetMuIndex0()].lv, tau[muTau[0].GetTauIndex0()].lv, downstream, pmiss_vector2));
      muTau[0].SetDPhi(fabs(Util::DeltaPhi(tau[indecies.first].lv.Phi(), muo[indecies.second].lv.Phi())));
      muTau[0].SetElecVeto(this->HasNoVetoElecForMuTau());
      muTau[0].SetMuVeto(this->HasNoVetoMuForMuTau(indecies.second));
      muTau[0].SetBeingSignal((muTau[0].isDesirableEvent() && muTau[0].GetSumCharge() == 0));
      muTau[0].SetBeingQCD((muTau[0].isDesirableEvent() && muTau[0].GetSumCharge() != 0));
      muTau[0].SetPVisibleZeta(PVisibleZeta(tau[indecies.first].lv, muo[indecies.second].lv));
      muTau[0].SetPZeta(PZeta(tau[indecies.first].lv, muo[indecies.second].lv, pfmet[0])); 
      muTau[0].SetPZetaImbalanced(PZeta(tau[indecies.first].lv, muo[indecies.second].lv, (-muTau[0].GetLV()))); 
      muTau[0].SetTauTrgSF(tau[indecies.first].trgSFmuTau);
      muTau[0].SetMuTrgSF(muo[indecies.second].trgSFmuTau);
      muTau[0].SetMuIdSF(muo[indecies.second].idSFmuTau);
      muTau[0].SetMuIsoSF(muo[indecies.second].isoSFmuTau);
      muTau[0].SetTauWjetsSF(tau[indecies.first].WjetsSFTauPlusX);
      muTau[0].SetTauEnergySF(tau[indecies.first].energySF);
      muTau[0].SetDiLepPtRatio(DiLepPtRatio(tau[indecies.first].lv, muo[indecies.second].lv));
      if(muo[indecies.second].Charge >= tau[indecies.first].Charge){
	muTau[0].SetPlusLepZAngle(PositiveChargedLeptonDecayAngleinZframe(muo[indecies.second].lv, tau[indecies.first].lv));
	muTau[0].SetPlusLepZBeamAngle(PositiveChargedLepWithZBeamPlane(muo[indecies.second].lv, tau[indecies.first].lv));
      }else{
	muTau[0].SetPlusLepZAngle(PositiveChargedLeptonDecayAngleinZframe(tau[indecies.first].lv, muo[indecies.second].lv));
	muTau[0].SetPlusLepZBeamAngle(PositiveChargedLepWithZBeamPlane(tau[indecies.first].lv, muo[indecies.second].lv));
      }
      muTau[0].SetMinMetLepDPhi(MinMetLepDPhi(tau[indecies.first].lv, muo[indecies.second].lv));
 
      if(this->fVerbose > 3 )
	muTau[0].printObject();
    }else{//QCD NonIso Mu and non Iso Tau
      muTau[0].Reset();	
      std::pair<int,int> indecies = this->GetTauMuQCD();
      if(this->fVerbose > 3 )
	std::cout<<"muTauQCD[0]: tau index: "<<indecies.first<<", mu index: "<<indecies.second<<endl;
      if(indecies.first != -1 && indecies.second != -1){
	muTau[0].SetIsolated(-1);
	muTau[0].SetTauIndex0(indecies.first);
	muTau[0].SetMuIndex0(indecies.second);
	muTau[0].SetSumCharge(tau[indecies.first].Charge + muo[indecies.second].Charge);
	muTau[0].SetMT2(this->CalcMT2(0, false, tau[indecies.first].lv, muo[indecies.second].lv, pfmet[0]));
	muTau[0].SetLV(tau[indecies.first].lv + muo[indecies.second].lv);
	muTau[0].SetMT2Imbalanced(this->CalcMT2(0, false, tau[indecies.first].lv, muo[indecies.second].lv, (-muTau[0].GetLV())));
	pmiss_vector2.Set(pfmet[0].Px(), pfmet[0].Py());
	muTau[0].SetMCT(this->GetMCTcorr(muo[muTau[0].GetMuIndex0()].lv, tau[muTau[0].GetTauIndex0()].lv, downstream, pmiss_vector2));
	pmiss_vector2.Set(-muTau[0].GetLV().Px(), -muTau[0].GetLV().Py());
	muTau[0].SetMCTImbalanced(this->GetMCTcorr(muo[muTau[0].GetMuIndex0()].lv, tau[muTau[0].GetTauIndex0()].lv, downstream, pmiss_vector2));
	muTau[0].SetDPhi(fabs(Util::DeltaPhi(tau[indecies.first].lv.Phi(), muo[indecies.second].lv.Phi())));
	muTau[0].SetElecVeto(this->HasNoVetoElecForMuTau());
	muTau[0].SetMuVeto(this->HasNoVetoMuForMuTau(indecies.second));
	muTau[0].SetBeingSignal((muTau[0].isDesirableEvent() && muTau[0].GetSumCharge() == 0));
	muTau[0].SetBeingQCD((muTau[0].isDesirableEvent() && muTau[0].GetSumCharge() != 0));
	muTau[0].SetPVisibleZeta(PVisibleZeta(tau[indecies.first].lv, muo[indecies.second].lv));
	muTau[0].SetPZeta(PZeta(tau[indecies.first].lv, muo[indecies.second].lv, pfmet[0])); 
	muTau[0].SetPZetaImbalanced(PZeta(tau[indecies.first].lv, muo[indecies.second].lv, (-muTau[0].GetLV()))); 
	muTau[0].SetTauTrgSF(tau[indecies.first].trgSFmuTau);
 	muTau[0].SetMuTrgSF(muo[indecies.second].trgSFmuTau);
 	muTau[0].SetMuIdSF(muo[indecies.second].idSFmuTau);
 	muTau[0].SetMuIsoSF(muo[indecies.second].isoSFmuTau);
	muTau[0].SetTauWjetsSF(tau[indecies.first].WjetsSFTauPlusX);
	muTau[0].SetTauEnergySF(tau[indecies.first].energySF);
	muTau[0].SetDiLepPtRatio(DiLepPtRatio(tau[indecies.first].lv, muo[indecies.second].lv));
	if(muo[indecies.second].Charge >= tau[indecies.first].Charge){
	  muTau[0].SetPlusLepZAngle(PositiveChargedLeptonDecayAngleinZframe(muo[indecies.second].lv, tau[indecies.first].lv));
	  muTau[0].SetPlusLepZBeamAngle(PositiveChargedLepWithZBeamPlane(muo[indecies.second].lv, tau[indecies.first].lv));
	}else{
	  muTau[0].SetPlusLepZAngle(PositiveChargedLeptonDecayAngleinZframe(tau[indecies.first].lv, muo[indecies.second].lv));
	  muTau[0].SetPlusLepZBeamAngle(PositiveChargedLepWithZBeamPlane(tau[indecies.first].lv, muo[indecies.second].lv));
	}
	muTau[0].SetMinMetLepDPhi(MinMetLepDPhi(tau[indecies.first].lv, muo[indecies.second].lv));
	
	if(this->fVerbose > 3 )
	  muTau[0].printObject();}
    }
  }
}

Int_t MT2tree::minMetTauDPhiMuTauInd(){
  Int_t Ind = -1;
  Float_t mindPhi = 100.0;
  for(int i=0; i<NTaus; ++i){ 
    if(tau[i].PassTau_MuTau){
      Float_t dPhi = fabs(Util::DeltaPhi(tau[i].lv.Phi(), pfmet[0].Phi()));
      if(dPhi < mindPhi){
	Ind = i;
	mindPhi = dPhi;
      }
    }
  }
  return Ind;
}

Float_t MT2tree::minMetTauDPhiMuTau(){
  Float_t dPhi = 100;
  if(minMetTauDPhiMuTauInd() != -1)
    dPhi = fabs(Util::DeltaPhi(tau[minMetTauDPhiMuTauInd()].lv.Phi(), pfmet[0].Phi()));
//     dPhi = fabs(Util::DeltaPhi(tau[muTau[0].GetTauIndex0()].lv.Phi(), pfmet[0].Phi()));

  return dPhi;
}
