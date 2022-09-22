
#ifndef OBJMANAGER__HH
#define OBJMANAGER__HH 1

#include <iostream>
#include <memory>
#include <map>
#include <optional>
#include <iomanip>
#include <utility>
#include <string>
#include <type_traits>
#include <vector>

#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TTree.h"

#include "globals.hh"

namespace B2
{
  class ObjManager {

  public:

    ObjManager();
    virtual ~ObjManager();

    /** Static referance to the singleton */
    static ObjManager& Instance();

    /** Open tfile */
    void OpenRootFiles();
    /** Write and Close tfile */
    void CloseRootFiles();

    /** Create Objects */
    void CreateObjects();

    /** Set Input File Name */
    void SetInputRootFile(G4String p) {input_title = p;}
    /** Set Output File Name */
    void SetOutputRootFile(G4String p) {output_title = p;}
    /** Set Collated File Name */
    void SetCollatedRootFile(G4String p) {collated_title = p;}

    G4String Print() {return "I am here";};

  private:

    /** Input Root File Name */
    G4String input_title;
    /** Output Root File Name */
    G4String output_title;
    /** Collated Root File Name */
    G4String collated_title;

    /** Input Root Files */
    TFile *ifile;
    /** Collated Root Files */
    TFile *cfile;
    /** Output Root Files */
    // std::unique_ptr<TFile> ofile;
    TFile *ofile;

    G4int isIntialized;

  public:

    /** Input Root Tree */
    TTree *itree;
    /** Collated Root Tree */
    TTree *ctree;
    /** Output Root Tree */
    TTree *otree;

    /*
      C : a character string terminated by the 0 character
      B : an 8 bit signed integer (Char_t)
      b : an 8 bit unsigned integer (UChar_t)
      S : a 16 bit signed integer (Short_t)
      s : a 16 bit unsigned integer (UShort_t)
      I : a 32 bit signed integer (Int_t)
      i : a 32 bit unsigned integer (UInt_t)
      F : a 32 bit floating point (Float_t)
      f : a 24 bit floating point with truncated mantissa (Float16_t)
      D : a 64 bit floating point (Double_t)
      d : a 24 bit truncated floating point (Double32_t)
      L : a 64 bit signed integer (Long64_t)
      l : a 64 bit unsigned integer (ULong64_t)
      G : a long signed integer, stored as 64 bit (Long_t)
      g : a long unsigned integer, stored as 64 bit (ULong_t)
      O : [the letter o, not a zero] a boolean (Bool_t)
    */

    /** Event ID */
    UInt_t eventID;

    /** Gen Info */
    Double_t vxin,
      vyin,
      vzin,
      momin,
      thein,
      phiin;
    UInt_t pdgin;

    /** Sim Info */
    const UInt_t max_npart = 500;
    UInt_t npart;
    Double_t edep[500],
      vxout[500],
      vyout[500],
      vzout[500],
      momout[500],
      theout[500],
      phiout[500];
    Int_t pdgout[500], sdcopytrk[500];
    Int_t trkid[500];
    Int_t motherid[500];
    char creatorProcess[500][100];
  };
}

#endif
