{
    //TString outputdir = "/17TB/MT2Top/MassPlots/";
    TString outputdir = "../MassPlotssmall/";
    TString samples = "./samples/samplesMineSmearedJetsNewBTag.dat";
    int verbose = 3;

    gSystem->CompileMacro("../MT2Code/src/MassPlotter.cc", "kf"); //"k", "f"
    gROOT->ProcessLine(".x SetStyle_PRD.C");

    int gNMT2bins = 17;
    double gMT2bins[gNMT2bins + 1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 300, 400, 550, 800};

    int gNMT2Bbins = 15;
    double gMT2Bbins[gNMT2bins + 1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 300, 500};

    int gNMT2bins_l = 14;
    double gMT2bins_l[gNMT2bins + 1] = {0, 10, 20, 30, 40, 50, 65, 80, 95, 115, 140, 180, 250, 350, 500};

    MassPlotter *tA = new MassPlotter(outputdir, "MassPlots.root");
    tA->SetSave(false);
    tA->setVerbose(verbose);
    tA->init(samples);
    tA->SetIsPhoton(false);

    std::ostringstream cutStream;
    cutStream << " "
            << "(misc.ProcessID!=10 || (Susy.MassGlu >= 350 && Susy.MassGlu < 355" << "&&"
            << "Susy.MassLSP >= 50 && Susy.MassLSP < 55))" << "&&"
            //<< "misc.MT2>125" << "&&"
            << "NBJetsCSVT> 0" << "&&"
            << "misc.MET>30" << "&&"
            << "NJetsIDLoose40  >=4" << "&&"
            << "(NEles==0  || ele[0].lv.Pt()<5)" << "&&"
            << "(NMuons==0 || muo[0].lv.Pt()<5)" << "&&"
            << "misc.Jet0Pass ==1" << "&&"
            << "misc.Jet1Pass ==1" << "&&"
            << "misc.PassJetID ==1" << "&&"
            << "misc.Vectorsumpt < 70" << "&&"
            << "misc.MinMetJetDPhi4 >0.3" << "&&"
            << "(((NJetsIDLoose40  >=4 && jet[3].lv.Pt() >= 100.0) || (NJetsIDLoose40  >=6 && jet[5].lv.Pt() >= 65.0))" << "||"
            << "((NJetsIDLoose40  >=5 && jet[4].lv.Pt() >= 85.0) || (NJetsIDLoose40  >=7 && jet[6].lv.Pt() >= 55.0)))";

    std::ostringstream triggerStream;
    triggerStream << "( "
            << " misc.ProcessID != 0 || ((misc.CrazyHCAL==0 && misc.NegativeJEC==0 " << "&&"
            << " misc.CSCTightHaloIDFlag==0 && misc.HBHENoiseFlag==0 " << "&&"
            << " misc.hcalLaserEventFlag==0 && misc.trackingFailureFlag==0 " << "&&"
            << " misc.eeBadScFlag==0 && misc.EcalDeadCellTriggerPrimitiveFlag==0 )" << "&&("

            << "(((trigger.HLT_QuadJet80_v1 ==1)" << "||"
            << "(trigger.HLT_QuadJet80_v2 ==1)" << "||"
            << "(trigger.HLT_QuadJet80_v3 ==1)" << "||"
            << "(trigger.HLT_QuadJet80_v4 ==1)" << "||"
            << "(trigger.HLT_QuadJet80_v6 ==1)" << ") &&"

            << " ((NJetsIDLoose40  >=4 " << "&&"
            << " jet[3].lv.Pt() >= 100.0 " << ") || "
            << " (NJetsIDLoose40  >=5 " << "&&"
            << " jet[4].lv.Pt() >= 85.0 " << "))) || "

            << "(((trigger.HLT_SixJet45_v1 ==1)" << "||"
            << "(trigger.HLT_SixJet45_v2 ==1)" << "||"
            << "(trigger.HLT_SixJet45_v3 ==1)" << "||"
            << "(trigger.HLT_SixJet45_v4 ==1)" << "||"
            << "(trigger.HLT_SixJet45_v6 ==1)" << ") &&"

            << " ((NJetsIDLoose40  >=6 " << "&&"
            << " jet[5].lv.Pt() >= 65.0 " << ") ||"

            << " (NJetsIDLoose40  >=7 " << "&&"
            << " jet[6].lv.Pt() >= 55.0 " << "))))))";

    TString trigger = triggerStream.str().c_str();
    TString cuts = cutStream.str().c_str();

    tA->makePlot("NTops", cuts, -1, -1, -10, trigger, "MT2", 2, 0, 4, false, true, true, true, true, true, 1, 1);

}
