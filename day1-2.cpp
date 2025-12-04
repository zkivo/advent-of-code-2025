#include <iostream>
#include <fstream>
#include <string>

int day1() {
    std::ifstream file("day1.txt");
    std::string str;

    if (!file.is_open()) {
        std::cerr << "Could not open the file!\n";
        return 1;
    }

    int dial = 50;
    int ans = 0;
    while (std::getline(file, str)) {
        std::cout << dial << " -(";
        bool pos = (dial > 0 ? true  : false);
        bool neg = (dial > 0 ? false : true);
        bool not_zero = (dial != 0 ? true : false);
        int rotation = std::stoi(str.substr(1, std::string::npos));
        if (str[0] == 'L') rotation = -rotation;
        std::cout << rotation << ")-> ";
        dial += rotation;
        std::cout << dial << " -%> ";
        ans += abs(dial) / 100;
        if (((dial < 0) && pos && not_zero) || ((dial > 0) && neg && not_zero)) {
            std::cout << "<...CHANGE...>";
            ans++;
        }
        if (dial == 0 && not_zero) ans++;
        dial %= 100;
        std::cout << dial << "\t(" << ans << ")" << std::endl;
     }

    file.close();
    
    std::cout << ans;

    return 0;
}