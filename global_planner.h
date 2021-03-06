#ifndef GLOBAL_PLANNER_H
#define GLOBAL_PLANNER_H

// A C / C++ program for Dijkstra's single source shortest
// path algorithm. The program is for adjacency matrix
// representation of the graph.
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <iostream>
#include <exception>
#include "grid_map.h"
#include "definitions.h"

// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree

namespace dijkstra {



    class dijkstra_exception : public std::exception {
    public:
        const static int NO_PATH_FOUND = 1;

        dijkstra_exception(int err_id) {
            this->err_id = err_id;
        }

        virtual const char *what() const throw() {
            return "No path found";
        }

        int get_err_id() {
            return err_id;
        }

    private:
        int err_id;
    };

    class Dijkstra {
    public:

        Dijkstra();

        std::vector<int> findShortestPath(std::vector<std::vector<float> > *graph, int src, int target);

        std::vector<int> getSolution();

    private:

        std::vector<int> path;      // The shortest path - initialize in function getShortestPath()
        int source;                 //start point

        int minDistance(std::vector<float> dist, bool sptSet[]);

        std::vector<int> getSolution(std::vector<int> parent, std::vector<float> dist, int target);

        void printPath(std::vector<int> parent, int j);
    };
}


class GlobalPlanner{

public:
   //GlobalPlanner(){}
    GlobalPlanner(grid_map::Map *map);

    bool makePlan(Definitions::POINT start, Definitions::POINT target, std::vector<Definitions::POINT> *plan);

private:
    grid_map::Map *map;

    bool erasePoint(Definitions::POINT p1, Definitions::POINT p2);

};

#endif // GLOBAL_PLANNER_H
