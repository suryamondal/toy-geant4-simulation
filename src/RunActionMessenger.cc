#include "RunActionMessenger.hh"
#include "RunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include <sstream>
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"

namespace B2
{

  RunActionMessenger::RunActionMessenger(RunAction* aRunAction)
    :theRunAction(aRunAction)
  {
    runDirectory = new G4UIdirectory("/B2/");
    runDirectory->SetGuidance("UI commands of this example");

    runDir = new G4UIdirectory("/B2/run/");
    runDir->SetGuidance("RunAction control");

    // runIDCmd = new G4UIcommand("/B2/run/SetRunID",this);
    // runIDCmd->SetGuidance("Set run ID");
    // runIDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    // G4UIparameter* p1 = new G4UIparameter("runID",'i',true);
    // p1->SetDefaultValue(1000);
    // runIDCmd->SetParameter(p1);

    InputDirCmd = new G4UIcmdWithAString("/B2/run/input_dir",this);
    InputDirCmd->SetGuidance(" Input Directory name");
    InputDirCmd->SetParameterName("input_dir",true, true);
    InputDirCmd->SetDefaultValue("./");

    OutputDirCmd = new G4UIcmdWithAString("/B2/run/output_dir",this);
    OutputDirCmd->SetGuidance(" OutputFile name");
    OutputDirCmd->SetParameterName("output_dir",true, true);
    OutputDirCmd->SetDefaultValue("./");

    InputFileCmd = new G4UIcmdWithAString("/B2/run/input_file",this);
    InputFileCmd->SetGuidance(" InputFile name");
    InputFileCmd->SetParameterName("input_file",true, true);
    InputFileCmd->SetDefaultValue("input_file");

    OutputFileCmd = new G4UIcmdWithAString("/B2/run/output_file",this);
    OutputFileCmd->SetGuidance(" OutputFile name");
    OutputFileCmd->SetParameterName("output_file",true, true);
    OutputFileCmd->SetDefaultValue("output_file");

    CollatedFileCmd = new G4UIcmdWithAString("/B2/run/collated_input_file",this);
    CollatedFileCmd->SetGuidance("Collated InputFile name");
    CollatedFileCmd->SetParameterName("collated_input_file",true, true);
    CollatedFileCmd->SetDefaultValue("collated_input_file");

    FirstEvtCmd = new G4UIcmdWithAnInteger("/B2/run/firstEvt",this);
    FirstEvtCmd->SetGuidance("Starting points at nuance output file");
    FirstEvtCmd->SetParameterName("first_evt",true, true);
    FirstEvtCmd->SetDefaultValue(1);

  }

  RunActionMessenger::~RunActionMessenger() {
    // delete runIDCmd;
    delete runDirectory;
    delete runDir;
  }

  void RunActionMessenger::SetNewValue(G4UIcommand * command,G4String newValue) {
    // const char* nv = (const char*)newValue;
    // if( command==runIDCmd ) {
    //   G4int id;
    //   std::istringstream is(nv);
    //   is >> id;
    //   theRunAction->SetRunID(id);
    // }
    if( command == InputDirCmd )
      { theRunAction->SetInputDirectory(newValue);}
  
    if( command == OutputDirCmd )
      { theRunAction->SetOutputDirectory(newValue);}
  
    if( command == InputFileCmd )
      { theRunAction->SetInputFile(newValue);}
  
    if( command == OutputFileCmd )
      { theRunAction->SetOutputFile(newValue);}

    if( command == CollatedFileCmd )
      { theRunAction->SetCollatedFile(newValue);
	theRunAction->SetCollatedIn(1);} 
  
    if( command == FirstEvtCmd )
      { theRunAction->SetFirstEvt(FirstEvtCmd->GetNewIntValue(newValue));}  
  }
}
