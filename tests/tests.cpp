#include <catch2/catch_test_macros.hpp>
#include <KMP.h>
#include <vector>

// Assume preprocess_pattern and KMP_search are declared and defined
// If they are in another file, you should include that file here

TEST_CASE("KMP Preprocessing and Single Match", "[weight=5]") {
    std::string pattern = "CACATCTA";
    std::vector<int> lps;
    
    preprocess_pattern(pattern, lps);

    std::string text = "TGATTTTAAAAAAACACTTAACACATCTAGATAGAATAGTACTCTGCCCTATTTGAGGGAACAGTCTCAAACNATGAAGTACATGATATTTAATGCCCTA";
    auto result = KMP_search(text, pattern, lps);
    std::vector<int> expected = {27};  // 27 is the index where the pattern starts in the text

    REQUIRE(expected == result);
}

TEST_CASE("KMP Preprocessing and No Match", "[weight=5]") {
    std::string pattern = "AAAAAAAAAA";
    std::vector<int> lps;

    preprocess_pattern(pattern, lps);

    std::string text = "TGATTTTAAAAAAACACTTAACACATCTAGATAGAATAGTACTCTGCCCTATTTGAGGGAACAGTCTCAAACNATGAAGTACATGATATTTAATGCCCTA";
    auto result = KMP_search(text, pattern, lps);
    std::vector<int> expected;  // empty vector since there should be no match

    REQUIRE(expected == result);
}

TEST_CASE("KMP Preprocessing and Multiple Matches", "[weight=5]") {
    std::string pattern = "CCTT";
    std::vector<int> lps;

    preprocess_pattern(pattern, lps);

    std::string text = "CCTTCCTTTGATTTTCCTT";
    auto result = KMP_search(text, pattern, lps);
    std::vector<int> expected = {0, 4, 15};  // multiple occurrences at these indices

    REQUIRE(expected == result);
}
