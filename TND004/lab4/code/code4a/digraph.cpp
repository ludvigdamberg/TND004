/*********************************************
 * file:	~\code4a\digraph.cpp              *
 * remark: implementation of directed graphs  *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <queue>
#include "digraph.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero


// -- CONSTRUCTORS

const int infinity = std::numeric_limits<int>::max();
Digraph::Digraph(int n)
    : table(size_t(n) + 1)
    , size{n}
    , n_edges{0}
    , dist(size_t(n) + 1)
    , path(size_t(n) + 1)
    , done(size_t(n) + 1) {
    assert(n >= 1);

    // Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<Edge>& V, int n) : Digraph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge e = (u, v, w)
// update weight w if edge (u, v) is present
void Digraph::insertEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    // Check if edge e already exists
    if (auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                               [e](const Edge& ed) { return e.links_same_nodes(ed); });
        it == end(table[e.head])) {
        table[e.head].push_back(e);  // insert new edge e
        ++n_edges;
    } else {
        it->weight = e.weight;  // update the weight
    }
}

// remove directed edge e
void Digraph::removeEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                           [e](const Edge& ed) { return e.links_same_nodes(ed); });

    assert(it != end(table[e.head]));
    table[e.head].erase(it);
    --n_edges;
}

// construct unweighted single source shortest path-tree for start vertex s
void Digraph::uwsssp(int s) const {
    assert(s >= 1 && s <= size);

    // *** TODO ***
 
    std::queue <int> Q;



    //Record the distance and path in the graph.
    for(int i = 1; i <= size; i++)
    {
        dist[i] = infinity;
        path[i] = 0;
       
    }
    dist[s] = 0; //start node where distance is zero

    Q.push(s); //placing start node in the queue
   

   

    while (Q.size() != 0 )
    {
        int v = Q.front();
        Q.pop();

        //Sorting while only taking into account the closest vertex point and not the weight.
        for (auto it = table[v].begin(); it != table[v].end(); it++) {
            int u = it->tail;

            if(dist[u] == infinity)
            {

                dist[u] = dist[v] + 1;
                path[u] = v;
                Q.push(u);
            }
        }
    }
}




// construct positive weighted single source shortest path-tree for start vertex s
// Dijktra’s algorithm
void Digraph::pwsssp(int s) const {
    assert(s >= 1 && s <= size);
    

        //  TODO 

    //Record the distance and path in the graph.

        for (int i = 1; i <= size; ++i) 
        {
            dist[i] = infinity; //record the distance

            path[i] = 0; //record the path

            done[i] = false; //mark as visited
        }

        dist[s] = 0; //start node where distance is zero

        done[s] = true; 

        int v = s; //start node

        while (true)
        {

            // går igenom hela textfilen från start till slut och skapar ett rad 
            for (auto it = table[v].begin(); it != table[v].end(); it++) {
                int u = it->tail;

                if (done[u] == false && dist[u] > dist[v] + it->weight)
                {
                    dist[u] = dist[v] + it->weight;
                    path[u] = v;
                }

                done[v] = true;
            }

            int smallestDistance = infinity;

            // Update vertex according to shortest distance and the weight of the vertecies
            for (int i = 1; i <= size; ++i)
            {
                if (!done[i] && dist[i] < smallestDistance)
                {
                    smallestDistance = dist[i]; // update shortest path
                    v = i;
                }
            }


            if (smallestDistance == infinity) { break; } // All nodes have been added to the tree => exit

            done[v] = true;   //Else, add to the tree.


        }


}



// print graph
void Digraph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                  \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; ++v) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << "----------------------\n";
    std::cout << "vertex    dist    path\n";
    std::cout << "----------------------\n";

    for (int v = 1; v <= size; ++v) {
        std::cout << std::setw(4) << v << " :" << std::setw(8)
                  << ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
                  << path[v] << "\n";
    }
    std::cout << "----------------------\n";
}

// print shortest path from s to t and the corresponding path length
// Hint: consider using recursion
void Digraph::printPath(int t) const {
    assert(t >= 1 && t <= size);
    
       

        // *** TODO ***
        if (path[t] == 0)
        {
            std::cout << " " << t << " ";
            return;
        }

        printPathOnly(t);

        std::cout << "(" << dist[t] << ")";

    


   // *** TODO ***
}
void Digraph::printPathOnly(int t) const {
    assert(t >= 1 && t <= size);



    // *** TODO ***
    if (path[t] == 0)
    {
        std::cout << " " << t << " ";
        return;
    }

    printPathOnly(path[t]);

    std::cout << " " << t << " ";





    // *** TODO ***
}
