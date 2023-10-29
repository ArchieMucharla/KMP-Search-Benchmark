#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "KMP.h" // Assume preprocess_pattern and KMP_search are declared and defined in here

// reads the content of a given text file and returns it as a single string
std::string read_file_content(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

TEST_CASE("Preprocessing and Single Match", "[weight=5]") {
    std::string text = read_file_content("../../data/1_spotify.csv");

    // Use a known pattern from 1_spotify.csv
    std::string pattern = "love";
    std::vector<int> lps;
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // Expected indices where "policy_pattern_1" appears in text
    std::vector<int> expected = {index1};  

    REQUIRE(expected == result);
}

TEST_CASE("Preprocessing and Multiple Matches", "[weight=5]") {
    std::string text = read_file_content("../../data/1_spotify.csv");

    // Use a known pattern from 1_spotify.csv
    std::string pattern = "policy_pattern_2";
    std::vector<int> lps;
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // Expected indices where "policy_pattern_2" appears in text
    std::vector<int> expected = {index1, index2, index3};  

    REQUIRE(expected == result);
}

TEST_CASE("No Matches", "[weight=5]") {
    std::string text = read_file_content("../../data/1_spotify.csv");

    // Use a pattern that doesn't exist in 1_spotify.csv
    std::string pattern = "non_existent_pattern";
    std::vector<int> lps;
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // No match, so the result should be empty
    REQUIRE(result.empty());
}
