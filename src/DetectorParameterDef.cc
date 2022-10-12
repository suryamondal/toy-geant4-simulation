
#include "DetectorParameterDef.hh"

namespace B2
{

  DetectorParameterDef::DetectorParameterDef() {

    sliceDim[0] = 10*cm;
    sliceDim[1] = 10*cm;
    sliceDim[2] = 1*mm;
    sliceN = 100;

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
