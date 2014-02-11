#pragma once
#include <Box2D\Box2D.h>

class T2DTestContactListener : public b2ContactListener
{
public:
	T2DTestContactListener(void);
	~T2DTestContactListener(void);

	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
};

