#include "EventAnalysis.h"
#include <TRandom.h>
//#include <TVector3.h>
//================================================================================
// MATHEMATICAL AND ADDITIONAL FUNCTIONS
//================================================================================

// struct used for sorting vectors of hits (functor)
struct EntityComp {
  string property;
  EntityComp(string property) {this->property = property;}
  bool operator()(const Hit& h1, const Hit& h2) const {
      if(property == "TIME")
          return h1.time < h2.time;
      else if (property == "EDEP")
          return h1.edep < h2.edep;
  }
};

double sign(double x) {
  if (x>0) return 1.;
  else if (x<0) return -1.;
  else return 0;
}

//================================================================================
// DEFINITIONS OF CLASS FUNCTIONS - BASIC ANALYSIS
//================================================================================

EventAnalysis::EventAnalysis()
{
  compton_hits.clear();
  compton_hits_blurred.clear();
  
  N0 = 0;
  N = 0;
  multiplicity = 0;
  distance = -1.;
  distance_blurred = -1.;
  theta_angles.clear();
  theta_angles_blurred.clear();
//  h12 = new TH1F("h12", "h12", 50, 2.0, 4.0);

}

void EventAnalysis::select_compton_hits(vector<Hit> hits)
{
  N0 = hits.size();
  double COMPTON_E_TH = atof(getenv("COMPTON_E_TH"));
  for (int i=0; i<hits.size(); i++)
  {
    if (hits[i].edep>COMPTON_E_TH)
        compton_hits.push_back(hits[i]);
  }
  N = compton_hits.size();
//   cout << N0 << "\t" << N << endl;
}

void EventAnalysis::sort_compton_hits(string key)
{
  sort(compton_hits.begin(), compton_hits.end(), EntityComp(key));
}

// //================================================================================
// // DEFINITIONS OF CLASS FUNCTIONS - ADVANCED ANALYSIS
// //================================================================================
// 
// void EventAnalysis::calculate_multiplicity() {
//   multiplicity = nr_of_hits;
//   
//   if (multiplicity>1) {
//     
//     // only first time difference is taken into account
//     int id_diff = min(abs(compton_hits[1].volumeID-compton_hits[0].volumeID), 384-abs(compton_hits[1].volumeID-compton_hits[0].volumeID));
//     double time_diff = fabs(compton_hits[1].time-compton_hits[0].time)*1e9;
//     double id_diff_ref = 42*time_diff+150.; // above this line coincidences are treated as true coincidences
// 
//     if (id_diff<=id_diff_ref) multiplicity = -multiplicity;
//     
//   }
//   
// }
// 

//================================================================================
// PRINTING
//================================================================================

int EventAnalysis::verify_type_of_coincidence(Hit h1, Hit h2) {
  
  int t= 0;
  
  if (h1.eventID==h2.eventID) { //true, phantom-scattered and detector-scattered
    if (h1.nPhantomCompton==0 and h2.nPhantomCompton==0) {
      if (h1.nCrystalCompton==1 and h2.nCrystalCompton==1) { //true
	t = 1;
      }
      else { //detector-scattered
        t = 3;
      }
    }
    else { //phantom-scattered
      t = 2;
    }
  }
  else { //accidental
    t = 4;
  }
  
  return t;
}

void EventAnalysis::print_coincidences() {
  
  cout.setf(ios::fixed);

//     for (int i=0; i<nr_of_hits-1; i++) {
    
//       Hit h1 = compton_hits[i];
//       Hit h2 = compton_hits[i+1];
      
      Hit h1 = compton_hits[0];
      Hit h2 = compton_hits[1];
      
    
      //Hit h1 = compton_hits_blurred[i];
      //Hit h2 = compton_hits_blurred[i+1];
      
//       if (verify_type_of_coincidence(h1, h2)==1 and h1.nCrystalCompton!=h2.nCrystalCompton) {
      
      
      cout.precision(2);
      cout << h1.posX/10. << "\t" << h1.posY/10. << "\t" << h1.posZ/10. << "\t";
      cout.precision(1);
      cout << h1.time*1e12 << "\t";

      cout.precision(2);
      cout << h2.posX/10. << "\t" << h2.posY/10. << "\t" << h2.posZ/10. << "\t";
      cout.precision(1);
      cout << h2.time*1e12 << "\t";
      
      cout << h1.volumeID << "\t";
      cout << h2.volumeID << "\t";
      
      cout.precision(2);
      cout << h1.edep*1000 << "\t";
      cout << h2.edep*1000 << "\t";
      
      cout << verify_type_of_coincidence(h1, h2) << "\t";
      
      cout.precision(2);
      cout << h1.sourcePosX/10. << "\t" << h1.sourcePosY/10. << "\t" << h1.sourcePosZ/10. << endl;

//       cout << h1.nCrystalCompton << "\t" << h2.nCrystalCompton << endl;
      
//       cout << verify_type_of_coincidence2(h1, h2) << endl;

      
//       cout << verify_type_of_coincidence(h1, h2) << "\t" << verify_type_of_coincidence2(h1, h2) << endl;
      
      //cout.precision(2);
      //cout << h1.localPosX/10. << "\t" << h1.localPosY/10. << "\t" << h1.localPosZ/10. << "\t" << h2.localPosX/10. << "\t" << h2.localPosY/10. << "\t" << h2.localPosZ/10. << endl;      
      
      //int id_diff = min(abs(h2.volumeID-h1.volumeID), 384-abs(h2.volumeID-h1.volumeID));
    
//     }
//     }  
  
}

//================================================================================
// DEFINITIONS OF CLASS FUNCTIONS - MAIN ANALYSIS FUNCTION
//================================================================================

void EventAnalysis::analyze_event(vector< Hit > hits, TH1F* h12, TH1F* hPhi, TH1F* hCosTheta, TH3F* hPos, TH1F* hTheta, TH1F* hEdep)
{		

  select_compton_hits(hits);

//   if (N==2 and N0==2) print_coincidences();
//  if (N==2 and (N0==2 or N0==3)) print_coincidences();
//  if(N==1 and (N0==1 or N0==2) and h12 and hPhi and hCosTheta)
//  {
//       Hit hit1 = compton_hits[0];
//       TLorentzVector v1(hit1.posX-hit1.sourcePosX, hit1.posY-hit1.sourcePosY, hit1.posZ-hit1.sourcePosZ, 0.0);
//       hPhi->Fill(v1.Phi());
//       hCosTheta->Fill(v1.CosTheta());
//  }
  if (N==2 and (N0==2 or N0==3))
  {
//      print_coincidences();
      Hit hit1 = compton_hits[0];
      Hit hit2 = compton_hits[1];
//      if(hit1.nCrystalCompton==1 && hit2.nCrystalCompton==1 && hit1.nPhantomCompton==0 && hit2.nPhantomCompton==0 && \
//              h12 and hPhi and hCosTheta and hPos and hTheta and hEdep)
      {
//          int t =verify_type_of_coincidence(hit1, hit2);
//          cout<<"t="<<t<<" ";

          TLorentzVector v1(hit1.posX-hit1.sourcePosX, hit1.posY-hit1.sourcePosY, hit1.posZ-hit1.sourcePosZ, 0.0);
          TLorentzVector v2(hit2.posX-hit2.sourcePosX, hit2.posY-hit2.sourcePosY, hit2.posZ-hit2.sourcePosZ, 0.0);
          TLorentzVector v10(hit1.posX, hit1.posY, hit1.posZ, 0.0);
          TLorentzVector v20(hit2.posX, hit2.posY, hit2.posZ, 0.0);
          double angle3 = v2.Angle(v1.Vect());

//          if(angle3<3.14)
//             cout<<"angle3="<<v2.Angle(v1.Vect())<<" ";
//          else
//          {
              double cc = 0;
              double dd = 250;
//              if((v10.Z()>-dd && v10.Z()<-cc) || (v20.Z()>-dd && v20.Z()<-cc) || (v10.Z()>cc && v10.Z()<dd) || (v20.Z()>cc && v20.Z()<dd))
              if(verify_type_of_coincidence(hit1, hit2)==1) //tylko true coincidences
              {
                  h12->Fill(v2.Angle(v1.Vect()));
//                  hPhi->Fill(v10.Phi());
//                  hCosTheta->Fill(v10.CosTheta());
//                  hPhi->Fill(v20.Phi());
//                  hCosTheta->Fill(v20.CosTheta());
//                  hPos->Fill(v10.X(), v10.Y(), v10.Z());
//                  hPos->Fill(v20.X(), v20.Y(), v20.Z());
//                  hTheta->Fill(v10.Theta());
//                  hTheta->Fill(v20.Theta());
//                  hEdep->Fill(hit1.edep);
//                  hEdep->Fill(hit2.edep);
              }
//          }

      }
  }
  // test
//   if (N==2 and N0==2) verify_type_of_coincidence(compton_hits[0], compton_hits[1]);
  
  
//   sort_compton_hits("TIME");
//   verify_type_of_coincidence(hits[0],hits[1]);
  
//   print_coincidences();
  
}
