#include <bits/stdc++.h>

using namespace std;

int main()
{

    vector<pair<int, int>> time_pair;
    vector<pair<int, int>> ans_pair;

    int n, t1, t2;
    int resources;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t1 >> t2;
        time_pair.push_back(make_pair(t1, t2));
    }

    sort(time_pair.begin(), time_pair.end());

    ans_pair.push_back(time_pair[0]);
    resources = 1;
    for (int i = 1; i < time_pair.size(); i++)
    {
        for (int j = 0; j < ans_pair.size(); j++)
        {
            if (ans_pair[j].second > time_pair[i].first)
            {
                resources++;
                //ans_pair.push_back(make_pair(time_pair[i].first, time_pair[i].second));
            }
            else{
                ans_pair.erase(ans_pair.begin()+j);
                ans_pair.push_back(time_pair[i]);
            }
        }
    }

    cout << resources << "\n";

    for (auto i = ans_pair.begin(); i < ans_pair.end(); i++)
    {
        cout << (*i).first << " " << (*i).second << "\n";
    }

    return 0;
}
