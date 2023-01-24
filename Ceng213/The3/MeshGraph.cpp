#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>


MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    // TODO:
    int i = 0;
    while(i < vertexPositions.size())
    {
        Vertex temp;
        temp.id =i;
        temp.position3D = vertexPositions[i];
        
        vertices.push_back(temp);
        
        i++;
    }
    
    int count= 0;
    while(count  < vertices.size())
    {
        std::list<Vertex*> temp_list;
        
        Vertex* vertex = &(vertices[count]);
        
        temp_list.push_back(vertex);
        adjList.push_back(temp_list);
        count++;
    }
    
    
    int j = 0;
    while(j < edges.size())
    {
        
        Vertex* second = &(vertices[edges[j].vertexId1]);
        adjList[edges[j].vertexId0].push_back(second);
        
        Vertex* first = &(vertices[edges[j].vertexId0]);
        adjList[edges[j].vertexId1].push_back(first);
        
        j++;
        
    }
    //std::cout<<vertices[0].position3D.x<<'\n';
    //std::cout<<adjList.size()<<'\n';
    
    
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    
    Double3 total_dist;
    double result = 0;
    
    int i = 0;
    int j = 0;
    
    //std::cout<<vertices.size()<<'\n';
    //std::cout<<adjList.size()<<'\n';
    while(i < adjList.size())
    {
        
        std::list<Vertex*>::const_iterator iter,steady;
        iter = adjList[i].begin();
        steady = adjList[i].begin();
        
        //std::cout<<(*iter)->position3D.x<<'\n';
        iter++;
        
        while(iter != adjList[i].end())
        {
            
            result += total_dist.Distance((*steady)->position3D, (*iter)->position3D);
            //std::cout<<(*steady)->id<<' '<<(*iter)->id<<'-';
            
            
            iter++;
            
            //std::cout<<result<<'\n';
            j++;
        }
        
        i++;
    }
    //std::cout<<j<<'\n';
    
    
    return (result / j);
    
    
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    double result = 0;
    int i = 0;
    //int j = 0;
    
    //std::cout<<vertices.size()<<'\n';
    //std::cout<<adjList.size()<<'\n';
    while(i < adjList.size())
    {
        
        std::list<Vertex*>::const_iterator iter,steady;
        iter = adjList[i].begin();
        steady = adjList[i].begin();
        
        iter++;
        
        while(iter != adjList[i].end())
        {
            
            result++;
            
            iter++;
            //j++;
            
        }
        
        i++;
    }
    //std::cout<<j<<'\n';
    //std::cout<<result<<'\n';
    return (result/(vertices.size()*2));
    
    
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    
    
    int result = 0;
    int i = 0;
    //int j = 0;
    
    //std::cout<<vertices.size()<<'\n';
    //std::cout<<adjList.size()<<'\n';
    while(i < adjList.size())
    {
        
        std::list<Vertex*>::const_iterator iter,steady;
        iter = adjList[i].begin();
        steady = adjList[i].begin();
        
        iter++;
        
        while(iter != adjList[i].end())
        {
            
            result++;
            
            iter++;
            
            
        }
        
        i++;
    }
    return (result/2);
    
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    
    bool flag = false;
    int result = 0;
    int i;
    
    for(i = 0;i < vertices.size(); i++)
    {
        if(vertices[i].id == vertexId)
        {
            flag = true;
            break;
        }
    }
    
    if(flag == false)
    {
        return -1;
    }
    
    std::list<Vertex*>::const_iterator iter,steady;
    iter = adjList[vertexId].begin();
    steady = adjList[vertexId].begin();
        
    iter++;
        
    while(iter != adjList[i].end())
    {
        //std::cout<<(*iter)->id<<'\n';
        result++;
        
        iter++;
        
        
    }
    
    return result;
    
    
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    // TODO:
    bool flag = false;
    
    int i;
    
    for(i = 0;i < vertices.size(); i++)
    {
        if(vertices[i].id == vertexId)
        {
            flag = true;
            break;
        }
    }
    
    if(flag == false)
    {
        return;
    }
    
    std::list<Vertex*>::const_iterator iter,steady;
    iter = adjList[vertexId].begin();
    steady = adjList[vertexId].begin();
        
    iter++;
        
    while(iter != adjList[i].end())
    {
        
        outVertexIds.push_back((*iter)->id);
        
        iter++;
    
    }
    
    return;
    
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    // TODO:
    
    //---------------------initial part-------------------------------
    bool flag1 = false;
    bool flag2 = false;
    
    int i;
    
    for(i = 0;i < vertices.size(); i++)
    {
        if(vertices[i].id == vertexIdFrom)
        {
            flag1 = true;
        }
        
        if(vertices[i].id == vertexIdTo)
        {
            flag2 = true;
        }
        
        if(flag1 == true && flag2 == true)
        {
            break;
        }
    }
    
    if(vertexIdFrom == vertexIdTo || flag1 != true || flag2 != true)
    {
        return;
    }
    
    for(int i = 0;i < vertices.size();i++)
    {
        Color temp;
        temp.r = 0;
        temp.g = 0;
        temp.b = 0;
        
        outputColorAllVertex.push_back(temp);
        
    }
    
    //-----------------------------shortest path part------------------------------
    
    const int tot_vertex = vertices.size();
    //std::cout<<tot_vertex<<'\n';
    
    std::vector<double> distance(tot_vertex);
    
    std::vector<std::vector<int> >  path(tot_vertex); // keep the path from one node to another
    
    for(int i = 0;i < tot_vertex;i++)
    {
        distance[i] = INFINITY;
        path[i].push_back(vertexIdFrom);  //the path of all nodes will be vertexidfrom
        
    }
    
    BinaryHeap djikstra_heap; //create heap
    
    for(int i = 0;i < tot_vertex;i++)    //initialize the heap
    {
        djikstra_heap.Add(i, INFINITY);
    }
    //std::cout<<djikstra_heap.HeapSize()<<'\n';
    
    // a vertex's distance to itself will be 0
    distance[vertexIdFrom] = 0;
    djikstra_heap.ChangePriority(vertexIdFrom, 0);
    
    while(djikstra_heap.HeapSize() != 0)
    {
        int out_index;
        double out_weight;
        
        djikstra_heap.PopHeap(out_index, out_weight);  //min is out and the out_index/out_weight values are updated
        
        //std::cout<<out_index<<'-'<<out_weight<<'\n';
        
        std::list<Vertex*>::const_iterator iter;  //neighbours of the node that is removed will be traveled
        iter = adjList[out_index].begin();
        iter++;
        
        while(iter != adjList[out_index].end())
        {
        
            int adj_id = (*iter)->id;
            
            
            if(out_weight != INFINITY &&
               (out_weight + ((*iter)->position3D).Distance(vertices[out_index].position3D, vertices[adj_id].position3D) < distance[adj_id]))
            {
                distance[adj_id] = out_weight + ((*iter)->position3D).Distance(vertices[out_index].position3D, (*iter)->position3D);
                
                //update the distance in both heap and vector
                
                djikstra_heap.ChangePriority(adj_id, distance[adj_id]);
                
                path[adj_id] = path[out_index];  //update the path
                path[adj_id].push_back(adj_id);
                
            }
        
            iter++;
        }
        
    }
    
    
    
    for(int i = 0;i < path[vertexIdTo].size();i++)
    {
        outputColorAllVertex[path[vertexIdTo][i]] = color;
        //std::cout<<path[vertexIdTo][i]<<'\n';
        //std::cout<<path.size()<<'\n';
    }
    
    
    
    
    
    
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
    
    //---------------------initial part-------------------------------
    bool flag1 = false;
    
    
    int i;
    
    for(i = 0;i < vertices.size(); i++)
    {
        if(vertices[i].id == vertexId)
        {
            flag1 = true;
        }
        
        
        
        if(flag1 == true)
        {
            break;
        }
    }
    
    if(flag1 != true)
    {
        return;
    }
    
    for(int i = 0;i < vertices.size();i++)
    {
        Color temp;
        temp.r = 0;
        temp.g = 0;
        temp.b = 0;
        
        outputColorAllVertex.push_back(temp);
        
    }
    
    //------------------------main part---------------------------------------------
    
    std::vector<bool> visited(vertices.size());  //visited array'i
    std::vector<int> previous(vertices.size());
    
    for (int i = 0; i < vertices.size(); i++)
    {
        visited[i] = false;  //initialize 
    }
    
    BinaryHeap fake_queue;
    int dummy_weight = 0;
    
    visited[vertexId] = true;
    
    fake_queue.Add(vertexId, dummy_weight);  //add the first vertex to heap
    
    
    while(fake_queue.HeapSize() != 0)  //breadth first search
    {
        int out_index;
        double out_weight;
        
        fake_queue.PopHeap(out_index, out_weight);
        
        std::list<Vertex*>::const_iterator iter; //iterate in adjList
        
        
        iter = adjList[out_index].begin();
        iter++;
        
        //std::cout<<out_index<<'\n';
        while(iter != adjList[out_index].end())  
        {
            int adj_id = (*iter)->id;
            
            dummy_weight++;
                
            //std::cout<<out_index<<"---"<<adj_id<<" ";
            
            if (visited[adj_id] != true) 
            {
                
                previous[adj_id] = out_index;
                visited[adj_id] = true;
                fake_queue.Add(adj_id, dummy_weight);
            }
            iter++;
        }
        //std::cout<<'\n';
        
    }
    
    
    
    std::vector<int> depth(vertices.size());
    std::vector<double> distance(vertices.size());
    
    i = 0;
    while(i < vertices.size())
    {
        Double3 temp;
        double tot_dist = 0;
        int wanted = i;
        int level = 0;
        int backtrack = previous[i];
        
        while(wanted != vertexId)
        {
            tot_dist += temp.Distance(vertices[wanted].position3D, vertices[backtrack].position3D);
            
            wanted = backtrack;
            backtrack = previous[wanted];
            level++;
        }
        
        distance[i] = tot_dist;
        depth[i] = level;
        i++;
    }
    
    depth[vertexId] = 0;
    distance[vertexId] = 0;
    //depth[14] = 4;
    
    for(int z = 0;z <= maxDepth;z++)  //color the nodes
    {
        for(int paint = 0;paint < depth.size();paint++)
        {
            if(depth[paint] == z)
            {
                Color temp;
                
                
                if(type == FILTER_BOX)
                {
                    if(alpha >= distance[paint] && alpha*(-1) <= distance[paint])
                    {
                        temp.r = color.r;
                        temp.g = color.g;
                        temp.b = color.b;
                    }
                    else
                    {
                        temp.r = 0;
                        temp.g = 0;
                        temp.b = 0;
                    }
                }
                
                else if( type == FILTER_GAUSSIAN)
                {
                    double cons;
                    
                    cons = std::exp(- ((distance[paint]*distance[paint]) / (alpha*alpha)));
                    //std::cout<<'$'<<cons<<"--->>"<<int(color.r*cons)<<'\n';
                    
                    temp.r = int(color.r*cons);
                    temp.g = int(color.g*cons);
                    temp.b = int(color.b*cons);
                }
                
                outputColorAllVertex[paint] = temp;
                
            }
        }
        
    }
    
    
    
    /*for(int y = 0;y <= maxDepth;y++)  // to print the results
    {
        std::cout<<"level "<<y<<'\n';
        for(int x = 0;x < depth.size();x++)
        {
            if(depth[x] == y)
            {
                std::cout<<x<<"--";
                
            }
            
        }
        std::cout<<'\n'<<"--------------"<<'\n';
        
    }*/
    
    
    
    
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
    
    //---------------------initial part-------------------------------
    bool flag1 = false;
    
    
    int i;
    
    for(i = 0;i < vertices.size(); i++)
    {
        if(vertices[i].id == vertexId)
        {
            flag1 = true;
        }
        
        
        
        if(flag1 == true)
        {
            break;
        }
    }
    
    if(flag1 != true)
    {
        return;
    }
    
    for(int i = 0;i < vertices.size();i++)
    {
        Color temp;
        temp.r = 0;
        temp.g = 0;
        temp.b = 0;
        
        outputColorAllVertex.push_back(temp);
        
    }
    
    //----------------main part---------------------------------------------
    
    std::vector<bool> visited(vertices.size());  //to check if the node is visited
    std::vector<int> previous(vertices.size());
    
    for (int i = 0; i < vertices.size(); i++)
    {
        visited[i] = false;  //initialize
    }
    
    BinaryHeap fake_queue;
    int dummy_weight = 0;
    
    visited[vertexId] = true;
    
    fake_queue.Add(vertexId, dummy_weight);  //add the first vertex to heap
    
    
    while(fake_queue.HeapSize() != 0)  //bfs
    {
        int out_index;
        double out_weight;
        
        fake_queue.PopHeap(out_index, out_weight);
        
        std::list<Vertex*>::const_iterator iter; 
    
        iter = adjList[out_index].begin();
        iter++;
        
        while(iter != adjList[out_index].end())  
        {
            int adj_id = (*iter)->id;
            
            dummy_weight++;
                
            if (visited[adj_id] != true) 
            {
                previous[adj_id] = out_index;
                visited[adj_id] = true;
                fake_queue.Add(adj_id, dummy_weight);
            }
            iter++;
        }
        
        
    }
    
    
    
    std::vector<int> depth(vertices.size());
    
    
    i = 0;
    while(i < vertices.size())
    {
        int wanted = -1;
        int level = 0;
        int backtrack = previous[i];
        
        while(wanted != vertexId)
        {
            wanted = backtrack;
            backtrack = previous[wanted];
            level++;
        }
        
        depth[i] = level;
        i++;
    }
    
    depth[vertexId] = 0;
    
    for(int z = 0;z <= maxDepth;z++)  //to paint the nodes
    {
        for(int paint = 0;paint < depth.size();paint++)
        {
            if(depth[paint] == z)
            {
                Double3 curr;
                double dist;
                Color temp;
                
                dist = curr.Distance(vertices[vertexId].position3D, vertices[paint].position3D);
                
                if(type == FILTER_BOX)
                {
                    if(alpha >= dist && alpha*(-1) <= dist)
                    {
                        temp.r = color.r;
                        temp.g = color.g;
                        temp.b = color.b;
                    }
                    else
                    {
                        temp.r = 0;
                        temp.g = 0;
                        temp.b = 0;
                    }
                }
                
                else if( type == FILTER_GAUSSIAN)
                {
                    double cons;
                    
                    cons = std::exp(- ((dist*dist) / (alpha*alpha)));
                    //std::cout<<'$'<<cons<<"--->>"<<int(color.r*cons)<<'\n';
                    
                    temp.r = int(color.r*cons);
                    temp.g = int(color.g*cons);
                    temp.b = int(color.b*cons);
                }
                
                outputColorAllVertex[paint] = temp;
                
            }
        }
        
    }
    
    
    /*for(int y = 0;y <= maxDepth;y++)  //for printing the results
    {
        std::cout<<"level "<<y<<'\n';
        for(int x = 0;x < depth.size();x++)
        {
            if(depth[x] == y)
            {
                std::cout<<x<<"--";
                
            }
            
        }
        std::cout<<'\n'<<"--------------"<<'\n';
        
    }*/
    
    
    /*for(int j = 0;j < depth.size();j++)
    {
        std::cout<<j<<"--->"<<depth[j]<<'\n';
    }*/
    
    
    
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}