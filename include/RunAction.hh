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
/// \file RunAction.hh
/// \brief Definition of the B2::RunAction class

#ifndef B2RunAction_h
#define B2RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "ObjManager.hh"

class G4Run;

namespace B2
{

  /// Run action class

  class RunActionMessenger;

  class RunAction : public G4UserRunAction
  {
  public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run* run) override;
    void   EndOfRunAction(const G4Run* run) override;

    void SetRunID(G4int run_id) {run_ID = run_id;};

    void SetInputDirectory(G4String p) {  a_dir_title = p;}
    void SetOutputDirectory(G4String p) { r_dir_title = p;}

    void SetInputFile(G4String p) {  a_file_title = p;}
    void SetOutputFile(G4String p) { r_file_title = p;}

    void SetCollatedIn(G4int p) { collatedIn = p; }
    void SetCollatedFile(G4String p) { c_file_title = p; }
  
    void SetFirstEvt(G4int p) { FirstEvt = p;}

    void SetPartId(const int& p) {PDGEncoding=p;}

    void SetMomLowLimit(G4double p) {MomLowLim=p*GeV;}
    void SetMomUpLimit(G4double p) {MomUpLim=p*GeV;}

  private:

    // ObjManager *objManager;
    RunActionMessenger *fMessenger;
    
    G4String input_title;
    G4String output_title;
    G4String collated_title;
    G4String a_dir_title;
    G4String r_dir_title;
    G4String a_file_title;
    G4String r_file_title;
    G4String c_file_title;

    G4int run_no;
    G4int evt_no;
    G4int run_ID;

    G4int FirstEvt;
    G4int InputOutput;
    G4int collatedIn;
    G4int isVisOut;
    G4int isXtermOut;

    int PDGEncoding;
    G4double MomLowLim;
    G4double MomUpLim;
  };

}

#endif
