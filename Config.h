// MeshStat command line options handling

#ifndef MESH_STAT_CONFIG_H
#define MESH_STAT_CONFIG_H

#include <string>
#include <vector>

#include "wx/cmdline.h"

typedef std::vector<std::string> NodeList;

class ConfigInfo {
public:
    ConfigInfo() {};

public:
    bool parseCommandLine(int& argc, wxChar **argv);

    void dump() const;

public:
    double period;
    wxFileName config_filename;
    NodeList nodes;
};


#endif /* end of MESH_STAT_CONFIG_H */
