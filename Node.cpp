#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <wx/wx.h>
#include <wx/url.h>
#include <wx/sstream.h>

#include "MainFrame.h"
extern MainFrame *main_frame_global;

#include "Config.h"
extern ConfigInfo config;

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
      last_response_time(0),
      display(0)
{
    last_succesful_probe_time = wxDateTime::Now();
    start_time = wxDateTime::Now();

    std::string url_lower_case(url);
    std::transform(url_lower_case.begin(), url_lower_case.end(), url_lower_case.begin(), ::tolower);
    if (ends_with(url_lower_case, ".local.mesh"))
	name = url.substr(0, url.size() - 11);
    else
	name = url;
}

Node::~Node()
{
}


void Node::setNodeDisplay(NodeDisplay *new_display)
{
    display = new_display;
}


void Node::updateDisplay()
{
    display->updateDisplay(*this);
}


void Node::probe()
{
    last_response_time = 0;

    wxString htmldata;
 
    wxStopWatch timer;  // Start the timer
 
    const std::string full_url = std::string("http://") + url + ":8080/cgi-bin/sysinfo.json";

    // ??? std::stringstream msg;
    // ??? msg << "-------------------- NODE: " << name << std::endl;
    // ??? msg << "OPEN URL: " << full_url << " at " << timer.Time() << " ms" << std::endl;

    wxURL url(full_url.c_str());
    // ??? msg << "URL OK: " << url.IsOk() << std::endl;

    if(url.GetError()==wxURL_NOERR)
    {
	url.GetProtocol().SetDefaultTimeout(config.node_access_timeout);
 	// ??? msg << "GET INPUT STREAM BEFORE: " << timer.Time() << " ms" << std::endl;
  	wxInputStream *in = url.GetInputStream();

	// Give the display a chance to catch up
	display->update();

 	// ??? msg << "GET INPUT STREAM AFTER: " << in << " " << timer.Time() << " ms" << std::endl;

  	if (in and in->IsOk())
  	{
 	    // ??? msg << "CAN READ: " << in->CanRead() << std::endl;
  	    wxStringOutputStream html_stream(&htmldata);
 	    // ??? msg << "READ INPUT STREAM: " << timer.Time() << " ms" << std::endl;

	    // Give the display a chance to catch up
	    display->update();

  	    in->Read(html_stream);
 	    // ??? msg << "READ INPUT STREAM DONE: " << timer.Time() << " ms" << std::endl;

	    last_response_time = timer.Time();

	    delete in;
  	}
    }
    else 
    {
 	// ??? msg << "ERROR OPENING URL: " << full_url << " at "<< timer.Time() << " ms" << std::endl;
  	htmldata = "";
    }
    timer.Pause();
 
    // ??? msg << "FINISHED: " << timer.Time() << " ms" << std::endl;
    // ??? msg << "DATA READ: " << htmldata.size() << std::endl;

    // ??? if (timer.Time() > 3000) {
    // ???     wxMessageDialog dialog(this, msg.str(), _("ERROR"), wxICON_ERROR);
    // ???     dialog.ShowModal();
    // ???     }

    if (htmldata.size() > 0)
    {
	last_succesful_probe_time = wxDateTime::Now();
	num_fails = 0;

 	const std::string lines = std::string(htmldata.mb_str());

	// Give the display a chance to catch up
	display->update();

	// Example JSON output
	// {"lat":"34.200464",
	//  "grid_square":"",
	//  "chanbw":"20",
	//  "api_version":"1.0",
	//  "node":"W6JPL-M5R-180R6",
	//  "tunnel_installed":"true",
	//  "ssid":"AREDN-20-v3",
	//  "board_id":"0xe1b5",
	//  "firmware_mfg":"AREDN",
	//  "model":"Ubiquiti Rocket M",
	//  "channel":"174",
	//  "firmware_version":"3.16.1.1",
	//  "active_tunnel_count":"0",
	//  "lon":"-118.174341",
	//  "interfaces":[{"name":"eth0",
	//                 "ip":"10.65.182.97",
	//                 "mac":"24:A4:3C:A5:1B:66"},
	//                {"name":"eth0.1",
	// 		"ip":"44.16.15.50",
	//                 "mac":"24:A4:3C:A5:1B:66"},
	//                {"name":"eth0.2",
	//                 "ip":"10.165.27.102",
	//                 "mac":"24:A4:3C:A5:1B:66"},
	//                {"name":"wlan0",
	//                 "ip":"10.164.27.102",
	//                 "mac":"24:A4:3C:A4:1B:66"},
	//                {"name":"wlan0-1",
	//                 "ip":"none",
	//                 "mac":"24-A4-3C-A4-1B-66-00-44-00-00-00-00-00-00-00-00"}]
	// }

	readDataFromJSON(lines);
    }
    else if (num_fails == -1)
    {
	num_fails = 1;
    }
    else
    {
	num_fails += 1;
    }

}


void Node::readDataFromJSON(const std::string &json)
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
		// Get the basic node properties
		if (key == "node") {
		    name = it->second.get_value<std::string>();
		    }
		else if (key == "channel") {
		    channel = it->second.get_value<int>();
		    }
		else if (key == "chanbw") {
		    chanbw = it->second.get_value<double>();
		    }
		else if (key == "lat") {
		    const std::string lat_str = it->second.get_value<std::string>();
		    if (lat_str.empty())
			latitude = 0.0;
		    else
			latitude = it->second.get_value<double>();
		    }
		else if (key == "lon") {
		    const std::string lon_str = it->second.get_value<std::string>();
		    if (lon_str.empty())
			longitude = 0.0;
		    else
			longitude = it->second.get_value<double>();
		    }
		else if (key == "model") {
		    model = it->second.get_value<std::string>();
		    }
		else if (key == "firmware_mfg") {
		    firmware_mfg = it->second.get_value<std::string>();
		    }
		else if (key == "firmware_version") {
		    firmware_version = it->second.get_value<std::string>();
		    }
		else if (key == "ssid") {
		    ssid = it->second.get_value<std::string>();
		    }
	    }
	    else if (key == "interfaces")
	    {
		// Process the interfaces
		for (boost::property_tree::ptree::const_iterator arit = subtree.begin(); arit != subtree.end(); ++arit) 
		{
		    const std::string key(arit->first);
		    const boost::property_tree::ptree & array = arit->second;

		    std::string if_name;
		    std::string if_ip;

		    for (boost::property_tree::ptree::const_iterator ifit = array.begin(); ifit != array.end(); ++ifit) 
		    {
			const std::string key(ifit->first);
			const std::string val(ifit->second.get_value<std::string>());
			if (key == "name")
			    if_name = val;
			else if (key == "ip")
			    if_ip = val;
		    }

		    // Figure out which interface this is
		    if ((if_name == "eth0") and (if_ip != "none"))
			lan_ip = if_ip;
		    else if ((if_name == "eth0.0") and (if_ip != "none"))
			lan_ip = if_ip;
		    else if ((if_name == "eth0.1") and (if_ip != "none"))
			wan_ip = if_ip;
		    else if ((if_name == "eth0.2") and (if_ip != "none"))
			wifi_ip = if_ip;
		    else if ((if_name == "eth1") and (if_ip != "none"))
			wan_ip = if_ip;
		    else if ((if_name == "wlan0") and (if_ip != "none"))
			wifi_ip = if_ip;
		}
	    }
	    else 
	    {
		std::cerr << "Error parsing sysinfo.json output for " << name << std::endl;
	    }
	}
    }
    catch (std::exception const& e) 
    {
	const std::string errmsg =
	    std::string("Error reading sysinfo.json data!  ") + std::string(e.what());
	wxMessageDialog dialog(main_frame_global, errmsg, _("ERROR"), wxICON_ERROR);
	dialog.ShowModal();
    }

}
