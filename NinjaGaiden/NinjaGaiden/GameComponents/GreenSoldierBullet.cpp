#include "GreenSoldierBullet.h"
#include "Ninja.h"

GreenSoldierBullet::GreenSoldierBullet(Enemy* enemy)
{
	LoadResources();

	this->enemy = enemy;

	this->x = enemy->GetPositionX();
	this->y = enemy->GetPositionY() - 10;

	width = GREEN_SOLDIER_BULLET_WIDTH;
	height = GREEN_SOLDIER_BULLET_HEIGHT;

	vx = -GREEN_SOLDIER_BULLET_SPEED;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = 0;
	collider.width = GREEN_SOLDIER_BULLET_WIDTH;
	collider.height = GREEN_SOLDIER_BULLET_HEIGHT;

	isLeft = true;
	damage = 5;
}

void GreenSoldierBullet::LoadResources()
{
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % SHURIKEN_TEXTURE_COLUMNS) * GREEN_SOLDIER_BULLET_WIDTH;
		rect.right = rect.left + GREEN_SOLDIER_BULLET_WIDTH;
		rect.top = (i / SHURIKEN_TEXTURE_COLUMNS) * GREEN_SOLDIER_BULLET_HEIGHT;
		rect.bottom = rect.top + GREEN_SOLDIER_BULLET_HEIGHT;
		Sprite * sprite = new Sprite(GREEN_SOLDIER_BULLET, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void GreenSoldierBullet::Update(DWORD dt)
{
	shootTime += dt;
	if (shootTime >= 3000)
	{
		if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
		{
			this->Active = true;
			if (abs(distance) >= 50)
			{
				Reset();
			}
			else
			{
				this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt));
				distance += vx * dt;
			}
		}
		else
		{
			this->Active = false;
			Reset();
		}
	}
}

void GreenSoldierBullet::Render()
{
	if (Active == true)
	{
		SpriteData spriteEnemyData;

		spriteEnemyData.width = GREEN_SOLDIER_BULLET_WIDTH;
		spriteEnemyData.height = GREEN_SOLDIER_BULLET_HEIGHT + 10;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();

		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();

		this->animations[0]->Render(spriteEnemyData);
	}
}

void GreenSoldierBullet::Reset()
{
	//Grid::GetInstance()->DeleteBullet(enemy);
	this->x = enemy->GetPositionX();
	this->y = enemy->GetPositionY() - 10;
	this->Active = false;
	distance = 0;
	shootTime = 0;
}


GreenSoldierBullet::~GreenSoldierBullet()
{
}
