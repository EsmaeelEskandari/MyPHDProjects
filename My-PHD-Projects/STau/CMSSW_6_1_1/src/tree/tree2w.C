const Int_t MAXMEC = 30;
// PARAMETER (MAXMEC=30) 
// COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7)
//     + ,NMEC,LMEC(MAXMEC) 
//     + ,NAMEC(MAXMEC),NSTEP 
//     + ,PID,DESTEP,DESTEL,SAFETY,SLENG 
//     + ,STEP,SNEXT,SFIELD,TOFG,GEKRAT,UPWGHT

typedef struct { 
  Float_t  vect[7];
  Float_t  getot; 
  Float_t  gekin;
  Float_t  vout[7]; 
  Int_t    nmec; 
  Int_t    lmec[MAXMEC]; 
  Int_t    namec[MAXMEC]; 
  Int_t    nstep; 
  Int_t    pid;
  Float_t  destep; 
  Float_t  destel; 
  Float_t  safety; 
  Float_t  sleng; 
  Float_t  step; 
  Float_t  snext; 
  Float_t  sfield; 
  Float_t  tofg; 
  Float_t  gekrat; 
  Float_t  upwght; 
} Gctrak_t;

void helixStep(Float_t step, Float_t *vect, Float_t *vout)
{
  // extrapolate track in constant field
   Float_t field = 20; // field in kilogauss
   enum Evect {kX,kY,kZ,kPX,kPY,kPZ,kPP};
   vout[kPP] = vect[kPP];

   Float_t h4    = field*2.99792e-4;
   Float_t rho   = -h4/vect[kPP];
   Float_t tet   = rho*step;
   Float_t tsint = tet*tet/6;
   Float_t sintt = 1 - tsint;
   Float_t sint  = tet*sintt;
   Float_t cos1t = tet/2;
   Float_t f1 = step*sintt;
   Float_t f2 = step*cos1t;
   Float_t f3 = step*tsint*vect[kPZ];
   Float_t f4 = -tet*cos1t;
   Float_t f5 = sint;
   Float_t f6 = tet*cos1t*vect[kPZ];

   vout[kX]  = vect[kX]  + (f1*vect[kPX] - f2*vect[kPY]);
   vout[kY]  = vect[kY]  + (f1*vect[kPY] + f2*vect[kPX]);
   vout[kZ]  = vect[kZ]  + (f1*vect[kPZ] + f3);
   vout[kPX] = vect[kPX] + (f4*vect[kPX] - f5*vect[kPY]);
   vout[kPY] = vect[kPY] + (f4*vect[kPY] + f5*vect[kPX]);
   vout[kPZ] = vect[kPZ] + (f4*vect[kPZ] + f6); 
}



void tree2w() {

   // write tree2 example
   //create a Tree file tree2.root
   TFile f("tree2.root","recreate");

   //create the file, the Tree
   TTree t2("t2","a Tree with data from a fake Geant3");
   // declare a variable of the C structure type
   Gctrak_t gstep;

   // add the branches for a subset of gstep
   t2.Branch("vect",gstep.vect,"vect[7]/F");
   t2.Branch("getot",&gstep.getot,"getot/F");const Int_t MAXMEC = 30;
// PARAMETER (MAXMEC=30) 
// COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7)
//     + ,NMEC,LMEC(MAXMEC) 
//     + ,NAMEC(MAXMEC),NSTEP 
//     + ,PID,DESTEP,DESTEL,SAFETY,SLENG 
//     + ,STEP,SNEXT,SFIELD,TOFG,GEKRAT,UPWGHT

typedef struct { 
  Float_t  vect[7];
  Float_t  getot; 
  Float_t  gekin;
  Float_t  vout[7]; 
  Int_t    nmec; 
  Int_t    lmec[MAXMEC]; 
  Int_t    namec[MAXMEC]; 
  Int_t    nstep; 
  Int_t    pid;
  Float_t  destep; 
  Float_t  destel; 
  Float_t  safety; 
  Float_t  sleng; 
  Float_t  step; 
  Float_t  snext; 
  Float_t  sfield; 
  Float_t  tofg; 
  Float_t  gekrat; 
  Float_t  upwght; 
} Gctrak_t;
   t2.Branch("gekin",&gstep.gekin,"gekin/F");
   t2.Branch("nmec",&gstep.nmec,"nmec/I");
   t2.Branch("lmec",gstep.lmec,"lmec[nmec]/I");
   t2.Branch("destep",&gstep.destep,"destep/F");
   t2.Branch("pid",&gstep.pid,"pid/I"); 

   //Initialize particle parameters at first point
   Float_t px,py,pz,p,charge=0;
   Float_t vout[7];
   Float_t mass  = 0.137;
   Bool_t newParticle = kTRUE;                             
   gstep.step    = 0.1;
   gstep.destep  = 0;
   gstep.nmec    = 0;
   gstep.pid     = 0;

   //transport particles 
   for (Int_t i=0; i<10000; i++) {
//generate a new particle if necessary (Geant3 emulation)
if (newParticle) {
px = gRandom->Gaus(0,.02);
py = gRandom->Gaus(0,.02);
pz = gRandom->Gaus(0,.02);
p  = TMath::Sqrt(px*px+py*py+pz*pz);
charge = 1;                                   
if (gRandom->Rndm() < 0.5) charge = -1;
gstep.pid    += 1;
gstep.vect[0] = 0;
gstep.vect[1] = 0;
gstep.vect[2] = 0;
gstep.vect[3] = px/p;
gstep.vect[4] = py/p;
gstep.vect[5] = pz/p;
gstep.vect[6] = p*charge;
gstep.getot   = TMath::Sqrt(p*p + mass*mass);
gstep.gekin   = gstep.getot - mass;
newParticle   = kFALSE;
}
// fill the Tree with current step parameters
t2.Fill();


//transport particle in magnetic field (Geant3 emulation)
    helixStep(gstep.step, gstep.vect, vout);   
 //make one step
//apply energy loss
gstep.destep   = gstep.step*gRandom->Gaus(0.0002,0.00001);
gstep.gekin -= gstep.destep;
gstep.getot  = gstep.gekin + mass;
gstep.vect[6]= charge*TMath::Sqrt(gstep.getot*gstep.getot - mass*mass);
  gstep.vect[0] = vout[0];
gstep.vect[1] = vout[1];
gstep.vect[2] = vout[2];
gstep.vect[3] = vout[3];                              
gstep.vect[4] = vout[4];                             
gstep.vect[5] = vout[5];
gstep.nmec    = (Int_t)(5*gRandom->Rndm());
for (Int_t l=0; l<gstep.nmec; l++) gstep.lmec[l] = l;
if  (gstep.gekin < 0.001) newParticle = kTRUE;
if  (TMath::Abs(gstep.vect[2]) > 30) newParticle = kTRUE;
   }
   //save the Tree header. The file will be automatically 
   // closed when going out of the function scope
   t2.Write();
}
