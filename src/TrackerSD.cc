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
/// \file TrackerSD.cc
/// \brief Implementation of the B2::TrackerSD class

#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"

#include "ObjManager.hh"

namespace B2
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  TrackerSD::TrackerSD(const G4String& name,
		       const G4String& hitsCollectionName)
    : G4VSensitiveDetector(name)
  {
    collectionName.insert(hitsCollectionName);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  TrackerSD::~TrackerSD()
  {}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void TrackerSD::Initialize(G4HCofThisEvent* hce)
  {
    // Create hits collection

    fHitsCollection
      = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);

    // Add this collection in hce

    G4int hcID
      = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection( hcID, fHitsCollection );
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  G4bool TrackerSD::ProcessHits(G4Step* aStep,
				G4TouchableHistory*)
  {
    // energy deposit
    G4double edep = aStep->GetTotalEnergyDeposit()/GeV;
    // if(edep == 0.) return false;

    Int_t copyNo = aStep->GetTrack()->GetVolume()->GetCopyNo();

    Int_t trkID = aStep->GetTrack()->GetTrackID();
    Int_t pdgID = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
    Int_t motherid = aStep->GetTrack()->GetParentID();
    const G4VProcess *process = aStep->GetTrack()->GetCreatorProcess();
    TString creatorProcess = "";
    if(process) {
      creatorProcess = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();}

    G4ThreeVector parmom = aStep->GetPreStepPoint()->GetMomentum();
    G4ThreeVector glbpos = aStep->GetPreStepPoint()->GetPosition();

    Hit* hit = ObjManager::Instance().event->AddHit();

    hit->edep = edep;
    // hit->sdcopytrk = copyNo;
    hit->pdg = pdgID;
    hit->trkid = trkID;
    hit->motherid = motherid;
    strcpy(hit->creatorProcess, creatorProcess.Data());
    hit->mom = parmom.mag()/GeV;
    hit->the = parmom.theta();
    hit->phi = parmom.phi();
    hit->vx = glbpos.x()/mm;
    hit->vy = glbpos.y()/mm;
    hit->vz = glbpos.z()/mm;

    // UInt_t nstep = ObjManager::Instance().nstep;
    // if(nstep < ObjManager::Instance().max_nstep) {
    //   ObjManager::Instance().edep[nstep] = edep;

    //   ObjManager::Instance().sdcopytrk[nstep] = copyNo;

    //   ObjManager::Instance().pdgout[nstep] = pdgID;
    //   ObjManager::Instance().trkid[nstep] = trkID;
    //   ObjManager::Instance().motherid[nstep] = motherid;
    //   strcpy(ObjManager::Instance().creatorProcess[nstep], creatorProcess.Data());

    //   ObjManager::Instance().momout[nstep] = parmom.mag()/GeV;
    //   ObjManager::Instance().theout[nstep] = parmom.theta();
    //   ObjManager::Instance().phiout[nstep] = parmom.phi();

    //   ObjManager::Instance().vxout[nstep] = glbpos.x()/mm;
    //   ObjManager::Instance().vyout[nstep] = glbpos.y()/mm;
    //   ObjManager::Instance().vzout[nstep] = glbpos.z()/mm;

    //   ObjManager::Instance().nstep++;
    // }

    TrackerHit* newHit = new TrackerHit();

    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
    newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()
			 ->GetCopyNumber());
    newHit->SetEdep(edep);
    newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());

    fHitsCollection->insert( newHit );

    //newHit->Print();

    return true;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void TrackerSD::EndOfEvent(G4HCofThisEvent*)
  {
    if ( verboseLevel>1 ) {
      G4int nofHits = fHitsCollection->entries();
      G4cout << G4endl
	     << "-------->Hits Collection: in this event they are " << nofHits
	     << " hits in the tracker chambers: " << G4endl;
      for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
    }
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

