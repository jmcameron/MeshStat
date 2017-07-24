/// Node Utils

#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <map>
#include <string>

typedef std::map<std::string, std::string> NodeDataMap;

void getNodeDataJSON(NodeDataMap &data, const std::string &json);

#endif /* end of NODE_UTILS_H */
