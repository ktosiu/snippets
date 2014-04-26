#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int cases;
    cin>>cases;
    while(cases--)
    {
        // Input
        int n;
        int i = 0;
        cin >> n;
        vector<int> level_count;

        while(n--)
        {
            int v;
            cin >> v;
            for(; i < v; i++)
            {
                level_count.push_back(1);
            }
            cout << level_count.back() << " ";
            level_count.pop_back();
            for(vector<int>::iterator it = level_count.begin(); it != level_count.end(); it++)
            {
                (*it)++;
            }
        }
        cout << "\n";
    }
}
