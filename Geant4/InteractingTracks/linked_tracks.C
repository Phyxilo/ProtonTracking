#define linked_tracks_cxx
#include "linked_tracks.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

vector<int> UStrID;
vector<int> DStrID;
vector<int> intVec;

vector<int> ReadFile(char *inFile);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
TH1F *IntHist = new TH1F("IntHist","Interaction",9,0,9);

void linked_tracks::Loop()
{
   if (fChain == 0) return;

   char pdfOutName[64];
   sprintf(pdfOutName,"Interaction.pdf");

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   char USInName[128] = "Links/connectedUS_00.dat";
   char DSInName[128] = "Links/connectedDS_00.dat";

   sprintf(USInName,"Links/connectedUS_0%d.dat", dirIndex);
   sprintf(DSInName,"Links/connectedDS_0%d.dat", dirIndex);

   UStrID = ReadFile(USInName);
   DStrID = ReadFile(DSInName);

   char outName[64];
   sprintf(outName, "Output/Interacted_%02d.dat", dirIndex);

   FILE *outFile = fopen(outName, "w");

   for (int i = 0; i < DStrID.size(); i++)
   {
      auto it = find(UStrID.begin(), UStrID.end(), DStrID[i]);
      if (it != UStrID.end())
      {
         UStrID.erase(it);
      }
   }

   intVec.assign(UStrID.begin(), UStrID.end());

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {  
      int jentryint=jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (s_ePID[0] == 0)
      {
         auto it = find(intVec.begin(), intVec.end(), trid);
         if (it != intVec.end())
         {
            int plateID = s_ePID[nseg];

            if (/*plateID < 10*/ true)
            {
               //fprintf(outFile, "%8d, %8d\n", trid, plateID);

               fprintf(outFile, "%8d: ", trid);
               for (int seg = 0; seg < nseg; seg++)
               {
                  fprintf(outFile, "%8d ", s_ePID[seg]);
               }
               fprintf(outFile, "\n");

               cout << "TrackID: " << trid << ", PlateID: " << plateID << endl;

               IntHist->Fill(s_ePID[nseg]);
            }

            intVec.erase(it);
         }

         //cout << intVec.size() << endl;
      }
   }
   
   IntHist->Draw();
   Canvas->Print(pdfOutName, "pdf");

   fclose(outFile);
}


vector<int> ReadFile(char *inFile)
{
   vector<int> trIDVec;

   FILE *fUS = fopen(inFile, "r");
      
   char line[1024];

   int numLines = 0;
   char buff[512];

   size_t num;

   while ((num = fread(buff, 1, 512, fUS)) > 0)
   {
      for (int i = 0; i < num; i++)
      {
         if(buff[i] == '\n')
         {
            ++numLines;
         }
      }
      
   }
   fclose(fUS);

   const int numL = numLines;

   int trID[numLines];
   int pltID[numLines];
   int segID[numLines];
   int sxID[numLines];
   int syID[numLines];
   int szID[numLines];

   fUS = fopen(inFile, "r");

   for(int i = 0; i < numLines; i++)
   {
      fscanf(fUS, "%8d, %8d, %8d, %8d, %8d, %8d", &trID[i], &pltID[i], &segID[i], &sxID[i], &syID[i], &szID[i]);
      trIDVec.push_back(trID[i]);
   }
   fclose(fUS);

   return trIDVec;
}