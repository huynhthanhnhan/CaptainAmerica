#include "YellowPanther.h"
#include "YellowPantherState.h"

YellowPanther::YellowPanther()
{
	LoadResources();

	idleState = new YellowPantherState(this,  YELLOW_PANTHER_ANI_IDLE);
	walkingState = new YellowPantherState(this,  YELLOW_PANTHER_ANI_WALKING);
	state = walkingState;

	this->isLeft = false;
	this->vx = YELLOW_PANTHER_WALKING_SPEED;
	this->SetPositionX(350);
	this->SetPositionY(60);

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = YELLOW_PANTHER_SPRITE_WIDTH;
	collider.height = YELLOW_PANTHER_SPRITE_HEIGHT;

	Type = EnemyType::YELLOWPANTHER;
}
YellowPanther::YellowPanther(float posx , float posy)
{
	LoadResources();

	idleState = new YellowPantherState(this, YELLOW_PANTHER_ANI_IDLE);
	walkingState = new YellowPantherState(this, YELLOW_PANTHER_ANI_WALKING);
	state = walkingState;

	this->vx = YELLOW_PANTHER_WALKING_SPEED;

	this->SetPositionX(posx);
	this->SetPositionY(posy);

	width = YELLOW_PANTHER_SPRITE_WIDTH;
	height = YELLOW_PANTHER_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = YELLOW_PANTHER_SPRITE_WIDTH;
	collider.height = YELLOW_PANTHER_SPRITE_HEIGHT;

	Type = EnemyType::YELLOWPANTHER;
}
void YellowPanther::LoadResources()
{
	// Enemy_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i %  YELLOW_PANTHER_TEXTURE_COLUMNS) *  YELLOW_PANTHER_SPRITE_WIDTH;
		rect.right = rect.left +  YELLOW_PANTHER_SPRITE_WIDTH;
		rect.top = (i /  YELLOW_PANTHER_TEXTURE_COLUMNS) *  YELLOW_PANTHER_SPRITE_HEIGHT;
		rect.bottom = rect.top +  YELLOW_PANTHER_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite( YELLOW_PANTHER_TEXTURE_LOCATION, rect,  YELLOW_PANTHER_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
	// NINJA_ANI_WALKING
	anim = new Animation(100);
	for (int i = 0; i < 2; i++)
	{
		RECT rect;
		rect.left = (i %  YELLOW_PANTHER_TEXTURE_COLUMNS) *  YELLOW_PANTHER_SPRITE_WIDTH;
		rect.right = rect.left +  YELLOW_PANTHER_SPRITE_WIDTH;
		rect.top = (i /  YELLOW_PANTHER_TEXTURE_COLUMNS) *  YELLOW_PANTHER_SPRITE_HEIGHT;
		rect.bottom = rect.top +  YELLOW_PANTHER_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite( YELLOW_PANTHER_TEXTURE_LOCATION, rect,  YELLOW_PANTHER_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
}

void YellowPanther::Idle()
{
	state->Idle();
}
void YellowPanther::Walk()
{
	state->Walk();
}
//Hàm c?p nh?t
void YellowPanther::Update(DWORD dt)
{
	state->Update(dt);
	this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt));
}
//Hàm render
void YellowPanther::Render()
{
	state->Render();
}