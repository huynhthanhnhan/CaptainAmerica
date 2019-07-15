#include "Shuriken.h"
#include "Grid.h"


Shuriken::Shuriken()
{
	LoadResources();

	//IsActive = false;

	width = SHURIKEN_WIDTH;
	height = SHURIKEN_HEIGHT;

	vx = SHURIKEN_SPEED; 

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = SHURIKEN_WIDTH;
	collider.height = SHURIKEN_HEIGHT;
}

void Shuriken::LoadResources()
{
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		RECT rect;
		rect.left = (i % SHURIKEN_TEXTURE_COLUMNS) * SHURIKEN_WIDTH;
		rect.right = rect.left + SHURIKEN_WIDTH;
		rect.top = (i / SHURIKEN_TEXTURE_COLUMNS) * SHURIKEN_HEIGHT;
		rect.bottom = rect.top + SHURIKEN_HEIGHT;
		Sprite * sprite = new Sprite(SHURIKEN_TEXTTURE_LOCATION, rect, NINJA_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Shuriken::Update(DWORD dt)
{
	this->SetSpeedY(0);
	distance += abs(this->GetSpeedX() * dt);
	Ninja* ninja = Ninja::GetInstance();
	if (abs(ninja->GetPositionX() - this->GetPositionX()) >= 150)
	{
		distance = 0;
		this->SetSpeedX(this->GetSpeedX() * -1);
	}
	/*if (ninja->GetPositionY() > this->GetPositionY())
	{
		this->SetSpeedY(0.125f);
	}
	else if (ninja->GetPositionY() < this->GetPositionY())
	{
		this->SetSpeedY(-0.125f);
	}*/

	this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt*(isLeft == true ? -1 : 1)));
	this->SetPositionY((float)(this->GetPositionY() + this->GetSpeedY()* dt));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<Enemy* > enemies = Grid::GetInstance()->GetAllEnemies();
	if (Game::GetInstance()->GetStage() == Stage::STAGE_BOSS)
	{
		enemies = Grid::GetInstance()->GetAllEnemies();
	}
	this->CalcPotentialCollisionsAttackingEnemy(enemies, coEvents);
}

void Shuriken::Render()
{
	Ninja * ninja = Ninja::GetInstance();
	if (ninja->IsThrowing() == true)
	{
		SpriteData spriteEnemyData;

		spriteEnemyData.width = SHURIKEN_WIDTH + 20;
		spriteEnemyData.height = SHURIKEN_HEIGHT + 20;
		spriteEnemyData.x = this->GetPositionX();
		spriteEnemyData.y = this->GetPositionY();

		spriteEnemyData.scale = 1;
		spriteEnemyData.angle = 0;
		spriteEnemyData.isLeft = ninja->IsLeft();
		spriteEnemyData.isFlipped = ninja->IsFlipped();

		this->animations[0]->Render(spriteEnemyData);
	}
}

Shuriken::~Shuriken()
{
}

void Shuriken::CreateShuriken(float posx, float posy, float dt,bool isLeft)
{
	this->Active = true;
	this->x = posx;
	this->y = posy;

	float vx = SHURIKEN_SPEED * (isLeft == true ? -1 : 1);
	this->vx = vx;
	this->collider.vx = vx;

	collider.x = posx;
	collider.y = posy;
	this->dt = dt;
}