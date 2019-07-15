#include "RedBird.h"
#include "RedBirdState.h"

RedBird::RedBird()
{
	LoadResources();

	idleState = new RedBirdState(this, RED_BIRD_ANI_IDLE);
	walkingState = new RedBirdState(this, RED_BIRD_ANI_WALKING);
	state = walkingState;

	this->isLeft = false;
	this->vx = 0;
	this->SetPositionX(350);
	this->SetPositionY(90);

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = RED_BIRD_SPRITE_WIDTH;
	collider.height = RED_BIRD_SPRITE_HEIGHT;

	Type = EnemyType::REDBIRD;
}
RedBird::RedBird(float posx , float posy)
{
	LoadResources();

	idleState = new RedBirdState(this, RED_BIRD_ANI_IDLE);
	walkingState = new RedBirdState(this, RED_BIRD_ANI_WALKING);
	state = walkingState;

	this->isLeft = false;
	this->vx = 0;
	this->SetPositionX(posx);
	this->SetPositionY(posy);

	width = RED_BIRD_SPRITE_WIDTH;
	height = RED_BIRD_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = RED_BIRD_SPRITE_WIDTH;
	collider.height = RED_BIRD_SPRITE_HEIGHT;

	Type = EnemyType::REDBIRD;
}
void RedBird::LoadResources()
{
	// Enemy_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % RED_BIRD_TEXTURE_COLUMNS) * RED_BIRD_SPRITE_WIDTH;
		rect.right = rect.left + RED_BIRD_SPRITE_WIDTH;
		rect.top = (i / RED_BIRD_TEXTURE_COLUMNS) * RED_BIRD_SPRITE_HEIGHT;
		rect.bottom = rect.top + RED_BIRD_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(RED_BIRD_TEXTURE_LOCATION, rect, RED_BIRD_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
	// NINJA_ANI_WALKING
	anim = new Animation(200);
	for (int i = 0; i < 2; i++)
	{
		RECT rect;
		rect.left = (i % RED_BIRD_TEXTURE_COLUMNS) * RED_BIRD_SPRITE_WIDTH;
		rect.right = rect.left + RED_BIRD_SPRITE_WIDTH;
		rect.top = (i / RED_BIRD_TEXTURE_COLUMNS) * RED_BIRD_SPRITE_HEIGHT;
		rect.bottom = rect.top + RED_BIRD_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(RED_BIRD_TEXTURE_LOCATION, rect, RED_BIRD_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
}

void RedBird::Idle()
{
	state->Idle();
}
void RedBird::Walk()
{
	state->Walk();
}

void RedBird::Update(DWORD dt)
{
	state->Update(dt);
}
void RedBird::Render()
{
	state->Render();
}