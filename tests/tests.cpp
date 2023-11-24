#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "../src/KMP.h"

// reads the content of a given text file and returns it as a single all-lowercase string (with NO newline characters)
std::string read_file_content(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::string content, line;
    while (std::getline(file, line)) {
        // Convert line to lowercase
        std::transform(line.begin(), line.end(), line.begin(), 
                       [](unsigned char c){ return std::tolower(c); });
        
        // Append the line without newline character
        content += line;
    }

    if (content.empty()) std::cerr << "No content read from file: " << filename << std::endl;

    return content;
}

TEST_CASE("LPS Table - preprocess test", "[weight=5]") {
    std::string pattern = "ABABAC";

    // Manually computed LPS table for "ABABAC"
    std::vector<int> expectedLPS = {0, 0, 1, 2, 3, 0};

    std::vector<int> lps(pattern.size(), 0);

    preprocess_pattern(pattern, lps);

    REQUIRE(lps == expectedLPS);
}

TEST_CASE("Preprocessing and Single Match", "[weight=5]") {
    std::string text = read_file_content("/workspaces/CS 225/CS_225_EC/data/1_spotify");
    std::cout << "text: " << text << std::endl;

    // Use a known pattern from 1_spotify.csv
    std::string pattern = "peach";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = {0, 0, 0, 0, 0};
    REQUIRE(expectedLPS == lps);

    auto result = KMP_search(text, pattern, lps);
    // Expected indices where "peach" appears in text
    std::vector<int> expected = {53};  

    REQUIRE(expected == result);
}

TEST_CASE("Preprocessing and Multiple Matches", "[weight=5]") {
std::string text = read_file_content("/workspaces/CS 225/CS_225_EC/data/1_spotify");

    // Use a known pattern from 1_spotify.csv
    std::string pattern = "love";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // Expected indices where "love" appears in text
    std::vector<int> expected = {124, 137, 570, 1601, 1649, 1742};  

    REQUIRE(expected == result);
}

TEST_CASE("No Matches", "[weight=5]") {
std::string text = read_file_content("/workspaces/CS 225/CS_225_EC/data/1_spotify");

    // Use a pattern that doesn't exist in 1_spotify.csv
    std::string pattern = "pineapple";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // No match, so the result should be empty
    REQUIRE(result.empty());
}
