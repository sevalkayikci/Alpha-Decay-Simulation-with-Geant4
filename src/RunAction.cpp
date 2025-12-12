#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

RunAction::RunAction()
    : fRootFile(nullptr),
      fStepFile(nullptr),
      fAlphaHist(nullptr),
      fStepTree(nullptr),
      fX(0.), fY(0.), fZcoord(0.),
      fEdep(0.), fStepL(0.), fTheta(0.),
      fAtomicZ(0), fMode(0), fRunEvents(0)
{
}

RunAction::~RunAction()
{
    if (fRootFile)
        delete fRootFile;
    if (fStepFile)
        delete fStepFile;
}

void RunAction::BeginOfRunAction(const G4Run *)
{
    auto runMan = G4RunManager::GetRunManager();

    auto pg = (PrimaryGeneratorAction *)runMan->GetUserPrimaryGeneratorAction();
    auto det = (DetectorConstruction *)runMan->GetUserDetectorConstruction();

    fAtomicZ = pg->GetZ();
    fMode = pg->GetMode();
    fMaterial = std::string(det->GetMaterialName());
    fRunEvents = 0;

    G4cout << "\n=== RUN START ===" << G4endl;
    G4cout << "Material: " << fMaterial << G4endl;
    G4cout << "Z: " << fAtomicZ << G4endl;
    G4cout << "Mode: " << (fMode == 0 ? "8MeV" : "SuperHeavy") << G4endl;

    // ----- File names -----
    G4String spectrumFile = "data/spectrum_" + G4String(fMaterial) + "_Z" + std::to_string(fAtomicZ) + ".root";
    G4String stepsFile = "data/steps_" + G4String(fMaterial) + "_Z" + std::to_string(fAtomicZ) + ".root";

    fRootFile = TFile::Open(spectrumFile, "RECREATE");
    fStepFile = TFile::Open(stepsFile, "RECREATE");

    // Histogram
    fAlphaHist = new TH1D("hAlpha", "Alpha spectrum", 140, 5, 12);
    fAlphaHist->SetDirectory(nullptr);

    // Step Tree
    fStepTree = new TTree("steps", "Step Data");
    fStepTree->Branch("x", &fX);
    fStepTree->Branch("y", &fY);
    fStepTree->Branch("z", &fZcoord);
    fStepTree->Branch("edep", &fEdep);
    fStepTree->Branch("stepl", &fStepL);
    fStepTree->Branch("theta", &fTheta);
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    fRunEvents = run->GetNumberOfEvent();

    // Save spectrum
    if (fRootFile)
    {
        fRootFile->cd();
        fAlphaHist->Write();
        fRootFile->Write();
        fRootFile->Close();
    }

    // Save steps + info tree
    if (fStepFile)
    {
        fStepFile->cd();

        fStepTree->Write();

        TTree *info = new TTree("info", "Metadata");
        info->Branch("Z", &fAtomicZ);
        info->Branch("material", &fMaterial);
        info->Branch("mode", &fMode);
        info->Branch("events", &fRunEvents);
        info->Fill();
        info->Write();

        fStepFile->Write();
        fStepFile->Close();
    }

    G4cout << "\nEvents: " << fRunEvents << G4endl;

    G4cout << "==============================\n";
    G4cout << "==   RUN FINISHED CLEANLY   ==\n";
    G4cout << "==   ALL ROOT FILES SAVED   ==\n";
    G4cout << "==============================\n";
}

void RunAction::FillAlphaSpectrum(G4double e)
{
    if (fAlphaHist)
        fAlphaHist->Fill(e);
}