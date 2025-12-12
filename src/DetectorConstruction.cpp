#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4Element.hh"

// ⭐ Buradan TARGET seçiyorsun (0–4)
#define TARGET_OPTION 4
// 0 = Silicon
// 1 = Germanium
// 2 = Gold
// 3 = Diamond (Carbon)
// 4 = Boron Nitride (BN)

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(),
      fMaterialName("Undefined")
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    auto nist = G4NistManager::Instance();

    // ======================
    // 1) WORLD (vacuum)
    // ======================
    G4double worldSize = 20 * cm;
    auto worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    auto solidWorld =
        new G4Box("World", worldSize / 2, worldSize / 2, worldSize / 2);

    auto logicWorld =
        new G4LogicalVolume(solidWorld, worldMat, "WorldLV");

    auto physWorld =
        new G4PVPlacement(nullptr, {}, logicWorld,
                          "WorldPV", nullptr, false, 0, true);

    // ======================
    // 2) TARGET MATERIAL SELECTION
    // ======================

    G4Material *targetMat = nullptr;

    if (TARGET_OPTION == 0)
    {
        targetMat = nist->FindOrBuildMaterial("G4_Si");
        fMaterialName = "Silicon";
    }
    else if (TARGET_OPTION == 1)
    {
        targetMat = nist->FindOrBuildMaterial("G4_Ge");
        fMaterialName = "Germanium";
    }
    else if (TARGET_OPTION == 2)
    {
        targetMat = nist->FindOrBuildMaterial("G4_Au");
        fMaterialName = "Gold";
    }
    else if (TARGET_OPTION == 3)
    {
        targetMat = nist->FindOrBuildMaterial("G4_C");
        fMaterialName = "Diamond";
    }
    else if (TARGET_OPTION == 4)
    {
        // Manual Boron Nitride
        G4Element *elB = new G4Element("Boron", "B", 5., 10.81 * g / mole);
        G4Element *elN = new G4Element("Nitrogen", "N", 7., 14.01 * g / mole);

        G4Material *BN = new G4Material("BoronNitride", 2.1 * g / cm3, 2);
        BN->AddElement(elB, 1);
        BN->AddElement(elN, 1);

        targetMat = BN;
        fMaterialName = "BoronNitride";
    }

    // ======================
    // 3) TARGET SLAB
    // ======================
    auto targetSizeXY = 10 * cm;
    auto targetThickness = 1 * cm;

    auto solidTarget =
        new G4Box("Target", targetSizeXY / 2, targetSizeXY / 2, targetThickness / 2);

    auto logicTarget =
        new G4LogicalVolume(solidTarget, targetMat, "TargetLV");

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        logicTarget,
        "TargetPV",
        logicWorld,
        false,
        0,
        true);

    return physWorld;
}