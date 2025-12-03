#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

// found constraints:
// - the max diffrence in number of digits between the upper and lower bounds does not exceed 1,
//   e.g. you find 1-10 but you do not find 1-100.
// - only numbers with even number of digits can have repeted halves, e.g. 1212 but not 12312.

long long repeat_twice(long long n1) {
    std::string s = std::to_string(n1);
    s += s;  // repeat twice
    return std::stoll(s);
}

int main() {
    std::ifstream file("day2.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    char c;
    std::string left_str, right_str;
    bool dash = false;
    long long ans = 0;
    while (file.get(c)) {
        if (c == '-') {
            dash = true;
        } else if (c == ',') {
            dash = false;

            int digits_left = left_str.size();
            int digits_right = right_str.size();
            int diff_digits = digits_right - digits_left;

            std::string upper_str;
            std::string lower_str;

            if (diff_digits == 0) {
                if (digits_left % 2) {
                    // if the string lengths are odd there cannot be invalid IDs.
                    left_str.clear();
                    right_str.clear();
                    continue; 
                }
                lower_str = left_str;
                upper_str = right_str;
            } else {
                if (digits_left % 2 == 0) {
                    lower_str = left_str;
                    upper_str = std::string(digits_left, '9');
                } else {
                    upper_str = right_str;
                    lower_str = '1' + std::string(digits_right - 1, '0');;
                }
            }

            long long upper_left  = std::stoll(upper_str.substr(0, upper_str.size() / 2));
            long long lower_left  = std::stoll(lower_str.substr(0, lower_str.size() / 2));
            long long upper_right = std::stoll(upper_str.substr(upper_str.size() / 2, upper_str.npos));
            long long lower_right = std::stoll(lower_str.substr(lower_str.size() / 2, lower_str.npos));

            if (lower_right > lower_left) {
                lower_left++;
                lower_right = 0;
                if (lower_left > upper_left) {
                    left_str.clear();
                    right_str.clear();
                    continue;
                }
            }
            if (upper_left == lower_left) {
                if (upper_right >= upper_left) {
                    ans += repeat_twice(upper_left);
                }
            } else if (upper_left > lower_left) {
                for (; lower_left < upper_left; lower_left++) {
                    ans += repeat_twice(lower_left);
                }
                if (upper_right >= upper_left) {
                    ans += repeat_twice(upper_left);
                }
            } else {
                // impossible state
            }

            left_str.clear();
            right_str.clear();
        } else if (dash) {
            right_str += c;
        } else if (!dash) {
            left_str += c;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;
    std::cout << "sum invalid IDs: " << ans << std::endl;

    file.close();
    return 0;
}

int day2_old() {

    // this should return the number of invalidIDs, note this is O(n)

    std::ifstream file("day2.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    char c;
	std::string left_str, right_str;
    bool dash = false;
    int ans = 0;
    while (file.get(c)) {
        if (c == '-') {
            dash = true;
        } else if (c == ',') {
            dash = false;
			int digits_left = left_str.size();
			int digits_right = right_str.size();
			int diff_digits = digits_right - digits_left;
            int temp = 0;
            //std::cout << "difference in # of digits: " << diff_digits << std::endl;
            std::string upper_str;
			std::string lower_str;

            if (diff_digits == 0) {
                if (digits_left % 2) {
                    left_str.clear();
                    right_str.clear();
                    continue; // if str length is odd there cannot be invalid IDs.
                }
                lower_str = left_str;
                upper_str = right_str;
            } else {
                if (digits_left % 2 == 0) {
                    lower_str = left_str;
                    upper_str = std::string(digits_left, '9');
                } else {
                    upper_str = right_str;
                    lower_str = '1' + std::string(digits_right - 1, '0');;
                }
            }

            //std::cout << left_str << " " << right_str << std::endl;
            std::cout << upper_str << " " << lower_str << ", ";

            int left_upper  = std::stoi(upper_str.substr(0, upper_str.size() / 2));
            int left_lower  = std::stoi(lower_str.substr(0, lower_str.size() / 2));
            int right_upper = std::stoi(upper_str.substr(upper_str.size() / 2, upper_str.npos));
            int right_lower = std::stoi(lower_str.substr(lower_str.size() / 2, lower_str.npos));

            int mid = left_upper - left_lower - 1;
            if (mid < 0) mid = 0;
            std::cout << mid << ", ";
            temp += mid;

            if (mid == 0 && left_upper == left_lower) {
                if (right_lower <= left_upper && left_upper <= right_upper) temp++;
            } else {
                if (right_upper >= left_upper) temp++;
                if (right_lower <= left_lower) temp++;
            }

            std::cout << temp - mid << " ";

			left_str.clear();
			right_str.clear();
            upper_str.clear();
            lower_str.clear();
            std::cout << std::endl;
            ans += temp;
        } else if (dash) {
            right_str += c;
        } else if (!dash) {
            left_str += c;
        }
    }

	std::cout << "invalid IDs: " << ans << std::endl;

    file.close();
    return 0;
}
