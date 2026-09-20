#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> h[i];
    }

    vector<int> dp(n + 1, 0);
    dp[n] = h[n];
    for (int i = n; i > 1; i--)
    {
        int curr = 0;
        if (h[i - 1] <= h[i])
        {
            curr = h[i] + 1;
        }
        else if (h[i - 1] > h[i])
        {
            curr = h[i - 1];
        }

        dp[i - 1] = max(curr, dp[i] + 1);
    }
    cout << dp[1] << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}