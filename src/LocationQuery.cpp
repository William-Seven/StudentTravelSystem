#include "LocationQuery.h"
#include <cmath>
#include "Algorithms.h"
#include "Graph.h"

LocationQuery::LocationQuery(Graph& g)
    : graph(g) {}

// Placeholder for actual load function
void LocationQuery::loadFacilities() {
    for (int i = 0; i < graph.size; i++) {
        Node* node = graph.getNode(i);
        if (node->getType() == Node::Type::FACILITY)
            facilities.push_back(node);
    }
}

std::vector<Node*> LocationQuery::findNearbyFacilities(Node* location, double radius) {
    std::vector<Node*> nearbyFacilities;

    for (const auto& facility : facilities) {
        Algorithms::PathResult pathresult = Algorithms::findShortestPath(graph, location->id, facility->id);
        double distance = pathresult.length;
        if (distance <= radius)
            nearbyFacilities.push_back(facility);
    }

    return nearbyFacilities;
}

std::vector<Node> LocationQuery::filterResultsByCategory(const std::vector<Node>& results, const std::string& category) {
    std::vector<Node> filteredResults;

    for (const auto& facility : results)
        if (facility.getDescription() == category)
            filteredResults.push_back(facility);

    return filteredResults;
}
