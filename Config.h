// MeshStat command line options handling

#ifndef MESH_STAT_CONFIG_H
#define MESH_STAT_CONFIG_H

#include <string>
#include <vector>

#include "wx/cmdline.h"

typedef std::vector<std::string> NodeNameList;

class ConfigInfo {
public:
    ConfigInfo();

public:
    bool parseCommandLine(int& argc, wxChar **argv);

    void dump() const;

public:
    // Config fields
    unsigned int num_columns;
    double period;

    wxFileName config_filename;
    NodeNameList nodes;
};


#endif /* end of MESH_STAT_CONFIG_H */
