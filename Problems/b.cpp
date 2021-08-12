#include <bits/stdc++.h>

using namespace std;

int kthElement(int a1[], int a2[], int n, int m, int k, int lo, int hi)
{
  if (n > m)
    return kthElement(a1, a2, m, n, k, lo, hi);
  if (lo > hi)
    return 1;

  int cut1 = (lo + hi) >> 1;
  int cut2 = k - cut1;
  int l1 = cut1 == 0 ? INT_MIN : a1[cut1 - 1];
  int l2 = cut2 == 0 ? INT_MIN : a2[cut2 - 1];
  int r1 = cut1 == n ? INT_MAX : a1[cut1];
  int r2 = cut2 == m ? INT_MAX : a2[cut2];

  if (l1 <= r2 && l2 <= r1)
    return max(l1, l2);
  else if (l1 > r2)
    return kthElement(a1, a2, n, m, k, lo, cut1 - 1);
  else 
    return kthElement(a1, a2, n, m, k, cut1 + 1, hi);
}
int main()
{
  int n, m, k;
  cin >> n >> m >> k;
  int a1[n], a2[m];
  for (int i = 0; i < n; i++) cin >> a1[i];
  for (int i = 0; i < m; i++) cin >> a2[i];
  cout << kthElement(a1, a2, n, m, k, max(0, k - m), min(k, n)) << endl;
  return (0);
}
// 1 2 3
// 4 5 6
// k = 2