#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define N 1010
int inData[N][2];
struct node{
  int val, pos;
} outData[N * 9];

int inNum, outNum, total, width;

bool cmp(const node &n1, const node &n2) {
  return n1.pos < n2.pos;
}

int getValue(int loc) {
  int low = 0, high = inNum - 1;
  while (low <= high) {
      int mid = (low + high) / 2;
      if (inData[mid][1] <= loc) {
          low = mid + 1;
      }
      else {
          high = mid - 1;
      }
  }
  //printf("high = %dn", high);
  return inData[high][0];
}

int cal(int loc) {
  int row, col, i, j, ret = 0;
  row = loc / width;
  col = loc % width;
  for (i = row - 1; i <= row + 1; ++i) {
      for (j = col - 1; j <= col + 1; ++j) {
          int p = i * width + j;
          if (i < 0 || j < 0 || j >= width || p >= total || p == loc) {
              continue;
          }
   int q = abs(getValue(p) - getValue(loc));
  //printf("q = %d, p = %d, loc = %d,n", q, p, loc);
   if (q > ret) {
  ret = q;
   }
  }
  }
  return ret;
}

void solve() {
  int i, j, k, row, col;
  outNum = 0;
  for (i = 0; i <= inNum; ++i) {
  row = inData[i][1] / width;
  col = inData[i][1] % width;
  for (j = row - 1; j <= row + 1; ++j) {
   for (k = col - 1; k <= col + 1; ++k) {
  int p = j * width + k;
  if (j < 0 || p >= total || p < 0) {
      continue;
  }
  outData[outNum].val = cal(p);
  outData[outNum].pos = p;
  ++outNum;
   }
  }
  }
  for (i = 0; i < outNum; ++i) {
  //printf("%d, %dn", outData[i].val, outData[i].pos);
  }
  sort(outData, outData + outNum, cmp);
  node cur = outData[0];
  for (i = 0; i < outNum; ++i) {
  if (cur.val == outData[i].val) {
   continue;
  }
  printf("%d %d\n", cur.val, outData[i].pos - cur.pos);
  cur = outData[i];
  }
  printf("%d %d\n", cur.val, total - cur.pos);
  printf("0 0\n");
}

int main() {
  //freopen("in.txt", "r", stdin);
  while (scanf("%d", &width) != EOF && width) {
  printf("%d\n", width);
  int i = 0, j;
  total = 0;
  while (scanf("%d%d", &inData[i][0], &inData[i][1]) != EOF) {
   j = inData[i][1];
   inData[i][1] = total;
   total += j;
   if (0 == j) break;
   ++i;
  }
  inNum = i;
  solve();
  }
  printf("0\n");
  return 0;
}