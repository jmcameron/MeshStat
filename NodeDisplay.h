/// NodeDisplay Class

#ifndef MESH_STAT_NODE_DISPLAY_H
#define MESH_STAT_NODE_DISPLAY_H

#include <map>
#include <string>

class Node;

class NodeDisplay {
public:

    virtual ~NodeDisplay() {};

    virtual void updateDisplay(const Node &node) = 0;

    virtual void update() {};
};


typedef std::map<std::string, NodeDisplay*> NodeDisplayMap;


#endif /* end of MESH_STAT_NODE_DISPLAY_H */
