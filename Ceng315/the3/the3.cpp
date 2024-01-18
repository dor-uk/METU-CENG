#include "the3.h"
//#include <iostream> 

// do not add extra libraries, but you can define helper functions below.

int char_score(char a, char b, int match, int mismatch)
{
    if (a == b)
    {
        return match;
    }
    else
    {
        return -mismatch;
    }
}


// Helper function to find the maximum of three integers
int my_max(int a, int b, int c) 
{
    if (a >= b && a >= c) 
    {
        return a;
    } 
    
    else if (b >= a && b >= c) 
    {
        return b;
    } 
    
    else 
    {
        return c;
    }
}
int recursive_alignment_helper(const std::string &sequence_A, const std::string &sequence_B,
                               int i, int j, int gap, int mismatch, int match,
                               std::string &alignment, int &call_count) {
    // Check if the call count limit is reached
    if (call_count++ > 1000000) 
    {
        alignment = "STACK LIMIT REACHED";
        return INT_MIN;
    }

    // Base cases
    if (i == 0 && j == 0) 
    {
        return 0;
    } 
    else if (i == 0) 
    {
        return -gap * j;
    } 
    else if (j == 0) 
    {
        return -gap * i;
    }

    // Recursive cases
    int score1 = recursive_alignment_helper(sequence_A, sequence_B, i - 1, j - 1, gap, mismatch, match, alignment, call_count) 
                                                                    + char_score(sequence_A[i - 1], sequence_B[j - 1], match, mismatch);
    int score2 = recursive_alignment_helper(sequence_A, sequence_B, i - 1, j, gap, mismatch, match, alignment, call_count) - gap;
    int score3 = recursive_alignment_helper(sequence_A, sequence_B, i, j - 1, gap, mismatch, match, alignment, call_count) - gap;

    int alignment_score = my_max(score1, score2, score3);


    return alignment_score;
}

/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/
int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){
    // Initialize call_count to 0 before the recursive call
    call_count = 0;

    // Initialize the alignment string
    possible_alignment = "";

    // Start the recursive call
    int highest_alignment_score = recursive_alignment_helper(sequence_A, sequence_B, sequence_A.length(), sequence_B.length(),
                                                     gap, mismatch, match, possible_alignment, call_count);
    
    
    if(call_count < 1000000)
    {
        dp_table_alignment(sequence_A, sequence_B, gap, mismatch, match, possible_alignment);
    }
    return highest_alignment_score;
}

/* 
PART 2
you are expected to create a dynamic programming table to find the highest alignment score. 
then you will need to reconstruct a possible alignment string from the table.
*/
int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    
    int highest_alignment_score;
    int n = sequence_A.size();
    int m = sequence_B.size();
    
    // Allocate memory for the DP table
    int **dp = new int*[n + 1];
    for (int i = 0; i <= n; ++i) 
    {
        dp[i] = new int[m + 1];
    }
    
    // Initialize DP table
    for (int i = 0; i <= n; ++i) 
    {
        dp[i][0] = -i * gap;
    }
    for (int j = 0; j <= m; ++j) 
    {
        dp[0][j] = -j * gap;
    }
    
    // Fill DP table
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            int scoreDiag = dp[i - 1][j - 1] + char_score(sequence_A[i - 1], sequence_B[j - 1], match, mismatch); 
            int scoreUp = dp[i - 1][j] - gap;
            int scoreLeft = dp[i][j - 1] - gap;
            dp[i][j] = my_max(scoreDiag, scoreUp, scoreLeft);
            //std::cout << dp[i][j] << "  ";
        }
        //std::cout << std::endl;
    }
    
    // traceback to allign
    possible_alignment = "";
    //std::string alignment_A = "";
    //std::string alignment_B = "";
    //string alignment_B = "";
    int i = n, j = m;
    
    
    
    while (i > 0 || j > 0) 
    {
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + char_score(sequence_A[i - 1], sequence_B[j - 1], match, mismatch)) 
        {
            possible_alignment = (sequence_A[i - 1] == sequence_B[j - 1]) ? sequence_A[i - 1] + possible_alignment : "!" + possible_alignment;
            //alignment_B = sequence_B[j - 1] + alignment_B;
            --i; --j;
        } 
        else if (i > 0 && dp[i][j] == dp[i - 1][j] - gap) 
        {
            //alignment_A = sequence_A[i - 1] + alignment_A;
            possible_alignment = '.' + possible_alignment;
            --i;
        } 
        else 
        {
            possible_alignment = '_' + possible_alignment;
            //alignment_B = sequence_B[j - 1] + alignment_B;
            --j;
        }
    }

    
    
    highest_alignment_score = dp[n][m];
    
    
    
    return highest_alignment_score;    
}
