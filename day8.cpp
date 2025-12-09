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

class UnionFind {
public:
    int components;
    vector<int> parents;
    vector<int> sizes;

    UnionFind(int components) : components(components), sizes(components, 1) {
        parents.resize(components);
        for (int i = 0; i < components; ++i) {
            parents[i] = i;
        }
    }

    int find(int node) {
        if (parents[node] == node) return node;
        return parents[node] = find(parents[node]);
    }

    bool join(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb) return false;
        if (sizes[pa] < sizes[pb]) {
            parents[pa] = pb;
            sizes[pb] += sizes[pa];
            sizes[pa] = 0;
        } else {
            parents[pb] = pa;
            sizes[pa] += sizes[pb];
            sizes[pb] = 0;
        }
        components--;
        return true;
    }

};

int main() {
    ifstream file("day8.txt");

    if (!file.is_open()) {
        cerr << "Could not open the file!\n";
        return 1;
    }

    vector<vector<int> > points;
    string line;
    while (getline(file, line)) {
        int idx1 = line.find(',');
        int idx2 = line.find(',', idx1 + 1);
        int n1 = stoi(line.substr(0, line.find(',')));
        int n2 = stoi(line.substr(idx1 + 1, idx2 - idx1 - 1));
        int n3 = stoi(line.substr(idx2 + 1, line.npos));
        points.push_back({n1, n2, n3});
    }

    vector<vector<double>> edges;

    int n = points.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double n1 = pow(points[i][0] - points[j][0], 2);
            double n2 = pow(points[i][1] - points[j][1], 2);
            double n3 = pow(points[i][2] - points[j][2], 2);
            edges.push_back({sqrt(n1 + n2 + n3), (double)i, (double)j});
        }
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(n);

#ifdef PART1
    int edges_added = 0;
    for (auto& e : edges) {
        if (edges_added == 1000) break;
        uf.join((int)e[1], (int)e[2]);
        edges_added++;
    }

    int max_size1 = uf.sizes[0];
    int max_size2 = uf.sizes[1];
    int max_size3 = uf.sizes[2];

    for (int i = 3; i < n; ++i) {
        if (uf.sizes[i] > max_size1) {
            max_size3 = max_size2;
            max_size2 = max_size1;
            max_size1 = uf.sizes[i];
        } else if (uf.sizes[i] > max_size2) {
            max_size3 = max_size2;
            max_size2 = uf.sizes[i];
        } else if (uf.sizes[i] > max_size3) {
            max_size3 = uf.sizes[i];
        }
    }

    cout << max_size1 << " " << max_size2 << " " << max_size3 << endl;

    cout << "Result: " << max_size1 * max_size2 * max_size3 << endl;

#else

    int prev_x1 = -1;
    int prev_x2 = -1;

    for (auto& e : edges) {
        if (uf.components == 1) break;
        uf.join((int)e[1], (int)e[2]);
        prev_x1 = (int)points[(int)e[1]][0];
        prev_x2 = (int)points[(int)e[2]][0];
    }

    cout << "Result: " << (long long)prev_x1 * prev_x2 << endl;

#endif
    return 0;
}