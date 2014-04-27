#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
using namespace std;

int a[100][100];
int cnt[100][100];
int r;
int c;

int DP(int i, int j)
{
    int max = 0;
    if(cnt[i][j] > 0)
        return cnt[i][j];

    if(i - 1 >= 0)
    {
        if(a[i][j] > a[i-1][j])
        {
            int v = DP(i - 1, j);
            if(v > max)
                max = v;
        }
    }
    if(i + 1 < r)
    {
        if(a[i][j] > a[i+1][j])
        {
            int v = DP(i + 1, j);
            if(v > max)
                max = v;
        }
    }
    if(j - 1 >= 0)
    {
        if(a[i][j] > a[i][j-1])
        {
            int v = DP(i, j - 1);
            if(v > max)
                max = v;
        }
    }
    if(j + 1 < c)
    {
        if(a[i][j] > a[i][j+1])
        {
            int v = DP(i, j + 1);
            if(v > max)
                max = v;
        }
    }
    cnt[i][j] = max + 1;
    return max + 1;
}

int main()
{
    cin >> r >> c;
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cin >> a[i][j];
            cnt[i][j] = 0;
        }
    }
    int max = 0;
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
           if(max < DP(i, j))
               max = DP(i, j);
        }
    }

    cout << max << endl;
}
