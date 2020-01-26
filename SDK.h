#pragma once
#include <cmath>
#include <cstdint>
// Glow Object
struct glow_t
{
	float r, g, b, a;
	char padding_0000[16];
	bool RenderWhenOccluded;
	bool RenderWhenUnoccluded;
	bool FullBloom;
	char padding_0001;
	int FullBloomStencilTestValue;
	int GlowStyle;
	char padding_0002[10];
};