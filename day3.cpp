#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("day3.txt");
    std::string str;

    if (!file.is_open()) {
        std::cerr << "Could not open the file!\n";
        return 1;
    }

	int ans = 0;
    while (std::getline(file, str)) {
		char first  = str[str.size() - 2];
		char second = str[str.size() - 1];
		char prev_max = (first > second) ? first : second;
		for (int i = str.size() - 3; i >= 0; --i) {
			if (str[i] >= first) {
				first = str[i];
				second = prev_max;
				if (str[i] > prev_max) {
					prev_max = str[i];
				}
			}
		}
		ans += (int)(first - '0') * 10 + (second - '0');
    }
	std::cout << "joltage: " << ans << std::endl;
    return 0;
}