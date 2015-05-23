{

  TString outputdir = "../Histos/";
  //  TString outname = "ZInv-MT2_0_9999-HT_800-1Mu_pt10";
  bool EFF_CORR=false;
  float MT2_low =  -1;
  float MT2_high = 9999;
  int NEles = 0;
  int NMuons = 0;
  bool IS_MC = false;

  ostringstream MT2_low_s, MT2_high_s;
  MT2_low_s << MT2_low;
  MT2_high_s << MT2_high;
  TString outname = "ZInv-MT2_"+MT2_low_s.str()+"_"+MT2_high_s.str()+"-Jet40-HT_700-1Mu_pt10_4450pb";
  if(IS_MC) outname += "-MC_Closure";

//  TString samples   = "../MT2Code/samples/samplesMine_full.dat";
//  TString samples   = "../MT2Code/samples/samplesMine.dat";
//  TString samples   = "../MT2Code/samples/samplesMineSmearedJet.dat"; 
//  TString samples   = "../MT2Code/samples/samplesMineSmearedJetsNewBTag.dat";
//  TString samples  = "../MT2Code/samples/samplesMineSmearedJetMETNewBTag.dat";
//  TString samples  = "../MT2Code/samples/samplesMineSmearedJetMETNewBTagParkedNewSamples.dat";
TString samples  = "../MT2Code/samples/samplesMineSmearedJetMETNewBTagParkedNewSamples_No7trig.dat";
//  TString samples  = "../MT2Code/samples/samplesMineSmearedJetMETNewBTagParked.dat";

  int verbose = 0;

  gSystem->CompileMacro("../MT2Code/src/ZInvEstFromW.cc", "k");
  gROOT->ProcessLine(".x SetStyle_PRD.C");

  ZInvEstFromW *tA = new ZInvEstFromW(outputdir);
  


  tA->setVerbose(verbose);
  tA->init(samples);

// added by esi for parked data
/*
  std::ostringstream cutStream;
  cutStream << " " 
            << "(misc.ProcessID!=10 || (Susy.MassGlu >= 350 && Susy.MassGlu < 355"<< "&&"
            << "Susy.MassLSP >= 50 && Susy.MassLSP < 55))"                     << "&&"
            << "misc.MT2>125"                                                << "&&"
	    << "misc.MET>30"                                                << "&&"
	    << "NJetsIDLoose40  >=4"                                         << "&&"
 	    << "misc.Jet0Pass ==1"                                           << "&&"
 	    << "misc.Jet1Pass ==1"                                           << "&&"
 	    << "misc.PassJetID ==1"                                          << "&&"
    	    << "misc.Vectorsumpt < 70"                                       << "&&"
	    << "misc.MinMetJetDPhi4 >0.3"                                    << "&&"

	    
    // QuadJet45/50
  <<"((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 80.0) || (NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 65.0))";



  std::ostringstream triggerStream;
  triggerStream << "( "
		<<" misc.ProcessID != 0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 " <<"&&"
		<<" misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 " <<"&&"
		<<" misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 " <<"&&"
		<<" misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 )" <<"&&("

   //Or between Six and Quad
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
 
/*/
//added by esi for no 7 trigger
  std::ostringstream cutStream;
  cutStream << " " 
            << "(misc.ProcessID!=10 || (Susy.MassGlu >= 350 && Susy.MassGlu < 355"<< "&&"
            << "Susy.MassLSP >= 50 && Susy.MassLSP < 55))"                     << "&&"
            << "misc.MT2>125"                                                << "&&"
	    << "misc.MET>30"                                                << "&&"
	    << "NJetsIDLoose40  >=4"                                         << "&&"
 	    << "misc.Jet0Pass ==1"                                           << "&&"
 	    << "misc.Jet1Pass ==1"                                           << "&&"
 	    << "misc.PassJetID ==1"                                          << "&&"
    	    << "misc.Vectorsumpt < 70"                                       << "&&"
	    << "misc.MinMetJetDPhi4 >0.3"                                    << "&&"

	    
    //Or between Six and Quad
	    <<"(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0))"<<"||"
 	    <<"(NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0))";



  std::ostringstream triggerStream;
  triggerStream << "( "
		<<" misc.ProcessID != 0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 " <<"&&"
		<<" misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 " <<"&&"
		<<" misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 " <<"&&"
		<<" misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 )" <<"&&("

   //Or between Six and Quad
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

  TString trigger = triggerStream.str().c_str();
  TString cuts = cutStream.str().c_str();
 

/*/

/*
  std::ostringstream cutStream;
  cutStream << " " 
	    << "misc.MET             >  30"                            << "&&"
	    << "NJetsIDLoose40       >= 4                                  && "
	    << "misc.Jet0Pass        == 1                                   &&"
	    << "misc.Jet1Pass        == 1                                   &&"
	    << "misc.PassJetID       == 1                                  &&"
	    << "misc.Vectorsumpt     <  70                                 &&"
	    << "misc.MT2             > 125                                 &&"
	    <<"(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0))"<<"||"
	    <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0)))";



  std::ostringstream triggerStream;
  triggerStream << "( "
		<<" misc.ProcessID!=0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 " <<"&&"
		<<" misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 " <<"&&"
		<<" misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 " <<"&&"
		<<" misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 )" <<"&&("
    //Or between Six and Quad
        	<< "(((trigger.HLT_QuadJet80_v1 ==1)" << "||"
		<< "(trigger.HLT_QuadJet80_v2 ==1)" << "||"
		<< "(trigger.HLT_QuadJet80_v3 ==1)" << "||"
		<< "(trigger.HLT_QuadJet80_v4 ==1)" << "||"
		<< "(trigger.HLT_QuadJet80_v6 ==1)" << ") &&"
		<< " (NJetsIDLoose40  >=4 "            << "&&"
		<< " jet[3].lv.Pt() >= 100.0 "       << ") || "
		<< " (NJetsIDLoose40  >=5 "            << "&&"
		<< " jet[4].lv.Pt() >= 85.0 "       << ")) || "


		<< "(((trigger.HLT_SixJet45_v1 ==1)" << "||"
		<< "(trigger.HLT_SixJet45_v2 ==1)" << "||"
		<< "(trigger.HLT_SixJet45_v3 ==1)" << ") &&"
		<< " (NJetsIDLoose40  >=6 "            << "&&"
		<< " jet[5].lv.Pt() >= 65.0 "       << ") ||"
		<< " (NJetsIDLoose40  >=7 "            << "&&"
		<< " jet[6].lv.Pt() >= 55.0 "       << ")))))";


  TString trigger = triggerStream.str().c_str();
  
  TString cuts = cutStream.str().c_str();

  */
  //actual call
  float *ttbarRes = new float[10];
  ttbarRes = tA->Analysis("MT2b", IS_MC, "histos_"+outname+"_1b.root", 3, NEles, NMuons, MT2_low, MT2_high, trigger, cuts, true, EFF_CORR);
  cout << "ttbarRes is ready"<< endl;
             tA->Analysis("MT2b", IS_MC, "histos_"+outname+"_0b.root", 3, NEles, NMuons, MT2_low, MT2_high, trigger, cuts, false, EFF_CORR, ttbarRes);

}
