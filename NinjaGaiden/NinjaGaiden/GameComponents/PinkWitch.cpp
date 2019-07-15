#include "PinkWitch.h"
#include "PinkWitchState.h"

PinkWitch::PinkWitch()
{
	LoadResources();

	idleState = new PinkWitchState(this, PINK_WITCH_ANI_IDLE);
	walkingState = new PinkWitchState(this, PINK_WITCH_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = -0.075f;
	this->SetPositionX(450);
	this->SetPositionY(65);

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = PINK_WITCH_SPRITE_WIDTH;
	collider.height = PINK_WITCH_SPRITE_HEIGHT - 10;

	Type = EnemyType::PINKWITCH;
}

PinkWitch::PinkWitch(float posx , float posy)
{
	LoadResources();

	idleState = new PinkWitchState(this, PINK_WITCH_ANI_IDLE);
	walkingState = new PinkWitchState(this, PINK_WITCH_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = -0.075f;
	this->SetPositionX(posx);
	this->SetPositionY(posy);

	width = PINK_WITCH_SPRITE_WIDTH;
	height = PINK_WITCH_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = PINK_WITCH_SPRITE_WIDTH;
	collider.height = PINK_WITCH_SPRITE_HEIGHT - 5;

	Type = EnemyType::PINKWITCH;
}

void PinkWitch::LoadResources()
{
	// Enemy_ANI_IDLE
	Animation * anim = new Animation(200);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i %  PINK_WITCH_TEXTURE_COLUMNS) *  PINK_WITCH_SPRITE_WIDTH;
		rect.right = rect.left + PINK_WITCH_SPRITE_WIDTH;
		rect.top = (i / PINK_WITCH_TEXTURE_COLUMNS) *  PINK_WITCH_SPRITE_HEIGHT;
		rect.bottom = rect.top + PINK_WITCH_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(PINK_WITCH_TEXTURE_LOCATION, rect, PINK_WITCH_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
	// NINJA_ANI_WALKING
	anim = new Animation(300);
	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i == 1)
		{
			RECT rect;
			rect.left = (i %  PINK_WITCH_TEXTURE_COLUMNS) *  PINK_WITCH_SPRITE_WIDTH;
			rect.right = rect.left + PINK_WITCH_SPRITE_WIDTH + 8;
			rect.top = (i / PINK_WITCH_TEXTURE_COLUMNS) *  PINK_WITCH_SPRITE_HEIGHT;
			rect.bottom = rect.top + PINK_WITCH_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(PINK_WITCH_TEXTURE_LOCATION, rect, PINK_WITCH_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
		if (i == 2)
		{
			RECT rect;
			rect.left = (i %  PINK_WITCH_TEXTURE_COLUMNS) *  PINK_WITCH_SPRITE_WIDTH+6;
			rect.right = rect.left + PINK_WITCH_SPRITE_WIDTH +8;
			rect.top = (i / PINK_WITCH_TEXTURE_COLUMNS) *  PINK_WITCH_SPRITE_HEIGHT;
			rect.bottom = rect.top + PINK_WITCH_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(PINK_WITCH_TEXTURE_LOCATION, rect, PINK_WITCH_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	this->animations.push_back(anim);
}

void PinkWitch::Idle()
{
	state->Idle();
}
void PinkWitch::Walk()
{
	state->Walk();
}
void PinkWitch::Update(DWORD dt)
{
	state->Update(dt);
}

void PinkWitch::Render()
{
	state->Render();
}