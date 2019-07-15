#include "GameObject.h"
#include "Game.h"
#include "Sword.h"
#include "Flames.h"
#include "WindmillStar.h"
#include "FireWheels.h"
#include "HealthItem.h"
#include "BonusPointBlue.h"
#include "BonusPointRed.h"
#include "ThrowingStar.h"
#include "FireWheels.h"
#include "SpiritPointBlue.h"
#include "SpiritPointRed.h"
#include "TimeFreeze.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = 0;
	collider.height = 0;
}
GameObject::GameObject(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = width;
	collider.height = height;
}

GameObject::~GameObject()
{
}

//Hàm cập nhật
void GameObject::Update(DWORD dt)
{

}
//Hàm render
void GameObject::Render()
{

}

void GameObject::AddGameItem(Enemy * enemy)
{
	GameItem * gameitem;
	if (enemy->GetEnemyType() == EnemyType::REDBIRD && Game::GetInstance()->GetStage() == Stage::STAGE_31)
	{
		switch (enemy->GetItemType())
		{
		case Item::FLAMES:
		{
			gameitem = Flames::CreateFlames(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::WINDMILLSTAR:
		{
			gameitem = WindmillStar::CreateWindmillStar(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::FIREWHEELS:
		{
			gameitem = FireWheels::CreateFireWheels(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::SPIRITPOINTBLUE:
		{
			gameitem = SpiritPointBlue::CreateSpiritPointBlue(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::SPIRITPOINTRED:
		{
			gameitem = SpiritPointRed::CreateSpiritPointRed(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::TIMEFREEZE:
		{
			gameitem = TimeFreeze::CreateTimeFreeze(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::THROWINGSTAR:
		{
			gameitem = ThrowingStar::CreateThrowingStar(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::BONUSPOINTBLUE:
		{
			gameitem = BonusPointBlue::CreateBonusPointBlue(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::BONUSPOINTRED:
		{
			gameitem = BonusPointRed::CreateBonusPointRed(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::HEALTHITEM:
		{
			gameitem = HealthItem::CreateHealthItem(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		default:
			break;
		}
	}
	else if (enemy->GetEnemyType() == EnemyType::BLOODYBIRD && Game::GetInstance()->GetStage() == Stage::STAGE_32)
	{
		switch (enemy->GetItemType())
		{
		case Item::FLAMES:
		{
			gameitem = Flames::CreateFlames(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::WINDMILLSTAR:
		{
			gameitem = WindmillStar::CreateWindmillStar(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::FIREWHEELS:
		{
			gameitem = FireWheels::CreateFireWheels(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::SPIRITPOINTBLUE:
		{
			gameitem = SpiritPointBlue::CreateSpiritPointBlue(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::SPIRITPOINTRED:
		{
			gameitem = SpiritPointRed::CreateSpiritPointRed(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::TIMEFREEZE:
		{
			gameitem = TimeFreeze::CreateTimeFreeze(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::THROWINGSTAR:
		{
			gameitem = ThrowingStar::CreateThrowingStar(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::BONUSPOINTBLUE:
		{
			gameitem = BonusPointBlue::CreateBonusPointBlue(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::BONUSPOINTRED:
		{
			gameitem = BonusPointRed::CreateBonusPointRed(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		case Item::HEALTHITEM:
		{
			gameitem = HealthItem::CreateHealthItem(GameItem::GetGameItemId(), enemy->GetPositionX(), enemy->GetPositionY(), enemy->GetDt());
			Grid::GetInstance()->AddGameItem(gameitem);
		}break;
		default:
			break;
		}
	}
}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float t, nx, ny;

	t = Game::SweptAABB(
		this->collider,
		coO->GetCollider(),
		nx,
		ny
	);

	LPCOLLISIONEVENT e = new CollisionEvent(t, nx, ny, coO);
	return e;
}
void GameObject::CalcPotentialGameObjectCollisions(
	vector<LPGAMEOBJECT> &coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	return;
}
void GameObject::CalcPotentialMapCollisions(
	vector<Tile *> &tiles,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	LPGAMEOBJECT solidTileDummy = new GameObject(0, 0, 16, 16);
	for (int i = 0; i < tiles.size(); i++)
	{
		Tile * curTile = tiles[i];
		solidTileDummy->SetPositionX(curTile->x);
		solidTileDummy->SetPositionY(curTile->y);
		solidTileDummy->UpdateTileCollider();

		if (curTile->type == ObjectType::BRICK || curTile->type == ObjectType::BRICK_NOCOLLISION_BOTTOM)
		{	
			LPCOLLISIONEVENT e = SweptAABBEx(solidTileDummy);
			e->collisionID = 1;

			if (e->t >= 0 && e->t < 1.0f && e->ny == 1)
			{
				coEvents.push_back(e);
				//Ninja::GetInstance()->SetClimming(false);
			}
			else
			{
				delete e;
			}
		}
		else if (curTile->type == ObjectType::VINES)
		{
			LPCOLLISIONEVENT e = SweptAABBEx(solidTileDummy);
			e->collisionID = 1;
			Ninja* ninja = Ninja::GetInstance();

			if (e->t >= 0 && e->t < 1.0f && e->ny == 1)
			{
				ninja->SetState(ninja->GetClimbState());
				ninja->SetSpeedY(0);
				ninja->SetSpeedX(0);
				ninja->SetClimming(true);
			}
		}
		else 
		{
			
		}
	}
}

void GameObject::CalcPotentialCollisions(
	vector<Tile *> &tiles,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	this->UpdateObjectCollider();
	CalcPotentialMapCollisions(tiles, coEvents);

	sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void GameObject::CalcPotentialCollisionsWithEnemy(
	vector<Enemy *> &enemies,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	UpdateObjectCollider();
	CalcPotentialNinjaCollideWithEnemy(enemies, coEvents,CollisionWithEnemy::COLLIDING);
}
void GameObject::NinjaCollideWithEnemyBullet(vector<Bullet *> enemiesbullets,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	UpdateObjectCollider();
	CalcPotentialNinjaCollideWithBullet(enemiesbullets, coEvents);
}
void GameObject::CalcPotentialCollisionsWithGameItem(vector<GameItem *> &gameitems)
{
	UpdateObjectCollider();
	CalcPotentialNinjaCollideWithGameItem(gameitems);
}

void GameObject::CalcPotentialNinjaCollideWithGameItem(vector<GameItem *> &gameitems)
{
	for (int i = 0; i < gameitems.size(); i++)
	{
		if (gameitems[i]->IsActive() == true)
		{
			GameItem * gameitem = gameitems[i];

			if (this->IsCollideWithGameItem(gameitem))
			{
				// update item effect for ninja
				Ninja::GetInstance()->SetCheckItem(true);
				Ninja::GetInstance()->Additem(gameitem);
			}
		}
	}
}
void GameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) 
		{
			min_tx = c->t; 
			nx = c->nx; 
			min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) 
		{
			min_ty = c->t; 
			ny = c->ny; 
			min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void GameObject::CalcPotentialCollisionsAttackingEnemy(vector<Enemy*>& enemies, vector<LPCOLLISIONEVENT>& coEvents)
{
	int direction = (Ninja::GetInstance()->IsLeft() == true) ? -1 : 1;
	this->UpdateSwordCollider(direction);
	CalcPotentialNinjaCollideWithEnemy(enemies, coEvents, CollisionWithEnemy::ATACKING);
}
void GameObject::CalcPotentialNinjaSwordWithBullet(vector<Bullet*>& bullets, vector<LPCOLLISIONEVENT>& coEvents)
{
	int direction = (Ninja::GetInstance()->IsLeft() == true) ? -1 : 1;
	this->UpdateSwordCollider(direction);
	CalcPotentialNinjaSwordWithBullet(bullets);
}
void GameObject::CalcPotentialNinjaCollideWithEnemy(vector<Enemy*>& enemies, vector<LPCOLLISIONEVENT>& coEvents, CollisionWithEnemy HitType)
{
	LPGAMEOBJECT CollisionEnemy = new GameObject(0, 0, 16, 16);
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsActive() == true )
		{
			Enemy * enemy = enemies[i];

			CollisionEnemy->SetPositionX(enemy->x);
			CollisionEnemy->SetPositionY(enemy->y);
			CollisionEnemy->SetSpeedX(enemy->vx);
			CollisionEnemy->SetSpeedY(enemy->vy);
			CollisionEnemy->height = enemy->height;
			CollisionEnemy->width = enemy->width;
			CollisionEnemy->UpdateObjectCollider();

			CollisionEnemy->collider.width = enemy->width;
			CollisionEnemy->collider.height = enemy->height;

			if (HitType == CollisionWithEnemy::ATACKING)
			{
				if (this->IsCollide(CollisionEnemy))
				{
					enemy->TakeDamage(Sword::GetInstance()->GetDamage());

					LPCOLLISIONEVENT e = new CollisionEvent(0.0f, 0.0f, 0.0f, NULL);
					coEvents.push_back(e);

					if (enemy->GetEnemyStamina() <= 0)
					{
						// add death animation when kill enemy
						if (enemy->GetEnemyType() == EnemyType::BOSS)
						{
							int posx = enemy->GetPositionX(), posy = enemy->GetPositionY();
							DeathAnimation * animationtopleft = DeathAnimation::CreateDeateAnimation(enemy,posx,posy);
							DeathAnimation * animationbottomleft = DeathAnimation::CreateDeateAnimation(enemy,posx, posy - enemy->GetHeight()/2);
							DeathAnimation * animationtopright = DeathAnimation::CreateDeateAnimation(enemy,posx + enemy->GetWidth()/2, posy);
							DeathAnimation * animationbottomright = DeathAnimation::CreateDeateAnimation(enemy,posx + enemy->GetWidth()/2, posy - enemy->GetHeight()/2);

							Grid::GetInstance()->AddDeathAnimation(animationtopleft);
							Grid::GetInstance()->AddDeathAnimation(animationbottomleft);
							Grid::GetInstance()->AddDeathAnimation(animationtopright);
							Grid::GetInstance()->AddDeathAnimation(animationbottomright);
						}
						else
						{
							DeathAnimation * animation = DeathAnimation::CreateDeateAnimation(enemy);
							Grid::GetInstance()->AddDeathAnimation(animation);
							AddGameItem(enemy);
						}
						// delete enemy
						int EnemyIndex = Grid::GetInstance()->GetEnemyIndexById(enemy->GetId());
						int score = Ninja::GetInstance()->GetScore() + enemy->GetPoint();
						Ninja::GetInstance()->SetScore(score);
						Grid::GetInstance()->DeleteEnemy(EnemyIndex);
						// delete bullet of enemy
						Grid::GetInstance()->DeleteBullet(enemy);
					}	
				}
			}
			else
			{
				LPCOLLISIONEVENT e = SweptAABBEx(CollisionEnemy);
				e->collisionID = 0;

				if (e->t >= 0 && e->t < 1.0f)
				{
					Ninja::GetInstance()->TakeDamage(enemy->GetDamage());
					//Ninja::GetInstance()->Attacked();
					if (Ninja::GetInstance()->GetStamina() <= 0)
					{
						Ninja::GetInstance()->Reset();
					}
					coEvents.push_back(e);
				}
				else
				{
					delete e;
				}
			}
		}
	}
}

void GameObject::CalcPotentialNinjaCollideWithBullet(vector<Bullet*>& bullets, vector<LPCOLLISIONEVENT>& coEvents)
{
	LPGAMEOBJECT CollisionBullet = new GameObject(0, 0, 16, 16);
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->IsActive() == true)
		{
			Bullet * bullet = bullets[i];

			CollisionBullet->SetPositionX(bullet->x);
			CollisionBullet->SetPositionY(bullet->y);
			CollisionBullet->SetSpeedX(bullet->vx);
			CollisionBullet->SetSpeedY(bullet->vy);
			CollisionBullet->height = bullet->height;
			CollisionBullet->width = bullet->width;
			CollisionBullet->UpdateObjectCollider();

			CollisionBullet->collider.width = bullet->width;
			CollisionBullet->collider.height = bullet->height;

			LPCOLLISIONEVENT e = SweptAABBEx(CollisionBullet);
			e->collisionID = 0;

			if (e->t >= 0 && e->t < 1.0f)
			{
				Ninja::GetInstance()->TakeDamage(bullet->GetDamage());
				if (Ninja::GetInstance()->GetStamina() <= 0)
				{
					Ninja::GetInstance()->Reset();
				}
				bullets[i]->Reset();
				coEvents.push_back(e);
			}
			else
			{
				delete e;
			}
		}
	}
}

void GameObject::CalcPotentialNinjaSwordWithBullet(vector<Bullet*>& bullets)
{
	LPGAMEOBJECT CollisionBullet = new GameObject(0, 0, 16, 16);
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->IsActive() == true && bullets[i]->GetBulletType() == BulletType::BOSS_BULLET)
		{
			Bullet * bullet = bullets[i];

			CollisionBullet->SetPositionX(bullet->x);
			CollisionBullet->SetPositionY(bullet->y);
			CollisionBullet->SetSpeedX(bullet->vx);
			CollisionBullet->SetSpeedY(bullet->vy);
			CollisionBullet->height = bullet->height;
			CollisionBullet->width = bullet->width;
			CollisionBullet->UpdateObjectCollider();

			CollisionBullet->collider.width = bullet->width;
			CollisionBullet->collider.height = bullet->height;

			LPCOLLISIONEVENT e = SweptAABBEx(CollisionBullet);
			e->collisionID = 0;

			if (e->t >= 0 && e->t < 1.0f)
			{
				DeathAnimation * animation = DeathAnimation::CreateDeateAnimationForGameObject(bullets[i]);
				Grid::GetInstance()->AddDeathAnimation(animation);
				bullets[i]->SetActive(false);
				Grid::GetInstance()->DeleteBossBullet();
			}
			else
			{
				delete e;
			}
		}
	}
}
bool GameObject::IsCollide(GameObject * CollisionObject)
{
	Collider MainObject = this->collider;
	RECT rec;
	rec.top = MainObject.y;
	rec.left = MainObject.x;
	rec.right = MainObject.x + MainObject.width;
	rec.bottom = MainObject.y - MainObject.height;

	Collider TargetObject = CollisionObject->collider;
	if (MainObject.direction == 1)
	{
		if (TargetObject.x > rec.left && TargetObject.x < rec.right )
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
		}
		else 
		{
			return false;
		}
	}
	else if (MainObject.direction == -1)
	{
		if (TargetObject.x + TargetObject.width > rec.left && TargetObject.x + TargetObject.width < rec.right)
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}
	return false;
}
bool GameObject::IsCollideWithGameItem(GameItem * gameitem)
{
	Collider MainObject = this->collider;
	RECT rec;
	rec.top = MainObject.y;
	rec.left = MainObject.x;
	rec.right = MainObject.x + MainObject.width;
	rec.bottom = MainObject.y - MainObject.height;

	Collider TargetObject = gameitem->collider;
	if (MainObject.direction == 1)
	{
		if (TargetObject.x > rec.left && TargetObject.x < rec.right)
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else if (MainObject.direction == -1)
	{
		if (TargetObject.x + TargetObject.width > rec.left && TargetObject.x + TargetObject.width < rec.right)
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom > TargetObject.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}
void GameObject::UpdateObjectCollider()
{
	int direction = (isLeft == true) ? -1 : 1;
	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.direction = direction;
}
void GameObject::UpdateSwordCollider(int direction)
{
	collider.x = x + direction * 5;
	if (Game::GetInstance()->GetStage() == STAGE_BOSS)
	{
		collider.x = x + direction * width/3;
	}
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.width = width;
	collider.height = height;
	collider.direction = direction;
}
void GameObject::UpdateNinjaAttackingtCollider()
{
	int direction = (isLeft == true) ? -1 : 1;
	collider.x = x + (collider.width) * direction;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.direction = direction;
}
void GameObject::UpdateTileCollider()
{
	collider.x = x;
	collider.y = y - 8;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.height = 8;
}
RECT GameObject::GetRect()
{
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.right = x + width;
	rect.bottom = y - height;
	return rect;
}