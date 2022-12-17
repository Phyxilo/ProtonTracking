#include "linked_tracks.C"

//.L linked_tracks.C;
//linked_tracks t;
//t.Loop();

vector<int> pot1st;
vector<int> protonsbfW;
vector<int> protonsafW;

vector<int> sub1Vec[6];
vector<int> sub2Vec[6];

int dirIndex;

void ProtonTracking()
{
    for (int sv = 0; sv < 2; sv++)
    {
        dirIndex = sv;

        //pot1st.clear();
        //protonsbfW.clear();
        //protonsafW.clear();
        
        linked_tracks t;
        t.Loop();
        //cout << nseg << endl;

        //cout << "Full Vector Size: " << pot1st.size() << ", After Vector Size: " << protonsafW.size()<< ", Before Vector Size: " << protonsbfW.size() << endl;

        //cout << "Sub1Size: " << sub1Vec[0].size() << endl;
        //cout << "Sub2Size: " << sub2Vec[0].size() << endl;

        /*
        if (sv%2)
        {
            for (int i = 0; i < sub2Vec[0].size(); i++)
            {
                for (int j = 0; j < sub1Vec[0].size(); j++)
                {
                    if (sub2Vec[1][i] == 20 && sub1Vec[1][j] == 20)
                    {
                        cout << "Sub1: " << sub1Vec[0][j] << endl;
                        cout << "Sub2: " << sub2Vec[0][i] << endl;
                    }
                }
            }
        }
        */
    }
}