#include "global_planner.h"

namespace dijkstra {

// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation

    Dijkstra::Dijkstra() {
    }

    std::vector<int> Dijkstra::findShortestPath(std::vector<std::vector<float> > *graph, int src, int target) {

        //graph - matrix representation of the graph
        std::vector<int> parent((*graph).size());     // Parent array to store shortest path tree
        std::vector<float> dist((*graph).size());    // The output array. dist[i] will hold
        // the shortest distance from src to i

        this->source = src;
        // sptSet[i] will true if vertex i is included / in shortest
        // path tree or shortest distance from src to i is finalized
        bool sptSet[(*graph).size()];

        // Initialize all distances as INFINITE and stpSet[] as false
        for (int i = 0; i < (*graph).size(); i++) {
            //parent[0] = -1;
            parent[i] = -1;
            dist[i] = 1000.0; //INT_MAX
            sptSet[i] = false;
        }

        // Distance of source vertex from itself is always 0
        dist[src] = 0;

        // Find shortest path for all vertices
        for (int count = 0; count < (*graph).size() - 1; count++) {
            // Pick the minimum distance vertex from the set of
            // vertices not yet processed. u is always equal to src
            // in first iteration.
            int u = minDistance(dist, sptSet);

            // Mark the picked vertex as processed
            sptSet[u] = true;

            // Update dist value of the adjacent vertices of the
            // picked vertex.
            for (int v = 0; v < (*graph).size(); v++)

                // Update dist[v] only if is not in sptSet, there is
                // an edge from u to v, and total weight of path from
                // src to v through u is smaller than current value of
                // dist[v]
                if (!sptSet[v] && (*graph)[u][v] &&
                    dist[u] + (*graph)[u][v] < dist[v]) {
                    parent[v] = u;
                    dist[v] = dist[u] + (*graph)[u][v];

                }
        }

        // print the constructed distance array
        return getSolution(parent, dist, target);
    }


    int Dijkstra::minDistance(std::vector<float> dist, bool sptSet[]) {
        // Initialize min value
        int min = 1000.0, min_index; //INT_MAX

        for (int v = 0; v < dist.size(); v++)
            if (sptSet[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

// Function to print shortest path from source to j
// using parent array
    void Dijkstra::printPath(std::vector<int> parent, int j) {
        // Base Case : If j is source
        if (parent[j] == -1)
            return;

        printPath(parent, parent[j]);

        path.push_back(j);
    }

// A utility function to print the constructed distance
// array

    std::vector<int> Dijkstra::getSolution(std::vector<int> parent, std::vector<float> dist, int target) {

        path.clear();


        if (dist[target] >= 1000.0) {
            throw dijkstra_exception(dijkstra_exception::NO_PATH_FOUND);
        }
        path.push_back(source);

        printPath(parent, target);

        return path;
    }

    std::vector<int> Dijkstra::getSolution() {

        return path;
    }
}


GlobalPlanner::GlobalPlanner(grid_map::Map *map){
    this->map = map;

}

bool GlobalPlanner::makePlan(Definitions::POINT start, Definitions::POINT target, std::vector<Definitions::POINT> *plan){

    dijkstra::Dijkstra dijkstra;
    plan->clear();

    std::vector<std::vector<float> > graph = map->getGraph();
    std::vector<int> points;

    try{
        points = dijkstra.findShortestPath(&graph, map->getCellId(start), map->getCellId(target));
    } catch (std::exception &e){
        return false;

    }
    plan->push_back((*map)(points[0]));

    double anglePrevious = Definitions::getAngle(plan->at(0), start);

    for (int i = 1; i < points.size(); i++){
        plan->push_back((*map)(points[i]));
        map->setValue(points[i], grid_map::PATH);
        double angle = Definitions::getAngle(plan->at(i - 1), plan->at(i));
        //vymaze zbytocne body
        if (fabs(anglePrevious - angle) < 0.0001) {
            plan->erase(plan->begin() + i - 1);
            points.erase(points.begin() + i - 1);
            i--;
        } else {
            anglePrevious = angle;
        }
    }

    //nahradi posledny bod cielom
    plan->pop_back();
    plan->push_back(target);
    return true;
}


