#include "Enemy3Bullet.h"

Enemy3Bullet::Enemy3Bullet(float posX, float posY, bool isRightToLeft)
{
	LoadResource();

	this->x = posX;
	this->y = posY;

	this->isRightToLeft = isRightToLeft;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = 7;
	collider.height = 7;

	this->countTimeLife = 0;
}

void Enemy3Bullet::LoadResource()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemy\\Enemies.txt");
	Animation * anim;
	Sprite * sprite;

	// IDLE
	anim = new Animation(100);
	sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[15], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[17], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animation.push_back(anim);
}
void Enemy3Bullet::Update(DWORD dt)
{
	this->timeLife++;
	if (countTimeLife >= timeLife)
	{
		delete this;
	}
	this->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X);
	if (isRightToLeft)
	{
		this->SetPositionX(this->GetPositionX() - this->GetSpeedX() * dt);
		this->isFlipped = false;
	}
	else
	{
		this->SetPositionX(this->GetPositionX() + this->GetSpeedX() * dt);
		this->isFlipped = true;

	}
}
void Enemy3Bullet::Render()
{
	SpriteData spriteEnemyData;
	if (this != NULL)
	{
		spriteEnemyData.width = 24;
		spriteEnemyData.height = 43;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();

		spriteEnemyData.isFlipped = isFlipped;
		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
	}
	this->GetAnimationList()[0]->Render(spriteEnemyData);
}

Enemy3Bullet::~Enemy3Bullet()
{
}