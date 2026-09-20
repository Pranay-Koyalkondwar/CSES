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
    int n, m;
    cin >> n >> m;
 
    vector<string> s(n);
    for (auto &v : s)
        cin >> v;
 
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
 
    auto check = [&](int &x, int &y)
    {
        return (x >= 0 && y >= 0 && x < n && y < m);
    };
 
    auto bfs = [&](int &i, int &j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
 
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
 
            for (int i = 0; i < 4; i++)
            {
                int xx = x + dx[i];
                int yy = y + dy[i];
 
                if (check(xx, yy) && s[xx][yy] != '#')
                {
                    s[xx][yy] = '#';
                    q.push({xx, yy});
                }
            }
        }
    };
 
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] != '#')
            {
                s[i][j] = '#';
                cnt++;
                bfs(i, j);
            }
        }
    }
 
    cout << cnt << endl;
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
