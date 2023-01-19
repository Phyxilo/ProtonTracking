//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov  4 00:10:11 2022 by ROOT version 6.26/04
// from TTree tracks/tracks
// found on file: linked_tracks.root
//////////////////////////////////////////////////////////

#ifndef linked_tracks_h
#define linked_tracks_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"

extern int dirIndex;
char ltDir [128] = "pl001_030/linked_tracks.root";

class linked_tracks {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxt = 1;
   static constexpr Int_t kMaxs = 30;
   static constexpr Int_t kMaxsf = 30;

   // Declaration of leaf types
   Int_t           trid;
   Int_t           nseg;
   Int_t           npl;
   Int_t           n0;
   Float_t         xv;
   Float_t         yv;
   Float_t         w;
   //EdbSegP         *t_;
   Int_t           s_;
   UInt_t          s_fUniqueID[kMaxs];   //[s_]
   UInt_t          s_fBits[kMaxs];   //[s_]
   //EdbSegP         *s_EdbTrack2D;
   Int_t           s_ePID[kMaxs];   //[s_]
   Int_t           s_eID[kMaxs];   //[s_]
   Int_t           s_eVid[kMaxs][2];   //[s_]
   Int_t           s_eAid[kMaxs][2];   //[s_]
   Int_t           s_eFlag[kMaxs];   //[s_]
   Int_t           s_eTrack[kMaxs];   //[s_]
   Float_t         s_eX[kMaxs];   //[s_]
   Float_t         s_eY[kMaxs];   //[s_]
   Float_t         s_eZ[kMaxs];   //[s_]
   Float_t         s_eTX[kMaxs];   //[s_]
   Float_t         s_eTY[kMaxs];   //[s_]
   Float_t         s_eSZ[kMaxs];   //[s_]
   Float_t         s_eChi2[kMaxs];   //[s_]
   Float_t         s_eProb[kMaxs];   //[s_]
   Float_t         s_eW[kMaxs];   //[s_]
   Float_t         s_eVolume[kMaxs];   //[s_]
   Float_t         s_eDZ[kMaxs];   //[s_]
   Float_t         s_eDZem[kMaxs];   //[s_]
   Float_t         s_eP[kMaxs];   //[s_]
   Int_t           s_eMCTrack[kMaxs];   //[s_]
   Int_t           s_eMCEvt[kMaxs];   //[s_]
   //EdbID           s_eScanID[kMaxs];
   Int_t           sf_;
   UInt_t          sf_fUniqueID[kMaxsf];   //[sf_]
   UInt_t          sf_fBits[kMaxsf];   //[sf_]
   //EdbSegP         *sf_EdbTrack2D;
   Int_t           sf_ePID[kMaxsf];   //[sf_]
   Int_t           sf_eID[kMaxsf];   //[sf_]
   Int_t           sf_eVid[kMaxsf][2];   //[sf_]
   Int_t           sf_eAid[kMaxsf][2];   //[sf_]
   Int_t           sf_eFlag[kMaxsf];   //[sf_]
   Int_t           sf_eTrack[kMaxsf];   //[sf_]
   Float_t         sf_eX[kMaxsf];   //[sf_]
   Float_t         sf_eY[kMaxsf];   //[sf_]
   Float_t         sf_eZ[kMaxsf];   //[sf_]
   Float_t         sf_eTX[kMaxsf];   //[sf_]
   Float_t         sf_eTY[kMaxsf];   //[sf_]
   Float_t         sf_eSZ[kMaxsf];   //[sf_]
   Float_t         sf_eChi2[kMaxsf];   //[sf_]
   Float_t         sf_eProb[kMaxsf];   //[sf_]
   Float_t         sf_eW[kMaxsf];   //[sf_]
   Float_t         sf_eVolume[kMaxsf];   //[sf_]
   Float_t         sf_eDZ[kMaxsf];   //[sf_]
   Float_t         sf_eDZem[kMaxsf];   //[sf_]
   Float_t         sf_eP[kMaxsf];   //[sf_]
   Int_t           sf_eMCTrack[kMaxsf];   //[sf_]
   Int_t           sf_eMCEvt[kMaxsf];   //[sf_]
   //EdbID           sf_eScanID[kMaxsf];

   // List of branches
   TBranch        *b_trid;   //!
   TBranch        *b_nseg;   //!
   TBranch        *b_npl;   //!
   TBranch        *b_n0;   //!
   TBranch        *b_xv;   //!
   TBranch        *b_yv;   //!
   TBranch        *b_w;   //!
   TBranch        *b_t_;   //!
   TBranch        *b_s_;   //!
   TBranch        *b_s_fUniqueID;   //!
   TBranch        *b_s_fBits;   //!
   TBranch        *b_s_ePID;   //!
   TBranch        *b_s_eID;   //!
   TBranch        *b_s_eVid;   //!
   TBranch        *b_s_eAid;   //!
   TBranch        *b_s_eFlag;   //!
   TBranch        *b_s_eTrack;   //!
   TBranch        *b_s_eX;   //!
   TBranch        *b_s_eY;   //!
   TBranch        *b_s_eZ;   //!
   TBranch        *b_s_eTX;   //!
   TBranch        *b_s_eTY;   //!
   TBranch        *b_s_eSZ;   //!
   TBranch        *b_s_eChi2;   //!
   TBranch        *b_s_eProb;   //!
   TBranch        *b_s_eW;   //!
   TBranch        *b_s_eVolume;   //!
   TBranch        *b_s_eDZ;   //!
   TBranch        *b_s_eDZem;   //!
   TBranch        *b_s_eP;   //!
   TBranch        *b_s_eMCTrack;   //!
   TBranch        *b_s_eMCEvt;   //!
   TBranch        *b_sf_;   //!
   TBranch        *b_sf_fUniqueID;   //!
   TBranch        *b_sf_fBits;   //!
   TBranch        *b_sf_ePID;   //!
   TBranch        *b_sf_eID;   //!
   TBranch        *b_sf_eVid;   //!
   TBranch        *b_sf_eAid;   //!
   TBranch        *b_sf_eFlag;   //!
   TBranch        *b_sf_eTrack;   //!
   TBranch        *b_sf_eX;   //!
   TBranch        *b_sf_eY;   //!
   TBranch        *b_sf_eZ;   //!
   TBranch        *b_sf_eTX;   //!
   TBranch        *b_sf_eTY;   //!
   TBranch        *b_sf_eSZ;   //!
   TBranch        *b_sf_eChi2;   //!
   TBranch        *b_sf_eProb;   //!
   TBranch        *b_sf_eW;   //!
   TBranch        *b_sf_eVolume;   //!
   TBranch        *b_sf_eDZ;   //!
   TBranch        *b_sf_eDZem;   //!
   TBranch        *b_sf_eP;   //!
   TBranch        *b_sf_eMCTrack;   //!
   TBranch        *b_sf_eMCEvt;   //!

   linked_tracks(TTree *tree=0);
   virtual ~linked_tracks();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void SubVol(int SVIndex);
};

#endif

#ifdef linked_tracks_cxx

linked_tracks::linked_tracks(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

   SubVol(dirIndex);
   //cout << dirIndex << endl;
   
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(ltDir);
      
      if (!f || !f->IsOpen()) {
         f = new TFile(ltDir);
      }
      f->GetObject("tracks",tree);

   }
   Init(tree);
}

linked_tracks::~linked_tracks()
{
   if (!fChain) return;
   //cout << "1" << endl;
   delete fChain->GetCurrentFile();
}

Int_t linked_tracks::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   //cout << "2" << endl;
   return fChain->GetEntry(entry);
}
Long64_t linked_tracks::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   //cout << "3" << endl;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void linked_tracks::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   //t_ = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   //cout << "5" << endl;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("trid", &trid, &b_trid);
   fChain->SetBranchAddress("nseg", &nseg, &b_nseg);
   fChain->SetBranchAddress("npl", &npl, &b_npl);
   fChain->SetBranchAddress("n0", &n0, &b_n0);
   fChain->SetBranchAddress("xv", &xv, &b_xv);
   fChain->SetBranchAddress("yv", &yv, &b_yv);
   fChain->SetBranchAddress("w", &w, &b_w);
   //fChain->SetBranchAddress("t.", &t_, &b_t_);
   fChain->SetBranchAddress("s", &s_, &b_s_);
   fChain->SetBranchAddress("s.fUniqueID", s_fUniqueID, &b_s_fUniqueID);
   fChain->SetBranchAddress("s.fBits", s_fBits, &b_s_fBits);
   fChain->SetBranchAddress("s.ePID", s_ePID, &b_s_ePID);
   fChain->SetBranchAddress("s.eID", s_eID, &b_s_eID);
   fChain->SetBranchAddress("s.eVid[2]", s_eVid, &b_s_eVid);
   fChain->SetBranchAddress("s.eAid[2]", s_eAid, &b_s_eAid);
   fChain->SetBranchAddress("s.eFlag", s_eFlag, &b_s_eFlag);
   fChain->SetBranchAddress("s.eTrack", s_eTrack, &b_s_eTrack);
   fChain->SetBranchAddress("s.eX", s_eX, &b_s_eX);
   fChain->SetBranchAddress("s.eY", s_eY, &b_s_eY);
   fChain->SetBranchAddress("s.eZ", s_eZ, &b_s_eZ);
   fChain->SetBranchAddress("s.eTX", s_eTX, &b_s_eTX);
   fChain->SetBranchAddress("s.eTY", s_eTY, &b_s_eTY);
   fChain->SetBranchAddress("s.eSZ", s_eSZ, &b_s_eSZ);
   fChain->SetBranchAddress("s.eChi2", s_eChi2, &b_s_eChi2);
   fChain->SetBranchAddress("s.eProb", s_eProb, &b_s_eProb);
   fChain->SetBranchAddress("s.eW", s_eW, &b_s_eW);
   fChain->SetBranchAddress("s.eVolume", s_eVolume, &b_s_eVolume);
   fChain->SetBranchAddress("s.eDZ", s_eDZ, &b_s_eDZ);
   fChain->SetBranchAddress("s.eDZem", s_eDZem, &b_s_eDZem);
   fChain->SetBranchAddress("s.eP", s_eP, &b_s_eP);
   fChain->SetBranchAddress("s.eMCTrack", s_eMCTrack, &b_s_eMCTrack);
   fChain->SetBranchAddress("s.eMCEvt", s_eMCEvt, &b_s_eMCEvt);
   fChain->SetBranchAddress("sf", &sf_, &b_sf_);
   fChain->SetBranchAddress("sf.fUniqueID", sf_fUniqueID, &b_sf_fUniqueID);
   fChain->SetBranchAddress("sf.fBits", sf_fBits, &b_sf_fBits);
   fChain->SetBranchAddress("sf.ePID", sf_ePID, &b_sf_ePID);
   fChain->SetBranchAddress("sf.eID", sf_eID, &b_sf_eID);
   fChain->SetBranchAddress("sf.eVid[2]", sf_eVid, &b_sf_eVid);
   fChain->SetBranchAddress("sf.eAid[2]", sf_eAid, &b_sf_eAid);
   fChain->SetBranchAddress("sf.eFlag", sf_eFlag, &b_sf_eFlag);
   fChain->SetBranchAddress("sf.eTrack", sf_eTrack, &b_sf_eTrack);
   fChain->SetBranchAddress("sf.eX", sf_eX, &b_sf_eX);
   fChain->SetBranchAddress("sf.eY", sf_eY, &b_sf_eY);
   fChain->SetBranchAddress("sf.eZ", sf_eZ, &b_sf_eZ);
   fChain->SetBranchAddress("sf.eTX", sf_eTX, &b_sf_eTX);
   fChain->SetBranchAddress("sf.eTY", sf_eTY, &b_sf_eTY);
   fChain->SetBranchAddress("sf.eSZ", sf_eSZ, &b_sf_eSZ);
   fChain->SetBranchAddress("sf.eChi2", sf_eChi2, &b_sf_eChi2);
   fChain->SetBranchAddress("sf.eProb", sf_eProb, &b_sf_eProb);
   fChain->SetBranchAddress("sf.eW", sf_eW, &b_sf_eW);
   fChain->SetBranchAddress("sf.eVolume", sf_eVolume, &b_sf_eVolume);
   fChain->SetBranchAddress("sf.eDZ", sf_eDZ, &b_sf_eDZ);
   fChain->SetBranchAddress("sf.eDZem", sf_eDZem, &b_sf_eDZem);
   fChain->SetBranchAddress("sf.eP", sf_eP, &b_sf_eP);
   fChain->SetBranchAddress("sf.eMCTrack", sf_eMCTrack, &b_sf_eMCTrack);
   fChain->SetBranchAddress("sf.eMCEvt", sf_eMCEvt, &b_sf_eMCEvt);
   Notify();
}

Bool_t linked_tracks::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void linked_tracks::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t linked_tracks::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void linked_tracks::SubVol(int SVIndex)
{
   //char dir [128] = "pl001_";
   sprintf(ltDir,"pl0%d1_%02d0/linked_tracks.root", SVIndex, SVIndex+3);
   /*
   sprintf(dir,"pl0%d1_", SVIndex);

   string path = "/Users/emin/Desktop/Workspace/ProtonTracking/Geant4";
   for (const auto & entry : fs::directory_iterator(path))
   {
      string dirs = entry.path();
      if (dirs.find(dir) != std::string::npos)
      {
         char* cArr = new char[128];
         
         strcpy(cArr, dirs.c_str());
         sprintf(ltDir, "%s/linked_tracks.root", cArr);

         cout << ltDir << endl;
      }
   }
   */
}
#endif // #ifdef linked_tracks_cxx