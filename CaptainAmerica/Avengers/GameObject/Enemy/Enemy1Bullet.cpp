#include "Enemy1Bullet.h"

Enemy1Bullet::Enemy1Bullet(float posX, float posY, bool isRightToLeft)
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

void Enemy1Bullet::LoadResource()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemy\\Enemies.txt");
	Animation * anim;
	Sprite * sprite;

	// IDLE
	anim = new Animation(100);
	sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[6], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animation.push_back(anim);
}
void Enemy1Bullet::Update(DWORD dt)
{
	this->timeLife++;
	if (countTimeLife >= timeLife)
	{
		delete this;
	}
	this->SetSpeedX(CAPTAIN_AMERICA_WALKING_SPEED_X);
	if(isRightToLeft)
		this->SetPositionX(this->GetPositionX() - this->GetSpeedX() * dt);
	else 
		this->SetPositionX(this->GetPositionX() + this->GetSpeedX() * dt);
}
void Enemy1Bullet::Render()
{
	SpriteData spriteEnemyData;
	if (this != NULL)
	{
		spriteEnemyData.width = 24;
		spriteEnemyData.height = 43;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();


		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
	}
	this->GetAnimationList()[0]->Render(spriteEnemyData);
}

Enemy1Bullet::~Enemy1Bullet()
{
}