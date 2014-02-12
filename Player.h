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
	virtual void OnCollision(SceneObject *other);
	virtual void PopulateBodyDefinition(b2BodyDef &def);
	virtual void OnBodyInitialized();
private:
	Tiny2D::Sprite megaManSprite;
	bool facingLeft;

	std::string currentAnimation;
	bool isJumping;

	b2Fixture *top;
	b2Fixture *bottom;
	b2Fixture *left;
	b2Fixture *right;
};