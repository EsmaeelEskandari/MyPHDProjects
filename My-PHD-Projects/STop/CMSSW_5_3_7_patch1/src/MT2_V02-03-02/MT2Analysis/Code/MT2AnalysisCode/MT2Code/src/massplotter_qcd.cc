void MassPlotter::QCD(){
  
  TH1::SetDefaultSumw2();
  double x[14] = {0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 125.0, 500.0, 2000.0}; 
  TH1F *MT2HighDPhi = new TH1F("MT2HighDPhi", "MT2HighDPhi", 13, x);//40,   0, 1000);//
  TH1F *MT2LowDPhi = new TH1F("MT2LowDPhi", "MT2LowDPhi", 13, x);//40,   0, 1000);//


    for(int ii = 0; ii <(int) fSamples.size(); ii++){
    sample Sample = fSamples[ii];
//    if(Sample.sname == "QCD" || Sample.sname == "SMS")
//       continue;
    if(Sample.type != "data")
      continue;

    fMT2tree = new MT2tree();

    Sample.tree->SetBranchAddress("MT2tree", &fMT2tree);
    Long64_t nentries =  Sample.tree->GetEntries();
    float Weight = Sample.xsection * Sample.kfact * Sample.lumi / (Sample.nevents * Sample.PU_avg_weight );
 
    if(Sample.type == "mc")
      Weight *= -1.0;
    
    std::cout << setfill('=') << std::setw(70) << "" << std::endl;
    cout << "looping over :     " <<endl;	
    cout << "   Name:           " << Sample.name << endl;
    cout << "   File:           " << (Sample.file)->GetName() << endl;
    cout << "   Events:         " << Sample.nevents  << endl;
    cout << "   Events in tree: " << nentries << endl; 
    cout << "   Xsection:       " << Sample.xsection << endl;
    cout << "   kfactor:        " << Sample.kfact << endl;
    cout << "   avg PU weight:  " << Sample.PU_avg_weight << endl;
    cout << "   Weight:         " << Weight <<endl;
    std::cout << setfill('-') << std::setw(70) << "" << std::endl;
    cout.precision(2);
    cout.setf(ios::fixed,ios::floatfield); 

    for (Long64_t jentry=0; jentry<nentries;jentry++) {
     
      Sample.tree->GetEntry(jentry); 
      if ( fVerbose>2 && jentry % 100000 == 0 ){ 
	fprintf(stdout, "\rProcessed events: %6d of %6d ", jentry + 1, nentries);
	fflush(stdout);
      }
      
      if (!((fMT2tree->NEles==0  ||  fMT2tree->ele[0].lv.Pt()<5)                   &&
	    (fMT2tree->NMuons==0 ||  fMT2tree->muo[0].lv.Pt()<5)))
	continue;

      if(fMT2tree->misc.MinMetJetDPhi4 > 0.3)
	MT2HighDPhi->Fill(fMT2tree->misc.MT2, Weight);
      else
	//if(fMT2tree->misc.MinMetJetDPhi4 <= 0.2)
	MT2LowDPhi->Fill(fMT2tree->misc.MT2, Weight);
    }}

    TCanvas *MyC = new TCanvas("MyC", "MyC");
    MyC->Divide(2,1);

    MyC->cd(1);
    cout<<"Low  "<<MT2LowDPhi->GetBinContent(14)<<" "<<MT2LowDPhi->GetBinError(14)<<endl;
    MT2LowDPhi->Draw();
    TH1F* hMT2HighDPhi = (TH1F*) MT2HighDPhi->Clone("hMT2HighDPhi");
    hMT2HighDPhi->SetName("hMT2HighDPhi");
    hMT2HighDPhi->SetLineColor(4);
    hMT2HighDPhi->Draw("sames");

    MyC->cd(2);
    cout<<"High "<<MT2HighDPhi->GetBinContent(14)<<" "<<MT2HighDPhi->GetBinError(14)<<endl;
    MT2HighDPhi->Divide(MT2LowDPhi);
    cout<<"Divi "<<MT2HighDPhi->GetBinContent(14)<<" "<<MT2HighDPhi->GetBinError(14)<<endl;
    MT2HighDPhi->Draw();
}
