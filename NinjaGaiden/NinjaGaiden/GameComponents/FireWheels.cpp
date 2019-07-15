#include "FireWheels.h"
#include "Grid.h"

FireWheels::FireWheels()
{
	LoadResources();

	Active = true;

	width = FLAMES_SPRITE_WIDTH;
	height = FLAMES_SPRITE_HEIGHT;

	vy = -NINJA_GRAVITY;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = FLAMES_SPRITE_WIDTH;
	collider.height = FLAMES_SPRITE_HEIGHT;
}

void FireWheels::LoadResources()
{
	Animation * anim = new Animation(100);
	for (int i = 7; i < 8; i++)
	{
		RECT rect;
		rect.left = (i % FLAMES_TEXTURE_COLUMNS) * FLAMES_SPRITE_WIDTH;
		rect.right = rect.left + FLAMES_SPRITE_WIDTH + 5;
		rect.top = (i / FLAMES_TEXTURE_COLUMNS) * FLAMES_SPRITE_HEIGHT;
		rect.bottom = rect.top + FLAMES_SPRITE_HEIGHT + 2;
		Sprite * sprite = new Sprite(FLAMES_TEXTURE_LOCATION, rect, FLAMES_TEXTURE_TRANS_COLOR);

		anim->AddFrame(sprite);
	}

	animations.push_back(anim);

}

void FireWheels::Update(DWORD dt)
{
	if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
	{
		this->SetActive(true);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		vector<Tile *> tiles = Grid::GetInstance()->GetCollisionTiles();

		this->SetSpeedY(this->GetSpeedY() - NINJA_GRAVITY);

		coEvents.clear();
		this->SetDt(dt);
		this->CalcPotentialCollisions(tiles, coEvents);

		if (coEvents.size() == 0)
		{
			float moveY = trunc(this->GetSpeedY()* dt);

			this->SetPositionY(this->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
			float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;

			this->SetPositionY(this->GetPositionY() + moveY);

			if (ny != 0) this->SetSpeedY(0);
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		this->SetActive(false);
		this->SetSpeedX(0);
	}
}

void FireWheels::Render()
{

	SpriteData spriteEnemyData;

	spriteEnemyData.width = FLAMES_SPRITE_WIDTH + 20;
	spriteEnemyData.height = FLAMES_SPRITE_HEIGHT + 20;
	spriteEnemyData.x = this->GetPositionX();
	spriteEnemyData.y = this->GetPositionY();

	spriteEnemyData.scale = 1;
	spriteEnemyData.angle = 0;

	this->animations[0]->Render(spriteEnemyData);
}

FireWheels *  FireWheels::CreateFireWheels(int GameItemId, float posx, float posy, float dt)
{
	FireWheels * firewheel = new FireWheels();
	firewheel->Id = GameItemId;
	firewheel->Active = true;
	firewheel->x = posx;
	firewheel->y = posy;
	firewheel->SetItemType(Item::FIREWHEELS);

	firewheel->collider.x = posx;
	firewheel->collider.y = posy;
	firewheel->dt = dt;

	return firewheel;
}
FireWheels::~FireWheels()
{
}