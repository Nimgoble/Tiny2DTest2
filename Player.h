#pragma once

#include "SceneObject.h"

//Our mega-man player
class Player : public SceneObject
{
public:
	Player();
	Player(const T2DTVec2D& position);
	~Player();

	virtual void Initialize();
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(Tiny2D::Texture& renderTarget);
	virtual void OnCollision(b2Fixture *ourFixture, SceneObject *other);
	virtual void PopulateBodyDefinition(b2BodyDef &def);
	virtual void OnBodyInitialized();

	void TeleportToGround();
private:
	Tiny2D::Sprite megaManSprite;
	bool facingLeft;

	std::string currentAnimation;
	bool isJumping;
	bool canJump;
	bool jumped;
	bool onGround;
	bool wallSliding;
	bool teleporting;

	/*b2Fixture *top;
	b2Fixture *bottom;
	b2Fixture *left;
	b2Fixture *right;*/

	Tiny2D::Font font;
	void CheckMovement();
	void UpdateAnimation();

	bool CurrentAnimationDone();
	b2Vec2 previousVelocity;

	struct BorderInfo
	{
		BorderInfo()
		{
			touching = false;
			fixture = NULL;
		}
		bool touching;
		b2Fixture *fixture;
	};

	BorderInfo top;
	BorderInfo bottom;
	BorderInfo left;
	BorderInfo right;

};