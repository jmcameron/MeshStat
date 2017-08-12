#include <wx/wx.h>

#include "ColorInterpolate.h"



void ColorInterpolate::setColors(unsigned char r1_,
				 unsigned char g1_,
				 unsigned char b1_,
				 unsigned char r2_,
				 unsigned char g2_,
				 unsigned char b2_)
{
    r1 = r1_;
    g1 = g1_;
    b1 = b1_;

    r2 = r2_;
    g2 = g2_;
    b2 = b2_;

    r_range = static_cast<double>(r2 - r1);
    g_range = static_cast<double>(g2 - g1);
    b_range = static_cast<double>(b2 - b1);
}


wxColour* ColorInterpolate::color(const double x) const
{
    if (x <= 0.0)
	return new wxColour(r1,g1,b1);
    if (x >= 1.0)
	return new wxColour(r2,g2,b2);
    
    const unsigned char r = r1 + static_cast<unsigned char>(x*r_range);
    const unsigned char g = g1 + static_cast<unsigned char>(x*g_range);
    const unsigned char b = b1 + static_cast<unsigned char>(x*b_range);

    return new wxColour(r, g, b);
}
