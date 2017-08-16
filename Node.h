/// Node Class

#ifndef MESH_STAT_NODE_H
#define MESH_STAT_NODE_H

#include <map>
#include <string>
#include <wx/datetime.h>

class NodeDisplay;


class Node {
public:
    Node(const std::string url_);

    ~Node();

    void setNodeDisplay(NodeDisplay *new_display);

    void readDataFromJSON(const std::string &json);

    void updateDisplay();

    void probe();

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

    int num_fails;
    unsigned int last_response_time;  // milliseconds

    wxDateTime last_succesful_probe_time;
    wxDateTime start_time;

protected:

    NodeDisplay *display;

private:
    Node() {};  // Disabled
};


typedef std::map<std::string, Node*> NodeMap;


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
