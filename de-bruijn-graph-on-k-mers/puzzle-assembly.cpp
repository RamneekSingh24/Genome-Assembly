#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define GRID_SIZE 5


enum DIRS {
    UP,
    LEFT,
    DOWN,
    RIGHT
};

class SqPiece {
public:
    vector<string> edges;
    int id;
    SqPiece (string _up, string _left, string _down, string _right, int _id) {
        edges.assign(4,"");
        edges[UP] = _up;
        edges[LEFT] = _left;
        edges[DOWN] = _down;
        edges[RIGHT] = _right;
        id = _id;
    }

    void print() {
        cout << "(" << edges[UP] << ",";
        cout << edges[LEFT] << ",";
        cout << edges[DOWN] << ",";
        cout << edges[RIGHT] << ")";
    }

};



SqPiece *grid[GRID_SIZE][GRID_SIZE];

bool check_ok() {

    /* Assuming Outer Edges are all black
    /* Check Vertical Edges */
    for (int col = 1; col < GRID_SIZE; col++) {
        for (int row = 0; row < GRID_SIZE; row++) {
            if(grid[row][col]->edges[LEFT] != grid[row][col-1]->edges[RIGHT]) return false;
        }
    }

    /* Check Horizontal Edges */

    for (int row = 1; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if(grid[row][col]->edges[UP] != grid[row-1][col]->edges[DOWN]) return false;
        }
    }

    return true;

}

void print_sol_and_exit() {

    for (int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            grid[i][j]->print();
            if(j < GRID_SIZE -1) {
                cout << ";";
            } else {
                cout << endl;
            }

        }
    }

    exit(0);
}



int main() {


#ifdef MYPC
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    string line;
    vector<SqPiece*> puzzle_pieces;
    int id = 0;

    /* Take input */

    while ((cin >> line)) {
        line = line.substr(1, line.length() - 2);
        stringstream sstr(line);
        string token;
        vector<string> tokens;
        while (getline(sstr, token, ',')) {
            tokens.push_back(token);
        }
        SqPiece *piece = new SqPiece(tokens[UP], tokens[LEFT], tokens[DOWN], tokens[RIGHT], id);
        puzzle_pieces.push_back(piece);
        id++;
    }

    int top_left;
    int top_right;
    int bot_left;
    int bot_right;
    vector<int> top_row_pieces;
    vector<int> bot_row_pieces;
    vector<int> left_col_pieces;
    vector<int> right_col_pieces;
    vector<int> inner_pieces;


    for (SqPiece* piece : puzzle_pieces) {
        vector<string> edges = piece->edges;
        if (edges[UP] == "black") {
            if (edges[LEFT] == "black") {
                top_left = piece->id;
            } else if (edges[RIGHT] == "black") {
                top_right = piece->id;
            } else {
                top_row_pieces.push_back(piece->id);
            }
        }
        else if (edges[LEFT] == "black") {
            if (edges[DOWN] == "black") {
                bot_left = piece->id;
            }
            else {
                left_col_pieces.push_back(piece->id);
            }
        }
        else if (edges[DOWN] == "black") {
            if (edges[RIGHT] == "black") {
                bot_right = piece->id;
            }
            else {
                bot_row_pieces.push_back(piece->id);
            }
        } else if (edges[RIGHT] == "black"){
            right_col_pieces.push_back(piece->id);
        } else {
            inner_pieces.push_back(piece->id);
        }
    }



    grid[0][0] = puzzle_pieces[top_left];
    grid[0][GRID_SIZE - 1] = puzzle_pieces[top_right];
    grid[GRID_SIZE - 1][0] = puzzle_pieces[bot_left];
    grid[GRID_SIZE - 1][GRID_SIZE - 1] = puzzle_pieces[bot_right];


    do {
        do {
            do {
                do {
                    do {

                        /* Fill top row */
                        for (int i = 0; i < top_row_pieces.size(); i++) {
                            grid[0][1 + i] = puzzle_pieces[top_row_pieces[i]];
                        }

                        /* Fill bot row */
                        for (int i = 0; i < bot_row_pieces.size(); i++) {
                            grid[GRID_SIZE - 1][1 + i] = puzzle_pieces[bot_row_pieces[i]];
                        }

                        /* Fill left col */
                        for (int i = 0; i < left_col_pieces.size(); i++) {
                            grid[1 + i][0] = puzzle_pieces[left_col_pieces[i]];
                        }

                        /* Fill right col */
                        for (int i = 0; i < right_col_pieces.size(); i++) {
                            grid[1 + i][GRID_SIZE - 1] = puzzle_pieces[right_col_pieces[i]];
                        }

                        int INNER_LEN = GRID_SIZE - 2;
                        int OFFSET = 1;

                        for (int i = 0; i < inner_pieces.size(); i++) {
                            int row = OFFSET + i / INNER_LEN;
                            int col = OFFSET + (i % INNER_LEN);
                            grid[row][col] = puzzle_pieces[inner_pieces[i]];
                        }


                        if (check_ok()) {
                            print_sol_and_exit();
                        }


                    } while(next_permutation(right_col_pieces.begin(), right_col_pieces.end()));

                } while(next_permutation(bot_row_pieces.begin(), bot_row_pieces.end()));

            } while(next_permutation(left_col_pieces.begin(), left_col_pieces.end()));

        } while(next_permutation(top_row_pieces.begin(), top_row_pieces.end()));

    } while (next_permutation(inner_pieces.begin(), inner_pieces.end()));




    return 0;
}
