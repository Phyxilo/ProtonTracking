#define linked_tracks_cxx
#include "linked_tracks.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void linked_tracks::Loop()
{
//   In a ROOT session, you can do:
//      root> .L linked_tracks.C
//      root> linked_tracks t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   FILE *fp2=fopen("plate10.txt","r");
   vector<int>incoming_protons;
   int i,n;
   int numLines1=0;
   char buff1[512];//array for symbols input
   size_t num1;
   while ((num1=fread(buff1,1,512,fp2))>0)
   {
      for (i=0;i<num1;i++)
      {
         if(buff1[i]=='\n')
         {
            ++numLines1;
         }
      }
   }
   fclose(fp2);
   const int numL= numLines1;
   int *a101 = new int[numL];

   fp2=fopen("plate10.txt","r");
   for(i=0;i<numL;i++)
   {
      fscanf(fp2,"%d",&a101[i]);
    incoming_protons.push_back(a101[i]);

   }
      fclose(fp2);

   FILE *f= fopen("plate20.txt","w");

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   vector<int>pot1st;
   vector<int> protonsbfW;
   vector<int> protonsafW;

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {  
      int jentryint=jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
if (find(incoming_protons.begin(), incoming_protons.end(), trid) == incoming_protons.end())
        {
                 
      if(s_ePID[0]==0){
      for(int i=0; i<nseg; i++ )
      {
      
            int pdgid = s_eMCTrack[i] ;
            int plateid = s_ePID[i];
            int segid = s_eID[i];

     
            if(pdgid==2212 && plateid==4)
      {
               protonsbfW.push_back(trid);
            }

            if(pdgid==2212 && plateid==5)
      {
               protonsafW.push_back(trid);
            }
            
            if(plateid == 0 )
         {
              pot1st.push_back(trid);
         }
                     if(plateid == 10 && i==10)
            {
               fprintf(f, "%d\n", segid);      
            }

      }
   }
   }
}
int not_interacted_aft_bf = 0;

   for (int i = 0; i < protonsafW.size(); i++)
   {
    if (find(protonsbfW.begin(), protonsbfW.end(), protonsafW[i]) != protonsbfW.end())
        {
            not_interacted_aft_bf++;
        }
   }


    cout << "Full Vector: " << pot1st.size() << ", not_interacted_aft_bf: " << not_interacted_aft_bf << ", after Vector: " << protonsafW.size()<< ", before Vector: " << protonsbfW.size()<< endl;
   fclose(f);
}
