#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "../src/KMP.h"

// reads the content of a given text file and returns it as a single string
std::string read_file_content(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

TEST_CASE("LPS Table - preprocess test", "[weight=5]") {
    // Choose a pattern
    std::string pattern = "ABABAC";

    // Manually computed LPS table for "ABABAC"
    std::vector<int> expectedLPS = {0, 0, 1, 2, 3, 0};

    // Vector to store the result from preprocess_pattern
    std::vector<int> lps(pattern.size(), 0);

    // Generate LPS table using preprocess_pattern
    preprocess_pattern(pattern, lps);

    // Verify that the generated LPS table matches the expected one
    REQUIRE(lps == expectedLPS);
}

TEST_CASE("Preprocessing and Single Match", "[weight=5]") {
    std::string text = read_file_content("../../data/1_spotify.csv");

    // Use a known pattern from 1_spotify.csv
    std::string pattern = "peach";
    // std::vector<int> lps;
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // Expected indices where "peach" appears in text
    std::vector<int> expected = {39};  

    REQUIRE(expected == result);
}

TEST_CASE("Preprocessing and Multiple Matches", "[weight=5]") {
    std::string text = read_file_content("../../data/1_spotify.csv");

    // Use a known pattern from 1_spotify.csv
    std::string pattern = "love";
    // std::vector<int> lps;
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // Expected indices where "love" appears in text
    std::vector<int> expected = {106, 118, 526, 1494, 1539, 1627};  

    REQUIRE(expected == result);
}

TEST_CASE("No Matches", "[weight=5]") {
    std::string text = read_file_content("../../data/1_spotify.csv");

    // Use a pattern that doesn't exist in 1_spotify.csv
    std::string pattern = "pineapple";
    // std::vector<int> lps;
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // No match, so the result should be empty
    REQUIRE(result.empty());
}
