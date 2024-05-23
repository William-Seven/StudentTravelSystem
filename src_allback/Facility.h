#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include "Node.h"

class Facility {
   private:
    Node location;  // 使用 Node 类型来代表位置
    std::string name;
    std::string type;

   public:
    Facility(const Node& loc, const std::string& name, const std::string& type);

    std::string getName() const;
    std::string getType() const;
    const Node& getLocation() const;
};

#endif  // FACILITY_H
