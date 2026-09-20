#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define F first
#define S second
#define all(a) a.begin(), a.end()
#define pb push_back

const int MOD = 1000000000 + 7;
int N = 1000000;
const int INF = INT_MAX;

void solve()
{
    int n, d;
    cin >> n >> d;

    vector<int> a(n);
    for (auto &v : a)
        cin >> v;

    vector<ll> sum(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++)
    {
        sum[i + 1] = a[i % n] + sum[i];
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        ll res = 2LL * d * a[i];
        // int j = i;
        // if (i + n)
        ll l = sum[i + n] - sum[i + n - d];
        ll r = sum[i + d + 1] - sum[i + 1];

        res -= (l + r);
        ans += (res > 0 ? res : 0);
    }

    cout << ans << endl;
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