#include <catch2/catch_test_macros.hpp>
#include "KMP.h"
#include <sstream>

/**
 * Reads in the dataset and searches for the pattern "latin pop"
 * The pattern exists multiple times in the csv under the playlist_subgenre column.
 */
TEST_CASE("Find Multiple Occurrences of 'latin pop'", "[weight=5]")
{
    int expected = 6;  // The pattern "latin pop" appears 6 times in your data set
    std::string infile = "../../data/your-dataset.csv";
    std::string search = "latin pop";
    int out = blackbox_count(infile, search);

    REQUIRE(expected == out);
}

/**
 * Reads in the dataset and searches for the pattern "Ariana Grande"
 * The pattern exists one time in the csv under the track_artist column.
 */
TEST_CASE("Find Single Occurrence of 'Ariana Grande'", "[weight=5]")
{
    int expected = 1;  // The pattern "Ariana Grande" appears 1 time in your data set
    std::string infile = "../../data/your-dataset.csv";
    std::string search = "Ariana Grande";
    int out = blackbox_count(infile, search);

    REQUIRE(expected == out);
}

/**
 * Reads in the dataset and searches for a pattern that does not exist "XYZZYX"
 * The pattern does not exist in the csv.
 */
TEST_CASE("No Occurrence of Non-Existent Pattern", "[weight=5]")
{
    int expected = 0;  // The pattern "XYZZYX" does not appear in your data set
    std::string infile = "../../data/your-dataset.csv";
    std::string search = "XYZZYX";
    int out = blackbox_count(infile, search);

    REQUIRE(expected == out);
}
