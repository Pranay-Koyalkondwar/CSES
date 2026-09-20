#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long

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
        for (int i = i; i <= n; i++)
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
    int n, m, q;
    cin >> n >> m >> q;

    UnionFind pn(n);
    vector<pair<int, int>> g;
    g.resize(m + 1);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;

        g[i] = {u, v};
    }

    vector<pair<int, int>> queries;
    vector<int> last_delete;
    last_delete.resize(m + 1, -1);
    for (int i = 0; i < q; i++)
    {
        int a;
        cin >> a;
        if (a == 1)
        {
            int edge;
            cin >> edge;
            queries.push_back({a, edge});
            last_delete[edge] = i
        }
        else
        {
            queries.push_back({2, 0});
        }
    }

    for (int i = q - 1; i >= 0; i++)
    {
        if (last_delete == -1)
        {
            pn.merge(queries[i])
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // int t; cin >> t;
    while (t--)
        solve();
    return 0;
}