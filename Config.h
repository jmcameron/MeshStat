// MeshStat command line options handling

#ifndef MESH_STAT_CONFIG_H
#define MESH_STAT_CONFIG_H

#include <string>
#include <vector>

#include <wx/filename.h>


const unsigned int default_period = 10; // Seconds

const unsigned int default_max_response_time = 2000;  // milliseconds

const unsigned int default_max_num_fails = 10;

const unsigned int default_seconds_for_max_fails = 60; // seconds

const unsigned int default_pane_width_chars = 66;
const unsigned int default_pane_height_lines = 4;


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
    unsigned int max_response_time;
    unsigned int max_num_fails;

    unsigned int pane_width_chars;
    unsigned int pane_height_lines;

    wxFileName config_filename;
    NodeNameList nodes;
};


#endif /* end of MESH_STAT_CONFIG_H */
