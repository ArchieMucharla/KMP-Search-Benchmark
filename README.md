# CS 225 EC Project Summary

We implemented the Knuth-Morris-Pratt (KMP) Algorithm for finding occurrences of a string pattern within a larger string.

# Code

All of our code can be found in the `src/` directory. We defined our functions in `KMP.h` and our source code in `KMP.cpp`.

# Running Instructions

1. Start the CS 225 Docker container.
2. Open our project in the CS 225 Docker container.
3. To create the executable, run `mkdir build` followed by `cd build` and `cmake ..`
4. Run the test cases with `./test`


# Tests

Our tests can be found in the `tests/` directory. We have separated our tests into two overall sections:

* Preprocessing Function Tests
  
    * LPS table with single char
    
    * LPS table with non-repetitive pattern
    
    * LPS table with a repetitive pattern
    
    * LPS table with a complex repetitive pattern
  
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

The test data can be found in the `data/` directory. The code we used for data cleaning is called `data_cleaning.ipymb`. All data was sourced from Kaggle.com; these are their original links:

* Spotify songs: https://www.kaggle.com/datasets/sujaykapadnis/spotify-songs

* Horror Movies: https://www.kaggle.com/datasets/sujaykapadnis/horror-movies-profits-dataset

* Starbucks Reviews: https://www.kaggle.com/datasets/harshalhonde/starbucks-reviews-dataset)

* Makeup Products: https://www.kaggle.com/datasets/shivd24coder/cosmetic-brand-products-dataset?select=output.csv

* Amazon UK Products: https://www.kaggle.com/datasets/asaniczka/amazon-uk-products-dataset-2023


# Written Report

Our written report can be found in the `documents/` directory in `final_report.pdf`.


# Presentation

Our video presentation can be found in the `documents/` directory in `final_presentation.md`.


# Development Logs

Our development logs can be found in the `mentor/` directory. Feedback from project mentors can be found in `feedback.md`.


# Project Proposal

The proposal can be found in the `documents/` directory in `proposal.md`.

# Authors

The authors are Simone-Nicole Angelov and Archie Mucharla.
