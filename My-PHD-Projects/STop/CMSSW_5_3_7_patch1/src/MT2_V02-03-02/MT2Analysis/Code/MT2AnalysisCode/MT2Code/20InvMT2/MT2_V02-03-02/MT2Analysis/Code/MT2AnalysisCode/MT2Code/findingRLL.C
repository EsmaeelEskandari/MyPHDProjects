Double_t myfunc(double * x , double * par){
	double a = (1.-x[0])*(1.-x[0]);
	double b = (1.-x[0]*x[0]);
	double c = (1.+x[0])*(1.+x[0]);  
	return par[2]*(3./8.*a*par[0]+3./4.*b*par[1]+3./8.*c*(1.-par[0]-par[1])); 
}
Double_t linearFit(double * x , double * par){
	return (par[0]*x[0]+par[1]);
}
void findingRLL(){
        //gStyle->SetOptTitle(0);
        gStyle->SetOptStat(0);
	gStyle->SetStatFontSize(0.01); 
	gStyle->SetStatW(0.15);
	gStyle->SetStatH(0.2);                
	gStyle->SetStatY(0.9);                
	gStyle->SetStatX(0.9);                

	TH1::SetDefaultSumw2();

	TH1D * h = new TH1D("eff","eff",2,0,2);	

// most updated result with pu and btag scale factors applied in printwefficiency
	-->> Wele.prob() 0.411515 pm 0.055583
	-->> Wmuo.prob() 0.552687 pm 0.067688

// before applying btag sf
	-->> Wele.prob() 0.407692 pm 0.044487
	-->> Wmuo.prob() 0.545132 pm 0.053617

	double muo = 0.545139;
	double ele = 0.407714;

	h->SetBinContent(1,muo);
	h->SetBinError(1,0.053606);
	h->SetBinContent(2,ele);
	h->SetBinError(2,0.044457);

	TH1D * f = new TH1D("f","f",2,0,2);	

        f->SetBinContent(1,0.778096);
        f->SetBinContent(2,0.803913);
        f->SetBinError(1,0.0243038);
        f->SetBinError(2,0.0265745);

	TH1D * g = f->Clone();

	f->Divide(f, h, 1.0, 1.0, "B");
	//f->Divide(h);
	f->Add(g,-1);

	cout<<"muo; RLL : "<<f->GetBinContent(1)<<" +- "<<f->GetBinError(1)<<endl;
	cout<<"ele; RLL : "<<f->GetBinContent(2)<<" +- "<<f->GetBinError(2)<<endl;
}
