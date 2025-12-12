# AlphaDecaySim  
**Geant4-based Simulation & ROOT Analysis of Alpha Decay from Superheavy Elements**

![Geant4](https://img.shields.io/badge/Geant4-11.x-blue)
![ROOT](https://img.shields.io/badge/ROOT-6.x-orange)
![C++](https://img.shields.io/badge/C%2B%2B-Standard-success)
![Physics](https://img.shields.io/badge/Nuclear%20Physics-Alpha%20Decay-critical)

---

## 📌 Overview
**AlphaDecaySim** is a Monte Carlo simulation framework developed using **Geant4** to study the interaction of alpha particles emitted from **superheavy nuclei (Z = 114–126)** with various detector materials.

The project focuses on:
- Energy deposition behavior  
- Material-dependent stopping power  
- Survival probability of alpha particles  
- Comparative detector performance  
- Visualization of trends related to the **Island of Stability**

All simulation outputs are analyzed using **ROOT**, producing publication-quality figures.

---

## 🧪 Physics Motivation
Superheavy elements experience extreme Coulomb repulsion, making them highly unstable.  
However, nuclear shell effects predict an **Island of Stability**, where certain isotopes exhibit relatively longer lifetimes.

This project investigates:
- How alpha decay signatures vary with **proton number (Z)**
- How different detector materials respond to alpha particles
- Whether material response trends can indirectly reflect enhanced stability regions

---

## 🧱 Detector Materials
The following materials are implemented and compared:

- **Silicon (Si)**
- **Germanium (Ge)**
- **Gold (Au)**
- **Boron Nitride (BN)**
- **Diamond (C)**

Each material is evaluated under identical simulation conditions.

---

## ⚙️ Simulation Setup
- **Framework:** Geant4 (v11.x)
- **Physics List:** Standard EM (FTFP_BERT based)
- **Primary Particle:** Alpha (α)
- **Energy Range:** ~8–12 MeV (typical for SHE alpha decay)
- **Geometry:** Planar detector configuration
- **Statistics:** High-statistics Monte Carlo runs
- **Output Format:** ROOT (.root)

---

## 📊 Data Analysis (ROOT)
Simulation outputs are post-processed with ROOT to generate:

- **Alpha energy spectra**
- **dE/dx distributions**
- **Energy loss vs depth**
- **Topology scatter plots**
- **Survival probability curves**
- **Z-dependent trend plots**
- **Heatmaps and colormaps**

All figures are exported as **PNG and PDF**, suitable for academic publications.

## 🚀 Build & Run

mkdir build
cd build
cmake ..
make
./AlphaDecaySim run.mac

## 📈 Key Outcomes

Clear material-dependent energy loss behavior  
Strong correlation between proton number (Z) and alpha stopping power  
Quantitative comparison of detector efficiency  
Visual tools supporting Island of Stability discussions

## 📝 Applications

Nuclear physics research  
Detector material comparison  
Monte Carlo simulation studies  
Conference / journal publications  
Graduate-level research projects

## 🔬 Future Work

Beta decay and gamma interaction extensions  
Hybrid detector configurations  
ML-based pattern recognition on ROOT outputs  
Comparison with experimental datasets

---

## 📁 Project Structure
```text
AlphaDecaySim/
├── src/                # Geant4 source files
├── include/            # Header files
├── macros/             # Run macros
├── build/              # Build directory
├── data/
│   └── Z114–Z126/
│       └── Material/
│           ├── spectrum_*.root
│           ├── steps_*.root
│           └── survival_*.root
├── analysis/           # ROOT C++ analysis scripts
├── graphs/             # Generated figures (PNG / PDF)
└── README.md
```

## 👩‍💻 Author

Seval Hatice Kayıkcı  
Computer Engineering | Simulation & Modelling | Nuclear Physics  
GitHub: https://github.com/sevalkayikci

## 📜 License

This project is intended for academic and research use.
