#ifndef LOCATIONQUERY_H
#define LOCATIONQUERY_H

#include <algorithm>
#include <vector>
#include "Facility.h"
#include "Graph.h"
#include "Node.h"

class LocationQuery {
   private:
    Graph& graph;
    std::vector<Node*> facilities;

   public:
    explicit LocationQuery(Graph& graph);

    void loadFacilities();
    std::vector<Node*> findNearbyFacilities(Node* location, double radius);
    std::vector<Node*> filterResultsByCategory(std::vector<Node*> results, std::string& category);
    std::vector<Node*> sortFacilitiesByDistance(std::vector<Node*>& facilities, int low, int high);
};

#endif  // LOCATIONQUERY_H
