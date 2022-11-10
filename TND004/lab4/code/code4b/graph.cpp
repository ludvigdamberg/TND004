/*********************************************
 * file:	~\code4b\graph.h                  *
 * remark:implementation of undirected graphs *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>  //assert

#include "graph.h"
#include "heap.h"
#include "dsets.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS
const int infinity = std::numeric_limits<int>::max();



// Create a graph with n vertices and no vertices
Graph::Graph(int n) : table(size_t(n) + 1), size{n}, n_edges{0} {
    assert(n >= 1);
}

Graph::Graph(const std::vector<Edge> &V, int n) : Graph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge e
// update weight if edge e is present
void Graph::insertEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edge_insertion = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        if (auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                                   [e1](const Edge &ed) { return e1.links_same_nodes(ed); });
            it == end(T[e1.head])) {
            T[e1.head].push_back(e1);  // insert new edge e
            ++n;                       // increment the counter of edges
        } else {
            it->weight = e1.weight;  // update the weight
        }
    };

    edge_insertion(e);
    edge_insertion(e.reverse());
}

// remove undirected edge e
void Graph::removeEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edgeRemoval = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                               [e1](const Edge &ed) { return e1.links_same_nodes(ed); });

        assert(it != end(T[e1.head]));
        T[e1.head].erase(it);  // remove edge e1
        --n;                   // decrement the counter of edges
    };

    edgeRemoval(e);
    edgeRemoval(e.reverse());
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {
    std::vector<int> dist(size_t(size) + 1);
    std::vector<int> path(size_t(size) + 1);
    std::vector<bool> done(size_t(size) + 1);

    // *** TODO ***


    // Record the distance and path of the vertecies in the graph
    for (int i = 1; i <= size; ++i) 
    {
        dist[i] = infinity;
        path[i] = 0;
        done[i] = false; 
    }
    int v = 1;
    dist[v] = 0; //start can be any vertex
    done[v] = true;

    int totWeight = 0;


    while (true) {

        //Creating att tree with the shortest distance

        for (auto it = table[v].begin(); it != table[v].end(); it++) {
            int u = it->tail;

            if (done[u] == false && dist[u] > it->weight)
            {
                path[u] = v;
                dist[u] = it->weight;
            }


        }
        int smallestDistance = infinity;

        // Update vertex according to shortest distance 
        for (int i = 1; i <= size; ++i)
        {
            if (!done[i] && dist[i] < smallestDistance)
            {
                smallestDistance = dist[i]; // update shortest path
                v = i;
            }
        }

        if (smallestDistance == infinity) { break; } // All nodes have been added to the tree => exit
        Edge myEdge(path[v], v, dist[v]);
        std::cout << myEdge << "\n";
        totWeight += dist[v];

        done[v] = true;   //Else, add to the tree.

    }
    std::cout << "\n" << "total weight: " << totWeight << "\n";

}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {

    // *** TODO ***
    std::vector<Edge> edges;
    DSets DS(size);

    int counter = 0;
    int totalWeight = 0;
   

  //removing unecessary edges by creating the shortest route.
    for (int i = 1; i <= size; ++i)
    {
        for (auto it = table[i].begin(); it != table[i].end(); ++it) {

            int v = it->tail;

            if (i <= v) {
                Edge myEdge(i, v, it->weight);

              edges.push_back(myEdge);
            }
        }

    }

    Heap H(edges); // using the heap created in the header with all the edges


            //writing out the results. 
        while (counter < (size - 1)) {

            Edge edge = H.deleteMin();

            if (DS.find(edge.head) != DS.find(edge.tail))
            {
                std::cout << edge << "\n";

                //merge two trees
                DS.join(DS.find(edge.head), DS.find(edge.tail));
                totalWeight += edge.weight;
                counter++;
            }
        }

        std::cout << "\n" << "total weight: " << totalWeight << "\n";
    
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight
                      << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}
