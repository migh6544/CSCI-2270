#include <iostream>
#include <vector>
#include <queue>
#include "Graph.hpp"

using namespace std;


void Graph::addVertex(string name)
{
    bool exists = false;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == name)
        {
            exists = true;
        }
    }
    if (exists == false)
    {
        vertex *v = new vertex;
        v->name = name;
        vertices.push_back(v);
    }
}

void Graph::addEdge(string v1, string v2)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == v1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j]->name == v2 && i != j)
                {
                    adjVertex adjV1;
                    adjV1.v = vertices[j];
                    vertices[i]->adj.push_back(adjV1);
                    adjVertex adjV2;
                    adjV2.v = vertices[i];
                    vertices[j]->adj.push_back(adjV2);
                }
            }
        }
    }
}

void Graph::displayEdges()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i]->name << " --> ";
        for (int j = 0; j < vertices[i]->adj.size(); j++)
        {
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex)
{
    vertex *startV;
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i]->visited = false;
        if (vertices[i]->name == sourceVertex)
        {
            startV = vertices[i];
        }
    }
    cout << "Starting vertex (root): " << startV->name << "-> ";
    startV->visited = true;
    queue<vertex *> visitedList;
    visitedList.push(startV);
    vertex *temp;
    while (!visitedList.empty())
    {
        temp = visitedList.front();
        visitedList.pop();
        for (int i = 0; i < temp->adj.size(); i++)
        {
            if (!temp->adj[i].v->visited)
            {
                temp->adj[i].v->visited = true;
                temp->adj[i].v->distance = temp->distance + 1;
                visitedList.push(temp->adj[i].v);
                cout << temp->adj[i].v->name << "(" << temp->adj[i].v->distance << ") ";
            }
        }
    }
}

int Graph::getConnectedComponents()
{
    int subC = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i]->visited = false;
    }
    for (int i = 0; i < vertices.size(); i++)
    {
        if (!vertices[i]->visited)
        {
            vertices[i]->visited = true;
            vector<vertex *> vList;
            vList.push_back(vertices[i]);
            vertex *tempV;
            while (!vList.empty())
            {
                tempV = vList.back();
                vList.pop_back();
                for (int j = 0; j < tempV->adj.size(); j++)
                {
                    if (!tempV->adj[j].v->visited)
                    {
                        tempV->adj[j].v->visited = true;
                        tempV->adj[j].v->distance = tempV->distance + 1;
                        vList.push_back(tempV->adj[j].v);
                    }
                }
            }
            subC++;
        }
    }
    return subC;
}