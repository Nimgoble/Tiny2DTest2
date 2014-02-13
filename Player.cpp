#include "Player.h"

using namespace Tiny2D;

Player::Player() :
	facingLeft(false),
	currentAnimation("idle"),
	isJumping(false),
	top(nullptr),
	bottom(nullptr),
	left(nullptr),
	right(nullptr),
	canJump(false),
	jumped(false),
	onGround(false),
	wallSliding(false)
{
}

Player::Player(const T2DTVec2D& position) :
	facingLeft(false),
	currentAnimation("idle"),
	isJumping(false),
	top(nullptr),
	bottom(nullptr),
	left(nullptr),
	right(nullptr),
	canJump(false),
	jumped(false),
	onGround(false),
	wallSliding(false)
{
	this->position = position;
}

Player::~Player()
{
}

void Player::Initialize()
{
	megaManSprite.Create("megamanx_base", false, Sprite::AtlasType::AtlasType_XML);
	megaManSprite.PlayAnimation(currentAnimation);
}

void Player::OnUpdate(float deltaTime)
{
	const float speed = 5.0f;

	bool isWalking = false;
	b2Vec2 velocity = body->GetLinearVelocity();
	if (Input::IsKeyDown(Input::Key_Left))
	{
		velocity.x = -speed;
		//position.x -= deltaTime * speed;
		isWalking = true;
		facingLeft = true;
	}
	else if (Input::IsKeyDown(Input::Key_Right))
	{
		velocity.x = speed;
		isWalking = true;
		facingLeft = false;
	}
	else 
		velocity.x = 0.0f;

	if(Input::IsKeyDown(Input::Key_Up) && isJumping == false)
	{
		velocity.y = -15;
		isJumping = true;
	}

	body->SetLinearVelocity(velocity);
	//body->ApplyForceToCenter(velocity);

	currentAnimation = (isJumping) ? "jumpStart" : (isWalking) ? "run" : "idle";

	megaManSprite.PlayAnimation(currentAnimation);
	megaManSprite.Update(deltaTime);
}

void Player::OnDraw(Tiny2D::Texture& renderTarget)
{
	Sprite::DrawParams params;
	params.position = T2DTVec2D::FromBox2DVec(body->GetPosition());//position;
	params.flipX = facingLeft;
	//params.scale = 1.4f;//...maybe?
	params.centered = true;

	megaManSprite.Draw(&params);
}

void Player::OnCollision(b2Fixture *ourFixture, SceneObject *other)
{
	isJumping = false;
	if(ourFixture == top)
		int d = 0;
	else if(ourFixture == bottom)
		int d = 0;
	else if(ourFixture == left)
		int d = 0;
	else if(ourFixture == right)
		int d = 0;
}

void Player::PopulateBodyDefinition(b2BodyDef &def)
{
	def.type = b2BodyType::b2_dynamicBody;
	def.fixedRotation = true;
	def.gravityScale = 10.0f;
	def.allowSleep = false;
	SceneObject::PopulateBodyDefinition(def);
}

void Player::OnBodyInitialized()
{
	b2PolygonShape boundingBox;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boundingBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;

	
	float topBottomWidth = (15.0f / 32.0f);//15 pixels
	float leftRightHeight = (13.0f / 32.0f);//13 pixels
	float otherSize = (1.0f / 32.0f);//1 pixel
	b2Vec2 boxSize(topBottomWidth, topBottomWidth);

	//calculations between pixels and meters are a pain in the ass.
	boundingBox.SetAsBox(topBottomWidth, otherSize, b2Vec2(0.0f, -boxSize.y), 0.0f);
	top = body->CreateFixture(&fixtureDef);

	boundingBox.SetAsBox(topBottomWidth, otherSize, b2Vec2(0.0f, boxSize.y - otherSize), 0.0f);
	bottom = body->CreateFixture(&fixtureDef);

	boundingBox.SetAsBox(otherSize, leftRightHeight, b2Vec2(-boxSize.x, 0.0f), 0.0f);
	left = body->CreateFixture(&fixtureDef);

	boundingBox.SetAsBox(otherSize, leftRightHeight, b2Vec2(boxSize.x - otherSize, 0.0f), 0.0f);
	right = body->CreateFixture(&fixtureDef);
}