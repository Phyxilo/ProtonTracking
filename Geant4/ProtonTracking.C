#include "linked_tracks.C"

vector<int> subaVec[6];
vector<int> subbVec[6];

vector<int> preAVec[6];
vector<int> preBVec[6];

int dirIndex;
int PCnt, nonPCnt;
int dist2Sum;

int aVecSize, bVecSize;
const int maxLT = 3;
float sigma;

//TFile *outFile;
ofstream out = ofstream("LinkResults.log", ios::out);

void LogOut();
void DatOut();
//void RootOut();
void Draw();

void ProtonTracking()
{
    int arrSize = sizeof(subaVec)/sizeof(subaVec[0]);

    for (int sv = 0; sv < maxLT; sv++)
    {
        dirIndex = sv;

        linked_tracks t;
        t.Loop();

        for (int i = 0; i < arrSize; i++)
        {
            preAVec[i].assign(subaVec[i].begin(), subaVec[i].end());
            preBVec[i].assign(subbVec[i].begin(), subbVec[i].end());
        }

        vector<int>::iterator itaf = unique(preAVec[0].begin(), preAVec[0].end());
        vector<int>::iterator itbf = unique(preBVec[0].begin(), preBVec[0].end());

        auto aDist = distance(preAVec[0].begin(), itaf);
        auto bDist = distance(preBVec[0].begin(), itbf);

        for (int i = 0; i < arrSize; i++)
        {
            preAVec[i].resize(aDist);
            preBVec[i].resize(bDist);
        }

        bVecSize = preBVec[0].size();
        aVecSize = preAVec[0].size();

        LogOut();
        DatOut();
        //RootOut();
        Draw();

        for (int i = 0; i < arrSize; i++)
        {
            preAVec[i].clear();
            preBVec[i].clear();
        }
    }
    //outFile->Close();
    //delete outFile;
}

void LogOut()
{
    if (dirIndex == 0)
    {
        out << "Slope X Sigma: " << sigma << endl;
        out << "----------------------------------" << endl;
    }

    out << "Tungsten # " << dirIndex << endl;
    out << "\nTotal Size: " << PCnt << ", Non-Proton Size: " << nonPCnt << endl;

    out << "\nSegment Vector Size -- Upstream: " << subbVec[0].size() << ", Downstream: " << subaVec[0].size() << endl;
    out << "Track Vector Size -- Upstream: " << bVecSize << ", Downstream: " << aVecSize << endl;

    out << "\nAverage Distance Square: " << (float)dist2Sum/PCnt << endl;
    out << "--------------------------------------------------------------------" << endl;
}

void DatOut()
{
    char outNameA[64], outNameB[64];
    sprintf(outNameA, "Output/connectedDS_%02d.dat", dirIndex);
    sprintf(outNameB, "Output/connectedUS_%02d.dat", dirIndex);

    FILE *outFileA = fopen(outNameA, "w");
    FILE *outFileB = fopen(outNameB, "w");

    //fprintf(outFileA, "Vector Track Size: %8d\n\n", aVecSize);
    //fprintf(outFileB, "Vector Track Size: %8d\n\n", bVecSize);

    for (int i = 0; i < aVecSize; i++)
    {
        fprintf(outFileA, "%8d, %8d, %8d, %8d, %8d, %8d\n", preAVec[0][i], preAVec[1][i], preAVec[2][i], preAVec[3][i], preAVec[4][i], preAVec[5][i]);
    }
    for (int i = 0; i < bVecSize; i++)
    {
        fprintf(outFileB, "%8d, %8d, %8d, %8d, %8d, %8d\n", preBVec[0][i], preBVec[1][i], preBVec[2][i], preBVec[3][i], preBVec[4][i], preBVec[5][i]);
    }

    fclose(outFileA);
    fclose(outFileB);
}

/*
int wNum;
int trID[maxLT];
int plateID[maxLT];
int segID[maxLT];
int segX[maxLT];
int segY[maxLT];
int segZ[maxLT];

void RootOut()
{
    char treeName[16];
    sprintf(treeName, "w#%02d", dirIndex);

    if (dirIndex == 0)
    {
        outFile = TFile::Open("conectedLT.root", "RECREATE");
    }

    TTree *tree = new TTree(treeName,"Info");

    tree->Branch("wNum",&wNum,"wNum/I");
    tree->Branch("trID",trID,"trID[wNum]/I");
    tree->Branch("plateID",plateID,"plateID[wNum]/I");
    tree->Branch("segID",segID,"segID[wNum]/I");
    tree->Branch("segX",segX,"segX[wNum]/I");
    tree->Branch("segY",segY,"segY[wNum]/I");
    tree->Branch("segZ",segZ,"segZ[wNum]/I");

    for (int i = 0; i < aVecSize; i++)
    {
        wNum = dirIndex;
        trID[dirIndex] = preAVec[0][i];
        plateID[dirIndex] = preAVec[1][i];
        segID[dirIndex] = preAVec[2][i];
        segX[dirIndex] = preAVec[3][i];
        segY[dirIndex] = preAVec[4][i];
        segZ[dirIndex] = preAVec[5][i];

        tree->Fill();
    }
    outFile->cd();
    tree->Write();

    delete tree;
}
*/

TCanvas *Canvas;
TGraph *IntGraph;
TGraph *PurGraph;

void Draw()
{
    if (dirIndex == 0)
    {
        IntGraph = new TGraph (maxLT);
        PurGraph = new TGraph (maxLT-1);
    }
    else
    {
        float PurPer = ((float)(PCnt-nonPCnt)/PCnt)*100;
        PurGraph->SetPoint(dirIndex-1, dirIndex, PurPer);
    }

    float IntPer = ((float)(bVecSize - aVecSize)/bVecSize)*100;
    IntGraph->SetPoint(dirIndex, dirIndex, IntPer);

    if (dirIndex == maxLT-1)
    {
        Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
        Canvas->SetGrid();

        IntGraph->Draw();
        IntGraph->SetTitle("Interaction Rate");
        IntGraph->GetXaxis()->SetTitle("Tungsten");
        IntGraph->GetYaxis()->SetTitle("Percentage");
        IntGraph->SetMarkerSize(1.5);
        IntGraph->SetMarkerStyle(kFullCircle);
        
        Canvas->Print("Results.pdf(","pdf");
        delete Canvas;

        Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
        Canvas->SetGrid();

        PurGraph->Draw();
        PurGraph->SetTitle("Proton Purity");
        PurGraph->GetXaxis()->SetTitle("Tungsten");
        PurGraph->GetYaxis()->SetTitle("Percentage");
        PurGraph->SetMarkerSize(1.5);
        PurGraph->SetMarkerStyle(kFullCircle);
        
        Canvas->Print("Results.pdf)","pdf");
        delete Canvas;
    }
}