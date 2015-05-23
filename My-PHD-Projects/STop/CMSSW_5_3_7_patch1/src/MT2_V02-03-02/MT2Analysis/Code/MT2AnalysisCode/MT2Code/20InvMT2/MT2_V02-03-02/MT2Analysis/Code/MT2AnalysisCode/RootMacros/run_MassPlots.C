{
  TString outputdir = "../MassPlots/";
  //TString samples   = "./samples/samplesMine.dat";
  //TString samples   = "./samples/samplesMineSmearedJet.dat";
  //TString samples   = "./samples/samplesMineSmearedJetsNewBTag.dat";
//  TString samples   = "./samples/samplesMineSmearedJetMETNewBTag.dat";
  TString samples   = "./samples/samplesMineSmearedJetMETNewBTagParked.dat";
  int verbose =3;

  gSystem->CompileMacro("../MT2Code/src/MassPlotter.cc", "k");
  gROOT->ProcessLine(".x SetStyle_PRD.C");

  int gNMT2bins                   = 17;
  double  gMT2bins[gNMT2bins+1]   = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 300, 400, 550, 800}; 	
  
  int gNMT2Bbins                   = 15;
  double  gMT2Bbins[gNMT2bins+1]   = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 300, 500}; 	

  int gNMT2bins_l                   = 14;
  double  gMT2bins_l[gNMT2bins+1]   = {0, 10, 20, 30, 40, 50, 65, 80, 95, 115, 140, 180, 250, 350, 500}; 	

  MassPlotter *tA = new MassPlotter(outputdir, "MassPlots.root");
  tA->SetSave(false);
  tA->setVerbose(verbose);
  tA->init(samples);
  tA->SetIsPhoton(false);
  
  std::ostringstream cutStream;
  cutStream << " " 
	    // cmmented on 13 sep to find fit values 
//	    << "misc.MT2>125"                                              << "&&"
	    << "misc.MET>30"                                                << "&&"
	    << "NJetsIDLoose40  >=4"                                         << "&&"
   	    << "NBJetsCSVT > 0"                                              << "&&"
 	    << "misc.Jet0Pass ==1"                                           << "&&"
 	    << "misc.Jet1Pass ==1"                                           << "&&"
 	    << "misc.PassJetID ==1"                                          << "&&"
            << "misc.Vectorsumpt < 70"                                       << "&&"
            << "(misc.ProcessID!=10 || (Susy.MassGlu >= 350 && Susy.MassGlu < 355"<< "&&"
            << "Susy.MassLSP >= 50 && Susy.MassLSP < 55))"                     << "&&"
// mindphi4 is relaxed for pt and mt distributions
	    << "(misc.MinMetJetDPhi4 >0.3)"                                  << "&&"
	    // cmmented on 13 sep to find fit values
	    << "((NEles==0 || ele[0].lv.Pt()<5) && (NMuons==0 || muo[0].lv.Pt()<5))"                    << "&&"
	    //<< "(NEles==1 && NMuons==0)"                    << "&&"// just for pt and mt distributions
	    //<< "(NEles==0 && NMuons==1)"                  << "&&"// just for pt and mt distributions
//	    << "(NEles==1 && NMuons==0 && ele[0].MT<100)"                    << "&&"
//	    << "(NEles==0 && NMuons==1 && muo[0].MT<100)"                  << "&&"

/// offline triggers for non-parked data, commented on Nov 16
///  <<"(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0))"<<"||"
//  <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0)))";
///  <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0)))";
/* offline trigger cuts for parked data */
<<"((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 80.0) || (NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 65.0))";

  std::ostringstream triggerStream;
  triggerStream << "( "
		<<" misc.ProcessID != 0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 " <<"&&"
		<<" misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 " <<"&&"
		<<" misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 " <<"&&"
		<<" misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 )" <<"&&("
    
    //Or between Six and Quad
/// online triggers for non-parked data, commented on Nov 16
/*
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
		<< " ((NJetsIDLoose40  >=6 "            << "&&"
                << " jet[5].lv.Pt() >= 65.0 "       << "))))))";
//		<< " jet[5].lv.Pt() >= 65.0 "       << ") ||"
//		<< " (NJetsIDLoose40  >=7 "            << "&&"
//		<< " jet[6].lv.Pt() >= 55.0 "       << "))))))";
*/
// online trigger cuts for parkded data
                << "(((trigger.HLT_QuadJet50_v1 ==1)" << "||"
                << "(trigger.HLT_QuadJet50_v2 ==1)" << "||"
                << "(trigger.HLT_QuadJet50_v3 ==1)" << "||"
                << "(trigger.HLT_QuadJet50_v5 ==1)" << ") &&"

                << " ((NJetsIDLoose40  >=4 "            << "&&"
                << " jet[3].lv.Pt() >= 80.0 "       << ") || "
                << " (NJetsIDLoose40  >=5 "            << "&&"
                << " jet[4].lv.Pt() >= 65.0 "       << "))))))";

  TString trigger = triggerStream.str().c_str();
  TString cuts = cutStream.str().c_str();
 
  //tA->SetPileUpReweight(false);
   
  //                     variable,              cuts,  njet, nbjet, nlep,     HLT,     xtitle             nbins  bins      flip_order,    log  , comp ,  ratio, stack, overlay
  //tA->makePlot("misc.HT",              cuts,    -1,  -10 ,-10 ,    trigger , "HT"      ,40,   0, 1000,        false,         true ,  true,   true,  true,  true, 1);
  tA->makePlot("misc.MT2",             cuts,    -1,  -1 , -10 ,   trigger , "M_{T2}"     , 60, 0, 1500, false, false ,  true,   false,  true, true, 1);
  //tA->makePlot("misc.Vectorsumpt",             cuts,    -1,  -1 , -10 ,   trigger , "VSPT"     , 50, 0, 500, false, true ,  true,   true,  true,  true, 1);
   //tA->makePlot("ele[0].lv.Pt()", cuts, -1, -1, -10 , trigger , "Electron p_{T}", 15, 0, 300, false, false, true, true, true, true, 1); 
   //tA->makePlot("muo[0].lv.Pt()", cuts, -1, -1, -10 , trigger , "Muon p_{T}", 15, 0, 300, false, false, true, true, true, true, 1);
   //tA->makePlot("ele[0].MT", cuts, -1, -1, -10 , trigger , "Electron m_{T}", 15, 0, 300, false, false, true, true, true, true, 1); 
   //tA->makePlot("muo[0].MT", cuts, -1, -1, -10 , trigger , "Muon m_{T}", 15, 0, 300, false, false, true, true, true, true, 1);
  //tA->TriggerEfficiency(5, 3, 0, 100000000000);
  //tA->SortHighMT2(100.0, 100000000);

  //tA->TopStudy("TTbar",3000);
  //tA->TauContamination(-1, 1000000000, 27);
  //tA->Efficiency("SMS");
  //tA->MySmallMakePlot(1000000000);
  //tA->makeSmallCopy(100000000,100);
  //tA->QCD();
  //tA->PrintContent(10000000,true);
}
