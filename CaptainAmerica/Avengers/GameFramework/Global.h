#pragma once


//Tên ứng dụng
#define WINDOW_CLASS_NAME L"Captain America"
#define MAIN_WINDOW_TITLE L"Captain America"
//Màu background, kích cỡ màn hình
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 228
#define MAP_HEIGHT 176

//Framerate tối đa
#define MAX_FRAME_RATE 90

//
enum Stage {
	STAGE_1,
	STAGE_2,
	STAGE_BOSS_1,
	STAGE_BOSS_2,
};
enum ObjectType
{
	DEFAULT,
	BRICK,
	VINES,
	BRICK_NOCOLLISION_BOTTOM,
	SWING_PLATFORM,
	ON_BUTTON,
	WATER,
};

enum EnemyType
{
	ENEMY1,
	ENEMY2,
	ENEMY3,
};

enum eCaptainState
{
	IDLE,
	WALK,
	JUMP,
	CROUCH,
	THROW_SHIELD,
	ROLL,
	KICK,
	STAND_HIT,
	CROUCH_HIT,
	SIT_ON_SHIELD,
	SWING,
	WADE,
	SHIELD_TOP,
	HURT,
	DEAD,
	DASH,
	DIVE,
};

enum eEnemyState
{
	EnemyIDLE,
	EnemyWALK,
	EnemyCROUCH,
	EnemyHURT,
	EnemyJUMP,
};

enum eController
{
	NoneControl,
	LeftControl,
	RightControl,
	UpControl,
	DownControl,
	JumpControl,
	DashControl,
	ThrowControl
};

//TiledMap
// TILE
#define CHARLESTON_MAP L"Resources\\TiledMap\\Map-Charleston-Matrix.txt"
#define PITTSBURGH_MAP L"Resources\\TiledMap\\Map-Pittsburgh-Matrix.txt"
#define WIZARD_BOSS_MAP L"Resources\\TiledMap\\Map-Boss1-Matrix.txt"

#define MAP_MATRIX_DELIMITER " "
#define TILE_WIDTH	16
#define TILE_HEIGHT	16
#define TILES_TRANSCOLOR D3DCOLOR_XRGB(255, 0, 255)

#define GRID_SIZE 32
#define GRID_MAX_X 48
#define GRID_MAX_Y 5

//Giá trị tốc độ đi, tốc độ nhảy, trọng lực
#define CAPTAIN_AMERICA_WALKING_SPEED_X		0.125f
#define CAPTAIN_AMERICA_JUMP_SPEED_Y		0.2f
#define CAPTAIN_AMERICA_GRAVITY			0.02f
#define CAPTAIN_AMERICA_WADING_SPEED 0.08F


#define CAPTAIN_AMERICA_TEXTURE_LOCATION L"Resources\\Captain\\Character.png"
#define CAPTAIN_AMERICA_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(0, 168, 80, 1)
#define CAPTAIN_AMERICA_SPRITE_WIDTH 26
#define CAPTAIN_AMERICA_SPRITE_HEIGHT 36

#define ENEMIES_TEXTURE_LOCATION L"Resources\\Enemy\\Enemies.png"


//Các số để chạy animation của Shield
#define SHIELD_LEFT 0
#define SHIELD_CENTER 1
#define SHIELD_UP 2
#define SHIELD_DOWN 3
#define NO_SHIELD 4

#define SHIELD_SPEED 0.4f
