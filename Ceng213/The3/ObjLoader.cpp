#include "ObjLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool IdPairLess(const IdPair& id0, const IdPair& id1)
{
    if(id0.vertexId0 < id1.vertexId0) return true;
    else if(id0.vertexId0 == id1.vertexId0)
    {
        if(id0.vertexId1 < id1.vertexId1)
            return true;
        else
            return false;
    }
    return false;
}

bool EqualPair(const IdPair& id0, const IdPair& id1)
{
    return (id0.vertexId0 == id1.vertexId0 &&
            id0.vertexId1 == id1.vertexId1);
}

void SwapIds(IdPair& id)
{
    if(id.vertexId0 > id.vertexId1)
        std::swap(id.vertexId0, id.vertexId1);
}

bool ObjLoader::LoadObjFile(const std::string& filePath)
{
    vertexPositions.clear();
    edges.clear();

    static const std::string V_LINE = "v ";
    static const std::string F_LINE = "f ";

    std::ifstream objFile(filePath.c_str());
    if(!objFile)
    {
        std::cout << "Unable to Open " << filePath << std::endl;
        return false;
    }

    std::string line;
    while(std::getline(objFile, line))
    {
        if(line.size() < 2) continue;
        std::string headerToken = line.substr(0, 2);
        std::string rest = line.substr(2);

        if(headerToken == V_LINE)
        {
            Double3 pos;
            std::stringstream s(rest);
            s >> pos.x;
            s >> pos.y;
            s >> pos.z;
            vertexPositions.push_back(pos);
        }
        else if(headerToken == F_LINE)
        {
            // Face line generate edges
            // Max edge is 4
            int indexCount = 0;
            int indices[5] = {};
            std::stringstream faceStream(rest);

            std::string id;
            while(faceStream >> id)
            {
                // Split from the "/" char
                std::stringstream(id) >> indices[indexCount];
                indexCount++;
            }
            indices[indexCount] = indices[0];

            //std::cout << "Pair ";
            for(int i = 0; i < indexCount; i++)
            {
                // Now calculate edges
                // Don't forget that Ids are one indexed
                IdPair pair;
                pair.vertexId0 = indices[i] - 1;
                pair.vertexId1 = indices[i + 1] - 1;
                edges.push_back(pair);
                //std::cout << "{" << edges.back().vertexId0 << ", "
                //                 << edges.back().vertexId1 << "} ";
            }
            //std::cout << std::endl;

        }
    }

    // Now remove the duplicates
    // If mesh is proper  there should be at most two (v0, v1) and or (v1, v0)
    // First swap the larger one, then sort and the check th
    typedef std::vector<IdPair>::iterator It;
    std::for_each(edges.begin(), edges.end(), SwapIds);
    std::sort(edges.begin(), edges.end(), IdPairLess);
    It last = std::unique(edges.begin(), edges.end(), EqualPair);
    edges.erase(last, edges.end());
    return true;
}

const std::vector<Double3>& ObjLoader::GetVertexPos() const
{
    return vertexPositions;
}

const std::vector<IdPair>& ObjLoader::GetEdges() const
{
    return edges;
}