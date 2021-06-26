#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

/* Global Variables */
int NUM_NODES;

int Th;
vector<int> Curr_path;
vector<vector<int>> Adj;
unordered_set<int> End_candidates;
unordered_map<int, vector<vector<int>>> Candidate_paths;
vector<bool> Visited;
int Start_Node;




void dfs(int u) {
    Visited[u] = true;
    Curr_path.push_back(u);

    if (Curr_path.size() - 1 > Th) {
        Curr_path.pop_back();
        Visited[u] = false;
        return;
    }
    if (End_candidates.find(u) != End_candidates.end() && u != Start_Node) {
        Candidate_paths[Start_Node + u * NUM_NODES].push_back(Curr_path);
    }

    for (int v : Adj[u]) {
        if (!Visited[v]) {
            dfs(v);
        }
    }
    Visited[u] = false;
    Curr_path.pop_back();

}

bool check_disjoint(vector<int> path1, vector<int> path2, int start_n, int end_n) {
    set<int> p1(path1.begin(), path1.end()), p2(path2.begin(), path2.end());
    for (int node : p1) {
        if (node != start_n && node != end_n) {
            if (p2.find(node) != p2.end()) return false;
        }
    }
    return true;
}





int main() {
#ifdef MYPC
    freopen("input.txt", "r", stdin);
#endif


    int k_mer_len = 15;

    vector<string> reads;
    string read;

    while(cin >> read) {
        reads.push_back(read);
    }

    int READ_LEN = read.length();


    unordered_set<string> unique_k_mers;
    unordered_set<string> nodes;
    unordered_map<string, int> node_to_id;

    for (string read : reads) {
        for (int i = 0 ; i + k_mer_len - 1 < read.length(); i++) {
            string k_mer = read.substr(i, k_mer_len);
            unique_k_mers.insert(k_mer);
        }
    }

    for (string k_mer : unique_k_mers) {
        string prefix = k_mer.substr(0, k_mer_len - 1);
        string suffix = k_mer.substr(1, k_mer_len + 1);
        nodes.insert(prefix);
        nodes.insert(suffix);
    }

    int id = 0;
    for (string node : nodes) {
        node_to_id[node] = id;
        id++;
    }

//    for (auto pp : node_to_id) {
//        cout << pp.second << " " << pp.first << endl;
//    }

    NUM_NODES = nodes.size();

    vector<set<int>> adj(NUM_NODES);
    vector<set<int>> adj_rev(NUM_NODES);

    vector<int> inDeg(NUM_NODES), outDeg(NUM_NODES);

    for (string k_mer : unique_k_mers) {
        string prefix = k_mer.substr(0, k_mer_len - 1);
        string suffix = k_mer.substr(1, k_mer_len + 1);
        int id1 = node_to_id[prefix], id2 = node_to_id[suffix];
        adj[id1].insert(id2);
        adj_rev[id2].insert(id1);
    }

    for (int i = 0; i < NUM_NODES; i++) {
        for (int v : adj[i]) {
            outDeg[i]++;
            inDeg[v]++;
        }
    }


    queue<int> tip_nodes;

    for (int i = 0; i < NUM_NODES; i++) {
        if (inDeg[i] == 0 || outDeg[i] == 0) tip_nodes.push(i);
    }


    int removed_count = 0;
    vector<bool> is_removed(NUM_NODES, false);

    while (!tip_nodes.empty()) {
        int node =  tip_nodes.front();
        tip_nodes.pop();
        if(is_removed[node]) continue;
        ++removed_count;
        is_removed[node] = true;


        if (inDeg[node] == 0) {
            for(int nb : adj[node]) {
                inDeg[nb]--;
                adj_rev[nb].erase(node);
                if (!is_removed[nb] && inDeg[nb] == 0) tip_nodes.push(nb);
            }
        } else if (outDeg[node] == 0) {
            for(int nb : adj_rev[node]) {
                outDeg[nb]--;
                adj[nb].erase(node);
                if (!is_removed[nb] && outDeg[nb] == 0) tip_nodes.push(nb);
            }
        }


    }


    cout << removed_count << endl;


    return 0;

}