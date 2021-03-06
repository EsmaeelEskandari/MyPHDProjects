#ifndef MT2MuTau_hh
#define MT2MuTau_hh
#include <iostream>
using namespace std;

class MT2MuTau: public TObject {
public:
  MT2MuTau(){Reset();};
  ~MT2MuTau(){};
  //Reset values to default
  void Reset(){
    lv.SetPxPyPzE(0, 0, 0, 0);
    tau0Ind = -1;
    mu0Ind = -1;
    chargeSum = -1;
    MT2 = -1.;
    MT2Imbalanced = -1.;
    MCT = -1.;
    MCTImbalanced = -1.;
    hasNoVetoElec = false;
    hasNoVetoMu = false;
    signalMuTau = false;
    qcdMuTau = false;
    DPhi = -9.;
    pVisibleZeta = -9.99;
    pZeta        = -9.99;
    pZetaImbalanced = -9.99;
    tauTrgSF  = -.99;
    muTrgSF   = -.99;
    muIdSF    = -.99;
    muIsoSF   = -.99;
    tauWjetsSF= -.99;
    tauEnergySF= -.99;
    Isolated  = -2.0;//IsoMU and IsoTau 1, IsoMu and NonIsoTau, 0 and NonIsoMu and NonIsoTau -1
    diLepPtRatio= -2.0;
    plusLepZAngle= -4.0;
    plusLepZBeamAngle= -4.0;
    minMetLepDPhi= -4.0;

  };

  //Setters
  void SetTauIndex0(int input){ tau0Ind = input; };
  void SetMuIndex0(int input){ mu0Ind = input; };
  void SetSumCharge(int input){ chargeSum = input; };
  void SetMT2(float input){ MT2 = input; };
  void SetMT2Imbalanced(float input){ MT2Imbalanced = input; };
  void SetMCT(float input){ MCT = input; };
  void SetMCTImbalanced(float input){ MCTImbalanced = input; };
  void SetLV(TLorentzVector input){ lv = input; };
  void SetElecVeto(bool input){ hasNoVetoElec = input; };
  void SetMuVeto(bool input){ hasNoVetoMu = input; };
  void SetBeingSignal(bool input){ signalMuTau = input; };
  void SetBeingQCD(bool input){ qcdMuTau = input; };
  void SetDPhi(float input){DPhi = input;};
  void SetPVisibleZeta(float input){pVisibleZeta = input;};
  void SetPZeta(float input){pZeta = input;};
  void SetPZetaImbalanced(float input){pZetaImbalanced = input;};
  void SetTauEnergySF(float input){tauEnergySF = input;};
  void SetTauTrgSF(float input){tauTrgSF = input;};
  void SetMuTrgSF(float input){muTrgSF = input;};
  void SetMuIdSF(float input){muIdSF = input;};
  void SetMuIsoSF(float input){muIsoSF = input;};
  void SetTauWjetsSF(float input){tauWjetsSF = input;};
  void SetIsolated(int input){ Isolated = input;};
  void SetDiLepPtRatio(float input){diLepPtRatio= input; };
  void SetPlusLepZAngle(float input){plusLepZAngle= input; };
  void SetPlusLepZBeamAngle(float input){plusLepZBeamAngle= input; };
  void SetMinMetLepDPhi(float input){minMetLepDPhi= input; };


  //Getters
  float GetDiLepPtRatio(){return diLepPtRatio;};
  float GetPlusLepZAngle(){return plusLepZAngle;};
  float GetPlusLepZBeamAngle(){return plusLepZBeamAngle;};
  float GetMinMetLepDPhi(){return minMetLepDPhi;};
  int GetIsolated(){return Isolated;};
  float GetTauEnergySF(){return tauEnergySF;};
  float GetTauTrgSF(){return tauTrgSF;};
  float GetMuTrgSF(){return muTrgSF;};
  float GetMuIdSF(){return  muIdSF;};
  float GetMuIsoSF(){return muIsoSF;};
  float GetTauWjetsSF(){return tauWjetsSF;};
  float GetPVisibleZeta(){return pVisibleZeta;};
  float GetPZeta(){return pZeta;};
  float GetPZetaImbalanced(){return pZetaImbalanced;};
  int GetTauIndex0(){ return tau0Ind; };
  int GetMuIndex0(){ return mu0Ind; };
  int GetSumCharge(){ return chargeSum; };
  float GetMT2(){ return MT2; };
  float GetMT2Imbalanced(){ return MT2Imbalanced; };
  float GetMCT(){ return MCT; };
  float GetMCTImbalanced(){ return MCTImbalanced; };
  TLorentzVector GetLV(){ return lv; };
  bool HasNoVetoElec(){ return hasNoVetoElec; };
  bool HasNoVetoMu(){ return hasNoVetoMu; };
  float GetDPhi(){return DPhi;};
  //Event Selection Methods (only focus on leptons)
  bool isDesirableEvent(){
    bool ret = (tau0Ind != -1);
    ret = ret && (mu0Ind != -1);
    ret = ret && hasNoVetoElec;
    ret = ret && hasNoVetoMu;
    return ret;
  }
  bool isSignalMuTau(){
    //                return  (this->isDesirableEvent() && (chargeSum == 0));
    return signalMuTau;
  }
  bool isQCDMuTau(){
    //		return  (this->isDesirableEvent() && (chargeSum != 0));
    return qcdMuTau;
  }
  void printObject(){
    cout<<"MuTau quantities in object: "<<endl;
    cout<<"\ttau0Ind: "<<tau0Ind<<endl;
    cout<<"\tmu0Ind: "<<mu0Ind<<endl;
    cout<<"\tchargeSum: "<<chargeSum<<endl;
    cout<<"\tMT2: "<<MT2<<endl;
    cout<<"\tMT2Imbalanced: "<<MT2Imbalanced<<endl;
    cout<<"\tMETImbalanced: "<<lv.Pt()<<endl;
    cout<<"\tMETImbalancedPhi: "<<(-lv).Phi()<<endl;
    cout<<"\thasNoVetoElec: "<<hasNoVetoElec<<endl;
    cout<<"\thasNoVetoMu: "<<hasNoVetoMu<<endl;
    cout<<"\tsignalMuTau: "<<signalMuTau<<endl;
    cout<<"\tqcdMuTau: "<<qcdMuTau<<endl;
    cout<<"\tDPhi of the two leptons: "<<DPhi<<endl;
  }
private:
  //General properties
  TLorentzVector lv;
  int tau0Ind;
  int mu0Ind;
  int chargeSum;
  float MT2;
  float MT2Imbalanced;
  float MCT;
  float MCTImbalanced;
  bool hasNoVetoElec;
  bool hasNoVetoMu;
  bool signalMuTau;
  bool qcdMuTau;
  float DPhi;
  float pZeta;
  float pZetaImbalanced;
  float pVisibleZeta; 
  float tauTrgSF;
  float muTrgSF;
  float muIdSF;
  float muIsoSF;
  float tauWjetsSF;
  float tauEnergySF;
  int Isolated;

  float diLepPtRatio;
  float plusLepZAngle;
  float plusLepZBeamAngle;
  float minMetLepDPhi;


  ClassDef(MT2MuTau, 1)

    };
#endif /*MT2MuTau_hh*/
                         
