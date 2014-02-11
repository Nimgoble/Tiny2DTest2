#pragma once
#include "Box2D\Box2D.h"
#include "ThirdParty\Tiny2D\Include\Tiny2D.h"

class T2DTColorHelper
{
public:
	static b2Color GetBox2DColorFromTiny2DColor(const Tiny2D::Color& color)
	{
		return b2Color(color.r, color.g, color.b);
	}

	static Tiny2D::Color GetTiny2DColorFromBox2DColor(const b2Color& color)
	{
		return Tiny2D::Color(color.r, color.g, color.b);
	}
};