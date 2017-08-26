// MeshStat command line options handling

#ifndef MESH_STAT_CONFIG_H
#define MESH_STAT_CONFIG_H

#include <string>
#include <vector>

#include <wx/filename.h>


typedef enum {
    UNDEFINED = 0,
    STREAM,
    NODE_DISPLAY_PANE,
    NODE_DISPLAY_PANE_ONE_LINE_STATUS
} DISPLAY_MODE;


const unsigned int default_period = 10; // Seconds

const unsigned int default_num_columns = 1;

const unsigned int default_node_access_timeout = 2;  // seconds

const unsigned int default_max_response_time = 2000;  // milliseconds
const unsigned int default_max_num_fails = 10;

const unsigned int default_display_mode = NODE_DISPLAY_PANE;

const unsigned int default_pane_width_chars = 68;
const unsigned int default_pane_height_lines = 4;
const unsigned int default_pane_border_width = 1;
const unsigned int default_pane_interline_space = 2;

const unsigned int default_font_size = 12;


typedef std::vector<std::string> NodeNameList;


class ConfigInfo {
public:
    ConfigInfo();

public:
    bool parseCommandLine(int& argc, wxChar **argv);

    void writeSampleConfigFile() const;

    void dump() const;

public:
    // Config fields
    double period;

    unsigned int num_columns;

    unsigned int node_access_timeout;

    unsigned int max_response_time;
    unsigned int max_num_fails;

    unsigned int display_mode;
    
    unsigned int pane_width_chars;
    unsigned int pane_height_lines;
    unsigned int pane_border_width;
    unsigned int pane_interline_space;

    unsigned int font_size;

    wxFileName config_filename;
    NodeNameList nodes;
};


#endif /* end of MESH_STAT_CONFIG_H */
