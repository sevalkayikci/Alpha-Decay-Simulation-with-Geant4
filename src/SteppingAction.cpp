#include "SteppingAction.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"

void SteppingAction::UserSteppingAction(const G4Step *step)
{
    // RunAction’a güvenli erişim
    const RunAction *constRun =
        static_cast<const RunAction *>(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runAction = const_cast<RunAction *>(constRun);

    if (!runAction)
        return;

    // Enerji kaybı ve adım uzunluğu
    G4double edep = step->GetTotalEnergyDeposit();
    G4double stepl = step->GetStepLength();
    if (stepl <= 0)
        return;

    // Pozisyon
    G4ThreeVector pos = step->GetPostStepPoint()->GetPosition();

    // Momentumdan saçılma açısı
    G4ThreeVector mom = step->GetPostStepPoint()->GetMomentumDirection();
    G4double theta = mom.theta();

    // RunAction değişkenlerini doldur
    runAction->fX = pos.x() / mm;
    runAction->fY = pos.y() / mm;
    runAction->fZcoord = pos.z() / mm;
    runAction->fEdep = edep / MeV;
    runAction->fStepL = stepl / mm;
    runAction->fTheta = theta / deg;

    // TTree'ye satır ekle
    if (runAction->fStepTree)
        runAction->fStepTree->Fill();
}
