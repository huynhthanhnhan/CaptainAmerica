﻿#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include <algorithm>
#include "Sprite.h"
#include "Animation.h"

class Bullet;
class GameItem;
struct Collider
{
	float x, y;
	float width, height;
	float vx = 0, vy = 0;
	float dt = 0;
	int direction;
};

class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;
struct CollisionEvent
{
	int collisionID;
	LPGAMEOBJECT coO;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT coO = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->coO = coO; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};
struct Tile;

typedef vector<Tile> Row;
typedef vector<Row> Matrix;

class Enemy;
class GameObject
{

protected:
	float x;
	float y;

	float vx;
	float vy;

	float width;
	float height;

	float dt;

	bool isLeft;
	bool isFlipped;

	Collider collider;
public:
	void SetPositionX(float x) { this->x = x; }
	void SetPositionY(float y) { this->y = y; }

	void SetSpeedX(float vx) { this->vx = vx; }
	void SetSpeedY(float vy) { this->vy = vy; }

	float GetPositionX() { return this->x; }
	float GetPositionY() { return this->y; }
	float GetSpeedX() { return this->vx; }
	float GetSpeedY() { return this->vy; }
	
	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }

	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	RECT GetRect();

	void SetCollider(Collider col) { this->collider = col; }

	void UpdateObjectCollider();
	void UpdateSwordCollider(int direction);
	void UpdateNinjaAttackingtCollider();
	void UpdateTileCollider();

	void SetDt(float dt) { this->dt = dt; }
	float GetDt() { return dt; }

	void AddGameItem(Enemy* enemy);

	Collider GetCollider() { return this->collider; }
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);

	void CalcPotentialGameObjectCollisions(
		vector<LPGAMEOBJECT> &coObjects,
		vector<LPCOLLISIONEVENT> &coEvents);

	void CalcPotentialMapCollisions(
		vector<Tile *> &tiles,
		vector<LPCOLLISIONEVENT> &coEvents);

	void CalcPotentialCollisions(
		vector<Tile *> &tiles,
		vector<LPCOLLISIONEVENT> &coEvents);

	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	void CalcPotentialCollisionsAttackingEnemy(
		vector<Enemy *> &enemies,
		vector<LPCOLLISIONEVENT> &coEvents);

	void CalcPotentialNinjaCollideWithEnemy(
		vector<Enemy *> &enemies,
		vector<LPCOLLISIONEVENT> &coEvents,
		CollisionWithEnemy HitType);

	void CalcPotentialCollisionsWithEnemy(
		vector<Enemy *> &enemies,
		vector<LPCOLLISIONEVENT> &coEvents);
	void CalcPotentialCollisionsWithGameItem(
		vector<GameItem *> &gameitems);
	void CalcPotentialNinjaCollideWithGameItem(vector<GameItem *> &gameitems);

	void NinjaCollideWithEnemyBullet(vector<Bullet *> enemiesbullets,
		vector<LPCOLLISIONEVENT> &coEvents);
	void CalcPotentialNinjaCollideWithBullet(vector<Bullet*>& bullets, vector<LPCOLLISIONEVENT>& coEvents);

	void CalcPotentialNinjaSwordWithBullet(vector<Bullet*>& bullets, vector<LPCOLLISIONEVENT>& coEvents);
	void CalcPotentialNinjaSwordWithBullet(vector<Bullet*>& bullets);

	bool IsCollide(GameObject * CollisionObject);
	bool IsCollideWithGameItem(GameItem * gameitem);

	GameObject();
	GameObject(float x, float y, float width, float height);
	virtual void Update(DWORD dt);
	virtual void Render();
	~GameObject();
};

