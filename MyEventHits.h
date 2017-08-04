#ifndef MYEVENTHITS_H
#define MYEVENTHITS_H

#include "EventHits.h"
#include <TH3.h>
//#include "Constants.h"

//#include <TLorentzVector.h>

class MyEventHits : public EventHits
{
public:
    TH1F* hRootPhi;// = new TH1F("hRootPhi", "hRootPhi", 50, -TMath::Pi()-0.2, TMath::Pi()+0.2);
    TH1F* hRootCosTheta;// = new TH1F("hRootCosTheta", "hRootCosTheta", 50, -1.1, 1.1);
    TH1F* hRoot12;// = new TH1F("hRoot12", "hRoot12", 50, 2.0, 4.0);
    TH1F* hRootEdep;// = new TH1F("hRootEdep", "hRootEdep", 50, 0.0, 0.4);
    TH1F* hRootEdepPre;// = new TH1F("hRootEdepPre", "hRootEdepPre", 50, 0.0, 0.4);
    TH1F* hRootTheta;
    TH3F* hRootPos;

    MyEventHits();
    virtual ~MyEventHits();
    virtual void Loop();
};

#endif // MYEVENTHITS_H
