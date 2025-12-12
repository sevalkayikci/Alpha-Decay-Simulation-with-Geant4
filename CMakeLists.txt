cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(AlphaDecaySim)

# Geant4
find_package(Geant4 REQUIRED ui vis)

# ROOT
find_package(ROOT REQUIRED COMPONENTS Hist Tree)

# Geant4 ayarlarını al
include(${Geant4_USE_FILE})

# Include dizinleri
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${ROOT_INCLUDE_DIRS}
)

# Kaynak dosyaları
set(SOURCES
  src/main.cpp
  src/DetectorConstruction.cpp
  src/PrimaryGeneratorAction.cpp
  src/RunAction.cpp
  src/EventAction.cpp
  src/SteppingAction.cpp
  src/ActionInitialization.cpp
)

add_executable(AlphaDecaySim ${SOURCES})

# Geant4 + ROOT kütüphaneleriyle linkle
target_link_libraries(AlphaDecaySim
  ${Geant4_LIBRARIES}
  ${ROOT_LIBRARIES}
)

# Çıktı dizinini biraz düzenli yapalım
set_target_properties(AlphaDecaySim PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)
