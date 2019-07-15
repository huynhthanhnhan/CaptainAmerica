#include "BossBullet.h"
#include "Ninja.h"

BossBullet::BossBullet(Enemy* enemy)
{
	LoadResources();

	this->enemy = enemy;

	this->x = enemy->GetPositionX();
	this->y = enemy->GetPositionY() - 10;

	width = BOSS_MAP_33_BULLET_WIDTH;
	height = BOSS_MAP_33_BULLET_HEIGHT;

	vx = -BOSS_MAP_33_BULLET_SPEED;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = 0;
	collider.width = BOSS_MAP_33_BULLET_WIDTH;
	collider.height = BOSS_MAP_33_BULLET_HEIGHT;

	isLeft = true;
	damage = 5;

	bullettype = BulletType::BOSS_BULLET;
}

void BossBullet::LoadResources()
{
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % SHURIKEN_TEXTURE_COLUMNS) * BOSS_MAP_33_BULLET_WIDTH;
		rect.right = rect.left + BOSS_MAP_33_BULLET_WIDTH;
		rect.top = (i / SHURIKEN_TEXTURE_COLUMNS) * BOSS_MAP_33_BULLET_HEIGHT;
		rect.bottom = rect.top + BOSS_MAP_33_BULLET_HEIGHT;
		Sprite * sprite = new Sprite(BOSS_MAP_33_BULLET, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void BossBullet::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
	{
		if (Boss::GetInstance()->GetCheckBullet())
		{
			this->Active = true;
		}
		else
		{
			Reset();
		}
		this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt*(isLeft == true ? 1 : -1)));
	}
	else
	{
		this->Active = false;
		Reset();
	}
}

void BossBullet::Render()
{
	if (Active == true)
	{
		SpriteData spriteEnemyData;

		spriteEnemyData.width = BOSS_MAP_33_BULLET_WIDTH;
		spriteEnemyData.height = BOSS_MAP_33_BULLET_HEIGHT + 10;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();

		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();

		this->animations[0]->Render(spriteEnemyData);
	}
}

void BossBullet::Reset()
{
	this->x = enemy->GetPositionX();
	this->y = this->GetPositionY();
	this->Active = false;
	Boss::GetInstance()->StopShootBullet();
}
BossBullet::~BossBullet()
{
}
