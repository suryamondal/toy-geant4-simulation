#ifndef RUNACTIONMESSENGER__HH
#define RUNACTIONMESSENGER__HH 1

#include "G4UImessenger.hh"
#include "globals.hh"

// #include "RunAction.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;

namespace B2
{
  // class G4UIdirectory;
  class RunAction;

  class RunActionMessenger: public G4UImessenger
  {
  public:
    RunActionMessenger(RunAction*);
    virtual ~RunActionMessenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);

  private:
    RunAction * theRunAction;
    
    G4UIdirectory *             runDirectory;
    G4UIdirectory*              runDir;
    // G4UIcommand *               runIDCmd ;

    G4UIcmdWithAString*          InputDirCmd;
    G4UIcmdWithAString*          OutputDirCmd;
    G4UIcmdWithAString*          InputFileCmd;
    G4UIcmdWithAString*          OutputFileCmd;
    G4UIcmdWithAString*          CollatedFileCmd;
  
    G4UIcmdWithAnInteger*        FirstEvtCmd;

    G4UIcmdWithAnInteger*        PartIdCmd;
    G4UIcmdWithADouble*          MomLowLimitCmd;
    G4UIcmdWithADouble*          MomUpLimitCmd;
  };
}

#endif
