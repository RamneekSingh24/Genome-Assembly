#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;


class Graph {

public:
    int NUM_NODES;
    vector<vector<int>> adj;
    Graph(int n) {
        adj.assign(n,vector<int>(0));
        NUM_NODES = n;
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    vector<int> find_eulerian_cycle() {
        /** Assuming it exists **/

        vector<int> path_track;
        vector<int> eulerian_cycle;

        path_track.push_back(0);


        while (!path_track.empty()) {
            int curr_node = path_track.back();
            if (!adj[curr_node].empty()) {
                path_track.push_back(adj[curr_node].back());
                adj[curr_node].pop_back();
            } else {
                eulerian_cycle.push_back(curr_node);
                path_track.pop_back();
            }
        }

        reverse(eulerian_cycle.begin(), eulerian_cycle.end());

        return eulerian_cycle;
    }

};

int main() {

#ifdef MYPC
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif


    int k;
    cin >> k;
    int num_nodes = 1 << (k - 1); /** All binary strings of size k-1 **/

    Graph gr(num_nodes);

    for (int mask = 0; mask < (1 << k); mask++) {
        int prefix = mask >> 1;               /** (1010)0 div 2 = (1010) **/
        int suffix = mask & ~ (1 << (k - 1)); /** 1(0010) & (...) = 0010 **/
        gr.add_edge(prefix, suffix);
    }

    vector<int> eulerian_cycle = gr.find_eulerian_cycle();

    assert(eulerian_cycle[0] == 0);

    string k_universal(k - 1, '0');

    for (int i = 1; i < eulerian_cycle.size(); i++) {
        if(eulerian_cycle[i] % 2 == 0) k_universal += "0";
        else k_universal += "1";
    }



    string k_universal_cyclic = k_universal.substr(0, k_universal.length() - k +1);

    cout << k_universal_cyclic << endl;





    return 0;
}
