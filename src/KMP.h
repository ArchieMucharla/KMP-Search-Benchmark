#pragma once
#include <string>
#include <vector>

// Stores result of a KMP_search instance
// @param matchStartIndices: Starting indices of all occurrences of the pattern 
// @param totalComparisons: Total number of character comparisons
struct KMPResult {
    std::vector<int> matchStartIndices;
    int totalComparisons;
};

// Preprocesses the pattern and populates the Longest Prefix Suffix (LPS)
// @param pattern: The string pattern that we intend to search for in the main text
// @param lps: It stores the lengths of the longest proper prefix which is also a suffix for all prefixes of the pattern
// @returns: Nothing! The function updates the lps array directly
void preprocess_pattern(const std::string& pattern, std::vector<int>& lps);

// Performs the Knuth-Morris-Pratt (KMP) search on a given text to find all occurrences of a pattern
// @param text: The main text where the pattern is to be searched
// @param pattern: The string pattern that we are looking for
// @param lps: The preprocessed Longest Prefix Suffix (LPS) array
// @return: A KMPResult struct containing the vector of match start indices and the total number of character comparisons
KMPResult KMP_search(const std::string& text, const std::string& pattern, const std::vector<int>& lps);

// Naive search algorithm to find all occurrences of a pattern in a given text
// Also counts the total number of character comparisons
// @param text: The text to search in
// @param pattern: The pattern to search for
// @return: A KMPResult struct containing the vector of match start indices and the total number of character comparisons
KMPResult naive_search(const std::string& text, const std::string& pattern);