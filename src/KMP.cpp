#include "KMP.h"
#include <string>
#include <vector>
#include <iostream>

// PURPOSE-- To preprocess the given pattern string and populate the Longest Prefix Suffix (LPS) array, enabling efficient pattern searching using the KMP algorithm.
// PATTERN -- The string pattern that we intend to search for in the main text.
// LPS -- It stores the lengths of the longest proper prefix which is also a suffix for all prefixes of the pattern. This array is used to skip characters while searching, avoiding unnecessary comparisons after a mismatch.
// RETURNS -- Nothing. The function updates the lps array directly.
// Inspired by wikipedia: https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void preprocess_pattern(const std::string& pattern, std::vector<int>& lps) {
    // Length of the previous longest prefix suffix
    int length = 0;
    
    // Start iterating from second character of the pattern
    int i = 1;

    // LPS of the first character is always 0
    lps[0] = 0;

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


// PURPOSE -- To find all occurrences of a given pattern in a given text string using the Knuth-Morris-Pratt (KMP) algorithm, leveraging a preprocessed LPS array for efficient searching.
// TEXT -- The main text where the pattern is to be searched.
// PATTERN -- The string pattern that we are looking for.
// LPS -- The preprocessed LPS array.
// RETURNS -- A vector of integers indicating the starting indices of all occurrences of the pattern in the text.
std::vector<int> KMP_search(const std::string& text, const std::string& pattern, const std::vector<int>& lps) {
    // Vector to store the starting indices of pattern matches in the text
    std::vector<int> matchStartIndices;

    // Initialize indices for pattern and text
    int patternIndex = 0;
    int textIndex = 0;

    while (textIndex < (int) text.size()) {
        // Check for character match between pattern and text
        if (pattern[patternIndex] == text[textIndex]) {
            patternIndex++;
            textIndex++;

            // If entire pattern is matched
            if (patternIndex == (int) pattern.size()) {
                // Add starting index of match to the vector
                matchStartIndices.push_back(textIndex - patternIndex);

                // Update pattern index using the LPS array for the next possible match
                patternIndex = lps[patternIndex - 1];
            }
        } 

        // Handle mismatch after some matches
        // Use LPS array to skip unmatched characters in the pattern
        else if (patternIndex != 0) patternIndex = lps[patternIndex - 1];
        
        // Handle mismatch at the start
        else textIndex++;
    }

    return matchStartIndices;
}

// KMP_SEARCH() WITH DEBUGGING PRINT STATEMENTS -------------------------------------------------
// std::vector<int> KMP_search(const std::string& text, const std::string& pattern, const std::vector<int>& lps) {
//     std::vector<int> matchStartIndices;
//     int patternIndex = 0;
//     int textIndex = 0;

//     while (textIndex < (int) text.size()) {
//         std::cout << "Text Index: " << textIndex << ", letter: " << text[textIndex] << " Pattern Index: " << patternIndex << " , letter: " << pattern[patternIndex] << std::endl;

//         if (pattern[patternIndex] == text[textIndex]) {
//             patternIndex++;
//             textIndex++;

//             if (patternIndex == (int) pattern.size()) {
//                 matchStartIndices.push_back(textIndex - patternIndex);
//                 std::cout << "Match found at: " << textIndex - patternIndex << std::endl;
//                 patternIndex = lps[patternIndex - 1];
//             }
//         } else if (patternIndex != 0) {
//             std::cout << "Mismatch after some matches. Skipping characters in pattern using LPS." << std::endl;
//             patternIndex = lps[patternIndex - 1];
//         } else {
//             std::cout << "Mismatch at the start. Moving to next character in text." << std::endl;
//             textIndex++;
//         }
//     }

//     std::cout << "Search complete. Total matches found: " << matchStartIndices.size() << std::endl;
//     return matchStartIndices;
// }
