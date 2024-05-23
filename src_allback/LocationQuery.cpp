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
        if (distance <= radius) {
            facility->setDistance(distance);
            nearbyFacilities.push_back(facility);
            // distances.push_back(distance);
        }
    }

    return nearbyFacilities;
}

std::vector<Node*> LocationQuery::filterResultsByCategory(std::vector<Node*> results, std::string& category) {
    std::vector<Node*> filteredResults;

    for (const auto& facility : results)
        if (facility->getDescription() == category)
            filteredResults.push_back(facility);

    return filteredResults;
}

std::vector<Node*> LocationQuery::sortFacilitiesByDistance(std::vector<Node*>& facilities, int low, int high) {
    if (low < high) {
        Node* pivot = facilities[low];  // 选择第一个元素作为基准
        int l = low;
        int r = high;

        while (l < r) {
            while (l < r && facilities[r]->getDistance() >= pivot->getDistance())
                r--;
            facilities[l] = facilities[r];
            while (l < r && facilities[l]->getDistance() <= pivot->getDistance())
                l++;
            facilities[r] = facilities[l];
        }
        facilities[l] = pivot;

        // 分别对分区前后的子数组进行排序
        sortFacilitiesByDistance(facilities, low, l - 1);
        sortFacilitiesByDistance(facilities, r + 1, high);
    }
    return facilities;
}
