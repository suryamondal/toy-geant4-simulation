// A TrackerEvent emulates 2 detectors A and B producing each
// a TClonesArray of Hit objects.
// A TClonesArray  of Track objects is built with Hits objects
// of detectors A and B. Eack Track object has a TRefArray of hits.
// A TClonesArray of Jets is made with a subset of the Track objects
// also stored in a TRefArray.
// see $ROOTSYS/tutorials/jets.C for an example creating a Tree
// with TrackerEvents.
 
#include "TMath.h"
#include "TRandom.h"
#include "TrackerEvent.h"

// TClonesArray *TrackerEvent::fgJets   = 0;
// TClonesArray *TrackerEvent::fgTracks = 0;
TClonesArray *TrackerEvent::fgHits  = 0;

////////////////////////////////////////////////////////////////////////////////
/// Create a TrackerEvent object.
/// When the constructor is invoked for the first time, the class static
/// variables fgxxx are 0 and the TClonesArray fgxxx are created.

TrackerEvent::TrackerEvent()
{
  // if (!fgTracks) fgTracks = new TClonesArray("Track", 100);
  // if (!fgJets)   fgJets   = new TClonesArray("Jet", 10);
  if (!fgHits)  fgHits  = new TClonesArray("Hit", 10000);
  // fJets   = fgJets;
  // fTracks = fgTracks;
  fHits  = fgHits;
  // fHitsB  = fgHitsB;
}

////////////////////////////////////////////////////////////////////////////////

TrackerEvent::~TrackerEvent()
{
  Reset();
}

////////////////////////////////////////////////////////////////////////////////
///Build one event

// void TrackerEvent::Build(Int_t jetm, Int_t trackm, Int_t hitam, Int_t hitbm) {
//   //Save current Object count
//   Int_t ObjectNumber = TProcessID::GetObjectCount();
//   Clear();

//   Hit *hit;
//   Track *track;
//   Jet *jet;
//   fNjet   = fNtrack = fNhitA  = fNhitB  = 0;

//   fVertex.SetXYZ(gRandom->Gaus(0,0.1),
// 		 gRandom->Gaus(0,0.2),
// 		 gRandom->Gaus(0,10));

//   Int_t njets = (Int_t)gRandom->Gaus(jetm,1); if (njets < 1) njets = 1;
//   for (Int_t j=0;j<njets;j++) {
//     jet = AddJet();
//     jet->fPt = gRandom->Gaus(0,10);
//     jet->fPhi = 2*TMath::Pi()*gRandom->Rndm();
//     Int_t ntracks = (Int_t)gRandom->Gaus(trackm,3); if (ntracks < 1) ntracks = 1;
//     for (Int_t t=0;t<ntracks;t++) {
//       track = AddTrack();
//       track->fPx = gRandom->Gaus(0,1);
//       track->fPy = gRandom->Gaus(0,1);
//       track->fPz = gRandom->Gaus(0,5);
//       jet->fTracks.Add(track);
//       Int_t nhitsA = (Int_t)gRandom->Gaus(hitam,5);
//       for (Int_t ha=0;ha<nhitsA;ha++) {
// 	hit = AddHitA();
// 	hit->fX = 10000*j + 100*t +ha;
// 	hit->fY = 10000*j + 100*t +ha+0.1;
// 	hit->fZ = 10000*j + 100*t +ha+0.2;
// 	track->fHits.Add(hit);
//       }
//       Int_t nhitsB = (Int_t)gRandom->Gaus(hitbm,2);
//       for (Int_t hb=0;hb<nhitsB;hb++) {
// 	hit = AddHitB();
// 	hit->fX = 20000*j + 100*t +hb+0.3;
// 	hit->fY = 20000*j + 100*t +hb+0.4;
// 	hit->fZ = 20000*j + 100*t +hb+0.5;
// 	track->fHits.Add(hit);
//       }
//       track->fNhit = nhitsA + nhitsB;
//     }
//   }
//   //Restore Object count
//   //To save space in the table keeping track of all referenced objects
//   //we assume that our events do not address each other. We reset the
//   //object count to what it was at the beginning of the event.
//   TProcessID::SetObjectCount(ObjectNumber);
// }


////////////////////////////////////////////////////////////////////////////////
/// Add a new Jet to the list of tracks for this event.

// Jet *TrackerEvent::AddJet()
// {
//   TClonesArray &jets = *fJets;
//   Jet *jet = new(jets[fNjet++]) Jet();
//   return jet;
// }


////////////////////////////////////////////////////////////////////////////////
/// Add a new track to the list of tracks for this event.

// Track *TrackerEvent::AddTrack()
// {
//   TClonesArray &tracks = *fTracks;
//   Track *track = new(tracks[fNtrack++]) Track();
//   return track;
// }


////////////////////////////////////////////////////////////////////////////////
/// Add a new hit to the list of hits in detector A

Hit *TrackerEvent::AddHit()
{
  TClonesArray &hits = *fHits;
  Hit *hit = new(hits[fNhit++]) Hit();
  return hit;
}

////////////////////////////////////////////////////////////////////////////////

void TrackerEvent::Clear(Option_t *option)
{
  // fJets->Clear(option);
  // fTracks->Clear(option);
  fHits->Clear(option);
}

////////////////////////////////////////////////////////////////////////////////
/// Static function to reset all static objects for this event

void TrackerEvent::Reset(Option_t *)
{
  // delete fgJets;   fgJets = 0;
  // delete fgTracks; fgTracks = 0;
  delete fgHits;  fgHits = 0;
}

