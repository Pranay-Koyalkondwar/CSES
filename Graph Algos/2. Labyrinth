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
    queue<pair<int, int>> q;
    vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(m, {-1, -1}));
    int enx = 0, eny = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] == 'A')
            {
                q.push({i, j});
            }
            else if (s[i][j] == 'B')
            {
                enx = i;
                eny = j;
            }
        }
    }
 
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
 
    auto check = [&](int x, int y)
    {
        return (x >= 0 && y >= 0 && x < n && y < m);
    };
 
    bool found = false;
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
 
        if (s[x][y] == 'B')
        {
            found = true;
            break;
        }
 
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dx[i];
            int yy = y + dy[i];
 
            if (check(xx, yy) && s[xx][yy] != '#' && s[xx][yy] != 'A')
            {
                if (s[xx][yy] != 'B')
                    s[xx][yy] = '#';
                par[xx][yy] = {x, y};
                q.push({xx, yy});
            }
        }
    }
 
    if (!found)
    {
        cout << "NO" << endl;
        return;
    }
 
    cout << "YES" << endl;
    string ans = "";
    while (s[enx][eny] != 'A')
    {
        auto [x, y] = par[enx][eny];
        if (enx == x + 1 && eny == y)
            ans.pb('D');
        else if (enx == x - 1 && eny == y)
            ans.pb('U');
        else if (enx == x && eny == y - 1)
            ans.pb('L');
        else
            ans.pb('R');
 
        enx = x;
        eny = y;
    }
    reverse(all(ans));
    cout << ans.size() << endl;
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
