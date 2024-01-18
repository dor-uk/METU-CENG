#include "the4.h"

// do not add extra libraries here
using namespace std;
int divide_land(int X, int Y, bool** possible_plots){
    
    
    std::vector<std::vector<int>> dp(X+1, std::vector<int>(Y+1, INT_MAX));
    dp[0][0] = 0; // Starting point, no land is unused.

     
    for (int i = 1; i <= X; ++i) 
    {
        for (int j = 1; j <= Y; ++j) 
        {
            if (possible_plots[i][j]) 
            {
                dp[i][j] = 0; 
            }
            
            else
            {
                for(int k = 1; k <= i; ++k)  // vertical cuts
                {
                    if (dp[k][j] != INT_MAX && dp[i - k][j] != INT_MAX) 
                    {
                        dp[i][j] = std::min(dp[i][j], dp[k][j] + dp[i - k][j]);
                        
                    }
                }
                
                for (int k = 1; k < j; ++k)  // horizontal cuts
                {
                    if (dp[i][k] != INT_MAX && dp[i][j - k] != INT_MAX) 
                    {
                        dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[i][j - k]);
                        
                    }
                }
                
                if (dp[i][j] == INT_MAX)  // if no possible cuts 
                {
                    dp[i][j] = i * j;
                }
            }
        }
    }

    // Find the minimum waste for the full land size.
    int min_waste = INT_MAX;
    
    for (int i = 1; i <= X; ++i) 
    {
        for (int j = 1; j <= Y; ++j) 
        {
            if (i * Y == X * j && dp[i][j] != INT_MAX) 
            {
                min_waste = std::min(min_waste, X * Y - i * j + dp[i][j]);
            }
        }
    }
    return min_waste == INT_MAX ? X * Y : min_waste;
    
}
