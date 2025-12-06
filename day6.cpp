#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <chrono>

using namespace std;

int day6_1() {
    ifstream file("day6.txt");
    string line;

    if (!file.is_open()) {
        cerr << "Could not open the file!\n";
        return 1;
    }

    vector<vector<int>> matrix;
    vector<char> operations;

    while (getline(file, line)) {
        if (line.find('+') != line.npos) {
            // operations (and last) line
            size_t i = line.find_first_not_of(' ', 0);
            while (i != line.npos) {
                operations.push_back(line[i]);
                i = line.find_first_not_of(" ", i + 1);
            }
            break;
        } else {
            vector<int> temp;
            size_t i = line.find_first_not_of(' ', 0);
            while(i != line.npos) {
                size_t idx_space = line.find(' ', i);
                if (idx_space == line.npos) {
                    temp.push_back(stoi(line.substr(i, line.npos)));
                    break;
                }
                temp.push_back(stoi(line.substr(i, idx_space - i + 1)));
                i = line.find_first_not_of(' ', idx_space);
            }
            matrix.push_back(temp);
        }
    }

    int n = matrix[0].size();
    int m = matrix.size();

    long long ans = 0;
    
    for (int col = 0; col < n; ++col) {
        long long res;
        for (int row = 0; row < m; ++row) {
            if (row == 0) {
                res = matrix[row][col];
                continue;
            }
            switch (operations[col]) {
            case '+':
                res += matrix[row][col];
                break;

            case '*':
                res *= matrix[row][col];
                break;
            }
        }
        ans += res;
    }

    cout << "Grand total: " << ans << endl;

    //for (const auto& row : matrix) {
    //    for (int val : row) {
    //        cout << val << " ";
    //    }
    //    cout << "\n";
    //}

    //for (char op : operations) {
    //    cout << op << " ";
    //}
    //cout << "\n";

    return 0;
}