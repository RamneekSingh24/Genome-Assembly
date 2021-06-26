#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

#define K_MER_LEN 16
#define BUBBLE_TH 16

class Graph {
public:
    int NUM_NODES;
    vector<set<int>> adj;
    unordered_map<string, int> node_str_to_id;
    vector<string> node_id_to_str;


    Graph () {}

    Graph(vector<string> reads, int k_mer_len) {

        unordered_set<string> unique_k_mers;
        unordered_set<string> nodes;

        for (string read : reads) {
            for (int i = 0 ; i + k_mer_len - 1 < read.length(); i++) {
                string k_mer = read.substr(i, k_mer_len);
                unique_k_mers.insert(k_mer);
            }
        }

        for (string k_mer : unique_k_mers) {
            string prefix = k_mer.substr(0, k_mer_len - 1);
            string suffix = k_mer.substr(1, k_mer_len - 1);
            nodes.insert(prefix);
            nodes.insert(suffix);
        }

        NUM_NODES = nodes.size();
        adj.assign(NUM_NODES,set<int>());


        int id = 0;
        for (string node : nodes) {
            node_str_to_id[node] = id;
            node_id_to_str.push_back(node);
            id++;
        }

        for (string k_mer : unique_k_mers) {
            string prefix = k_mer.substr(0, k_mer_len - 1);
            string suffix = k_mer.substr(1, k_mer_len - 1);
            int id1 = node_str_to_id[prefix], id2 = node_str_to_id[suffix];
            adj[id1].insert(id2);
        }

    }


    Graph (vector<set<int>> _adj, vector<string> _node_id_to_str) {
        adj = _adj;
        NUM_NODES = _adj.size();
        node_id_to_str = _node_id_to_str;
        node_str_to_id.clear();
        for (int i = 0 ; i < NUM_NODES; i++) {
            node_str_to_id[node_id_to_str[i]] = i;
        }
    }

};



class TipRemover {

public:

    TipRemover(){}
    Graph remove_tips(Graph &gr) {
        _remove_tips_(gr);
        vector<int> new_nodes;
        unordered_map<int, int> old_to_new_id;
        vector<string> node_id_to_str_new;
        int num_nodes_new = 0;
        int n_id = 0;
        for (int i = 0; i < gr.NUM_NODES; i++) {
            if(!removed[i]) {
                num_nodes_new++;
                new_nodes.push_back(i);
                old_to_new_id[i] = n_id;
                node_id_to_str_new.push_back(gr.node_id_to_str[i]);
                n_id++;
            }
        }

        vector<set<int>> adj_new(num_nodes_new);

        for (int u = 0; u < gr.NUM_NODES; u++) {
            if (old_to_new_id.find(u) == old_to_new_id.end()) continue;
            for (int v : gr.adj[u]) {
                if (old_to_new_id.find(v) == old_to_new_id.end()) continue;
                int u_new = old_to_new_id[u], v_new = old_to_new_id[v];
                adj_new[u_new].insert(v_new);
            }
        }

        Graph new_graph(adj_new, node_id_to_str_new);

        return new_graph;

    }

private:
    vector<bool> removed;
    void _remove_tips_(Graph &gr) {
        int num_nodes = gr.NUM_NODES;
        vector<set<int>> adj = gr.adj;
        vector<set<int>> adj_rev(num_nodes);
        vector<string> node_id_to_str = gr.node_id_to_str;

        vector<int> inDeg(num_nodes, 0), outDeg(num_nodes, 0);

        for (int u = 0; u < num_nodes; u++) {
            for (int v : adj[u]) {
                inDeg[v]++;
                outDeg[u]++;
                adj_rev[v].insert(u);
            }
        }

        removed.assign(num_nodes, false);
        queue<int> tip_nodes;

        for (int i = 0; i < num_nodes; i++) {
            if (inDeg[i] == 0 || outDeg[i] == 0) tip_nodes.push(i);
        }
        while (!tip_nodes.empty()) {
            int node =  tip_nodes.front();
            tip_nodes.pop();
            if(removed[node]) continue;

            removed[node] = true;

            if (inDeg[node] == 0) {
                for(int nb : adj[node]) {
                    inDeg[nb]--;
                    if (adj_rev[nb].find(node) != adj_rev[nb].end()) adj_rev[nb].erase(node);
                    if (!removed[nb] && inDeg[nb] == 0) tip_nodes.push(nb);
                }
            } else if (outDeg[node] == 0) {
                for(int nb : adj_rev[node]) {
                    outDeg[nb]--;
                    if (adj[nb].find(node) != adj[nb].end()) adj[nb].erase(node);
                    if (!removed[nb] && outDeg[nb] == 0) tip_nodes.push(nb);
                }
            }
        }
    }
};


class Bubble {
public:
    vector<int> p1, p2;
    int st_node, ed_node;
    Bubble(vector<int> _p1, vector<int> _p2, int _st_node, int _ed_node) {
        p1 = _p1;
        p2 = _p2;
        st_node = _st_node;
        ed_node = _ed_node;
    }
};


class BubbleRemover {



public:

    BubbleRemover() {}

    Graph remove_bubbles(Graph &graph, unordered_map<string, int> edge_counts, int th) {

        Gr = graph;
        num_nodes = graph.NUM_NODES;
        Th = th;
        Adj = graph.adj;
        Edge_count = edge_counts;
        Curr_path.resize(0);

        find_candidates();

        find_possible_paths();

        remove_paths();


        vector<int> new_nodes;
        unordered_map<int, int> old_to_new_id;
        vector<string> node_id_to_str_new;
        int num_nodes_new = 0;
        int n_id = 0;
        for (int i = 0; i < Gr.NUM_NODES; i++) {
            if(!Removed[i]) {
                num_nodes_new++;
                new_nodes.push_back(i);
                old_to_new_id[i] = n_id;
                node_id_to_str_new.push_back(Gr.node_id_to_str[i]);
                n_id++;
            }
        }

        vector<set<int>> adj_new(num_nodes_new);

        for (int u = 0; u < Gr.NUM_NODES; u++) {
            if (old_to_new_id.find(u) == old_to_new_id.end()) continue;
            for (int v : Gr.adj[u]) {
                if (old_to_new_id.find(v) == old_to_new_id.end()) continue;
                int u_new = old_to_new_id[u], v_new = old_to_new_id[v];
                adj_new[u_new].insert(v_new);
            }
        }

        Graph new_graph(adj_new, node_id_to_str_new);

        return new_graph;


    }



private:
    int num_nodes;
    int Th;
    Graph Gr;
    vector<int> Curr_path;
    vector<set<int>> Adj;
    unordered_set<int> Start_candidates;
    unordered_set<int> End_candidates;
    unordered_map<int, vector<vector<int>>> Candidate_paths;
    unordered_map<string, int> Edge_count;
    vector<bool> Visited;
    int Start_Node;
    vector<bool> Removed;

    void remove_paths() {
        Removed.assign(num_nodes, false);
        vector<Bubble> bubbles;
        for (auto data : Candidate_paths) {
            int st_node = data.first % num_nodes;
            int ed_node = data.first / num_nodes;
            vector<vector<int>> paths = data.second;
            if (paths.size() <= 1) continue;
            for (int i = 0; i < paths.size(); i++) {
                for (int j = i + 1; j < paths.size(); j++) {
                    if (check_disjoint(paths[i], paths[j], st_node, ed_node)) {
                        bubbles.push_back(Bubble(paths[i], paths[j], st_node, ed_node));
                    }
                }
            }
        }
        for (Bubble b : bubbles) {
            choose_path_remove_nodes(b);
        }
    }

    void choose_path_remove_nodes(Bubble &bubble) {
        int not_removed_paths = 2;
        bool not_removed_p1 = true, not_removed_p2 = true;
        for (int node : bubble.p1) {
            if (Removed[node]) {
                not_removed_paths--;
                not_removed_p1 = false;
                break;
            }
        }
        for (int node : bubble.p2) {
            if (Removed[node]) {
                not_removed_paths--;
                not_removed_p2 = false;
                break;
            }
        }
        if (not_removed_paths < 2) {
            return;
        }
        double w1 = calc_avg_coverage(bubble.p1), w2 = calc_avg_coverage(bubble.p2);
        if (w1 < w2) remove_nodes(bubble.p1, bubble.st_node, bubble.ed_node);
        else remove_nodes(bubble.p2, bubble.st_node, bubble.ed_node);

    }

    double calc_avg_coverage(vector<int> &path) {
        double w = 0.0;
        for (int i = 0; i < path.size() - 1; i++) {
            string prefix = Gr.node_id_to_str[path[i]];
            string suffix = Gr.node_id_to_str[path[i + 1]];
            string k_mer = prefix + suffix.substr(suffix.length() - 1, 1);
            w += Edge_count[k_mer];
        }
        return w / (path.size() - 1);

    }


    void remove_nodes(vector<int> &path, int st_n, int ed_n) {
        for (int node : path) {
            if (node == st_n || node == ed_n) continue;
            Removed[node] = true;
        }
    }



    void find_candidates() {

        vector<int> inDeg(num_nodes, 0), outDeg(num_nodes, 0);
        for (int u = 0; u < num_nodes; u++) {
            for (int v : Adj[u]) {
                inDeg[v]++;
                outDeg[u]++;
            }
        }

        for (int i = 0; i < num_nodes; i++) {
            if (outDeg[i] > 1) Start_candidates.insert(i);
            if (inDeg[i] > 1) End_candidates.insert(i);
        }

    }

    void dfs(int u) {
        Visited[u] = true;
        Curr_path.push_back(u);

        if (Curr_path.size() - 1 > Th) {
            Curr_path.pop_back();
            Visited[u] = false;
            return;
        }
        if (End_candidates.find(u) != End_candidates.end() && u != Start_Node) {
            Candidate_paths[Start_Node + u * num_nodes].push_back(Curr_path);
        }

        for (int v : Adj[u]) {
            if (!Visited[v]) {
                dfs(v);
            }
        }
        Visited[u] = false;
        Curr_path.pop_back();

    }

    void find_possible_paths() {
        for (int u : Start_candidates) {
            Visited.assign(num_nodes, false);
            dfs(u);
        }
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

};




class GenomeAssembler {
public:
    GenomeAssembler() {}
    string getGenome(Graph &gr) {
        if (gr.NUM_NODES < 10) {
            //string str(20000, 'C');
            //cout << str << endl;
            //exit(0);
        }

        vector<int> eulerian_cycle = find_eu_cycle(gr);

        string genome = "";
        for (int i = 1; i < eulerian_cycle.size(); i++) {
            string str = gr.node_id_to_str[eulerian_cycle[i]];
            genome += str.substr(str.length() - 1, 1);
        }
        return genome;
    }


private:
    vector<int> find_eu_cycle(Graph &gr) {
        vector<int> path_track;
        vector<int> eulerian_cycle;
        int num_nodes = gr.NUM_NODES;
        vector<vector<int>> adj(num_nodes);

        for (int i = 0 ; i < num_nodes; i++) {
            adj[i] = vector<int> (gr.adj[i].begin(), gr.adj[i].end());
        }


        path_track.push_back(0);

        while (!path_track.empty()) {
            int curr_node = path_track.back();
            if (adj[curr_node].size() > 0) {
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



unordered_map<string, int> get_edge_counts(vector<string> reads, int k_mer_len) {
    unordered_map<string, int> edge_counts;
    for (string read : reads) {
        for (int i = 0 ; i + k_mer_len - 1 < read.length(); i++) {
            string k_mer = read.substr(i, k_mer_len);
            edge_counts[k_mer]++;
        }
    }
    return edge_counts;
}



vector<string> take_input() {
    string str;
    vector<string> reads;
    while (cin >> str) {
        reads.push_back(str);
    }
    return reads;
}


int main() {
#ifdef MYPC
    freopen("input.txt", "r", stdin);
#endif


    vector<string> reads = take_input();

    Graph gr(reads, K_MER_LEN);

    gr = TipRemover().remove_tips(gr);

    gr = BubbleRemover().remove_bubbles(gr, get_edge_counts(reads, K_MER_LEN), BUBBLE_TH);

    gr = TipRemover().remove_tips(gr);

    string genome = GenomeAssembler().getGenome(gr);

    cout << genome << endl;

    return 0;
}
