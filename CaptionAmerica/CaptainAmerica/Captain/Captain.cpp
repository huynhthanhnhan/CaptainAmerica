#include "Captain.h"

vector<Animation *> Captain::animations = vector<Animation *>();
Captain * Captain::__instance = NULL;

Captain::Captain()
{
	LoadResources();

	idleState = new CaptainState(this, CAPTAIN_ANI_IDLE);
	walkingState = new CaptainState(this, CAPTAIN_ANI_WALKING);
	jumpingState = new CaptainState(this, CAPTAIN_ANI_JUMPING);
	crouchingState = new CaptainState(this, CAPTAIN_ANI_CROUCHING);

	state = idleState;

	this->x = 100;
	this->y = 100;
	this->width = 25;
	this->height = 45;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;

	stamina = 100;

	/*  // Throw a lot of suriken
		Shurikens.push_back(new Shuriken());
		Shurikens.push_back(new Shuriken());
		Shurikens.push_back(new Shuriken());
		Shurikens.push_back(new Shuriken());*/
}
Captain * Captain::GetInstance()
{
	if (__instance == NULL)
		__instance = new Captain();
	return __instance;
}
void Captain::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"CharacterSprite.txt");
	// CAPTAIN_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		//this->SetColliderDemension(listSprite[i].right - listSprite[i].left, listSprite[i].bottom - listSprite[i].top);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_WALKING
	anim = new Animation(100);
	for (int i = 1; i < 5; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}

	animations.push_back(anim);

	// NINJA_ANI_JUMPING
	anim = new Animation(100);
	for (int i = 7; i < 8; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// NINJA_ANI_CROUCHING
	anim = new Animation(100);
	for (int i = 19; i < 20; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}
void Captain::SetState(State * state)
{
	this->state = state;
}
State * Captain::GetIdleState()
{
	return idleState;
}
State * Captain::GetWalkingState()
{
	return walkingState;
}
State * Captain::GetCrouchingState()
{
	return crouchingState;
}
State * Captain::GetJumpingState()
{
	return jumpingState;
}
void Captain::Idle()
{
	state->Idle();
}
void Captain::Walk()
{
	state->Walk();
}
void Captain::Jump()
{
	state->Jump();
}
void Captain::Crouch()
{
	state->Crouch();
}
void Captain::TurnLeft()
{
	isLeft = true;
}
void Captain::TurnRight()
{
	isLeft = false;
}
void Captain::Reset()
{
	this->stamina = 100;
	this->SetPositionX(100);
	this->SetPositionY(100);
	Viewport::GetInstance()->Reset();
	//Hud::GetInstance()->Reset();
}
void Captain::Update(DWORD dt)
{
	if (Game::GetInstance()->GetStage() == Stage::STAGE_31)
	{
		/*if (this->GetPositionX() >= 400 && this->GetPositionX() <= 450 && PantherAppear == false)
		{
			YellowPanther * enemy = new YellowPanther(220, 100);
			enemy->Setleft(false);
			enemy->SetActive(true);
			Grid::GetInstance()->AddEnemy(enemy);
			PantherAppear = true;
		}*/
	}
	if (this->GetSpeedX() > 0 && this->GetPositionX() > Game::GetInstance()->GetTiledMap()->GetWidth() - CAPTAIN_SPRITE_WIDTH)
	{
		int map = (int)Game::GetInstance()->GetStage() + 1;
		if (map < 3)
		{
			Game::GetInstance()->SetStage(map);
			this->SetPositionX(0);
			if (STAGE_32 == Game::GetInstance()->GetStage())
			{
				Viewport::GetInstance()->Reset();
				Game::GetInstance()->GetTiledMap()->ResetTiledMap();
				Game::GetInstance()->SetTileMap(TiledMap::GetInstance(TILES_MATRIX_STAGE_32));
				Grid::SetNewGrid();
				//Hud::GetInstance()->Reset();
				Game::GetInstance()->SetGrid(Grid::GetInstance());
				this->SetSpeedY(0.0f);
			}
			else if (STAGE_BOSS == Game::GetInstance()->GetStage())
			{
				Viewport::GetInstance()->Reset();
				Game::GetInstance()->GetTiledMap()->ResetTiledMap();
				Game::GetInstance()->SetTileMap(TiledMap::GetInstance(TILES_MATRIX_STAGE_BOSS));
				Grid::SetNewGrid();
				//Hud::GetInstance()->Reset();
				Game::GetInstance()->SetGrid(Grid::GetInstance());
				this->SetPositionX(100);
				this->SetSpeedY(0.0f);
			}
		}
		else if (STAGE_BOSS == Game::GetInstance()->GetStage())
		{
			this->SetPositionX(Game::GetInstance()->GetTiledMap()->GetWidth() - CAPTAIN_SPRITE_WIDTH);
		}
	}
	if (this->GetSpeedX() < 0 && this->GetPositionX() < 0)
	{
		this->SetPositionX(0);
	}
	state->Update(dt);
}
void Captain::Render()
{
	state->Render();
}