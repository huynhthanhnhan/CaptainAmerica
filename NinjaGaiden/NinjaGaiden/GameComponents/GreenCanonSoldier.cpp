#include "GreenCanonSoldier.h"
#include "GreenCanonSoldierState.h"
#include "Grid.h"

GreenCanonSoldier::GreenCanonSoldier()
{
	LoadResources();

	idleState = new GreenCanonSoldierState(this, GREEN_CANON_SOLDIER_ANI_IDLE);
	walkingState = new GreenCanonSoldierState(this, GREEN_CANON_SOLDIER_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = 0.0f;
	this->SetPositionX(270);
	this->SetPositionY(80);

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = GREEN_CANON_SOLDIER_SPRITE_WIDTH;
	collider.height = GREEN_CANON_SOLDIER_SPRITE_HEIGHT;

	Type = EnemyType::GREENCANONSOLDIER;
}
GreenCanonSoldier::GreenCanonSoldier(float posx, float posy)
{
	LoadResources();

	idleState = new GreenCanonSoldierState(this, GREEN_CANON_SOLDIER_ANI_IDLE);
	walkingState = new GreenCanonSoldierState(this, GREEN_CANON_SOLDIER_ANI_WALKING);
	state = walkingState;

	this->isLeft = true;
	this->vx = 0.0f;
	this->SetPositionX(posx);
	this->SetPositionY(posy);

	width = GREEN_CANON_SOLDIER_SPRITE_WIDTH;
	height = GREEN_CANON_SOLDIER_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = GREEN_CANON_SOLDIER_SPRITE_WIDTH;
	collider.height = GREEN_CANON_SOLDIER_SPRITE_HEIGHT;

	Type = EnemyType::GREENCANONSOLDIER;

	//bullet = new GreenCannonSoldierBullet(this);
}
void GreenCanonSoldier::LoadResources()
{
	// Enemy_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % GREEN_CANON_SOLDIER_TEXTURE_COLUMNS) * GREEN_CANON_SOLDIER_SPRITE_WIDTH;
		rect.right = rect.left + GREEN_CANON_SOLDIER_SPRITE_WIDTH;
		rect.top = (i / GREEN_CANON_SOLDIER_TEXTURE_COLUMNS) * GREEN_CANON_SOLDIER_SPRITE_HEIGHT;
		rect.bottom = rect.top + GREEN_CANON_SOLDIER_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(GREEN_CANON_SOLDIER_TEXTURE_LOCATION, rect, GREEN_CANON_SOLDIER_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
	// NINJA_ANI_WALKING
	anim = new Animation(200);
	for (int i = 0; i < 2; i++)
	{
		RECT rect;
		rect.left = (i % GREEN_CANON_SOLDIER_TEXTURE_COLUMNS) * GREEN_CANON_SOLDIER_SPRITE_WIDTH;
		rect.right = rect.left + GREEN_CANON_SOLDIER_SPRITE_WIDTH;
		rect.top = (i / GREEN_CANON_SOLDIER_TEXTURE_COLUMNS) * GREEN_CANON_SOLDIER_SPRITE_HEIGHT;
		rect.bottom = rect.top + GREEN_CANON_SOLDIER_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(GREEN_CANON_SOLDIER_TEXTURE_LOCATION, rect, GREEN_CANON_SOLDIER_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	this->animations.push_back(anim);
}

void GreenCanonSoldier::Idle()
{
	state->Idle();
}
void GreenCanonSoldier::Walk()
{
	state->Walk();
}
//Hàm c?p nh?t
void GreenCanonSoldier::Update(DWORD dt)
{
	//bullet->Update(dt);
	state->Update(dt);
}
//Hàm render
void GreenCanonSoldier::Render()
{
	//bullet->Render();
	state->Render();
}