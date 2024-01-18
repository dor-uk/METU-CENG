#include "the5.h"
//#include <iostream> //sil
// do not add extra libraries here

void customSwap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void customMin(int& a, int b) {
    if (b < a) {
        a = b;
    }
}



void topo_dfs(int u, const std::vector<std::vector<int>>& dependencyMatrix,
                std::vector<int>& index, std::vector<int>& lowLink,
                std::vector<bool>& onStack, std::vector<int>& stack,
                std::vector<std::vector<int>>& cyclicDependencies, int& currentIndex) {
    
    index[u] = lowLink[u] = currentIndex++;
    stack.push_back(u);
    onStack[u] = true;

    for (int v = 0; v < dependencyMatrix.size(); v++) 
    {
        if (dependencyMatrix[u][v]) 
        {
            if (index[v] == -1) 
            {
                topo_dfs(v, dependencyMatrix, index, lowLink, onStack, stack, cyclicDependencies, currentIndex);
                lowLink[u] = std::min(lowLink[u], lowLink[v]);
            } 
            
            else if (onStack[v]) 
            {
                customMin(lowLink[u], index[v]);
            }
        }
    }

    if (lowLink[u] == index[u]) 
    {
        std::vector<int> currentCycle;
        while (true) 
        {
            int v = stack.back();
            stack.pop_back();
            onStack[v] = false;
            currentCycle.push_back(v);
            if (v == u) break;
        }
        
        cyclicDependencies.push_back(currentCycle);
    }
}

void merge(const std::vector<std::vector<int>>& dependencyMatrix,
            std::vector<std::vector<int>>& cyclicDependencies) {
    
    int file_num = dependencyMatrix.size();
    std::vector<int> index(file_num, -1);
    std::vector<int> lowLink(file_num, -1);
    std::vector<bool> onStack(file_num, false);
    std::vector<int> stack;
    int currentIndex = 0;

    for (int i = 0; i < file_num; i++) 
    {
        if (index[i] == -1) 
        {
            topo_dfs(i, dependencyMatrix, index, lowLink, onStack, stack, cyclicDependencies, currentIndex);
        }
    }
}


/*void customSort(std::vector<int>& compileOrder, const std::vector<int>& orderIndex) {
    int file_num = static_cast<int>(compileOrder.size());
    for (int i = 0; i < file_num - 1; ++i) {
        for (int j = i + 1; j < file_num; ++j) {
            if (orderIndex[compileOrder[i]] > orderIndex[compileOrder[j]]) {
                customSwap(compileOrder[i], compileOrder[j]);
            }
        }
    }
}*/

bool isIn(std::vector<std::vector<int>> v, int node)
{
    //std::cout << node << std::endl; 
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            //std::cout << v[i][j] << "  ";
            if (v[i][j] == node) return true;
        }
        //std::cout << std::endl;
    }
    return false;
}


void run(const std::vector<std::vector<int>>& dependencyMatrix,
         bool& isCompilable, std::vector<int>& compileOrder,
         std::vector<std::vector<int>>& cyclicDependencies) {

    int file_num = dependencyMatrix.size();
    isCompilable = true;
    cyclicDependencies.clear();

    std::vector<std::vector<int>> reversedDependencyMatrix = dependencyMatrix;
    
    for (int i = 0; i < file_num; i++) 
    {
        for (int j = 0; j < file_num; j++) 
        {
            reversedDependencyMatrix[i][j] = dependencyMatrix[j][i];
        }
    }

    std::vector<std::vector<int>> stronglyConnectedComponents;
    merge(reversedDependencyMatrix, stronglyConnectedComponents);

    for (const auto& component : stronglyConnectedComponents) 
    {
        if (component.size() > 1) 
        {
            cyclicDependencies.push_back(component);
            isCompilable = false;
        }
    }

    if (!isCompilable) 
    {
        compileOrder.clear();  // Compilation order is not valid in the presence of cycles
    } 
    
    else 
    {
        // Sort the files based on their finishing times in the strongly connected components
        std::vector<int> orderIndex(file_num, -1);
        for (int i = 0; i < stronglyConnectedComponents.size(); i++) 
        {
            for (int file : stronglyConnectedComponents[i]) 
            {
                orderIndex[file] = i;
            }
        }

        compileOrder.resize(file_num);
        
        for (int i = 0; i < file_num; i++) 
        {
            compileOrder[i] = i;
        }

        
        for (int i = 0; i < file_num - 1; i++) 
        {
            for (int j = i + 1; j < file_num; j++) 
            {
                
                if (orderIndex[compileOrder[i]] > orderIndex[compileOrder[j]]) 
                {
                    customSwap(compileOrder[i], compileOrder[j]);
                }
            }
        }
    }
    std::vector<int> diagonal;
    for (int i = 0, j = 0; i < dependencyMatrix.size(); i++,j++)
    {
        if (dependencyMatrix[i][j] == 1 && !isIn(cyclicDependencies, i))
        {
            diagonal.push_back(i);
            cyclicDependencies.push_back(diagonal);
        }
    }
}


