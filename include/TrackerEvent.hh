#ifndef ROOT_TrackerEvent
#define ROOT_TrackerEvent

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TrackerEvent                                                         //
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

  class Hits : public TObject {

  public:

    Int_t layerid, nX, nY;
    Double_t edep,
      vx, vy,
      vz, mom,
      the, phi;
    Int_t pdg, trkid, motherid;
    char creatorProcess[100];

  public:
    Hits() {
      layerid = 0; nX = 0; nY = 0;
      edep = 0;
      vx = 0; vy = 0; vz = 0;
      mom = 0; the = 0; phi = 0;
      pdg = 0; trkid = 0; motherid = 0;
      sprintf(creatorProcess,"%s","");
    }
    virtual ~Hits() { }

    // ClassDef(Hits,1)  //A track hit
  };

  // class Track : public TObject {

  // public:
  //   Double_t     fPx;           //X component of the momentum
  //   Double_t     fPy;           //Y component of the momentum
  //   Double_t     fPz;           //Z component of the momentum
  //   Int_t        fNhit;         //Number of hits for this track
  //   TRefArray    fHits;         //List of Hits for this track

  // public:
  //   Track() { }
  //   virtual ~Track() { }
  //   Int_t         GetNhit() const { return fNhit; }
  //   TRefArray   &GetHits()  {return fHits; }

  //   // ClassDef(Track,1)  //A track segment
  // };


  // class Jet : public TObject {

  // public:
  //   Double_t   fPt;       //Pt of jet
  //   Double_t   fPhi;      //Phi of jet
  //   TRefArray  fTracks;   //List of tracks in the jet

  // public:
  //   Jet() { }
  //   virtual ~Jet(){ }
  //   TRefArray   &GetTracks() {return fTracks; }

  //   // ClassDef(Jet,1)  //Jet class
  // };

  class TrackerEvent : public TObject {

  private:
    // TVector3       fVertex;            //vertex coordinates
    // Int_t          fNjet;              //Number of jets
    // Int_t          fNtrack;            //Number of tracks
    Int_t          fNhit;             //Number of hist in detector A
    // TClonesArray  *fJets;              //->array with all jets
    // TClonesArray  *fTracks;            //->array with all tracks
    TClonesArray  *fHits;             //->array of hits in detector A

    // static TClonesArray *fgJets;
    // static TClonesArray *fgTracks;
    static TClonesArray *fgHits;

  public:
    TrackerEvent();
    virtual ~TrackerEvent();
    // void          Build(Int_t jetm=3, Int_t trackm=10, Int_t hitam=100, Int_t hitbm=10);
    void          Clear(Option_t *option ="");
    void          ClearAll();
    void          Reset(Option_t *option ="");
    // Int_t         GetNjet()   const { return fNjet; }
    // Int_t         GetNtrack() const { return fNtrack; }
    Int_t         GetNhit()  const { return fNhit; }
    TClonesArray *GetHits()  const { return fHits; }
    // Jet          *AddJet();
    // Track        *AddTrack();
    Hits          *AddHit();
    // TClonesArray *GetJets() const { return fJets; }

    // ClassDef(TrackerEvent,1)  //Event structure
  };

}
#endif
