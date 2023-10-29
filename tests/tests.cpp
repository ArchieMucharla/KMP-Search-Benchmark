#include <catch2/catch_test_macros.hpp>

#include "blackbox.h"

#include <sstream>

/**
 * Reads in the dataset smallset and searches for a known matching pattern CACATCTA
 * The pattern exists (1) time in the csv on row 1:
 * TGATTTTAAAAAAACACTTAACACATCTAGATAGAATAGTACTCTGCCCTATTTGAGGGAACAGTCTCAAACNATGAAGTACATGATATTTAATGCCCTA
 */
TEST_CASE("Descriptive Name 1", "[weight=5]")
{
	bool expected = true;
    std::string infile = "../../data/smallset.csv";
    std::string search = "CACATCTA";
    bool out = blackbox_exists(infile, search);

    REQUIRE(expected == out);
}

/**
 * Reads in the dataset smallset and searches for a known non-matching pattern GGGGGGG
 * The pattern does not exist in the csv.
 */
TEST_CASE("Descriptive Name 2", "[weight=5]")
{
	bool expected = false;
    std::string infile = "../../data/smallset.csv";
    std::string search = "AAAAAAAAAA";
    bool out = blackbox_exists(infile, search);

    REQUIRE(expected == out);
}

/**
 * Real tests will include things you havent implemented yet
 * For example, I know that I have not yet written blackbox_count yet
 * but I have a good idea of what the input / output of this function should be...
 * 
 * Reads in the dataset smallset and searches for a known matching pattern CCTT
 * The pattern exists (51) time in the csv. Accordingly it should pass a test to find it 51 times
 * and fail to find it 52 times.
 */
TEST_CASE("Descriptive Name 3", "[weight=5]")
{
	bool expected = true;
    std::string infile = "../../data/smallset.csv";
    std::string search = "CCTT";
    bool out = blackbox_count(infile, search, 51);

    REQUIRE(expected == out);

    expected = false;
    out = blackbox_count(infile, search, 52);

    REQUIRE(expected == out);
}
