#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

// Assume preprocess_pattern and KMP_search are declared and defined
// If they are in another file, you should include that file here

std::string read_file_content(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

TEST_CASE("KMP Preprocessing and Single Match", "[weight=5]") {
    std::string text = read_file_content("path/to/your/policies.txt");

    // Use a known pattern from policies.txt
    std::string pattern = "policy_pattern_1";
    std::vector<int> lps;
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // Expected indices where "policy_pattern_1" appears in text
    std::vector<int> expected = {index1};  

    REQUIRE(expected == result);
}

TEST_CASE("KMP Preprocessing and Multiple Matches", "[weight=5]") {
    std::string text = read_file_content("path/to/your/policies.txt");

    // Use a known pattern from policies.txt
    std::string pattern = "policy_pattern_2";
    std::vector<int> lps;
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // Expected indices where "policy_pattern_2" appears in text
    std::vector<int> expected = {index1, index2, index3};  

    REQUIRE(expected == result);
}

TEST_CASE("KMP No Match", "[weight=5]") {
    std::string text = read_file_content("path/to/your/policies.txt");

    // Use a pattern that doesn't exist in policies.txt
    std::string pattern = "non_existent_pattern";
    std::vector<int> lps;
    
    preprocess_pattern(pattern, lps);

    auto result = KMP_search(text, pattern, lps);

    // No match, so the result should be empty
    REQUIRE(result.empty());
}
