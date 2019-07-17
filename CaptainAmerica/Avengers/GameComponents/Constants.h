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
	STAGE_31,
	STAGE_32,
	STAGE_BOSS
};
enum ObjectType
{
	DEFAULT,
	BRICK,
	VINES,
	BRICK_NOCOLLISION_BOTTOM
};
//TiledMap
//
// MAP
#define BACKGROUND_3_1 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_3_2 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_BOSS L"Resources\\TiledMap\\Map-Charleston.png"
// TILE
#define TILES_MATRIX_STAGE_31 L"Resources\\TiledMap\\Map-Charleston-Matrix.txt"
#define TILES_MATRIX_STAGE_32 L"Resources\\TiledMap\\Map-Pittsburgh-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS L"Resources\\TiledMap\\Map-Boss1-Matrix.txt"

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
#define CAPTAIN_ANI_IDLE					0
#define CAPTAIN_ANI_WALKING 				1
#define CAPTAIN_ANI_JUMPING 				2
#define CAPTAIN_ANI_CROUCHING 				3

#define CAPTAIN_TEXTURE_LOCATION L"Resources\\CAPTAIN\\Character.png"
#define CAPTAIN_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(0, 168, 80, 1)
#define CAPTAIN_SPRITE_WIDTH 26
#define CAPTAIN_SPRITE_HEIGHT 36


//Các số để chạy animation của Shield
#define SHIELD_LEFT 0
#define SHIELD_CENTER 1
#define SHIELD_UP 2
#define SHIELD_DOWN 3
