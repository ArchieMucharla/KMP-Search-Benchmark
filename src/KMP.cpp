#include "KMP.h"
#include <string>
#include <vector>

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
    // lps.push_back(0);

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
    std::vector<int> result;
    return result;
}
