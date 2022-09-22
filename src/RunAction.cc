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
/// \file RunAction.cc
/// \brief Implementation of the B2::RunAction class

#include "RunAction.hh"
#include "RunActionMessenger.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

namespace B2
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  RunAction::RunAction()
    : fMessenger(0),
      input_title(""), output_title(""), collated_title(""),
      a_dir_title(""), r_dir_title(""),
      a_file_title(""), r_file_title("test_out"), c_file_title(""),
      collatedIn(0)
  {
    // set printing event number per each 100 events
    G4RunManager::GetRunManager()->SetPrintProgress(1000);
    // objManager = ObjManager::AnPointer;
    fMessenger = new RunActionMessenger(this);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  RunAction::~RunAction()
  {
    delete fMessenger;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void RunAction::BeginOfRunAction(const G4Run*)
  {
    //inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    if(a_file_title != "") {
      input_title = a_dir_title;
      input_title.append(a_file_title);
      input_title.append(".root");
    }

    if(r_file_title != "") {
      output_title = r_dir_title;
      output_title.append(r_file_title);
      output_title.append(".root");
    }

    if(collatedIn) {
      if(c_file_title != "") {
	collated_title.append(r_dir_title);
	collated_title.append(c_file_title);
	collated_title.append(".root");
      }
    }

    ObjManager::Instance().SetInputRootFile(input_title);
    ObjManager::Instance().SetOutputRootFile(output_title);
    ObjManager::Instance().SetCollatedRootFile(collated_title);
    ObjManager::Instance().OpenRootFiles();
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void RunAction::EndOfRunAction(const G4Run* )
  {
    // ObjManager::Instance().CloseRootFiles();
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

