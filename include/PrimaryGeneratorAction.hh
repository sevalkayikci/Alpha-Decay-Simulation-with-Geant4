#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event *event) override;

    // --- INFORMATION ACCESS ---
    G4double GetCurrentAlphaEnergyMeV() const { return fCurrentEnergyMeV; }
    G4int GetMode() const { return fMode; }
    G4int GetZ() const { return fZ; } // ⭐ EKLENDİ

    // --- CONTROL METHODS ---
    void SetMode(G4int mode) { fMode = mode; } // 0 = 8 MeV, 1 = SH
    void SetZ(G4int Z) { fZ = Z; }             // ⭐ EKLENDİ

private:
    G4ParticleGun *fParticleGun;

    G4double fCurrentEnergyMeV;
    G4int fMode; // 0 = normal, 1 = superheavy Qα
    G4int fZ;    // atomic number (Z=114–126)

    // (Opsiyonel) Z’ye göre ortalama enerji fonksiyonu tanımlayabilirsin
    G4double ComputeMeanAlphaEnergy(G4int Z) const;
};

#endif