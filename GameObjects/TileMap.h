#ifndef _TILE_MAP_H
#define _TILE_MAP_H

#include "../../Engine/Physics/Collider2D.h"
#include "../../Engine/Core/GameObject.h"
#include "../GameData/SpritesheetDef.h"
#include "SFML\Graphics.hpp"

#include <fstream>


class TileMap
	:public GameObject, public Collider2D, public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	virtual ~TileMap();

	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int& y);

	virtual bool CollidesWith(Collider2D* pCollider2D);
	virtual bool CollidesWith(BoxCollider2D* pBoxCollider2D);
	virtual bool CollidesWith(CircleCollider2D* pCircleCollider2D);
	virtual bool CollidesWith(TileMap* pTileMapCollider);

	virtual void OnCollision(Collider2D* pCollider2D);

	bool LoadFromFileDesertMap(SpritesheetDef*pSpritesheetDef);
	bool LoadFromFileDesertMap2(SpritesheetDef*pSpritesheetDef);
	bool LoadFromFileShipMap(SpritesheetDef*pSpritesheetDef);
	bool LoadFromFileShipMap2(SpritesheetDef*pSpritesheetDef);



	bool LoadFromSpriteSheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, unsigned int width, unsigned int height);

	int TileIndexAtPosition(int x, int y);
	sf::FloatRect m_CollisionRect;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_Vertices;
	sf::Texture* m_pTileset;

	std::vector<std::vector<int>> m_TileIndices;
	
	int m_mapWidth; //Number of tiles
	int m_mapHeight; //Number of tiles
	int m_tileWidth; //In Pixels
	int m_tileHeight; //In Pixels
};

#endif
