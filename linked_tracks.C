#define linked_tracks_cxx
#include "linked_tracks.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

extern vector<int> subaVec[6];
extern vector<int> subbVec[6];

vector<int> prea3Vec[6];
vector<int> preb3Vec[6];
vector<int> prea3VecTemp[6];
vector<int> prea3VecBuf[6];

float posAc = 1000;

void initVect(int TrID, int PltID, int SegID, int SegX, int SegY, int SegZ, int pltOffset);

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

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   vector<int> linkCnt;

   int PCnt = 0, nonPCnt = 0;
   int totalPCnt = 0, totalNonPCnt = 0;

   int arrSize = sizeof(prea3Vec)/sizeof(prea3Vec[0]);
   
   for (int i = 0; i < arrSize; i++)
   {
      prea3VecTemp[i].assign(prea3Vec[i].begin(), prea3Vec[i].end());

      prea3Vec[i].clear();
      preb3Vec[i].clear();
   }
   //cout << prea3VecTemp[0].size() << endl;

   int vecSize = prea3VecTemp[0].size();
   int pltBegin = dirIndex*10;
   int pltSize = 5;

   int dist2Sum = 0;

   //cout << prea3Vec[0].size() << ", " << prea3Vec[1].size() << endl;
   /*
   for (int j = 0; j < pltSize; j++)
   {
      int currentPlt = pltBegin + j;

      linkCnt.push_back(count(prea3VecTemp[1].begin(), prea3VecTemp[1].end(), currentPlt));

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

         if (posAc == 0 || (segX <= posAc && segX >= -posAc && segY <= posAc && segY >= -posAc))
         {
            if (vecSize == 0)
            {
               if(s_ePID[0] == 0 && pdgID == 2212)
               {
                  initVect(trid, plateID, segID, segX, segY, segZ, pltBegin);
               }               
            }
            else
            {
               for (int j = 0; j < pltSize; j++)
               {
                  int currentPlt = j;
                  //cout << segCnt << endl;
                  /*
                  int segCnt = linkCnt[j];
                  for (int k = 0; k < segCnt; k++)
                  {
                     auto it = find(prea3VecTemp[1].begin() + index + 1, prea3VecTemp[1].end(), currentPlt);
                     if (it != prea3VecTemp[1].end())
                     {
                        index = it - prea3VecTemp[1].begin();
                        if (segID == prea3VecTemp[2][index])
                        {
                           //cout << "PltID: " << plateID << ", SegID: " << segID << endl;
                           //cout << "PltID: " << plateID << ", SegID: " << segID << ", PDGID: " << pdgID <<  endl;
                           //cout << "SegX: 1: " << segX << ", 2: " << prea3VecTemp[3][index] << ", SegY: 1: " << segY << ", 2: " << prea3VecTemp[4][index] << ", SegZ: 1: " << segZ << ", 2: " << prea3VecTemp[5][index] << endl;
                           
                           PCnt++;
                           if (pdgID != 2212){nonPCnt++;}
                        }

                        totalPCnt++;
                        if (pdgID != 2212) {totalNonPCnt++;}
                     }
                  }
                  */
                  
                  if (plateID == currentPlt)
                  {
                     totalPCnt++;
                     if (pdgID != 2212) {totalNonPCnt++;}
                     
                     for (int k = 0; k < vecSize; k++)
                     {
                        if (prea3VecTemp[1][k]-10 == currentPlt)
                        {
                           //cout << "SegZ: 1: " << prea3VecTemp[5][k] << ", 2: " << segZ << endl;

                           int xDif = prea3VecTemp[3][k] - segX;
                           int yDif = prea3VecTemp[4][k] - segY;
                           int dif = 0;

                           if (segID == prea3VecTemp[2][k] /*xDif <= dif && xDif >= -dif && yDif <= dif && yDif >= -dif*/)
                           {
                              //initVect(trid, plateID, segID, segX, segY, segZ, pltBegin);
                              
                              preb3Vec[0].push_back(trid);
                              preb3Vec[1].push_back(plateID);
                              preb3Vec[2].push_back(segID);
                              preb3Vec[3].push_back(segX);
                              preb3Vec[4].push_back(segY);
                              preb3Vec[5].push_back(segZ);

                              //cout << "PltID: " << plateID << ", SegID: " << segID << ", PDGID: " << pdgID <<  endl;
                              //cout << "SegX: 1: " << segX << ", 2: " << prea3VecTemp[3][k] << ", SegY: 1: " << segY << ", 2: " << prea3VecTemp[4][k] << ", SegZ: 1: " << segZ << ", 2: " << prea3VecTemp[5][k] << endl;
                              
                              dist2Sum += xDif*xDif + yDif*yDif;
                              
                              PCnt++;
                              if (pdgID != 2212){nonPCnt++;}
                           }
                        }
                     }
                  }
               }

               if (plateID > 5 && plateID <= 9)
               {
                  prea3VecBuf[0].push_back(trid);
                  prea3VecBuf[1].push_back(plateID);
                  prea3VecBuf[2].push_back(segID);
                  prea3VecBuf[3].push_back(segX);
                  prea3VecBuf[4].push_back(segY);
                  prea3VecBuf[5].push_back(segZ);
               }
            }
         }
      }

      if (!(jentry%100000))
      {
         cout << jentry << "/" << nentries << endl;
         //cout << "Before Vector Size: " << preb3Vec[0].size() << endl;
      }
   }
   
   if (dirIndex != 0)
   {
      int ind = -1;

      /*
      for (int x = 0; x < preb3Vec[0].size(); x++)
      {
         cout << "TrID: " << prea3VecTemp[0][x] << ", PltID: " << prea3VecTemp[1][x] << ", SegID: " << prea3VecTemp[2][x] << ", SegX: " << prea3VecTemp[3][x] << ", SegY: " << prea3VecTemp[4][x] << ", SegZ: " << prea3VecTemp[5][x] << endl;
      }
      */

      for (int i = 0; i < prea3VecBuf[0].size(); i++)
      {
         /*
         int cnt = count(preb3Vec[0].begin(), preb3Vec[0].end(), prea3VecBuf[0][i]);

         for (int j = 0; j < cnt; j++)
         {
            auto it = find(preb3Vec[0].begin() + ind + 1, preb3Vec[0].end(), prea3VecBuf[0][i]);
            if (it != preb3Vec[0].end())
            {
               ind = it - preb3Vec[0].begin();
               if (prea3VecBuf[0][i] == preb3Vec[0][ind])
               {
                  for (int k = 0; k < arrSize; k++)
                  {
                     prea3Vec[k].push_back(prea3VecBuf[k][i]);
                  }
               }
            }
         }
         */

         auto it = find(preb3Vec[0].begin() + ind + 1, preb3Vec[0].end(), prea3VecBuf[0][i]);
         if (it != preb3Vec[0].end())
         {
            ind = it - preb3Vec[0].begin();
            if (prea3VecBuf[0][i] == preb3Vec[0][ind])
            {
               for (int k = 0; k < arrSize; k++)
               {
                  prea3Vec[k].push_back(prea3VecBuf[k][i]);
               }
               //cout << prea3VecBuf[0][i] << endl;
            }
         }
      }

      /*
      for (int i = 0; i < prea3VecBuf[0].size(); i++)
      {
         for (int j = 0; j < preb3Vec[0].size(); j++)
         {
            if (prea3VecBuf[0][i] == preb3Vec[0][j])
            {
               for (int k = 0; k < arrSize; k++)
               {
                  prea3Vec[k].push_back(prea3VecBuf[k][i]);
               }
            }
         }

         //cout << i << "/" << prea3VecBuf[0].size() << endl;
      }
      */
   }

   for (int i = 0; i < arrSize; i++)
   {
      subbVec[i] = preb3Vec[i];
      subaVec[i] = prea3Vec[i];

      prea3VecTemp[i].clear();
      prea3VecBuf[i].clear();
   }

   
   cout << "Total Size: " << PCnt << ", Non-Proton Size: " << nonPCnt << endl;
   cout << "No Cut - Total Size: " << totalPCnt << ", Non-Proton Size: " << totalNonPCnt << endl;
   cout << "Average Distance Squre: " << (float)dist2Sum/PCnt << endl;
}

void initVect(int TrID, int PltID, int SegID, int SegX, int SegY, int SegZ, int pltOffset)
{
   if(PltID <= 4)
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

   if(PltID > 5 && PltID <= 9)
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