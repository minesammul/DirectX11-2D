#pragma once
#include <Script.h>
class CTileScript : public CScript
{
private:
	const float TILE_MOVE_SPEED = 600.f;
	const float TILE_SCALE_MULTI_VALUE = 1.2f;
	const int GRID_COUNT = 23;
	const int TEXTURE_TILE_COUNT = 487;

private:
	int selectTileX;
	int selectTileY;
	int selectTileIndex;
	int gridCount;
	int textureTileCount;
	CCamera* tileMapCamera;

public:
	CTileScript();
	~CTileScript();

public:
	virtual void awake();
	virtual void update();

	int GetSelectTileX() { return selectTileX; }
	int GetSelectTileY() { return selectTileY; }
	int GetSelectTileIndex() { return selectTileIndex; }

	void EditMoveTileMap();
	void ClickTileSetTile();
};

