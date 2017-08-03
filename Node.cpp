#include "Node.h"


Node::Node(const std::string url_, 
	   NodeDisplay *new_display)
    : url(url_),
      display(new_display)
{
}
