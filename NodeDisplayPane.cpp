#include <stdio.h>

#include <iostream>
#include <sstream>
#include <algorithm>  // max()

#include <wx/tooltip.h>

#include "Config.h"

extern ConfigInfo config;

#include "Node.h"
#include "NodeDisplayPane.h"
#include "ColorInterpolate.h"


NodeDisplayPane::NodeDisplayPane(wxWindow *parent, const wxSize &cell_size)
    : wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, cell_size,
		 wxTE_MULTILINE|wxTE_READONLY|wxTE_NO_VSCROLL|wxTE_RICH2)
{
    start_color.Set(start_r, start_g, start_b);

    response_color.setColors(fast_color_r, fast_color_g, fast_color_b, 
			     slow_color_r, slow_color_g, slow_color_b);

    fail_color.setColors(min_fails_color_r, min_fails_color_g, min_fails_color_b, 
			 max_fails_color_r, max_fails_color_g, max_fails_color_b);

    SetMinSize(cell_size);
}


void NodeDisplayPane::update()
{
    Update();
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
    ClearBackground();

    // Print the node name in bold
    wxTextAttr ta = GetDefaultStyle();
    ta.SetFontWeight(wxFONTWEIGHT_BOLD);
    ta.SetBackgroundColour(*bg_color);
    SetDefaultStyle(ta);
    if (node.name.empty())
	AppendText(node.url);
    else
	AppendText(node.name);

    // Print the rest normally
    ta.SetFontWeight(wxFONTWEIGHT_NORMAL);
    ta.SetBackgroundColour(*bg_color);
    SetDefaultStyle(ta);

    delete bg_color;

    if (node.num_fails < 0)
    {
	// Show nothing else initially
    }
    else if (node.num_fails == 0)
    {
	std::stringstream node_info;
	
	if (!node.wifi_ip.empty())
	    node_info << "     WIFI:" << node.wifi_ip;
	if (!node.lan_ip.empty())
	    node_info << "  LAN:" << node.lan_ip;
	if (!node.wan_ip.empty())
	    node_info << "  WAN:" << node.wan_ip;
	node_info << std::endl;

	char info[200];
	sprintf(info, "Channel: %3d  BW: %2.0f, SSID: %s\n", 
		node.channel, node.chanbw, node.ssid.c_str());
	node_info << info;

	sprintf(info, "Model: %s,  Firmware: %s %s\n", node.model.c_str(), 
		node.firmware_mfg.c_str(),
		node.firmware_version.c_str());
	node_info << info;

	std::string last_time = node.last_succesful_probe_time.Format("%X %x").ToStdString();
	sprintf(info, "Last Response Time: %6.2f seconds  at %s", 
		static_cast<double>(node.last_response_time) / 1000.0,
		last_time.c_str());
	node_info << info;

	if (config.display_mode == NODE_DISPLAY_PANE)
	{
	    AppendText(node_info.str());
	}
	else if (config.display_mode == NODE_DISPLAY_PANE_ONE_LINE_STATUS)
	{
	    std::string last_time = node.last_succesful_probe_time.Format("%X %x").ToStdString();
	    std::stringstream line;
	    line << "   Last seen at " << last_time.c_str();
	    AppendText(line.str());

	    std::string tool_tip = std::string("Node stats for ") + node.name;
	    tool_tip += node_info.str();
	    SetToolTip(tool_tip);
	}

	Update();

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

	std::stringstream fail_info;
	fail_info << std::endl;

	if (no_successful_probe)
	{
	    fail_info << "No successful access ";
	}
	else
	{
	    std::string last_time = node.last_succesful_probe_time.Format("%X %x").ToStdString();
	    fail_info << "Last successful access at " << last_time << ", " << std::endl;
	}

	if ((num_days > 0) or (num_hours > 0) or (num_minutes > 0) or (num_seconds > 0.0))
	    fail_info << "since ";

	if (num_days > 0)
	    fail_info << num_days << " days ";
	if (num_hours > 0)
	    fail_info << num_hours << " hours ";
	if (num_minutes > 0)
	    fail_info << num_minutes << " minutes ";
	if (num_seconds > 0.0)
	    fail_info << num_seconds << " seconds";

	if ((num_days > 0) or (num_hours > 0) or (num_minutes > 0) or (num_seconds > 0.0))
	    fail_info << " ago ";

	if (no_successful_probe) 
	{
	    std::string start_time = node.start_time.Format("%X %x").ToStdString();
	    fail_info << std::endl << "at " << start_time << ", ";
	}

	fail_info << "(num failures: " << node.num_fails << ")";

	if (config.display_mode == NODE_DISPLAY_PANE)
	{
	    AppendText(fail_info.str());
	}
	else if (config.display_mode == NODE_DISPLAY_PANE_ONE_LINE_STATUS)
	{
	    std::stringstream ss;
	    if (no_successful_probe) 
	    {
		std::string start_time = node.start_time.Format("%X %x").ToStdString();
		ss << "   " << "No access since " << start_time << ", " << node.num_fails << " fails";
	    }
	    else
	    {
		std::string last_time = node.last_succesful_probe_time.Format("%X %x").ToStdString();
		ss << "   " << "Last access at " << last_time  << ", " << node.num_fails << " fails";
	    }

	    AppendText(ss.str());

	    std::string tool_tip = std::string("Node failure stats for ") + node.name;
	    tool_tip += fail_info.str();
	    SetToolTip(tool_tip);
	}

	Update();
    }

}
