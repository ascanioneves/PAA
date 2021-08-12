#include <bits/stdc++.h>

using namespace std;

// Question 3.9 
int bSearch(int n, int a[], int lo, int hi, int ans)
{
  if (lo >= hi)
    return lo;
  int mid = (lo + hi) / 2;
  if (a[mid] > a[mid + 1])
    return bSearch(n, a, lo, mid, mid);
  else 
    return bSearch(n, a, mid + 1, hi, ans);
}
int main()
{
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++)
    cin >> a[i];
  cout << bSearch(n, a, 0, n - 1, -1) << endl;
  return (0);
}