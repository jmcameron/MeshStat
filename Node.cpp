#include "Node.h"


Node::Node(const std::string url_)
    : url(url_),
      latitude(0),
      longitude(0),
      chanbw(0),
      channel(0),
      num_fails(-1),
      last_read_time(0),
      display(0)
{
}


void Node::setNodeDisplay(NodeDisplay *new_display)
{
    display = new_display;
}
