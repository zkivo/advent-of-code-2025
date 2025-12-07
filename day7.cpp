#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <chrono>

using namespace std;

vector<string> read_file_lines(const string& path);

void dfs(int row, int col, int& ans, vector<string>& diagram) {
    if (row >= diagram.size()) {
        ans++;
        return;
    }
    if (diagram[row][col] == '^') {
        dfs(row + 1, col + 1, ans, diagram);
        dfs(row + 1, col - 1, ans, diagram);
    } else dfs(row + 1, col, ans, diagram);
}

int main() {
    vector<string> diagram = read_file_lines("day7.txt");

    for (string s : diagram) cout << s << endl;

    int m = diagram.size();
    int n = diagram[0].size();

    vector<long long> timelines(n, 1);

    for (int i = m - 2; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            if (diagram[i][j] == '^') timelines[j] = timelines[j - 1] + timelines[j + 1];
        }
    }

    cout << "Num timelines: " << timelines[n / 2] << endl;

    return 0;
}

int day7_1() {
    ifstream file("day7.txt");
    string line;

    if (!file.is_open()) {
        cerr << "Could not open the file!\n";
        return 1;
    }

    getline(file, line);
    string beans_line(line.size(), '.');
    beans_line[line.size() / 2] = '|';
    getline(file, line);

    int ans = 0;

    while (getline(file, line)) {
        size_t splitter_index = line.find('^');
        while (splitter_index != line.npos) {
            if (beans_line[splitter_index] == '|') {
                beans_line[splitter_index] = '.';
                beans_line[splitter_index + 1] = '|';
                beans_line[splitter_index - 1] = '|';
                ans++;
            }
            splitter_index = line.find('^', splitter_index + 1);
        }
        cout << beans_line << endl;
    }

    cout << "Splits: " << ans << endl;

    return 0;
}

vector<string> read_file_lines(const string& path) {
    ifstream in(path, ios::binary);
    if (!in) {
        throw runtime_error("Cannot open file");
    }

    in.seekg(0, ios::end);
    size_t size = static_cast<size_t>(in.tellg());
    in.seekg(0, ios::beg);

    string data(size, '\0');
    in.read(&data[0], size);

    vector<string> lines;
    lines.reserve(count(data.begin(), data.end(), '\n') + 1);

    size_t start = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] == '\n') {
            size_t len = i - start;

            // Handle Windows "\r\n": strip trailing '\r' if present
            if (len > 0 && data[i - 1] == '\r') {
                --len;
            }

            lines.emplace_back(data.substr(start, len));
            start = i + 1;
        }
    }

    if (start < data.size()) {
        size_t len = data.size() - start;
        if (len > 0 && data.back() == '\r') {
            --len;
        }
        lines.emplace_back(data.substr(start, len));
    }

    return lines;
}