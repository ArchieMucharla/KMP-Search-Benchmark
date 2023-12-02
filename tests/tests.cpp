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



//PREPROCESSING FUNCTION TESTS:
//------------------------------------------------------------------------------------------------------------------------

TEST_CASE("LPS Table - single char", "[0]") {
    std::string pattern = " ";

    std::vector<int> expectedLPS = {0};
    std::vector<int> lps(pattern.size(), 0);

    preprocess_pattern(pattern, lps);

    REQUIRE(lps == expectedLPS);
}

TEST_CASE("LPS Table - Non-repetitive Pattern", "[0-1]") {
    std::string pattern = "ABCDEFG";

    std::vector<int> expectedLPS = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> lps(pattern.size(), 0);

    preprocess_pattern(pattern, lps);

    REQUIRE(lps == expectedLPS);
}


TEST_CASE("LPS Table - preprocess test", "[0-2]") {
    std::string pattern = "ABABAC";

    std::vector<int> expectedLPS = {0, 0, 1, 2, 3, 0};
    std::vector<int> lps(pattern.size(), 0);

    preprocess_pattern(pattern, lps);

    REQUIRE(lps == expectedLPS);
}

TEST_CASE("LPS Table - preprocess test with repetitive pattern", "[0-3]") {
    std::string pattern = "AAABAAA";

    std::vector<int> expectedLPS = {0, 1, 2, 0, 1, 2, 3};
    std::vector<int> lps(pattern.size(), 0);

    preprocess_pattern(pattern, lps);

    REQUIRE(lps == expectedLPS);
}

TEST_CASE("LPS Table - Complex Repetitive Pattern", "[0-4]") {
    std::string pattern = "AABAACAABAAA";

    std::vector<int> expectedLPS = {0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5, 2};
    std::vector<int> lps(pattern.size(), 0);

    preprocess_pattern(pattern, lps);

    REQUIRE(lps == expectedLPS);
}

/*
*/
/*
*/
/*
*/
/*
*/
/*
*/
/*
*/
//KMP SEARCH TESTS:
//------------------------------------------------------------------------------------------------------------------------




//SPOTIFY DATASET (SMALLEST)
//------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Preprocessing and Single Match: Spotify (1)", "[1]") {
    std::string text = read_file_content("../data/1_spotify");

    std::string pattern = "peach";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = {0, 0, 0, 0, 0};
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {53};
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = {53};
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    // The total number of comparisons in KMP should be less than or equal to that in the naive approach
    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}


TEST_CASE("Preprocessing and Multiple Matches: Spotify (1)", "[1-1]") {
    std::string text = read_file_content("../data/1_spotify");

    std::string pattern = "love";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = {0, 0, 0, 0};
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {124, 137, 570, 1601, 1649, 1742};
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = {124, 137, 570, 1601, 1649, 1742};
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    // The total number of comparisons in KMP should be less than or equal to that in the naive approach
    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and No Matches: Spotify (1)", "[1-2]") {
    std::string text = read_file_content("../data/1_spotify");

    std::string pattern = "nomatch";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 0, 0, 0, 0 };
    REQUIRE(expectedLPS == lps);

    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {}; 
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    KMPResult naiveResult = naive_search(text, pattern);
    REQUIRE(expectedKMPIndices == naiveResult.matchStartIndices);

//    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}










//HORROR MOVIE DATASET (2nd)
//------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Preprocessing and Single Match: Horror Movie (2) --kmp has less comparisons than naive", "[2]") {
    std::string text = read_file_content("../data/2_horror_movie");
    // std::cout << "text: " << text << std::endl;

    std::string pattern = "the the";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = {0, 0, 0, 0, 1, 2, 3};
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {5661};
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = {5661};
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons < naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and Multiple Matches: Horror (2)", "[2-1]") {
    std::string text = read_file_content("../data/2_horror_movie");

    std::string pattern = "the th";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = {0, 0, 0, 0, 1, 2};
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {5661, 11347};
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = {5661, 11347};
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    // The total number of comparisons in KMP should be less than or equal to that in the naive approach
    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and No Matches: horror (2)", "[2-2]") {
    std::string text = read_file_content("../data/2_horror_movie");

    std::string pattern = "nomatch";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 0, 0, 0, 0 };
    REQUIRE(expectedLPS == lps);

    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {}; 
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    KMPResult naiveResult = naive_search(text, pattern);
    REQUIRE(expectedKMPIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}








//STARBUCKS DATASET (3rd)
//------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Preprocessing and Single Match: starb (3)", "[3]") {
    std::string text = read_file_content("../data/3_starbucks_reviews");
    // std::cout << "text: " << text << std::endl;

    std::string pattern = "fellowship";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {81285};
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = {81285};
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons < naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and Multiple Matches: starb (3)", "[3-1]") {
    std::string text = read_file_content("../data/3_starbucks_reviews");

    std::string pattern = "states";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 0, 0, 1 };
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = { 33241, 125868, 158915, 188447,
  201765, 221284, 329890, 380403 };
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = { 33241, 125868, 158915, 188447,
  201765, 221284, 329890, 380403 };
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    // The total number of comparisons in KMP should be less than or equal to that in the naive approach
    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and No Matches: starb (3)", "[3-2]") {
    std::string text = read_file_content("../data/3_starbucks_reviews");

    std::string pattern = "simoneblubie";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    REQUIRE(expectedLPS == lps);

    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {}; 
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    KMPResult naiveResult = naive_search(text, pattern);
    REQUIRE(expectedKMPIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}









//MAKEUP DATASET (4th)
//------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Preprocessing and Single Match: makeup(4)", "[4]") {
    std::string text = read_file_content("../data/4_makeup");
    // std::cout << "text: " << text << std::endl;

    std::string pattern = "the the";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 0, 1, 2, 3 };
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {474578};
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = {474578};
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons < naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and Multiple Matches: makeup(4)", "[4-1]") {
    std::string text = read_file_content("../data/4_makeup");

    std::string pattern = "the th";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS ={ 0, 0, 0, 0, 1, 2 };
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = { 6061, 7136, 7828, 35324, 45004, 191583, 193043, 474578, 569089 };
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = { 6061, 7136, 7828, 35324, 45004, 191583, 193043, 474578, 569089 };
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    // The total number of comparisons in KMP should be less than or equal to that in the naive approach
    REQUIRE(kmpResult.totalComparisons < naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and No Matches: makeup (4)", "[4-2]") {
    std::string text = read_file_content("../data/4_makeup");

    std::string pattern = "archiedacoder";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
    REQUIRE(expectedLPS == lps);

    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {}; 
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    KMPResult naiveResult = naive_search(text, pattern);
    REQUIRE(expectedKMPIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}













//AMAZON DATASET (Largest)
//------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Preprocessing and Single Match: amazon  (5) --kmp has less comparisons than naive", "[5]") {
    std::string text = read_file_content("../data/5_amazon");
    // std::cout << "text: " << text << std::endl;

    std::string pattern = "enclosue";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 0, 0, 0, 0, 1 };
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {8020};
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = {8020};
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons < naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and Multiple Matches: 5_amazon", "[5-1]") {
    std::string text = read_file_content("../data/5_amazon");

    std::string pattern = "el el";
    std::vector<int> lps(pattern.size(), 0);
    
    // Preprocess the pattern to generate the LPS array
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS = { 0, 0, 0, 1, 2 };
    REQUIRE(expectedLPS == lps);

    // Perform KMP search and check result
    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices =  { 287628, 288957, 470098, 636659, 735764, 829619, 901779, 963868,1163701 };
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    // Perform naive search and check result
    KMPResult naiveResult = naive_search(text, pattern);
    std::vector<int> expectedNaiveIndices = { 287628, 288957, 470098, 636659, 735764, 829619, 901779, 963868,1163701 };
    REQUIRE(expectedNaiveIndices == naiveResult.matchStartIndices);

    // The total number of comparisons in KMP should be less than or equal to that in the naive approach
    REQUIRE(kmpResult.totalComparisons < naiveResult.totalComparisons);
}

TEST_CASE("Preprocessing and No Matches: 5_amazon", "[5-2]") {
    std::string text = read_file_content("../data/5_amazon");

    std::string pattern = "yooooooooooo";
    std::vector<int> lps(pattern.size(), 0);
    
    preprocess_pattern(pattern, lps);
    std::vector<int> expectedLPS =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    REQUIRE(expectedLPS == lps);

    KMPResult kmpResult = KMP_search(text, pattern, lps);
    std::vector<int> expectedKMPIndices = {}; 
    REQUIRE(expectedKMPIndices == kmpResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons >= (int) text.size());

    KMPResult naiveResult = naive_search(text, pattern);
    REQUIRE(expectedKMPIndices == naiveResult.matchStartIndices);

    REQUIRE(kmpResult.totalComparisons <= naiveResult.totalComparisons);
}





