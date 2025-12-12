#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class PrimaryGeneratorAction;
class G4Event;

class EventAction : public G4UserEventAction
{
public:
    EventAction(RunAction *runAction, PrimaryGeneratorAction *primary);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event *) override;
    void EndOfEventAction(const G4Event *) override;

private:
    RunAction *fRunAction;
    PrimaryGeneratorAction *fPrimary;
};

#endif
