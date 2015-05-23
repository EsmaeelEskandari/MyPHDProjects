/*********************************************************************************
*  Pascal, MT2Analysis, May 26th 2011                                            *
*                                                                                *
*********************************************************************************/
#include <iomanip>
#include <map>

// USER INPUT -------------------------------------------
TString outputdir                 = "LostLepton/test/";
TString fTrigger                  = "HT"; // HT or MHT_HT
Bool_t  fPrintTable               = true;
Bool_t  fMakeEfficiencies         = true;
Int_t   fTypeOfEffErr             = 0;
Bool_t  fMakeEfficienciesPresel   = true;  
Bool_t  fMakePrediction           = true;
Bool_t  fIncludeTaus              = true;  
Bool_t  fIncludeTop               = true;  // include top into signal rather than background 
Bool_t  fTopEfficencies           = true;  // set to true to take the lepton efficiencies from top  
Bool_t  fTopOnly                  = false;  // set to true to treat W as background
Bool_t  fIncludeSingleTop         = true;  // set to true to include single top as signal *** was false by default ***
Bool_t  fDebug                    = true;
Int_t   fNEventsForEff            = 20000000;
Bool_t  fLLSkim                   = false;
Bool_t  fTagandProbeMC            = false;
Bool_t  fMakeEfficienciesPablo    = false; // set to true in order to use Pablo's efficiencies
Int_t   fVerbose                  = 1;// was 2 by default... commented on 8 Dec
Bool_t  fMCClosure                = false; // was false by default... changed on 15 Dec
Bool_t  fWeightedProb             = true; // set to true to account for relative contribution of W and Top for prob and prob_err *** was TRUE by default! *** changed on 10 december
TString fPablofile_ele_data = "/public/MT2Top/LeptJetMult/efficiencies/effElectron.root"; // pablo's files, currently not used
TString fPablofile_muo_data = "/public/MT2Top/LeptJetMult/efficiencies/effMuon.root";     // pablo's files, currently not used
TString fPablofile_ele_mc   = "/public/MT2Top/LeptJetMult/efficiencies/effElectronMC.root"; // pablo's files, currently not used
TString fPablofile_muo_mc   = "/public/MT2Top/LeptJetMult/efficiencies/effMuonMC.root";     // pablo's files, currently not used

// --------------------------------------------------------
TH1::SetDefaultSumw2();
TH2F* WeleEffHistdR;
TH2F* WeleEffHistEta;
TH2F* WeleEffHistdRMC;
TH2F* WeleEffHistEtaMC;
TH2F* WmuoEffHistdR;
TH2F* WmuoEffHistEta;
TH2F* WmuoEffHistdRMC;
TH2F* WmuoEffHistEtaMC;

struct leptonicW{
	bool firstime;	
	bool firstime_bg;	
	bool firstime_leptveto;	
	TH1D* hnData;
	TH1D* hnW;
	TH1D* hnW_bg;
	TH1D* hnW_leptveto;
	TH1D* hnW2;
	TH1D* hnW2_bg;
	TH1D* hnW2_leptveto;
	TH1D* hnW3;
	TH1D* hnW3_bg;
	TH1D* hnW3_leptveto;
	TH1D* hnW4;
	TH1D* hnW4_bg;
	TH1D* hnW4_leptveto;
	TH1D* hTopnW;
	TH1D* hTopnW_bg;
	TH1D* hTopnW_leptveto;
	TH1D* hTopnW_s;
	TH1D* hTopnW_s_bg;
	TH1D* hTopnW_s_leptveto;
	TH1D* hTopnW2_s;
	TH1D* hTopnW2_s_bg;
	TH1D* hTopnW2_s_leptveto;
	TH1D* hTopnW_t;
	TH1D* hTopnW_t_bg;
	TH1D* hTopnW_t_leptveto;
	TH1D* hTopnW2_t;
	TH1D* hTopnW2_t_bg;
	TH1D* hTopnW2_t_leptveto;
	TH1D* hTopnW_tW;
	TH1D* hTopnW_tW_bg;
	TH1D* hTopnW_tW_leptveto;
	TH1D* hTopnW2_tW;
	TH1D* hTopnW2_tW_bg;
	TH1D* hTopnW2_tW_leptveto;
	double binByBinMCTruthError[4];
	double nData;
	double nW;
	double nW_bg;
	double nW_leptveto;
	double nW2;
	double nW2_bg;
	double nW2_leptveto;
	double nW3;
	double nW3_bg;
	double nW3_leptveto;
	double nW4;
	double nW4_bg;
	double nW4_leptveto;
	double TopnW;
	double TopnW_bg;
	double TopnW_leptveto;
	double TopnW_s;
	double TopnW_s_bg;
	double TopnW_s_leptveto;
	double TopnW2_s;
	double TopnW2_s_bg;
	double TopnW2_s_leptveto;
	double TopnW_t;
	double TopnW_t_bg;
	double TopnW_t_leptveto;
	double TopnW2_t;
	double TopnW2_t_bg;
	double TopnW2_t_leptveto;
	double TopnW_tW;
	double TopnW_tW_bg;
	double TopnW_tW_leptveto;
	double TopnW2_tW;
	double TopnW2_tW_bg;
	double TopnW2_tW_leptveto;
	double prob;
	double prob_err;
	double prob2;
	double prob2_err;
	double prob3;
	double prob3_err;
	double prob4;
	double prob4_err;
	double acc;
	double acc_err;
	double rec;
	double rec_err;
	double Topprob;
	double Topprob_err;
	double Topacc;
	double Topacc_err;
	double Toprec;
	double Toprec_err;
	double Top_bg;
	double W_bg;
	double Z_bg;
	double QCD_bg;
	double Other_bg;
	TTree* EffTree;
	vector<double> pt;
	vector<double> eta;
	vector<double> dR;
	vector<double> eff;
	vector<double> err;
	vector<double> ptMC;
	vector<double> etaMC;
	vector<double> dRMC;
	vector<double> effMC;
	vector<double> errMC;
	static const double rel_sys_uncert = 0.05;
	static const double rel_sys_uncert_bg = 1.;
	static const double Wnevents       =  10026385;
	static const double Wnevents2       =  4931110;
	static const double Wnevents3       =  5141023;
	static const double Wnevents4       =  1647807;
	static const double Topnevents     =  6895490;
	static const double Topnevents_s   =  259961;
	static const double Topnevents2_s   = 139974;
	static const double Topnevents_t   =  99876;
	static const double Topnevents2_t   = 1935072;
	static const double Topnevents_tW  =  497658;
	static const double Topnevents2_tW  = 493460;
	static const double Wxsection      = 90.27;
	static const double Wxsection2      = 48.01;
	static const double Wxsection3      = 38.3;
	static const double Wxsection4      = 25.22;
	static const double Topxsection    = 234.;
	static const double Topxsection_s  =   2.82;
	static const double Topxsection2_s  =  1.57;
	static const double Topxsection_t  =  47;
	static const double Topxsection2_t  =  25;
	static const double Topxsection_tW  =  10.7;
	static const double Topxsection2_tW  =  10.7;
	static const double lumi           = 19600;
	TH1D * hdata(){return hnData;}
	TH1D * hnW_scaled(){ 
		if(fIncludeTop)        {
			if(firstime == true)hTopnW->Scale(lumi*Topxsection/Topnevents);
		}
		if(fIncludeSingleTop)  {
			if(firstime == true)hTopnW_s->Scale(lumi*Topxsection_s  /Topnevents_s);
			if(firstime == true)hTopnW2_s->Scale(lumi*Topxsection2_s  /Topnevents2_s);
			if(firstime == true)hTopnW_t->Scale(lumi*Topxsection_t  /Topnevents_t);
			if(firstime == true)hTopnW2_t->Scale(lumi*Topxsection2_t  /Topnevents2_t);
			if(firstime == true)hTopnW_tW->Scale(lumi*Topxsection_tW /Topnevents_tW);
			if(firstime == true)hTopnW2_tW->Scale(lumi*Topxsection2_tW /Topnevents2_tW);
		}
		if(!fTopOnly)          {
			if(firstime == true)hnW->Scale(lumi*Wxsection/Wnevents);
			if(firstime == true)hnW2->Scale(lumi*Wxsection2/Wnevents2);
			if(firstime == true)hnW3->Scale(lumi*Wxsection3/Wnevents3);
			if(firstime == true)hnW4->Scale(lumi*Wxsection4/Wnevents4);
		}
		TH1D* hn=(TH1D*)hTopnW->Clone();	
		hn->Add(hTopnW_s);	
		hn->Add(hTopnW2_s);	
		hn->Add(hTopnW_t);	
		hn->Add(hTopnW2_t);	
		hn->Add(hTopnW_tW);	
		hn->Add(hTopnW2_tW);	
		hn->Add(hnW);	
		hn->Add(hnW2);	
		hn->Add(hnW3);	
		hn->Add(hnW4);
		firstime = false;
		return hn;
	}
	double nW_scaled(){ 
		double res=0;
		if(fIncludeTop)        {
			res +=TopnW*lumi*Topxsection/Topnevents;
		}
		if(fIncludeSingleTop)  {
			res +=TopnW_s* lumi*Topxsection_s  /Topnevents_s + TopnW2_s* lumi*Topxsection2_s  /Topnevents2_s;
			res +=TopnW_t* lumi*Topxsection_t  /Topnevents_t + TopnW2_t* lumi*Topxsection2_t  /Topnevents2_t;
			res +=TopnW_tW*lumi*Topxsection_tW /Topnevents_tW + TopnW2_tW*lumi*Topxsection2_tW /Topnevents2_tW;
		}
		if(!fTopOnly)          {
			res +=nW*lumi*Wxsection/Wnevents+nW2*lumi*Wxsection2/Wnevents2+nW3*lumi*Wxsection3/Wnevents3+nW4*lumi*Wxsection4/Wnevents4;
		}
		cout<<" nW res: "<<res<<endl;
		return res;
	}
	TH1D * hnW_bg_scaled(){ 
		if(fIncludeTop)        {
			if(firstime_bg == true)hTopnW_bg->Scale(lumi*Topxsection/Topnevents);
		}
		if(fIncludeSingleTop)  {
			if(firstime_bg == true)hTopnW_s_bg->Scale(lumi*Topxsection_s  /Topnevents_s);
			if(firstime_bg == true)hTopnW2_s_bg->Scale(lumi*Topxsection2_s  /Topnevents2_s);
			if(firstime_bg == true)hTopnW_t_bg->Scale(lumi*Topxsection_t  /Topnevents_t);
			if(firstime_bg == true)hTopnW2_t_bg->Scale(lumi*Topxsection2_t  /Topnevents2_t);
			if(firstime_bg == true)hTopnW_tW_bg->Scale(lumi*Topxsection_tW  /Topnevents_tW);
			if(firstime_bg == true)hTopnW2_tW_bg->Scale(lumi*Topxsection2_tW  /Topnevents2_tW);
		}
		if(!fTopOnly)           {
			if(firstime_bg == true)hnW_bg->Scale(lumi*Wxsection/Wnevents);	
			if(firstime_bg == true)hnW2_bg->Scale(lumi*Wxsection2/Wnevents2);	
			if(firstime_bg == true)hnW3_bg->Scale(lumi*Wxsection3/Wnevents3);	
			if(firstime_bg == true)hnW4_bg->Scale(lumi*Wxsection4/Wnevents4);	
		}

		TH1D* hn_bg=(TH1D*)hTopnW_bg->Clone();
		hn_bg->Add(hTopnW_s_bg);
		hn_bg->Add(hTopnW2_s_bg);
		hn_bg->Add(hTopnW_t_bg);
		hn_bg->Add(hTopnW2_t_bg);
		hn_bg->Add(hTopnW_tW_bg);
		hn_bg->Add(hTopnW2_tW_bg);
		hn_bg->Add(hnW_bg);
		hn_bg->Add(hnW2_bg);
		hn_bg->Add(hnW3_bg);
		hn_bg->Add(hnW4_bg);
		firstime_bg = false;
		return hn_bg;
	}
	double nW_bg_scaled(){ 
		double res=0;
		if(fIncludeTop)        {
			res +=TopnW_bg*lumi*Topxsection/Topnevents;
		}
		if(fIncludeSingleTop)  {
			res +=TopnW_s_bg* lumi*Topxsection_s  /Topnevents_s + TopnW2_s_bg* lumi*Topxsection2_s  /Topnevents2_s;
			res +=TopnW_t_bg* lumi*Topxsection_t  /Topnevents_t + TopnW2_t_bg* lumi*Topxsection2_t  /Topnevents2_t;
			res +=TopnW_tW_bg*lumi*Topxsection_tW /Topnevents_tW + TopnW2_tW_bg*lumi*Topxsection2_tW /Topnevents2_tW;
		}
		if(!fTopOnly)           {
			res +=nW_bg*lumi*Wxsection/Wnevents+nW2_bg*lumi*Wxsection2/Wnevents2+nW3_bg*lumi*Wxsection3/Wnevents3+nW4_bg*lumi*Wxsection4/Wnevents4;
		}
		cout<<" nW_bg res: "<<res<<endl;
		return res;
	}
	TH1D * hnW_leptveto_scaled(){
		if(fIncludeTop)        {
			if(firstime_leptveto == true)hTopnW_leptveto->Scale(lumi*Topxsection/Topnevents);
		}
		if(fIncludeSingleTop)  {
			if(firstime_leptveto == true)hTopnW_s_leptveto->Scale(lumi*Topxsection_s  /Topnevents_s);
			if(firstime_leptveto == true)hTopnW2_s_leptveto->Scale(lumi*Topxsection2_s  /Topnevents2_s);
			if(firstime_leptveto == true)hTopnW_t_leptveto->Scale(lumi*Topxsection_t  /Topnevents_t);
			if(firstime_leptveto == true)hTopnW2_t_leptveto->Scale(lumi*Topxsection2_t  /Topnevents2_t);
			if(firstime_leptveto == true)hTopnW_tW_leptveto->Scale(lumi*Topxsection_tW  /Topnevents_tW);
			if(firstime_leptveto == true)hTopnW2_tW_leptveto->Scale(lumi*Topxsection2_tW  /Topnevents2_tW);
		}
		if(!fTopOnly)           {
			if(firstime_leptveto == true)hnW_leptveto->Scale(lumi*Wxsection/Wnevents);
			if(firstime_leptveto == true)hnW2_leptveto->Scale(lumi*Wxsection2/Wnevents2);
			if(firstime_leptveto == true)hnW3_leptveto->Scale(lumi*Wxsection3/Wnevents3);
			if(firstime_leptveto == true)hnW4_leptveto->Scale(lumi*Wxsection4/Wnevents4);
		}
		TH1D* hn_leptveto=(TH1D*)hTopnW_leptveto->Clone();
		hn_leptveto->Add(hTopnW_s_leptveto);
		hn_leptveto->Add(hTopnW2_s_leptveto);
		hn_leptveto->Add(hTopnW_t_leptveto);
		hn_leptveto->Add(hTopnW2_t_leptveto);
		hn_leptveto->Add(hTopnW_tW_leptveto);
		hn_leptveto->Add(hTopnW2_tW_leptveto);
		hn_leptveto->Add(hnW_leptveto);
		hn_leptveto->Add(hnW2_leptveto);
		hn_leptveto->Add(hnW3_leptveto);
		hn_leptveto->Add(hnW4_leptveto);

		if(firstime_leptveto == true) for (i = 1; i <= 4 ; i++ ) { 	
		double err = sqrt(hTopnW_leptveto->GetBinContent(i)*pow(lumi*Topxsection/Topnevents,2)+hTopnW_s_leptveto->GetBinContent(i)*pow(lumi*Topxsection_s/Topnevents_s,2)+hTopnW2_s_leptveto->GetBinContent(i)*pow(lumi*Topxsection2_s/Topnevents2_s,2)+hTopnW_t_leptveto->GetBinContent(i)*pow(lumi*Topxsection_t/Topnevents_t,2)+hTopnW2_t_leptveto->GetBinContent(i)*pow(lumi*Topxsection2_t/Topnevents2_t,2)+hTopnW_tW_leptveto->GetBinContent(i)*pow(lumi*Topxsection_tW/Topnevents_tW,2)+hTopnW2_tW_leptveto->GetBinContent(i)*pow(lumi*Topxsection2_tW/Topnevents2_tW,2)+hnW_leptveto->GetBinContent(i)*pow(lumi*Wxsection/Wnevents,2)+hnW2_leptveto->GetBinContent(i)*pow(lumi*Wxsection2/Wnevents2,2)+hnW3_leptveto->GetBinContent(i)*pow(lumi*Wxsection3/Wnevents3,2)+hnW4_leptveto->GetBinContent(i)*pow(lumi*Wxsection4/Wnevents4,2));
		binByBinMCTruthError[i-1] = err;
		}

		firstime_leptveto = false;
		return hn_leptveto;
	}
	double nW_leptveto_scaled(){
		double res=0;
		if(fIncludeTop)        {
			res +=TopnW_leptveto*lumi*Topxsection/Topnevents;
		}
//		cout<<"###### from ttbar: "<<res<<endl;
		if(fIncludeSingleTop)  {
			res +=TopnW_s_leptveto* lumi*Topxsection_s  /Topnevents_s + TopnW2_s_leptveto* lumi*Topxsection2_s  /Topnevents2_s;
//		cout<<"###### S-CH: from single top: "<<TopnW_s_leptveto* lumi*Topxsection_s  /Topnevents_s<<" &&&&&&& from single topbar"<<TopnW2_s_leptveto* lumi*Topxsection2_s  /Topnevents2_s<<endl;
			res +=TopnW_t_leptveto* lumi*Topxsection_t  /Topnevents_t + TopnW2_t_leptveto* lumi*Topxsection2_t  /Topnevents2_t;
//		cout<<"###### T-CH: from single top: "<<TopnW_t_leptveto* lumi*Topxsection_t  /Topnevents_t<<" &&&&&&& from single topbar"<<TopnW2_t_leptveto* lumi*Topxsection2_t  /Topnevents2_t<<endl;
			res +=TopnW_tW_leptveto*lumi*Topxsection_tW /Topnevents_tW + TopnW2_tW_leptveto*lumi*Topxsection2_tW /Topnevents2_tW;
//		cout<<"###### TW-CH: from single top: "<<TopnW_tW_leptveto* lumi*Topxsection_tW  /Topnevents_tW<<" &&&&&&& from single topbar"<<TopnW2_tW_leptveto* lumi*Topxsection2_tW  /Topnevents2_tW<<endl;
		}
		if(!fTopOnly)           {
			res +=nW_leptveto*lumi*Wxsection/Wnevents+nW2_leptveto*lumi*Wxsection2/Wnevents2+nW3_leptveto*lumi*Wxsection3/Wnevents3+nW4_leptveto*lumi*Wxsection4/Wnevents4;
		}
/*		cout<<"###### from W1: "<<nW_leptveto*lumi*Wxsection/Wnevents<<endl;
		cout<<"###### from W2: "<<nW2_leptveto*lumi*Wxsection2/Wnevents2<<endl;
		cout<<"###### from W2: "<<nW3_leptveto*lumi*Wxsection3/Wnevents3<<endl;
		cout<<"###### from W4: "<<nW4_leptveto*lumi*Wxsection4/Wnevents4<<endl;
*/
		
		double error = sqrt(TopnW_leptveto*pow(lumi*Topxsection/Topnevents,2)+TopnW_s_leptveto*pow(lumi*Topxsection_s/Topnevents_s,2)+TopnW2_s_leptveto*pow(lumi*Topxsection2_s/Topnevents2_s,2)+TopnW_t_leptveto*pow(lumi*Topxsection_t/Topnevents_t,2)+TopnW2_t_leptveto*pow(lumi*Topxsection2_t/Topnevents2_t,2)+TopnW_tW_leptveto*pow(lumi*Topxsection_tW/Topnevents_tW,2)+TopnW2_tW_leptveto*pow(lumi*Topxsection2_tW/Topnevents2_tW,2)+nW_leptveto*pow(lumi*Wxsection/Wnevents,2)+nW2_leptveto*pow(lumi*Wxsection2/Wnevents2,2)+nW3_leptveto*pow(lumi*Wxsection3/Wnevents3,2)+nW4_leptveto*pow(lumi*Wxsection4/Wnevents4,2));
		cout<<"###### error from sumw2: "<<error<<endl;

		cout<<" nW_leptveto res: "<<res<<endl;
		return res;
	}
	double bg(){
		if(fIncludeTop && !fTopOnly) return nW_bg_scaled()            +Z_bg + QCD_bg + Other_bg/* + Top_bg*/; // *** Top_bg now contains bkgs from SingleTop, due to changes on line 1142 of MassPlotter.cc which only accounts for single tops... Sun Dec 23 ***
		else if(fTopOnly)            return nW_bg_scaled() +W_bg      +Z_bg + QCD_bg + Other_bg; 
		else                         return nW_bg_scaled() +Top_bg    +Z_bg + QCD_bg + Other_bg; // add full top as backgroun
	}
	double all_MC(){
		if(fIncludeTop && !fTopOnly) return nW_scaled()               + Z_bg + QCD_bg + Other_bg/* + Top_bg*/; // *** Top_bg now contains bkgs from SingleTop, due to changes on line 1142 of MassPlotter.cc which only accounts for single tops... Sun Dec 23 ***
		else if(fTopOnly)            return nW_scaled() + W_bg        + Z_bg + QCD_bg + Other_bg;
		else                         return nW_scaled() + Top_bg      + Z_bg + QCD_bg + Other_bg; 
	}
	double pred(){
		if(fMCClosure){
			return (all_MC()-bg())*(1-prob())/prob();
		}else{
			return (nData - bg())*(1-prob())/prob();
		}
	}
	double pred_error_stat(){
		if(fMCClosure) return 0;
		else return    fabs(sqrt(nData)*(1-prob())/prob());
	}
	double pred_error_sys(){
		if(fMCClosure){
			return sqrt(  pow((all_MC()-bg()) *(1/(prob()*prob())*prob_err_sys()),2)
			             +pow(rel_sys_uncert_bg*bg()*(1-prob())/prob(),2));
		}else{
			return sqrt(  pow((nData-bg()) *(1/(prob()*prob())*prob_err_sys()),2)
			     +pow(rel_sys_uncert_bg*bg()*(1-prob())/prob(),2));
		}
	}
	double prob(){
		if(! fMakeEfficienciesPablo){
			if(fWeightedProb){
				double WEvents   = (nW - nW_bg)      *lumi*Wxsection/Wnevents;
				double WEvents2   = (nW2 - nW2_bg)      *lumi*Wxsection2/Wnevents2;
				double WEvents3   = (nW3 - nW3_bg)      *lumi*Wxsection3/Wnevents3;
				double WEvents4   = (nW4 - nW4_bg)      *lumi*Wxsection4/Wnevents4;
				double TopEvents = (TopnW - TopnW_bg)*lumi*Topxsection/Topnevents;
				return (Topprob*TopEvents + prob*WEvents + prob2*WEvents2 + prob3*WEvents3 + prob4*WEvents4)/(TopEvents+WEvents+WEvents2+WEvents3+WEvents4);
			}else{
				if(fTopEfficencies)  return Topprob;
				else                 return prob;
			}
		}else if(fMCClosure && fMakeEfficienciesPablo &&!fWeightedProb){
			if(fTopEfficencies)  return TPRecoMC()*Topacc;
			else                 return TPRecoMC()*acc;
		}else if(!fMCClosure && fMakeEfficienciesPablo &&!fWeightedProb){
			if(fTopEfficencies)  return TPReco()*Topacc;
			else                 return TPReco()*acc;
		}else{
			cout << " what do you want? " << endl; exit(1);
		}
	}
	double prob_err_sys(){
		if(fMakeEfficienciesPablo){
			if(fMCClosure) {
				if(fTopEfficencies) {
					return sqrt(pow(Topacc*TPRecoErrMC(),2)+pow(Accerr()*TPRecoMC(),2));
				}else{
					return sqrt(pow(acc*TPRecoErrMC(),2)+pow(Accerr()*TPRecoMC(),2));
				}
			}else   {
				if(fTopEfficencies) { 
					return sqrt(pow(Topacc*TPRecoErr(),2)  +pow(Accerr()*TPReco()  ,2));
				}else {
					return sqrt(pow(acc*TPRecoErr(),2)  +pow(Accerr()*TPReco()  ,2));
				}
			}
		}else{
			if(fWeightedProb){
				double WEvents   = (nW - nW_bg)      *lumi*Wxsection/Wnevents;
                                double WEvents2   = (nW2 - nW2_bg)      *lumi*Wxsection2/Wnevents2;
                                double WEvents3   = (nW3 - nW3_bg)      *lumi*Wxsection3/Wnevents3;
                                double WEvents4   = (nW4 - nW4_bg)      *lumi*Wxsection4/Wnevents4;
				double TopEvents = (TopnW - TopnW_bg)*lumi*Topxsection/Topnevents;
				double err       = (Topprob_err*TopEvents + prob_err*WEvents + prob2_err*WEvents2 + prob3_err*WEvents3 + prob4_err*WEvents4)/(TopEvents+WEvents+WEvents2+WEvents3+WEvents4);
				return sqrt(pow(rel_sys_uncert*prob(),2)+ pow(err,2));
				
			}else{
				if(fTopEfficencies){
					return sqrt(pow(rel_sys_uncert*Topprob,2)+ pow(Topprob_err,2));
				}else{
					return sqrt(pow(rel_sys_uncert*prob,2)+ pow(prob_err,2));
				}
			}
		}

	}
	double TPRecoMC(){
			double reco_eff=0;
			for(int i=0; i<effMC.size(); ++i) reco_eff+=effMC[i];
			reco_eff=reco_eff/effMC.size();
			return reco_eff;
	}
	double TPRecoErrMC(){
			double reco_err=0;
			for(int i=0; i<errMC.size(); ++i) reco_err+=errMC[i]*errMC[i];
			reco_err=sqrt(reco_err)/errMC.size();
			return sqrt(reco_err*reco_err+ pow(rel_sys_uncert*TPRecoMC(),2));
	}
	double TPReco(){
			double reco_eff=0;
			for(int i=0; i<eff.size(); ++i) reco_eff+=eff[i];
			reco_eff=reco_eff/eff.size();
			return reco_eff;
	}
	double TPRecoErr(){
			double reco_err=0;
			for(int i=0; i<err.size(); ++i) reco_err+=err[i]*err[i];
			reco_err=sqrt(reco_err)/err.size();
			return sqrt(reco_err*reco_err+ pow(rel_sys_uncert*TPReco(),2));
	}
	double Accerr(){
		if(fTopEfficencies) return sqrt(pow(rel_sys_uncert*Topacc,2)+Topacc_err*Topacc_err);
		else                return sqrt(pow(rel_sys_uncert*acc,2)   +acc_err*acc_err);
	}
} Wele, Wmuo;
Wele.firstime=true;
Wele.firstime_bg=true;
Wele.firstime_leptveto=true;
Wmuo.firstime=true;
Wmuo.firstime_bg=true;
Wmuo.firstime_leptveto=true;
map<int, double> mymap;
TH1D* zbg_e;
TH1D* qcdbg_e;
TH1D* zbg_m;
TH1D* qcdbg_m;
double zbg_ele[4];
double zbg_muo[4];
double qcdbg_ele[4];
double qcdbg_muo[4];

//double nTau_leptveto=0;
TH1D* findingRLL(){

//	TH1::SetDefaultSumw2();
	TH1D * h = new TH1D("eff","eff",2,0,2);	

	double muo = Wmuo.prob();
	double ele = Wele.prob();

	h->SetBinContent(1,muo);
	h->SetBinError(1,Wmuo.prob_err_sys());
	h->SetBinContent(2,ele);
	h->SetBinError(2,Wele.prob_err_sys());

	TH1D * f = new TH1D("f","f",2,0,2);	
        f->SetBinContent(1,0.803658);
        f->SetBinContent(2,0.81126);
        f->SetBinError(1,0.0242723);
        f->SetBinError(2,0.0280645);

	TH1D * g = f->Clone();

	f->Divide(f, h, 1.0, 1.0, "B");
	//f->Divide(h);
	f->Add(g,-1);

	cout<<"muo; RLL : "<<f->GetBinContent(1)<<" +- "<<f->GetBinError(1)<<endl;
	cout<<"ele; RLL : "<<f->GetBinContent(2)<<" +- "<<f->GetBinError(2)<<endl;
	return f;
}

//__________________________________
const int gNMT2bins                   = 19;
double    gMT2bins[gNMT2bins+1]   = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 85, 105, 135, 180, 260, 360, 500};

const int gNMT2bins_l                   = 14;
double    gMT2bins_l[gNMT2bins+1]   = {0, 10, 20, 30, 40, 50, 65, 80, 95, 115, 140, 180, 250, 350, 500};
//__________________________________



void run_LostLeptonSmearedJetsNewBTag(){

	gSystem->Load("libPhysics");
	gSystem->CompileMacro("../MT2Code/src/MassPlotter.cc", "k");

	if( (fTopOnly && !fTopEfficencies) || (!fIncludeTop && fTopOnly) || (fIncludeSingleTop && !fIncludeTop)){
		cout << "make up your mind" << endl; exit(1);
	}

	if(fTagandProbeMC &&!fMakeEfficienciesPablo) exit(1);
        // ------------------------
	mymap = calcAvrPUWeight();
	if(fMakeEfficiencies)      getEfficiencies( fNEventsForEff);
	if(fMakeEfficienciesPablo) readEfficienciesPablo();
	if(fMakePrediction)   {
		makePlots(); 
		makePrediction();
	}
	if(fPrintTable) printTable();
	InclusiveEstimation();
	LostLeptonInMT2Bins();
        // ------------------------

}

void getEfficiencies(Long64_t nevents){
	
	int verbose = 3;

	MassPlotter *tA = new MassPlotter(outputdir, "MassPlots.root");
	tA->setVerbose(verbose);
	if(fMakeEfficienciesPresel){
		if(fLLSkim) tA->init("samples_LLSkim/samples_WJets_Presel.dat");	
		else        tA->init("samples/samplesMineSmearedJetMETNewBTagParkedNewSamples_No7trig.dat");//samples/samplesMineSmearedJetMETNewBTag.dat");	
	} else  tA->init("samples_LLSkim/samples_WJets.dat");
		
	tA->PrintWEfficiency(9 ,"W", "ele", nevents, fIncludeTaus);
	tA->PrintWEfficiency(9 ,"W", "muo", nevents, fIncludeTaus);

	Wele.prob          =tA->fWpred.Wenu_prob;
	Wele.prob_err      =tA->fWpred.Wenu_prob_err;
	Wmuo.prob          =tA->fWpred.Wmunu_prob;
	Wmuo.prob_err      =tA->fWpred.Wmunu_prob_err;
	
	Wele.acc           =tA->fWpred.Wenu_acc;
	Wele.acc_err       =tA->fWpred.Wenu_acc_err;
	Wele.rec           =tA->fWpred.Wenu_rec;
	Wele.rec_err       =tA->fWpred.Wenu_rec_err;
	
	Wmuo.acc           =tA->fWpred.Wmunu_acc;
	Wmuo.acc_err       =tA->fWpred.Wmunu_acc_err;
	Wmuo.rec           =tA->fWpred.Wmunu_rec;
	Wmuo.rec_err       =tA->fWpred.Wmunu_rec_err;
// ============================================================

	tA->PrintWEfficiency(10 ,"W", "ele", nevents, fIncludeTaus);
	tA->PrintWEfficiency(10 ,"W", "muo", nevents, fIncludeTaus);
	Wele.prob2          =tA->fWpred.Wenu_prob;
	Wele.prob2_err      =tA->fWpred.Wenu_prob_err;
	Wmuo.prob2          =tA->fWpred.Wmunu_prob;
	Wmuo.prob2_err      =tA->fWpred.Wmunu_prob_err;


	tA->PrintWEfficiency(11 ,"W", "ele", nevents, fIncludeTaus);
	tA->PrintWEfficiency(11 ,"W", "muo", nevents, fIncludeTaus);
	Wele.prob3          =tA->fWpred.Wenu_prob;
	Wele.prob3_err      =tA->fWpred.Wenu_prob_err;
	Wmuo.prob3          =tA->fWpred.Wmunu_prob;
	Wmuo.prob3_err      =tA->fWpred.Wmunu_prob_err;


	tA->PrintWEfficiency(12 ,"W", "ele", nevents, fIncludeTaus);
	tA->PrintWEfficiency(12 ,"W", "muo", nevents, fIncludeTaus);
	Wele.prob4          =tA->fWpred.Wenu_prob;
	Wele.prob4_err      =tA->fWpred.Wenu_prob_err;
	Wmuo.prob4          =tA->fWpred.Wmunu_prob;
	Wmuo.prob4_err      =tA->fWpred.Wmunu_prob_err;

// ============================================================


/*	if(fIncludeTop){
		if(fMakeEfficienciesPresel) {
			if(fLLSkim) tA->init("samples_LLSkim/samples_Top_Presel.dat");	
			else        tA->init("samples/samplesMine.dat");	
		}
		else       tA->init("samples_LostLepton//samples_Top.dat");
*/
		tA->PrintWEfficiency(19 ,"Top", "ele", nevents, fIncludeTaus);
		tA->PrintWEfficiency(19 ,"Top", "muo", nevents, fIncludeTaus);
		Wele.Topacc           =tA->fWpred.TopWenu_acc;
		Wele.Topacc_err       =tA->fWpred.TopWenu_acc_err;
		Wele.Toprec           =tA->fWpred.TopWenu_rec;
		Wele.Toprec_err       =tA->fWpred.TopWenu_rec_err;
		Wmuo.Topacc           =tA->fWpred.TopWmunu_acc;
		Wmuo.Topacc_err       =tA->fWpred.TopWmunu_acc_err;
		Wmuo.Toprec           =tA->fWpred.TopWmunu_rec;
		Wmuo.Toprec_err       =tA->fWpred.TopWmunu_rec_err;
		
		Wele.Topprob          =tA->fWpred.TopWenu_prob;
		Wele.Topprob_err      =tA->fWpred.TopWenu_prob_err;
		Wmuo.Topprob          =tA->fWpred.TopWmunu_prob;
		Wmuo.Topprob_err      =tA->fWpred.TopWmunu_prob_err;

		cout << "Wele prob    " << Wele.prob    << " pm " << Wele.prob_err    << endl;
		cout << "Wele prob    " << Wele.prob2    << " pm " << Wele.prob2_err    << endl;
		cout << "Wele prob    " << Wele.prob3    << " pm " << Wele.prob3_err    << endl;
		cout << "Wele prob    " << Wele.prob4    << " pm " << Wele.prob4_err    << endl;
		cout << "TopWele prob " << Wele.Topprob << " pm " << Wele.Topprob_err << endl;
		cout << "Wmuo prob    " << Wmuo.prob    << " pm " << Wmuo.prob_err    << endl;
		cout << "Wmuo prob    " << Wmuo.prob2    << " pm " << Wmuo.prob2_err    << endl;
		cout << "Wmuo prob    " << Wmuo.prob3    << " pm " << Wmuo.prob3_err    << endl;
		cout << "Wmuo prob    " << Wmuo.prob4    << " pm " << Wmuo.prob4_err    << endl;
		cout << "TopWmuo prob " << Wmuo.Topprob << " pm " << Wmuo.Topprob_err << endl;
		/*cout << "Wele acc     " << Wele.acc     << " pm " << Wele.acc_err     << endl;
		cout << "Wele rec     " << Wele.rec     << " pm " << Wele.rec_err     << endl;
		cout << "TopWele acc  " << Wele.Topacc  << " pm " << Wele.Topacc_err     << endl;
		cout << "TopWele rec  " << Wele.Toprec  << " pm " << Wele.Toprec_err     << endl;
		cout << "Wmuo acc     " << Wmuo.acc     << " pm " << Wmuo.acc_err     << endl;
		cout << "Wmuo rec     " << Wmuo.rec     << " pm " << Wmuo.rec_err     << endl;
		cout << "TopWmuo acc  " << Wmuo.Topacc  << " pm " << Wmuo.Topacc_err     << endl;
		cout << "TopWmuo rec  " << Wmuo.Toprec  << " pm " << Wmuo.Toprec_err     << endl;*/
/*	}else{
		Wele.Topacc           =0;
		Wele.Topacc_err       =0;
		Wele.Toprec           =0;
		Wele.Toprec_err       =0;
		Wmuo.Topacc           =0;
		Wmuo.Topacc_err       =0;
		Wmuo.Toprec           =0;
		Wmuo.Toprec_err       =0;
		
		Wele.Topprob          =0;
		Wele.Topprob_err      =0;
		Wmuo.Topprob          =0;
		Wmuo.Topprob_err      =0;
	}
*/


	delete tA;
}
void makePlots(){
  TString samples   = "./samples/samplesMineSmearedJetMETNewBTagParkedNewSamples_No7trig.dat";//samplesMineSmearedJetMETNewBTag.dat";
/*
	TString samples;
	if     (fTrigger=="HT")     {
		if(fLLSkim) samples = "samples_LLSkim/samples_MG_V02-01-02_golden_HTonly.dat";
		else        samples = "samples_LostLepton/samples_MG_V02-01-02_golden_HTonly.dat";
	}
	else if(fTrigger=="MHT_HT") samples = "samples_LLSkim/samples_MG_V02-01-02_golden.dat";
*/
	int verbose = 3;

	MassPlotter *tA = new MassPlotter(outputdir, "MassPlots.root");
	tA->setVerbose(verbose);
	tA->init(samples);

	std::ostringstream cutStream;
        cutStream << " "
            << "misc.MET>30"                                                << "&&"
	  // << "misc.MT2>125  "                                              << "&&" // for talk
            << "NJetsIDLoose40  >=4"                                         << "&&"

            << "NBJetsCSVT > 0"                                                  << "&&"
            //<< "(NEles==0  || ele[0].lv.Pt()<5)"                             << "&&" // because we want to estimated the bkg to exactly one electron
            //<< "(NMuons==0 || muo[0].lv.Pt()<5)"                             << "&&" // because we want to estimated the bkg to exactly one muon
            << "misc.Jet0Pass ==1"                                           << "&&"
            << "misc.Jet1Pass ==1"                                           << "&&"
            << "misc.PassJetID ==1"                                          << "&&"// un-commented on 11 dec
            << "misc.Vectorsumpt < 70"                                       << "&&"
//            << "(misc.MinMetJetDPhi4 >0.3)"                                  << "&&"// cut on dPhi is relaxed for Lost Lepton estimation, applied on Wed 10 April

            <<"(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0))"<<"||"
            //<<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0)))";
            <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0)))";

	//__________________________________________________________________________________________
	// ATTENTION! makePlot adds the underflow and the overflow to the fist and last bin
	//            this is probably not what you want. 
	//            comment out appropriate lines in MassPlotter::makePlot()
	//__________________________________________________________________________________________

	std::ostringstream triggerStream;
        triggerStream << "( "
                <<" misc.ProcessID!=0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 " <<"&&"
                <<" misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 " <<"&&"
                <<" misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 " <<"&&"
                <<" misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 )" <<"&&("
                << "(((trigger.HLT_QuadJet80_v1 ==1)" << "||"
                << "(trigger.HLT_QuadJet80_v2 ==1)" << "||"
                << "(trigger.HLT_QuadJet80_v3 ==1)" << "||"
                << "(trigger.HLT_QuadJet80_v4 ==1)" << "||"
                << "(trigger.HLT_QuadJet80_v6 ==1)" << ") &&"
                << " ((NJetsIDLoose40  >=4 "            << "&&"
                << " jet[3].lv.Pt() >= 100.0 "       << ") || "
                << " (NJetsIDLoose40  >=5 "            << "&&"
                << " jet[4].lv.Pt() >= 85.0 "       << "))) || "
                << "(((trigger.HLT_SixJet45_v1 ==1)" << "||"
                << "(trigger.HLT_SixJet45_v2 ==1)" << "||"
                << "(trigger.HLT_SixJet45_v3 ==1)" << "||"
                << "(trigger.HLT_SixJet45_v4 ==1)" << "||"
                << "(trigger.HLT_SixJet45_v6 ==1)" << ") &&"
                << " (NJetsIDLoose40  >=6 "            << "&&"
                << " jet[5].lv.Pt() >= 65.0 "       << ")))))";
                //<< " jet[5].lv.Pt() >= 65.0 "       << ") ||"
                //<< " (NJetsIDLoose40  >=7 "            << "&&"
                //<< " jet[6].lv.Pt() >= 55.0 "       << ")))))";
/*
	triggerStream << "( "
		<< "(trigger.HLT_HT440_v2==1 && misc.Run<=161176)" << "||"
		<< "(trigger.HLT_HT450_v2==1 && (misc.Run>=161217 && misc.Run<=163261))" << "||"
		<< "(trigger.HLT_HT500_v3==1 && (misc.Run>=163270 && misc.Run<=163869))" << "||"
		<< "(trigger.HLT_HT550_v4==1 && (misc.Run>=165088 && misc.Run<=165633))" << "||"
		<< "(trigger.HLT_HT550_v5==1 && (misc.Run>=165970 && misc.Run<=167043 && misc.Run!=166346))" << "||"
		<< "(trigger.HLT_HT550_v6==1 && (misc.Run==166346))"                     << "||"
		<< "(trigger.HLT_HT550_v7==1 && (misc.Run>=167078 && misc.Run<=167913))" << "||"
		<< "(trigger.HLT_HT550_v8==1 && (misc.Run>=169561 && misc.Run<=173198))" << "||"
		<< "(trigger.HLT_HT600_v1==1 && (misc.Run>=173236 && misc.Run<=173692))" << "||"
		<< "(trigger.HLT_HT600_v1==1 && (misc.Run>=175860 && misc.Run<=177452))" << " )";
*/
  	TString trigger = triggerStream.str().c_str();
	TString cuts = cutStream.str().c_str();

	//TString ele_cuts = cuts+"&&ele[0].lv.Pt()>=5";
	//TString muo_cuts = cuts+"&&muo[0].lv.Pt()>=5";

 	TString ele_cuts = cuts;//+"&& ele[0].MT<100";
	TString muo_cuts = cuts;//+"&& muo[0].MT<100";

	//	tA->makePlot("ele[0].lv.Pt()"/*misc.MT2"*/                       , ele_cuts,  -4, -1, -11 ,  trigger, "electron p_{T}"/*electron M_{T}*/     , /*60*/20,0 /*0*/, 500           ,   false,   true , true,   true,  true,  false , 1);
	
  //    	tA->makePlot("ele[0].lv.Pt()"/*misc.MT2"*/                       , ele_cuts,  -4, -1, -11 ,  trigger, "electron p_{T}"/*electron M_{T}*/     , /*60*/20,0 /*0*/, 500           ,   false,   false , true,   true,  true,  true , 1);
        //   	tA->makePlot("muo[0].lv.Pt()"/*misc.MT2"*/                        , muo_cuts,  -4, -1, -13 ,  trigger, "muon p_{T}"        , /*60*/20, 0/*0*/, 500           ,   false,   false , true,   true,  true,  true , 1);

	//	tA->makePlot("ele[0].MT"/*misc.MT2"*/                       , ele_cuts,  -4, -1, -11 ,  trigger, "electron m_{T}"/*electron M_{T}*/     , /*60*/20,0 /*0*/, 500           ,   false,   false , true,   true,  true,  true , 1);
		tA->makePlot("muo[0].MT"/*misc.MT2"*/                        , muo_cuts,  -4, -1, -13 ,  trigger, "muon m_{T}"        , /*60*/20, 0/*0*/, 500           ,   false,   false , true,   true,  true,  true , 1);

	// save number of background events
	Wmuo.Top_bg   =tA->fWpred.Top_bg_mu;
	Wele.Top_bg   =tA->fWpred.Top_bg_e;
	Wmuo.W_bg     =tA->fWpred.W_bg_mu;
	Wele.W_bg     =tA->fWpred.W_bg_e;
	Wmuo.Z_bg     =tA->fWpred.Z_bg_mu;
	Wele.Z_bg     =tA->fWpred.Z_bg_e;
	Wmuo.QCD_bg   =tA->fWpred.QCD_bg_mu;
	Wele.QCD_bg   =tA->fWpred.QCD_bg_e;
	Wmuo.Other_bg =tA->fWpred.Other_bg_mu;
	Wele.Other_bg =tA->fWpred.Other_bg_e;

	zbg_m     =tA->fWpred.hZ_bg_mu;
	zbg_muo[0] = zbg_m->GetBinContent(1);
	zbg_muo[1] = zbg_m->GetBinContent(2);
	zbg_muo[2] = zbg_m->GetBinContent(3);
	zbg_muo[3] = zbg_m->GetBinContent(4);
	zbg_e     =tA->fWpred.hZ_bg_e;
	zbg_ele[0] = zbg_e->GetBinContent(1);
	zbg_ele[1] = zbg_e->GetBinContent(2);
	zbg_ele[2] = zbg_e->GetBinContent(3);
	zbg_ele[3] = zbg_e->GetBinContent(4);
	qcdbg_m   =tA->fWpred.hQCD_bg_mu;
	qcdbg_muo[0] = qcdbg_m->GetBinContent(1);
	qcdbg_muo[1] = qcdbg_m->GetBinContent(2);
	qcdbg_muo[2] = qcdbg_m->GetBinContent(3);
	qcdbg_muo[3] = qcdbg_m->GetBinContent(4);
	qcdbg_e   =tA->fWpred.hQCD_bg_e;
	qcdbg_ele[0] = qcdbg_e->GetBinContent(1);
	qcdbg_ele[1] = qcdbg_e->GetBinContent(2);
	qcdbg_ele[2] = qcdbg_e->GetBinContent(3);
	qcdbg_ele[3] = qcdbg_e->GetBinContent(4);

	// delete pointer
	delete tA;

/*
	cout<<"--->>>"<<" Wele.QCD_bg: "<<Wele.QCD_bg<<" from integral: "<<qcdbg_e->Integral()<<endl;
	cout<<"			--->>> bin : "<<qcdbg_e->GetBinContent(0)<<endl;
	cout<<"			--->>> bin : "<<qcdbg_e->GetBinContent(1)<<endl;
	cout<<"			--->>> bin : "<<qcdbg_e->GetBinContent(2)<<endl;
	cout<<"			--->>> bin : "<<qcdbg_e->GetBinContent(3)<<endl;
	cout<<"--->>>"<<" Wele.Z_bg: "<<Wele.Z_bg<<" from integral: "<<zbg_e->Integral()<<endl;
	cout<<"			--->>> bin : "<<zbg_e->GetBinContent(0)<<endl;
	cout<<"			--->>> bin : "<<zbg_e->GetBinContent(1)<<endl;
	cout<<"			--->>> bin : "<<zbg_e->GetBinContent(2)<<endl;
	cout<<"			--->>> bin : "<<zbg_e->GetBinContent(3)<<endl;

	//cout<<"--->>>"<<" Wmuo.QCD_bg: "<<Wmuo.QCD_bg<<" from integral: "<<qcdbg_m->Integral()<<endl;
	cout<<"			--->>> bin : "<<qcdbg_muo[0]<<endl;
	cout<<"			--->>> bin : "<<qcdbg_muo[1]<<endl;
	cout<<"			--->>> bin : "<<qcdbg_muo[2]<<endl;
	cout<<"			--->>> bin : "<<qcdbg_muo[3]<<endl;
	//cout<<"--->>>"<<" Wmuo.Z_bg: "<<Wmuo.Z_bg<<" from integral: "<<zbg_m->Integral()<<endl;
	cout<<"			--->>> bin : "<<zbg_muo[0]<<endl;
	cout<<"			--->>> bin : "<<zbg_muo[1]<<endl;
	cout<<"			--->>> bin : "<<zbg_muo[2]<<endl;
	cout<<"			--->>> bin : "<<zbg_muo[3]<<endl;

	cout<<"--->>>"<<" Wele.W_bg: "<<Wele.W_bg<<endl;
	cout<<"--->>>"<<" Wele.Top_bg: "<<Wele.Top_bg<<endl;
	cout<<"--->>>"<<" Wele.Other_bg: "<<Wele.Other_bg<<endl;
	cout<<"--->>>"<<" Wmuo.QCD_bg: "<<Wmuo.QCD_bg<<" from integral: "<<(Wmuo.qcdbg)->Integral()<<endl;
	cout<<"--->>>"<<" Wmuo.Z_bg: "<<Wmuo.Z_bg<<" from integral: "<<(Wmuo.zbg)->Integral()<<endl;
	cout<<"--->>>"<<" Wmuo.W_bg: "<<Wmuo.W_bg<<endl;
	cout<<"--->>>"<<" Wmuo.Top_bg: "<<Wmuo.Top_bg<<endl;
	cout<<"--->>>"<<" Wmuo.Other_bg: "<<Wmuo.Other_bg<<endl;
*/
}

void makePrediction(){
	Wele.hnW                        = get_histo("ele"                , false, false, 9);
	Wele.hnW_bg                     = get_histo("ele"                , true,  false, 9);
	Wele.hnW_leptveto               = get_histo("ele"                , false, true, 9);
	Wele.hnW2                        = get_histo("ele"                , false, false, 10);
	Wele.hnW2_bg                     = get_histo("ele"                , true,  false, 10);
	Wele.hnW2_leptveto               = get_histo("ele"                , false, true, 10);
	Wele.hnW3                        = get_histo("ele"                , false, false, 11);
	Wele.hnW3_bg                     = get_histo("ele"                , true,  false, 11);
	Wele.hnW3_leptveto               = get_histo("ele"                , false, true, 11);
	Wele.hnW4                        = get_histo("ele"                , false, false, 12);
	Wele.hnW4_bg                     = get_histo("ele"                , true,  false, 12);
	Wele.hnW4_leptveto               = get_histo("ele"                , false, true, 12);
	Wele.hTopnW                     = get_histo("eleTop"             , false, false, 19);
	Wele.hTopnW_bg                  = get_histo("eleTop"             , true,  false, 19);
	Wele.hTopnW_leptveto            = get_histo("eleTop"             , false, true, 19);
	if(fIncludeSingleTop){
	Wele.hTopnW_s                   = get_histo("eleTop_s"           , false, false, 20);
	Wele.hTopnW_s_bg                = get_histo("eleTop_s"           , true,  false, 20);
	Wele.hTopnW_s_leptveto          = get_histo("eleTop_s"           , false, true, 20);
	Wele.hTopnW2_s                   = get_histo("eleTop_s"           , false, false, 21);
	Wele.hTopnW2_s_bg                = get_histo("eleTop_s"           , true,  false, 21);
	Wele.hTopnW2_s_leptveto          = get_histo("eleTop_s"           , false, true, 21);
	Wele.hTopnW_t                   = get_histo("eleTop_t"           , false, false, 22);
	Wele.hTopnW_t_bg                = get_histo("eleTop_t"           , true,  false, 22);
	Wele.hTopnW_t_leptveto          = get_histo("eleTop_t"           , false, true, 22);
	Wele.hTopnW2_t                   = get_histo("eleTop_t"           , false, false, 23);
	Wele.hTopnW2_t_bg                = get_histo("eleTop_t"           , true,  false, 23);
	Wele.hTopnW2_t_leptveto          = get_histo("eleTop_t"           , false, true, 23);
	Wele.hTopnW_tW                  = get_histo("eleTop_tW"          , false, false, 24);
	Wele.hTopnW_tW_bg               = get_histo("eleTop_tW"          , true,  false, 24);
	Wele.hTopnW_tW_leptveto         = get_histo("eleTop_tW"          , false, true, 24);
	Wele.hTopnW2_tW                  = get_histo("eleTop_tW"          , false, false, 25);
	Wele.hTopnW2_tW_bg               = get_histo("eleTop_tW"          , true,  false, 25);
	Wele.hTopnW2_tW_leptveto         = get_histo("eleTop_tW"          , false, true, 25);
	}
	Wmuo.hnW                        = get_histo("muo"                , false, false, 9);
	Wmuo.hnW_bg                     = get_histo("muo"                , true,  false, 9);
	Wmuo.hnW_leptveto               = get_histo("muo"                , false, true, 9);
	Wmuo.hnW2                        = get_histo("muo"                , false, false, 10);
	Wmuo.hnW2_bg                     = get_histo("muo"                , true,  false, 10);
	Wmuo.hnW2_leptveto               = get_histo("muo"                , false, true, 10);
	Wmuo.hnW3                        = get_histo("muo"                , false, false, 11);
	Wmuo.hnW3_bg                     = get_histo("muo"                , true,  false, 11);
	Wmuo.hnW3_leptveto               = get_histo("muo"                , false, true, 11);
	Wmuo.hnW4                        = get_histo("muo"                , false, false, 12);
	Wmuo.hnW4_bg                     = get_histo("muo"                , true,  false, 12);
	Wmuo.hnW4_leptveto               = get_histo("muo"                , false, true, 12);
	Wmuo.hTopnW                     = get_histo("muoTop"             , false, false, 19);
	Wmuo.hTopnW_bg                  = get_histo("muoTop"             , true,  false, 19);
	Wmuo.hTopnW_leptveto            = get_histo("muoTop"             , false, true, 19);
	if(fIncludeSingleTop){
	Wmuo.hTopnW_s                   = get_histo("muoTop_s"           , false, false, 20);
	Wmuo.hTopnW_s_bg                = get_histo("muoTop_s"           , true,  false, 20);
	Wmuo.hTopnW_s_leptveto          = get_histo("muoTop_s"           , false, true, 20);
	Wmuo.hTopnW2_s                   = get_histo("muoTop_s"           , false, false, 21);
	Wmuo.hTopnW2_s_bg                = get_histo("muoTop_s"           , true,  false, 21);
	Wmuo.hTopnW2_s_leptveto          = get_histo("muoTop_s"           , false, true, 21);
	Wmuo.hTopnW_t                   = get_histo("muoTop_t"           , false, false, 22);
	Wmuo.hTopnW_t_bg                = get_histo("muoTop_t"           , true,  false, 22);
	Wmuo.hTopnW_t_leptveto          = get_histo("muoTop_t"           , false, true, 22);
	Wmuo.hTopnW2_t                   = get_histo("muoTop_t"           , false, false, 23);
	Wmuo.hTopnW2_t_bg                = get_histo("muoTop_t"           , true,  false, 23);
	Wmuo.hTopnW2_t_leptveto          = get_histo("muoTop_t"           , false, true, 23);
	Wmuo.hTopnW_tW                  = get_histo("muoTop_tW"          , false, false, 24);
	Wmuo.hTopnW_tW_bg               = get_histo("muoTop_tW"          , true,  false, 24);
	Wmuo.hTopnW_tW_leptveto         = get_histo("muoTop_tW"          , false, true, 24);
	Wmuo.hTopnW2_tW                  = get_histo("muoTop_tW"          , false, false, 25);
	Wmuo.hTopnW2_tW_bg               = get_histo("muoTop_tW"          , true,  false, 25);
	Wmuo.hTopnW2_tW_leptveto         = get_histo("muoTop_tW"          , false, true, 25);
	}
	Wele.hnData                     = get_histo("ele_data"           , false, false, -10);
	Wmuo.hnData                     = get_histo("muo_data"           , false, false, -10);
	//                                                                   bg     leptonveto     sample_index                       
	Wele.nW                        = get_n_events("ele"                , false, false, 9);
	Wele.nW_bg                     = get_n_events("ele"                , true,  false, 9);
	Wele.nW_leptveto               = get_n_events("ele"                , false, true, 9);
	Wele.nW2                        = get_n_events("ele"                , false, false, 10);
	Wele.nW2_bg                     = get_n_events("ele"                , true,  false, 10);
	Wele.nW2_leptveto               = get_n_events("ele"                , false, true, 10);
	Wele.nW3                        = get_n_events("ele"                , false, false, 11);
	Wele.nW3_bg                     = get_n_events("ele"                , true,  false, 11);
	Wele.nW3_leptveto               = get_n_events("ele"                , false, true, 11);
	Wele.nW4                        = get_n_events("ele"                , false, false, 12);
	Wele.nW4_bg                     = get_n_events("ele"                , true,  false, 12);
	Wele.nW4_leptveto               = get_n_events("ele"                , false, true, 12);
	Wele.TopnW                     = get_n_events("eleTop"             , false, false, 19);
	Wele.TopnW_bg                  = get_n_events("eleTop"             , true,  false, 19);
	Wele.TopnW_leptveto            = get_n_events("eleTop"             , false, true, 19);
	if(fIncludeSingleTop){
	Wele.TopnW_s                   = get_n_events("eleTop_s"           , false, false, 20);
	Wele.TopnW_s_bg                = get_n_events("eleTop_s"           , true,  false, 20);
	Wele.TopnW_s_leptveto          = get_n_events("eleTop_s"           , false, true, 20);
	Wele.TopnW2_s                   = get_n_events("eleTop_s"           , false, false, 21);
	Wele.TopnW2_s_bg                = get_n_events("eleTop_s"           , true,  false, 21);
	Wele.TopnW2_s_leptveto          = get_n_events("eleTop_s"           , false, true, 21);
	Wele.TopnW_t                   = get_n_events("eleTop_t"           , false, false, 22);
	Wele.TopnW_t_bg                = get_n_events("eleTop_t"           , true,  false, 22);
	Wele.TopnW_t_leptveto          = get_n_events("eleTop_t"           , false, true, 22);
	Wele.TopnW2_t                   = get_n_events("eleTop_t"           , false, false, 23);
	Wele.TopnW2_t_bg                = get_n_events("eleTop_t"           , true,  false, 23);
	Wele.TopnW2_t_leptveto          = get_n_events("eleTop_t"           , false, true, 23);
	Wele.TopnW_tW                  = get_n_events("eleTop_tW"          , false, false, 24);
	Wele.TopnW_tW_bg               = get_n_events("eleTop_tW"          , true,  false, 24);
	Wele.TopnW_tW_leptveto         = get_n_events("eleTop_tW"          , false, true, 24);
	Wele.TopnW2_tW                  = get_n_events("eleTop_tW"          , false, false, 25);
	Wele.TopnW2_tW_bg               = get_n_events("eleTop_tW"          , true,  false, 25);
	Wele.TopnW2_tW_leptveto         = get_n_events("eleTop_tW"          , false, true, 25);
	}
	Wmuo.nW                        = get_n_events("muo"                , false, false, 9);
	Wmuo.nW_bg                     = get_n_events("muo"                , true,  false, 9);
	Wmuo.nW_leptveto               = get_n_events("muo"                , false, true, 9);
	Wmuo.nW2                        = get_n_events("muo"                , false, false, 10);
	Wmuo.nW2_bg                     = get_n_events("muo"                , true,  false, 10);
	Wmuo.nW2_leptveto               = get_n_events("muo"                , false, true, 10);
	Wmuo.nW3                        = get_n_events("muo"                , false, false, 11);
	Wmuo.nW3_bg                     = get_n_events("muo"                , true,  false, 11);
	Wmuo.nW3_leptveto               = get_n_events("muo"                , false, true, 11);
	Wmuo.nW4                        = get_n_events("muo"                , false, false, 12);
	Wmuo.nW4_bg                     = get_n_events("muo"                , true,  false, 12);
	Wmuo.nW4_leptveto               = get_n_events("muo"                , false, true, 12);
	Wmuo.TopnW                     = get_n_events("muoTop"             , false, false, 19);
	Wmuo.TopnW_bg                  = get_n_events("muoTop"             , true,  false, 19);
	Wmuo.TopnW_leptveto            = get_n_events("muoTop"             , false, true, 19);
	if(fIncludeSingleTop){
	Wmuo.TopnW_s                   = get_n_events("muoTop_s"           , false, false, 20);
	Wmuo.TopnW_s_bg                = get_n_events("muoTop_s"           , true,  false, 20);
	Wmuo.TopnW_s_leptveto          = get_n_events("muoTop_s"           , false, true, 20);
	Wmuo.TopnW2_s                   = get_n_events("muoTop_s"           , false, false, 21);
	Wmuo.TopnW2_s_bg                = get_n_events("muoTop_s"           , true,  false, 21);
	Wmuo.TopnW2_s_leptveto          = get_n_events("muoTop_s"           , false, true, 21);
	Wmuo.TopnW_t                   = get_n_events("muoTop_t"           , false, false, 22);
	Wmuo.TopnW_t_bg                = get_n_events("muoTop_t"           , true,  false, 22);
	Wmuo.TopnW_t_leptveto          = get_n_events("muoTop_t"           , false, true, 22);
	Wmuo.TopnW2_t                   = get_n_events("muoTop_t"           , false, false, 23);
	Wmuo.TopnW2_t_bg                = get_n_events("muoTop_t"           , true,  false, 23);
	Wmuo.TopnW2_t_leptveto          = get_n_events("muoTop_t"           , false, true, 23);
	Wmuo.TopnW_tW                  = get_n_events("muoTop_tW"          , false, false, 24);
	Wmuo.TopnW_tW_bg               = get_n_events("muoTop_tW"          , true,  false, 24);
	Wmuo.TopnW_tW_leptveto         = get_n_events("muoTop_tW"          , false, true, 24);
	Wmuo.TopnW2_tW                  = get_n_events("muoTop_tW"          , false, false, 25);
	Wmuo.TopnW2_tW_bg               = get_n_events("muoTop_tW"          , true,  false, 25);
	Wmuo.TopnW2_tW_leptveto         = get_n_events("muoTop_tW"          , false, true, 25);
	}
	Wele.nData                     = get_n_events("ele_data"           , false, false, -10);
	Wmuo.nData                     = get_n_events("muo_data"           , false, false, -10);
//	nTau_leptveto                  = get_n_events("tau_leptveto"       , false, false)*Wele.Wxsection*Wele.lumi/Wele.Wnevents;

	cout<<"--->>>"<<" Wele.nData: "<<Wele.nData<<endl;
	cout<<"--->>>"<<" Wmuo.nData: "<<Wmuo.nData<<endl;

	cout<<"--->>>"<<" Wele.TopnW_leptveto: "<<Wele.TopnW_leptveto<<endl;
	cout<<"--->>>"<<" Wmuo.TopnW_leptveto: "<<Wmuo.TopnW_leptveto<<endl;

	// cout new efficiecies
	if(fMakeEfficienciesPablo ){
		if(fTagandProbeMC){
			double ele_recoeff=0, ele_recoerr=0;
			double muo_recoeff=0, muo_recoerr=0;
			for(int i=0; i<Wele.effMC.size(); ++i){
				ele_recoeff+=Wele.effMC[i];	
				ele_recoerr+=Wele.errMC[i]*Wele.errMC[i];
			}
			for(int i=0; i<Wmuo.effMC.size(); ++i){
				muo_recoeff+=Wmuo.effMC[i];	
				muo_recoerr+=Wmuo.errMC[i]*Wmuo.errMC[i];
			}
			muo_recoeff=muo_recoeff/Wmuo.effMC.size();
			ele_recoeff=ele_recoeff/Wele.effMC.size();
			muo_recoerr=sqrt(muo_recoerr)/Wmuo.effMC.size();
			ele_recoerr=sqrt(ele_recoerr)/Wele.effMC.size();
			cout << "------------------------------" << endl;
			cout << "MC efficiencies:                 " << endl;
			cout << "electrons                     " << endl;
			cout << "W:    reco " << Wele.rec    << " pm " << Wele.rec_err    << endl;
			cout << "WTop: reco " << Wele.Toprec << " pm " << Wele.Toprec_err << endl;
			cout << "T&P:  reco " << ele_recoeff << " pm " << ele_recoerr     << endl;
			cout << "muons                     " << endl;
			cout << "W:    reco " << Wmuo.rec    << " pm " << Wmuo.rec_err    << endl;
			cout << "WTop: reco " << Wmuo.Toprec << " pm " << Wmuo.Toprec_err << endl;
			cout << "T&P:  reco " << muo_recoeff << " pm " << muo_recoerr<< endl;
			cout << "------------------------------" << endl;
		}
		double ele_recoeff=0; double ele_recoerr=0;
		double muo_recoeff=0; double muo_recoerr=0;
		for(int i=0; i<Wele.eff.size(); ++i){
			ele_recoeff+=Wele.eff[i];	
			ele_recoerr+=Wele.err[i]*Wele.err[i];
		}
		for(int i=0; i<Wmuo.eff.size(); ++i){
			muo_recoeff+=Wmuo.eff[i];	
			muo_recoerr+=Wmuo.err[i]*Wmuo.err[i];
		}
		muo_recoeff=muo_recoeff/Wmuo.eff.size();
		muo_recoerr=sqrt(muo_recoerr)/Wmuo.eff.size();
		ele_recoeff=ele_recoeff/Wele.eff.size();
		ele_recoerr=sqrt(ele_recoerr)/Wele.eff.size();
		cout << "Data efficiencies"          << endl;
		cout << "electrons                     " << endl;
		cout << "T&P:  reco " << ele_recoeff << " pm " << ele_recoerr     << endl;
		cout << "muons                     " << endl;
		cout << "T&P:  reco " << muo_recoeff << " pm " << muo_recoerr<< endl;
		cout << "------------------------------" << endl;
	
	}
	// makePrint(); // this line commented because it's showing useless information. commented on 23 July 2013.
}

void makePrint(){

	// __________________________________
	cout << "____________________________________________________"      << endl;
	cout << "W->l nu statistics                                  "      << endl;
	cout << "----------------------------------------------------"      << endl;
	cout << "prob for true W->lv event to be recoed              "      << endl;
	if(!fTopEfficencies){
	cout << " Wele.prob:  " <<Wele.prob 
             << " pm "<<Wele.prob_err_sys() << " (sys)  " 	            << endl;
	}else if(fTopEfficencies){
	cout << " Top Wele.prop: " << Wele.Topprob 
             << " pm "<<Wele.prob_err_sys()   << " (sys)  " 	            << endl;
	}
	if(!fTopEfficencies){
	cout << " Wmunu_prob:  " <<Wmuo.prob 
             << " pm "<<Wmuo.prob_err_sys() << " (sys)  " 	            << endl;
	}else if(fTopEfficencies){
	cout << " Top Wmuo.prop: " << Wmuo.Topprob 
             << " pm "<<Wmuo.prob_err_sys() << " (sys)  " 	            << endl;
	}
	if(fIncludeTop && fTopEfficencies && !fMakeEfficienciesPablo){
	cout << "WARNING: efficiencies for pred taken from Top W->enu"      << endl;
	}else if(! fMakeEfficienciesPablo){
	cout << "WARNING: efficiencies for pred taken from W->enu    "      << endl;
	}else {
	cout << "WARNING: efficiencies from T&P                      "      << endl;
	cout << "Data"                                                      << endl;
	cout << "Wele.TPReco " << Wele.TPReco() << " pm " << Wele.TPRecoErr() << endl;
	cout << "Wmuo.TPReco " << Wmuo.TPReco() << " pm " << Wmuo.TPRecoErr() << endl;
	if(fTagandProbeMC){
	cout << "MC "                                                       << endl;
	cout << "Wele.TPRecoMC " << Wele.TPRecoMC() << " pm " << Wele.TPRecoErrMC() << endl;
	cout << "Wmuo.TPRecoMC " << Wmuo.TPRecoMC() << " pm " << Wmuo.TPRecoErrMC() << endl;
	}}
	cout << "----------------------------------------------------"      << endl;
	cout << "Acc*Reco eff"                                              << endl;
	//cout << "Wele.prob() " << Wele.prob() << " pm " << Wele.prob_err_sys() << endl;
	//cout << "Wmuo.prob() " << Wmuo.prob() << " pm " << Wmuo.prob_err_sys() << endl;
	cout << "----------------------------------------------------"      << endl;
	cout << "acceptance                                          "      << endl;
	if(fTopEfficencies){
	cout << "Wele.Topacc " << Wele.Topacc << " pm " << Wele.Accerr()     << endl;
	cout << "Wmuo.Topacc " << Wmuo.Topacc << " pm " << Wmuo.Accerr()     << endl;
	}else{
	cout << "Wele.acc " << Wele.acc << " pm " << Wele.Accerr()     << endl;
	cout << "Wmuo.acc " << Wmuo.acc << " pm " << Wmuo.Accerr()     << endl;
	}
	cout << "----------------------------------------------------"      << endl;
	cout << "number of MC W->lnu events                          "      << endl;
	cout << " W->enu:      " << Wele.nW+Wele.nW2+Wele.nW3+Wele.nW4                                 << endl;
	cout << " W->munu:     " << Wmuo.nW+Wmuo.nW2+Wmuo.nW3+Wmuo.nW4                                 << endl;
	cout << "number of true MC W->lnu event (w/ or w/o tau)      "      << endl;
	cout << " nW - nW_bg:  "  << (Wele.nW+Wele.nW2+Wele.nW3+Wele.nW4) - (Wele.nW_bg+Wele.nW2_bg+Wele.nW3_bg+Wele.nW4_bg)                   << endl;
	cout << " nW - nW_bg:  "  << (Wmuo.nW+Wmuo.nW2+Wmuo.nW3+Wmuo.nW4) - (Wmuo.nW_bg+Wmuo.nW2_bg+Wmuo.nW3_bg+Wmuo.nW4_bg)                   << endl;
	cout << "number of true MC W->lnu events passing l-veto      "      << endl;
	cout << " nW_leptveto: " << Wele.nW_leptveto+Wele.nW2_leptveto+Wele.nW3_leptveto+Wele.nW4_leptveto                        << endl;
	cout << " nW_leptveto: " << Wmuo.nW_leptveto+Wmuo.nW2_leptveto+Wmuo.nW3_leptveto+Wmuo.nW4_leptveto                        << endl;
	if(fIncludeTop){
	cout << "----------------------------------------------------"      << endl;
	cout << "number of MC Top W->lnu events                      "      << endl;
	cout << " Top W->enu:      " << Wele.TopnW                          << endl;
	cout << " Top W->munu:     " << Wmuo.TopnW                          << endl;
	cout << "number of true MC Top W->lnu event (w/ or w/o tau)  "      << endl;
	cout << " Top nW - nW_bg:  "  << Wele.TopnW - Wele.TopnW_bg         << endl;
	cout << " Top nW - nW_bg:  "  << Wmuo.TopnW - Wmuo.TopnW_bg         << endl;
	cout << "number of true MC Top W->lnu events passing l-veto  "      << endl;
	cout << " Top nW_leptveto: " << Wele.TopnW_leptveto                 << endl;
	cout << " Top nW_leptveto: " << Wmuo.TopnW_leptveto                 << endl;
	}
	if(fIncludeSingleTop){
	cout << "----------------------------------------------------"      << endl;
	cout << "number of MC Single Top W->lnu events:s-channel     "      << endl;
	cout << " Top W->enu:      " << Wele.TopnW_s+Wele.TopnW2_s          << endl;
	cout << " Top W->munu:     " << Wmuo.TopnW_s+Wmuo.TopnW2_s          << endl;
	cout << "number of true MC Top W->lnu event (w/ or w/o tau)  "      << endl;
	cout << " Top nW - nW_bg:  "  << (Wele.TopnW_s+Wele.TopnW2_s) - (Wele.TopnW_s_bg+Wele.TopnW2_s_bg)     << endl;
	cout << " Top nW - nW_bg:  "  << (Wmuo.TopnW_s+Wmuo.TopnW2_s) - (Wmuo.TopnW_s_bg+Wmuo.TopnW2_s_bg)     << endl;
	cout << "number of true MC Top W->lnu events passing l-veto  "      << endl;
	cout << " Top nW_leptveto: " << Wele.TopnW_s_leptveto+Wele.TopnW2_s_leptveto               << endl;
	cout << " Top nW_leptveto: " << Wmuo.TopnW_s_leptveto+Wmuo.TopnW2_s_leptveto               << endl;
	cout << "----------------------------------------------------"      << endl;
	cout << "number of MC Single Top W->lnu events:t-channel     "      << endl;
	cout << " Top W->enu:      " << Wele.TopnW_t+Wele.TopnW2_t                        << endl;
	cout << " Top W->munu:     " << Wmuo.TopnW_t+Wmuo.TopnW2_t                        << endl;
	cout << "number of true MC Top W->lnu event (w/ or w/o tau)  "      << endl;
	cout << " Top nW - nW_bg:  "  << (Wele.TopnW_t+Wele.TopnW2_t) - (Wele.TopnW_t_bg+Wele.TopnW2_t_bg)     << endl;
	cout << " Top nW - nW_bg:  "  << (Wmuo.TopnW_t+Wmuo.TopnW2_t) - (Wmuo.TopnW_t_bg+Wmuo.TopnW2_t_bg)     << endl;
	cout << "number of true MC Top W->lnu events passing l-veto  "      << endl;
	cout << " Top nW_leptveto: " << Wele.TopnW_t_leptveto+Wele.TopnW2_t_leptveto               << endl;
	cout << " Top nW_leptveto: " << Wmuo.TopnW_t_leptveto+Wmuo.TopnW2_t_leptveto               << endl;
	cout << "----------------------------------------------------"      << endl;
	cout << "number of MC Single Top W->lnu events:tW-channel     "     << endl;
	cout << " Top W->enu:      " << Wele.TopnW_tW+Wele.TopnW2_tW                       << endl;
	cout << " Top W->munu:     " << Wmuo.TopnW_tW+Wmuo.TopnW2_tW                       << endl;
	cout << "number of true MC Top W->lnu event (w/ or w/o tau)  "      << endl;
	cout << " Top nW - nW_bg:  "  << (Wele.TopnW_tW+Wele.TopnW2_tW) - (Wele.TopnW_tW_bg+Wele.TopnW2_tW_bg)   << endl;
	cout << " Top nW - nW_bg:  "  << (Wmuo.TopnW_tW+Wmuo.TopnW2_tW) - (Wmuo.TopnW_tW_bg+Wmuo.TopnW2_tW_bg)   << endl;
	cout << "number of true MC Top W->lnu events passing l-veto  "      << endl;
	cout << " Top nW_leptveto: " << Wele.TopnW_tW_leptveto+Wele.TopnW2_tW_leptveto              << endl;
	cout << " Top nW_leptveto: " << Wmuo.TopnW_tW_leptveto+Wmuo.TopnW2_tW_leptveto              << endl;
	}
	cout << "----------------------------------------------------"      << endl;
	cout << "MC sanity test                                      "      << endl;
	cout << " electrons:                                         "      << endl;
	cout << "   all events MC     : " << Wele.all_MC()                  << endl;
	cout << "   MC - all bg       : " << Wele.all_MC()-Wele.bg()        << endl;
	cout << "   pred total W->enu : " 
	     <<     (Wele.all_MC()-Wele.bg())/Wele.prob()                   << endl;
	cout << "   pred W lepton veto: " 
	     <<     (Wele.all_MC()-Wele.bg())*(1-Wele.prob())/Wele.prob()   << endl;
	cout << "   true W->enu passing lept veto : "
	     <<     Wele.nW_leptveto_scaled()                               << endl;
	cout << " muons:                                             "      << endl;
	cout << "   all events MC     : " << Wmuo.all_MC()                  << endl;
	cout << "   MC - all bg       : " << Wmuo.all_MC()-Wmuo.bg()        << endl;
	cout << "   pred total W->enu : " 
	     <<     (Wmuo.all_MC()-Wmuo.bg())/Wmuo.prob()                   << endl;
	cout << "   pred W lepton veto: " 
	     <<     (Wmuo.all_MC()-Wmuo.bg())*(1-Wmuo.prob())/Wmuo.prob()   << endl;
	cout << "   true W->enu passing lept veto : "
	     <<     Wmuo.nW_leptveto_scaled()                               << endl;
	cout << "----------------------------------------------------"      << endl;
	cout << "number of events in data                            "      << endl;
	cout << " nWele_data: " << Wele.nData                               << endl;
	cout << " nWmuo_data: " << Wmuo.nData                               << endl;
	cout << "background from other MC                            "      << endl;
	if(!fIncludeTop && !fTopOnly){
	cout << " Top_m   " << Wmuo.Top_bg  << " Top_e   " <<Wele.Top_bg    << endl;
	}
	if(fTopOnly){
	cout << " W_m     " << Wmuo.W_bg    << " W_e     " <<Wele.W_bg      << endl;
	}
	cout << " QCD_m   " << Wmuo.QCD_bg  << " QCD_e   " <<Wele.QCD_bg    << endl;
	cout << " Z_m     " << Wmuo.Z_bg    << " Z_e     " <<Wele.Z_bg      << endl;
	cout << " Other_m " << Wmuo.Other_bg<< " Other_e " <<Wele.Other_bg  << endl;
	if(fIncludeTop && !fTopOnly){
	cout << "bg from Wjets and Top                               "     << endl;
	}
	if(fTopOnly){
	cout << "bg from Top                                         "     << endl;
	}
	if(!fIncludeTop){
	cout << "bg from Wjets                                       "     << endl;
	}
	cout << " muo     " << Wmuo.nW_bg_scaled() 
	     << " ele     " << Wele.nW_bg_scaled()                          << endl;
	cout << "bg subtracted number of event in data               "      << endl;
	cout << " electron: " << Wele.nData-Wele.bg()                       << endl;
	cout << " muon    : " << Wmuo.nData-Wmuo.bg()                       << endl;
	cout << "----------------------------------------------------"      << endl;
	if(fMCClosure){
	cout << "MC CLOSURE TEST "                                          << endl;
	}
	cout << "PREDICTION:                                         "      << endl;
	cout << " number of W->enu passing lepton veto "                           ;
	cout <<    Wele.pred()                                                     ;
	cout << " pm " << Wele.pred_error_stat()       << " (stat)"                ;
	cout << " pm " << Wele.pred_error_sys() << " (sys)"                 << endl;
	cout << " number of W->munu passing lepton veto "                          ;
	cout <<    Wmuo.pred()                                                     ;
	cout << " pm " << Wmuo.pred_error_stat()       << " (stat)"                ;
	cout << " pm " << Wmuo.pred_error_sys()        << " (sys)"          << endl;
	cout << "MC:                                                 "      << endl;
	cout << " MC number of W->enu passing lepton veto  "                       ;
	cout <<    Wele.nW_leptveto_scaled()                                << endl; 
	cout << " MC number of W->munu passing lepton veto "                       ;
	cout <<    Wmuo.nW_leptveto_scaled()                                << endl; 
	cout << "____________________________________________________"      << endl;
	cout << "MC Number of W->tau nu events passing the lept-veto"       << endl;
	if(fIncludeTaus){
	cout << "  leptonic taus *NOT* included!                     "      << endl;
	}else{
	cout << "  leptonic taus included!                           "      << endl;
	}
//	cout << "nTau_leptveto " << nTau_leptveto                           << endl;
	cout << "____________________________________________________"      << endl;
//	cout << " ele uncertainty on prob "     << Wele.prob_err/Wele.prob          << endl;
//	cout << "  -> " << (Wele.nData-Wele.bg()) *(1/(Wele.prob()*Wele.prob())*Wele.prob_err)  << endl;
//	cout << " ele uncertainty on prob of  " << Wele.rel_sys_uncert *100 << "%"                                 << endl; 
//	cout << "  -> " << (Wele.nData-Wele.bg()) *(1/(Wele.prob()*Wele.prob())*(Wele.prob*Wele.rel_sys_uncert)) << endl;
//	cout << " ele uncertainty on bg subraction: " << Wele.rel_sys_uncert_bg << " %: " << endl; 
//	cout << "  -> " << Wele.rel_sys_uncert_bg*Wele.bg()*(1-Wele.prob())/Wele.prob()          << endl;
//	cout << " muo uncertainty on prob "     << Wele.prob_err/Wele.prob          << endl;
//	cout << "  -> " << (Wmuo.nData-Wmuo.bg()) *(1/(Wmuo.prob()*Wmuo.prob())*Wmuo.prob_err)  << endl;
//	cout << " muo uncertainty on prob of " << Wmuo.rel_sys_uncert << "%"                                   << endl; 
//	cout << "  -> " << (Wmuo.nData-Wmuo.bg()) *(1/(Wmuo.prob()*Wmuo.prob())*(Wmuo.prob*Wmuo.rel_sys_uncert)) << endl;
//	cout << " muo uncertainty on bg subraction: " << Wmuo.rel_sys_uncert_bg << " %: " << endl; 
//	cout << "  -> " << Wmuo.rel_sys_uncert_bg*Wmuo.bg()*(1-Wmuo.prob())/Wmuo.prob()          << endl;



}

double get_n_events(string process, bool background, bool leptveto, int sample_index = -1){
	//setStyle(); commented by me on 2 Dec
	TString      basecut   =  " ";
	TChain       *chain    = new TChain("MassTree");
	double       weight    = 1.;
        for (map<int, double>::const_iterator it = mymap.begin(); it != mymap.end(); it++)
        //cout << it->first << "=" << it->second << " " << endl; 
        if(sample_index == it->first) weight = weight/(it->second);

	
	TString path     ="";
	TString path_data="";
	if(fLLSkim) path = "/shome/pnef/SUSY/SUSY_macros/analyzed/RunLeptJetMultAnalyzer/MT2_V00-06-10/20110730_MC_HT300_data_nocuts/SmartSkimmed-LostLepton/";
	else        path = "/dataLOCAL/MT2Top/RootFiles/NewTreesSmearedJetMETNewBTag/";
	if(fLLSkim) path_data="/shome/pnef/SUSY/SUSY_macros/analyzed/RunLeptJetMultAnalyzer/MT2_V00-06-10/20110730_MC_HT300_data_nocuts/SmartSkimmed-LostLepton2/";
	else        path_data="/dataLOCAL/MT2Top/RootFiles/NewTreesSmearedJetMETNewBTag/";

	if(process == "ele"){
		if (sample_index == 9) chain   ->Add(path+"WJetsToLNu-HT-200To250-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7C-v1-2_smallb.root");
		if (sample_index == 10) chain   ->Add(path+"WJetsToLNu-HT-250To300-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 11) chain   ->Add(path+"WJetsToLNu-HT-300To400-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 12) chain   ->Add(path+"WJetsToLNu-HT-400ToInf-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="GenLeptFromW(11, 0, 1000, fIncludeTaus)==0  &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100 &&";
		else           basecut +="(NEles==0)&&(NMuons==0) && GenLeptFromW(11, 0, 1000, fIncludeTaus)==1 &&";
	} else if ( process == "eleTop"){
		chain   ->Add(path+"TTJets-MassiveBinDECAY-TuneZ2star-8TeV-madgraph-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100 &&";
		else           basecut +="(NEles==0)&&(NMuons==0)&&TopDecayModeResult(11)==1 &&";
	} else if ( process == "eleTop_s"){
		if (sample_index == 20) chain   ->Add(path+"T-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 21) chain   ->Add(path+"Tbar-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0)&& TopDecayModeResult(11)==1 &&";
	} else if ( process == "eleTop_t"){
		if (sample_index == 22) chain   ->Add(path+"T-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v3_smallb.root");
		if (sample_index == 23) chain   ->Add(path+"Tbar-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(11)==1 &&";
	} else if ( process == "eleTop_tW"){
		(sample_index == 24) chain   ->Add(path+"T-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		(sample_index == 25) chain   ->Add(path+"Tbar-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(11)==1 &&";
	}else if(process == "muo"){
		if (sample_index == 9) chain   ->Add(path+"WJetsToLNu-HT-200To250-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7C-v1-2_smallb.root");
		if (sample_index == 10) chain   ->Add(path+"WJetsToLNu-HT-250To300-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 11) chain   ->Add(path+"WJetsToLNu-HT-300To400-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 12) chain   ->Add(path+"WJetsToLNu-HT-400ToInf-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="GenLeptFromW(13, 0, 1000, fIncludeTaus)==0  &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 && muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && GenLeptFromW(13, 0, 1000, fIncludeTaus)==1 &&";
	} else if ( process == "muoTop"){
		chain   ->Add(path+"TTJets-MassiveBinDECAY-TuneZ2star-8TeV-madgraph-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 &&muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "muoTop_s"){
		if (sample_index == 20) chain   ->Add(path+"T-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 21) chain   ->Add(path+"Tbar-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 &&muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "muoTop_t"){
		if (sample_index == 22) chain   ->Add(path+"T-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v3_smallb.root");
		if (sample_index == 23) chain   ->Add(path+"Tbar-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 &&muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "muoTop_tW"){
		(sample_index == 24) chain   ->Add(path+"T-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		(sample_index == 25) chain   ->Add(path+"Tbar-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 && muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "tau_leptveto"){
		chain   ->Add(path+"WJetsToLNu-HT-250To300-8TeV-madgraph_smallb.root");
		basecut +="(NEles==0)&&(NMuons==0) && GenLeptFromW(13, 0, 1000, fIncludeTaus)==0 && GenLeptFromW(11, 0, 1000, fIncludeTaus)==0 &&";
	} else if ( process == "ele_data"){
		chain   ->Add(path_data+"MultiJet-Run2012A-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012A-recover-06Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012B-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-24Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-PromptReco-v2_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012D-PromptReco-v1_smallb.root");
		basecut +="NMuons==0 && NEles==1 && ele[0].MT<100 && ";
	} else if ( process == "muo_data"){
		chain   ->Add(path_data+"MultiJet-Run2012A-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012A-recover-06Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012B-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-24Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-PromptReco-v2_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012D-PromptReco-v1_smallb.root");
		basecut +="NMuons==1 && NEles==0 && muo[0].MT<100 &&";
	} else {return -1;}

	basecut  += "misc.MET>30 && ";
	basecut  += "misc.MT2 >125 && ";
	basecut  += "NJetsIDLoose40  >=4 && ";
	basecut  += "NBJetsCSVT >0 &&";
	basecut  += "misc.Jet0Pass==1 && ";
	basecut  += "misc.Jet1Pass==1 && ";
	basecut  += "misc.PassJetID ==1 && ";
	basecut  += "misc.Vectorsumpt <70 && ";
//	basecut  += "misc.MinMetJetDPhi4 >0.3 &&";// cut on dPhi is relaxed for Lost Lepton estimation, applied on Wed 10 April
        //basecut  += "(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0)) || ((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0))) &&";
        basecut  += "(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0)) || ((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0))) &&";
	// run on data only, corrected on 21 Jan
        basecut  += "(misc.ProcessID!=0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 && misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 && misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 && misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 ) &&";
        basecut  += "((((trigger.HLT_QuadJet80_v1 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v2 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v3 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v4 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v6 ==1)) &&";
        basecut  += " ((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || ";// open pran
        basecut  +=" (NJetsIDLoose40  >=5 &&";
        basecut  +=" jet[4].lv.Pt() >= 85.0 ))) || ";// close pran
        basecut  +="(((trigger.HLT_SixJet45_v1 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v2 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v3 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v4 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v6 ==1)) &&";
        basecut  +=" (NJetsIDLoose40  >=6 &&";// open
        basecut  +=" jet[5].lv.Pt() >= 65.0 )))))";
        //basecut  +=" jet[5].lv.Pt() >= 65.0 ) ||";
        //basecut  +=" (NJetsIDLoose40  >=7 &&";
        //basecut  +=" jet[6].lv.Pt() >= 55.0 )))))";// close


	TString selection;
	if(process == "ele_data" || process == "muo_data"){
		selection = TString::Format("(%f) * (%s)",weight, basecut.Data());
	}else{
		selection = TString::Format("(%.15f*SFWeight.BTagCSV40ge1*pileUp.Weight) * (%s)",weight, basecut.Data());
		//selection = TString::Format("(%.15f*pileUp.Weight) * (%s)",weight, basecut.Data());
		//selection = TString::Format("(%.15f) * (%s)",weight, basecut.Data());// if btag sf and pu sf are turned off, then the same number of events are found comparing with the direct couning of lost lepton ttbar events. *** sat aug 31 ***  
	}
 
	double nevents=0;
	if(process == "ele_data" || process == "muo_data" || 
	  (process == "ele"    && !background &&!leptveto&& fTagandProbeMC && !fTopEfficencies)|| 
	  (process == "eleTop" && !background &&!leptveto&& fTagandProbeMC &&  fTopEfficencies)|| 
	  (process == "muo"    && !background &&!leptveto&& fTagandProbeMC && !fTopEfficencies)|| 
	  (process == "muoTop" && !background &&!leptveto&& fTagandProbeMC &&  fTopEfficencies)){
		nevents = GetHistoAndEff(chain, selection, process);
	}else{
		//TH1D* h1 = GetHisto(chain, "misc.MET    >>", selection, "h1");	
		TH1D* h1 = GetHisto(chain, "misc.MT2    >>", selection, "h1");	
		cout << "+++ get_n_events: " << process << " background=" << background << " integral " << h1->Integral() << " entries " << h1->GetEntries() << endl;

		nevents  = h1->Integral();
		delete h1;
	}


	delete chain;

      	return nevents;	
}

map<int, double> calcAvrPUWeight(){
 
        MassPlotter *tA = new MassPlotter(outputdir, "MassPlots.root");
	TString samples   = "./samples/samplesMineSmearedJetMETNewBTagParkedNewSamples_No7trig.dat";//samplesMineSmearedJetMETNewBTag.dat";
        tA->init(samples);
	map<int, double> mymap = tA->calcWeight();
	delete tA;
	return mymap;
}
	
TH1D* get_histo(string process, bool background, bool leptveto, int sample_index = -1){
	//setStyle(); commented by me on 2 Dec
	TString      basecut   =  " ";
	TChain       *chain    = new TChain("MassTree");
	double       weight    = 1.;

	for (map<int, double>::const_iterator it = mymap.begin(); it != mymap.end(); it++)
        //cout << it->first << "=" << it->second << " " << endl; 
	if(sample_index == it->first) weight = weight/(it->second);
	
	TString path     ="";
	TString path_data="";
	if(fLLSkim) path = "/shome/pnef/SUSY/SUSY_macros/analyzed/RunLeptJetMultAnalyzer/MT2_V00-06-10/20110730_MC_HT300_data_nocuts/SmartSkimmed-LostLepton/";
	else        path = "/dataLOCAL/MT2Top/RootFiles/NewTreesSmearedJetMETNewBTag/";
	if(fLLSkim) path_data="/shome/pnef/SUSY/SUSY_macros/analyzed/RunLeptJetMultAnalyzer/MT2_V00-06-10/20110730_MC_HT300_data_nocuts/SmartSkimmed-LostLepton2/";
	else        path_data="/dataLOCAL/MT2Top/RootFiles/NewTreesSmearedJetMETNewBTag/";

	if(process == "ele"){
		if (sample_index == 9) chain   ->Add(path+"WJetsToLNu-HT-200To250-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7C-v1-2_smallb.root");
		if (sample_index == 10) chain   ->Add(path+"WJetsToLNu-HT-250To300-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 11) chain   ->Add(path+"WJetsToLNu-HT-300To400-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 12) chain   ->Add(path+"WJetsToLNu-HT-400ToInf-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="GenLeptFromW(11, 0, 1000, fIncludeTaus)==0  &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100 &&";
		else           basecut +="(NEles==0)&&(NMuons==0) && GenLeptFromW(11, 0, 1000, fIncludeTaus)==1 &&";
	} else if ( process == "eleTop"){
		chain   ->Add(path+"TTJets-MassiveBinDECAY-TuneZ2star-8TeV-madgraph-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100 &&";
		else           basecut +="(NEles==0)&&(NMuons==0)&&TopDecayModeResult(11)==1 &&";
	} else if ( process == "eleTop_s"){
		if (sample_index == 20) chain   ->Add(path+"T-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 21) chain   ->Add(path+"Tbar-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0)&& TopDecayModeResult(11)==1 &&";
	} else if ( process == "eleTop_t"){
		if (sample_index == 22) chain   ->Add(path+"T-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v3_smallb.root");
		if (sample_index == 23) chain   ->Add(path+"Tbar-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(11)==1 &&";
	} else if ( process == "eleTop_tW"){
		(sample_index == 24) chain   ->Add(path+"T-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		(sample_index == 25) chain   ->Add(path+"Tbar-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(11)==0 &&";
		if(!leptveto)  basecut +="NEles==1 && NMuons==0 && ele[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(11)==1 &&";
	}else if(process == "muo"){
		if (sample_index == 9) chain   ->Add(path+"WJetsToLNu-HT-200To250-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7C-v1-2_smallb.root");
		if (sample_index == 10) chain   ->Add(path+"WJetsToLNu-HT-250To300-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 11) chain   ->Add(path+"WJetsToLNu-HT-300To400-8TeV-madgraph-v2-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 12) chain   ->Add(path+"WJetsToLNu-HT-400ToInf-8TeV-madgraph-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="GenLeptFromW(13, 0, 1000, fIncludeTaus)==0  &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 && muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && GenLeptFromW(13, 0, 1000, fIncludeTaus)==1 &&";
	} else if ( process == "muoTop"){
		chain   ->Add(path+"TTJets-MassiveBinDECAY-TuneZ2star-8TeV-madgraph-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 &&muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "muoTop_s"){
		if (sample_index == 20) chain   ->Add(path+"T-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if (sample_index == 21) chain   ->Add(path+"Tbar-s-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 &&muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "muoTop_t"){
		if (sample_index == 22) chain   ->Add(path+"T-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v3_smallb.root");
		if (sample_index == 23) chain   ->Add(path+"Tbar-t-channel-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 &&muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "muoTop_tW"){
		(sample_index == 24) chain   ->Add(path+"T-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		(sample_index == 25) chain   ->Add(path+"Tbar-tW-channel-DR-TuneZ2star-8TeV-powheg-tauola-Summer12-DR53X-PU-S10-START53-V7A-v1_smallb.root");
		if( background)basecut +="TopDecayModeResult(13)==0 &&";
		if(!leptveto)  basecut +="NEles==0 && NMuons==1 && muo[0].MT<100&&";
		else           basecut +="(NEles==0)&&(NMuons==0) && TopDecayModeResult(13)==1 &&";
	} else if ( process == "tau_leptveto"){
		chain   ->Add(path+"WJetsToLNu-HT-250To300-8TeV-madgraph_smallb.root");
		basecut +="(NEles==0)&&(NMuons==0) && GenLeptFromW(13, 0, 1000, fIncludeTaus)==0 && GenLeptFromW(11, 0, 1000, fIncludeTaus)==0 &&";
	} else if ( process == "ele_data"){
		chain   ->Add(path_data+"MultiJet-Run2012A-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012A-recover-06Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012B-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-24Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-PromptReco-v2_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012D-PromptReco-v1_smallb.root");
		basecut +="NMuons==0 && NEles==1 && ele[0].MT<100 && ";
	} else if ( process == "muo_data"){
		chain   ->Add(path_data+"MultiJet-Run2012A-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012A-recover-06Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012B-13Jul2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-24Aug2012-v1_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012C-PromptReco-v2_smallb.root");
		chain   ->Add(path_data+"MultiJet-Run2012D-PromptReco-v1_smallb.root");
		basecut +="NMuons==1 && NEles==0 && muo[0].MT<100 &&";
	} else {return -1;}

	basecut  += "misc.MET>30 && ";
	basecut  += "misc.MT2 >125 && ";
	basecut  += "NJetsIDLoose40  >=4 && ";
	basecut  += "NBJetsCSVT >0 &&";
	basecut  += "misc.Jet0Pass==1 && ";
	basecut  += "misc.Jet1Pass==1 && ";
	basecut  += "misc.PassJetID ==1 && ";
	basecut  += "misc.Vectorsumpt <70 && ";
//	basecut  += "misc.MinMetJetDPhi4 >0.3 &&";// cut on dPhi is relaxed for Lost Lepton estimation, applied on Wed 10 April
        //basecut  += "(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0)) || ((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0))) &&";
        basecut  += "(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0)) || ((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0))) &&";
	// run on data only, corrected on 21 Jan
        basecut  += "(misc.ProcessID!=0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 && misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 && misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 && misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 ) &&";
        basecut  += "((((trigger.HLT_QuadJet80_v1 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v2 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v3 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v4 ==1) ||";
        basecut  += "(trigger.HLT_QuadJet80_v6 ==1)) &&";
        basecut  += "((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || ";// open pran
        basecut  +=" (NJetsIDLoose40  >=5 &&";
        basecut  +=" jet[4].lv.Pt() >= 85.0 ))) || ";// close pran
        basecut  +="(((trigger.HLT_SixJet45_v1 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v2 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v3 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v4 ==1) ||";
        basecut  +="(trigger.HLT_SixJet45_v6 ==1)) &&";
        basecut  +=" (NJetsIDLoose40  >=6 &&";// open
        basecut  +=" jet[5].lv.Pt() >= 65.0 )))))";
        //basecut  +=" jet[5].lv.Pt() >= 65.0 ) ||";
        //basecut  +=" (NJetsIDLoose40  >=7 &&";
        //basecut  +=" jet[6].lv.Pt() >= 55.0 )))))";// close


	TString selection;
	if(process == "ele_data" || process == "muo_data"){
		selection = TString::Format("(%f) * (%s)",weight, basecut.Data());
	}else{
		selection = TString::Format("(%.15f*SFWeight.BTagCSV40ge1*pileUp.Weight) * (%s)",weight, basecut.Data());
		//selection = TString::Format("(%.15f*pileUp.Weight) * (%s)",weight, basecut.Data());
		//selection = TString::Format("(%.15f) * (%s)",weight, basecut.Data());// if btag sf and pu sf are turned off, then the same number of events are found comparing with the direct couning of lost lepton ttbar events. *** sat aug 31 ***  
	}
 
		TH1D* h1 = GetHisto(chain, "misc.MT2    >>", selection, "h1");	
		cout << "+++ get_histo: " << process << " background=" << background << " integral " << h1->Integral() << " entries " << h1->GetEntries() << endl;

	delete chain;

      	return h1;	
}

double   GetHistoAndEff(TChain* chainorig, TString basecut, TString process){
	TChain *chain=chainorig->Clone();
	MT2tree *fMT2tree = new MT2tree();
	chain->SetBranchAddress("MT2tree", &fMT2tree);
	Long64_t nentries =  chain->GetEntries();
	Long64_t nbytes = 0, nb = 0;
	int nev =0;
	chain->Draw(">>selList", basecut);

	TEventList *myEvtList = (TEventList*)gDirectory->Get("selList");
	chain->SetEventList(myEvtList);
	int counter=0;
	cout << "+++ Filtering done, size=" <<myEvtList->GetN()  << endl;

	if(myEvtList->GetSize()==0) continue;
	cout << "+++ Passing events for " << process << endl;	    
	while(myEvtList->GetEntry(counter++) !=-1){
		int jentry = myEvtList->GetEntry(counter-1);
		nb =  chain->GetEntry(jentry);   nbytes += nb;
		chain->SetBranchAddress("MT2tree", &fMT2tree);
                  
		if(process=="ele_data"){
			float eff=0; float eff_err=0;
			PabloEffEle(fMT2tree->ele[0].lv.Pt(), fMT2tree->ele[0].lv.Eta(), fMT2tree->LeptJetDR(11,0,0,1), fTypeOfEffErr, eff, eff_err, true);
			Wele.pt .push_back(fMT2tree->ele[0].lv.Pt());
			Wele.eta.push_back(fMT2tree->ele[0].lv.Eta());
			Wele.dR .push_back(fMT2tree->LeptJetDR(11,0,0,1));
			Wele.eff.push_back((double)eff);
			Wele.err.push_back((double)eff_err);
			if(fVerbose>1){
			cout << "++event   " << fMT2tree->misc.Event          << endl;
			cout << "  ele pt  " << fMT2tree->ele[0].lv.Pt()      << endl;
			cout << "  ele eta " << fMT2tree->ele[0].lv.Eta()     << endl;
			cout << "  ele dR  " << fMT2tree->LeptJetDR(11,0,0,1) << endl;
			cout << "  ele eff " << eff << " pm " << eff_err          << endl;
			}
		}else if(process=="ele" || process=="eleTop"){
			float eff=0; float eff_err=0;
			PabloEffEle(fMT2tree->ele[0].lv.Pt(), fMT2tree->ele[0].lv.Eta(), fMT2tree->LeptJetDR(11,0,0,1), fTypeOfEffErr, eff, eff_err, false);
			Wele.ptMC .push_back(fMT2tree->ele[0].lv.Pt());
			Wele.etaMC.push_back(fMT2tree->ele[0].lv.Eta());
			Wele.dRMC .push_back(fMT2tree->LeptJetDR(11,0,0,1));
			Wele.effMC.push_back((double)eff);
			Wele.errMC.push_back((double)eff_err);
			if(fVerbose>1){
			cout << "++event   " << fMT2tree->misc.Event          << endl;
			cout << "  ele pt  " << fMT2tree->ele[0].lv.Pt()      << endl;
			cout << "  ele eta " << fMT2tree->ele[0].lv.Eta()     << endl;
			cout << "  ele dR  " << fMT2tree->LeptJetDR(11,0,0,1) << endl;
			cout << "  ele eff " << eff << " pm " << eff_err          << endl;
			}
		}else if(process=="muo_data"){
			float eff=0; float eff_err=0;
			PabloEffMuo(fMT2tree->muo[0].lv.Pt(), fMT2tree->muo[0].lv.Eta(), fMT2tree->LeptJetDR(13,0,0,1), fTypeOfEffErr, eff, eff_err, true);
			Wmuo.pt .push_back(fMT2tree->muo[0].lv.Pt());
			Wmuo.eta.push_back(fMT2tree->muo[0].lv.Eta());
			Wmuo.dR .push_back(fMT2tree->LeptJetDR(13,0,0,1));
			Wmuo.eff.push_back((double) eff);
			Wmuo.err.push_back((double) eff_err);
			if(fVerbose>1){
			cout << "++event   " << fMT2tree->misc.Event          << endl;
			cout << "  muo pt  " << fMT2tree->muo[0].lv.Pt()      << endl;
			cout << "  muo eta " << fMT2tree->muo[0].lv.Eta()     << endl;
			cout << "  muo dR  " << fMT2tree->LeptJetDR(13,0,0,1) << endl;
			cout << "  muo eff " << eff  << " pm " << eff_err     << endl;
			}
		}else if(process=="muo" || process=="muoTop"){
			float eff=0; float eff_err=0;
			PabloEffMuo(fMT2tree->muo[0].lv.Pt(), fMT2tree->muo[0].lv.Eta(), fMT2tree->LeptJetDR(13,0,0,1), fTypeOfEffErr, eff, eff_err, false);
			Wmuo.ptMC .push_back(fMT2tree->muo[0].lv.Pt());
			Wmuo.etaMC.push_back(fMT2tree->muo[0].lv.Eta());
			Wmuo.dRMC .push_back(fMT2tree->LeptJetDR(13,0,0,1));
			Wmuo.effMC.push_back((double)eff);
			Wmuo.errMC.push_back((double)eff_err);
			if(fVerbose>1){
			cout << "++event   " << fMT2tree->misc.Event          << endl;
			cout << "  ele pt  " << fMT2tree->muo[0].lv.Pt()      << endl;
			cout << "  ele eta " << fMT2tree->muo[0].lv.Eta()     << endl;
			cout << "  ele dR  " << fMT2tree->LeptJetDR(13,0,0,1) << endl;
			cout << "  ele eff " << eff << " pm " << eff_err      << endl;
			}
		}
	}
	return myEvtList->GetN();
}	

TH1D* GetHisto(TChain* chain, TString var, TString basecut, TString name){
  // double xbin[10]={0,25,50,75,100,125,150,200,300,450}; 
    double xbin[5]={125,150,200,250,1500}; 
	//TH1D* h = new TH1D(name,"", 60, 0, 1500);
	//TH1D* h = new TH1D(name,"", 9, xbin);
	TH1D* h = new TH1D(name,"", 4, xbin); // change on 30 oct, since we have already a cut on MT2>125 GeV 
	TString varname = var + h->GetName();
	cout << "+++drawing:  " << chain->GetName() << "\n"
	     << "             " << varname << " with cut " << basecut << endl;
	int n = chain->Draw(varname,basecut,"goff");
	cout << " MC events " << n << endl;
	return h;
}

void setStyle(){
	gROOT->ProcessLine(".x ~casal/SetStyle_PRD.C");
	gStyle->SetLegendBorderSize(0);
	gStyle->SetFillStyle(0);
	gStyle->SetTextFont(62);
	gStyle->SetTextSize(0.045);
	gStyle->SetPalette(1);
}

void printTable(){

		cout << "	-->> Wele.prob() " << Wele.prob() << " pm " << Wele.prob_err_sys() << endl;
		cout << "	-->> Wmuo.prob() " << Wmuo.prob() << " pm " << Wmuo.prob_err_sys() << endl;
	cout << "*********************************************************************" << endl;
	cout << "\%BEGINLATEX\%"             << endl;
	cout << "\\begin{table}"             << endl
	     << "\\begin{center}"            << endl
             << "\\begin{tabular}{lcc}"      << endl	     
	     << "\\hline\\hline"             << endl
	     << "                               &  $" << "W\\to e \\nu"      << "$ & $" << " W\\to \\mu \\nu$ \\\\"               << endl
	     << "\\hline"                                                                                                         << endl
	     << " $N_{e,\\mu}^{reco}$           &  $" << Wele.nData          << "$ & $" << Wmuo.nData          << "$ \\\\"        << endl
	     << "\\hline"                                                                                                         << endl;
	if(fIncludeTop && !fTopOnly){
	cout << setprecision(4)
	     << " $N_{e,\\mu}^{MC}(W \\& Top)$  &  $" << Wele.nW_scaled()-Wele.nW_bg_scaled()
     	                                                                     << "$ & $" << Wmuo.nW_scaled()-Wmuo.nW_bg_scaled()         
									                                       << "$ \\\\"        << endl
	     << "\\hline"                                                                                                         << endl;
	}
	if(fTopOnly){
	cout << setprecision(4)
	     << " $N_{e,\\mu}^{MC}(Top)$        &  $" << Wele.nW_scaled()-Wele.nW_bg_scaled()
     	                                                                     << "$ & $" << Wmuo.nW_scaled()-Wmuo.nW_bg_scaled()         
									                                       << "$ \\\\"        << endl
	     << "\\hline"                                                                                                         << endl;
		
	}
	if(! fIncludeTop){
	cout << setprecision(4)
	     << " $N_{e,\\mu}^{MC}(W)$          &  $" << Wele.nW_scaled()-Wele.nW_bg_scaled()
     	                                                                     << "$ & $" << Wmuo.nW_scaled()-Wmuo.nW_bg_scaled()         
									                                       << "$ \\\\"        << endl
	     << "\\hline"                                                                                                         << endl;
	}
	if(fIncludeTop && !fTopOnly){
	cout << " $N_{e,\\mu}^{bg}(W \\&Top \\ BG)$ &  $" << Wele.nW_bg_scaled() << "$ & $" << Wmuo.nW_bg_scaled() << "$ \\\\"        << endl;
	}
	if(fTopOnly){
	cout << " $N_{e,\\mu}^{bg}(Top)$        &  $" << Wele.nW_bg_scaled() << "$ & $" << Wmuo.nW_bg_scaled() << "$ \\\\"        << endl
	     << " $N_{e,\\mu}^{bg}(W)  $        &  $" << Wele.W_bg           << "$ & $" << Wmuo.W_bg           << "$ \\\\"        << endl;
	}
	if(!fIncludeTop){
	cout << " $N_{e,\\mu}^{bg}(W)$          &  $" << Wele.nW_bg_scaled() << "$ & $" << Wmuo.nW_bg_scaled() << "$ \\\\"        << endl
	     << " $N_{e,\\mu}^{bg}(Top)$        &  $" << Wele.Top_bg         << "$ & $" << Wmuo.Top_bg         << "$ \\\\"        << endl;
	}
	cout << " $N_{e,\\mu}^{bg}(Z)$          &  $" << Wele.Z_bg           << "$ & $" << Wmuo.Z_bg           << "$ \\\\"        << endl
	     << " $N_{e,\\mu}^{bg}(QCD)$        &  $" << Wele.QCD_bg         << "$ & $" << Wmuo.QCD_bg         << "$ \\\\"        << endl
	     << " $N_{e,\\mu}^{bg}(Other)$      &  $" << Wele.Other_bg       << "$ & $" << Wmuo.Other_bg       << "$ \\\\"        << endl
	     << "\\hline"                                                                                                         << endl;
	cout << " $\\varepsilon      $          &  $" << Wele.prob()         << "$ & $" << Wmuo.prob()       << "$ \\\\"        << endl;
	cout << "\\hline"                                                                                                         << endl
	     << setprecision(3) 
	     << " $W_{e,\\mu}^{pass \\ veto}$ &  $"   << Wele.pred()        
	                                              << " \\pm "             << Wele.pred_error_stat()   
						      << " \\ (stat) \\ \\pm "<< Wele.pred_error_sys()          << " \\ (sys) \\"                 
	                                              << " $ & $"             << Wmuo.pred()        
	                                              << " \\ \\pm "          << Wmuo.pred_error_stat()   
						      << " \\ (stat) \\ \\pm "<< Wmuo.pred_error_sys()          << "\\ (sys) $ \\\\"<< endl   
	     << "\\hline"                                                                                                        << endl
	     << setprecision(4) 
	     << " $W_{e,\\mu}^{pass \\ veto}$ MC & $"<< Wele.nW_leptveto_scaled() << "$ & $" << Wmuo.nW_leptveto_scaled() <<  " $ \\\\ "   << endl  
	     << "\\hline\\hline"                                                                                                << endl
	     << "\\end{tabular}"                                                                                                << endl
	     << "\\end{center}"                                                                                                 << endl
	     << "\\end{table}"                                                                                                  << endl
	     << "\%ENDLATEX\%"                                                                                                  << endl
	     << endl;

//	cout << "\%BEGINLATEX\%"                                                                                                << endl
//	     << "\\begin{table}"                                                                                                << endl
//	     << "\\begin{center}"                                                                                               << endl
//             << "\\begin{tabular}{lcc}"                                                                                         << endl	     
//	     << "\\hline\\hline"                                                                                                << endl;
//	if(fIncludeTaus){
//	cout << "                                      &  $" << " W\\to \\tau \\nu, \\ \\tau \\to \\ hadrons$ \\\\"             << endl;
//	}else{
//	cout << "                                      &  $" << " W\\to \\tau \\nu, \\ \\tau \\to \\ anything$  \\\\"           << endl;
//	}	
//	cout << " MC  events  passing  l-veto          &  $" << nTau_leptveto << "$ \\\\"                                       << endl
//	     << "\\hline\\hline"                                                                                                << endl
//	     << "\\end{tabular}"                                                                                                << endl
//	     << "\\end{center}"                                                                                                 << endl
//	     << "\\end{table}"                                                                                                  << endl
//	     << "\%ENDLATEX\%"                                                                                                  << endl
//	     << endl;
//	cout << "*********************************************************************" << endl;
		     

}

void InclusiveEstimation(){

        TH1D* h = findingRLL();
        double muofactor = h->GetBinContent(1);
        double muoerror  = h->GetBinError(1);
        double elefactor = h->GetBinContent(2);
        double eleerror  = h->GetBinError(2);
	cout<<"*** electrons ***"<<endl;
	double centralvalue = (Wele.nData-Wele.bg())*elefactor;
	double stat = sqrt(Wele.nData)*elefactor;
	double system = sqrt(pow(((Wele.nData-Wele.bg())*eleerror),2)+pow(Wele.bg()*elefactor,2));
	cout<<centralvalue<<" +- "<<stat<<" +- "<<system<<endl;
	double mcpred = (Wele.all_MC()-Wele.bg())*elefactor;
	cout<<"		>>>>>>>>> MC prediction"<<mcpred<<endl;
	cout<<"*** muons ***"<<endl;
	centralvalue = (Wmuo.nData-Wmuo.bg())*muofactor;
	stat = sqrt(Wmuo.nData)*muofactor;
	system = sqrt(pow(((Wmuo.nData-Wmuo.bg())*muoerror),2)+pow(Wmuo.bg()*muofactor,2));
	cout<<centralvalue<<" +- "<<stat<<" +- "<<system<<endl;
	mcpred = (Wmuo.all_MC()-Wmuo.bg())*muofactor;
	cout<<"		>>>>>>>>> MC prediction"<<mcpred<<endl;
}
void LostLeptonInMT2Bins(){

	cout<<">>>> nw: "<<(Wele.hnW_scaled())->Integral()<<" bg: "<<(Wele.hnW_bg_scaled())->Integral()<<" lepton veto: "<<(Wele.hnW_leptveto_scaled())->Integral()<<" >>>>"<<endl;
	cout<<">>>> nw: "<<(Wmuo.hnW_scaled())->Integral()<<" bg: "<<(Wmuo.hnW_bg_scaled())->Integral()<<" lepton veto: "<<(Wmuo.hnW_leptveto_scaled())->Integral()<<" >>>>"<<endl;

	TH1D* h = findingRLL();
	double muofactor = h->GetBinContent(1);
	double muoerror  = h->GetBinError(1);
	double elefactor = h->GetBinContent(2);
	double eleerror  = h->GetBinError(2);

	cout<<"Wele.binByBinMCTruthError[0] "<<Wele.binByBinMCTruthError[0]<<endl;
	cout<<"Wele.binByBinMCTruthError[1] "<<Wele.binByBinMCTruthError[1]<<endl;
	cout<<"Wele.binByBinMCTruthError[2] "<<Wele.binByBinMCTruthError[2]<<endl;
	cout<<"Wele.binByBinMCTruthError[3] "<<Wele.binByBinMCTruthError[3]<<endl;
	for (unsigned int i = 1; i <= (Wele.hdata())->GetNbinsX(); i++)
	{
		cout<<"		-> bin "<<i<<" -------------------------------------------------------------"<<endl;
		double lostlepton = ((Wele.hdata())->GetBinContent(i)-(Wele.hnW_bg_scaled())->GetBinContent(i)-zbg_ele[i-1]-qcdbg_ele[i])*elefactor; 
		cout<<"			-> electrons: "<<lostlepton<<" compared to MC-truth: "<<(Wele.hnW_leptveto_scaled())->GetBinContent(i)<<" +- "<<Wele.binByBinMCTruthError[i-1]<<endl;
		cout<<"				      "<<" +- "<<sqrt((Wele.hdata())->GetBinContent(i))*elefactor<<" (stat) "<<endl;
		cout<<"				      "<<" +- "<<sqrt(pow((((Wele.hdata())->GetBinContent(i)-(Wele.hnW_bg_scaled())->GetBinContent(i)-zbg_ele[i-1]-qcdbg_ele[i])*eleerror),2)+pow(((Wele.hnW_bg_scaled())->GetBinContent(i)+zbg_ele[i-1]+qcdbg_ele[i])*elefactor,2))<<" (sys) "<<endl;
		lostlepton = ((Wmuo.hdata())->GetBinContent(i) - (Wmuo.hnW_bg_scaled())->GetBinContent(i)-zbg_muo[i-1]-qcdbg_muo[i-1])*muofactor; 
		cout<<"			-> muons: "<<lostlepton<<" compared to MC-truth: "<<(Wmuo.hnW_leptveto_scaled())->GetBinContent(i)<<" +- "<<Wmuo.binByBinMCTruthError[i-1]<<endl;
		cout<<"				      "<<" +- "<<sqrt((Wmuo.hdata())->GetBinContent(i))*muofactor<<" (stat) "<<endl;
		cout<<"				      "<<" +- "<<sqrt(pow((((Wmuo.hdata())->GetBinContent(i)-(Wmuo.hnW_bg_scaled())->GetBinContent(i)-zbg_muo[i-1]-qcdbg_muo[i-1])*muoerror),2)+pow(((Wmuo.hnW_bg_scaled())->GetBinContent(i)+zbg_muo[i-1]+qcdbg_muo[i-1])*muofactor,2))<<" (sys) "<<endl;
	}
}

void readEfficienciesPablo(){	
	// electros

	cout << "--------------------------------------" << endl;
	cout << "Read Pablo EffTrees " << endl;	
  	TFile* fele   = TFile::Open(fPablofile_ele_data);
  	TFile* feleMC = TFile::Open(fPablofile_ele_mc);
  	if (!fele || !feleMC) {
		cout << "ERROR : Could not open file " << fPablofile_ele_data << " or " fPablofile_ele_mc<< "!"  << endl;
	    	exit(1);
  	}
  
  	fele->GetObject("histo_electron_var1pt_var2dr_data",WeleEffHistdR) ;
  	fele->GetObject("histo_electron_var1pt_var2eta_data",WeleEffHistEta);
  	feleMC->GetObject("histo_electron_var1pt_var2dr_mc",WeleEffHistdRMC) ;
  	feleMC->GetObject("histo_electron_var1pt_var2eta_mc",WeleEffHistEtaMC);
	if(WeleEffHistdR==NULL || WeleEffHistEta==NULL || WeleEffHistdRMC==NULL || WeleEffHistEtaMC==NULL) {cout << " cannot get hist" << endl; exit(-1);}

	// muons
	TFile* fmuo   = TFile::Open(fPablofile_muo_data);
	TFile* fmuoMC = TFile::Open(fPablofile_muo_mc);
  	if (!fmuo || !fmuoMC) {
		cout << "ERROR : Could not open file " << fPablofile_muo_data << " or " << fPablofile_muo_mc << "!"  << endl;
	    	exit(1);
  	}
  
  	fmuo  ->GetObject("histo_muon_var1pt_var2dr_data" ,WmuoEffHistdR) ;
  	fmuo  ->GetObject("histo_muon_var1pt_var2eta_data",WmuoEffHistEta);
  	fmuoMC->GetObject("histo_muon_var1pt_var2dr_mc" ,WmuoEffHistdRMC) ;
  	fmuoMC->GetObject("histo_muon_var1pt_var2eta_mc",WmuoEffHistEtaMC);
	if(WmuoEffHistdR==NULL || WmuoEffHistEta==NULL || WmuoEffHistdRMC==NULL || WmuoEffHistdRMC==NULL) {cout << " cannot get hist" << endl; exit(-1);}

	cout << " done"                                  << endl;
	cout << "--------------------------------------" << endl;
}

void PabloEffEle(float pt_, float eta_, float dr_, int typeOfError, float &eff, float &err, bool data) {
	if(! fMakeEfficienciesPablo) return;

	float efficiency,  e_efficiency1, e_efficiency2;
	float pt, eta, dr, njets;
	float ptwidth, etawidth, drwidth, njetswidth;
	TH2F* H_eta=(data)? WeleEffHistEta->Clone(): WeleEffHistEtaMC->Clone();
	TH2F* H_dR =(data)? WeleEffHistdR ->Clone(): WeleEffHistdRMC ->Clone();
	if(pt_ < 20){
		int bin = 	H_eta->FindBin(pt_, eta_);
		if(bin!=1){ 
			eff = H_eta->GetBinContent( bin  );
			err = H_eta->GetBinError( bin  );
		}
		else exit(-1);
	}
	else{
		int bin = -1;
		float tmpDr=dr_, tmpPt=pt_;
		// for leptons with dR<0.5, I'm taking dR=0.5. Same for pt
		if(dr_ <0.5) tmpDr = 0.5;
		if(pt_ >200) tmpPt = 199;
		bin = H_dR->FindBin(tmpPt, tmpDr );
		if(bin!=-1){ 
			eff = H_dR->GetBinContent( bin  );
			err = H_dR->GetBinError( bin  );
		}
		else exit(-1);
	}

	if(eff==0) {cout << "eff not found " << endl; exit(1);}

}

void PabloEffMuo(float pt_, float eta_, float dr_ , int typeOfError, float &eff, float &err, bool data) {
	if(! fMakeEfficienciesPablo) return;

	float efficiency,  e_efficiency1, e_efficiency2;
	float pt, eta, dr, njets;
	float ptwidth, etawidth, drwidth, njetswidth;
	TH2F* H_eta=(data)? WmuoEffHistEta->Clone(): WmuoEffHistEtaMC->Clone();
	TH2F* H_dR =(data)? WmuoEffHistdR ->Clone(): WmuoEffHistdRMC ->Clone();


	if(pt_ < 20){
		int bin = 	H_eta->FindBin(pt_, eta_);
		if(bin!=1){ 
			eff = H_eta->GetBinContent( bin  );
			err = H_eta->GetBinError( bin  );
		}
		else exit(-1);
	}
	else{
		int bin = -1;
		float tmpDr=dr_;
		float tmpPt=pt_;
		// for leptons with dR<0.5, I'm taking dR=0.5. Same for pt
		if(dr_ <0.5) tmpDr = 0.5;
		if(pt_ >200) tmpPt = 199;
		bin = H_dR->FindBin(tmpPt, tmpDr );
		if(bin!=-1){ 
			eff = H_dR->GetBinContent( bin  );
			err = H_dR->GetBinError( bin  );
		}
		else exit(-1);
	}

	if(eff==0) {cout << "eff not found " << endl; exit(1);}

}
