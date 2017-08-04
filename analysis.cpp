#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <TCanvas.h>
#include <TImage.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>

#include "MyHits.h"
#include "MyEventHits.h"

using namespace std;

void drawPhi(TH1F* hPhi, TH1F* hRootPhi)
{
    ////// ***********DRAWING PHI****************************
    hPhi->GetXaxis()->SetTitle("#phi");

    TCanvas* cphi = new TCanvas("cphi", "cphi", 600, 800);
    cphi->Divide(1,2);
    TLegend* legPhi = new TLegend(0.35, 0.2, 0.65, 0.5);
    cphi->cd(1);
    hPhi->Scale(1.0/hPhi->Integral());
    hPhi->SetLineColor(kBlue);
    hPhi->SetLineWidth(2);
//    hPhi->Sumw2();
    hPhi->Draw();
    legPhi -> AddEntry(hPhi, "GATE");
    hRootPhi->Scale(1.0/hRootPhi->Integral());
    hRootPhi->SetLineColor(kRed);
    hRootPhi->SetLineWidth(2);
//    hRootPhi->Sumw2();
    hRootPhi->Draw("same");
    legPhi -> AddEntry(hRootPhi, "ROOT");
//    legPhi->Draw();
    cphi->cd(2);
    TH1F* hPhiDiff = new TH1F("hPhiDiff", "hPhiDiff", 100, -TMath::Pi()-0.2, TMath::Pi()+0.2);
    hPhiDiff->GetXaxis()->SetTitle("#phi");
    int NBins = hPhi->GetNbinsX();// > hRootPhi->GetNbinsX() ? hRootPhi->GetNbinsX() : hPhi->GetNbinsX();
    for(int ii=1; ii<NBins; ii++)
    {
        float binCenter = hPhi->GetXaxis()->GetBinCenter(ii);
        float val1 = hPhi->GetBinContent(ii);
        float val2 = hRootPhi->GetBinContent(ii);
        float diff = val1 - val2;
        hPhiDiff->SetBinContent(ii, diff);
    }
    hPhiDiff->SetMarkerStyle(21);
    hPhiDiff->Sumw2();
    hPhiDiff->Draw("E");
    TLine* line = new TLine(1.0*-TMath::Pi(), 0.0, 1.0*TMath::Pi(), 0.0);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");
    TImage *img = TImage::Create();
    img->FromPad(cphi);
    img->WriteImage("phi.png");
    delete img;
}

void drawCosTheta(TH1F* hCosTheta, TH1F* hRootCosTheta)
{
    ////// ***********DRAWING COS THETA****************************
    hCosTheta->GetXaxis()->SetTitle("cos(#theta)");

    TCanvas* ccostheta = new TCanvas("ccostheta", "ccostheta", 600, 800);
    ccostheta->Divide(1,2);
    TLegend* legCosTheta = new TLegend(0.35, 0.2, 0.65, 0.5);
    ccostheta->cd(1);
    hCosTheta->Scale(1.0/hCosTheta->Integral());
    hCosTheta->SetLineColor(kBlue);
    hCosTheta->SetLineWidth(2);
    hCosTheta->Draw();
    legCosTheta -> AddEntry(hCosTheta, "GATE");
    hRootCosTheta->Scale(1.0/hRootCosTheta->Integral());
    hRootCosTheta->SetLineColor(kRed);
    hRootCosTheta->SetLineWidth(2);
    hRootCosTheta->Draw("same");
    legCosTheta -> AddEntry(hRootCosTheta, "ROOT");
//    legCosTheta->Draw();
    ccostheta->cd(2);
    TH1F* hCosThetaDiff = new TH1F("hCosThetaDiff", "hCosThetaDiff", 100, -1.1, 1.1);
    hCosThetaDiff->GetXaxis()->SetTitle("cos(#theta)");
    int NBins = hCosTheta->GetNbinsX();// > hRootPhi->GetNbinsX() ? hRootPhi->GetNbinsX() : hPhi->GetNbinsX();
    for(int ii=1; ii<NBins; ii++)
    {
        float binCenter = hCosTheta->GetXaxis()->GetBinCenter(ii);
        float val1 = hCosTheta->GetBinContent(ii);
        float val2 = hRootCosTheta->GetBinContent(ii);
        float diff = val1 - val2;
        hCosThetaDiff->SetBinContent(ii, diff);
    }
    hCosThetaDiff->SetMarkerStyle(21);
    hCosThetaDiff->Sumw2();
    hCosThetaDiff->Draw("E");
    TLine* line = new TLine(-1.0, 0.0, 1.0, 0.0);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");
    TImage *img = TImage::Create();
    img->FromPad(ccostheta);
    img->WriteImage("cos(theta).png");
    delete img;
}

void drawTheta(TH1F* hTheta, TH1F* hRootTheta)
{
    ////// ***********DRAWING COS THETA****************************
    hTheta->GetXaxis()->SetTitle("#theta");

    TCanvas* ctheta = new TCanvas("ctheta", "ctheta", 600, 800);
    ctheta->Divide(1,2);
    TLegend* legTheta = new TLegend(0.35, 0.2, 0.65, 0.5);
    ctheta->cd(1);
    hTheta->Scale(1.0/hTheta->Integral());
    hTheta->SetLineColor(kBlue);
    hTheta->SetLineWidth(2);
    hTheta->Draw();
    legTheta -> AddEntry(hTheta, "GATE");
    hRootTheta->Scale(1.0/hRootTheta->Integral());
    hRootTheta->SetLineColor(kRed);
    hRootTheta->SetLineWidth(2);
    hRootTheta->Draw("same");
    legTheta -> AddEntry(hRootTheta, "ROOT");
//    legCosTheta->Draw();
    ctheta->cd(2);
    TH1F* hThetaDiff = new TH1F("hThetaDiff", "hThetaDiff", 100, -0.2, TMath::Pi()+0.2);
    hThetaDiff->GetXaxis()->SetTitle("#theta");
    int NBins = hTheta->GetNbinsX();// > hRootPhi->GetNbinsX() ? hRootPhi->GetNbinsX() : hPhi->GetNbinsX();
    for(int ii=1; ii<NBins; ii++)
    {
        float binCenter = hTheta->GetXaxis()->GetBinCenter(ii);
        float val1 = hTheta->GetBinContent(ii);
        float val2 = hRootTheta->GetBinContent(ii);
        float diff = val1 - val2;
        hThetaDiff->SetBinContent(ii, diff);
    }
    hThetaDiff->SetMarkerStyle(21);
    hThetaDiff->Sumw2();
    hThetaDiff->Draw("E");
    TLine* line = new TLine(0.0, 0.0, TMath::Pi(), 0.0);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");
    TImage *img = TImage::Create();
    img->FromPad(ctheta);
    img->WriteImage("theta.png");
    delete img;
}

void drawRelAngle(TH1F* h12, TH1F* hRoot12)
{
    ////// ***********DRAWING Relative ANGLE DISTR ****************************
    h12->GetXaxis()->SetTitle("#theta_{12}");

    TCanvas* cRelAngles = new TCanvas("cRelAngles", "cRelAngles", 600, 800);
    cRelAngles->Divide(1,2);
    TLegend* legRelAngles = new TLegend(0.65, 0.2, 0.95, 0.5);
    cRelAngles->cd(1);
    h12->Scale(1.0/h12->Integral());
    h12->SetLineColor(kBlue);
    h12->SetLineWidth(2);

    legRelAngles -> AddEntry(h12, "GATE");
    hRoot12->Scale(1.0/hRoot12->Integral());
    hRoot12->SetLineColor(kRed);
    hRoot12->SetLineWidth(2);

    legRelAngles -> AddEntry(hRoot12, "ROOT");
    hRoot12->Draw("hist");
    h12->Draw("same");
    legRelAngles->Draw();
    cRelAngles->cd(2);
    TH1F* hRelAnglesDiff = new TH1F("hRelAnglesDiff", "hRelAnglesDiff", 19, 3.10, 3.20);
    hRelAnglesDiff->GetXaxis()->SetTitle("theta_{12}");
    int NBins = h12->GetNbinsX();// > hRootPhi->GetNbinsX() ? hRootPhi->GetNbinsX() : hPhi->GetNbinsX();
    for(int ii=1; ii<NBins; ii++)
    {
        float binCenter = h12->GetXaxis()->GetBinCenter(ii);
        float val1 = h12->GetBinContent(ii);
        float val2 = hRoot12->GetBinContent(ii);
        float diff = val1 - val2;
        hRelAnglesDiff->SetBinContent(ii, diff);
    }
    hRelAnglesDiff->SetMarkerStyle(21);
    hRelAnglesDiff->Sumw2();
    hRelAnglesDiff->Draw("E");
    TLine* line = new TLine(3.10, 0.0, 3.20, 0.0);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");
    TImage *img = TImage::Create();
    img->FromPad(cRelAngles);
    img->WriteImage("relAngles.png");
    delete img;
}

void drawPos(TH3F* hPos, TH3F* hRootPos)
{
    TCanvas* posCanvas = new TCanvas("posCanvas", "posCanvas", 1400, 800);
    posCanvas->Divide(2,1);
    posCanvas->cd(1);
    gPad->SetTheta(20);
    gPad->SetPhi(235);
    gStyle->SetOptStat(1);
    hPos->GetXaxis()->SetTitle("X");
    hPos->GetXaxis()->SetTitleOffset(2);
    hPos->GetYaxis()->SetTitle("Y");
    hPos->GetYaxis()->SetTitleOffset(2);
    hPos->GetZaxis()->SetTitle("Z");
    hPos->GetZaxis()->SetTitleOffset(2);
    hPos->Draw("ISO");

    posCanvas->cd(2);
    gPad->SetTheta(20);
    gPad->SetPhi(235);
    gStyle->SetOptStat(1);
    hRootPos->GetXaxis()->SetTitle("X");
    hRootPos->GetXaxis()->SetTitleOffset(2);
    hRootPos->GetYaxis()->SetTitle("Y");
    hRootPos->GetYaxis()->SetTitleOffset(2);
    hRootPos->GetZaxis()->SetTitle("Z");
    hRootPos->GetZaxis()->SetTitleOffset(2);
    hRootPos->Draw("ISO");
    TImage *img = TImage::Create();
    img->FromPad(posCanvas);
    img->WriteImage("pos.png");
    delete img;
}

////// ***********DRAWING Edep DISTR WITH SMEAR EFFECT ****************************
void drawEdepSmear(TH1F* hEdep, TH1F* hRootEdep)
{

    TCanvas* cEdep = new TCanvas("cEdep", "edep with SMEAR", 600, 800);
    cEdep->Divide(1,2);
    TLegend* legEdep = new TLegend(0.15, 0.2, 0.45, 0.5);
    cEdep->cd(1);
    hEdep->Scale(1.0/hEdep->Integral());
    hEdep->SetLineColor(kBlue);
    hEdep->SetLineWidth(2);

    legEdep -> AddEntry(hEdep, "GATE");
    hRootEdep->Scale(1.0/hRootEdep->Integral());
    hRootEdep->SetLineColor(kRed);
    hRootEdep->SetLineWidth(2);


    hRootEdep->Draw();
    hEdep->Draw("same");

    legEdep -> AddEntry(hRootEdep, "ROOT");
    legEdep->Draw();
    cEdep->cd(2);
    TH1F* hEdepDiff = new TH1F("hEdepDiff", "hEdepDiff", 100, 0.0, 0.4);
    hEdepDiff->GetXaxis()->SetTitle("E [MeV]");
    int NBins = hEdep->GetNbinsX();// > hRootPhi->GetNbinsX() ? hRootPhi->GetNbinsX() : hPhi->GetNbinsX();
    for(int ii=1; ii<NBins; ii++)
    {
        float binCenter = hEdep->GetXaxis()->GetBinCenter(ii);
        float val1 = hEdep->GetBinContent(ii);
        float val2 = hRootEdep->GetBinContent(ii);
        float diff = val1 - val2;
        hEdepDiff->SetBinContent(ii, diff);
    }
    hEdepDiff->SetMarkerStyle(21);
    hEdepDiff->Sumw2();
    hEdepDiff->Draw("E");
    TLine* line = new TLine(0.0, 0.0, 0.4, 0.0);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");
    TImage *img = TImage::Create();
    img->FromPad(cEdep);
    img->WriteImage("edepWithSMEAR.png");
    delete img;
}

////// ***********DRAWING Edep DISTR WITHOUT SMEAR EFFECT ****************************
void drawEdep(TH1F* hEdep, TH1F* hRootEdepPre)
{
    TCanvas* cEdepPre = new TCanvas("cEdepPre", "WITHOUT SMEAR", 600, 800);
    cEdepPre->Divide(1,2);
    TLegend* legEdep = new TLegend(0.15, 0.65, 0.45, 0.95);
    cEdepPre->cd(1);

    hEdep->Scale(1.0/hEdep->Integral());
    hEdep->SetLineColor(kBlue);
    hEdep->SetLineWidth(2);
    legEdep -> AddEntry(hEdep, "GATE");
    hRootEdepPre->Scale(1.0/hRootEdepPre->Integral());
    hRootEdepPre->SetLineColor(kRed);
    hRootEdepPre->SetLineWidth(2);


    hRootEdepPre->Draw();
    hEdep->Draw("same");

    legEdep -> AddEntry(hRootEdepPre, "ROOT");
    legEdep->Draw();
    cEdepPre->cd(2);
    TH1F* hEdepPreDiff = new TH1F("hEdepPreDiff", "Edep diff without SMEAR", 100, 0.0, 0.4);
    hEdepPreDiff->GetXaxis()->SetTitle("E [MeV]");
    int NBins = hEdep->GetNbinsX();// > hRootPhi->GetNbinsX() ? hRootPhi->GetNbinsX() : hPhi->GetNbinsX();
    for(int ii=1; ii<NBins; ii++)
    {
        float binCenter = hEdep->GetXaxis()->GetBinCenter(ii);
        float val1 = hEdep->GetBinContent(ii);
        float val2 = hRootEdepPre->GetBinContent(ii);
        float diff = val1 - val2;
        hEdepPreDiff->SetBinContent(ii, diff);
    }
    hEdepPreDiff->SetMarkerStyle(21);
    hEdepPreDiff->Sumw2();
    hEdepPreDiff->Draw("E");
    TLine* line = new TLine(0.0, 0.0, 0.4, 0.0);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");
    TImage *img = TImage::Create();
    img->FromPad(cEdepPre);
    img->WriteImage("edepPreSMEAR.png");
    delete img;
}


int main (int argc, char* argv[]) {

  if (argc==3) {
    setenv("COMPTON_E_TH", argv[1], 1);
    setenv("ROOT_FILENAME", argv[2], 1);
  }
  else {
    setenv("COMPTON_E_TH", "0.0", 1);
    setenv("ROOT_FILENAME", "/home/rafal/Projekty/gojaRM/output/output_side.root", 1);
  }
  
  MyHits h;
  h.Loop(); 
//  setenv("ROOT_FILENAME", "/home/rafal/Projekty/goja/output/side.root", 1);

  MyEventHits eh;
  eh.Loop();
  // Drawing
  drawPhi(h.hPhi, eh.hRootPhi);
  drawCosTheta(h.hCosTheta, eh.hRootCosTheta);
  drawRelAngle(h.h12, eh.hRoot12);
  drawPos(h.hPos, eh.hRootPos);
  drawEdep(h.hEdep, eh.hRootEdepPre);
  drawTheta(h.hTheta, eh.hRootTheta);
//  cout<<getenv("ROOT_FILENAME")<<" ";
  cout<<"GATE entries="<<h.hPos->GetEntries()<<" ROOT entriess="<<eh.hRootPos->GetEntries()<<endl;
  return 0;
  
}
