
#include "ObjManager.hh"

namespace B2
{

  ObjManager::ObjManager()
    : input_title(""), output_title(""), collated_title(""),
      eventID(0)
  {
    std::cout<<" ObjManager constructor called "<<std::endl;

    ifile = 0;
    cfile = 0;
    ofile = 0;
    itree = 0;
    ctree = 0;
    otree = 0;

    isIntialized = 0;
  }

  ObjManager::~ObjManager() {
    std::cout<<" ObjManager destructor called "<<std::endl;
  }

  ObjManager& ObjManager::Instance()
  {
    static ObjManager v;
    return v;
  }
  
  void ObjManager::OpenRootFiles() {
    if(!isIntialized) {

      if((!ifile || !ifile->IsOpen()) &&
	 input_title != "") {
	ifile = new TFile(input_title,"read");
	G4cout<<" input file: "<<input_title<<G4endl;}

      if(!ofile || !ofile->IsOpen()) {
	ofile = new TFile(output_title,"recreate");
	G4cout<<" output file: "<<output_title<<" "<<(ofile)<<G4endl;
      }

      if((!cfile || !cfile->IsOpen()) &&
	 collated_title != "") {
	cfile = new TFile(collated_title,"read");
	G4cout<<" collated file: "<<collated_title<<G4endl;}

      if(ofile && ofile->IsOpen()) {
	CreateObjects();
      }

      isIntialized = true;
    }

  }

  void ObjManager::CloseRootFiles() {
    if(ifile && ifile->IsOpen())
      ifile->Close();
    if(cfile && cfile->IsOpen())
      cfile->Close();
    if(ofile && ofile->IsOpen()) {
      G4cout<<" Closing tree at: "<<output_title<<" "<<(ofile)<<G4endl;
      ofile->Write();
      ofile->Purge();
      ofile->Close();
    }
  }

  void ObjManager::CreateObjects() {
    G4cout<<" setting tree at: "<<output_title<<" "<<(ofile)<<G4endl;
    // ofile->mkdir("ttrees");
    // ofile->cd("ttrees");
    ofile->cd();

    otree = new TTree("SDHits","Sensitive Detector Hits");
    otree->Branch("eventID",&eventID,"eventID/i");

    otree->Branch("pdgin",&pdgin,"pdgin/i");
    otree->Branch("momin",&momin,"momin/D");
    otree->Branch("thein",&thein,"thein/D");
    otree->Branch("phiin",&phiin,"phiin/D");
    otree->Branch("vxin",&vxin,"vxin/D");
    otree->Branch("vyin",&vyin,"vyin/D");
    otree->Branch("vzin",&vzin,"vzin/D");

    otree->Branch("npart",&npart,"npart/i");
    otree->Branch("trkSDcopy",sdcopytrk,"trkSDcopy[npart]/I");
    otree->Branch("trkpdg",pdgout,"trkpdg[npart]/I");
    otree->Branch("trkid",trkid,"trkid[npart]/I");
    otree->Branch("motherid",motherid,"motherid[npart]/I");
    otree->Branch("creatorProcess",creatorProcess,"creatorProcess[npart]/C");
    otree->Branch("trkedep",edep,"trkedep[npart]/D");
    otree->Branch("trkmom",momout,"trkmom[npart]/D");
    otree->Branch("trkthe",theout,"trkthe[npart]/D");
    otree->Branch("trkphi",phiout,"trkphi[npart]/D");
    otree->Branch("trkvx",vxout,"trkvx[npart]/D");
    otree->Branch("trkvy",vyout,"trkvy[npart]/D");
    otree->Branch("trkvz",vzout,"trkvz[npart]/D");
  }

}
