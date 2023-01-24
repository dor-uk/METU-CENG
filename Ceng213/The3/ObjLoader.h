#pragma once

#include <string>
#include <vector>
#include "Structs.h"

class ObjLoader
{
    private:
    std::vector<Double3>            vertexPositions;
    std::vector<IdPair>             edges;

    public:
    // Constructors & Destructor
    bool                            LoadObjFile(const std::string& filePath);
    const std::vector<Double3>&     GetVertexPos() const;
    const std::vector<IdPair>&      GetEdges() const;
};