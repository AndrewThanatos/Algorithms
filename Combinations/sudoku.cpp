#include <iostream>
#include <fstream>

using namespace std;
bool finished = false;
int in_rec = 0;
int min_fc = 81;
const int MAXCANDIDATES = 81;
#define DIMENSION 9
#define NCELLS DIMENSION*DIMENSION

struct point{
    int x, y;
};

struct boardtype{
    int m[DIMENSION+1][DIMENSION+1];
    int freecount;
    point move[NCELLS+1];
};

void next_square(int *x, int *y, boardtype *board){
    for (int i=1; i<=DIMENSION; i++)
        for (int j=1; j<=DIMENSION; j++)
            if (!board->m[i][j]){
                *x = i;
                *y = j;
                return;
            }
}

void print_board(boardtype *board){
    for (int i=1; i<=DIMENSION; i++){
        for (int j=1; j<=DIMENSION; j++)
            cout << board->m[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void possible_values(int x, int y, boardtype *board, bool possible[]){
    for (int i=1; i<=DIMENSION; i++) possible[i] = true;
    for (int i=1; i<=DIMENSION; i++){
        possible[board->m[i][y]] = false;
        possible[board->m[x][i]] = false;
    }

    int start_square_x = ((x-1) / 3) * 3 + 1;
    int end_square_x = start_square_x + 3;
    int start_square_y = ((y-1) / 3) * 3 + 1;
    int end_square_y = start_square_y + 3;
    for (int i=start_square_x; i<end_square_x; i++)
        for (int j=start_square_y; j<end_square_y; j++)
            possible[board->m[i][j]] = false;
}

void construct_candidates(int a[], int k, boardtype *board, int c[], int *ncandidates){
    int x=0, y=0;
    int i;
    bool possible[DIMENSION+1];

    next_square(&x, &y, board);

    board->move[k].x = x;
    board->move[k].y = y;

    int count = 0;
    if ((x<=0) && (y<=0)) return;
    possible_values(x, y, board, possible);

    for (i=1; i<=DIMENSION; i++){
        if (possible[i]){
            c[count] = i;
            count++;
        }
    }
    *ncandidates = count;
}

void fill_square(int x, int y, int c, boardtype *board){
    board->m[x][y] = c;
    board->freecount--;
}

void free_square(int x, int y, boardtype *board){
    board->m[x][y] = 0;
    board->freecount++;
}

void make_move(int a[], int k, boardtype * board){
    fill_square(board->move[k].x, board->move[k].y, a[k], board);
}

void unmake_move(int a[], int k, boardtype * board){
    free_square(board->move[k].x, board->move[k].y, board);
}

bool is_a_solution(int a[], int k, boardtype *board){
    if (min_fc > board->freecount){
        min_fc = board->freecount;
        // print_board(board);
    }
    if (!board->freecount)
        return true;
    else
        return false;
}

void process_solution(int a[], int k, boardtype *board){
    print_board(board);
    finished = true;
}

void backtrack(int a[], int k, boardtype *board){
    in_rec++;
    int c[MAXCANDIDATES];
    int ncandidates;
    int i;
    if (is_a_solution(a, k, board))
        process_solution(a, k, board);
    else {
        k += 1;
        construct_candidates(a, k, board, c, &ncandidates);
        for (i=0; i<ncandidates; i++){
            a[k] = c[i];
            make_move(a, k, board);
            backtrack(a, k, board);
            unmake_move(a, k, board);
            if (finished) return;
        }
    }


}

int main(){
    ifstream read_data("sudoku_input.txt");
    boardtype b;
    b.freecount = MAXCANDIDATES;
    for (int i=1; i<=DIMENSION; i++)
        for (int j=1; j<=DIMENSION; j++){
            read_data >> b.m[i][j];
            if (b.m[i][j])
                b.freecount--;
        }
    long MAXINT = NCELLS;
    int a[MAXINT];
    backtrack(a, 0, &b);
            
    // print_board(&b);
    printf("Recurtion = %d\nMin_FC = %d", in_rec, min_fc);
}