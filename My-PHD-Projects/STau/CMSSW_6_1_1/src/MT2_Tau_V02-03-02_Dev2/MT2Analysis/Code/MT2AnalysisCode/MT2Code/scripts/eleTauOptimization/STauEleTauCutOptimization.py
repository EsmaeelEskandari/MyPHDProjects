#!/usr/bin/env python
# Standard python import
import os
import sys    # exit
import time   # time accounting
from optparse import OptionParser

import itertools #combinatiories
import math
from array import array
import xml.etree.ElementTree as etree 

# Import ROOT classes
from ROOT import gSystem, gROOT, gApplication, TFile, TTree, TCut, gDirectory , TH1F , TFormula, std, TGraphAsymmErrors

# Import TMVA classes from ROOT
from ROOT import TMVA

os.environ['DISPLAY'] = '0'
os.environ['TMVASYS'] = os.environ['ROOTSYS']

# Default settings for command line arguments
DEFAULT_INFNAME  = "/dataLOCAL/hbakhshi/MT2_80_ReOptimize_TreeZPeakVeto.root"
DEFAULT_TREENAME = "ZPeakVeto"


#VARIABLES = {"ElePt":['F'] , "EleMT":['F'] ,  "MT2":['F'] , "MCT":['F'] , "MT2Imb":['F'] ,"TauPt":['F'] , "DPt":['F'] , "MET":['F'] ,"EleTauPt":['F'] ,"JPTModMZPTMod":['F'] , 'METModPPZMod':['F'] , 'METModMPZMod':['F'] , 'ModMETmPZ':['F'] }
#VARIABLES = {"EleMTpTauMT":['F'] ,  "MT2":['F'] , 'METModPPZMod':['F'] , 'METModMPZMod':['F']  }
#VARIABLES = {'METModPPZMod':['F'] , 'METModMPZMod':['F'] , "abs(DPhiJPtZPt)":['F'] ,"EleTauDPhi":['F'] , "EleTauDR":['F'] , 'EleMTpTauMT':['F'] , 'MT2':['F'] }
VARIABLES = {'EleMTpTauMT':['F'] , 'MT2':['F']}

Category1 = [ ] # 'EleTauPt' , 'METModPPZMod' , 'METModMPZMod' , 'MET' ]
Category2 = [ ] # 'MCT' , 'MT2' , 'MT2Imb' ]


# SUSYCats = {"50-100":"SUSYCategory >= 1  && SUSYCategory < 2" ,  "100-150":"SUSYCategory >= 2  && SUSYCategory < 3" , 
#             "150-200":"SUSYCategory >= 3  && SUSYCategory < 4" , "200-250":"SUSYCategory >= 4  && SUSYCategory < 5" , 
#             "250-300":"SUSYCategory >= 5  && SUSYCategory < 6" , "300-350":"SUSYCategory >= 6  && SUSYCategory < 7" , 
#             "350-400":"SUSYCategory >= 7  && SUSYCategory < 8" , "400-450":"SUSYCategory >= 8  && SUSYCategory < 9" , 
#             "450-500":"SUSYCategory >= 9  && SUSYCategory < 10" }

SUSYCats = {"000-100":"(MassGlu-MassLSP) >= 175 && (MassGlu-MassLSP) < 225",
            "100-200":"(MassGlu-MassLSP) >= 100 && (MassGlu-MassLSP) < 200",
            "200-300":"(MassGlu-MassLSP) >= 200 && (MassGlu-MassLSP) < 300",
            "300-400":"(MassGlu-MassLSP) >= 300 && (MassGlu-MassLSP) < 400",
            "400-500":"(MassGlu-MassLSP) >= 400 && (MassGlu-MassLSP) < 500"}


class MethodInfo :

    def __init__(self , titDir , name , title , nsignal , nbkg ):
          self.methodName = name
          self.methodTitle = title

          hname = "MVA_" + self.methodTitle

          self.sig = titDir.Get( hname + "_S" )
          self.bgd = titDir.Get( hname + "_B" )
          self.origSigE = titDir.Get( hname + "_effS" )
          self.origBgdE = titDir.Get( hname + "_effB" )
          self.sigE = None
          self.bgdE = None
          self.purS = None
          self.sSig = None
          self.effpurS = None
          self.maxSignificance = 0.0
          self.maxSignificanceErr = 0.0

          self.maxbin = -1
          self.fNSignal = nsignal
          self.fNBackground = nbkg

          self.SetResultHists()
          self.UpdateSignificanceHists('S/sqrt(B+S)')
          #self.UpdateSignificanceHists('S/B')
          
    def SetResultHists(self):
  
        pname    = "purS_"         + self.methodTitle;
        epname   = "effpurS_"      + self.methodTitle;
        ssigname = "significance_" + self.methodTitle;

        self.sigE = self.origSigE.Clone("sigEffi");
        self.bgdE = self.origBgdE.Clone("bgdEffi");
      
        nbins = self.sigE.GetNbinsX();
        low = self.sigE.GetBinLowEdge(1);
        high = self.sigE.GetBinLowEdge(nbins+1);
        self.purS = TH1F(pname, pname, nbins, low, high);
        self.sSig  = TH1F(ssigname, ssigname, nbins, low, high);
        self.effpurS = TH1F(epname, epname, nbins, low, high);        

        
        self.sigE.SetFillStyle( 0 );
        self.bgdE.SetFillStyle( 0 );
        self.sSig.SetFillStyle( 0 );
        self.sigE.SetLineWidth( 3 );
        self.bgdE.SetLineWidth( 3 );
        self.sSig.SetLineWidth( 3 );

        self.purS.SetFillStyle( 0 );
        self.purS.SetLineWidth( 2 );
        self.purS.SetLineStyle( 5 );
        self.effpurS.SetFillStyle( 0 );
        self.effpurS.SetLineWidth( 2 );
        self.effpurS.SetLineStyle( 6 );
  
    def UpdateSignificanceHists(self, significance_formula , doprint = False):
        f = TFormula("sigf", significance_formula.replace("S", "x").replace("B", 'y') )
        cname = "Classifier"
        maxLenTitle = len(cname)

        maxSig    = -1.;
        maxSigErr = -1.;
        for i in range( 1 , self.origSigE.GetNbinsX()+1 )  :
            eS = self.origSigE.GetBinContent( i )
            S = eS * self.fNSignal
            B = self.origBgdE.GetBinContent( i ) * self.fNBackground
            purity = 0.0
            if not S+B ==0 :
                purity = S/(S+B)
            self.purS.SetBinContent( i, purity)
         
            sig = f.Eval(S,B);
            if sig > maxSig :
                maxSig = sig;
                if significance_formula == "S/sqrt(B)" and not B == 0 and not S == 0:
                    maxSigErr = sig * math.sqrt( 1./S + 1./(2.*B))
                                
            self.sSig.SetBinContent( i, sig )
            self.effpurS.SetBinContent( i, eS*self.purS.GetBinContent( i ) )
    
      
        self.maxSignificance    = self.sSig.GetMaximum()
        self.maxbin = self.sSig.GetMaximumBin();
        self.maxSignificanceErr = maxSigErr if maxSigErr > 0 else 0
        self.sSig.Scale(1/self.maxSignificance);
        self.optimalcut = self.sSig.GetXaxis().GetBinCenter( self.maxbin )
        self.NSig = self.origSigE.GetBinContent( self.maxbin )*self.fNSignal
        self.NBkg = self.origBgdE.GetBinContent( self.maxbin )*self.fNBackground
        self.EffSig = self.origSigE.GetBinContent( self.maxbin ) 
        self.EffBkg = self.origBgdE.GetBinContent( self.maxbin )
        
        if doprint:
            str = "%(name)s   (  #signal, #backgr.)  Optimal-cut  %(sig_formula)s      NSig      NBkg   EffSig   EffBkg" % {'name':cname , 'sig_formula':significance_formula }
            print str

            str = "%(name)s   (  %(signal)d, %(bkg)d )  %(optimalcut)f  %(sig)f+- %(sigerr)f      %(NSig)f       %(NBkg)f   %(EffSig)f   %(EffBkg)f" % {'name':self.methodName , 'signal':self.fNSignal , 'bkg':self.fNBackground , 'optimalcut':self.optimalcut , 'sig':self.maxSignificance , 'sigerr':self.maxSignificanceErr , 'NSig':self.NSig , 'NBkg':self.NBkg , 'EffSig':self.EffSig , 'EffBkg':self.EffBkg }
            print str

    def ReadCuts( self, xmlfilename):
        tree = etree.parse(xmlfilename)
        root = tree.getroot()
        variables = []
        self.Variables = {}
        vars = root.find( 'Variables' )
        for var in vars:
            varname = var.attrib[ 'Title' ]
            variables.append( varname )
        weights = root.find( "Weights")
        for bins in weights:
            effs = float(bins.attrib['effS'])
            if round(self.EffSig,2) == round( effs , 2) :
                cuts = bins[0].attrib
                i = 0
                for varname in variables:
                    self.Variables[ varname ] = []
                    self.Variables[ varname ].append( round( float( cuts[ 'cutMin_%d' % (i) ] ) , 2 ) )
                    self.Variables[ varname ].append( round( float( cuts[ 'cutMax_%d' % (i) ] ) , 2 ) )
                    i+=1

    def Print( self ):
        ret = []
        ret.append( '%.2f' % ( 100* self.EffSig ) )
        ret.append( '%.2f' % ( 100* self.EffBkg ) )
        ret.append( '%.2f' % ( self.NSig ) )
        ret.append( '%.2f' % ( self.NBkg ) )
        ret.append( '%.2f' % ( self.maxSignificance ) )
        ret.append( '%.2f' % ( self.maxSignificanceErr ) )
        for var in self.Variables:
            lowercut = self.Variables[var][0]
            uppercut = self.Variables[var][1]
            if lowercut < -10000000:
                ret.append( '%(var)s < %(val).2f' % {'var':var , 'val':uppercut} )
            elif uppercut > 10000000:
                ret.append( '%(val).2f < %(var)s' % {'var':var , 'val':lowercut} )
            else:
                ret.append( '%(val).2f < %(var)s < %(val2).2f' % {'var':var , 'val':lowercut , 'val2':uppercut} )

        return ','.join( [str(item) for item in ret] )

if __name__ == "__main__":

    PDFCTEQ66 = {100:[5823.40, 0.0 , +3.4 , -.6 , -3.2],
                 125:[2434.10, 0.0, 3.6 , -.6 , -3.5 ],
                 150:[1194.60, 0.3, +3.9 , -.5 , -3.8],
                 175:[649.58, 0.3 , 4.2, -.5 , -4. ] ,
                 200:[379.24, 0.4, 4.5 , -.4 , -4.4] ,
                 225:[233.41 , 0.5, 5.0 , -.3 , -4.4],
                 250:[149.86 , 0.3 ,5.1 , -.4 , -4.8],
                 275:[99.27, 0.1 , 5.5 , -.4 , -5. ],
                 300:[67.51 , 0.0 , 5.9 , -.2 , -5.1],
                 325:[46.97 , 0.1 , 6.1 , -.2 , -5.5],
                 350:[33.28 , 0.0 , 6.4 , -.2 , -5.6],
                 375:[23.95 , 0.0 , 7.0 , -.1 , -5.7],
                 400:[17.51 , 0.0 , 6.8 , -.3 , -6.3],
                 425:[12.93 , 0.0 , 7.5 , -.3 , -6.1],
                 450:[9.66, 0.0 , 7.5 , -.5 , -6.7],
                 475:[7.28 , 0.1 , 7.8, -1 , -6.8],
                 500:[5.53 , 0.0 , 8.1 , -.9 , -7.0]
                 }
    
    gXSections = TGraphAsymmErrors( len(PDFCTEQ66) )
    step = 25
    cc = 0
    for mass in range(100 , 500 , step):
        gXSections.SetPoint( cc , mass , PDFCTEQ66[mass][0] )
        
        errh = math.hypot( PDFCTEQ66[mass][1] , PDFCTEQ66[mass][2] )
        errl = math.hypot( PDFCTEQ66[mass][3] , PDFCTEQ66[mass][4] )
        
        gXSections.SetPointError( cc , errl , errh , step/2. , step/2. )
            
        cc += 1

    infname     = DEFAULT_INFNAME
    treeName    = DEFAULT_TREENAME
    verbose     = False

    parser = OptionParser()
    parser.add_option("-n", "--ncombs", dest="ncombs" , type='int' , default=-1)    
    parser.add_option("-s", "--signal", dest="signal" , type='int')
    parser.add_option("-d", "--dir", dest="dir" , default='.' )
    (options, args) = parser.parse_args() 

    # Logon not automatically loaded through PyROOT (logon loads TMVA library) load also GUI
    gROOT.Macro       ( "TMVAlogon.C" )    
    gROOT.LoadMacro   ( "TMVAGui.C" )

    input = TFile.Open( infname )
    TheTree = input.Get( treeName )

    catIndex = -1
    for (SUSCatName,SUSCatCut) in SUSYCats.iteritems():
        print SUSCatName + " : "
        catIndex += 1
        if catIndex == options.signal:
            print "ok"
        else:
            print "skipped"
            continue

        SUSYSignalCut = TCut( SUSCatCut )
        BKGCut = TCut( "SUSYCategory < 0 && SUSYCategory > -10" )

        selection_cut = ' 1==1  ' #MT2 > 30 && EleMTpTauMT > 300'

        signal_selection_tcut = TCut( selection_cut + ' && ' + SUSCatCut )
        bkg_selection_tcut = TCut( selection_cut + ' && ' + "SUSYCategory < 0 && SUSYCategory > -10" )
        WWW = TCut("W")

        
        TheTree.Draw( "1>>hcounts" ,  (signal_selection_tcut)*WWW   )
        hcounts = ( gDirectory.Get("hcounts") )
        nSig = hcounts.Integral()

        fTotalNumbers = TFile('/home/hbakhshi/work/STau/CMSSW_6_1_1/src/HiggsAnalysis/all_Histos.root')
        hNEvents = fTotalNumbers.Get('h_SMSEvents')

        SusyRangeFormula = TFormula("susyformula" , SUSCatCut.replace( 'MassGlu' , 'x' ).replace('MassLSP', 'y' ) )
        nTotalSignal = 0

        mglu_avg = 0.0
        nmlsp_zero = 0
        
        for mglu_i in range( 1 , hNEvents.GetNbinsY()+1 ):
            for mlsp_i in range( 1 , hNEvents.GetNbinsX()+1 ):
                mlsp = hNEvents.GetYaxis().GetBinCenter(mlsp_i)
                mglu = hNEvents.GetXaxis().GetBinCenter(mglu_i)
                if( SusyRangeFormula.Eval( mglu , mlsp ) == 1 ):
                    if mlsp_i == 1 :
                        mglu_avg += mglu
                        nmlsp_zero += 1
                    #print mglu
                    #print mlsp
                    nTotalSignal += hNEvents.GetBinContent( mglu_i, mlsp_i)
                    #print nTotalSignal


        mglu_avg /= nmlsp_zero
        print mglu_avg
        xSection = gXSections.Eval( mglu_avg )
        print xSection

        Lumi = 19.6

        nSignal = xSection*Lumi*nSig / nTotalSignal
        print nSignal
        
        TheTree.Draw( "1>>hcountsB" ,  (bkg_selection_tcut)*WWW ) 
        hcountsB = ( gDirectory.Get("hcountsB") )
        nBKG = hcountsB.Integral()

        print nBKG
        
        for COMB_L in range(2,3):
            if options.ncombs > -1:
                if not COMB_L == options.ncombs:
                    continue
                
            outtxtfile = open( 'csvfiles/%s_%d.csv' % (SUSCatName, COMB_L) , 'w' )

            ALLComs = itertools.combinations( VARIABLES , COMB_L )
            print str(COMB_L) + ":"

            ccc = 0
            for comb in ALLComs:
                ccc +=1
                Name = "TMVA_" + SUSCatName
                for cut in comb:
                    Name += "_" + cut

                print "Combination #%d : %s " % (ccc , Name)

                nCategory1 = 0
                nCategory2 = 0
                for cut in comb:
                    if cut in Category1:
                        nCategory1 += 1
                    if cut in Category2:
                        nCategory2 += 1
                if (nCategory1 > 2) or (nCategory2 > 2):
                    print "two members from the same category, skipped"
                    continue

                outfname = options.dir + "/" + Name + ".root"
                outputFile = TFile( outfname, 'RECREATE' )

                factory = TMVA.Factory( Name, outputFile, 
                                        "!V:Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" )

                # Set verbosity
                factory.SetVerbose( verbose )

                #it crashes when these variables are being studied
                forbidden_vars = [ ] #'METModPPZMod' , 'JPTModMZPTMod' , 'MET' , 'METModMPZMod' ]
                forbidden_vars2 = [ ] #'EleTauPt' , 'MET' , 'METModMPZMod' ]
                n_forbidden_vars = 0
                n_forbidden_vars2 = 0

                for var in VARIABLES:
                    if var in comb:
                        if not selection_cut == '':
                            selection_cut += " && "
                        factory.AddVariable( var, VARIABLES[ var ][0] )
                        selection_cut += var + " > -1000000"
                        if var in forbidden_vars:
                            n_forbidden_vars += 1
                        if var in forbidden_vars2:
                            n_forbidden_vars2 += 1
                    else:
                        factory.AddSpectator( var )


                if n_forbidden_vars > 2 or n_forbidden_vars2 == 3:
                    continue

                factory.SetInputTrees( TheTree , SUSYSignalCut  , BKGCut  )
                factory.SetSignalWeightExpression("W")
                factory.SetBackgroundWeightExpression("W")

                mycutSig = TCut( selection_cut ) 
                mycutBkg = TCut( selection_cut )
                try:
                    err = ['err']*4
                    err += selection_cut.split("&&")
                    print ','.join( err )
                    factory.PrepareTrainingAndTestTree( mycutSig, mycutBkg,
                                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" )
                except:
                    err = ['err']*4
                    err += selection_cut.split("&&")
                    print >> outtxtfile, ','.join( err )
                    continue


                #factory.BookMethod( TMVA.Types.kCuts, "Cuts",
                #                   "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" )

                factory.BookMethod( TMVA.Types.kLD , "LD" , "!V" )                   
                # Train MVAs
                factory.TrainAllMethods()

                # Test MVAs
                factory.TestAllMethods()

                # Evaluate MVAs
                factory.EvaluateAllMethods()    

                # Save the output.
                outputFile.Close()

                #fin = TFile( outfname , 'read') 
                #fin.cd('Method_Cuts/Cuts/')
                #mInfo = MethodInfo( gDirectory , "Cuts" , "Cuts" , nSignal , nBKG )
                #mInfo.ReadCuts('weights/' + Name + '_Cuts.weights.xml')
                #print >> outtxtfile, mInfo.Print()
                #fin.Close()
            outtxtfile.close()
    input.Close()
