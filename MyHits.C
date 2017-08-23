#define MyHits_cxx
#include "MyHits.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "EventAnalysis.h"
#include "Constants.h"

MyHits::MyHits()
{
    hPhi = new TH1F("hPhi", "hPhi", 100, -TMath::Pi()-0.2, TMath::Pi()+0.2);
    hCosTheta = new TH1F("hCosTheta", "hCosTheta", 100, -1.1, 1.1);
    h12 = new TH1F("h12", "h12", 19, 3.1, 3.2);
    hEdep = new TH1F("hEdep", "hEdep", 100, 0.0, 0.4);
    hPos = new TH3F("hPos", "hPos", 300, -900, 900, 300, -900, 900, 300, -900, 900);
    hTheta = new TH1F("hTheta", "hTheta", 100, -0.2, TMath::Pi()+0.2);
}
MyHits::~MyHits()
{
    delete hPhi;
    delete hCosTheta;
    delete h12;
    delete hEdep;
    delete hPos;
    delete hTheta;
}

TLorentzVector MyHits::CalculateNewHitPoints(TLorentzVector h, const TLorentzVector source)
{
    TLorentzVector r(h.X()-source.X(), h.Y()-source.Y(), h.Z()-source.Z(), 0.0);
       double rx = r.X();
       double ry = r.Y();
       double rz = r.Z();
       double xs = source.X();
       double ys = source.Y();
       double zs = source.Z();
       double Rs2 = (xs*xs+ys*ys);
       double delta = 4*((xs*rx+ys*ry)*(xs*rx+ys*ry) -  (rx*rx+ry*ry)*(Rs2-R*R));
       double s = (-2*((xs*rx+ys*ry))+TMath::Sqrt(delta))/2.0/(rx*rx+ry*ry);
   //    cout<<"Rs="<<TMath::Sqrt(Rs2)<<" R="<<R<<" ";
   //    cout<<"delta="<<delta<<" s="<<s<<" ";
       TLorentzVector hh = r*s + source;
   //    cout<<TMath::Abs(hh.Mag())<<" ";
       if(TMath::Abs(hh.Z()) > L/2.0)
       {
   //        cout<<"W IFIE! ";
           hh.SetX(0);
           hh.SetY(0);
           hh.SetZ(0);
           hh.SetT(0);
         }
//    else
        ;//cout<<"Poza ifem ";
    return hh;
}

void MyHits::Loop() {

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   int last_eventID;
   double last_time;

   vector<Hit> hits;
   hits.clear();

//    for (Long64_t jentry=0; jentry<nentries;jentry++) {
//       Long64_t ientry = LoadTree(jentry);
//       if (ientry < 0) break;
//       nb = fChain->GetEntry(jentry);
//       nbytes += nb;
//
//       double E = edep;
//       if (E>0) cout << E*1000 << endl;
//    }

   if (EVENTS_SEPARATION_USING_IDS_OF_EVENTS)
   {
   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      if (jentry==0) {
        last_eventID = eventID;
      }

      Hit h;
      h.eventID = eventID;
      h.volumeID = volumeID[1]+1; // numbering from 1 not from 0
      h.trackID = trackID;
      h.parentID = parentID;
      h.primaryID = primaryID;
      h.time = time;
      h.processName = string(processName);
      h.edep = edep;
      h.posX = posX;
      h.posY = posY;
      h.posZ = posZ;
      h.sourcePosX = sourcePosX;
      h.sourcePosY = sourcePosY;
      h.sourcePosZ = sourcePosZ;
      h.comptVolName = comptVolName;
      h.nPhantomCompton = nPhantomCompton;
      h.nCrystalCompton = nCrystalCompton;
      h.nPhantomRayleigh = nPhantomRayleigh;
      h.nCrystalRayleigh = nCrystalRayleigh;

      double d = sqrt(h.posX*h.posX + h.posY*h.posY); // distance between the hit and the main axis of the scanner - chose only hits from strips
//      bool hit_is_proper = h.edep>COMPTON_E_TH_0 and h.nCrystalCompton==1 and h.nPhantomCompton==0 and h.nPhantomRayleigh==0 and h.nCrystalRayleigh==0 and PDGEncoding==22;
      bool hit_is_proper = h.edep>COMPTON_E_TH_0 and (h.processName=="Compton" or h.processName=="compt") and h.nPhantomRayleigh==0 and h.nCrystalRayleigh==0 and PDGEncoding==22;

      if (last_eventID==eventID)
      {

        if (hit_is_proper)
        {
           //wypelnianie tablicy hits kandydatami na koincydencje
            hits.push_back(h);
            TLorentzVector v10(h.posX, h.posY, h.posZ, 0.0);
            TLorentzVector source(h.sourcePosX, h.sourcePosY, h.sourcePosZ, 0.0);
            TLorentzVector v1 = v10-source;
            v10 = CalculateNewHitPoints(v10, source); //korekcja hit pointow
            double cc = 0;
            double dd = 250;
//            if((v10.Z()>-dd && v10.Z()<-cc) || (v10.Z()>cc && v10.Z()<dd) && v10.Mag() != 0)
            if(!(v10.X()==0 && v10.Y()==0 && v10.Z()==0 && v10.T()==0))
            {
                hPhi->Fill(v10.Phi());
                hCosTheta->Fill(v10.CosTheta());
                hPos->Fill(v10.X(), v10.Y(), v10.Z());
                hTheta->Fill(v10.Theta());
                hEdep->Fill(h.edep);
            }
        }
      }
      else
      {
        if (hits.size()==2 and hits[0].volumeID!=hits[1].volumeID)
        {
          //zaczal sie nowy event
          //analiza koincydencji z poprzedniego eventu
          EventAnalysis ea;
          ea.analyze_event(hits, h12, hPhi, hCosTheta, hPos, hTheta, hEdep);
        }
        hits.clear();
        if (hit_is_proper)
        {
            //dodaj pierwsza gamme z nowego eventu do hits
            hits.push_back(h);
            TLorentzVector v10(h.posX, h.posY, h.posZ, 0.0);
            TLorentzVector source(h.sourcePosX, h.sourcePosY, h.sourcePosZ, 0.0);
            TLorentzVector v1 = v10-source;
            v10 = CalculateNewHitPoints(v10, source);
            double cc = 0;
            double dd = 250;
//            if((v10.Z()>-dd && v10.Z()<-cc) || (v10.Z()>cc && v10.Z()<dd) && v10.Mag() != 0)
            if(!(v10.X()==0 && v10.Y()==0 && v10.Z()==0 && v10.T()==0))
            {
                hPhi->Fill(v10.Phi());
                hCosTheta->Fill(v10.CosTheta());
                hPos->Fill(v10.X(), v10.Y(), v10.Z());
                hTheta->Fill(v10.Theta());
                hEdep->Fill(h.edep);
            }

        }
      }

      last_eventID = eventID;
   }
   }

   else if (EVENTS_SEPARATION_USING_TIME_WINDOW) {
   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {
//       cout<<"TU NIE POWINNO MNIE BYC!"<<endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      if (jentry==0) {
        last_time = time;
      }

      Hit h;
      h.eventID = eventID;
      h.volumeID = volumeID[1]+1; // numbering from 1 not from 0
      h.trackID = trackID;
      h.parentID = parentID;
      h.primaryID = primaryID;
      h.time = time;
      h.processName = string(processName);
      h.edep = edep;
      h.posX = posX;
      h.posY = posY;
      h.posZ = posZ;
      h.sourcePosX = sourcePosX;
      h.sourcePosY = sourcePosY;
      h.sourcePosZ = sourcePosZ;
      h.comptVolName = comptVolName;
      h.nPhantomCompton = nPhantomCompton;
      h.nCrystalCompton = nCrystalCompton;
      h.nPhantomRayleigh = nPhantomRayleigh;
      h.nCrystalRayleigh = nCrystalRayleigh;

      double d = sqrt(h.posX*h.posX + h.posY*h.posY); // distance between the hit and the main axis of the scanner - chose only hits from strips
      bool hit_is_proper = h.edep>COMPTON_E_TH_0 and (h.processName=="Compton" or h.processName=="compt");// and h.nPhantomRayleigh==0 and h.nCrystalRayleigh==0 and PDGEncoding==22;
//       bool hit_is_proper = h.edep>COMPTON_E_TH_0 and d>R_inner and PDGEncoding==22;

      if (fabs(last_time-time)<TIME_WINDOW)
      {
          if (hit_is_proper)// and h.nCrystalCompton==1)
          {
             //wypelnianie tablicy hits kandydatami na koincydencje
              hits.push_back(h);
              TLorentzVector v10(h.posX, h.posY, h.posZ, 0.0);
              TLorentzVector source(h.sourcePosX, h.sourcePosY, h.sourcePosZ, 0.0);
              TLorentzVector v1 = v10-source;

              v10 = CalculateNewHitPoints(v10, source);
              double cc = 0;
              double dd = 250;
              if((v10.Z()>-dd && v10.Z()<-cc) || (v10.Z()>cc && v10.Z()<dd) && v10.Mag() != 0)
//              if(v10.Mag() != 0)
              {
                  hPhi->Fill(v10.Phi()); //wzgledem srodka
                  hCosTheta->Fill(v10.CosTheta()); //wzgledem srodka
                  hPos->Fill(v10.X(), v10.Y(), v10.Z()); //wzgledem srodka
                  hTheta->Fill(v10.Theta()); //wzgledem srodka
                  hEdep->Fill(h.edep);
              }
          }
      }
      else
      {
        if (hits.size()>=2)
        { // and hits[0].volumeID!=hits[1].volumeID) {
          EventAnalysis ea;
          ea.analyze_event(hits, h12, hPhi, hCosTheta, hPos, hTheta, hEdep);
        }
        hits.clear();
        if (hit_is_proper)// and h.nCrystalCompton==1)
        {
            //dodaj pierwsza gamme z nowego eventu do hits
            hits.push_back(h);
            TLorentzVector v10(h.posX, h.posY, h.posZ, 0.0);
            TLorentzVector source(h.sourcePosX, h.sourcePosY, h.sourcePosZ, 0.0);
            TLorentzVector v1 = v10-source;
            v10 = CalculateNewHitPoints(v10, source);
            double cc = 0;
            double dd = 250;
            if((v10.Z()>-dd && v10.Z()<-cc) || (v10.Z()>cc && v10.Z()<dd) && v10.Mag() != 0)
//            if(v10.Mag() != 0)
            {
                hPhi->Fill(v10.Phi());
                hCosTheta->Fill(v10.CosTheta());
                hPos->Fill(v10.X(), v10.Y(), v10.Z());
                hTheta->Fill(v10.Theta());
                hEdep->Fill(h.edep);
            }
        }
      }

      last_time = time;
   }
   }
}
