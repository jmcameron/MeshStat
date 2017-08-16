/// NodeDisplay Class

#ifndef MESH_STAT_NODE_DISPLAY_H
#define MESH_STAT_NODE_DISPLAY_H

#include <map>
#include <string>

class Node;

class NodeDisplay {
public:
    void virtual updateDisplay(const Node &node) = 0;

    virtual ~NodeDisplay() {};
};


typedef std::map<std::string, NodeDisplay*> NodeDisplayMap;


#endif /* end of MESH_STAT_NODE_DISPLAY_H */
