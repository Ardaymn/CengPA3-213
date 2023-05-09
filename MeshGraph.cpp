#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    int i;
    for(i=0; i< vertexPositions.size() ; i++)
    {
        Vertex temp;
        temp.id = i;
        temp.position3D = vertexPositions[i];
        
        vertices.push_back(temp);
    }

    

    int j;
    for(i=0; i< vertexPositions.size() ; i++)
    {
        //Vertex *p;
        std::list<Vertex*> listpointer;
        //p = &(vertices[i]);
        //listpointer.push_back(p);
        for(j=0; j<edges.size(); j++)
        {
            if(edges[j].vertexId0 == i) 
            {
                listpointer.push_back(&vertices[(edges[j].vertexId1)]);
            }
            if(edges[j].vertexId1 == i) 
            {
                listpointer.push_back(&vertices[(edges[j].vertexId0)]);
            }
        }
        adjList.push_back(listpointer);
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
   Double3 d;
   double total_distance=0;
   int i,j;
   for(i=0; i<adjList.size(); i++)
   {
        for (std::list<Vertex*>::const_iterator j = adjList[i].begin(); j != adjList[i].end(); j++)
        {
            Double3 left = vertices[i].position3D;
            Double3 right = (*j)->position3D;
            total_distance = total_distance + d.Distance(right,left);
        }
   }
    return total_distance/(TotalEdgeCount()*2);

}

double MeshGraph::AverageEdgePerVertex() const
{
    double result = (double)TotalEdgeCount()/(double)TotalVertexCount();
    return result;
    // TODO:
}

int MeshGraph::TotalVertexCount() const
{
    return vertices.size();
    // TODO:
}

int MeshGraph::TotalEdgeCount() const
{
    int i,j,result=0;
    for(i=0; i<adjList.size();i++)
    {
        for(j=0; j<adjList[i].size(); j++)
        {
            result++;
        }
        //result--;
    }
    return result/2;
    // TODO:
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    int i;
    for(i=0; i<vertices.size(); i++)
    {
        if(vertices[i].id == vertexId)
        {
            return adjList[i].size();
        }
    }
    return -1;

}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
        if(vertices.size() > vertexId && vertexId > 0)
        {
            std::list<Vertex*>::const_iterator j = adjList[vertexId].begin();
            for (; j != adjList[vertexId].end(); j++)
            {
                outVertexIds.push_back((*j)->id);
            }
        }
        else return;
   
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    
    std::vector<int> path;
    std::vector<double> dist;
    int i;
    if (vertexIdTo >= vertices.size() || vertexIdFrom >= vertices.size() ) return;
    
    outputColorAllVertex.resize(vertices.size());

    for(i=0; i<outputColorAllVertex.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }

    BinaryHeap bh;
    for(i=0; i< vertices.size(); i++)
    {
        bh.Add(i,INFINITY);
    }

    //int uniqueidd;
    //double weightt;
    int k;

    for(i=0; i< vertices.size(); i++)
    {
        if(vertices[i].id==vertexIdFrom)
        {
            k=i;
            bh.ChangePriority(vertices[i].id,0);
            //uniqueidd = vertices[i].id;
            //weightt = 0;
        }
        dist.push_back(INFINITY);
        path.push_back(-1);
    }
    dist[vertexIdFrom]=0;

    Double3 d;
    

    double newdistance;
    int j;
    
    while(bh.HeapSize()!=0)
    {
        std::vector<int> neighbours;
        int uniqueidd;
        double weightt;
        Double3 left;
        Double3 right;
        bh.PopHeap(uniqueidd,weightt);
        left = vertices[uniqueidd].position3D;
        ImmediateNeighbours(neighbours,uniqueidd);
        for (int i = 0; i< neighbours.size(); i++)
        {
            int j = neighbours[i];
            right = vertices[j].position3D;
            newdistance = dist[uniqueidd] + d.Distance(left,right);
            if(newdistance < dist[j])
            {
                dist[j] = newdistance;
                path[j] = uniqueidd;
                bh.ChangePriority(j, newdistance);
            }
        }
    }
    int pre = path[vertexIdTo];
    outputColorAllVertex[vertexIdTo] = color;
    
    while(pre != -1){
        outputColorAllVertex[pre].r = color.r;
        outputColorAllVertex[pre].g = color.g;
        outputColorAllVertex[pre].b = color.b;
        pre = path[pre];
    }



}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    
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