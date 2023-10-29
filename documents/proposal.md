

# Academic Reference
The algorithm we plan to implement is the Knuth-Morris-Pratt (KMP) string matching algorithm. The foundational academic paper we will refer to is by Donald Knuth, Vaughan Pratt, and James H. Morris (https://epubs.siam.org/doi/10.1137/0206024).

For a different explanation of the algorithm to help us better understand, we will be referencing Jayadev Misra's explanation of the KMP algorithm that he wrote for the University of Texas (https://www.cs.utexas.edu/users/misra/Notes.dir/KMP.pdf).

In addition, for a more approachable explanation and pseudocode, we'll be referencing Wikipedia's definition (https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm).

# Algorithm Summary
The KMP Algorithm offers an efficient way to find a substring within a given text. This algorithm preprocesses the pattern to generate a Longest Prefix Suffix (LPS) array in linear time complexity O(m), where m is the length of the pattern. Then, the algorithm utilizes the LPS array to scan the main text and find matches or skip sections. This occurs in O(n) time, where n is the length of the text. This makes KMP substantially faster than naive approaches, especially for large texts.

# Function I/O
**`void preprocess_pattern(const std::string &pattern, std::vector<int> &lps)`**

**Two Parameters**:

`pattern`: The string pattern that we intend to search for in the main text.

`lps`: A vector to hold the Longest Prefix Suffix (LPS) values, effectively acting as a skip table.
  
**Returns**: Nothing. The function updates the `lps` array directly.


**`std::vector<int> KMP_search(const std::string &text, const std::string &pattern, const std::vector<int> &lps)`**

**Three Parameters**:

`text`: The main text where the pattern is to be searched.

`pattern`: The string pattern that we are looking for.

`lps`: The preprocessed LPS array.
  
**Returns**: A vector of integers indicating the starting indices of all occurrences of the pattern in the text.

Depending on our needs while developing this algorithm, we might also create helper functions for readability.

# Proposed Tests
**Test 1**: Verifies whether KMP_search finds a known pattern in a string.

**Test 2**: Verifies whether KMP_search correctly returns an empty vector for a non-matching pattern.

**Test 3**: Verifies whether KMP_search correctly finds multiple occurrences of a pattern in a string.

# Data

The initial datasets are from Kaggle. We searched for datasets with enough textual content as KMP is based on string searching.

In the /data folder:


`1_spotify`: contains top songs on Spotify (smallest - 5.72 KB)

`2_horror_movie`: contains a list of horror movies and associated information (33.2 KB)

`3_starbucks_reviews`: contains reviews from Starbucks customers (453 KB)

`4_makeup`: contains a list of makeup products and related information (922 KB)

`5_amazon`: contains a list of products and descriptions from Amazon UK (1.34 MB)


