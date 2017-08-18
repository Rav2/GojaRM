//================================================================================
// CONSTANTS
//================================================================================

#define EVENTS_SEPARATION_USING_IDS_OF_EVENTS 1

#define EVENTS_SEPARATION_USING_TIME_WINDOW 1-EVENTS_SEPARATION_USING_IDS_OF_EVENTS
#define TIME_WINDOW 3e-9 // in s

// #ifndef COMPTON_E_TH
// #define COMPTON_E_TH 0.05 // in MeV
// #endif

#ifndef COMPTON_E_TH_0
#define COMPTON_E_TH_0 0.01 // in MeV (10 keV)
// #define COMPTON_E_TH_0 0.0001
#endif

#define BLURRED_HITS_POSITIONS 0

// GEOMETRY

#define R 437.3 // in mm
//#define R_inner 437.3 // in mm
#define R_inner 427.8 // in mm
#define L 500 //in mm
// MATERIALS

#define c 299792458. // speed of light in vacuum in m/s
#define n 1.58 // refractive index of EJ230 material 
#define v c/n // speed of light in EJ230 in m/s
