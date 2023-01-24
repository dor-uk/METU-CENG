#pragma once

#include <list>
#include <vector>
#include <string>

#include "Structs.h"

struct Color
{
    unsigned char r, g, b;
};

struct Vertex
{
    int id;
    Double3 position3D;
};

enum FilterType
{
    FILTER_BOX,         // Box filter means that all the time weights are 1 in the range
    FILTER_GAUSSIAN     // Gaussian filter can be seen on here
};

class MeshGraph
{
    private:
    std::vector<Vertex>                 vertices;
    std::vector<std::list<Vertex*> >     adjList;

    // Do not remove this the tester will utilize this
    // to access the private parts.
    friend class HW3Tester;

    protected:
    public:
    // Constructors & Destructor
                        MeshGraph(const std::vector<Double3>& vertexPositions,
                                  const std::vector<IdPair>& edges);


    // Functionality
    // Small functionality
    double              AverageDistanceBetweenVertices() const;
    double              AverageEdgePerVertex() const;
    int                 TotalVertexCount() const;
    int                 TotalEdgeCount() const;
    int                 VertexEdgeCount(int vertexId) const;

    void                ImmediateNeighbours(std::vector<int>& outVertexIds,
                                            int vertexId) const;

    // Big functionalities
    void                PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                             int vertexIdFrom, int vertexIdTo,
                                             const Color& color) const;
    void                PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                             int vertexId, const Color& color,
                                             int maxDepth, FilterType type, double alpha) const;
    void                PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                              int vertexId, const Color& color,
                                              int maxDepth, FilterType type, double alpha) const;

    // Static functions for outputting (you can use these for testing, testers will use these)
    // to check with reference implementation
    static void WriteColorToFile(const std::vector<Color>& colors, const std::string& fileName);
    static void PrintColorToStdOut(const std::vector<Color>& colors);
};