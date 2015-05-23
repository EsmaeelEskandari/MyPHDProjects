#include <iostream>
#include <string>
#include <vector>
#include "TH1F.h"
#include "TFile.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLatex.h" 
#include "TLine.h"
#include "TColor.h"

bool fSave = false;
void plotRatioStack(THStack* hstack, TH1* h1_orig, TH1* h2_orig, bool logflag, bool normalize, TString name, TLegend* leg, TString xtitle, TString ytitle,int njets, int nleps){
  // define canvas and pads 
  TH1D *h1 = (TH1D*)h1_orig->Clone("h1_copy");
  TH1D *h2 = (TH1D*)h2_orig->Clone("h2_copy");

  h1->SetStats(0);	
  h2->SetStats(0);	
	
  TCanvas* c1 = new TCanvas(name,"", 20,100,1000,700);
  cout << name << endl;
  c1 -> cd();
	
  float border = 0.3;
  float scale = (1-border)/border;
 
  TPad *p_plot  = new TPad(name+"_plotpad",  "Pad containing the overlay plot", 0.00, border, 1.00, 1.00, 0, 0);
  p_plot->SetBottomMargin(0);
  p_plot->Draw();
  TPad *p_ratio = new TPad(name+"_ratiopad", "Pad containing the ratio",        0.00, 0.00, 1.00, border, 0, 0);
  p_ratio->SetTopMargin(0);
  p_ratio->SetBottomMargin(0.35);
  p_ratio->Draw();
 
  // draw overlay plot
  p_plot ->cd();

  if(logflag) gPad->SetLogy(1);
  gPad->SetFillStyle(0);
		
  // Scaling
  if(normalize){
    h1->Scale(1.0/h1->Integral());
    h2->Scale(1.0/h2->Integral());
  }
	
  // Determine plotting range
  double max1 = h1->GetMaximum();
  double max2 = h2->GetMaximum();
  double max  = (max1>max2)?max1:max2;
  if(logflag) max = 2*max;
  else max = 1.05*max;
  h1->SetMaximum(max);
  h2->SetMaximum(max);
  hstack->SetMaximum(max);
  //	h1->SetMinimum(0.000000001);
  //	h2->SetMinimum(0.000000001);

  hstack->SetMinimum(0.02);
  hstack ->Draw("hist");
  //h2     ->Draw("sameEX0");
  h2     ->Draw("sameE1"); //LEO MOD

  // title
  TLatex lat;
  lat.SetNDC(1);
  lat.SetTextColor(4);
  lat.SetTextSize(0.1);

  // y axis title 
  lat.SetTextAlign(33); 
  lat.SetTextColor(1);
  lat.SetTextAngle(90);
  lat.DrawLatex(0.035, 0.9, ytitle);
		
  TLatex TitleBox;
  TitleBox.SetNDC();
  TitleBox.SetTextSize(0.05);
  TString text = "" ;
  if( njets < 0 ) 
    text = TString::Format("#geq %d Jets",abs(njets)) ;
  else
    text = TString::Format("%d Jets",abs(njets)) ) ;
  text += nleps == 1 ? ", 1 Lepton" : "";
  TitleBox.DrawLatex(0.18,0.943,text.Data());

  p_plot ->Draw();
  gPad->RedrawAxis();

  if(leg != NULL ){
    leg -> SetFillColor(0);
    leg -> SetBorderSize(0);
    leg -> Draw();
  } 
	
  // draw the ratio plot
  p_ratio ->cd();
  //gPad->SetLogy();
 
  TH1D *h_ratio = (TH1D*)h2_orig->Clone("h2_copy");	

  h_ratio->GetXaxis()->SetTitleSize(scale * h1->GetXaxis()->GetTitleSize());
  h_ratio->GetYaxis()->SetTitleSize(scale * h1->GetYaxis()->GetTitleSize());
  h_ratio->GetXaxis()->SetLabelSize(scale * h1->GetXaxis()->GetLabelSize());
  h_ratio->GetYaxis()->SetLabelSize(scale * h1->GetYaxis()->GetLabelSize());
  h_ratio->GetXaxis()->SetTickLength(scale * h1->GetXaxis()->GetTickLength());
  h_ratio->GetYaxis()->SetTickLength(h1->GetYaxis()->GetTickLength());
  h_ratio->SetLineWidth(2);
  //h_ratio->SetFillColor(kBlue);//leo
  //h_ratio->SetLineColor(kBlue);
  h_ratio ->SetStats(0);
  h_ratio ->SetMarkerStyle(20);
  //h_ratio ->SetMarkerSize(0.1);

  h_ratio ->Divide(h2, h1);
  h_ratio ->SetMinimum(0.4);
  h_ratio ->SetMaximum(3.0);
  h_ratio ->GetYaxis()->SetTitleOffset(h1->GetYaxis()->GetTitleOffset());

  h_ratio ->DrawCopy("E"/*2"*/);
 
  TLine *l3 = new TLine(h1->GetXaxis()->GetXmin(), 1.00, h1->GetXaxis()->GetXmax(), 1.00);
  l3->SetLineWidth(2);
  l3->SetLineStyle(7);
  l3->Draw();
  // ratio title
  lat.SetTextAlign(33);
  lat.SetTextColor(1);
  lat.SetTextSize(0.15);
  lat.SetNDC(1);
  lat.SetTextAngle(90);
  lat.DrawLatex(0.035, 1.0, "data / MC");
	
  // x axis title
  lat.SetTextSize(0.2);
  lat.SetTextAngle(0);
  float ypos = xtitle.Contains("slash") || xtitle.Contains("_") || xtitle.Contains("^") ? 0.23 : 0.16;
  lat.DrawLatex(0.9, ypos, xtitle);
  gPad->RedrawAxis();
  p_ratio ->Draw();
  c1->Update();

  //TString save=name+"_ratio";
  //if(fSave) Util::Print(c1, save, fOutputDir, fOutputFile);	

  // 	delete h1;
  // 	delete h2;
  // 	delete h_ratio;
  // 	delete p_plot;
  // 	delete p_ratio;
  // 	delete c1;

}
void ZInvPlotter1(){
}


void ZInvPlotter1( string variable_name , string cut_name , bool file0b  ) {

  TFile* theFile;
  if(file0b)
    theFile = TFile::Open("histos_ZInv-MT2_-1_9999-Jet40-HT_700-1Mu_pt10_4450pb_0b.root");
  else
    theFile = TFile::Open("histos_ZInv-MT2_-1_9999-Jet40-HT_700-1Mu_pt10_4450pb_1b.root");

  // list of input samples
  std::vector<string> samples_;
  std::vector<int> sample_colors;

  samples_.push_back("WtolnuMu");
  sample_colors.push_back( 419 );

  samples_.push_back("WtolnuTau");
  sample_colors.push_back( 417 );

  samples_.push_back("Top");
  sample_colors.push_back( 855 );

  samples_.push_back("QCD");
  sample_colors.push_back( 401 );

  samples_.push_back("Other");
  sample_colors.push_back( 603 );

//	TString  cnames[7] = {"QCD", "W+jets", "Z+jets", "Top", "Other", "susy", "data"};
//	int      ccolor[7] = { 401,   417,       419,      855,    603,     0,     632};

  std::vector<TH1F*> hists;
  THStack* stack = new THStack("all_mc" , "");
  TH1* all_mc= 0 ;
  for(unsigned int i=0; i<samples_.size(); ++i){

    string histo_name = variable_name+"_"+samples_[i]+"_"+ cut_name     ;
    cout << histo_name << endl;
    TH1F* h = (TH1F*) theFile->Get( histo_name.c_str() );
    theFile->Print("ALL");
    h->SetFillColor( sample_colors[i] );

    hists.push_back( h );
    stack->Add( h );
    
    if( all_mc == 0)
      all_mc =(TH1F*) h->Clone("all_mc_h");
    else
      all_mc->Add( h );
  }
  
  string histo_name = variable_name+"_"+ "data" + "_"+cut_name ;
  TH1* hData = (TH1F*) theFile->Get( histo_name.c_str() );

TLegend* leg = new TLegend(0.35,0.6,0.85,0.90);
  leg->SetFillStyle ( 0);
  leg->SetFillColor ( 0);
  leg->SetBorderSize( 0);
  leg->AddEntry( hData, "CMS Data 2012 Run_A+B(5.1/fb)"               , "PL");
  leg->AddEntry( hists[0], "WtolnuMu"                           , "F");
  leg->AddEntry( hists[1], "WtolnuTau"                           , "F");
  leg->AddEntry( hists[2], "Top"                           , "F");
  leg->AddEntry( hists[3], "QCD"              , "F");
  leg->AddEntry( hists[4], "Other"               , "F");

  
  leg->Draw("same");

  //plotRatioStack(THStack* hstack, TH1* h1_orig, TH1* h2_orig, bool logflag, bool normalize, TString name, TLegend* leg, TString xtitle, TString ytitle,int njets, int nleps);

  //set style first
  plotRatioStack( stack ,         all_mc ,     hData ,       false ,     false ,          TString(variable_name) , leg ,      TString("") , TString("#Events") ,     2 ,  1);     


}
