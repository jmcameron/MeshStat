#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <wx/wx.h>
#include <wx/url.h>
#include <wx/sstream.h>

#include "Node.h"
#include "NodeDisplay.h"
// ??? #include "NodeUtils.h"


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


void Node::probe()
{
    if (num_fails < 0)
	num_fails = 0;

    last_response_time = 0;

    wxString htmldata;
 
    wxStopWatch timer;  // Start the timer
 
    const std::string test_url = std::string("http://") + url + ":8080/cgi-bin/sysinfo.json";
    // ??? std::cerr << "-------------------- NODE: " << name << std::endl;
    // ??? std::cerr << "OPEN URL: " << test_url << " at " << timer.Time() << " ms" << std::endl;
    wxURL url(test_url.c_str());
    // ??? std::cerr << "URL OK: " << url.IsOk() << std::endl;
 
    if(url.GetError()==wxURL_NOERR)
    {
 	// ??? std::cerr << "GET INPUT STREAM: " << timer.Time() << " ms" << std::endl;
  	wxInputStream *in = url.GetInputStream();
  	if(in && in->IsOk())
  	{
 	    // ??? std::cerr << "CAN READ: " << in->CanRead() << std::endl;
 
  	    wxStringOutputStream html_stream(&htmldata);
 	    // ??? std::cerr << "READ INPUT STREAM: " << timer.Time() << " ms" << std::endl;
  	    in->Read(html_stream);
 	    // ??? std::cerr << "READ INPUT STREAM DONE: " << timer.Time() << " ms" << std::endl;
  	}
  	delete in;

	last_response_time = timer.Time();
    }
    else 
    {
 	// ??? std::cerr << "ERROR OPENING URL: " << test_url << " at "<< timer.Time() << " ms" << std::endl;
  	htmldata = "";
    }
    timer.Pause();
 
    // ??? std::cerr << "FINISHED: " << timer.Time() << " ms" << std::endl;
    // ??? std::cerr << "DATA READ: " << htmldata.size() << std::endl;
 
    if (htmldata.size() > 0)
    {
 	const std::string lines = std::string(htmldata.mb_str());
 
	readDataFromJSON(lines);

 	// ??? NodeDataMap data;
 
 	// ??? timer.Resume();
 
 	// ??? std::cerr << "START PARSING: " << timer.Time() << " ms" << std::endl;
 	// ??? getNodeDataJSON(data, lines);
 	// ??? std::cerr << "END PARSING: " << timer.Time() << " ms" << std::endl;
// ???  
// ???  	for (NodeDataMap::const_iterator dit = data.begin(); dit != data.end(); ++dit)
// ???  	{
// ???  	    const std::string name(dit->first);
// ???  	    const std::string val(dit->second);
// ???  	    const std::string prt = name + std::string(": ") + val + std::string("\n");
// ???  	    // AppendText(prt);
// ???  	}
 	// ??? timer.Pause();
    }
    else
    {
	num_fails += 1;
	// ??? std::cerr << std::string("ERROR: Unable to read data from ") + test_url + "\n";
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
		    latitude = it->second.get_value<double>();
		    }
		else if (key == "lon") {
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
	    else 
	    {
		// Subtree
	    }

	}
    }
    catch (std::exception const& e) 
    {
	const std::string errmsg = std::string("Error reading json!  ") + std::string(e.what());
	wxLogMessage(errmsg.c_str());
    }

}
