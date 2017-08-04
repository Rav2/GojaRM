#define Hits_cxx
#include "Hits.h"
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

void Hits::Loop() {

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
   
   if (EVENTS_SEPARATION_USING_IDS_OF_EVENTS) {
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
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
      bool hit_is_proper = h.edep>COMPTON_E_TH_0 and (h.processName=="Compton" or h.processName=="compt") and h.nPhantomRayleigh==0 and h.nCrystalRayleigh==0 and PDGEncoding==22;
 
      if (last_eventID==eventID) {
	if (hit_is_proper) hits.push_back(h);
      } 
      else {
	if (hits.size()==2 and hits[0].volumeID!=hits[1].volumeID) {
	  EventAnalysis ea;
          ea.analyze_event(hits);
	}
	hits.clear();
	if (hit_is_proper) hits.push_back(h);
      }

      last_eventID = eventID;
   }
   }
   
   else if (EVENTS_SEPARATION_USING_TIME_WINDOW) {
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
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
      bool hit_is_proper = h.edep>COMPTON_E_TH_0 and (h.processName=="Compton" or h.processName=="compt") and h.nPhantomRayleigh==0 and h.nCrystalRayleigh==0 and PDGEncoding==22;
//       bool hit_is_proper = h.edep>COMPTON_E_TH_0 and d>R_inner and PDGEncoding==22;
      
      if (fabs(last_time-time)<TIME_WINDOW) {
	if (hit_is_proper) hits.push_back(h);
      } 
      else {
 	if (hits.size()>=2) { // and hits[0].volumeID!=hits[1].volumeID) {
	  EventAnalysis ea;
          ea.analyze_event(hits);
	}
	hits.clear();
	if (hit_is_proper) hits.push_back(h);
      }
      
      last_time = time;
   }
   }
}
