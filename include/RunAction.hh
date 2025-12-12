#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run *) override;
    void EndOfRunAction(const G4Run *) override;

    void FillAlphaSpectrum(G4double energyMeV);

    // Step data (position + edep)
    TFile *fStepFile;
    TTree *fStepTree;
    double fX, fY, fZcoord; // Z_coord olarak yeniden adlandırıldı
    double fEdep;
    double fStepL;
    double fTheta;

private:
    // Alpha spectrum
    TFile *fRootFile;
    TH1D *fAlphaHist;

    // Metadata
    G4int fAtomicZ;        // Z of nucleus
    G4int fMode;           // energy mode
    std::string fMaterial; // "Silicon", "Gold" ...
    G4int fRunEvents;      // event count
};

#endif