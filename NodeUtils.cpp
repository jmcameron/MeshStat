#include "NodeUtils.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <wx/wx.h>
#include <wx/regex.h>


void getNodeDataJSON(NodeDataMap &data, const std::string &json)
{
    boost::property_tree::ptree pt;
    try 
    {
	std::stringstream ss;
	ss << json;
	boost::property_tree::read_json(ss, pt);

	const boost::property_tree::ptree::const_iterator end = pt.end();
	for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != end; ++it) 
	{
	    const std::string key(it->first);
	    const boost::property_tree::ptree & subtree = it->second;

	    if (subtree.empty())
	    {
		// Key-value
		const std::string val(it->second.get_value<std::string>());
		data[key] = val;
	    }
	    else 
	    {
		// Subtree
		data[key] = "[CHILDREN]";
	    }

	}
    }
    catch (std::exception const& e) 
    {
	const std::string errmsg = std::string("Error reading json!  ") + std::string(e.what());
	wxLogMessage(errmsg.c_str());
    }
}

//    std::string lines("{\"channel\":\"174\",\"lat\":\"34.200464\",\"board_id\":\"0xe1b5\",\"api_version\":\"1.0\",\"model\":\"Ubiquiti Rocket M\",\"chanbw\":\"20\",\"tunnel_installed\":\"true\",\"ssid\":\"AREDN-20-v3\",\"node\":\"W6JPL-M5R-180R6\",\"lon\":\"-118.174341\",\"firmware_version\":\"3.16.1.1\",\"firmware_mfg\":\"AREDN\",\"grid_square\":\"\",\"active_tunnel_count\":\"0\",\"interfaces\":[{\"name\":\"eth0\",\"ip\":\"10.65.182.97\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.1\",\"ip\":\"44.16.15.50\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.2\",\"ip\":\"10.165.27.102\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"wlan0\",\"ip\":\"10.164.27.102\",\"mac\":\"24:A4:3C:A4:1B:66\"},{\"name\":\"wlan0-1\",\"ip\":\"none\",\"mac\":\"24-A4-3C-A4-1B-66-00-44-00-00-00-00-00-00-00-00\"}]}");

// wxLogMessage(info.str().c_str());
