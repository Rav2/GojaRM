#ifndef MYHITS_H
#define MYHITS_H
#include <TH3.h>
#include "Hits.h"
#include <TLorentzVector.h>

class MyHits : public Hits
{
    public:

        TH1F* hPhi;// = new TH1F("hPhi", "hPhi", 50, -TMath::Pi()-0.2, TMath::Pi()+0.2);
        TH1F* hCosTheta;// = new TH1F("hCosTheta", "hCosTheta", 50, -1.1, 1.1);
        TH1F* h12;// = new TH1F("h12", "h12", 50, 2.0, 4.0);
        TH1F* hEdep;// = new TH1F("hEdep", "hEdep", 50, 0.0, 0.4);
        TH3F* hPos;
        TH1F* hTheta;

        void CalculateNewHitPoints(TLorentzVector &v1, const TLorentzVector &source);

        MyHits();
        virtual ~MyHits();
//        virtual Int_t    Cut(Long64_t entry);
//        virtual Int_t    GetEntry(Long64_t entry);
//        virtual Long64_t LoadTree(Long64_t entry);
//        virtual void     Init(TTree *tree);
        virtual void     Loop();
//        virtual Bool_t   Notify();
//        virtual void     Show(Long64_t entry = -1);
};

#endif // MYHITS_H
