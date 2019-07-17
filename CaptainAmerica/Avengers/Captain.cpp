#include "Captain.h"

vector<Animation *> Captain::animations = vector<Animation *>();
Captain * Captain::__instance = NULL;

Captain::Captain()
{
	LoadResources();

	idleState = new CaptainState(this, CAPTAIN_ANI_IDLE);
	walkState = new CaptainState(this, CAPTAIN_ANI_WALK);
	jumpState = new CaptainState(this, CAPTAIN_ANI_JUMP);
	crouchState = new CaptainState(this, CAPTAIN_ANI_CROUCH);
	throwShieldState = new CaptainState(this, CAPTAIN_ANI_THROW_SHIELD);
	rollState = new CaptainState(this, CAPTAIN_ANI_ROLL);
	kickState = new CaptainState(this, CAPTAIN_ANI_KICK);
	standHitState = new CaptainState(this, CAPTAIN_ANI_STAND_HIT);
	crouchHitState = new CaptainState(this, CAPTAIN_ANI_CROUCH_HIT);
	sitOnShieldState = new CaptainState(this, CAPTAIN_ANI_SIT_ON_SHIELD);
	swingState = new CaptainState(this, CAPTAIN_ANI_SWING);
	wadeState = new CaptainState(this, CAPTAIN_ANI_WADE);
	shieldUpState = new CaptainState(this, CAPTAIN_ANI_SHIELD_UP);
	getHurtState = new CaptainState(this, CAPTAIN_ANI_GET_HURT);
	deadState = new CaptainState(this, CAPTAIN_ANI_DEAD);

	state = idleState;

	this->x = 300;
	this->y = 100;
	this->width = 25;
	this->height = 45;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;

	stamina = 100;

	shield = new Shield();

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
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_WALK
	anim = new Animation(100);
	for (int i = 1; i < 5; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_JUMP
	anim = new Animation(100);
	for (int i = 7; i < 8; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH
	anim = new Animation(100);
	for (int i = 6; i < 7; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_THROW_SHIELD
	anim = new Animation(300);
	for (int i = 11; i < 13; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_ROLL
	anim = new Animation(300);
	for (int i = 8; i < 10; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_KICK
	anim = new Animation(300);
	for (int i = 10; i < 11; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_STAND_HIT
	anim = new Animation(300);
	for (int i = 13; i < 15; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_CROUCH_HIT
	anim = new Animation(300);
	for (int i = 15; i < 17; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_SIT_ON_SHIELD
	anim = new Animation(300);
	for (int i = 19; i < 20; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_SWING
	anim = new Animation(300);
	for (int i = 27; i < 30; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_WADE
	anim = new Animation(300);
	for (int i = 44; i < 46; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_SHIELD_UP
	anim = new Animation(300);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_GET_HURT
	anim = new Animation(300);
	for (int i = 33; i < 34; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_ANI_DEAD
	anim = new Animation(300);
	for (int i = 34; i < 36; i++)
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
	this->SetStateNum(CAPTAIN_ANI_IDLE);
	return idleState;
}

State * Captain::GetWalkState()
{
	this->SetStateNum(CAPTAIN_ANI_WALK);
	return walkState;
}

State * Captain::GetJumpState()
{
	this->SetStateNum(CAPTAIN_ANI_JUMP);
	return jumpState;
}

State * Captain::GetCrouchState()
{
	this->SetStateNum(CAPTAIN_ANI_CROUCH);
	return crouchState;
}

State * Captain::GetThrowShieldState()
{
	this->SetStateNum(CAPTAIN_ANI_THROW_SHIELD);
	return throwShieldState;
}

State * Captain::GetRollState()
{
	return rollState;
}

State * Captain::GetKickState()
{
	return kickState;
}

State * Captain::GetStandHitState()
{
	return standHitState;
}

State * Captain::GetCrouchHitState()
{
	return crouchHitState;
}

State * Captain::GetSitOnShieldState()
{
	return sitOnShieldState;
}

State * Captain::GetSwingState()
{
	return swingState;
}

State * Captain::GetWadeState()
{
	return wadeState;
}

State * Captain::GetShieldUpState()
{
	return shieldUpState;
}

State * Captain::GetGetHurtState()
{
	return getHurtState;
}

State * Captain::GetDeadState()
{
	return deadState;
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

void Captain::ThrowShield()
{
	state->ThrowShield();
}

void Captain::Roll()
{
	state->Roll();
}

void Captain::Kick()
{
	state->Kick();
}

void Captain::StandHit()
{
	state->StandHit();
}

void Captain::CrouchHit()
{
	state->CrouchHit();
}

void Captain::SitOnShield()
{
	state->SitOnShield();
}

void Captain::Swing()
{
	state->Swing();
}

void Captain::Wade()
{
	state->Wade();
}

void Captain::ShieldUp()
{
	state->ShieldUp();
}

void Captain::GetHurt()
{
	state->GetHurt();
}

void Captain::Dead()
{
	state->Dead();
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
	this->stamina = 300;
	this->SetPositionX(300);
	this->SetPositionY(100);
	Viewport::GetInstance()->Reset();
	//Hud::GetInstance()->Reset();
}
void Captain::Update(DWORD dt)
{
	if (Game::GetInstance()->GetStage() == Stage::STAGE_1)
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
			if (STAGE_2 == Game::GetInstance()->GetStage())
			{
				Viewport::GetInstance()->Reset();
				Game::GetInstance()->GetTiledMap()->ResetTiledMap();
				Game::GetInstance()->SetTileMap(TiledMap::GetInstance(TILES_MATRIX_STAGE_2));
				Grid::SetNewGrid();
				//Hud::GetInstance()->Reset();
				Game::GetInstance()->SetGrid(Grid::GetInstance());
				this->SetSpeedY(0.0f);
			}
			else if (STAGE_BOSS_1 == Game::GetInstance()->GetStage())
			{
				Viewport::GetInstance()->Reset();
				Game::GetInstance()->GetTiledMap()->ResetTiledMap();
				Game::GetInstance()->SetTileMap(TiledMap::GetInstance(TILES_MATRIX_STAGE_BOSS_1));
				Grid::SetNewGrid();
				//Hud::GetInstance()->Reset();
				Game::GetInstance()->SetGrid(Grid::GetInstance());
				this->SetPositionX(100);
				this->SetSpeedY(0.0f);
			}
		}
		else if (STAGE_BOSS_1 == Game::GetInstance()->GetStage())
		{
			this->SetPositionX(Game::GetInstance()->GetTiledMap()->GetWidth() - CAPTAIN_SPRITE_WIDTH);
		}
	}
	if (this->GetSpeedX() < 0 && this->GetPositionX() < 0)
	{
		this->SetPositionX(0);
	}
	state->Update(dt);
	shield->Update(dt);
}
void Captain::Render()
{
	state->Render();
	shield->Render();
}