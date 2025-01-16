#include <iostream>
#include <string>
#include <regex>
#include <chrono>

#include <iostream>
#include <string>

// Function to remove content before and including the extracted number
std::string removeContentBeforeNumber(std::string input, int number) {
    std::string numberStr = std::to_string(number);
    std::size_t pos = input.find(numberStr);

    if (pos != std::string::npos) {
        std::size_t end_pos = pos + numberStr.length();
        return input.substr(end_pos);
    }

    return input;  // Return original string if number not found
}

// Function using regex to extract the first number after an underscore
int extractNumberWithRegex(const std::string& input) {
    std::regex rgx("_([0-9]+)");
    std::smatch match;

    if (std::regex_search(input, match, rgx)) {
        return std::stoi(match[1].str());
    }

    return -1;  // Return -1 if no number is found
}

// Function using find_first_of / find_first_not_of to extract the first number after an underscore '_'
int extractNumberWithFind(const std::string& input) {
    std::string digits = "0123456789";
    std::size_t underscore_pos = input.find_first_of('_');
    if (underscore_pos != std::string::npos) {
        std::size_t num_pos = input.find_first_of(digits, underscore_pos + 1);

        if (num_pos != std::string::npos) {
            std::size_t num_end = input.find_first_not_of(digits, num_pos);
            return std::stoi(input.substr(num_pos, num_end - num_pos));
        }
    }
    return -1;
}

int main() {
    std::string str1 = "Pwm_PSU0_Fan_1";
    std::string str2 = "FAN_1_PWM";
    std::string str3 = "Pwm_11_12";

    // Measure performance for regex version
    auto start_regex = std::chrono::high_resolution_clock::now();
    int number1_regex = extractNumberWithRegex(str1);
    int number2_regex = extractNumberWithRegex(str2);
    int number3_regex = extractNumberWithRegex(str3);
    auto end_regex = std::chrono::high_resolution_clock::now();
    auto duration_regex = std::chrono::duration_cast<std::chrono::nanoseconds>(end_regex - start_regex).count();

    // Measure performance for find_first_of version
    auto start_find = std::chrono::high_resolution_clock::now();
    int number1_find = extractNumberWithFind(str1);
    int number2_find = extractNumberWithFind(str2);
    int number3_find = extractNumberWithFind(str3);
    auto end_find = std::chrono::high_resolution_clock::now();
    auto duration_find = std::chrono::duration_cast<std::chrono::nanoseconds>(end_find - start_find).count();
    std::string removed1 = removeContentBeforeNumber(str1, number1_find);
    std::string removed2 = removeContentBeforeNumber(str2, number2_find);
    std::string removed3 = removeContentBeforeNumber(str3, number3_find);

    // Output results
    std::cout << "Regex Version Results:" << std::endl;
    std::cout << "Str1: " << number1_regex << ", Str2: " << number2_regex << ", Str3: " << number3_regex << std::endl;
    std::cout << "Duration (nanoseconds): " << duration_regex << std::endl;

    std::cout << "Find Version Results:" << std::endl;
    std::cout << "Str1: " << number1_find << ", Str2: " << number2_find << ", Str3: " << number3_find << std::endl;
    std::cout << "Duration (nanoseconds): " << duration_find << std::endl;

    std::cout << "String after removal: \"" << removed1 << "\"" << std::endl;
    std::cout << "String after removal: \"" << removed2 << "\"" << std::endl;
    std::cout << "String after removal: \"" << removed3 << "\"" << std::endl;

    return 0;
}
