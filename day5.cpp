#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <chrono>

using namespace std;

int day5() {
    ifstream file("day5.txt");
    string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the file!\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    priority_queue<vector<long long>, vector<vector<long long>>, std::greater<vector<long long>>> min_heap;
    vector<vector<long long>> ranges;

    while (getline(file, line)) {
        if (line.empty()) break;
        int dash_idx = line.find('-');
        min_heap.push({ stoll(line.substr(0, dash_idx)), stoll(line.substr(dash_idx + 1, line.npos)) });
    }

    while (true) {
        vector<long long> first = min_heap.top();
        min_heap.pop();
        if (min_heap.empty()) {
            ranges.push_back(first);
            break;
        }
        vector<long long> second = min_heap.top();
        min_heap.pop();
        if (first[1] < second[0]) {
            ranges.push_back(first);
            min_heap.push(second);
        } else {
            long long farest_range = max(first[1], second[1]);
            min_heap.push({first[0], farest_range});
        }
    }

    //cout << "Ranges:" << endl;
    //for (auto& v : ranges) {
    //    cout << "[" << v[0] << "-" << v[1] << "]" << endl;
    //}
    //cout << endl;

    long long ans1 = 0;

    while (getline(file, line)) {
        long long id = stoll(line);
        auto lower_it = std::lower_bound(
            ranges.begin(),
            ranges.end(),
            id,
            [](const std::vector<long long>& range, long long value) {
                return range[1] < value;
            }
        );
        if (lower_it != ranges.end() && (*lower_it)[0] <= id) {
            ans1++;
            //cout << id << " in [" << (*lower_it)[0] << ", " << (*lower_it)[1] << "]\n";
        } else {
            //cout << id << " not in Ranges.\n";
        }
    }

    long long ans2 = 0;
    for (auto& v : ranges) ans2 += v[1] - v[0] + 1;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;
    cout << "\nFresh ingredients from database: " << ans1 << endl;
    cout << "\nTotal fresh ingredients: " << ans2 << endl;


    return 0;
}