#include "the6.h"

// do not add extra libraries here

int find_key(std::vector<std::vector<std::pair<int, int>>>& bond_energies,int i, int j){
    
    for(int a =0; a<bond_energies.size(); a++)
    {
        if(bond_energies[i][a].first == j)
        {
            return bond_energies[i][a].second;
        }
    }
    
    return 0;
}


int find_structure(std::vector<std::vector<std::pair<int, int>>>& bond_energies, std::vector<std::vector<std::pair<int, int>>>& lowest_energy_structure) {
    
    int n = bond_energies.size();

    std::vector<int> key(n, INT_MAX);
    std::vector<int> vertex(n, -1);
    std::vector<bool> visited(n, false);

    key[0] = 0;

    for (int count = 0; count < n; count++) 
    {
        int minKey = INT_MAX;
        int u = -1;

        for (int v = 0; v < n; v++) 
        {
            if (!visited[v] && key[v] < minKey) 
            {
                minKey = key[v];
                u = v;
            }
        }

        visited[u] = true;

        for (int i = 0; i < bond_energies[u].size(); i++) 
        {
            int v = bond_energies[u][i].first;
            int edge_weight = bond_energies[u][i].second;

            if (!visited[v] && edge_weight < key[v]) 
            {
                key[v] = edge_weight;
                vertex[v] = u;
            }
        }
    }
    
    
    for (int i = 0; i < n; i++) 
    {
        if (vertex[i] != -1) 
        {
            int u = i;
            int v = vertex[i];
            int weight = find_key(bond_energies,u,v);
            
            lowest_energy_structure[u].push_back(std::make_pair(v, weight));
            lowest_energy_structure[v].push_back(std::make_pair(u, weight));
        }
    }

    int lowest_total_energy = 0;
    
    for (int i = 0; i < n; i++) 
    {
        if (key[i] != INT_MAX) {
            lowest_total_energy += key[i];
        }
    }

    return lowest_total_energy;
}


void dfs(const std::vector<std::vector<std::pair<int, int>>>& graph, int u, int parent, int depth, int& max_depth, int& max_depth_node, std::vector<int>& path, std::vector<int>& temp_path) {
    temp_path.push_back(u);

    if (depth > max_depth) {
        max_depth = depth;
        max_depth_node = u;
        path = temp_path;
    }

    for (const auto& edge : graph[u]) {
        int v = edge.first;
        if (v != parent) {
            dfs(graph, v, u, depth + 1, max_depth, max_depth_node, path, temp_path);
        }
    }

    temp_path.pop_back();
}

int find_longest_chain(std::vector<std::vector<std::pair<int, int>>>& molecule_structure, std::vector<int>& chain) {
    int start_node = 0;
    int max_depth = 0, max_depth_node = 0;
    std::vector<int> path, temp_path;

    // First DFS to find the farthest node from the start node
    dfs(molecule_structure, start_node, -1, 0, max_depth, max_depth_node, path, temp_path);

    path.clear();
    temp_path.clear();
    max_depth = 0;

    // Second DFS from the farthest node found in the first DFS
    dfs(molecule_structure, max_depth_node, -1, 0, max_depth, max_depth_node, path, temp_path);

    chain = path;
    return path.size();
}
