#ifndef ROOT_EventHit
#define ROOT_EventHit

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// EventHit                                                             //
//                                                                      //
// Description of the event and track parameters                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TBits.h"
#include "TMath.h"
#include "TTimeStamp.h"

namespace B2
{

  class EventHit : public TObject {

  public:

    Int_t layerid, nX, nY;
    Double_t edep,
      vx, vy,
      vz, mom,
      the, phi;
    Int_t pdg, trkid, motherid;
    char creatorProcess[100];

  public:
    EventHit() {
      layerid = 0; nX = 0; nY = 0;
      edep = 0;
      vx = 0; vy = 0; vz = 0;
      mom = 0; the = 0; phi = 0;
      pdg = 0; trkid = 0; motherid = 0;
      sprintf(creatorProcess,"%s","");
    }
    virtual ~EventHit() { }

    ClassDef(EventHit,1)  //A track hit
  };

}
#endif
