{
//========= Macro generated from object: all/
//========= by ROOT version5.34/03
   Double_t xAxis1[4] = {40, 55, 70, 90}; 
   
   TH1D *all = new TH1D("all","",3, xAxis1);
   all->SetBinContent(1,1.74932);
   all->SetBinContent(2,0.318457);
   all->SetBinContent(3,0.352665);
   all->SetBinError(1,0.86726);
   all->SetBinError(2,0.34309);
   all->SetBinError(3,0.328821);
   all->SetEntries(5.99048);
   
   TPaveStats *ptstats = new TPaveStats(0.459809,0.618935,0.959809,0.898225,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(0);
   ptstats->SetFillColor(0);
   ptstats->SetLineWidth(2);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("all");
   text->SetTextSize(0.0642367);
   text = ptstats->AddText("Entries = 6      ");
   text = ptstats->AddText("Mean  =  54.21");
   text = ptstats->AddText("RMS   =  11.77");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(73);
   ptstats->Draw();
   all->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(all);
   all->SetLineColor(0);
   all->SetLineWidth(2);
   all->GetXaxis()->SetNdivisions(505);
   all->GetXaxis()->SetLabelFont(42);
   all->GetXaxis()->SetLabelSize(0.07);
   all->GetXaxis()->SetTitleSize(0.07);
   all->GetXaxis()->SetTitleOffset(1.1);
   all->GetXaxis()->SetTitleFont(42);
   all->GetYaxis()->SetNdivisions(505);
   all->GetYaxis()->SetLabelFont(42);
   all->GetYaxis()->SetLabelSize(0.07);
   all->GetYaxis()->SetTitleSize(0.07);
   all->GetYaxis()->SetTitleOffset(1.3);
   all->GetYaxis()->SetTitleFont(42);
   all->GetZaxis()->SetLabelFont(42);
   all->GetZaxis()->SetLabelSize(0.035);
   all->GetZaxis()->SetTitleSize(0.035);
   all->GetZaxis()->SetTitleFont(42);
   all->Draw("");
}
