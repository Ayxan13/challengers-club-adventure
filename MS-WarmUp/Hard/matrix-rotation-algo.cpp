// https://www.hackerrank.com/challenges/matrix-rotation-algo/problem

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

#pragma GCC optimize("O3")

// Complete the matrixRotation function below.
struct Point {
    int row, col;
};

enum class MoveRegion {
    up, left, down, right
};

constexpr MoveRegion getReg(
    Point p,
    int const row_min,
    int const row_max,
    int const col_min,
    int const col_max) noexcept {
    assert(p.row < row_max && p.row >= row_min && p.col < col_max && p.col >= col_min);
    if (p.row == row_min)
        return (p.col == col_min) ? MoveRegion::down : MoveRegion::left;
    else if (p.row == row_max - 1)
        return (p.col == col_max - 1) ? MoveRegion::up : MoveRegion::right;
    return (p.col == col_min) ? MoveRegion::down : MoveRegion::up;
}

constexpr Point rotate(
    Point p, int r,
    int const row_min, 
    int const row_max, 
    int const col_min, 
    int const col_max) noexcept 
{
    auto const len = (row_max - row_min) * 2 + (col_max - col_min - 2) * 2;
    r %= len;    
    int step = 0;
    while (r) {
        switch (getReg(p, row_min, row_max, col_min, col_max))
        {
            case MoveRegion::up:
                step = std::min(r, p.row - row_min);
                p.row -= step;
                break;
            case MoveRegion::left:
                step = std::min(r, p.col - col_min);
                p.col -= step;
                break;
            case MoveRegion::down:
                step = std::min(r, row_max - 1 - p.row);
                p.row += step;
                break;
            case MoveRegion::right:
                step = std::min(r, col_max - 1 - p.col);
                p.col += step;
                break;
        }
        r -= step;
        assert(r >= 0);
    }
    return p;
}


using Matrix = std::vector<std::vector<int>>;

void matrixRotation(Matrix const& arr, int r) {
    Matrix rotated(arr);
    int const row_cnt = (int)arr.size();
    int const col_cnt = (int)arr[0].size();

    for (int row = 0; row < row_cnt; ++row) {
        for (int col = 0; col < col_cnt; ++col) {
            auto const dim = std::min({ row, row_cnt - row - 1, col, col_cnt - col - 1 });
            Point const p = rotate({ row, col }, r, dim, row_cnt-dim, dim, col_cnt-dim);
            rotated[p.row][p.col] = arr[row][col];
        }
    }

    for (int row = 0; row < row_cnt; ++row) {
        for (int col = 0; col < col_cnt; ++col) {
            printf("%d ", rotated[row][col]);
        }
        putchar('\n');
    }
}

int main()
{
    string mnr_temp;
    getline(cin, mnr_temp);

    vector<string> mnr = split(rtrim(mnr_temp));

    int m = stoi(mnr[0]);

    int n = stoi(mnr[1]);

    int r = stoi(mnr[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
