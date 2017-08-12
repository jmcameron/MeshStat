#include <algorithm>

#include "Node.h"
#include "NodeDisplay.h"


inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

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
    std::string url_lower_case(url);
    std::transform(url_lower_case.begin(), url_lower_case.end(), url_lower_case.begin(), ::tolower);
    if (ends_with(url_lower_case, ".local.mesh"))
	name = url.substr(0, url.size() - 11);
    else
	name = url;
}


void Node::setNodeDisplay(NodeDisplay *new_display)
{
    display = new_display;
}


void Node::updateDisplay()
{
    display->updateDisplay(*this);
}
