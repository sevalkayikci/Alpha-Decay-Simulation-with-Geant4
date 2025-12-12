#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

#include "G4PhysListFactory.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "QGSP_BERT.hh" // veya FTFP_BERT

#ifdef G4UI_USE_QT
#include "G4UIExecutive.hh"
#endif

#include "G4VisExecutive.hh"

int main(int argc, char **argv)
{
    // 🔹 ARTIK MULTITHREAD YOK → SADECE TEK THREAD
    auto *runManager = new G4RunManager();

    // Zorunlu sınıflar
    runManager->SetUserInitialization(new DetectorConstruction());

    // Fizik listesi
    G4PhysListFactory factory;
    auto physList = factory.GetReferencePhysList("FTFP_BERT");
    runManager->SetUserInitialization(physList);

    // Actions
    runManager->SetUserInitialization(new ActionInitialization());

    // Visualization
    auto *visManager = new G4VisExecutive("warnings");
    visManager->Initialize();

    // UI manager
    auto *UImanager = G4UImanager::GetUIpointer();

#ifdef G4UI_USE_QT
    G4UIExecutive *ui = nullptr;

    if (argc == 1)
    {
        // Etkileşimli mod
        ui = new G4UIExecutive(argc, argv);

        // Görselle başlayalım
        UImanager->ApplyCommand("/control/execute vis.mac");

        ui->SessionStart();
        delete ui;
    }
    else
    {
        // Batch mod: komut satırından makro verilirse
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
#else
    // Qt yoksa: sadece batch mod
    if (argc > 1)
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
#endif

    delete visManager;
    delete runManager;

    return 0;
}
