#include <iostream>
#include <chrono>
using namespace std::chrono;

#define DEBUG

using namespace std;
const int MAX_SIZE = 21;

int rec(char board[MAX_SIZE][MAX_SIZE], int n, int column, int res){
    if (column >= n) return ++res;

    for (int x = 0; x < n; ++x)
    {
        bool can_place = true;

        for (int i = 0; i < column; ++i) {
            if (board[x][i])
                can_place = false;
        }

        for (int i = 1; i < n && can_place; ++i) {
            if((x - i >= 0 && column - i >= 0 && board[x - i][column - i])
            || (x + i < MAX_SIZE && column - i >= 0 && board[x + i][column - i]))
                can_place = false;
        }

        if (can_place) {
            board[x][column] = 1;
            res += rec(board, n, column + 1, 0);
            board[x][column] = 0;
        }
    }
    return res;
}

int main() {
    int n;
    char board[MAX_SIZE][MAX_SIZE] = {0};
#ifndef DEBUG
    cin >> n;
    cout << rec(board, n, 0, 0);
#else
    for (int i = 1; i <= MAX_SIZE; ++i) {
        n = i;
        auto start = high_resolution_clock::now();
        int res = rec(board, n, 0, 0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "----------------" << endl;
        cout <<  i << "\t" << res << endl;
        cout << "Time elapsed: " << duration.count()  << endl;
        cout << "----------------" << endl;
    }
#endif
    return 0;
}