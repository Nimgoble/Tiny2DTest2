#include "Player.h"

using namespace Tiny2D;

Player::Player() :
	facingLeft(false),
	currentAnimation("idle"),
	isJumping(false),
	canJump(false),
	jumped(false),
	onGround(false),
	wallSliding(false),
	teleporting(false)
{
}

Player::Player(const T2DTVec2D& position) :
	facingLeft(false),
	currentAnimation("idle"),
	isJumping(false),
	canJump(false),
	jumped(false),
	onGround(false),
	wallSliding(false),
	teleporting(false)
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

	font.Create("common/courbd.ttf", 28, Font::Flags_Italic, false);
}

void Player::OnUpdate(float deltaTime)
{
	CheckMovement();
	UpdateAnimation();
	//TODO: Clean up UpdateAnimation() and add this to that.
	megaManSprite.Update(deltaTime);
}

void Player::OnDraw(Tiny2D::Texture& renderTarget)
{
	Sprite::DrawParams params;
	params.position = T2DTVec2D::FromBox2DVec(body->GetPosition());//position;
	params.flipX = facingLeft;
	//params.scale = 1.5f;//...maybe?
	params.centered = true;

	megaManSprite.Draw(&params);

	font.Draw(megaManSprite.GetCurrentAnimation().c_str(), Vec2(400.f, 50.0f));
}

void Player::OnCollision(b2Fixture *ourFixture, SceneObject *other)
{
	if(bottom.touching && teleporting)
		teleporting = false;

	onGround = bottom.touching;
	canJump = true;
	isJumping = false;

	wallSliding =
	(
		(left.touching || right.touching) &&
		!onGround &&
		body->GetLinearVelocity().y > 0
	);
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
	fixtureDef.userData = &top.touching;
	top.fixture = body->CreateFixture(&fixtureDef);

	boundingBox.SetAsBox(topBottomWidth, otherSize, b2Vec2(0.0f, boxSize.y - otherSize), 0.0f);
	fixtureDef.userData = &bottom.touching;
	bottom.fixture = body->CreateFixture(&fixtureDef);

	boundingBox.SetAsBox(otherSize, leftRightHeight, b2Vec2(-boxSize.x, 0.0f), 0.0f);
	fixtureDef.userData = &left.touching;
	left.fixture = body->CreateFixture(&fixtureDef);

	boundingBox.SetAsBox(otherSize, leftRightHeight, b2Vec2(boxSize.x - otherSize, 0.0f), 0.0f);
	fixtureDef.userData = &right.touching;
	right.fixture = body->CreateFixture(&fixtureDef);
}

void Player::TeleportToGround()
{
	teleporting = true;
	currentAnimation = "teleportStart";
	megaManSprite.PlayAnimation(currentAnimation, Sprite::AnimationMode_OnceAndFreeze);
}

void Player::CheckMovement()
{
	if(teleporting)
		return;

	const float speed = 5.0f;
	previousVelocity = body->GetLinearVelocity(); 
	b2Vec2 velocity = previousVelocity;
	if (Input::IsKeyDown(Input::Key_Left))
	{
		velocity.x = -speed;
		//position.x -= deltaTime * speed;
		facingLeft = true;
	}
	else if (Input::IsKeyDown(Input::Key_Right))
	{
		velocity.x = speed;
		facingLeft = false;
	}
	else 
	{
		wallSliding = false;
		velocity.x = 0.0f;
	}


	if(Input::IsKeyDown(Input::Key_Up) && isJumping == false)
	{
		if(currentAnimation == "wallSlide" || !onGround)
		{
			velocity.x = 50 * ((facingLeft) ? 1.0f : -1.0f);
			wallSliding = false;
		}

		velocity.y = -25;
		isJumping = true;
		onGround = false;
	}

	body->SetGravityScale((wallSliding) ? 1.5f : 10.0f);
	body->SetLinearVelocity(velocity);
}

void Player::UpdateAnimation()
{
	if(currentAnimation == "teleportStart")
	{
		if(teleporting)
			return;
		else
		{
			currentAnimation = "teleportFinish";
			megaManSprite.PlayAnimation(currentAnimation, Sprite::AnimationMode_Once);
		}
	}
	else if(currentAnimation == "teleportFinish")
		return;

	b2Vec2 currentVelocity = body->GetLinearVelocity();
	std::string nextAnimation = currentAnimation;

	if(wallSliding)
		nextAnimation = "wallSlide";
	else if(currentVelocity.y != 0 || isJumping)
	{
		//If we've jumped and our jump animation is done playing and we're falling
        //Play the in-air animation
		if(currentAnimation == "jumpStart" && CurrentAnimationDone() && currentVelocity.y >= 0)
			nextAnimation = "jumpInAir";
		else if(currentVelocity.y < 0 && currentAnimation != "jumpStart")
			nextAnimation = "jumpStart"; //if we're going up and our animation isn't jump and we jumped
		else if(isJumping == false)
			nextAnimation = "jumpInAir"; //Regular falling animation goes here.
	}
	else if(currentVelocity.x != 0 && !isJumping)
	{
		if(currentAnimation != "jumpFinish" || (currentAnimation == "jumpFinish" && CurrentAnimationDone()))
			currentAnimation = "run";
	}
	else
		nextAnimation = "idle";

	//If we JUST got done jumping/falling: play the jumpFinish animation
	if(currentVelocity.y == 0 && previousVelocity.y != 0)
		nextAnimation = "jumpFinish";

	if(currentVelocity.x > 0 && facingLeft)
		facingLeft = false;
	else if(currentVelocity.x < 0 && !facingLeft)
		facingLeft = true;

	if(nextAnimation != megaManSprite.GetCurrentAnimation())
	{
		megaManSprite.PlayAnimation(nextAnimation);
		currentAnimation = nextAnimation;
	}
}

bool Player::CurrentAnimationDone()
{
	return megaManSprite.GetCurrentAnimation() != currentAnimation;
}