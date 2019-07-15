#include "GreenCannonSoldierBullet.h"
#include "Ninja.h"

GreenCannonSoldierBullet::GreenCannonSoldierBullet(Enemy* enemy)
{
	LoadResources();

	this->enemy = enemy;

	this->x = enemy->GetPositionX();
	this->y = enemy->GetPositionY() - 10;

	width = GREEN_CANNON_SOLDIER_BULLET_WIDTH;
	height = GREEN_CANNON_SOLDIER_BULLET_HEIGHT;

	vx = -GREEN_CANNON_SOLDIER_BULLET_SPEED;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = 0;
	collider.width = GREEN_CANNON_SOLDIER_BULLET_WIDTH;
	collider.height = GREEN_CANNON_SOLDIER_BULLET_HEIGHT;

	isLeft = true;
	damage = 5;
}

void GreenCannonSoldierBullet::LoadResources()
{
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % SHURIKEN_TEXTURE_COLUMNS) * GREEN_CANNON_SOLDIER_BULLET_WIDTH;
		rect.right = rect.left + GREEN_CANNON_SOLDIER_BULLET_WIDTH;
		rect.top = (i / SHURIKEN_TEXTURE_COLUMNS) * GREEN_CANNON_SOLDIER_BULLET_HEIGHT;
		rect.bottom = rect.top + GREEN_CANNON_SOLDIER_BULLET_HEIGHT;
		Sprite * sprite = new Sprite(GREEN_CANNON_SOLDIER_BULLET, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void GreenCannonSoldierBullet::Update(DWORD dt)
{
	shootTime += dt;
	if (shootTime >= 2000)
	{
		if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
		{
			this->Active = true;
			this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt ));
		}
		else
		{
			this->Active = false;
			Reset();
		}
	}
}

void GreenCannonSoldierBullet::Render()
{
	if (Active == true)
	{
		SpriteData spriteEnemyData;

		spriteEnemyData.width = GREEN_CANNON_SOLDIER_BULLET_WIDTH;
		spriteEnemyData.height = GREEN_CANNON_SOLDIER_BULLET_HEIGHT + 10;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();

		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();

		this->animations[0]->Render(spriteEnemyData);
	}
}

void GreenCannonSoldierBullet::Reset()
{
	this->x = enemy->GetPositionX();
	this->y = enemy->GetPositionY() - 10;
	this->Active = false;
	shootTime = 0;
}


GreenCannonSoldierBullet::~GreenCannonSoldierBullet()
{
}
