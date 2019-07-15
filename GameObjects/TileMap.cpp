#include "TileMap.h"
#include <iostream>

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
	SAFE_DELETE_PTR(m_pTileset);
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void TileMap::Initialise()
{

}

void TileMap::Update()
{

}

void TileMap::GetPosition(int& x, int& y)
{

}

bool TileMap::LoadFromSpriteSheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, unsigned int width, unsigned int height)
{
	if (!pSpritesheetDef)
		return false;

	m_CollisionType = E_Collider_Tile;
	m_mapWidth = width;
	m_mapHeight = height;

	AssetManager* pAssetManager = C_SysContext::Get<AssetManager>();
	m_pTileset = &(pAssetManager->GetTexture(pSpritesheetDef->m_Filename.c_str()));
	std::vector<sf::IntRect> frames;
	for (std::vector<SpritesheetSpriteDef>::iterator iter = pSpritesheetDef->m_pSpriteDefs.begin(); iter != pSpritesheetDef->m_pSpriteDefs.end(); iter++)
	{
		sf::IntRect rect((*iter).m_PosX, (*iter).m_PosY, (*iter).m_Width, (*iter).m_Height);
		frames.push_back(rect);
	}

	int numOfTiles = 0;
	for (unsigned int i = 0; i < (width * height); i++)
	{
		int tileNumber = tiles[i];
		if (tileNumber < 0 || (size_t)tileNumber >= (frames.size()))
			continue;

		numOfTiles++;
	}

	//resize the vertex array to fit the level size
	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices.resize(numOfTiles * 4);
	int quadNum = 0;

	m_TileIndices.resize(width);
	for (unsigned int i = 0; i < width; ++i)
	{
		m_TileIndices[i].resize(height);
	}

	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			//get the current tile number
			int tileNumber = tiles[i + j * width];
			if (tileNumber < 0 || (size_t)tileNumber >= (frames.size()))
				continue;

			m_TileIndices[i][j] = tileNumber;

			//find its position in the tileset texture
			int tu1 = frames[tileNumber].left;
			int tv1 = frames[tileNumber].top;
			int tu2 = tu1 + frames[tileNumber].width;
			int tv2 = tv1 + frames[tileNumber].height;

			//get a pointer to the current tile's quad
			sf::Vertex* quad = &m_Vertices[(quadNum) * 4];

			//Borders work
			m_tileWidth = frames[tileNumber].width;
			m_tileHeight = frames[tileNumber].height;

			//define its 4 corners
			quad[0].position = sf::Vector2f((float)i * frames[tileNumber].width, (float)j * frames[tileNumber].height);
			quad[1].position = sf::Vector2f(((float)i + 1.f) * frames[tileNumber].width, (float)j * frames[tileNumber].height);
			quad[2].position = sf::Vector2f(((float)i + 1.f) * frames[tileNumber].width, ((float)j + 1.f) * frames[tileNumber].height);
			quad[3].position = sf::Vector2f((float)i * frames[tileNumber].width, ((float)j + 1.f) * frames[tileNumber].height);

			//define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f((float)tu1, (float)tv1);
			quad[1].texCoords = sf::Vector2f((float)tu2, (float)tv1);
			quad[2].texCoords = sf::Vector2f((float)tu2, (float)tv2);
			quad[3].texCoords = sf::Vector2f((float)tu1, (float)tv2);
			quadNum++;
		}
	}

	m_CollisionRect.left = 0;
	m_CollisionRect.top = 0;
	m_CollisionRect.height = (float)(m_tileHeight * height);
	m_CollisionRect.width = (float)(m_tileWidth * width);

	C_SysContext::Get<RenderManager>()->AddRenderObject(this);

	return true;
}

int TileMap::TileIndexAtPosition(int posX, int posY)
{
	int locationX = posX / m_tileWidth;
	int locationY = posY / m_tileHeight;

	if (locationX >= m_mapWidth || locationY >= m_mapHeight || locationX < 0 || locationY < 0)
	{
		//if outside of range then return a value which creates a collision
		return 17;
	}

	int returnValue = m_TileIndices[locationX][locationY];

	return returnValue;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//apply transform
	states.transform *= getTransform();
	
	//apply tileset texture
	states.texture = m_pTileset;

	//draw the vertex array
	target.draw(m_Vertices, states);
}

bool TileMap::LoadFromFileDesertMap(SpritesheetDef*pSpritesheetDef)
{
	int mapWidth = 80; // width of the map

	int mapHeight = 82; // height of map

	std::ifstream file;
	file.open("levels/desertmap1.txt");// Read the file and store the value into our map

	if (file.is_open())
	{
		int* pMap = new int[mapWidth*mapHeight];
		int input;

		for (int i = 0; i < mapWidth * mapHeight; i++)
		{
			file >> input;
			pMap[i] = input;
		}

		file.close();

		LoadFromSpriteSheetDef(pSpritesheetDef, pMap, mapWidth, mapHeight);

		delete[] pMap;

	}
	else
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cerr << "Error: " << message;
	}


	return true;

}


bool TileMap::LoadFromFileDesertMap2(SpritesheetDef*pSpritesheetDef)
{
	int mapWidth = 80; // width of the map

	int mapHeight = 82; // height of map


	std::ifstream file2;
	file2.open("levels/desertmap2.txt");// Read the file and store the value into our map

	if (file2.is_open())
	{
		int* pMap = new int[mapWidth*mapHeight];
		int input;

		for (int i = 0; i < mapWidth * mapHeight; i++)
		{
			file2 >> input;
			pMap[i] = input;
		}

		file2.close();

		LoadFromSpriteSheetDef(pSpritesheetDef, pMap, mapWidth, mapHeight);

		delete[] pMap;

	}
	else
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cerr << "Error: " << message;
	}

	return true;
}

bool TileMap::LoadFromFileShipMap(SpritesheetDef*pSpritesheetDef)
{
	int mapWidth = 190; // width of the map

	int mapHeight = 60; // height of map




						
	// Read the file and store the value into our map

	std::ifstream file3;
	file3.open("levels/shipmap1.txt");// Read the file and store the value into our map

	if (file3.is_open())
	{
		int* pMap = new int[mapWidth*mapHeight];
		int input;

		for (int i = 0; i < mapWidth * mapHeight; i++)
		{
			file3 >> input;
			pMap[i] = input;
		}

		file3.close();

		LoadFromSpriteSheetDef(pSpritesheetDef, pMap, mapWidth, mapHeight);

		delete[] pMap;

	}
	else
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cerr << "Error: " << message;
	}


	return true;

}

bool TileMap::LoadFromFileShipMap2(SpritesheetDef*pSpritesheetDef)
{
	int mapWidth = 190; // width of the map

	int mapHeight = 60; // height of map




	// Read the file and store the value into our map

	std::ifstream file4;
	file4.open("levels/shipmap2.txt");// Read the file and store the value into our map

	if (file4.is_open())
	{
		int* pMap = new int[mapWidth*mapHeight];
		int input;

		for (int i = 0; i < mapWidth * mapHeight; i++)
		{
			file4 >> input;
			pMap[i] = input;
		}

		file4.close();

		LoadFromSpriteSheetDef(pSpritesheetDef, pMap, mapWidth, mapHeight);

		delete[] pMap;

	}
	else
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cerr << "Error: " << message;
	}


	return true;

}



bool TileMap::CollidesWith(Collider2D* pCollider2D)
{
	return pCollider2D->CollidesWith(this);
}

bool TileMap::CollidesWith(BoxCollider2D* pBoxCollider2D)
{
	return false;
}

bool TileMap::CollidesWith(CircleCollider2D* pCircleCollider2D)
{
	return false;
}

bool TileMap::CollidesWith(TileMap* pTileMapCollider)
{
	return false;
}

void TileMap::OnCollision(Collider2D * pCollider2D)
{
}