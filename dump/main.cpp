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

vector<pair<int, double>> tbPPre, tbPProc, tbPPost, tbDPre, tbDProc, tbDPost;
int remoteAssign[2005];
bool isFin[2005];
int lInMap[2005];
int currLayer[2005];
bool eFree;
bool cFree[10];

vector<int> qPPre, qPPost, qDPre, qDPost;
vector<int> qPProc[10], qDProc[10];

struct EventData {
    string type;
    vector<string> tokens;
};

void splitFast(const string& s, vector<string>& tokens) {
    tokens.clear();
    int n = s.length();
    int i = 0;
    while(i < n) {
        if(s[i] == ' ') { i++; continue; }
        int start = i;
        while(i < n && s[i] != ' ') i++;
        tokens.push_back(s.substr(start, i - start));
    }
}

double getCost(const vector<pair<int, double>>& tb, int x) {
    if(tb.empty()) return 0.0;
    if(x <= tb.front().F) return tb.front().S;
    if(x >= tb.back().F) return tb.back().S;
    auto it = lower_bound(all(tb), make_pair(x, -1.0));
    auto prev = it - 1;
    double x1 = prev->F, y1 = prev->S;
    double x2 = it->F, y2 = it->S;
    return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

int getBestBatch(const vector<pair<int, double>>& tb, int maxAvail, double lat) {
    if(maxAvail == 0) return 0;
    int bestSz = 1;
    double bestC = 1e18;
    for(const auto& p : tb) {
        int b = p.F;
        if(b > maxAvail) break;
        double c = (lat + p.S) / (double)b;
        if(c < bestC) {
            bestC = c;
            bestSz = b;
        }
    }
    double cMax = (lat + getCost(tb, maxAvail)) / (double)maxAvail;
    if(cMax < bestC) bestSz = maxAvail;
    return bestSz;
}

int popSRPT(vector<int>& q) {
    if(q.empty()) return -1;
    int bestIdx = 0;
    for(int i = 1; i < (int)q.size(); i++) {
        if(lInMap[q[i]] < lInMap[q[bestIdx]]) bestIdx = i;
    }
    int val = q[bestIdx];
    q.erase(q.begin() + bestIdx);
    return val;
}

int popFIFO(vector<int>& q) {
    if(q.empty()) return -1;
    int val = q.front();
    q.erase(q.begin());
    return val;
}

void solve()
{
    int k, bytesPerToken, numLayers;
    double sVal, latencyInMs, bandwidthGbps;
    
    if (!(cin >> k >> sVal >> latencyInMs >> bandwidthGbps >> bytesPerToken >> numLayers)) return;
    
    double slo1, slo2, tpUB, tpBase, distBase, wTp, wC;
    cin >> slo1 >> slo2 >> tpUB >> tpBase >> distBase >> wTp >> wC;
    
    memset(remoteAssign, 0, sizeof(remoteAssign));
    memset(isFin, 0, sizeof(isFin));
    memset(lInMap, 0, sizeof(lInMap));
    memset(currLayer, 0, sizeof(currLayer));
    eFree = true;
    for(int i = 0; i < 10; i++) cFree[i] = true;
    
    qPPre.clear(); qPPost.clear(); qDPre.clear(); qDPost.clear();
    for(int i = 0; i < 10; i++) { qPProc[i].clear(); qDProc[i].clear(); }
    tbPPre.clear(); tbPProc.clear(); tbPPost.clear();
    tbDPre.clear(); tbDProc.clear(); tbDPost.clear();
    
    int tableRows;
    cin >> tableRows;
    for (int i = 0; i < tableRows; i++) {
        int batchSize;
        double pPre, pProc, pPost, dPre, dProc, dPost;
        cin >> batchSize >> pPre >> pProc >> pPost >> dPre >> dProc >> dPost;
        tbPPre.pb({batchSize, pPre});
        tbPProc.pb({batchSize, pProc});
        tbPPost.pb({batchSize, pPost});
        tbDPre.pb({batchSize, dPre});
        tbDProc.pb({batchSize, dProc});
        tbDPost.pb({batchSize, dPost});
    }
    sort(all(tbPPre)); sort(all(tbPProc)); sort(all(tbPPost));
    sort(all(tbDPre)); sort(all(tbDProc)); sort(all(tbDPost));
    
    while (true) {
        string tStr;
        if (!(cin >> tStr)) break;
        if (tStr == "END") break;
        
        int numEvents;
        cin >> numEvents;
        vector<EventData> events(numEvents);
        
        for (int i = 0; i < numEvents; i++) {
            cin >> events[i].type;
            string line;
            getline(cin, line);
            splitFast(line, events[i].tokens);
        }
        
        for (int i = 0; i < numEvents; i++) {
            if (events[i].type == "FIN") {
                int rid = stoi(events[i].tokens[0]);
                isFin[rid] = true;
            }
        }
        
        for (int i = 0; i < numEvents; i++) {
            if (events[i].type == "FIN") continue;
            
            const auto& tokens = events[i].tokens;
            
            if (events[i].type == "ARR") {
                int rid = stoi(tokens[0]);
                lInMap[rid] = stoi(tokens[1]);
                currLayer[rid] = 0;
                
                int bestK = 0;
                double minLoad = 1e18;
                for(int j = 0; j < k; j++) {
                    double currentLoad = 0;
                    for(int r : qPProc[j]) currentLoad += getCost(tbPProc, lInMap[r]);
                    if(!qDProc[j].empty()) currentLoad += getCost(tbDProc, qDProc[j].size());
                    
                    if(currentLoad < minLoad) { 
                        minLoad = currentLoad; 
                        bestK = j; 
                    }
                }
                remoteAssign[rid] = bestK;
                qPPre.pb(rid);
            } 
            else if (events[i].type == "TDN") {
                string cmd1 = tokens[1];
                string cmd2 = tokens[2];
                
                if (cmd1 == "P" && cmd2 == "PRE") eFree = true;
                else if (cmd1 == "P" && cmd2 == "PROC") {
                    int le = stoi(tokens[4]);
                    int remote = stoi(tokens[5]);
                    int rid = stoi(tokens[6]);
                    cFree[remote] = true;
                    if(le < numLayers) {
                        qPProc[remote].pb(rid);
                    }
                }
                else if (cmd1 == "P" && cmd2 == "POST") {
                    eFree = true;
                    qDPre.pb(stoi(tokens[4]));
                } 
                else if (cmd1 == "D" && cmd2 == "PRE") eFree = true;
                else if (cmd1 == "D" && cmd2 == "PROC") cFree[stoi(tokens[3])] = true;
                else if (cmd1 == "D" && cmd2 == "POST") {
                    eFree = true;
                    int m = stoi(tokens[4]);
                    for(int j = 0; j < m; j++) {
                        int rid = stoi(tokens[5+j]);
                        if (!isFin[rid]) qDPre.pb(rid);
                    }
                }
            } 
            else if (events[i].type == "XDN") {
                string dir = tokens[0];
                string stage = tokens[3];
                int m = stoi(tokens[4]);
                for(int j = 0; j < m; j++) {
                    int rid = stoi(tokens[5+j]);
                    if (dir == "UP" && stage == "PRE") qPProc[remoteAssign[rid]].pb(rid);
                    else if (dir == "DOWN" && stage == "PRE") qPPost.pb(rid);
                    else if (dir == "UP" && stage == "DEC") qDProc[remoteAssign[rid]].pb(rid);
                    else if (dir == "DOWN" && stage == "DEC") qDPost.pb(rid);
                }
            }
        }
        
        vector<string> assignments;
        
        if (eFree) {
            if (!qDPost.empty()) {
                eFree = false;
                int sz = getBestBatch(tbDPost, qDPost.size(), latencyInMs);
                string cmd = "E D POST -1 " + to_string(sz);
                for(int j = 0; j < sz; j++) {
                    cmd += " " + to_string(popFIFO(qDPost));
                }
                assignments.pb(cmd);
            } 
            else if (!qPPost.empty()) {
                eFree = false;
                int rid = popSRPT(qPPost);
                string cmd = "E P POST " + to_string(remoteAssign[rid]) + " " + to_string(rid);
                assignments.pb(cmd);
            } 
            else if (!qDPre.empty()) {
                eFree = false;
                int sz = getBestBatch(tbDPre, qDPre.size(), latencyInMs);
                string cmd = "E D PRE -1 " + to_string(sz);
                for(int j = 0; j < sz; j++) {
                    cmd += " " + to_string(popFIFO(qDPre));
                }
                assignments.pb(cmd);
            } 
            else if (!qPPre.empty()) {
                eFree = false;
                int rid = popSRPT(qPPre);
                string cmd = "E P PRE " + to_string(remoteAssign[rid]) + " " + to_string(rid);
                assignments.pb(cmd);
            }
        }
        
        for (int i = 0; i < k; i++) {
            if (cFree[i]) {
                if (!qDProc[i].empty()) {
                    cFree[i] = false;
                    int sz = getBestBatch(tbDProc, qDProc[i].size(), latencyInMs);
                    string cmd = "C" + to_string(i) + " D PROC " + to_string(i) + " " + to_string(sz);
                    for(int j = 0; j < sz; j++) {
                        cmd += " " + to_string(popFIFO(qDProc[i]));
                    }
                    assignments.pb(cmd);
                } 
                else if (!qPProc[i].empty()) {
                    cFree[i] = false;
                    int rid = popSRPT(qPProc[i]);
                    
                    int ls = currLayer[rid];
                    int step = numLayers;
                    if(qDProc[i].size() > 0 && sVal < qDProc[i].size() * wC * 5.0) {
                        step = max(1, numLayers / 2);
                    }
                    int le = min(numLayers, ls + step);
                    currLayer[rid] = le;
                    
                    string cmd = "C" + to_string(i) + " P PROC " + to_string(ls) + " " + to_string(le) + " " + to_string(i) + " " + to_string(rid);
                    assignments.pb(cmd);
                }
            }
        }
        
        cout << assignments.size() << endl;
        for (const string& s : assignments) cout << s << endl;
        cout << flush;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    while(t--) solve();
    return 0;
}