#include "linked_tracks.C"

//.L linked_tracks.C;
//linked_tracks t;
//t.Loop();

vector<int> subaVec[6];
vector<int> subbVec[6];

vector<int> preAVec[6];
vector<int> preBVec[6];

int dirIndex;

void ProtonTracking()
{
    int arrSize = sizeof(subaVec)/sizeof(subaVec[0]);

    for (int sv = 0; sv < 8; sv++)
    {
        dirIndex = sv;

        char outNameA[64], outNameB[64];
        sprintf(outNameA, "Output/connectedAfterLT_%02d.dat", sv);
        sprintf(outNameB, "Output/connectedBeforeLT_%02d.dat", sv);

        FILE *outFileA = fopen(outNameA, "w");
        FILE *outFileB = fopen(outNameB, "w");

        linked_tracks t;
        t.Loop();

        for (int i = 0; i < arrSize; i++)
        {
            preAVec[i].assign(subaVec[i].begin(), subaVec[i].end());
            preBVec[i].assign(subbVec[i].begin(), subbVec[i].end());
        }

        cout << "Segment Vector Size -- Before Tungsten: " << preBVec[0].size() << ", After Tungsten: " << preAVec[0].size() << endl;

        vector<int>::iterator itaf = unique(preAVec[0].begin(), preAVec[0].end());
        vector<int>::iterator itbf = unique(preBVec[0].begin(), preBVec[0].end());

        auto aDist = distance(preAVec[0].begin(), itaf);
        auto bDist = distance(preBVec[0].begin(), itbf);

        for (int i = 0; i < arrSize; i++)
        {
            preAVec[i].resize(aDist);
            preBVec[i].resize(bDist);
        }

        int bVecSize = preBVec[0].size();
        int aVecSize = preAVec[0].size();

        cout << "Track Vector Size -- Before Tungsten: " << bVecSize << ", After Tungsten: " << aVecSize << endl;

        fprintf(outFileA, "Vector Track Size: %8d\n\n", aVecSize);
        fprintf(outFileB, "Vector Track Size: %8d\n\n", bVecSize);

        for (int i = 0; i < aVecSize; i++)
        {
            fprintf(outFileA, "%8d, %8d, %8d, %8d, %8d, %8d\n", preAVec[0][i], preAVec[1][i], preAVec[2][i], preAVec[3][i], preAVec[4][i], preAVec[5][i]);
        }
        for (int i = 0; i < bVecSize; i++)
        {
            fprintf(outFileB, "%8d, %8d, %8d, %8d, %8d, %8d\n", preBVec[0][i], preBVec[1][i], preBVec[2][i], preBVec[3][i], preBVec[4][i], preBVec[5][i]);
        }

        for (int i = 0; i < arrSize; i++)
        {
            preAVec[i].clear();
            preBVec[i].clear();
        }

        fclose(outFileA);
        fclose(outFileB);
    }
}