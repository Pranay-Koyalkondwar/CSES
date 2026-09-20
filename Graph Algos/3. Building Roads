#include<bits/stdc++.h>
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
 
    vector<vector<int>>g(n);
    vector<int>vis(n, 0);
 
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }
 
    auto bfs = [&](int node){
        queue<int>q;
        q.push(node);
        vis[node] = 1;
 
        while(!q.empty()){
            int x = q.front();
            q.pop();
 
            for(auto &v : g[x]){
                if(!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    };
 
    vector<int>res;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            cnt++;
            bfs(i);
            res.pb(i);
        }
    }
 
    cout << cnt - 1 << endl;
    for(int i = 1; i < (int)res.size(); i++){
        cout << res[0] + 1 << " " << res[i] + 1 << endl;
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
