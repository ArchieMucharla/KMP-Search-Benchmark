# CS 225 EC Project Summary
Our proposed project is to implement the Knuth-Morris-Pratt (KMP) Algorithm for finding occurrences of a string pattern within a larger string.

REMEMBER TO DELETE BUILD FOLDER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CAN WE DELETE ENTRY TOO??????

# Code

All of our code can be found in `/src`. We defined our functions in `KMP.h` and our source code in `KMP.cpp`.

# Running Instructions

1. Start the CS 225 Docker container.
2. Open our project in the CS 225 Docker container.
3. To create the executable, run `mkdir build` followed by `cd build` and `cmake ..`
4. Run the test cases with `./test`


# Tests

Our tests can be found in `/tests`. We have separated our tests into two overall sections:

* Preprocessing Function Tests
  
      * LPS table with single char
  
      * LPS table with non-repetitive pattern
      * LPS table with a repetitive pattern
      * LPS table with a complex repetitive pattern
          * Sub-nested bullet etc
* KMP Search Tests
    * Spotify Dataset
          * Single match
              * Perform preprocessing and check LPS accuracy
              * Perform KMP Search and check result accuracy
              * Perform Naive Search and check result accuracy
              * Compare KMP Search runtime with Naive Search runtime
          * Multiple matches
              * Perform preprocessing and check LPS accuracy
              * Perform KMP Search and check result accuracy
              * Perform Naive Search and check result accuracy
              * Compare KMP Search runtime with Naive Search runtime
          * No matches
              * Perform preprocessing and check LPS accuracy
              * Perform KMP Search and check result accuracy
              * Perform Naive Search and check result accuracy
              * Compare KMP Search runtime with Naive Search runtime
    * Repeat for other datasets...
  

# Data 

The test data can be found in `/data`. All data was sourced from Kaggle.com. These are their original links:

Spotify songs: https://www.kaggle.com/datasets/sujaykapadnis/spotify-songs

Amazon UK Products: https://www.kaggle.com/datasets/asaniczka/amazon-uk-products-dataset-2023

Horror Movies: https://www.kaggle.com/datasets/sujaykapadnis/horror-movies-profits-dataset

Starbucks Reviews: https://www.kaggle.com/datasets/harshalhonde/starbucks-reviews-dataset)

Makeup Products: https://www.kaggle.com/datasets/shivd24coder/cosmetic-brand-products-dataset?select=output.csv


# Written Report

Our written report can be found in `/documents/report`. 


# Presentation

Our video presentation can be found in `/documents/presentation`. 


# Development Logs

Our development logs can be found in `/mentor`.


# Project Proposal
The proposal can be found in the `documents/` directory.

# Feedback
All future feedback from our project mentor can be found in the `feedback/` directory.
