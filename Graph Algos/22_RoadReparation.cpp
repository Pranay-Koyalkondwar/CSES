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

struct UnionFind
{
    int n, set_size, *parent, *rank;
    UnionFind() {}
    UnionFind(int a)
    {
        n = a;
        set_size = a;
        parent = new int[n + 1];
        rank = new int[n + 1];
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void merge(int x, int y)
    {
        int xroot = find(x), yroot = find(y);
        if (xroot != yroot)
        {
            if (rank[xroot] >= rank[yroot])
            {
                rank[xroot] += rank[yroot];
                parent[yroot] = xroot;
            }
            else
            {
                rank[yroot] += rank[xroot];
                parent[xroot] = yroot;
            }
            set_size--;
        }
    }

    void reset()
    {
        set_size = n;
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int size() { return set_size; }

    void print()
    {
        for (int i = 1; i <= n; i++)
            cout << i << " -> " << parent[i] << endl;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    UnionFind dsu(n);
    vector<pair<int, pair<int, int>>> p;
    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        p.pb({c, {u, v}});
    }
    sort(all(p));

    ll ans = 0, cnt = 0;
    for (int i = 0; i < m; i++)
    {
        int u = p[i].S.F;
        int v = p[i].S.S;
        int c = p[i].F;

        if (dsu.find(u) != dsu.find(v))
        {
            dsu.merge(u, v);
            ans += c;
            cnt++;
        }
    }

    if (cnt < n - 1)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
        cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}