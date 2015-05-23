void set_plot_style01() {
    const Int_t NRGBs = 5, NCont = 999;
    gStyle->SetNumberContours(NCont);

    Double_t RGB[5][3] = {
        {0.00, 0.00, 0.51},
        {0.00, 0.81, 1.00},
        {0.87, 1.00, 0.12},
        {1.00, 0.20, 0.00},
        {0.51, 0.00, 0.00}
    };

    Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
    Double_t red[NRGBs] = {RGB[0][0], RGB[1][0], RGB[2][0], RGB[3][0], RGB[4][0]};
    Double_t green[NRGBs] = {RGB[0][1], RGB[1][1], RGB[2][1], RGB[3][1], RGB[4][1]};
    Double_t blue[NRGBs] = {RGB[0][2], RGB[1][2], RGB[2][2], RGB[3][2], RGB[4][2]};
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
}



void set_plot_style() {
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
    Double_t red[NRGBs] = {0.00, 0.00, 0.87, 1.00, 0.51};
    Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
    Double_t blue[NRGBs] = {0.51, 1.00, 0.12, 0.00, 0.00};
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}

void rootlogon() {
    
    gSystem->SetIncludePath(" -I../../../MT2Code/include/ -I../../../TESCO/include/");
    gSystem->Load("/public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw/CMSSW_5_2_5/lib/slc5_amd64_gcc462/libFWCoreFWLite.so");
    gSystem->Load("/public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw/CMSSW_5_2_5/lib/slc5_amd64_gcc462/libFWCoreUtilities.so");
    gSystem->Load("/public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw/CMSSW_5_2_5/lib/slc5_amd64_gcc462/libDataFormatsCommon.so");
    gSystem->Load("/public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw/CMSSW_5_2_5/lib/slc5_amd64_gcc462/libDataFormatsFWLite.so");

    gSystem->Load("libPhysics");
    gSystem->Load("../../../MT2Code/shlib/libDiLeptonAnalysis.so");
    gROOT->ProcessLine(".x SetStyle_PRD.C");
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    gStyle->SetPaintTextFormat("5.4g");

    set_plot_style01();
    //    	TBrowser* b = new TBrowser();


}




