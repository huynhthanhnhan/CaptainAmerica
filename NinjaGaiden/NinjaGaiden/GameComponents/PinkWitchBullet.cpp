#include "PinkWitchBullet.h"
#include "Ninja.h"

PinkWitchBullet::PinkWitchBullet(Enemy* enemy)
{
	LoadResources();

	this->enemy = enemy;

	this->x = enemy->GetPositionX();
	this->y = enemy->GetPositionY() - 10;

	width = PINK_WITCH_BULLET_WIDTH;
	height = PINK_WITCH_BULLET_HEIGHT;

	vx = -PINK_WITCH_BULLET_SPEED;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = 0;
	collider.width = PINK_WITCH_BULLET_WIDTH;
	collider.height = PINK_WITCH_BULLET_HEIGHT;

	isLeft = enemy->IsLeft();
	damage = 5;
}

void PinkWitchBullet::LoadResources()
{
	Animation * anim = new Animation(200);
	for (int i = 0; i < 4; i++)
	{
		RECT rect;
		rect.left = (i % 4) * PINK_WITCH_BULLET_WIDTH;
		rect.right = rect.left + PINK_WITCH_BULLET_WIDTH ;
		rect.top = (i / 4) * PINK_WITCH_BULLET_HEIGHT;
		rect.bottom = rect.top + PINK_WITCH_BULLET_HEIGHT;
		Sprite * sprite = new Sprite(PINK_WITCH_BULLET, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}
int getPt(int n1, int n2, float perc)
{
	int diff = n2 - n1;

	return n1 + (diff * perc);
}
void PinkWitchBullet::Update(DWORD dt)
{
	shootTime += dt;
	if (shootTime >= 300)
	{
		if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
		{
			this->Active = true;
			distance += vx * dt;
			if (enemy->IsLeft() == true )
			{
				this->SetPositionX((float)(this->GetPositionX() + -0.05*dt));
				this->isLeft = true;
 				if (abs(distance) >= 80)
				{
					this->SetPositionY((float)(this->GetPositionY() - 2));
				}
				else
				{
					this->SetPositionY((float)(this->GetPositionY() + 0.8f));

				}
				if ((float)this->GetPositionY() <= 40)
				{
					Reset();
				}
			}
			else
			{
					this->SetPositionX((float)(this->GetPositionX() + 0.05*dt));
					this->isLeft = false;
					if (abs(distance) >= 80)
					{
						this->SetPositionY((float)(this->GetPositionY() - 2));
					}
					else
					{
						this->SetPositionY((float)(this->GetPositionY() + 0.8f));

					}
					if ((float)this->GetPositionY() <= 40)
					{
						Reset();
					}
			}
		}
		else
		{
			this->Active = false;
			Reset();
		}
	}
}

void PinkWitchBullet::Render()
{
	if (Active == true)
	{
		SpriteData spriteEnemyData;

		spriteEnemyData.width = PINK_WITCH_BULLET_WIDTH;
		spriteEnemyData.height = PINK_WITCH_BULLET_HEIGHT + 10;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();
		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = enemy->IsLeft();
		spriteEnemyData.isFlipped = enemy->IsFlipped();

		this->animations[0]->Render(spriteEnemyData);
	}
}

void PinkWitchBullet::Reset()
{
	this->x = enemy->GetPositionX();
	this->y = enemy->GetPositionY();
	this->Active = false;
	distance = 0;
	shootTime = 0;
}


PinkWitchBullet::~PinkWitchBullet()
{
}
