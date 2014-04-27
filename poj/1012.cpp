#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
using namespace std;

bool joseph(int n, int m, int s)
{
    vector<int> p;
    for(int i = 0; i < n; i++)
        p.push_back(i+1);

    int index = 0;
    while(p.size() > s)
    {
        index += m - 1;
        if( index >= p.size() )
            index %= p.size();

        vector<int>::iterator it = p.begin() + index;

        if(*it <= n / 2)
            return false;

        p.erase(it);
    }
    return true;
}

int main()
{
    int n;
    while((cin>>n) && (n != 0))
    {
        for(int i = 1; ; i++)
        {
            if(joseph(n+n, i*n, n))
            {
                cout << i*n << endl;
                break;
            }
            if(joseph(n+n, i*n + 1, n))
            {
                cout << i*n + 1 << endl;
                break;
            }
        }
    }
}
