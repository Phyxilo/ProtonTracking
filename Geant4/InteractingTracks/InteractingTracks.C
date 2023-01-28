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

ofstream out = ofstream("LinkResults.log", ios::out);

void Draw();

void InteractingTracks()
{
    int arrSize = sizeof(subaVec)/sizeof(subaVec[0]);

    for (int sv = 0; sv < maxLT; sv++)
    {
        dirIndex = sv;

        linked_tracks t;
        t.Loop();
    }
    //outFile->Close();
    //delete outFile;
}