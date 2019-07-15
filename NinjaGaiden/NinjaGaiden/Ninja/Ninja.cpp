#include "Ninja.h"
#include "HealthItem.h"
#include "SpiritPointBlue.h"

vector<Animation *> Ninja::animations = vector<Animation *>();
Ninja * Ninja::__instance = NULL;

Ninja::Ninja()
{
	LoadResources();

	idleState = new NinjaSate(this, NINJA_ANI_IDLE);
	walkingState = new NinjaSate(this, NINJA_ANI_WALKING);
	attackingState = new NinjaSate(this, NINJA_ANI_STANDING_ATTACKING);
	jumpingState = new NinjaSate(this, NINJA_ANI_JUMPING);
	crouchingState = new NinjaSate(this, NINJA_ANI_CROUCHING);
	climbState = new NinjaSate(this, NINJA_ANI_CLIMBING);
	jumpattackingState = new NinjaSate(this, NINJA_ANI_JUMPING_ATTACKING);
	jumpattackedState = new NinjaSate(this, NINJA_ANI_JUMPING_ATTACKED);
	throwingState = new NinjaSate(this, NINJA_ANI_THROWING);

	state = idleState;

	this->x = 100;
	this->y = 100;
	this->width = NINJA_SPRITE_WIDTH;
	this->height = NINJA_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;

	stamina = 100;

	isUntouchable = false;
	UntouchableTime = 2000;

/*  // Ném nhiều phi tiêu
	Shurikens.push_back(new Shuriken());
	Shurikens.push_back(new Shuriken());
	Shurikens.push_back(new Shuriken());
	Shurikens.push_back(new Shuriken());*/
}
Ninja * Ninja::GetInstance()
{
	if (__instance == NULL)
		__instance = new Ninja();
	return __instance;
}
void Ninja::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Ninja\\CharacterSprite.txt");
	// NINJA_ANI_IDLE
 	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, listSprite[i], D3DCOLOR_XRGB(0, 168, 80, 1));
		//this->SetColliderDemension(listSprite[i].right - listSprite[i].left, listSprite[i].bottom - listSprite[i].top);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// NINJA_ANI_WALKING
	anim = new Animation(100);
	for (int i = 1; i < 5; i++)
	{
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, listSprite[i], NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	
	animations.push_back(anim);

	// NINJA_ANI_STANDING_ATTACK
	anim = new Animation(100);
	for (int i = 10; i < 15; i++)
	{
		if (10 == i)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
		else if (11 == i || 13 == i)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH * 2;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	animations.push_back(anim);

	// NINJA_ANI_CROUCHING_ATTACKING
	anim = new Animation(100);
	for (int i = 25; i < 30; i++)
	{
		if (25 == i)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
		else if (26 == i || 28 == i)
		{
			RECT rect;
			rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
			rect.right = rect.left + NINJA_SPRITE_WIDTH * 2;
			rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
			rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
			Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

			anim->AddFrame(sprite);
		}
	}
	animations.push_back(anim);

	// NINJA_ANI_JUMPING
	anim = new Animation(100);
	for (int i = 7; i < 8; i++)
	{
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, listSprite[i], D3DCOLOR_XRGB(0, 168, 80, 1));
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// NINJA_ANI_CROUCHING
	anim = new Animation(100);
	for (int i = 19; i < 20; i++)
	{
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, listSprite[i], D3DCOLOR_XRGB(0, 168, 80, 1));

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// NINJA_ANI_CLIMBING
	anim = new Animation(200);
	for (int i = 4; i < 6; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	// NINJA_ANI_JUMPING_ATTACKING
	anim = new Animation(70);
	RECT rect;
	rect.left = (7 % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
	rect.right = rect.left + NINJA_SPRITE_WIDTH;
	rect.top = (7 / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
	rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
	Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

	anim->AddFrame(sprite);

	for (int i = 16; i < 20; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}

	rect.left = (9 % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
	rect.right = rect.left + NINJA_SPRITE_WIDTH;
	rect.top = (9 / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
	rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
	sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

	anim->AddFrame(sprite);

	animations.push_back(anim);

	// NINJA_ANI_JUMPING_ATTACKED
	anim = new Animation(100);
	for (int i = 6; i < 7; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;
		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	anim = new Animation(100);
	for (int i = 20; i < 23; i++)
	{
		RECT rect;
		rect.left = (i % NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_WIDTH;
		rect.right = rect.left + NINJA_SPRITE_WIDTH;

		if (22 == i)
		{
			rect.right = rect.left + NINJA_SPRITE_WIDTH + 5;
		}

		rect.top = (i / NINJA_TEXTURE_COLUMNS) * NINJA_SPRITE_HEIGHT;
		rect.bottom = rect.top + NINJA_SPRITE_HEIGHT;
		Sprite * sprite = new Sprite(NINJA_TEXTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}
void Ninja::SetState(State * state)
{
	this->state = state;
}
State * Ninja::GetIdleState()
{
	return idleState;
}
State * Ninja::GetAttackedState()
{
	return jumpattackedState;
}
State * Ninja::GetThrowingState()
{
	return this->throwingState;;
}
State * Ninja::GetWalkingState()
{
	return walkingState;
}
State * Ninja::GetAttackingState()
{
	return attackingState;
}
State * Ninja::GetCrouchingState()
{
	return crouchingState;
}
State * Ninja::GetJumpingState()
{
	return jumpingState;
}
State * Ninja::GetClimbState()
{
	return climbState;
}

State * Ninja::GetJumpAttackState()
{
	return this->jumpattackingState;
}

void Ninja::Idle()
{
	state->Idle();
}
void Ninja::Attack()
{
	state->Attack();
}
void Ninja::Walk()
{
	state->Walk();
}
void Ninja::Jump()
{
	state->Jump();
}
void Ninja::Crouch()
{
	state->Crouch();
}
void Ninja::Climb()
{
	state->Climb();
}
void Ninja::JumpAttack()
{
	state->JumpAttack();
}
void Ninja::Attacked()
{
	state->Attacked();
}
void Ninja::TurnLeft()
{
	isLeft = true;
}
void Ninja::TurnRight()
{
	isLeft = false;
}
void Ninja::SetUntouchableTime(int value)
{
	UntouchableTime = value;
}
void Ninja::DescreaseShuriken()
{
	this->Shurikens.erase(Shurikens.begin());
}
void Ninja::Reset()
{
	this->stamina = 100;
	this->SetPositionX(100);
	this->SetPositionY(100);
	Viewport::GetInstance()->Reset();
	Hud::GetInstance()->Reset();
}
void Ninja::CreateThrownWeapon()
{
	this->SetState(GetThrowingState());
}
bool PantherAppear = false;
void Ninja::Additem(GameItem * gameitem)
{
	bool addItem = false;
	switch (gameitem->GetItemType())
	{
	case Item::FLAMES:
	{
		addItem = true;
		ninja_item = Item::FLAMES;
		break;
	}
	case Item::WINDMILLSTAR:
	{
		addItem = true;
		ninja_item = Item::WINDMILLSTAR;
		break;
	}
	case Item::FIREWHEELS:
	{
		addItem = true;
		break;
	}
	case Item::SPIRITPOINTBLUE:
	{
		addItem = true;
		support_item = Item::SPIRITPOINTBLUE;
		if (this->stamina < 100)
		{
			int heathpoint = ((SpiritPointBlue*)gameitem)->GetHeathPoint();
			this->stamina += heathpoint;
		}
		if (this->stamina > 100) this->stamina = 100;
		break;
	}
	case Item::SPIRITPOINTRED:
	{
		addItem = true;
		support_item = Item::SPIRITPOINTRED;
		break;
	}
	case Item::TIMEFREEZE:
	{
		addItem = true;
		break;
	}
	case Item::THROWINGSTAR:
	{
		addItem = true;
		ninja_item = Item::THROWINGSTAR;
		Shurikens.push_back(new Shuriken());
		break;
	}
	case Item::BONUSPOINTBLUE:
	{
		addItem = true;
		break;
	}
	case Item::BONUSPOINTRED:
	{
		addItem = true;
		break;
	}
	case Item::HEALTHITEM:
	{
		addItem = true;

		break;
	}
	default:
		break;
	}
	if (addItem == true)
	{
		int gameitemindex = Grid::GetInstance()->GetGameItemIndexById(gameitem->GetId());
		Grid::GetInstance()->DeleteGameItem(gameitemindex);
	}
}
void Ninja::Update(DWORD dt)
{
	if (Game::GetInstance()->GetStage() == Stage::STAGE_31)
	{
		if (this->GetPositionX() >= 400 && this->GetPositionX() <= 450 && PantherAppear == false)
		{
			YellowPanther * enemy = new YellowPanther(220, 100);
			enemy->Setleft(false);
			enemy->SetActive(true);
			Grid::GetInstance()->AddEnemy(enemy);
			PantherAppear = true;
		}
	}
	if (this->GetSpeedX() > 0 && this->GetPositionX() > Game::GetInstance()->GetTiledMap()->GetWidth() - NINJA_SPRITE_WIDTH)
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
				Hud::GetInstance()->Reset();
				Game::GetInstance()->SetGrid(Grid::GetInstance());
				this->SetSpeedY(0.0f);
			}
			else if (STAGE_BOSS == Game::GetInstance()->GetStage())
			{
				Viewport::GetInstance()->Reset();
				Game::GetInstance()->GetTiledMap()->ResetTiledMap();
				Game::GetInstance()->SetTileMap(TiledMap::GetInstance(TILES_MATRIX_STAGE_BOSS));
				Grid::SetNewGrid();
				Hud::GetInstance()->Reset();
				Game::GetInstance()->SetGrid(Grid::GetInstance());
				this->SetPositionX(100);
				this->SetSpeedY(0.0f);
			}
		}
		else if (STAGE_BOSS == Game::GetInstance()->GetStage())
		{
			this->SetPositionX(Game::GetInstance()->GetTiledMap()->GetWidth() - NINJA_SPRITE_WIDTH);
		}
	}
	if (this->GetSpeedX() < 0 && this->GetPositionX() < 0)
	{
		this->SetPositionX(0);
	}
	state->Update(dt);
}
void Ninja::Render()
{
	state->Render();
}