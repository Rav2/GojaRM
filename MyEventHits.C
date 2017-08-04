#define MyEventHits_cxx
#include "MyEventHits.h"
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "Constants.h"
MyEventHits::MyEventHits()
{
    hRootPhi = new TH1F("hRootPhi", "hRootPhi", 100, -TMath::Pi()-0.2, TMath::Pi()+0.2);
    hRootCosTheta = new TH1F("hRootCosTheta", "hRootCosTheta", 100, -1.1, 1.1);
    hRoot12 = new TH1F("hRoot12", "hRoot12", 19, 3.1, 3.2);
    hRootEdep = new TH1F("hRootEdep", "hRootEdep", 100, 0.0, 0.4);
    hRootEdepPre = new TH1F("hRootEdepPre", "hRootEdepPre", 100, 0.0, 0.4);
    hRootPos = new TH3F("hRootPos", "hRootPos", 300, -900, 900, 300, -900, 900, 300, -900, 900);
    hRootTheta = new TH1F("hRootTheta", "hRootTheta", 100, -0.2, TMath::Pi()+0.2);
}

MyEventHits::~MyEventHits()
{
    delete hRoot12;
    delete hRootCosTheta;
    delete hRootEdep;
    delete hRootEdepPre;
    delete hRootPhi;
    delete hRootPos;
    delete hRootTheta;
}

void MyEventHits::Loop()
{
//   In a ROOT session, you can do:
//      root> .L EventHits.C
//      root> EventHits t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
//   std::cout<<getenv("ROOT_FILENAME")<<" ";
   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {
       GetEntry(jentry);

//          for(int ii=0; ii<2; ii++)
//          {
//              if(fEdep_[ii] > COMPTON_E_TH_0 && fCutPassing_[ii])
//              {
//                  hRootPhi->Fill(fHitPhi_[ii]);
//                  hRootCosTheta->Fill(TMath::Cos(fHitTheta_[ii]));
//                  hRootEdepPre->Fill(fEdep_[ii]);
//                  hRootEdep->Fill(fEdepSmear_[ii]);
//              }
//          }


//       if(fEdep_[0]>COMPTON_E_TH_0 && fEdep_[1]>COMPTON_E_TH_0)// && fEdep_[0]>COMPTON_E_TH_0 and fEdep_[1]>COMPTON_E_TH_0)
//       {
           TLorentzVector v1(fHitPoint_[0].X() - fEmissionPoint_[0].X(), fHitPoint_[0].Y() - fEmissionPoint_[0].Y(), fHitPoint_[0].Z() - fEmissionPoint_[0].Z(), 0.0);
           TLorentzVector v2(fHitPoint_[1].X() - fEmissionPoint_[1].X(), fHitPoint_[1].Y() - fEmissionPoint_[1].Y(), fHitPoint_[1].Z() - fEmissionPoint_[1].Z(), 0.0);
           TLorentzVector v10(fHitPoint_[0].X(), fHitPoint_[0].Y(), fHitPoint_[0].Z(), 0.0);
           TLorentzVector v20(fHitPoint_[1].X(), fHitPoint_[1].Y(), fHitPoint_[1].Z(), 0.0);
           double cc = 0;
           double dd = 250;
//           if((v10.Z()>-dd && v10.Z()<-cc) || (v20.Z()>-dd && v20.Z()<-cc) || (v10.Z()>cc && v10.Z()<dd) || (v20.Z()>cc && v20.Z()<dd))
//           {
               if(fPassFlag_&& fEdep_[0]>COMPTON_E_TH_0 && fEdep_[1]>COMPTON_E_TH_0) hRoot12->Fill((v1).Angle((v2).Vect()));

               if(fCutPassing_[0] && fEdep_[0]>COMPTON_E_TH_0 && ((v10.Z()>cc && v10.Z()<dd) ||  (v10.Z()<-cc && v10.Z()>-dd)))
               {
                   hRootPhi->Fill(v1.Phi());
                   hRootCosTheta->Fill((v10).CosTheta());
                   hRootEdepPre->Fill(fEdep_[0]);
                   hRootEdep->Fill(fEdepSmear_[0]);
                   hRootTheta->Fill(v10.Theta());
                   hRootPos->Fill(v10.X(), v10.Y(), v10.Z());
               }
               if(fCutPassing_[1] && fEdep_[1]>COMPTON_E_TH_0 && ((v20.Z()>cc && v20.Z()<dd) ||  (v20.Z()<-cc && v20.Z()>-dd)))
               {
                   hRootPhi->Fill((v2).Phi()); //wzgledem zrodla
                   hRootCosTheta->Fill((v20).CosTheta()); //wzgledem srodka
                   hRootEdepPre->Fill(fEdep_[1]);
                   hRootEdep->Fill(fEdepSmear_[1]);
                   hRootTheta->Fill(v20.Theta()); //wzgledem srodka
                   hRootPos->Fill(v20.X(), v20.Y(), v20.Z()); //wzgledem srodka
               }
//           }



//       }
//      Long64_t ientry = LoadTree(jentry);
//      if (ientry < 0) break;
//      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
