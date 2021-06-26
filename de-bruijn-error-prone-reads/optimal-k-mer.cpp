#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;


/** Checks if de-brujin graph of reads with len = k_mer_len has a eucledian cycle */

bool check(int k_mer_len, vector<string> reads) {

    unordered_map<string, int> indeg;
    unordered_map<string, int> outdeg;
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
        string suffix = k_mer.substr(1, k_mer_len + 1);
        indeg[suffix]++;
        outdeg[prefix]++;
        nodes.insert(prefix);
        nodes.insert(suffix);
    }


    for (string node : nodes) {
        if (indeg[node] != outdeg[node]) {
            return false;
        }
    }

    return true;



}


int main() {
#ifdef MYPC
    freopen("input.txt", "r", stdin);
#endif

    vector<string> reads;
    string read;

    while(cin >> read) {
        reads.push_back(read);
    }

    int READ_LEN = read.length();

    for (int k_mer_len = READ_LEN; k_mer_len >= 1; k_mer_len--) {
        if (check(k_mer_len, reads)) {
            cout << k_mer_len << endl;
            break;
        }
    }

}