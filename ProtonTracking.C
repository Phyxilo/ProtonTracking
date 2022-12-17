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

        cout << "Vector Size -- Before Tungsten: " << preBVec[0].size()<< ", After Tungsten: " << preAVec[0].size() << endl;

        for (int i = 0; i < arrSize; i++)
        {
            preAVec[i].clear();
            preBVec[i].clear();
        }
    }
}