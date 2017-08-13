/// ColorInterpolate Class
///

#ifndef MESH_STAT_COLOR_INTERPOLATE_H
#define MESH_STAT_COLOR_INTERPOLATE_H

class wxColour;


/// Interpolate between to predefined colors

class ColorInterpolate {
public:
    ColorInterpolate() {};

    void setColors(unsigned char r1_,
		   unsigned char g1_,
		   unsigned char b1_,
		   unsigned char r2_,
		   unsigned char g2_,
		   unsigned char b2_);

    wxColour* color(const double x) const;

    unsigned char r1;
    unsigned char g1;
    unsigned char b1;

    unsigned char r2;
    unsigned char g2;
    unsigned char b2;

    double r_range;
    double g_range;
    double b_range;
};



#endif /* end of MESH_STAT_COLOR_INTERPOLATE_H */
