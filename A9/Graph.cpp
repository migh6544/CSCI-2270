#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;

/*
Helper Functions:
*/

void DFS(vertex *vertex)
{
    vertex->visited = true;
    for (int i = 0; i < vertex->adj.size(); i++)
    {
        if (!vertex->adj[i].v->visited)
        {
            cout << vertex->adj[i].v->name << " -> ";
            DFS(vertex->adj[i].v);
        }
    }
}

/* ------------------------------------------------------------------------------- */

void Graph::addEdge(string v1, string v2, int num)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == v1)
        {
            for (int j = 0; j < vertices.size(); j++)
            {
                if (vertices[j]->name == v2 && i != j)
                {
                    adjVertex tempV1;
                    tempV1.v = vertices[j];
                    tempV1.weight = num;
                    vertices[i]->adj.push_back(tempV1);
                    adjVertex tempV2;
                    tempV2.v = vertices[i];
                    tempV2.weight = num;
                    vertices[j]->adj.push_back(tempV2);
                }
            }
        }
    }
}

void Graph::dijkstraTraverse(string sourceVertex)
{
    vector<vertex *> solved;
    vertex *startV = nullptr;
    vertex *temp = nullptr;
    int minDist = 9999;

    /** intialise everything to false and distance to a large number**/
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i]->distance = 9999;
        vertices[i]->pred = 0;
        vertices[i]->visited = false;
    }

    /** find the source **/
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == sourceVertex)
        {
            startV = vertices[i];
            startV->distance = 0;   //set distance 0
            startV->visited = true; // set visited true
            solved.push_back(startV);
        }
    }

    for (int k = 0; k < vertices.size() - 1; k++) // for loop for rest of the vertices. One has been already pushed. So the limit is size()-1
    {
        minDist = 9999; //initialise minDist for each iteration
        temp = NULL;
        for (int i = 0; i < solved.size(); i++)
        {
            for (int j = 0; j < solved[i]->adj.size(); j++)
            {
                if (solved[i]->adj[j].v->visited == false)
                {
                    int dist = solved[i]->distance + solved[i]->adj[j].weight; //calculate the dist

                    if (dist < solved[i]->adj[j].v->distance) //relaxation: if required update the distance of the adj vertex
                        solved[i]->adj[j].v->distance = dist;

                    if (solved[i]->adj[j].v->distance < minDist) // if that distane is minimum store that vertex to push
                    {
                        temp = solved[i]->adj[j].v;
                        minDist = solved[i]->adj[j].v->distance;
                        solved[i]->adj[j].v->pred = solved[i];
                    }
                }
            }
        }

        temp->visited = true;
        solved.push_back(temp);
    }
}

void Graph::shortestPath(string s1, string s2)
{
    dijkstraTraverse(s1);
    vector<vertex *> list;
    vertex *endV = nullptr;

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->name == s2)
        {
            endV = vertices[i];
        }
    }
    int dist = endV->distance;

    while (endV && endV->name != s1)
    {
        list.push_back(endV);
        endV = endV->pred;
    }
    list.push_back(endV);
    for (int i = list.size(); i > 0; i--)
    {
        cout << list[i - 1]->name << " -> ";
    }
    cout << "DONE "
         << "[" << dist << "]" << endl;
}