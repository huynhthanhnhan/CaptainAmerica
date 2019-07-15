#include "Flames.h"
#include "Grid.h"

Flames::Flames()
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

void Flames::LoadResources()
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

void Flames::Update(DWORD dt)
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

void Flames::Render()
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



Flames *  Flames::CreateFlames(int GameItemId ,float posx, float posy, float dt)
{
	Flames * flames = new Flames();
	flames->Id = GameItemId;
	flames->Active = true;
	flames->x = posx;
	flames->y = posy;

	flames->SetItemType(Item::FLAMES);

	flames->collider.x = posx;
	flames->collider.y = posy;
	flames->dt = dt;

	return flames;
} 
Flames::~Flames()
{
}