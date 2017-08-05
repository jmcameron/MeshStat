#include "Node.h"


Node::Node(const std::string url_)
    : url(url_)
{
}


void Node::setNodeDisplay(NodeDisplay *new_display)
{
    display = new_display;
}
