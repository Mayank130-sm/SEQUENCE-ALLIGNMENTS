#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* ---------- GLOBAL ALIGNMENT ---------- */
vector<vector<int>> gsa(vector<vector<int>>& matrix, string& dna1, string& dna2,
                        int gap, int match, int mismatch, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int diag = matrix[i][j] + (dna1[i] == dna2[j] ? match : mismatch);
            int up   = matrix[i][j+1] + gap;
            int left = matrix[i+1][j] + gap;
            matrix[i+1][j+1] = max({diag, up, left});
        }
    }
    return matrix;
}

void traceback(vector<vector<int>>& matrix, string& dna1, string& dna2,
               int gap, int match, int mismatch, int row, int col) {

    string a1 = "", a2 = "";
    int i = row, j = col;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 &&
            matrix[i][j] == matrix[i-1][j-1] +
            (dna1[i-1] == dna2[j-1] ? match : mismatch)) {

            a1 += dna1[i-1];
            a2 += dna2[j-1];
            i--; j--;
        }
        else if (i > 0 && matrix[i][j] == matrix[i-1][j] + gap) {
            a1 += dna1[i-1];
            a2 += '-';
            i--;
        }
        else {
            a1 += '-';
            a2 += dna2[j-1];
            j--;
        }
    }

    reverse(a1.begin(), a1.end());
    reverse(a2.begin(), a2.end());

    cout << a1 << endl;
    cout << a2 << endl;
    cout << matrix[row][col] << endl;
}

/* ---------- LOCAL ALIGNMENT ---------- */
vector<vector<int>> lsa(vector<vector<int>>& matrix, string& dna1, string& dna2,
                        int gap, int match, int mismatch, int row, int col) {

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int diag = matrix[i][j] + (dna1[i] == dna2[j] ? match : mismatch);
            int up   = matrix[i][j+1] + gap;
            int left = matrix[i+1][j] + gap;
            matrix[i+1][j+1] = max({0, diag, up, left});
        }
    }
    return matrix;
}

void localtraceback(vector<vector<int>>& matrix, string& dna1, string& dna2,
                    int gap, int match, int mismatch, int row, int col) {

    string a1 = "", a2 = "";
    int maxScore = 0, i = 0, j = 0;

    for (int r = 0; r <= row; r++) {
        for (int c = 0; c <= col; c++) {
            if (matrix[r][c] > maxScore) {
                maxScore = matrix[r][c];
                i = r; j = c;
            }
        }
    }

    while (i > 0 && j > 0 && matrix[i][j] > 0) {
        if (matrix[i][j] == matrix[i-1][j-1] +
            (dna1[i-1] == dna2[j-1] ? match : mismatch)) {
            a1 += dna1[i-1];
            a2 += dna2[j-1];
            i--; j--;
        }
        else if (matrix[i][j] == matrix[i-1][j] + gap) {
            a1 += dna1[i-1];
            a2 += '-';
            i--;
        }
        else {
            a1 += '-';
            a2 += dna2[j-1];
            j--;
        }
    }

    reverse(a1.begin(), a1.end());
    reverse(a2.begin(), a2.end());

    cout << a1 << endl;
    cout << a2 << endl;
    cout << maxScore << endl;
}

/* ---------- MAIN (CLI ENTRY) ---------- */
int main(int argc, char* argv[]) {

    // argv: dna1 dna2 gap match mismatch choice
    string dna1 = argv[1];
    string dna2 = argv[2];
    int gap = stoi(argv[3]);
    int match = stoi(argv[4]);
    int mismatch = stoi(argv[5]);
    int choice = stoi(argv[6]);

    int row = dna1.length();
    int col = dna2.length();

    vector<vector<int>> matrix(row+1, vector<int>(col+1, 0));

    if (choice == 0) { // GLOBAL
        for (int j = 0; j <= col; j++) matrix[0][j] = j * gap;
        for (int i = 0; i <= row; i++) matrix[i][0] = i * gap;

        matrix = gsa(matrix, dna1, dna2, gap, match, mismatch, row, col);
        traceback(matrix, dna1, dna2, gap, match, mismatch, row, col);
    }
    else { // LOCAL
        matrix = lsa(matrix, dna1, dna2, gap, match, mismatch, row, col);
        localtraceback(matrix, dna1, dna2, gap, match, mismatch, row, col);
    }

    return 0;
}
