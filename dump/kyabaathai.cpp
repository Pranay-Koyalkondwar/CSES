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
    int n, Q;
    cin >> n >> Q;

    vector<int>g(n), indeg(n);
    vector<vector<int>>rev(n), up(n, vector<int>(21, 0));
    for(int i = 0; i < n; i++){
        int v;
        cin >> v;
        --v;
        g[i] = v;
        rev[v].pb(i);
        indeg[v]++;
        up[i][0] = v;
    }

    queue<int>q;
    for(int i = 0; i < n; i++){
        if(!indeg[i])q.push(i);
    }

    while(!q.empty()){
        int x = q.front();
        q.pop();

        if(--indeg[g[x]] == 0){
            q.push(g[x]);
        }
    }

    vector<int>cycLen(n + 1), pos(n), comp(n);
    int c = 0;
    for(int i = 0; i < n; i++){
        if(indeg[i] && comp[i] == 0){
            c++;
            int node = i, p = 0;
            do
            {
                comp[node] = c;
                pos[node] = p++;
                node = g[node];
            } while (node != i);
            cycLen[c] = p;  
        }
    }

    for(int i = 0; i < n; i++){
        if(indeg[i]) q.push(i);
    }

    vector<int>dis(n);
    while(!q.empty()){
        int x = q.front();
        q.pop();

        for(auto &v : rev[x]){
            if(!indeg[v]){
                comp[v] = comp[x];
                dis[v] = dis[x] + 1;
                q.push(v);
            }
        }
    }

    for(int j = 1; j <= 20; j++){
        for(int i = 0; i < n; i++){
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    auto check = [&](int node, int diff){
        for(int i = 20; i >= 0; i--){
            if((1 << i) & diff){
                node = up[node][i];
            }
        }
        return node;
    };

    while(Q--){
        int u, v;
        cin >> u >> v;
        --u; --v;

        if(comp[u] != comp[v]){
            cout << -1 << endl;
            continue;
        }

        if(dis[u] >= dis[v]){
            int node = check(u, dis[u] - dis[v]);

            if(node == v){
                cout << dis[u] - dis[v] << endl;
            }else if(dis[v] == 0){
                int len = cycLen[comp[u]];
                int ans = (pos[v] - pos[node] + len) % len;
                cout << ans + dis[u] << endl;
            }else{
                cout << -1 << endl;
            }
        }else{
            cout << -1 << endl;
        }
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