#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cmath>

#define PART2

using namespace std;
using Grid = vector<vector<char>>;

long long calcArea(vector<int> point1, vector<int> point2) {
    return (long long)(abs(point1[0] - point2[0]) + 1) * (long long)(abs(point1[1] - point2[1]) + 1);
}

bool isInsideOnes(vector<int> point1, vector<int> point2, Grid& grid) {
    int sign_x = (point2[0] > point1[0] ? 1 : -1);
    int sign_y = (point2[1] > point1[1] ? 1 : -1);
    for (int i = point1[0]; sign_x * i <= sign_x * point2[0]; i += sign_x) {
        for (int j = point1[1]; sign_y * j <= sign_y * point2[1]; j += sign_y) {
            // cout << "Checking: (" << i << ", " << j << ")\n";
            if (grid[j][i] == 0) return false;
        }
    }
    return true;
}

void dfs(int x, int y, Grid& grid, int max_x, int max_y) {

}

int main() {
    ifstream file("day9.txt");

    if (!file.is_open()) {
        cerr << "Could not open the file!\n";
        return 1;
    }

    vector<vector<int>> points;
    string line;

    // this max indicies will be inclusive
    int max_x = INT_MIN; 
    int max_y = INT_MIN;

    while (getline(file, line)) {
        int x = stoi(line.substr(0, line.find(',')));
        int y = stoi(line.substr(line.find(',') + 1));
        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
        points.push_back({x, y});
        // cout << "Read point: (" << x << ", " << y << ")\n";
    }

    int n = points.size();

#ifdef PART1

    long long max_area = LLONG_MIN;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long area = calcArea(points[i], points[j]);
            // cout << "Area between point " << i << " and point " << j << ": " << area << endl;
            // cout << "Points: (" << points[i][0] << ", " << points[i][1] << ") and ("
            //      << points[j][0] << ", " << points[j][1] << ")" << endl;
            if (area > max_area) max_area = area;

        }
    }

    cout << "Max area: " << max_area << endl;

#else

    cout << "Max x: " << max_x << ", Max y: " << max_y << endl;

    Grid grid(max_y + 1, vector<char>(max_x + 1, 0));

    vector<int> prev_point = points[0];
    for (int i = 1; i <= n; ++i) {
        vector<int> curr_point = points[0];
        if (i < n) curr_point = points[i];
        if (prev_point[0] == curr_point[0]) {
            // column
            int col = prev_point[0];
            int j = prev_point[1];
            while (j != curr_point[1]) {
                grid[j][col] = 1;
                if (curr_point[1] > j) ++j;
                else --j;
            }
        } else {
            // row
            int row = prev_point[1];
            int j = prev_point[0];
            while (j != curr_point[0]) {
                grid[row][j] = 1;
                if (curr_point[0] > j) ++j;
                else --j;
            }
        }
        prev_point = curr_point;
    }

    // for (auto& r : grid) {
    //     for (auto& e : r) {
    //         cout << e;
    //     }
    //     cout << endl;
    // }

    // search for any inside point
    int i = 1737, j = 47852;
    // for (i = 0; i <= max_y; ++i) {
    //     for (j = 0; j <= max_x; ++j) {
    //         // cout << i << " " << j << endl;
    //         int k;
    //         // go up
    //         for (k = i - 1; k >= 0; --k) if (grid[k][j] == 1) break;
    //         if (k == -1) continue;
    //         // go down
    //         for (k = i + 1; k <= max_y; ++k) if (grid[k][j] == 1) break;
    //         if (k > max_y) continue;
    //         // go left
    //         for (k = j - 1; k >= 0; --k) if (grid[i][k] == 1) break;
    //         if (k == -1) continue;
    //         // go right
    //         for (k = j + 1; k <= max_x; ++k) if (grid[i][k] == 1) break;
    //         if (k > max_x) continue;
    //         goto found_idxs;
    //     }
    // }

found_idxs:
    cout << j << " " << i << endl;

    stack<pair<int, int>> st;
    st.push({j, i});
    while (!st.empty()){
        pair<int, int> node = st.top();
        st.pop();
        if (grid[node.second][node.first] == 1) continue;
        grid[node.second][node.first] = 1;
        st.push({node.first + 1, node.second});
        st.push({node.first - 1, node.second});
        st.push({node.first, node.second + 1});
        st.push({node.first, node.second - 1});
    }
    cout << "Performed DFS to fill inside area.\n";

    // for (auto& r : grid) {
    //     for (auto& e : r) {
    //         cout << e;
    //     }
    //     cout << endl;
    // }

    long long max_area = LLONG_MIN;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (!isInsideOnes(points[i], points[j], grid)) continue;
            long long area = calcArea(points[i], points[j]);
            if (area > max_area) max_area = area;
            cout << "Area between point " << i << " and point " << j << ": " << area << endl;
            cout << "Points: (" << points[i][0] << ", " << points[i][1] << ") and ("
                 << points[j][0] << ", " << points[j][1] << ")" << endl;
        }
    }

    cout << "Max area: " << max_area << endl;


#endif

    return 0;
}