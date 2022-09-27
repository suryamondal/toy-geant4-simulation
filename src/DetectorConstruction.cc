//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the B2a::DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "TrackerSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4SubtractionSolid.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4UserLimits.hh"

#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"

namespace B2
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  G4ThreadLocal
  G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

  DetectorConstruction::DetectorConstruction()
    : worldPV(0)
  {
    fMessenger = new DetectorMessenger(this);

    fRegion = new G4Region("Target");
    G4ProductionCuts* cuts = new G4ProductionCuts();
    G4double defCut = 1*um;
    cuts->SetProductionCut(defCut,"gamma");
    cuts->SetProductionCut(defCut,"e-");
    cuts->SetProductionCut(defCut,"e+");
    cuts->SetProductionCut(defCut,"proton");
    fRegion->SetProductionCuts(cuts);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  DetectorConstruction::~DetectorConstruction()
  {
    if(fStepLimit) delete fStepLimit;
    delete fMessenger;
    delete fRegion;

    if(G10) delete G10;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  G4VPhysicalVolume* DetectorConstruction::Construct()
  {
    // Define materials
    DefineMaterials();

    // Define volumes
    return DefineVolumes();
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorConstruction::DefineMaterials()
  {
    // Material definition

    G4NistManager* nistManager = G4NistManager::Instance();
    G4int ncomponents, natoms;
    G4double fractionmass, density;

    // Air defined using NIST Manager
    nistManager->FindOrBuildMaterial("G4_AIR");

    G4Element* C = nistManager->FindOrBuildElement("C");
    G4Element* S = nistManager->FindOrBuildElement("S");
    G4Element* F = nistManager->FindOrBuildElement("F");
    G4Element* H = nistManager->FindOrBuildElement("H");
    G4Element* O = nistManager->FindOrBuildElement("O");
    G4Element* Si = nistManager->FindOrBuildElement("Si");

    Iron      = nistManager->FindOrBuildMaterial("G4_Fe");
    Copper    = nistManager->FindOrBuildMaterial("G4_Cu");
    Aluminium = nistManager->FindOrBuildMaterial("G4_Al");
    Air       = nistManager->FindOrBuildMaterial("G4_AIR");
    Silicon   = nistManager->FindOrBuildMaterial("G4_Si");

    // default target material
    TargetMaterial  = nistManager->FindOrBuildMaterial("G4_AIR");

    G10 = new G4Material("G10", density= 1.09*g/cm3, ncomponents=4);
    G10->AddElement(Si, natoms=1);
    G10->AddElement(O , natoms=2);
    G10->AddElement(C , natoms=3);
    G10->AddElement(H , natoms=3);

    // // Print materials
    // G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
  {

    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(DetectorParameterDef::Instance().GetWorldDim(2));

    G4cout << "Computed tolerance = "
	   << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
	   << " mm" << G4endl;

    G4Box* worldS
      = new G4Box("world",                                    //its name
		  DetectorParameterDef::Instance().GetWorldDim(0) * 0.5,
		  DetectorParameterDef::Instance().GetWorldDim(1) * 0.5,
		  DetectorParameterDef::Instance().GetWorldDim(2) * 0.5);
    // worldLength/2,worldLength/2,worldLength/2); //its size
    G4LogicalVolume* worldLV
      = new G4LogicalVolume(
			    worldS,   //its solid
			    Air,      //its material
			    "World"); //its name

    //  Must place the World Physical volume unrotated at (0,0,0).
    //
    worldPV
      = new G4PVPlacement(
			  0,               // no rotation
			  G4ThreeVector(), // at (0,0,0)
			  worldLV,         // its logical volume
			  "WorldPV",         // its name
			  0,               // its mother  volume
			  false,           // no boolean operations
			  0,               // copy number
			  fCheckOverlaps); // checking overlaps


    G4Box* envelopeS
      = new G4Box("envelope",                                    //its name
		  DetectorParameterDef::Instance().GetWorldDim(0) * 0.5,
		  DetectorParameterDef::Instance().GetWorldDim(1) * 0.5,
		  DetectorParameterDef::Instance().GetWorldDim(2) * 0.5);
    // envelopeLength/2,envelopeLength/2,envelopeLength/2); //its size
    G4LogicalVolume* envelopeLV
      = new G4LogicalVolume(
			    envelopeS,   //its solid
			    Air,      //its material
			    "Envelope"); //its name
    fRegion->AddRootLogicalVolume(envelopeLV);

    //  Must place the Envelope Physical volume unrotated at (0,0,0).
    //
    envelopePV
      = new G4PVPlacement(
			  0,               // no rotation
			  G4ThreeVector(), // at (0,0,0)
			  envelopeLV,         // its logical volume
			  "EnvelopePV",         // its name
			  worldLV,               // its mother  volume
			  false,           // no boolean operations
			  0,               // copy number
			  fCheckOverlaps); // checking overlaps



    // Build and Place slices


    G4Box* solidSliceBox =
      new G4Box("solidSliceBox",
		DetectorParameterDef::Instance().GetSliceDim(0) * 0.5,
		DetectorParameterDef::Instance().GetSliceDim(1) * 0.5,
		DetectorParameterDef::Instance().GetSliceDim(2) * 0.5);

    SliceLV =
      new G4LogicalVolume(solidSliceBox,
			  TargetMaterial,
			  "SliceLV");

    for(int ij=0; ij< DetectorParameterDef::Instance().GetSliceN(); ij++) {
      double xpos = 0;
      double ypos = 0;
      double zpos = - DetectorParameterDef::Instance().GetWorldDim(2) * 0.5 +
	DetectorParameterDef::Instance().GetFrontSpace() +
	DetectorParameterDef::Instance().GetSliceDim(2) * (ij + 0.5);
      G4ThreeVector position = G4ThreeVector(xpos, ypos, zpos);
      new G4PVPlacement(0,
			position,
			SliceLV,
			"SlicePV",
			envelopeLV,
			false,
			ij,
			fCheckOverlaps);
    }


    // Visualization attributes

    // if(!visGray){visGray=new G4VisAttributes(true,G4Colour(0.5,0.5,0.5));}
    // if(!visCyan){visCyan=new G4VisAttributes(true,G4Colour(0.0,1.0,1.0));}
    // if(!visBlue){visBlue=new G4VisAttributes(true, G4Colour(0.0,0.0,1.0));}
    // if(!visMagenta){visMagenta=new G4VisAttributes(true,G4Colour(1.0,0.0,1.0));
    //   visMagenta->SetForceSolid(true);}
    // if(!visNull){visNull=new G4VisAttributes();}

    G4VisAttributes* visNull= new G4VisAttributes();
    G4VisAttributes* visWhite= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    G4VisAttributes* visYellow= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    G4VisAttributes* visGreen= new G4VisAttributes(G4Colour(0.0,1.0,0.0));
    G4VisAttributes* visRed= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    // G4VisAttributes* chamberVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));

    worldLV  ->SetVisAttributes(visNull);
    SliceLV   ->SetVisAttributes(visRed);


    // Example of User Limits
    //
    // Below is an example of how to set tracking constraints in a given
    // logical volume
    //
    // Sets a max step length in the tracker region, with G4StepLimiter

    // G4double maxStep = 0.5*chamberWidth;
    // fStepLimit = new G4UserLimits(maxStep);
    // trackerLV->SetUserLimits(fStepLimit);

    /// Set additional contraints on the track, with G4UserSpecialCuts
    ///
    /// G4double maxLength = 2*trackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
    /// trackerLV->SetUserLimits(new G4UserLimits(maxStep,
    ///                                           maxLength,
    ///                                           maxTime,
    ///                                           minEkin));

    // Always return the physical world

    return worldPV;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorConstruction::ConstructSDandField()
  {
    // Sensitive detectors

    G4String sliceChamberSDname = "/TrackerChamberSD";
    TrackerSD* aTrackerSD = new TrackerSD(sliceChamberSDname,
			      "TrackerHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
    SetSensitiveDetector("SliceLV", aTrackerSD, true);

    // Create global magnetic field messenger.
    // Uniform magnetic field is then created automatically if
    // the field value is not zero.
    G4ThreeVector fieldValue = G4ThreeVector(0,0,0);
    fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
    fMagFieldMessenger->SetVerboseLevel(1);

    // Register the field messenger for deleting
    G4AutoDelete::Register(fMagFieldMessenger);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorConstruction::SetTargetMaterial(G4String materialName)
  {
    G4NistManager* nistManager = G4NistManager::Instance();

    G4Material* pttoMaterial =
      nistManager->FindOrBuildMaterial(materialName);

    if (TargetMaterial != pttoMaterial) {
      if ( pttoMaterial ) {
        TargetMaterial = pttoMaterial;
	if (SliceLV) SliceLV->SetMaterial(TargetMaterial);
	G4cout<<" Target Material: "<<TargetMaterial->GetName()<<G4endl;
      } else {
        G4cout
          << G4endl
          << "-->  WARNING from SetTargetMaterial : "
          << materialName << " not found" << G4endl;
      }
    }
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorConstruction::SetChamberMaterial(G4String materialName)
  {}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorConstruction::SetMaxStep(G4double maxStep)
  {
    if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
  {
    fCheckOverlaps = checkOverlaps;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
