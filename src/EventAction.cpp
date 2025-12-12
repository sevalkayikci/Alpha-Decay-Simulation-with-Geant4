#include "EventAction.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction(RunAction *runAction,
                         PrimaryGeneratorAction *primary)
    : G4UserEventAction(),
      fRunAction(runAction),
      fPrimary(primary) {}

void EventAction::BeginOfEventAction(const G4Event *)
{
    // Şimdilik burada ekstra bir şey yapmıyoruz.
}

void EventAction::EndOfEventAction(const G4Event *)
{
    // Her event için, o eventte atılan alfa enerjisini ROOT histogramına yaz
    if (fRunAction && fPrimary)
    {
        G4double eMeV = fPrimary->GetCurrentAlphaEnergyMeV();
        fRunAction->FillAlphaSpectrum(eMeV);
    }
}
