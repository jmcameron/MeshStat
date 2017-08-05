/// Node Class

#ifndef MESH_STAT_NODE_H
#define MESH_STAT_NODE_H

#include <string>

class NodeDisplay;


class Node {
public:
    Node(const std::string url_);

    void setNodeDisplay(NodeDisplay *new_display);

protected:
    std::string url;
    std::string name;
    double latitude;
    double longitude;

    double chanbw;
    int channel;

    std::string model;
    std::string firmware_mfg;
    std::string firmware_version;
    std::string ssid;

    NodeDisplay *display;

private:
    Node() {};  // Disabled
};


#endif /* end of MESH_STAT_NODE_H */


// node: W6JPL-M5R-180R6
// model: Ubiquiti Rocket M
// chanbw: 20
// channel: 174
// lat: 34.200464
// lon: -118.174341
// firmware_mfg: AREDN
// firmware_version: 3.16.1.1
// ssid: AREDN-20-v3

// active_tunnel_count: 0
// api_version: 1.0
// board_id: 0xe1b5
// grid_square: 
// interfaces: [CHILDREN]
// tunnel_installed: true
