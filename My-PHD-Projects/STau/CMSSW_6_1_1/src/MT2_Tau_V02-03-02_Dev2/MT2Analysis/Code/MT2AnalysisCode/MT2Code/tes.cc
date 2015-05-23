      double px_all_up = 0;
      double py_all_up = 0;
      double pz_all_up = 0;
      double E_all_up  = 0;

   for(int l=0; l <fMT2tree->NTaus; l++)
     {
       px_all_up += 0.03*fMT2tree->tau[l].lv.Px();
       py_all_up += 0.03*fMT2tree->tau[l].lv.Py();
       pz_all_up += 0.03*fMT2tree->tau[l].lv.Pz();
       E_all_up  += 0.03*fMT2tree->tau[l].lv.E();
     }

   TLorentzVector tau_delta_up    (px_all_up ,  py_all_up,  pz_all_up,  E_all_up);
   TLorentzVector tau_delta_down  (-px_all_up, -py_all_up, -pz_all_up, -E_all_up);


   TLorentzVector MET_up   = fMT2tree->pfmet[0] - tau_delta_up;
   TLorentzVector MET_down = fMT2tree->pfmet[0] - tau_delta_down;


   TLorentzVector tau0_ditau_up (1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.Px(),
                                 1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.Py(),
                                 1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.Pz(),
                                 1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.E());

   TLorentzVector tau0_ditau_down (0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.Px(),
                                   0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.Py(),
                                   0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.Pz(),
                                   0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex0()].lv.E());

   TLorentzVector tau1_ditau_up (1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.Px(),
                                 1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.Py(),
                                 1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.Pz(),
                                 1.03 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.E());

   TLorentzVector tau1_ditau_down (0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.Px(),
                                   0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.Py(),
                                   0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.Pz(),
                                   0.97 * fMT2tree->tau[fMT2tree->doubleTau[0].GetTauIndex1()].lv.E());

   double tau0_MT_ditau_up = fMT2tree->GetMT( tau0_ditau_up , 0., MET_up , 0.); 
   double tau1_MT_ditau_up = fMT2tree->GetMT( tau1_ditau_up , 0., MET_up , 0.);                  

   double tau0_MT_ditau_down = fMT2tree->GetMT( tau0_ditau_down , 0., MET_down , 0.);
   double tau1_MT_ditau_down = fMT2tree->GetMT( tau1_ditau_down , 0., MET_down , 0.);                      
            
   double maxMT_up   = max(tau0_MT_ditau_up   , tau1_MT_ditau_up);
   double maxMT_down = max(tau0_MT_ditau_down , tau1_MT_ditau_down);

   double sumMT_up   = tau0_MT_ditau_up   + tau1_MT_ditau_up;
   double sumMT_down = tau0_MT_ditau_down + tau1_MT_ditau_down;

   double mt2_ditau_up   = fMT2tree->CalcMT2(0, false, tau0_ditau_up, tau1_ditau_up, MET_up);
   double mt2_ditau_down = fMT2tree->CalcMT2(0, false, tau0_ditau_down, tau1_ditau_down, MET_down);
   double invMass_ditau_up    = (tau0_ditau_up + tau1_ditau_up).M();
   double invMass_ditau_down  = (tau0_ditau_down + tau1_ditau_down).M();

   double  MinMetJetDPhi_up   = fMT2tree->MinMetJetDPhi(0,40,5.0,100); 
   double  MinMetJetDPhi_down = fMT2tree->MinMetJetDPhi(0,40,5.0,-100);  

