#include "Enemy3.h"

Enemy3::Enemy3(int positionX, int positionY)
{
	LoadResource();

	eState = EnemyIDLE;

	this->isLeft = false;
	this->vx = 0;
	this->SetPositionX(positionX);
	this->SetPositionY(positionY);

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = 24;
	collider.height = 46;

	Type = EnemyType::ENEMY3;
}

void Enemy3::LoadResource()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemy\\Enemies.txt");
	Animation * anim;
	Sprite * sprite;

	// IDLE
	anim = new Animation(100);
	sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[22], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[30], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animation.push_back(anim);

	// WALK
	anim = new Animation(100);
	for (int i = 10; i <= 12; i++)
	{
		sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animation.push_back(anim);

	// CROUCH
	anim = new Animation(100);
	sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[13], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animation.push_back(anim);

	// HURT
	anim = new Animation(100);
	sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[14], CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animation.push_back(anim);
}

void Enemy3::Update(DWORD dt)
{
	if (Camera::GetInstance()->IsObjectInCamera(this) == true)
	{
		this->isActive = true;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		vector<Tile *> tiles = Grid::GetInstance()->GetCollisionTiles();

		//this->SetSpeedY(this->GetSpeedY() - CAPTAIN_AMERICA_GRAVITY);

		coEvents.clear();
		this->CalcPotentialCollisions(tiles, coEvents);

		if (coEvents.size() == 0)
		{
			float moveX = trunc(this->GetSpeedX()* dt);
			float moveY = trunc(this->GetSpeedY()* dt);

			this->SetPositionX(this->GetPositionX() + moveX);
			this->SetPositionY(this->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
			float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;

			this->SetPositionX(this->GetPositionX() + moveX);
			this->SetPositionY(this->GetPositionY() + moveY);


			if (nx != 0) this->SetSpeedX(0);
			if (ny != 0) this->SetSpeedY(0);

			if (coEventsResult[0]->collisionID == 1)
			{
				if (ny == 1)
				{
					this->SetSpeedY(0);
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		this->isActive = false;
	}
	if (this->isActive)
	{
		DebugOut(L"TimetoActionn: %f\n", timeToAction);
		if (this->GetPositionX() > Captain::GetInstance()->GetPositionX())
		{
			this->isFlipped = false;
		}
		else
		{
			this->isFlipped = true;
		}
		timeToAction++;
		countTimeToFire++;
		if (countTimeToFire > timeToFire)
			countTimeToFire = timeToFire;
		float speedX = CAPTAIN_AMERICA_WALKING_SPEED_X*5/9;
		float speedY = CAPTAIN_AMERICA_WALKING_SPEED_X * 2 / 3;
		if (timeToAction < 100)
		{
			this->SetSpeedX(speedX * 1);
			this->SetSpeedY(0);
		}
		else if (timeToAction >= 100 && timeToAction < 125)
		{
			this->SetSpeedX(speedX  * 1);
			this->SetSpeedY(speedY  * -1);
		}
		else if (timeToAction >= 125 && timeToAction < 150)
		{
			this->SetSpeedX(speedX * -1);
			this->SetSpeedY(speedY  * -1);
		}
		else if (timeToAction >= 150 && timeToAction < 250)
		{
			this->SetSpeedX(speedX  * -1);
			this->SetSpeedY(0);
		}
		else if (timeToAction >= 250 && timeToAction < 275)
		{
			this->SetSpeedX(speedX * -1);
			this->SetSpeedY(speedY  * 1);
		}
		else if (timeToAction >= 275 && timeToAction < 300)
		{
			this->SetSpeedX(speedX * 1);
			this->SetSpeedY(speedY * 1);
		}
		else
		{
			timeToAction = 0;
		}
		//else
		//{
		//	this->SetSpeedX(0);
		//	this->isFlipped = !this->isFlipped;
		//	bullet = new Enemy3Bullet(this->GetPositionX(), this->GetPositionY(), !isFlipped);
		//	timeToAction = 0;
		//}
		////if(countTimeToFire == 100 && this->eState!= EnemyWALK)
		////	//if(bullet == nullptr)
		////		bullet = new Enemy3Bullet(this->GetPositionX(), this->GetPositionY(), (this->GetPositionX()>Captain::GetInstance()->GetPositionX())?true:false);
		//if (bullet != nullptr)
		//{
		//	if (!bullet->GetIsDestroyed())
		//		bullet->Update(dt);
		//}
	}
	/*else
	{
		if (bullet != nullptr)
			bullet->SetIsDestroyed(true);
	}*/
}

void Enemy3::Render()
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
		spriteEnemyData.isLeft = this->IsLeft();
		spriteEnemyData.isFlipped = this->isFlipped;
	}
	switch (this->eState)
	{
	case EnemyIDLE:
	{
		this->GetAnimationList()[EnemyIDLE]->Render(spriteEnemyData);
	}
	break;
	/*case EnemyWALK:
	{
		this->GetAnimationList()[EnemyWALK]->Render(spriteEnemyData);
	}
	break;
	case EnemyCROUCH:
	{
		this->GetAnimationList()[EnemyCROUCH]->Render(spriteEnemyData);
	}
	break;
	case EnemyHURT:
	{
		this->GetAnimationList()[EnemyHURT]->Render(spriteEnemyData);
	}
	break;*/
	}
	//if (bullet != nullptr)
	//{
	//	if (!bullet->GetIsDestroyed())
	//		bullet->Render();
	//}
}