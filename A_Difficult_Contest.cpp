#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
#define F first
#define S second
#define all(a) a.begin(), a.end()
#define pb push_back

const int MOD = 998244353;
int N = 1000000;
const int INF = INT_MAX;

int fac[1000005], inv[1000005];

int pow(int base, int exp) {
    int res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int modinv(int n) {
    return pow(n, MOD - 2);
}

void precompute() {
    fac[0] = 1;
    inv[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv[N] = modinv(fac[N]);
    for (int i = N - 1; i >= 1; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

int nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int>a(n);
    for(auto &v : a) cin >> v;

    int s1 = 0;
    int s2 = 0;

    for (int i = 0; i < n; i++) {
        int val = ((a[i] % MOD) + MOD) % MOD;
        s1 = (s1 + val) % MOD;
        s2 = (s2 + (val * val) % MOD) % MOD;
    }

    int sumcr = (s1 * s1 % MOD - s2 + MOD) % MOD;

    int ans = (nCr(n - 1, k - 1) * s2) % MOD;
    ans = (ans + nCr(n - 2, k - 2) * sumcr) % MOD;

    cout << ans << endl;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    precompute();
    
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}