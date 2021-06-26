#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;



#define CUTOFF_KMER_LEN 12
#define ERROR_RATE_OVERLAP 5
#define PATTERN_MATCH_ERROR_TOLERANCE 5
#define CORRECTION_CONFIDENCE 10
#define SEARCH_LEN 0

/** Headers **/
class Node;
class Edge;

/** Global Variables **/
unordered_map<string, set<int>> relevant_reads;


/** Data Structures */


class Edge {
public:
    Node *from;
    Node *to;
    int weight;
    Edge(Node *_from, Node *_to, int _weight) {
        from = _from;
        to = _to;
        weight = _weight;
    }
};




class Node {
public:
    int id;
    string seq;
    vector<Edge*> adj;
    Node(string _seq, int _id) {
        seq = _seq;
        id = _id;
    }
    /** brief: add Node 'other' to adj list of our node
     *  if it shares a prefix with a suffix of our node.
     */

    int addNeighbour (Node* other) {
        string mySeq = this->seq;
        string otherSeq = other->seq;
        int common_len = find_longest_match(mySeq, otherSeq);

        if (common_len == 0) {
            return -1;
        } else {
            Edge *edg = new Edge(this, other, common_len);
            this->adj.push_back(edg);
            return 0;
        }

    }

private:


    /* first    ||    second

    AGTCCCCCAAA || CCAAAGTTAGC

    CCAAAGTTAGC $ AGTCCCCCAAA

    least x : x + Z[x] = strlen -> ans = z[x]

    */
    /** breif : returns length of max match **/

    static int find_longest_match(const string &first, const string &second) {
        int f_len = first.length(), s_len = second.length();

        for (int i = 0; i < f_len; i++) {
            int max_errors = ERROR_RATE_OVERLAP * (f_len - i) / 100;
            for (int idx = 0; i + idx < f_len; idx++) {
                if (first[i + idx] != second[idx]) --max_errors;
                if(max_errors < 0) break;
            }
            if(max_errors >= 0) return f_len - i;
        }
        return 0;
    }

    /** Ref: https://cp-algorithms.com/string/z-function.html */
    /** Not used in this part **/

    static vector<int> z_function(string s) {
        int n = (int) s.length();
        vector<int> z(n);
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r)
                z[i] = min (r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
        return z;
    }



};





class OverlapGraph {
public:

    vector<Node*> nodes;

    OverlapGraph (vector<string> reads) {
        nodes.resize(0);
        for (int i = 0; i < reads.size(); i++) {
            Node *node = new Node(reads[i], i);
            nodes.push_back(node);
        }

        num_vertices = nodes.size();

        unordered_map<string, vector<int>> reads_with_kmer;
        vector<vector<bool>> checked(num_vertices, vector<bool>(num_vertices, false));

        for (int i = 0; i < reads.size(); i++) {
            for (int st = 0; st + CUTOFF_KMER_LEN -1 < reads[i].size(); st++) {
                reads_with_kmer[reads[i].substr(st, CUTOFF_KMER_LEN)].push_back(i);
            }
        }

        for (auto str_vec_pair : reads_with_kmer) {
            vector<int> vec = str_vec_pair.second;
            set<int> s;
            unsigned size = vec.size();
            for (int i = 0; i < size; ++i ) {
                s.insert( vec[i] );
            }
            vec.assign(s.begin(), s.end() );

            for(int i = 0; i < vec.size(); i++) {
                for(int j = 0; j < vec.size(); j++) {
                    if(i != j && !checked[vec[i]][vec[j]]) {
                        nodes[vec[i]]->addNeighbour(nodes[vec[j]]);
                        checked[vec[i]][vec[j]] = true;
                    }
                }
            }

        }






    }

    string constructGenome() {
        find_hamiltonian_path();
        return genome_from_cycle();
    }







private :
    vector<Edge*> hamiltonian_cycle;
    vector<Edge*> path_track;
    int starting_node;
    int num_vertices;
    bool FOUND;
    vector<bool> visited;



    static bool compareEdge(Edge *e1, Edge *e2) {
        return e1->weight > e2->weight;
    };

    void dfs (Node* node) {

        visited[node->id] = true;
        for(auto edge : node->adj) {
            if(FOUND) return;
            if(path_track.size() == num_vertices - 1) {
                if (edge->to->id == starting_node) {
                    FOUND = true;
                    hamiltonian_cycle = path_track;    /** = on vectors does a deep copy **/
                    hamiltonian_cycle.push_back(edge);
                    return;
                }
            } else if (!visited[edge->to->id]){
                path_track.push_back(edge);
                dfs(edge->to);
                path_track.pop_back();
            }
        }
        visited[node->id] = false;

    }

    void find_hamiltonian_path() {

        FOUND = false;
        visited.resize(num_vertices, false);

        starting_node = 0;                          /** Start at any node **/

        for (int i = 0; i < num_vertices; i++) {   /** Sort the edges in decreasing order of their weights **/
            sort(nodes[i]->adj.begin(), nodes[i]->adj.end(), compareEdge);
        }

        dfs(nodes[starting_node]);            /** Backtracking function based on greedy
                                                        choice heuristic for finding hamiltonian path.
                                                    **/

    }

    string genome_from_cycle() {
        string genome = "";
        int prev_common = 0;

        for (int i = 0; i < hamiltonian_cycle.size(); i++) {
            Node *curr = hamiltonian_cycle[i]->from;
            int curr_match_pos = genome.length() - prev_common;
            string curr_read = curr->seq;
            genome += curr_read.substr(prev_common, curr_read.length());
            prev_common = hamiltonian_cycle[i]->weight;
            relevant_reads[curr->seq].insert(curr_match_pos);

        }
        genome = genome.substr(0, genome.length() - prev_common);
/*
        int TOLERANCE = 5;
        string start_read = hamiltonian_cycle[0]->from->seq;
        int circle_back_idx = genome.length();
        for (int end_idx = genome.length() - start_read.length(); end_idx >= start_read.length(); end_idx--) {
            int num_errors = 0;
            for (int i = 0; i < start_read.length(); i++) {
                if (start_read[i] != genome[end_idx + i]) {
                    ++num_errors;
                    if (num_errors > TOLERANCE) {
                        break;
                    }
                }
            }
            if (num_errors <= TOLERANCE) {
                circle_back_idx = end_idx;
                break;
            }
        } */

        return genome;
    }



};




/**
 * @brief : take input reads sequences from stdin
 *          store input into global variable 'reads'
 */

vector<string> take_input()
{
    vector<string> reads;
    string str;
    while (cin >> str) {
        reads.push_back(str);
    }

    set<string> s;
    unsigned size = reads.size();
    for (int i = 0; i < size; ++i ) {
        s.insert( reads[i] );
    }
    reads.assign(s.begin(), s.end() );

    return reads;
}


void refine_genome(string &genome)
{

    map<int , map<char, int>> corrections;
    string circ_genome = genome + genome;

    int genome_len = genome.length();

    for(auto read_pos_pair : relevant_reads) {
        string read = read_pos_pair.first;
        int read_len = read_pos_pair.first.length();

        vector<bool> checked_match(genome_len, false);


        for(auto approx_pos : read_pos_pair.second) {

            int l_st = max(0, approx_pos - SEARCH_LEN);
            int r_st = min(genome_len - 1, approx_pos + SEARCH_LEN);


            for (int st = l_st; st <= r_st; st++) {

                int num_errors = 0;
                vector<pair<int, char>> tmp_corrections;
                bool MATCHED = true;

                for (int idx = 0; idx < read_len; idx++) {
                    if(circ_genome[st + idx] != read[idx]) {
                        num_errors++;
                        tmp_corrections.push_back(make_pair(st + idx, read[idx]));
                    }
                    if(num_errors > PATTERN_MATCH_ERROR_TOLERANCE) {
                        MATCHED = false;
                        break;
                    }
                }

                if (MATCHED) {
                    for (auto corr : tmp_corrections) {
                        corrections[corr.first][corr.second]++;
                    }
                }

            }

        }




    }


    for (auto possible_corrs: corrections) {
        char best_corr = '$';
        int  best_conf = 0;
        int idx = possible_corrs.first % genome_len;

        for (auto corr : possible_corrs.second) {
            if (corr.second > best_conf) {
                best_conf = corr.second;
                best_corr = corr.first;
            }
        }
        if(best_conf > CORRECTION_CONFIDENCE) genome[idx] = best_corr;
    }


}





int main()
{

#ifdef MYPC
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif


    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads = take_input();

    OverlapGraph graph = *(new OverlapGraph(reads));


    string genome = graph.constructGenome();


    refine_genome(genome);

    cout << genome << endl;







    return 0;
}
