#include "TiledMap.h"
#include "../../GameObject/GameComponents/Game.h"
TiledMap *TiledMap::__instance = NULL;
TiledMap *TiledMap::GetInstance(LPCWSTR filePath)
{
	if (__instance == NULL || filePath != NULL)
	{
		if (__instance != NULL)
		{
			delete __instance;
		}
		__instance = new TiledMap(filePath);
	}
	return __instance;
}

TiledMap::TiledMap(LPCWSTR filePath)
{
	string tilesFilePath = LoadMatrix(filePath); // lấy được đường dẫn đến file tiles

	std::wstring stemp = std::wstring(tilesFilePath.begin(), tilesFilePath.end());// convert string sang wstring xử lí ở hàm sau
	LPCWSTR tilesFilePath_wstr = stemp.c_str();

	LoadTileSet(tilesFilePath_wstr);
}
string TiledMap::LoadMatrix(LPCWSTR filePath) // lấy ma trận vị trí các tile từ file matrix đồng thời trả về vị trí file tiles
{
	string tilesLocation;

	ifstream tilesInfo;
	DebugOut(L"filepath: %s\n", filePath);
	tilesInfo.open(filePath);
	if (tilesInfo.is_open())
	{
		getline(tilesInfo, tilesLocation); // truyền tilesInfo vào tilesLocation (lấy dòng đầu tiên trong file Maxtrix
											// là đường dẫn đến file tiles)

		string tmp;
		getline(tilesInfo, tmp); // tilesInfo => tmp (dòng thứ 2 là width, thứ 3 là height
		this->mapWidth = stoi(tmp); // convert string sang int
		getline(tilesInfo, tmp);
		this->mapHeight = stoi(tmp);

		string line;
		Row matrixRow;
		this->matrix.clear();

		int lineNum = 0;
		while (getline(tilesInfo, line)) // chạy từng dòng trong matrix của map
		{
			matrixRow = GetMatrixRow(lineNum, line, " ");
			this->matrix.push_back(matrixRow); // thêm hàng tile lấy dc vào matrix
			lineNum++;
		}
		tilesInfo.close();
	}
	return tilesLocation; // trả về đường dẫn đến file hình tiles

}
Row TiledMap::GetMatrixRow(int lineNum, string line, string delimiter)
{
	size_t pos = 0; // size_t là kiểu dữ liệu không dấu có thể tự mở rộng (mặc định sẽ là unsigned int)
	string token;
	Row result = Row();
	int rowNum = 0;
	Stage stage = Game::GetInstance()->GetStage();
	while ((pos = line.find(delimiter)) != string::npos)  // npos dùng trong xử lí chuỗi với ý nghĩa "until the end of the string"
	{
		token = line.substr(0, pos); // lấy kí tự đầu tiên trong hàng ( id của tile)

		Tile curTile;
		curTile.x = rowNum * TILES_WIDTH_PER_TILE; // số thứ tự của tile trên hàng x kích thước tile (16)
		curTile.y = this->mapHeight - lineNum * TILES_HEIGHT_PER_TILE; // vẽ map từ trên xuống, line = 0 => y = height là dòng đầu tiên 

		curTile.colider = new Collider();
		curTile.colider->x = rowNum * TILES_WIDTH_PER_TILE; // colider có vị trí như hình
		curTile.colider->y = this->mapHeight - lineNum * TILES_HEIGHT_PER_TILE;
		curTile.colider->width = TILES_WIDTH_PER_TILE;
		curTile.colider->height = TILES_HEIGHT_PER_TILE;

		curTile.tileId = stoi(token); // convert id của tile từ string sang int
		if (stage == Stage::STAGE_1)
		{
			// function find() lấy từng phần tử từ đầu đến cuối List để so sánh với val nếu không có trả về phần tử cuối
			if (find(_BrickStage_1.begin(), _BrickStage_1.end(), curTile.tileId) != _BrickStage_1.end())
				curTile.type = ObjectType::BRICK;
			else if (curTile.tileId == 101) // id = 101 là tile của nước
				curTile.type = ObjectType::WATER;
			else
				curTile.type = ObjectType::DEFAULT;
		}
		else if (stage == Stage::STAGE_2)
		{
			if (find(_BrickStage_2.begin(), _BrickStage_2.end(), curTile.tileId) != _BrickStage_2.end())
				curTile.type = ObjectType::BRICK;
			else if (curTile.tileId == 44)
				curTile.type = ObjectType::ON_BUTTON;
			else if (curTile.tileId == 61 || curTile.tileId == 62 || curTile.tileId == 74 || curTile.tileId == 96)
				curTile.type = ObjectType::SWING_PLATFORM;
			else
				curTile.type = ObjectType::DEFAULT;
		}
		else if (stage == Stage::STAGE_BOSS_1)
		{
			if (find(_BrickStage_BOSS_1.begin(), _BrickStage_BOSS_1.end(), curTile.tileId) != _BrickStage_BOSS_1.end())
				curTile.type = ObjectType::BRICK;
			else if (curTile.tileId == 6)
				curTile.type = ObjectType::ON_BUTTON;
			else
				curTile.type = ObjectType::DEFAULT;
		}
		else if (stage == Stage::STAGE_BOSS_2)
		{
			if (find(_BrickStage_BOSS_2.begin(), _BrickStage_BOSS_2.end(), curTile.tileId) != _BrickStage_BOSS_2.end())
				curTile.type = ObjectType::BRICK;
			else
				curTile.type = ObjectType::DEFAULT;
		}
		result.push_back(curTile); // đưa curTile vào list kiểu Row
		line.erase(0, pos + delimiter.length()); //xóa phần tử đầu khỏi hàng
		rowNum++; // qua phần tử tiếp theo trong hàng
	}

	return result; // trả về mảng các tile trong hàng
}

void TiledMap::LoadTileSet(LPCWSTR tilesFilePath)
{
	HRESULT result;
	D3DXIMAGE_INFO info; //Thông tin tileset
	result = D3DXGetImageInfoFromFile(tilesFilePath, &info); //Lấy thông tin texture từ đường dẫn file
	//Kiểm tra lỗi khi lấy thông tin
	if (result != D3D_OK)
	{
		return;
	}
	this->tileSetWidth = info.Width / TILES_WIDTH_PER_TILE; // lấy số lượng tile trên dòng
	this->tileSetHeight = info.Height / TILES_HEIGHT_PER_TILE; // lấy số lượng tile trên cột

	if (Game::GetInstance()->GetStage() == STAGE_1)
	{
		this->mapWidth = 2048; // kích thước gốc của hình stage 1
		this->mapHeight = 476;
	}
	else if (Game::GetInstance()->GetStage() == STAGE_2)
	{
		this->mapWidth = 1280; // kích thước gốc của hình stage 2
		this->mapHeight = 957;
	}
	else if (Game::GetInstance()->GetStage() == STAGE_BOSS_1)
	{
		this->mapWidth = 256; // kích thước gốc của hình stage boss 1
		this->mapHeight = 235;
	}
	else if (Game::GetInstance()->GetStage() == STAGE_BOSS_2) // chưa có hình cần sửa sau "edit"
	{
		this->mapWidth = 256; // kích thước gốc của hình stage boss 2
		this->mapHeight = 235;
	}

	tiles[0] = NULL; //tile id bắt đầu từ 1
	for (int i = 0; i < this->tileSetWidth; i++)
	{
		// lấy vị trí của tile
		RECT rect;
		rect.left = (i % this->tileSetWidth) * TILES_WIDTH_PER_TILE;
		rect.right = rect.left + TILES_WIDTH_PER_TILE;
		rect.top = (i / this->tileSetWidth) * TILES_HEIGHT_PER_TILE;
		rect.bottom = rect.top + TILES_HEIGHT_PER_TILE;

		Sprite *tile = new Sprite(tilesFilePath, rect, TILES_TRANSCOLOR); // lấy hình của tile

		tiles[i + 1] = tile;
	}
}

void TiledMap::Render() // vẽ cả map bằng tile
{
	for (int i = 0; i < matrix.size(); i++) // duyệt từng dòng của ma trận
	{
		Row curRow = matrix[i];
		for (int j = 0; j < curRow.size(); j++) // duyệt từng phần tử trên dòng
		{
			if (curRow[j].tileId != 0)
			{
				SpriteData spriteData;
				spriteData.width = TILES_WIDTH_PER_TILE;
				spriteData.height = TILES_HEIGHT_PER_TILE;
				spriteData.x = j * TILES_WIDTH_PER_TILE;
				spriteData.y = (matrix.size() - i) * TILES_HEIGHT_PER_TILE;
				spriteData.scale = 1;
				spriteData.angle = 0;

				tiles.at(curRow[j].tileId)->SetData(spriteData); // lấy sprite ứng với id để gắn vào tile
				Graphics::GetInstance()->Draw(tiles.at(curRow[j].tileId));
			}
		}
	}
}
void TiledMap::RenderTile(Tile *curTile) // vẽ tile dùng ở Grid
{
	SpriteData spriteData;
	spriteData.width = TILES_WIDTH_PER_TILE;
	spriteData.height = TILES_HEIGHT_PER_TILE;
	spriteData.x = curTile->x;
	spriteData.y = curTile->y;
	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = true;

	tiles.at(curTile->tileId)->SetData(spriteData);
	Graphics::GetInstance()->Draw(tiles.at(curTile->tileId));

}