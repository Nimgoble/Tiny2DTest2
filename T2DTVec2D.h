#pragma once
#include <Box2D\Box2D.h>
#include "ThirdParty\Tiny2D\Include\Tiny2D.h"

class T2DTVec2D : public Tiny2D::Vec2
{
public:
	//! Constructs vector
	inline T2DTVec2D(float x = 0.0f, float y = 0.0f) : Tiny2D::Vec2(x, y){}
	//! Copy consructor
	inline T2DTVec2D(const T2DTVec2D& other) : Tiny2D::Vec2(other){}
	//Convert Box2D b2vec2 to Tiny2D Vec2
	static inline Tiny2D::Vec2 FromBox2DVec(b2Vec2 vec){return Tiny2D::Vec2(vec.x * pixelsPerMeter, vec.y * pixelsPerMeter);}
	//Convert this to b2Vec2
	inline b2Vec2 ToBox2DVec(){return b2Vec2(this->x / pixelsPerMeter, this->y / pixelsPerMeter);}
private:
	static const float pixelsPerMeter;
};
