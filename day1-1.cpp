#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("day1.txt");
    std::string str;

    if (!file.is_open()) {
        std::cerr << "Could not open the file!\n";
        return 1;
    }

    int dial = 50;
    int ans = 0;

    while (std::getline(file, str)) {
        if (str[0] == 'R') {
            dial += std::stoi(str.substr(1, std::string::npos));
        } else {
            dial -= std::stoi(str.substr(1, std::string::npos));
        }
        dial %= 100;
        if (dial < 0) {
            dial += 100;
        } else if (dial == 0) ans++;
     }

    file.close();
    
    std::cout << ans;

    return 0;
}