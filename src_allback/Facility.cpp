#include "Facility.h"

Facility::Facility(const Node& loc, const std::string& name, const std::string& type)
    : location(loc), name(name), type(type) {}

std::string Facility::getName() const {
    return name;
}

std::string Facility::getType() const {
    return type;
}

const Node& Facility::getLocation() const {
    return location;
}
