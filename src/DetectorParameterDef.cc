
#include "DetectorParameterDef.hh"
#include "TMath.h"

namespace B2
{

  DetectorParameterDef::DetectorParameterDef() {

    sliceDim[0] = 10*mm;
    sliceDim[1] = 5*mm;
    sliceDim[2] = 30*um;
    sliceN = 1;

    UpdateDetectorParameterDef();

  }

  void DetectorParameterDef::UpdateDetectorParameterDef() {

    worldDim[0] = sliceDim[0] * 1.1;
    worldDim[1] = sliceDim[1] * 1.1;
    worldDim[2] = sliceDim[2] * sliceN * 1.1;

    Dfront = worldDim[2] * 0.5 * 0.1;
  }

  DetectorParameterDef& DetectorParameterDef::Instance()
  {
    static DetectorParameterDef v;
    return v;
  }
}
