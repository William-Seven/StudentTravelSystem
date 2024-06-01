// Edge相关方法实现

#include "Edge.h"

Edge::Edge(Node* source, Node* destination, double distance, double congestion, type transportMode, double speed)
    : source(source), destination(destination), distance(distance), congestion(congestion), transportMode(transportMode), speed(speed) {}

Node* Edge::getFrom() const {
    return source;
}

Node* Edge::getTo() const {
    return destination;
}

double Edge::getLength() const {
    return distance;
}

double Edge::getCongestion() const {
    return congestion;
}

double Edge::getSpeed() const {
    return speed;
}

Edge::type Edge::gettype() const {
    return transportMode;
}
