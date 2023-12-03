#include "KMP.h"
#include <string>
#include <vector>
#include <iostream>

// Preprocesses the pattern and populates the Longest Prefix Suffix (LPS)
// @param pattern: The string pattern that we intend to search for in the main text
// @param lps: It stores the lengths of the longest proper prefix which is also a suffix for all prefixes of the pattern
// @returns: Nothing! The function updates the lps array directly
void preprocess_pattern(const std::string& pattern, std::vector<int>& lps) {
    // Length of the previous longest prefix suffix
    int length = 0;
    
    // Start iterating from second character of the pattern
    int i = 1;

    // LPS of the first character is always 0
    lps[0] = 0;

    if(pattern.size() == 0) {
        return;
    }

    // Calculate lps[i]
    while (i < (int) pattern.size()) {
        // Check if the current character of the pattern matches with the character at 'length' index
        if (pattern[i] == pattern[length]) {
            // Found a longer prefix which is also a suffix
            length++;
            lps[i] = length;
            i++;
        }
        
        // Otherwise, handle mismatch after at least one matching character
        else {
            // Update 'length' to check the previous longest prefix suffix
            if (length != 0) length = lps[length - 1];
            else {
                // No matching prefix and suffix found! SO set LPS to 0
                lps[i] = 0;
                i++;
            }
        }
    }
}


// KMP search algorithm to find all occurrences of a pattern in a given text
// @param text: The main text where the pattern is to be searched
// @param pattern: The string pattern that we are looking for
// @param lps: The preprocessed Longest Prefix Suffix (LPS) array
// @return: A KMPResult struct containing the vector of match start indices and the total number of character comparisons
KMPResult KMP_search(const std::string& text, const std::string& pattern, const std::vector<int>& lps) {
    KMPResult result = {};
    int patternIndex = 0;
    int textIndex = 0;
    result.totalComparisons = 0;

    if(pattern.size() == 0 || text.size() == 0) {
        return result;
    }

    // Loop through the entire text
    while (textIndex < (int) text.size()) {
        result.totalComparisons++; // Increment comparison count for each character check

        // Check for character match between pattern and text
        if (pattern[patternIndex] == text[textIndex]) {
            patternIndex++;
            textIndex++;

            // Check if the entire pattern has been matched
            if (patternIndex == (int) pattern.size()) {
                // Add the starting index of the match to the result vector
                result.matchStartIndices.push_back(textIndex - patternIndex);
                //std::cout << "matched!" <<std::endl;

                // Update pattern index using the LPS array for the next possible match
                patternIndex = lps[patternIndex - 1];
            }
        } 
        // Handle mismatch after some matches using LPS array
        else if (patternIndex != 0) patternIndex = lps[patternIndex - 1];

        // Handle mismatch at the start by moving to the next character in text
        else textIndex++;
    }

    //std::cout<< result.totalComparisons <<std::endl;

    return result;
}


// Naive search algorithm to find all occurrences of a pattern in a given text
// Also counts the total number of character comparisons
// @param text: The text to search in
// @param pattern: The pattern to search for
// @return: A KMPResult struct containing the vector of match start indices and the total number of character comparisons
KMPResult naive_search(const std::string& text, const std::string& pattern) {
    KMPResult result;
    result.totalComparisons = 0;
    int textLength = text.length();
    int patternLength = pattern.length();

    // Loop through each possible start position in the text
    for (int startIndex = 0; startIndex <= textLength - patternLength; startIndex++) {
        int patternIndex;

        // Compare the pattern with the text at the current start position
        for (patternIndex = 0; patternIndex < patternLength; patternIndex++) {
            result.totalComparisons++;
            
            // Mismatch found, move to the next start position
            if (text[startIndex + patternIndex] != pattern[patternIndex]) break;
        }

        // If the entire pattern was matched at the current start position
        if (patternIndex == patternLength) result.matchStartIndices.push_back(startIndex);
    }

    return result;
}
