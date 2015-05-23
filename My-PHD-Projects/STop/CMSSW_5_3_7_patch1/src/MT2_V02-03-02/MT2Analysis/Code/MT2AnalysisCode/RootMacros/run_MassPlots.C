{
  TString outputdir = "../MassPlots/";
  TString samples   = "./samples/samplesMine.dat";
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
 
            << "misc.MT2>=125"                                                 << "&&"
            << "(misc.ProcessID!=10 || (Susy.MassGlu >= 350 && Susy.MassGlu < 355"<< "&&"
            << "Susy.MassLSP >= 50 && Susy.MassLSP < 55))"                     << "&&"
            << "NBJetsCSVT>=1"                                                    << "&&"
            << "misc.MET>=30"                                                     << "&&"
            << "misc.MinMetJetDPhi4 >0.3"                                         << "&&"
            << "misc.Vectorsumpt < 70"                                            << "&&"
            << "NJetsIDLoose40  >=4"                                              << "&&"
            << "(NEles==0  || ele[0].lv.Pt()<5)"                                  << "&&"
            << "(NMuons==0 || muo[0].lv.Pt()<5)"                                  << "&&"
            << "misc.Jet0Pass ==1"                                                << "&&"
            << "misc.Jet1Pass ==1"                                                << "&&"
            << "misc.PassJetID ==1"                                               << "&&"



   //       << "misc.HT>1500  "                                              << "&&"
    //      << "NTops > 0"                                                   << "&&"
    //      << "NTaus >0  && tau[0].Isolation3Hits > 1.5"                    << "&&"
    // //   << "misc.MT2<200&&misc.MT2>150  "                                << "&&"
//          << "misc.MT2 > 60 "                                              << "&&"
//          << "misc.MT2<80 "                                                << "&&"
       //   << "misc.MT2Top>130  "                                           << "&&"
    //      << "misc.MT2MassiveTop < 1000"                                   << "&&"
        //  << "misc.SecondJPt >100"                                         << "&&"
         // << "misc.LeadingJPt >150"                                        << "&&"
//          << "(misc.MinMetJetDPhi >0.3||misc.MinMetJetDPhiIndex>3)"        << "&&"
//           << "misc.MinMetJetDPhi > 0.3"                                   << "&&"
//          << "misc.MinMetBJetDPhi >0.7"                                    << "&&"
    //      << "misc.HBHENoiseFlagIso ==0"                                   << "&&"
    // //   << "misc.CSCTightHaloID==0"                                      << "&&"
    //      << "misc.CrazyHCAL==0";
  
//MC trigger
            <<"(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0))"<<"||"
            <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0);
// || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0)))";

    //HT Trigger
        // << "misc.HT>750";                             
        //  << "misc.HT>725";                             
        
    //Or between Six and Quad
         // <<"((NJets  >=4 && jet[3].lv.Pt() >= 120.0) || (NJets  >=6 && jet[5].lv.Pt() >= 80.0))";
         // <<"((NJets  >=4 && jet[3].lv.Pt() >= 100.0) || (NJets  >=6 && jet[5].lv.Pt() >= 70.0))";
 //         <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 95.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 60.0))";
        //  <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 90.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0))";
  //New Or
//          <<"(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 110.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 75.0))"<<"||"
//          <<"((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 95.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 60.0)))";


    //    <<"((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 120.0))";
 //        <<"((NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 80.0) && !(NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 120.0))";
 //      << "NJets  >=4 && 0==0";

  std::ostringstream triggerStream;
  triggerStream << "("
 
        <<" misc.ProcessID != 0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 " <<"&&"
        <<" misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 " <<"&&"
        <<" misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 " <<"&&"
        <<" misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 )" <<"&&("

 //    << "(trigger.HLT_PFHT650_v5 ==1)" << "||"
//     << "(trigger.HLT_PFHT650_v6 ==1)" << "||"
//     << "(trigger.HLT_PFHT650_v7 ==1)" << "||"
//     << "(trigger.HLT_PFHT650_v8 ==1)" << "||"
//     << "(trigger.HLT_PFHT650_v9 ==1)" << ")";

    // << "(trigger.HLT_QuadJet80_v1 ==1)" << "||"
    // << "(trigger.HLT_QuadJet80_v2 ==1)" << "||"
    // << "(trigger.HLT_QuadJet80_v3 ==1)" << ")";

    // << "(trigger.HLT_SixJet45_v1 ==1)" << "||"
    // << "(trigger.HLT_SixJet45_v2 ==1)" << "||"
    // << "(trigger.HLT_SixJet45_v3 ==1)" << ")";
    
    //Or between Six and Quad
        << "(((trigger.HLT_QuadJet80_v1 ==1)" << "||"
        << "(trigger.HLT_QuadJet80_v2 ==1)" << "||"
        << "(trigger.HLT_QuadJet80_v3 ==1)" << "||"
        << "(trigger.HLT_QuadJet80_v4 ==1)" << "||"
        << "(trigger.HLT_QuadJet80_v6 ==1)" << ") &&"
        // << " NJets >=4 "            << "&&"
        // << " jet[3].lv.Pt() >= 120.0 "       << ") || "
        // << " NJets >=4 "            << "&&"
        // << " jet[3].lv.Pt() >= 100.0 "       << ") || "
        // << " NJetsIDLoose40  >=5 "            << "&&"
        // << " jet[4].lv.Pt() >= 95.0 "       << ") || "
        // << " NJetsIDLoose40  >=5 "            << "&&"
        // << " jet[4].lv.Pt() >= 90.0 "       << ") || "
    //New Or
//         << " (NJetsIDLoose40  >=4 "            << "&&"
//         << " jet[3].lv.Pt() >= 110.0 "       << ") || "
//         << " (NJetsIDLoose40  >=5 "            << "&&"
//         << " jet[4].lv.Pt() >= 95.0 "       << ")) || "
            << " ((NJetsIDLoose40  >=4 "            << "&&"
            << " jet[3].lv.Pt() >= 100.0 "       << ") || "
            << " (NJetsIDLoose40  >=5 "            << "&&"
           << " jet[4].lv.Pt() >= 85.0 "       << "))) || "


        << "(((trigger.HLT_SixJet45_v1 ==1)" << "||"
        << "(trigger.HLT_SixJet45_v2 ==1)" << "||"
        << "(trigger.HLT_SixJet45_v3 ==1)" << "||"
        << "(trigger.HLT_SixJet45_v4 ==1)" << "||"
        << "(trigger.HLT_SixJet45_v6 ==1)" << ") &&"
        // << " NJets  >=6 "            << "&&"
        // << " jet[5].lv.Pt() >= 80.0 "       << "))";
        // << " NJets  >=6 "            << "&&"
        // << " jet[5].lv.Pt() >= 0.0 "       << "))";
             // << " NJetsIDLoose40  >=7 "            << "&&"
        // << " jet[6].lv.Pt() >= 60.0 "       << "))";
             // << " NJetsIDLoose40  >=7 "            << "&&"
        // << " jet[6].lv.Pt() >= 55.0 "       << "))";
  //New Or
//         << " (NJetsIDLoose40  >=6 "            << "&&"
//         << " jet[5].lv.Pt() >= 75.0 "       << ") ||"
//         << " (NJetsIDLoose40  >=7 "            << "&&"
//         << " jet[6].lv.Pt() >= 60.0 "       << ")))))";
        << " ((NJetsIDLoose40  >=6 "            << "&&"
        << " jet[5].lv.Pt() >= 65.0 "       << ") ||"
        << " (NJetsIDLoose40  >=7 "            << "&&"
        << " jet[6].lv.Pt() >= 55.0 "       << "))))))";



  //     << "(trigger.HLT_HT440_v2 ==1 && misc.Run<161216)" << "||"
  //     << "(trigger.HLT_HT450_v2 ==1 && (misc.Run>=161216 && misc.Run< 163269))" << "||"
  //     << "(trigger.HLT_HT500_v3 ==1 && (misc.Run>=163269 && misc.Run<=163869))" << "||"
  //     << "(trigger.HLT_HT500_v4 ==1 && (misc.Run>=165088 && misc.Run< 165970))" << "||"
  //     << "(trigger.HLT_HT550_v5 ==1 && (misc.Run>=165970 && misc.Run<=167043 && misc.Run!=166346))" << "||"
  //     << "(trigger.HLT_HT550_v6 ==1 && (misc.Run==166346))" << "||"
  //     << "(trigger.HLT_HT550_v7 ==1 && (misc.Run>=167078 && misc.Run< 170249))" << "||"
  //     << "(trigger.HLT_HT550_v8 ==1 && (misc.Run>=170249 && misc.Run< 173236))" << "||"
  //     << "(trigger.HLT_HT600_v1 ==1 && (misc.Run>=173236 && misc.Run< 178420))" << "||"
  //     << "(trigger.HLT_HT650_v4 ==1 && (misc.Run>=178420 && misc.Run< 179959))" << ")";
  TString trigger = triggerStream.str().c_str();
  TString cuts = cutStream.str().c_str();

  //tA->SetPileUpReweight(false);
   
  //                     variable,              cuts,  njet, nbjet, nlep,     HLT,     xtitle             nbins  bins      flip_order,    log  , comp ,  ratio, stack, overlay

 // tA->makePlot("NBJetsCSVT",              cuts,    -1,  -10 ,-10 ,    trigger , "NBJetsCSVT"      ,10,  0, 10,        false,         true ,  true,   true,  true,  true, 1,1);

 /// tA->makePlot("misc.HT",              cuts,    -1,  -10 ,-10 ,    trigger , "HT"      ,100,  0, 3000,        false,         true ,  true,   true,  true,  true, 1,1);

 //tA->makePlot("misc.MinMetJetDPhi4",              cuts,    -4,  -1 ,-10 ,    trigger , "MinMetJetDPhi4"      ,64,  0, 3.2,        false,         true ,  true,   true,  true,  true, 1,1);

// tA->makePlot("misc.Vectorsumpt",              cuts,    -4,  -1 ,-10 ,    trigger , "Vectorsumptout"      ,50,  0, 1000,        false,         true ,  true,   true,  true,  true, 1,1);


 //tA->makePlot("misc.MT2",              cuts,    -4,  -1 ,-10 ,    trigger , "MT2"      ,50,  0, 1000,        false,         true ,  true,   true,  true,  true, 1,1);

 //tA->makePlot("misc.SecondJPt",              cuts,    -4,  -1 ,-10 ,    trigger , "SecondJPt"      ,50,  0, 1000,        false,         true ,  true,   true,  true,  true, 1,1);

// tA->makePlot("misc.LeadingJPt",              cuts,    -4,  -1,-10 ,    trigger , "LeadingJPt"      ,50,  0, 1000,        false,         true ,  true,   true,  true,  true, 1,1);

 //tA->makePlot("misc.MET",              cuts,    -4,  -1 ,-10 ,    trigger , "MET"      ,50,  0, 1000,        false,         true ,  true,   true,  true,  true, 1,1);

 tA->makePlot("pileUp.NVertices",              cuts,    -4,  -10 ,-10 ,    trigger , "NVertices"      ,40,  0, 40,        false,         true ,  true,   true,  true,  true, 1,1);

  //saeid
  //NBJetsCSVT > 0 was removed from the list of the cuts.
  //Be careful, if you have a cut on bjets::
  //NBJetsCSVT >= N ==> nbjets == -N
  //NBJetsCSVT == M ==> nbjets == M
  //saeid

  //tA->makePlot("misc.MT2",             cuts,    -1,  -1 , -10 ,   trigger , "MT2"     , 10, 0, 350,        false,         true ,  true,   true,  true,  true, 1, 1);
  //tA->TriggerEfficiency(5, 3, 0, 100000000000);
  //tA->SortHighMT2(100.0, 100000000);

  //tA->TopStudy("TTbar",3000);
  //tA->TauContamination(-1, 1000000000, 27);
//  tA->vs();
  //tA->Efficiency("SMS");
  //tA->MySmallMakePlot(1000000000);
  //tA->makeSmallCopy(100000000,100);
  //tA->QCD();
 //  tA->vs1();
 // tA->MT2forVSPT();

}
