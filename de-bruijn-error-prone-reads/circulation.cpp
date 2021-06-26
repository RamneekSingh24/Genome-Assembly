#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Node;
class Edge;
class Graph;


class Node {
public:
    int id;
    Node (int _id) {
        id = _id;
    }
};

class Edge {

public:
    int id;
    int mn_flow;
    int mx_flow;
    Node* to;
    Node* from;
    Edge (Node* _from, Node* _to, int _id, int _mn_flow, int _mx_flow) {
        to = _to;
        from = _from;
        id = _id;
        mn_flow = _mn_flow;
        mx_flow = _mx_flow;
    }

};


class Graph {

public:
    int NUM_VERTICES;
    int NUM_EDGES;
    vector<Node*> nodes;
    vector<Edge*> edges;
    vector<vector<Edge*>> adj;

    Graph (vector<Node*> _nodes) {
        nodes = _nodes;
        NUM_VERTICES = _nodes.size();
        NUM_EDGES = 0;
        adj.assign(NUM_VERTICES,vector<Edge*>(0));
    }

    void addEdge(Edge *edge) {
        NUM_EDGES++;
        edges.push_back(edge);
        adj[edge->from->id].push_back(edge);
    }


    vector<int> findCirculation() {

        int dummy_source = NUM_VERTICES;
        int dummy_sink = NUM_VERTICES + 1;
        n = NUM_VERTICES + 2;

        capacity.assign(NUM_VERTICES + 2, vector<int>(NUM_VERTICES + 2, 0));

        for (Edge *edge : edges) {
            int from = edge->from->id;
            int to = edge->to->id;
            int mn_flow = edge->mn_flow;
            int mx_flow = edge->mx_flow;


            capacity[from][to] += mx_flow - mn_flow;
            capacity[dummy_source][to] += mn_flow;
            capacity[from][dummy_sink] += mn_flow;
        }


        int goal = 0;

        for(int i = 0; i < capacity[dummy_source].size(); i++) {
            goal += capacity[dummy_source][i];
        }


        if (max_flow(dummy_source, dummy_sink) < goal) {
            return vector<int> (0);
        }

        vector<int> flows = divide_flows();

        return flows;


    }

private:


    /** Push-Relabel algorithm implementation
     *  Source: https://cp-algorithms.com/graph/push-relabel.html
     */
    const int inf = 1000000000;

    int n;
    vector<vector<int>> capacity, flow;
    vector<int> height, excess, seen;
    queue<int> excess_vertices;


    vector<int> divide_flows() {
        vector<int> flows(NUM_EDGES, 0);
        vector<vector<vector<Edge*>>> adj_mat(NUM_VERTICES, vector<vector<Edge*>> (NUM_VERTICES));

        for (Edge* edge : edges) {
            adj_mat[edge->from->id][edge->to->id].push_back(edge);
        }

        for (int i = 0; i < NUM_EDGES; i++) {
            flows[i] += edges[i]->mn_flow;
        }
        for(int i = 0; i < NUM_VERTICES; i++) {
            for (int j = 0; j < NUM_VERTICES; j++) {
                if (flow[i][j] < 0) continue;
                for (Edge *edge : adj_mat[i][j]) {
                    int id = edge->id;
                    int x = min(flow[i][j], edge->mx_flow - edge->mn_flow);
                    flows[id] += x;
                    flow[i][j] -= x;
                }
            }
        }
        return flows;
    }


    void push(int u, int v)
    {
        int d = min(excess[u], capacity[u][v] - flow[u][v]);
        flow[u][v] += d;
        flow[v][u] -= d;
        excess[u] -= d;
        excess[v] += d;
        if (d && excess[v] == d)
            excess_vertices.push(v);
    }

    void relabel(int u)
    {
        int d = inf;
        for (int i = 0; i < n; i++) {
            if (capacity[u][i] - flow[u][i] > 0)
                d = min(d, height[i]);
        }
        if (d < inf)
            height[u] = d + 1;
    }

    void discharge(int u)
    {
        while (excess[u] > 0) {
            if (seen[u] < n) {
                int v = seen[u];
                if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                    push(u, v);
                else
                    seen[u]++;
            } else {
                relabel(u);
                seen[u] = 0;
            }
        }
    }

    int max_flow(int s, int t)
    {
        height.assign(n, 0);
        height[s] = n;
        flow.assign(n, vector<int>(n, 0));
        excess.assign(n, 0);
        excess[s] = inf;
        for (int i = 0; i < n; i++) {
            if (i != s)
                push(s, i);
        }
        seen.assign(n, 0);

        while (!excess_vertices.empty()) {
            int u = excess_vertices.front();
            excess_vertices.pop();
            if (u != s && u != t)
                discharge(u);
        }

        int max_flow = 0;
        for (int i = 0; i < n; i++)
            max_flow += flow[i][t];
        return max_flow;
    }



};





int main() {

#ifdef MYPC
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<Node*> nodes;
    vector<Edge*> edges;

    for (int i = 0; i < n; i++) {
        Node *node = new Node(i);
        nodes.push_back(node);
    }

    Graph circulation_gr(nodes);

    for (int i = 0; i < m; i++) {
        int u, v, mn_f, mx_f;
        cin >> u >> v >> mn_f >> mx_f;
        --u; --v;
        Edge *edge = new Edge(nodes[u], nodes[v], i, mn_f, mx_f);
        circulation_gr.addEdge(edge);
        edges.push_back(edge);
    }

    vector<int> flows = circulation_gr.findCirculation();

    if (flows.size() == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < flows.size(); i++) {
            cout << flows[i] << endl;
        }
    }



    return 0;
}
