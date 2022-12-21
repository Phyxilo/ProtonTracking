#define linked_tracks_cxx
#include "linked_tracks.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//extern vector<int> pot1st;
//extern vector<int> protonsbfW;
//extern vector<int> protonsafW;

extern vector<int> sub1Vec[6];
extern vector<int> sub2Vec[6];

vector<int> prea3Vec[6];
vector<int> preb3Vec[6];

int PCnt = 0, nonPCnt = 0;
int totalPCnt = 0, totalNonPCnt = 0;

void initVect(int TrID, int SegID, int PdgID, int PltID, int SegX, int SegY, int SegZ);

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
   //FILE *f = fopen("plate10.txt", "w");

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   vector<int>::iterator itbf;
   vector<int>::iterator itaf;

   vector<int> linkCnt;

   nentries = 100000;

   //prea3Vec[0].clear(); prea3Vec[1].clear(); prea3Vec[2].clear();
   //preb3Vec[0].clear(); preb3Vec[1].clear(); preb3Vec[2].clear();

   int vecSize = prea3Vec[0].size();
   int pltBegin = dirIndex*10;
   int pltSize = 5;

   int dist2Sum = 0;

   //cout << prea3Vec[0].size() << ", " << prea3Vec[1].size() << endl;
   /*
   for (int j = 0; j < pltSize; j++)
   {
      int currentPlt = pltBegin + j;

      linkCnt.push_back(count(prea3Vec[1].begin(), prea3Vec[1].end(), currentPlt));

      //cout << count(prea3Vec[1].begin(), prea3Vec[1].end(), currentPlt) << endl;
   }
   */

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {  
      int jentryint=jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      int index = -1;

      for(int i = 0; i < nseg; i++)
      {
         int pdgID = s_eMCTrack[i];
         int plateID = s_ePID[i];
         int segID = s_eID[i];

         int segX = s_eX[i];
         int segY = s_eY[i];
         int segZ = s_eZ[i];
   
         if (vecSize == 0 && s_ePID[0] == 0)
         {
            initVect(trid, segID, pdgID, plateID, segX, segY, segZ);
         }
         else
         {  
            
            for (int j = 0; j < pltSize; j++)
            {
               int currentPlt = pltBegin + j;
               //cout << segCnt << endl;
               
               /*
               int segCnt = linkCnt[j];
               for (int k = 0; k < segCnt; k++)
               {
                  auto it = find(prea3Vec[1].begin() + index + 1, prea3Vec[1].end(), currentPlt);
                  if (it != prea3Vec[1].end())
                  {
                     index = it - prea3Vec[1].begin();
                     if (segID == prea3Vec[2][index]){cout << "PltID: " << plateID << ", SegID: " << segID << endl;}
                  }
               }
               */

               if (plateID == currentPlt)
               {
                  totalPCnt++;

                  if (pdgID != 2212) {totalNonPCnt++;}

                  for (int k = 0; k < vecSize; k++)
                  {
                     if (prea3Vec[1][k]-pltBegin == currentPlt)
                     {
                        //cout << "SegZ: 1: " << prea3Vec[5][k] << ", 2: " << segZ << endl;

                        int xDif = prea3Vec[3][k] - segX;
                        int yDif = prea3Vec[4][k] - segY;
                        int dif = 0;

                        if (segID == prea3Vec[2][k] /*xDif <= dif && xDif >= -dif && yDif <= dif && yDif >= -dif*/)
                        {
                           //cout << "PltID: " << plateID << ", SegID: " << segID << ", PDGID: " << pdgID <<  endl;
                           //cout << "SegX: 1: " << segX << ", 2: " << prea3Vec[3][k] << ", SegY: 1: " << segY << ", 2: " << prea3Vec[4][k] << ", SegZ: 1: " << segZ << ", 2: " << prea3Vec[5][k] << endl;
                           
                           dist2Sum += xDif*xDif + yDif*yDif;
                           
                           PCnt++;

                           if (pdgID != 2212){nonPCnt++;}
                        }
                     }
                  }
               }
            }
         }
      }

      if (!(jentry%10000))
      {
         cout << jentry << "/" << nentries << endl;
      }
   }
   
   itaf = unique(prea3Vec[0].begin(), prea3Vec[0].end());
   itbf = unique(preb3Vec[0].begin(), preb3Vec[0].end());

   auto aDist = distance(prea3Vec[0].begin(), itaf);
   auto bDist = distance(preb3Vec[0].begin(), itbf);

   for (int i = 0; i < 3; i++)
   {
      prea3Vec[i].resize(aDist);
      preb3Vec[i].resize(bDist);
   }

   /*
   for (int j = 0; j < prea3Vec[0].size(); j++)
   {
      int cnt = count(prea3Vec[0].begin(), prea3Vec[0].end(), prea3Vec[0][j]);

      if (cnt != 1)
         cout << cnt << endl;
   }
   */
   
   //prea3Vec[0].resize(distance(prea3Vec[0].begin(),itaf));
   //preb3Vec[0].resize(distance(preb3Vec[0].begin(),itbf));

   //cout << prea3Vec[0].size() << ", " << prea3Vec[1].size() << endl;


   if (!dirIndex%2) { sub1Vec[0] = prea3Vec[0]; sub1Vec[1] = prea3Vec[1]; sub1Vec[2] = prea3Vec[2]; }
   else { sub2Vec[0] = prea3Vec[0]; sub2Vec[1] = prea3Vec[1]; sub2Vec[2] = prea3Vec[2]; }

   cout << "Total Size: " << PCnt << ", Non-Proton Size: " << nonPCnt << endl;
   cout << "No Cut - Total Size: " << totalPCnt << ", Non-Proton Size: " << totalNonPCnt << endl;
   cout << "Average Distance Squre: " << (float)dist2Sum/PCnt << endl;

   //cout << "After Vector: " << prea3Vec[0].size()<< ", Before Vector: " << preb3Vec[0].size() << endl;
   //fclose(f);
}

void initVect(int TrID, int SegID, int PdgID, int PltID, int SegX, int SegY, int SegZ)
{
   if(PdgID == 2212 && PltID <= 4)
   {
      //protonsbfW.push_back(trid);

      preb3Vec[0].push_back(TrID);
      preb3Vec[1].push_back(PltID);
      preb3Vec[2].push_back(SegID);
      preb3Vec[3].push_back(SegX);
      preb3Vec[4].push_back(SegY);
      preb3Vec[5].push_back(SegZ);

      //cout << trid << endl;
   }

   if(PdgID == 2212 && PltID >= 5)
   {
      //protonsafW.push_back(trid);

      prea3Vec[0].push_back(TrID);
      prea3Vec[1].push_back(PltID);
      prea3Vec[2].push_back(SegID);
      prea3Vec[3].push_back(SegX);
      prea3Vec[4].push_back(SegY);
      prea3Vec[5].push_back(SegZ);

      //cout << trid << endl;
   }
}