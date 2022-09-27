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
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the B2::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "DetectorParameterDef.hh"
#include "Randomize.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "ObjManager.hh"

namespace B2
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  PrimaryGeneratorAction::PrimaryGeneratorAction()
  {
    G4int nofParticles = 1;
    fParticleGun = new G4ParticleGun(nofParticles);

    // default particle kinematic

    // G4ParticleDefinition* particleDefinition
    //   = G4ParticleTable::GetParticleTable()->FindParticle("proton");

    // fParticleGun->SetParticleDefinition(particleDefinition);
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    // fParticleGun->SetParticleEnergy(3.0*GeV);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  PrimaryGeneratorAction::~PrimaryGeneratorAction()
  {
    delete fParticleGun;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
  {
    // This function is called at the begining of event

    // Note that this particular case of starting a primary particle on the world boundary
    // requires shooting in a direction towards inside the world.

    int ngent = fParticleGun->GetNumberOfParticles();
    for (int ij=0; ij<ngent; ij++) {

      // G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      // G4ParticleDefinition* particle = particleTable->FindParticle(ObjManager::Instance().GetPDGEncoding());
      // fParticleGun->SetParticleDefinition(particle);

      double posz = - DetectorParameterDef::Instance().GetWorldDim(2) * 0.5 +
	DetectorParameterDef::Instance().GetFrontSpace();
      double posx = 0;
      double posy = 0;
      // double beamspot = 0.5* DetectorParameterDef::Instance().GetBeamSpotDia();
      // double posx = beamspot*2.;
      // double posy = beamspot*2.;
      // while(std::sqrt((posx*posx) + (posy*posy)) > beamspot) {
      // 	posx = beamspot*2.*(0.5-G4UniformRand());
      // 	posy = beamspot*2.*(0.5-G4UniformRand());
      // }

      // Setting momentum

      G4double energy =
	ObjManager::Instance().GetMomLowLimit() +
	(ObjManager::Instance().GetMomUpLimit() - ObjManager::Instance().GetMomLowLimit()) *
	G4UniformRand();

      fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
      fParticleGun->SetParticleEnergy(energy);
      fParticleGun->SetParticlePosition(G4ThreeVector(posx, posy, posz));

      ObjManager::Instance().pdgin = fParticleGun->GetParticleDefinition()->GetPDGEncoding();

      ObjManager::Instance().momin = (fParticleGun->GetParticleDefinition()->GetPDGCharge() *
				      fParticleGun->GetParticleMomentum())/GeV;
      ObjManager::Instance().thein = fParticleGun->GetParticleMomentumDirection().theta();
      ObjManager::Instance().phiin = fParticleGun->GetParticleMomentumDirection().phi();

      ObjManager::Instance().vxin = fParticleGun->GetParticlePosition().x()/mm;
      ObjManager::Instance().vyin = fParticleGun->GetParticlePosition().y()/mm;
      ObjManager::Instance().vzin = fParticleGun->GetParticlePosition().z()/mm;

      fParticleGun->GeneratePrimaryVertex(anEvent);
    }
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

