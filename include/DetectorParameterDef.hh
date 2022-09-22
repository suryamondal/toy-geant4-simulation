#ifndef DETECTORPARAMETERDEF__HH
#define DETECTORPARAMETERDEF__HH 1

#include<iostream>

#include "G4SystemOfUnits.hh"

namespace B2
{

  class DetectorParameterDef {

  public:

    DetectorParameterDef();
    ~DetectorParameterDef() {};

    /** Static referance to the singleton */
    static DetectorParameterDef& Instance();
    // static DetectorParameterDef* AnPointer;
  
    /** Derived parameters */
    void UpdateDetectorParameterDef();

    double GetWorldDim(const int& ij) const {return worldDim[ij];}

    double GetFrontSpace() const {return Dfront;}

    int GetSliceN() const {return sliceN;}
    double GetSliceDim(const int& ij) const {return sliceDim[ij];}

  private:

    /** world dimension */
    double worldDim[3];

    /** space in front */
    double Dfront;

    /** slice parameters */
    double sliceDim[3];
    int sliceN;

  };
}
#endif
