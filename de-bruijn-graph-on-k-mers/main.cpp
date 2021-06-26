#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Node {

public:
    string k_mer;
    int id;

    vector<Node*> adj;

    Node (string _k_mer, int _id) {
        id = _id;
        k_mer = _k_mer;
    }

    void addEdgeTo(Node *other) {
        adj.push_back(other);
    }

};








class Graph {

public:
    int NUM_NODES;
    vector<Node*> nodes;

    Graph(vector <Node*> _nodes) {
        NUM_NODES = nodes.size();
        nodes = _nodes;
    }

    void add_edge(int from_id, int to_id) {
        nodes[from_id]->addEdgeTo(nodes[to_id]);
    }

    vector<Node*> find_eulerian_cycle() {
        /** Assuming it exists **/

        vector<int> path_track;
        vector<int> eulerian_cycle;

        path_track.push_back(0);


        while (!path_track.empty()) {
            int curr_node = path_track.back();
            if (!nodes[curr_node]->adj.empty()) {
                path_track.push_back(nodes[curr_node]->adj.back()->id);
                nodes[curr_node]->adj.pop_back();
            } else {
                eulerian_cycle.push_back(curr_node);
                path_track.pop_back();
            }
        }

        reverse(eulerian_cycle.begin(), eulerian_cycle.end());

        vector<Node*> cycle_nodes;

        for(int id : eulerian_cycle) {
            cycle_nodes.push_back(nodes[id]);
        }

        return cycle_nodes;
    }

};




vector<string> take_input() {

    vector<string> k_mers;
    string k_mer;
    while (cin >> k_mer) {
        k_mers.push_back(k_mer);
    }

    return k_mers;

}






int main() {

#ifdef MYPC
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    vector<string> k_mers = take_input();

    unordered_set<string> unique_k_m1_mers;

    for (string k_mer : k_mers) {
        string prefix = k_mer.substr(0, k_mer.length() - 1);
        string suffix = k_mer.substr(1, k_mer.length() - 1);
        unique_k_m1_mers.insert(prefix);
        unique_k_m1_mers.insert(suffix);
    }

    vector<Node*> nodes;
    int id = 0;

    unordered_map<string, int> node_str_to_id;

    for (string str : unique_k_m1_mers) {
        Node* node = new Node(str, id);
        nodes.push_back(node);
        node_str_to_id[str] = id;
        id++;
    }

    Graph de_brujin_gr(nodes);

    for(string k_mer : k_mers) {
        string prefix = k_mer.substr(0, k_mer.length() - 1);
        string suffix = k_mer.substr(1, k_mer.length() - 1);

        int id1 = node_str_to_id[prefix], id2 = node_str_to_id[suffix];
        de_brujin_gr.add_edge(id1, id2);
    }


    vector<Node*> eulerian_cycle = de_brujin_gr.find_eulerian_cycle();

    string genome = "";

    for(int i = 1; i < eulerian_cycle.size(); i++) {
        genome += eulerian_cycle[i]->k_mer.back();
    }

    cout << genome << endl;

    

    return 0;
}
