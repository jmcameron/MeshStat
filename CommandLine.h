// MeshStat command line options handling

#ifndef MESH_STAT_COMMAND_LINE_H
#define MESH_STAT_COMMAND_LINE_H

#include "wx/wx.h"
#include "wx/cmdline.h"

typedef struct {
    wxFileName filename;
} MeshStatRunInfo;

bool parseCommandLine(int& argc, wxChar **argv, MeshStatRunInfo &info);


#endif /* end of MESH_STAT_COMMAND_LINE_H */
