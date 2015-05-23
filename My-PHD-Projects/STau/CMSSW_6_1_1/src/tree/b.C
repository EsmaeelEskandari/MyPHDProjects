void b() {

TFile *f = new TFile("a.root");
TTree *t2 = (TTree*)f->Get("t2");
Float_t destep;
TBranch *b_destep = t2->GetBranch("destep");
b_destep->SetAddress(&destep);

TH1F *hdestep = new TH1F("hdestep","destep in Mev",100,1e-5,3e-5);

Int_t nentries = (Int_t)t2->GetEntries();
for (Int_t i=0;i<nentries;i++) {
b_destep->GetEntry(i);
 
hdestep->Fill(destep);
}


TCanvas *c1 = new TCanvas("c1","c1",600,800);
c1->SetFillColor(42);
c1->Divide(1,2);

c1->cd(1);
hdestep->SetFillColor(45);
hdestep->Fit("gaus");

c1->cd(2);
gPad->SetFillColor(37);                                  
t2->SetMarkerColor(kRed);
t2->Draw("vect[0]:vect[1]:vect[2]");
if (gROOT->IsBatch()) return;

gPad->GetViewer3D(“x3d”);
}

