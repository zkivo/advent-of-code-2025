#include <iostream>
#include <fstream>
#include <string>

int n;

bool isAccessable(int x, int y, std::string& upper_line, std::string& middle_line, std::string& lower_line) {
    int count = 0;
    if (y == 0) {
        if (upper_line[x] != '@') return false;
        if (x == 0) {
            if (upper_line[x + 1] == '@') count++;
            if (middle_line[x] == '@') count++;
            if (middle_line[x + 1] == '@') count++;
        } else if (x < n - 1) {
            if (upper_line[x + 1] == '@') count++;
            if (upper_line[x - 1] == '@') count++;
            if (middle_line[x] == '@') count++;
            if (middle_line[x + 1] == '@') count++;
            if (middle_line[x - 1] == '@') count++;
        } else {
            if (upper_line[x - 1] == '@') count++;
            if (middle_line[x] == '@') count++;
            if (middle_line[x - 1] == '@') count++;
        }
    } else if (y == 1) {
        if (middle_line[x] != '@') return false;
        if (x == 0) {
            if (upper_line[x] == '@') count++;
            if (upper_line[x + 1] == '@') count++;
            if (middle_line[x + 1] == '@') count++;
            if (lower_line[x] == '@') count++;
            if (lower_line[x + 1] == '@') count++;
        } else if (x < n - 1) {
            if (upper_line[x] == '@') count++;
            if (upper_line[x + 1] == '@') count++;
            if (upper_line[x - 1] == '@') count++;
            if (middle_line[x + 1] == '@') count++;
            if (middle_line[x - 1] == '@') count++;
            if (lower_line[x] == '@') count++;
            if (lower_line[x + 1] == '@') count++;
            if (lower_line[x - 1] == '@') count++;
        } else {
            if (upper_line[x] == '@') count++;
            if (upper_line[x - 1] == '@') count++;
            if (middle_line[x - 1] == '@') count++;
            if (lower_line[x] == '@') count++;
            if (lower_line[x - 1] == '@') count++;
        }
        //if (count < 4) std::cout << x << " " << y << std::endl;
    } else {
        if (lower_line[x] != '@') return false;
        if (x == 0) {
            if (lower_line[x + 1] == '@') count++;
            if (middle_line[x] == '@') count++;
            if (middle_line[x + 1] == '@') count++;
        } else if (x < n - 1) {
            if (lower_line[x + 1] == '@') count++;
            if (lower_line[x - 1] == '@') count++;
            if (middle_line[x] == '@') count++;
            if (middle_line[x + 1] == '@') count++;
            if (middle_line[x - 1] == '@') count++;
        } else {
            if (lower_line[x - 1] == '@') count++;
            if (middle_line[x] == '@') count++;
            if (middle_line[x - 1] == '@') count++;
        }
    }
    return (count < 4 ? true : false);
}


int day4() {
    std::ifstream file("day4.txt");
    int ans = 0;

    if (!file.is_open()) {
        std::cerr << "Could not open the file!\n";
        return 1;
    }

    std::string upper_line;
    std::string middle_line;
    std::string lower_line;

    std::getline(file, upper_line);
    std::getline(file, middle_line);
    std::getline(file, lower_line);

    std::cout << upper_line  << std::endl;
    std::cout << middle_line << std::endl;
    std::cout << lower_line  << std::endl;

    n = upper_line.size();
        
    for (int i = 0; i < n; ++i) if (isAccessable(i, 0, upper_line, middle_line, lower_line)) ans++;
    for (int i = 0; i < n; ++i) if (isAccessable(i, 1, upper_line, middle_line, lower_line)) ans++;
    std::cout << ans << std::endl;

    std::string temp;

    while (std::getline(file, temp)) {
        std::cout << temp << std::endl;
        std::cout << ans << std::endl;
        upper_line  = middle_line;
        middle_line = lower_line;
        lower_line  = temp;
        for (int i = 0; i < n; ++i) if (isAccessable(i, 1, upper_line, middle_line, lower_line)) ans++;
    }
    for (int i = 0; i < n; ++i) if (isAccessable(i, 2, upper_line, middle_line, lower_line)) ans++;

    std::cout << "Accessable rolls: " << ans << std::endl;

    return 0;
}