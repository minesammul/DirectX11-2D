#pragma once
#include <Script.h>

class CCamera;
class CTileMapScript : public CScript
{
private:
	const int GRID_COUNT = 32;
	const int TILEMAP_TILE_COUNT = 1024;

private:
	CResPtr<CMaterial>  m_pCloneMtrl;

	int referecneTileIndexData[1024];

	CScript* tilesetScript;
	POINT startMousePosition;

	CCamera* tileMapCamera;

public:
	CTileMapScript();
	~CTileMapScript();

public:
	virtual void awake();
	virtual void update();
	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

	void EditTileMap();
};

