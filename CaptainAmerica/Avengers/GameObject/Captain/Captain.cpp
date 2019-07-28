#include "Captain.h"

vector<Animation *> Captain::animations = vector<Animation *>();
Captain * Captain::__instance = NULL;

Captain * Captain::GetInstance()
{
	if (__instance == NULL)
		__instance = new Captain();
	return __instance;
}

Captain::Captain()
{
	LoadResources();

	idleState = new CaptainState(this, eCaptainState::IDLE);
	walkState = new CaptainState(this, eCaptainState::WALK);
	jumpState = new CaptainState(this, eCaptainState::JUMP);
	crouchState = new CaptainState(this, eCaptainState::CROUCH);
	throwShieldState = new CaptainState(this, eCaptainState::THROW_SHIELD);
	rollState = new CaptainState(this, eCaptainState::ROLL);
	kickState = new CaptainState(this, eCaptainState::KICK);
	standHitState = new CaptainState(this, eCaptainState::STAND_HIT);
	crouchHitState = new CaptainState(this, eCaptainState::CROUCH_HIT);
	sitOnShieldState = new CaptainState(this, eCaptainState::SIT_ON_SHIELD);
	swingState = new CaptainState(this, eCaptainState::SWING);
	wadeState = new CaptainState(this, eCaptainState::WADE);
	shieldUpState = new CaptainState(this, eCaptainState::SHIELD_TOP);
	getHurtState = new CaptainState(this, eCaptainState::HURT);
	deadState = new CaptainState(this, eCaptainState::DEAD);
	dashState = new CaptainState(this, eCaptainState::DASH);
	diveState = new CaptainState(this, eCaptainState::DIVE);

	state = idleState;

	this->x = 500;
	this->y = 150;
	//this->x = 300;
	//this->y = 100;
	this->width = 25;
	this->height = 45;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = 25;
	collider.height = 45;

	shield = new Shield();
	enemy1 = new Enemy1();
	enemy2 = new Enemy2();
	enemy3 = new Enemy3();
}

void Captain::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\CharacterSprite.txt");
	Animation * anim;
	Sprite * sprite;

	// CAPTAIN_AMERICA_ANIMATION_IDLE
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::idle_start], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_WALK
	anim = new Animation(100);
	for (int i = NS::walk_start; i <= NS::walk_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_JUMP
	anim = new Animation(100);
	for (int i = NS::jump_start; i <= NS::jump_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::jump_end - 1], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::jump_end], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_CROUCH
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::crouch_start], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_THROW_SHIELD
	anim = new Animation(300);
	for (int i = NS::throw_shiled_start; i <= NS::throw_shield_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::throw_shield_end], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_ROLL
	anim = new Animation(300);
	for (int i = NS::roll_start; i <= NS::roll_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_KICK
	anim = new Animation(300);
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::kick_start], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_STAND_HIT
	anim = new Animation(300);
	for (int i = NS::stand_hit_start; i <= NS::stand_hit_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_CROUCH_HIT
	anim = new Animation(300);
	for (int i = NS::crouch_hit_start; i <= NS::crouch_hit_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_SIT_ON_SHIELD
	anim = new Animation(300);
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::sit_on_shiled_start], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_SWING
	anim = new Animation(300);
	for (int i = NS::swing_start; i <= NS::swing_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_WADE
	anim = new Animation(300);
	for (int i = NS::wade_start; i <= NS::wade_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_SHIELD_UP
	anim = new Animation(300);
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::shield_up_start], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_HURT
	anim = new Animation(300);
	sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[NS::hurt_start], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_DEAD
	anim = new Animation(300);
	for (int i = NS::dead_start; i <= NS::dead_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_DASH
	anim = new Animation(300);
	for (int i = NS::dash_start; i <= NS::dash_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// CAPTAIN_AMERICA_ANIMATION_DIVE
	anim = new Animation(300);
	for (int i = NS::dive_start; i <= NS::dive_end; i++)
	{
		sprite = new Sprite(CAPTAIN_AMERICA_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}
void Captain::SetState(eCaptainState state)
{
	switch (state)
	{
	case IDLE: this->state = this->GetIdleState();
		break;
	case WALK: this->state = this->GetWalkState();
		break;
	case JUMP: this->state = this->GetJumpState();
		break;
	case CROUCH:this->state = this->GetCrouchState();
		break;
	case THROW_SHIELD:this->state = this->GetThrowShieldState();
		break;
	case ROLL:this->state = this->GetRollState();
		break;
	case KICK:this->state = this->GetKickState();
		break;
	case STAND_HIT:this->state = this->GetStandHitState();
		break;
	case CROUCH_HIT:this->state = this->GetCrouchHitState();
		break;
	case SIT_ON_SHIELD:this->state = this->GetSitOnShieldState();
		break;
	case SWING:this->state = this->GetSwingState();
		break;
	case WADE:this->state = this->GetWadeState();
		break;
	case SHIELD_TOP:this->state = this->GetShieldUpState();
		break;
	case HURT:this->state = this->GetHurtState();
		break;
	case DEAD:this->state = this->GetDeadState();
		break;
	case DASH:this->state = this->GetDashState();
		break;
	case DIVE:this->state = this->GetDiveState();
		break;
	}
}

State * Captain::GetIdleState()
{
	this->SetEnumState(eCaptainState::IDLE);
	return idleState;
}

State * Captain::GetWalkState()
{
	this->SetEnumState(eCaptainState::WALK);
	return walkState;
}

State * Captain::GetJumpState()
{
	this->SetEnumState(eCaptainState::JUMP);
	return jumpState;
}

State * Captain::GetCrouchState()
{
	this->SetEnumState(eCaptainState::CROUCH);
	return crouchState;
}

State * Captain::GetThrowShieldState()
{
	this->SetEnumState(eCaptainState::THROW_SHIELD);
	return throwShieldState;
}

State * Captain::GetRollState()
{
	this->SetEnumState(eCaptainState::ROLL);
	return rollState;
}

State * Captain::GetKickState()
{
	this->SetEnumState(eCaptainState::KICK);
	return kickState;
}

State * Captain::GetStandHitState()
{
	this->SetEnumState(eCaptainState::STAND_HIT);
	return standHitState;
}

State * Captain::GetCrouchHitState()
{
	this->SetEnumState(eCaptainState::CROUCH_HIT);
	return crouchHitState;
}

State * Captain::GetSitOnShieldState()
{
	this->SetEnumState(eCaptainState::SIT_ON_SHIELD);
	return sitOnShieldState;
}

State * Captain::GetSwingState()
{
	this->SetEnumState(eCaptainState::SWING);
	return swingState;
}

State * Captain::GetWadeState()
{
	this->SetEnumState(eCaptainState::WADE);
	return wadeState;
}

State * Captain::GetShieldUpState()
{
	this->SetEnumState(eCaptainState::SHIELD_TOP);
	return shieldUpState;
}

State * Captain::GetHurtState()
{
	this->SetEnumState(eCaptainState::HURT);
	return getHurtState;
}

State * Captain::GetDeadState()
{
	this->SetEnumState(eCaptainState::DEAD);
	return deadState;
}

State * Captain::GetDashState()
{
	this->SetEnumState(eCaptainState::DASH);
	return dashState;
}

State * Captain::GetDiveState()
{
	this->SetEnumState(eCaptainState::DIVE);
	return diveState;
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
	this->SetPositionX(300);
	this->SetPositionY(100);
	Camera::GetInstance()->Reset();
}
void Captain::Update(DWORD dt)
{
	if (this->GetPositionX() < 0)
	{
		this->SetPositionX(0);
	}
	state->Update(dt);
	shield->Update(dt);
	enemy1->Update(dt);
	enemy2->Update(dt);
	enemy3->Update(dt);
}
void Captain::Render()
{
	state->Render();
	shield->Render();
	enemy1->Render();
	enemy2->Render();
	enemy3->Render();
}