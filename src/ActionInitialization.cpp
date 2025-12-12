#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

// ---- Constructor (olmak ZORUNDA) ----
ActionInitialization::ActionInitialization()
    : G4VUserActionInitialization()
{
}

// ---- !! DESTRUCTOR YOK !! ----
// Çünkü ActionInitialization.hh içinde zaten '= default' var.
// Eğer burada tekrar yazarsak hata verir.

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    // PRIMARY
    auto primary = new PrimaryGeneratorAction();
    SetUserAction(primary);

    // RUNACTION
    auto runAction = new RunAction();
    SetUserAction(runAction);

    // EVENTACTION - constructor 2 argüman istiyor!
    auto eventAction = new EventAction(runAction, primary);
    SetUserAction(eventAction);

    // STEPPINGACTION
    SetUserAction(new SteppingAction());
}
