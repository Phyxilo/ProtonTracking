#define linked_tracks_cxx
#include "linked_tracks.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

extern vector<int> subaVec[6];
extern vector<int> subbVec[6];

extern int PCnt, nonPCnt;
extern int initSegPlt;
extern float dist2Sum;
extern float sigma;
extern int posXMin, posXMax, posYMin, posYMax;

vector<int> prea3Vec[6];
vector<int> preb3Vec[6];
vector<int> prea3VecTemp[6];
vector<int> prea3VecBuf[6];

static int pltSize = 5;

//float posAc = 1000;

void initVect(int TrID, int PltID, int SegID, int SegX, int SegY, int SegZ, int stpPlt);

void linked_tracks::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   vector<int> linkCnt;

   PCnt = 0, nonPCnt = 0, dist2Sum = 0;;

   //cout << prea3Vec[0].size() << endl;

   int arrSize = sizeof(subaVec)/sizeof(subaVec[0]);

   for (int i = 0; i < arrSize; i++)
   {
      prea3Vec[i].assign(subaVec[i].begin(), subaVec[i].end());
   }
   
   for (int i = 0; i < arrSize && dirIndex != 0; i++)
   {
      prea3VecTemp[i].assign(subaVec[i].begin(), subaVec[i].end());

      prea3Vec[i].clear();
      preb3Vec[i].clear();
   }
   //cout << prea3VecTemp[0].size() << endl;

   int vecSize = prea3VecTemp[0].size();
   int pltBegin = dirIndex*10;

   //cout << prea3Vec[0].size() << ", " << prea3Vec[1].size() << endl;
   
   for (int j = 0; j < pltSize; j++)
   {
      int currentPlt = j + 10;

      linkCnt.push_back(count(prea3VecTemp[1].begin(), prea3VecTemp[1].end(), currentPlt));

      //cout << count(prea3VecTemp[1].begin(), prea3VecTemp[1].end(), currentPlt) << endl;
   }

   if (dirIndex == 0)
   {
      sigma = 0;

      TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
      TH1F *slopeX = new TH1F("TX","Slope X",400,-0.4,0.4);
      for (Long64_t jentry=0; jentry<nentries;jentry++) 
      {  
         int jentryint=jentry;
         Long64_t ientry = LoadTree(jentry);
         if (ientry < 0) break;
         nb = fChain->GetEntry(jentry);   nbytes += nb;

         for(int i = 0; i < nseg; i++)
         {
            int plateID = s_ePID[i];
            float segTX = s_eTX[i];

            if (plateID < 5)
            {
               slopeX->Fill(segTX);
            }
         }
      }

      sigma = 3*slopeX->GetStdDev();
      //cout << "Slope X Sigma: " << sigma << endl;

      slopeX->Draw("HIST");
      Canvas->Print( "Slope.pdf", "pdf");
   }

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {  
      int jentryint=jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      int indexArr[pltSize];

      for (int i = 0; i < pltSize; i++)
      {
         indexArr[i] = -1;
      }

      for(int i = 0; i < nseg; i++)
      {
         int pdgID = s_eMCTrack[i];
         int plateID = s_ePID[i];
         int segID = s_eID[i];

         float segX = s_eX[i];
         float segY = s_eY[i];
         float segZ = s_eZ[i];

         float segTX = s_eTX[i];
         float segTY = s_eTY[i];

         //if (s_ePID[0] == initSegPlt && (posAc == 0 || (segX <= posAc && segX >= -posAc && segY <= posAc && segY >= -posAc)) && (segTX < sigma && segTX > -sigma && segTY < sigma && segTY > -sigma))
         if (s_ePID[0] == initSegPlt && ((segX <= posXMax && segX >= posXMin && segY <= posYMax && segY >= posYMin)) && (segTX < sigma && segTX > -sigma && segTY < sigma && segTY > -sigma))
         {
            if ((dirIndex == 0 && i == 0) || wIndex > 0)
            {
               //initVect(trid, plateID, segID, segX, segY, segZ, s_ePID[nseg]);

               if(plateID >= 10*wIndex && plateID < pltSize + 10*wIndex)
               {
                  
                  //protonsbfW.push_back(trid);

                  preb3Vec[0].push_back(trid);
                  preb3Vec[1].push_back(plateID);
                  preb3Vec[2].push_back(segID);
                  preb3Vec[3].push_back(segX);
                  preb3Vec[4].push_back(segY);
                  preb3Vec[5].push_back(segZ);
               }

               /*
               if((plateID > 9 && plateID <= 9 + pltSize) || s_ePID[nseg] > 9)
               {
                  //protonsafW.push_back(trid);

                  prea3VecBuf[0].push_back(trid);
                  prea3VecBuf[1].push_back(plateID);
                  prea3VecBuf[2].push_back(segID);
                  prea3VecBuf[3].push_back(segX);
                  prea3VecBuf[4].push_back(segY);
                  prea3VecBuf[5].push_back(segZ);

                  //cout << trid << endl;
               }
               */
            }
            if (dirIndex > 0 && dirIndex <= 7)
            {
               for (int j = 0; j < pltSize; j++)
               {
                  int currentPlt = j;
                  //cout << linkCnt[currentPlt] << endl;
                  
                  if (plateID == currentPlt)
                  {
                     int segCnt = linkCnt[currentPlt];
                     for (int k = 0; k < segCnt; k++)
                     {
                        auto it = find(prea3VecTemp[1].begin() + indexArr[currentPlt] + 1, prea3VecTemp[1].end(), currentPlt+10);
                        if (it != prea3VecTemp[1].end())
                        {
                           indexArr[currentPlt] = it - prea3VecTemp[1].begin();
                           if (segID == prea3VecTemp[2][indexArr[currentPlt]])
                           {
                              //cout << "PltID: " << plateID << ", SegID: " << segID << endl;
                              //cout << "PltID: " << plateID << ", SegID: " << segID << ", PDGID: " << pdgID <<  endl;
                              //cout << "SegX: 1: " << segX << ", 2: " << prea3VecTemp[3][indexArr[currentPlt]] << ", SegY: 1: " << segY << ", 2: " << prea3VecTemp[4][indexArr[currentPlt]] << ", SegZ: 1: " << segZ << ", 2: " << prea3VecTemp[5][indexArr[currentPlt]] << endl;

                              preb3Vec[0].push_back(trid);
                              preb3Vec[1].push_back(plateID);
                              preb3Vec[2].push_back(segID);
                              preb3Vec[3].push_back(segX);
                              preb3Vec[4].push_back(segY);
                              preb3Vec[5].push_back(segZ);

                              float xDif = prea3VecTemp[3][indexArr[currentPlt]] - segX;
                              float yDif = prea3VecTemp[4][indexArr[currentPlt]] - segY;

                              dist2Sum += xDif*xDif + yDif*yDif;
                              
                              PCnt++;
                              if (pdgID != 2212){nonPCnt++;}
                           }
                        }
                     }

                     /*
                     for (int k = 0; k < vecSize; k++)
                     {
                        if (prea3VecTemp[1][k]-10 == currentPlt)
                        {
                           //cout << "SegZ: 1: " << prea3VecTemp[5][k] << ", 2: " << segZ << endl;

                           int xDif = prea3VecTemp[3][k] - segX;
                           int yDif = prea3VecTemp[4][k] - segY;
                           int dif = 0;

                           if (segID == prea3VecTemp[2][k] && plateID < 5)
                           {
                              //cout << "TrkID: 1: " << prea3VecTemp[0][k] << ", 2: " << trid << endl;
                              
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
                     */
                  }
               }
            }
            
            if ((((plateID > 9 && plateID <= 9 + pltSize)  || s_ePID[nseg] > 9) && ((dirIndex == 0 && s_ePID[0] == 0) || (dirIndex != 0 && s_ePID[0] < 5))) || 
            (((plateID > 9 + 10*wIndex && plateID <= 9 + 10*wIndex + pltSize)  || s_ePID[nseg] > 9 + 10*wIndex) && s_ePID[0] == initSegPlt))
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

      if (!(jentry%100000))
      {
         cout << "Vector Filling Progress: " << jentry << "/" << nentries << endl;
         //cout << "Before Vector Size: " << preb3Vec[0].size() << endl;
      }
   }
   
   /*
   for (int x = 0; x < preb3Vec[0].size(); x++)
   {
      cout << "TrID: " << prea3VecTemp[0][x] << ", PltID: " << prea3VecTemp[1][x] << ", SegID: " << prea3VecTemp[2][x] << ", SegX: " << prea3VecTemp[3][x] << ", SegY: " << prea3VecTemp[4][x] << ", SegZ: " << prea3VecTemp[5][x] << endl;
   }
   */

   vector<int> uniqueVec;
   uniqueVec.assign(preb3Vec[0].begin(), preb3Vec[0].end());

   vector<int>::iterator it = unique(uniqueVec.begin(), uniqueVec.end());
   auto dist = distance(uniqueVec.begin(), it);
   uniqueVec.resize(dist);

   for (int i = 0; i < prea3VecBuf[0].size(); i++)
   {
      auto it = find(uniqueVec.begin(), uniqueVec.end(), prea3VecBuf[0][i]);
      if (it != uniqueVec.end())
      {
         int ind = it - uniqueVec.begin();
         if (prea3VecBuf[0][i] == uniqueVec[ind])
         {
            for (int k = 0; k < arrSize; k++)
            {
               prea3Vec[k].push_back(prea3VecBuf[k][i]);
            }
            //cout << prea3VecBuf[0][i] << endl;
         }
      }

      if (!(i%100000))
      {
         cout << "TrackLinking Progress: " << i << "/" << prea3VecBuf[0].size() << endl;
      }
   }

   /*
   for (int i = 0; i < prea3VecBuf[0].size(); i++)
   {
      auto it = find(preb3Vec[0].begin(), preb3Vec[0].end(), prea3VecBuf[0][i]);
      if (it != preb3Vec[0].end())
      {
         int ind = it - preb3Vec[0].begin();
         if (prea3VecBuf[0][i] == preb3Vec[0][ind])
         {
            for (int k = 0; k < arrSize; k++)
            {
               prea3Vec[k].push_back(prea3VecBuf[k][i]);

               //int xDif = prea3VecBuf[3][i] - preb3Vec[3][ind];
               //int yDif = prea3VecBuf[4][i] - preb3Vec[4][ind];

               //dist2Sum += xDif*xDif + yDif*yDif;
            }
            //cout << prea3VecBuf[0][i] << endl;
         }
      }
      
      if (!(prea3VecBuf[0].size()%100000))
      {
         cout << i << "/" << prea3VecBuf[0].size() << endl;
      }
   }
   */

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

   for (int i = 0; i < arrSize; i++)
   {
      subbVec[i] = preb3Vec[i];
      subaVec[i] = prea3Vec[i];

      prea3VecTemp[i].clear();
      prea3VecBuf[i].clear();
   }

   
   //cout << "Total Size: " << PCnt << ", Non-Proton Size: " << nonPCnt << endl;
   //cout << "No Cut - Total Size: " << totalPCnt << ", Non-Proton Size: " << totalNonPCnt << endl;
   //cout << "Average Distance Square: " << (float)dist2Sum/PCnt << endl;
}

void initVect(int TrID, int PltID, int SegID, int SegX, int SegY, int SegZ, int stpPlt)
{
   if(PltID < pltSize)
   {
      //protonsbfW.push_back(trid);

      preb3Vec[0].push_back(TrID);
      preb3Vec[1].push_back(PltID);
      preb3Vec[2].push_back(SegID);
      preb3Vec[3].push_back(SegX);
      preb3Vec[4].push_back(SegY);
      preb3Vec[5].push_back(SegZ);

   }
   /*
   if(PltID > 5 && PltID < 15)
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
   */

   
   if((PltID > 9 && PltID <= 9 + pltSize) || stpPlt > 9)
   {
      //protonsafW.push_back(trid);

      prea3VecBuf[0].push_back(TrID);
      prea3VecBuf[1].push_back(PltID);
      prea3VecBuf[2].push_back(SegID);
      prea3VecBuf[3].push_back(SegX);
      prea3VecBuf[4].push_back(SegY);
      prea3VecBuf[5].push_back(SegZ);

      //cout << trid << endl;
   }
   
}