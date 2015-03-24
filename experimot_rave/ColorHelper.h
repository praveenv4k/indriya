#ifndef __COLOR_HELPER_H__
#define __COLOR_HELPER_H__

#include "Colors.h"
#include "experimot\msgs\MessageTypes.h"
#include "openrave-core.h"

class ColorHelper{
public:
	static void HexToRgb(int hexValue, int& r, int& g, int& b){
		r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
		g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
		b = ((hexValue)& 0xFF) / 255.0;        // Extract the BB byte
	}

	static void HexToRgb(int hexValue, experimot::msgs::Color& color){
		int r, g, b;
		HexToRgb(hexValue, r, g, b);
		color.set_r(r);
		color.set_g(g);
		color.set_b(b);
	}

	static void HexToRgb(int hexValue, OpenRAVE::RaveVector<float>& color){
		int r, g, b;
		HexToRgb(hexValue, r, g, b);
		color.x = r;
		color.y = g;
		color.z = b;
	}
};

#endif