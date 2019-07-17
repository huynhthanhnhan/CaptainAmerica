#pragma once


//Tên ứng dụng
#define WINDOW_CLASS_NAME L"CaptainAmerica"
#define MAIN_WINDOW_TITLE L"CaptainAmerica"
//Màu background, kích cỡ màn hình
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 250
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
	SWING,
	ON_BUTTON,
	RIVER,
};
//TiledMap
//
// MAP
#define BACKGROUND_1 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_2 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_BOSS_1 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_BOSS_2 L"Resources\\TiledMap\\Map-Charleston.png"
// TILE
#define TILES_MATRIX_STAGE_1 L"Resources\\TiledMap\\Map-Charleston-Matrix.txt"
#define TILES_MATRIX_STAGE_2 L"Resources\\TiledMap\\Map-Pittsburgh-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS_1 L"Resources\\TiledMap\\Map-Boss1-Matrix.txt"

#define TILES_MATRIX_DELIMITER ","
#define TILES_WIDTH_PER_TILE	16
#define TILES_HEIGHT_PER_TILE	16
#define TILES_TRANSCOLOR D3DCOLOR_XRGB(255, 0, 255)

#define GRID_SIZE 64
#define GRID_MAX_X 48
#define GRID_MAX_Y 5

//Giá trị tốc độ đi, tốc độ nhảy, trọng lực
#define CAPTAIN_WALKING_SPEED		0.125f
#define CAPTAIN_JUMP_SPEED_Y		0.4f
#define CAPTAIN_GRAVITY			0.02f

//Các số để chạy animation của Captain

#define  ATTACKTIME 300
#define CAPTAIN_ANI_IDLE				0
#define CAPTAIN_ANI_WALK				1
#define CAPTAIN_ANI_JUMP				2
#define CAPTAIN_ANI_CROUCH 				3
#define CAPTAIN_ANI_THROW_SHIELD 		4
#define CAPTAIN_ANI_ROLL				5
#define CAPTAIN_ANI_KICK				6
#define CAPTAIN_ANI_STAND_HIT			7
#define CAPTAIN_ANI_CROUCH_HIT			8
#define CAPTAIN_ANI_SIT_ON_SHIELD		9
#define CAPTAIN_ANI_SWING				10
#define CAPTAIN_ANI_WADE				11
#define CAPTAIN_ANI_SHIELD_UP			12
#define CAPTAIN_ANI_GET_HURT			13
#define CAPTAIN_ANI_DEAD				14

#define CAPTAIN_TEXTURE_LOCATION L"Resources\\CAPTAIN\\Character.png"
#define CAPTAIN_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(0, 168, 80, 1)
#define CAPTAIN_SPRITE_WIDTH 26
#define CAPTAIN_SPRITE_HEIGHT 36


//Các số để chạy animation của Shield
#define SHIELD_LEFT 0
#define SHIELD_CENTER 1
#define SHIELD_UP 2
#define SHIELD_DOWN 3
#define SHIELD_SPEED 0.15f
