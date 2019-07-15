#include "GreenSolider.h"
#include "GreenSoliderState.h"

GreenSolider::GreenSolider()
{
	LoadResources();

	idleState = new GreenSoliderState(this, GREEN_SOLDIER_ANI_IDLE);
	walkingState = new GreenSoliderState(this, GREEN_SOLDIER_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = 0.0f;
	this->SetPositionX(200);
	this->SetPositionY(100);

	Type = EnemyType::GREENSOLDIER;
}
GreenSolider::GreenSolider(float posx , float posy)
{
	LoadResources();

	idleState = new GreenSoliderState(this, GREEN_SOLDIER_ANI_IDLE);
	walkingState = new GreenSoliderState(this, GREEN_SOLDIER_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = -0.075f;
	this->SetPositionX(posx);
	this->SetPositionY(posy);

	width = GREEN_SOLDIER_SPRITE_WIDTH;
	height = GREEN_SOLDIER_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = GREEN_SOLDIER_SPRITE_WIDTH;
	collider.height = GREEN_SOLDIER_SPRITE_HEIGHT;

	Type = EnemyType::GREENSOLDIER;
}
void GreenSolider::LoadResources()
{
	// Enemy_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i %  GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_WIDTH;
		rect.right = rect.left + GREEN_SOLDIER_SPRITE_WIDTH;
		rect.top = (i / GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_HEIGHT;
		rect.bottom = rect.top + GREEN_SOLDIER_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(GREEN_SOLDIER_TEXTURE_LOCATION, rect, GREEN_SOLDIER_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
	// NINJA_ANI_WALKING
	anim = new Animation(200);
	for (int i = 0; i < 5; i++)
	{
		if (i == 0 || i == 1 )
		{
			RECT rect;
			rect.left = (i %  GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_WIDTH;
			rect.right = rect.left + GREEN_SOLDIER_SPRITE_WIDTH;
			rect.top = (i / GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_HEIGHT;
			rect.bottom = rect.top + GREEN_SOLDIER_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(GREEN_SOLDIER_TEXTURE_LOCATION, rect, GREEN_SOLDIER_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
		if (i == 3 )
		{
			RECT rect;
			rect.left = (i %  GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_WIDTH;
			rect.right = rect.left + GREEN_SOLDIER_SPRITE_WIDTH* 1.5;
			rect.top = (i / GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_HEIGHT;
			rect.bottom = rect.top + GREEN_SOLDIER_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(GREEN_SOLDIER_TEXTURE_LOCATION, rect, GREEN_SOLDIER_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
		if (i == 4)
		{
			RECT rect;
			rect.left = (i %  GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_WIDTH+6;
			rect.right = rect.left + GREEN_SOLDIER_SPRITE_WIDTH * 2;
			rect.top = (i / GREEN_SOLDIER_TEXTURE_COLUMNS) *  GREEN_SOLDIER_SPRITE_HEIGHT;
			rect.bottom = rect.top + GREEN_SOLDIER_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(GREEN_SOLDIER_TEXTURE_LOCATION, rect, GREEN_SOLDIER_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	this->animations.push_back(anim);
}

void GreenSolider::Idle()
{
	state->Idle();
}
void GreenSolider::Walk()
{
	state->Walk();
}
void GreenSolider::Update(DWORD dt)
{
	state->Update(dt);
	/*this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt));
	if (this->GetSpeedX() < 0 && this->GetPositionX() <= 0)
	{
		this->TurnRight();
	}*/
}
void GreenSolider::Render()
{
	state->Render();
}