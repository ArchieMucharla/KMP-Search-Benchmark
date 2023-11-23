#include <iostream>
#include <string>
#include <vector>
#include "KMP.h"

int main() {
    std::string text = "your_text_here"; // Replace with actual text or read from a file
    std::string pattern = "search_pattern"; // Replace with the pattern you want to search

    // Preprocess the pattern
    std::vector<int> lps;
    preprocess_pattern(pattern, lps);

    // Perform the KMP search
    auto result = KMP_search(text, pattern, lps);

    // Output the results
    std::cout << "Pattern found at indices: ";
    for (int index : result) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return 0;
}
