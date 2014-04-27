#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
using namespace std;

int a[100][100];
int colsum[100][100];

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            colsum[i][j] = 0;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i > 0)
                colsum[i][j] = (colsum[i-1][j] + a[i][j]);
            else
                colsum[i][j] = a[i][j];
//            cout << colsum[i][j] << " ";
        }
//        cout << endl;
    }

    int max = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            int sum = 0;
            for(int k = 0; k < n; k++)
            {
                int m = colsum[j][k] - colsum[i][k];
                sum += m;
                if(sum < 0)
                    sum = 0;
                if(sum > max)
                    max = sum;
            }
        }
    }
    cout << max << endl;
}
