/*************************************************
 * file:	~\code4a\edge.h                      *
 * remark: interface for directed weighted edges *
 *************************************************/

#pragma once

#include <iostream>
#include <iomanip>
// #include <utility>

// Represents a directed edge from head to tail with weight
class Edge {
public:
    // -- CONSTRUCTORS
    Edge(int u = 0, int v = 0, int w = 0) : head{u}, tail{v}, weight{w} {
    }

    bool links_same_nodes(const Edge &e) const {
        return (head == e.head && tail == e.tail);
    }

    Edge reverse() const {
        return {tail, head, weight};
    }

    // -- RELATIONAL OPERATORS 
    // used in exercise b
    bool operator<(const Edge &e) const {
        return weight < e.weight;
    }

    bool operator>(const Edge &e) const {
        return weight > e.weight;
    }

    bool operator==(const Edge &e) const {
        return weight == e.weight;
    }

    // -- FRIENDS
    friend std::ostream &operator<<(std::ostream &os, const Edge &e) {
        os << "(" << std::setw(2) << e.head << ", " << std::setw(2) << e.tail << ", "
           << std::setw(2) << e.weight << ") ";

        return os;
    }

    // -- DATA MEMBERS
    int head;
    int tail;
    int weight;
};
