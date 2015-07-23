#ifndef __COLOR_HELPER_H__
#define __COLOR_HELPER_H__

#include "Colors.h"
#include "experimot\msgs\MessageTypes.h"
#include "openrave-core.h"

class ColorHelper{
public:
	static void HexToRgb(int hexValue, float& r, float& g, float& b){
		r = (float)((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
		g = (float)((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
		b = (float)((hexValue)& 0xFF) / 255.0;        // Extract the BB byte
	}

	static void HexToRgb(int hexValue, Indriya::Core::Msgs::Color& color){
		float r, g, b;
		HexToRgb(hexValue, r, g, b);
		color.set_r(r);
		color.set_g(g);
		color.set_b(b);
	}

	static void HexToRgb(int hexValue, OpenRAVE::RaveVector<float>& color){
		float r, g, b;
		HexToRgb(hexValue, r, g, b);
		color.x = r;
		color.y = g;
		color.z = b;
		color.w = 1;
	}

	static void HexToRgb(int hexValue, unsigned char alpha, OpenRAVE::RaveVector<float>& color){
		float r, g, b;
		HexToRgb(hexValue, r, g, b);
		color.x = r;
		color.y = g;
		color.z = b;
		color.w = alpha/255.0;
	}

	static void FromArgb(unsigned char a, unsigned char r, unsigned char g, unsigned char b, OpenRAVE::RaveVector<float>& color){
		color.x = (float)(r) / 255.0;		 // Extract the RR byte
		color.y = (float)(g) / 255.0;		 // Extract the GG byte
		color.z = (float)(b) / 255.0;        // Extract the BB byte
		color.w = (float)(a) / 255.0;
	}
};

#endif