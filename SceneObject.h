#pragma once
#include "ThirdParty\Tiny2D\Include\Tiny2D.h"
#include <Box2D\Box2D.h>
#include "T2DTVec2D.h"

class SceneObject
{
public:
	SceneObject();
	~SceneObject(void);

	virtual void Initialize();
	virtual void OnUpdate(float deltaTime);
	virtual void OnCollision(b2Fixture *ourFixture, SceneObject *other);
	virtual void OnDraw(Tiny2D::Texture& renderTarget);
	//Body
	void InitBody(b2World *world);
	virtual void PopulateBodyDefinition(b2BodyDef &def);
	virtual void OnBodyInitialized();
	b2Body *GetBody() {return body;}
	//Position
	const T2DTVec2D& GetPosition() {return position;}
	void SetPosition(const T2DTVec2D& newPosition) 
	{
		position = newPosition;
		UpdateBody();
	}
	//Angle
	float GetAngle() {return angle;}
	void SetAngle(float newAngle)
	{
		angle = newAngle;
		UpdateBody();
	}
protected:
	b2Body *body;
	T2DTVec2D position;
	float angle;

	inline void UpdateBody()
	{
		if(body != nullptr)
			body->SetTransform(position.ToBox2DVec(), angle);
	}
};