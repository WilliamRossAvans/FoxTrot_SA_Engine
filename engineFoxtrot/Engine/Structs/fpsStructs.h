#pragma once
#include "core.h"
struct API FpsMessage
{
	FpsMessage(const string& _text, int _r, int _g, int _b)
		: text{ _text }, red{ _r }, green{ _g }, blue{ _b }{}
	const string& text;
	int red, green, blue;
};

struct API TextPosition
{
	TextPosition(int _x, int _y) : xPos{ _x }, yPos{ _y } {}
	int xPos, yPos;
};

struct API TextSize
{
	TextSize(int _w, int _h) : width{ _w }, height{ _h } {}
	int width, height;
};