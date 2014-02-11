#pragma once

#include "Box2D\Box2D.h"
class DebugDrawer : public b2Draw
{
public:
	DebugDrawer(){SetFlags( b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit );}
	//void setRenderTarget(sf::RenderTarget *target){this->target = target;};
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);
};

