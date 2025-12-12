#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RandomTools.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include <cmath>

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fParticleGun(nullptr),
      fCurrentEnergyMeV(0.),
      fMode(1), // default: superheavy mode
      fZ(126)   // default Z=114
{
    // Alfa parçacığı üretecek particle gun
    fParticleGun = new G4ParticleGun(1);

    // Alfa parçacığı tanımı
    auto particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *alpha = particleTable->FindParticle("alpha");
    fParticleGun->SetParticleDefinition(alpha);

    // Kaynak pozisyonu
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

// ------------------------------------------------------------
//  Z → Qα enerji modeli
// ------------------------------------------------------------
G4double PrimaryGeneratorAction::ComputeMeanAlphaEnergy(G4int Z) const
{
    if (Z < 110)
        Z = 110;
    if (Z > 126)
        Z = 126;

    // Empirik model (literatüre uygun):
    //
    //   Qα(Z) = 9.5 MeV + 0.06*(Z - 110)
    //
    const G4double a = 9.5;  // baseline MeV
    const G4double b = 0.06; // MeV per Z unit

    return a + b * (Z - 110);
}

// ------------------------------------------------------------
//  PRIMARIES
// ------------------------------------------------------------
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    G4double meanE;
    G4double sigmaE;

    if (fMode == 0)
    {
        // Normal alfa kaynağı
        meanE = 8.0;
        sigmaE = 0.5;
    }
    else
    {
        // Superheavy regime → Z’ye göre hesapla
        meanE = ComputeMeanAlphaEnergy(fZ);
        sigmaE = 0.4;
    }

    // Gaussian sampling
    G4double sampledE = G4RandGauss::shoot(meanE, sigmaE);

    // Safety clamp
    if (sampledE < 5.0)
        sampledE = 5.0;
    if (sampledE > 15.0)
        sampledE = 15.0;

    fCurrentEnergyMeV = sampledE;

    // ParticleGun’a ayarla
    fParticleGun->SetParticleEnergy(sampledE * MeV);

    // İzotropik yön
    G4double cosTheta = 2.0 * G4UniformRand() - 1.0;
    G4double sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    G4double phi = 2 * CLHEP::pi * G4UniformRand();

    G4ThreeVector dir(
        sinTheta * std::cos(phi),
        sinTheta * std::sin(phi),
        cosTheta);

    fParticleGun->SetParticleMomentumDirection(dir);

    fParticleGun->GeneratePrimaryVertex(event);
}