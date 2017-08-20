#include <stdio.h>

#include <iostream>
#include <sstream>
#include <algorithm>  // max()

// #include <wx/tooltip.h>

#include "Config.h"

extern ConfigInfo config;

#include "Node.h"
#include "NodeDisplayPane.h"
#include "ColorInterpolate.h"


NodeDisplayPane::NodeDisplayPane(wxWindow *parent, const wxSize &cell_size)
    : wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, cell_size,
		 wxTE_MULTILINE|wxTE_READONLY|wxTE_NO_VSCROLL)
{
    start_color.Set(start_r, start_g, start_b);

    response_color.setColors(fast_color_r, fast_color_g, fast_color_b, 
			     slow_color_r, slow_color_g, slow_color_b);

    fail_color.setColors(min_fails_color_r, min_fails_color_g, min_fails_color_b, 
			 max_fails_color_r, max_fails_color_g, max_fails_color_b);

    SetMinSize(cell_size);
}



void NodeDisplayPane::updateDisplay(const Node &node)
{
    wxColour *bg_color;

    // Figure out the color for the background
    if (node.num_fails < 0) {
	bg_color = new wxColour(start_color);
	}
    else if (node.num_fails > 0) {
	double factor = 0.0;
	if (static_cast<unsigned int>(node.num_fails) >= config.max_num_fails)
	    factor = 1.0;
	else
	    factor = static_cast<double>(node.num_fails)/static_cast<double>(config.max_num_fails);
	bg_color = fail_color.color(factor);
	}
    else {
	double factor = 0.0;
	if (node.last_response_time >= config.max_response_time)
	    factor = 1.0;
	else
	    factor = static_cast<double>(node.last_response_time) / static_cast<double>(config.max_response_time);
	bg_color = response_color.color(factor);
	}

    // Clear the pane
    Clear();
    SetBackgroundColour(*bg_color);
    delete bg_color;
    ClearBackground();

    // Print the node name in bold
    wxTextAttr ta = GetDefaultStyle();
    ta.SetFontWeight(wxFONTWEIGHT_BOLD);
    SetDefaultStyle(ta); 
    AppendText(node.name);

    // Print the rest normally
    ta.SetFontWeight(wxFONTWEIGHT_NORMAL);
    SetDefaultStyle(ta); 

    std::stringstream ipinfo;
    if (!node.wifi_ip.empty())
	ipinfo << "     WIFI:" << node.wifi_ip;
    if (!node.lan_ip.empty())
	ipinfo << "  LAN:" << node.lan_ip;
    if (!node.wan_ip.empty())
	ipinfo << "  WAN:" << node.wan_ip;
    ipinfo << std::endl;
    AppendText(ipinfo.str());

    if (node.num_fails < 1)
    {
	char line[200];
	sprintf(line, "Channel: %3d  BW: %2.0f, SSID: %s\n", 
		node.channel, node.chanbw, node.ssid.c_str());
    	AppendText(line);

	sprintf(line, "Model: %s,  Firmware: %s %s\n", node.model.c_str(), 
		node.firmware_mfg.c_str(),
		node.firmware_version.c_str());
	AppendText(line);

	std::string last_time = node.last_succesful_probe_time.Format("%r").ToStdString();
	sprintf(line, "Last Response Time: %6.2f seconds  at %s", 
		static_cast<double>(node.last_response_time) / 1000.0,
		last_time.c_str());
	// ??? Display full date if last_succesful_probe_time more than 24 hours in past
	AppendText(line);

	// std::string tool_tip = std::string("Node stats for ") + node.name;
	// SetToolTip(tool_tip.c_str());

        // Right-click menu: https://stackoverflow.com/questions/14487102/wxwidgets-contextmenu-popup
    }
    else 
    {
	wxDateTime now = wxDateTime::Now();

	const bool no_successful_probe = node.last_succesful_probe_time == node.start_time;
	const wxTimeSpan delta_time = now.Subtract(node.last_succesful_probe_time);

	const unsigned long int nsecs = static_cast<unsigned int>(delta_time.GetSeconds().ToDouble());
	const unsigned int num_days =  nsecs / (24*60*60);
	const unsigned int num_hours = (nsecs - ((24*60*60) * num_days)) / (60*60);
	const unsigned int num_minutes = (nsecs - ((24*60*60) * num_days) - ((60*60) * num_hours)) / 60;
	const unsigned int num_seconds = nsecs - ((24*60*60) * num_days) - ((60*60) * num_hours) - (60 * num_minutes);

	std::stringstream ss;
	if (no_successful_probe) 
	    ss << "No succesful access in ";
	else
	    ss << "Last successful access ";
	if (num_days > 0)
	    ss << num_days << " days ";
	if (num_hours > 0)
	    ss << num_hours << " hours ";
	if (num_minutes > 0)
	    ss << num_minutes << " minutes ";
	if (num_seconds > 0.0)
	    ss << num_seconds << " seconds ";

	if (!no_successful_probe) 
	    ss << "ago ";

	ss << "  (num failures: " << node.num_fails << ")";

    	AppendText(ss.str());
    }

}
