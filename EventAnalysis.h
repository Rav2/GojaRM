#ifndef EventAnalysis_h
#define EventAnalysis_h

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <TRandom.h>
#include <TH3F.h>
#include <TLorentzVector.h>


#include "Hit.h"
#include "Constants.h"

class EventAnalysis {

  vector<Hit> compton_hits;
  vector<Hit> compton_hits_blurred;
  
  int N;
  int N0;
  int multiplicity;
  double distance;
  double distance_blurred;
  vector<double> theta_angles;
  vector<double> theta_angles_blurred;
  
public :

  EventAnalysis();
  
  void select_compton_hits(vector<Hit> hits);
  void sort_compton_hits(string key);
  void blur_compton_hits();
  
  int verify_type_of_coincidence(Hit, Hit); // types of coincidences: true, acci, scattered, detector-scattered
//   int verify_type_of_coincidence2(Hit, Hit); // types of coincidences: true, acci, scattered, detector-scattered
  void calculate_multiplicity(); // function to calculate multiplicity if there was detector-scatterer coincidence
  
  void calculate_distance(int blurred=BLURRED_HITS_POSITIONS); // TODO: distance from any point, not only (0,0,0)
  double calculate_distance_point_to_line(Hit, Hit);
  void calculate_theta_angles(int blurred=BLURRED_HITS_POSITIONS); // TODO: angles when source point is not (0,0,0)
  void print_coincidences();
  
  void print_sinogram(Hit, Hit);
 
  void analyze_event(vector<Hit> hits, TH1F* h12=nullptr, TH1F* hPhi=nullptr, TH1F* hCosTheta=nullptr, TH3F* hPos=nullptr, TH1F* hTheta=nullptr, TH1F* hEdep=nullptr);
  
  int find_coincidences(vector<Hit>);

};

#endif
