#include "WindmillStar.h"
#include "Grid.h"

WindmillStar::WindmillStar()
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

void WindmillStar::LoadResources()
{
	Animation * anim = new Animation(100);
	for (int i = 1; i < 2; i++)
	{
		RECT rect;
		rect.left = (i % 2) * SHURIKEN_WIDTH;
		rect.right = rect.left + SHURIKEN_WIDTH;
		rect.top = (i / 2) * (FLAMES_SPRITE_HEIGHT);
		rect.bottom = rect.top + (FLAMES_SPRITE_HEIGHT);
		Sprite * sprite = new Sprite(GAMEITEM_2, rect, D3DCOLOR_XRGB(0, 0, 0));

		anim->AddFrame(sprite);
	}

	animations.push_back(anim);

}

void WindmillStar::Update(DWORD dt)
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
			//float moveX = trunc(this->GetSpeedX()* dt);
			float moveY = trunc(this->GetSpeedY()* dt);

			//this->SetPositionX(this->GetPositionX() + moveX);
			this->SetPositionY(this->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
			float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;

			//this->SetPositionX(this->GetPositionX() + moveX);
			this->SetPositionY(this->GetPositionY() + moveY);


			//if (nx != 0) this->SetSpeedX(0);
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

void WindmillStar::Render()
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

WindmillStar*  WindmillStar::CreateWindmillStar(int GameItemId, float posx, float posy, float dt)
{
	WindmillStar * jumpFlash = new WindmillStar();
	jumpFlash->Id = GameItemId;
	jumpFlash->Active = true;
	jumpFlash->x = posx;
	jumpFlash->y = posy;
	jumpFlash->SetItemType(Item::WINDMILLSTAR);

	jumpFlash->collider.x = posx;
	jumpFlash->collider.y = posy;
	jumpFlash->dt = dt;

	return jumpFlash;
}
WindmillStar::~WindmillStar()
{
}