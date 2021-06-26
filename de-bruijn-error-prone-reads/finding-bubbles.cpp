#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

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



    int k_mer_len, th;
    cin >> k_mer_len >> th;

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

    NUM_NODES = nodes.size();

    vector<vector<int>> adj(NUM_NODES);

    vector<int> inDeg(NUM_NODES), outDeg(NUM_NODES);

    for (string k_mer : unique_k_mers) {
        string prefix = k_mer.substr(0, k_mer_len - 1);
        string suffix = k_mer.substr(1, k_mer_len + 1);
        int id1 = node_to_id[prefix], id2 = node_to_id[suffix];
        adj[id1].push_back(id2);
    }

    for (int i = 0; i < NUM_NODES; i++) {
        if (adj[i].size() > 0) {
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
            for (int v : adj[i]) {
                outDeg[i]++;
                inDeg[v]++;
            }
        }
    }

    unordered_set<int> start_candidates, end_candidates;

    for (int i = 0; i < NUM_NODES; i++) {
        if (outDeg[i] > 1) start_candidates.insert(i);
        if (inDeg[i] > 1) end_candidates.insert(i);
    }



    Adj = adj;
    End_candidates = end_candidates;
    Th = th;


    for (int st_node : start_candidates) {
        Start_Node = st_node;
        Visited.assign(NUM_NODES, false);
        dfs(Start_Node);
    }


    int bubble_count = 0;

    for (auto data : Candidate_paths) {
        int st_node = data.first % NUM_NODES;
        int ed_node = data.first / NUM_NODES;

        if (data.second.size() > 1) {
            vector<vector<int>> paths = data.second;
            for (int i = 0; i < paths.size(); i++) {
                for (int j = i+1; j < paths.size(); j++) {
                    if (check_disjoint(paths[i], paths[j], st_node, ed_node)) bubble_count++;
                }
            }
        }
    }

    cout << bubble_count << endl;












    return 0;

}