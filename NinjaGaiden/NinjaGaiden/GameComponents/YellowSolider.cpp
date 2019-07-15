#include "YellowSolider.h"
#include "YellowSoliderState.h"
#include "Grid.h"

YellowSolider::YellowSolider()
{
	LoadResources();

	idleState = new YellowSoliderState(this, YELLOW_SOLDIER_ANI_IDLE);
	walkingState = new YellowSoliderState(this, YELLOW_SOLDIER_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = -YELLOW_SOLDIER_WALKING_SPEED;

	this->width = YELLOW_SOLDIER_SPRITE_WIDTH;
	this->height = YELLOW_SOLDIER_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = YELLOW_SOLDIER_SPRITE_WIDTH;
	collider.height = YELLOW_SOLDIER_SPRITE_HEIGHT;

	Type = EnemyType::YELLOWSOLDIER;
}

YellowSolider::YellowSolider(float posx , float posy )
{
	LoadResources();

	idleState = new YellowSoliderState(this, YELLOW_SOLDIER_ANI_IDLE);
	walkingState = new YellowSoliderState(this, YELLOW_SOLDIER_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = -YELLOW_SOLDIER_WALKING_SPEED;
	this->SetPositionX(posx);
	this->SetPositionY(posy);

	this->width = YELLOW_SOLDIER_SPRITE_WIDTH;
	this->height = YELLOW_SOLDIER_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = YELLOW_SOLDIER_SPRITE_WIDTH;
	collider.height = YELLOW_SOLDIER_SPRITE_HEIGHT;

	Type = EnemyType::YELLOWSOLDIER;
}
void YellowSolider::LoadResources()
{
	// Enemy_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % YELLOW_SOLDIER_TEXTURE_COLUMNS) * YELLOW_SOLDIER_SPRITE_WIDTH;
		rect.right = rect.left + YELLOW_SOLDIER_SPRITE_WIDTH;
		rect.top = (i / YELLOW_SOLDIER_TEXTURE_COLUMNS) * YELLOW_SOLDIER_SPRITE_HEIGHT;
		rect.bottom = rect.top + YELLOW_SOLDIER_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(YELLOW_SOLDIER_TEXTURE_LOCATION, rect, YELLOW_SOLDIER_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
	// NINJA_ANI_WALKING
	anim = new Animation(250);
	for (int i = 0; i < 3; i++)
	{
		/*if (i == 0 || i== 1)
		{*/
			RECT rect;
			rect.left = (i % YELLOW_SOLDIER_TEXTURE_COLUMNS) * YELLOW_SOLDIER_SPRITE_WIDTH;
			rect.right = rect.left + YELLOW_SOLDIER_SPRITE_WIDTH;
			rect.top = (i / YELLOW_SOLDIER_TEXTURE_COLUMNS) * YELLOW_SOLDIER_SPRITE_HEIGHT;
			rect.bottom = rect.top + YELLOW_SOLDIER_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(YELLOW_SOLDIER_TEXTURE_LOCATION, rect, YELLOW_SOLDIER_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
	/*	}
		if (i == 2 )
		{*/
		/*	RECT rect;
			rect.left = (i % YELLOW_SOLDIER_TEXTURE_COLUMNS) * YELLOW_SOLDIER_SPRITE_WIDTH;
			rect.right = rect.left + YELLOW_SOLDIER_SPRITE_WIDTH*2;
			rect.top = (i / YELLOW_SOLDIER_TEXTURE_COLUMNS) * YELLOW_SOLDIER_SPRITE_HEIGHT;
			rect.bottom = rect.top + YELLOW_SOLDIER_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(YELLOW_SOLDIER_TEXTURE_LOCATION, rect, YELLOW_SOLDIER_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}*/
	}
	this->animations.push_back(anim);
}

void YellowSolider::Idle()
{
	state->Idle();
}
void YellowSolider::Walk()
{
	state->Walk();
}
//Hàm cập nhật
void YellowSolider::Update(DWORD dt)
{
	state->Update(dt);
	this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt));
	if (this->GetSpeedX() < 0 && this->GetPositionX() <= 50)
	{
		this->TurnRight();
	}
}
//Hàm render
void YellowSolider::Render()
{
	state->Render();
}