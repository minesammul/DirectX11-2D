#include "stdafx.h"
#include "TileScript.h"

#include <Camera.h>


CTileScript::CTileScript() : 
	CScript((UINT)SCRIPT_TYPE::TILESCRIPT)
{
}


CTileScript::~CTileScript()
{
}

void CTileScript::awake()
{
	CResPtr<CTexture> tileTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Tile\\No Animation Tile\\16x16\\16x16Tileset.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &tileTexture);

	gridCount = GRID_COUNT;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &gridCount);

	textureTileCount = TEXTURE_TILE_COUNT;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &textureTileCount);

	selectTileIndex = -1;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_2, &selectTileIndex);

	selectTileX = -1;
	selectTileY = -1;

	vector<CCamera*> cameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
	tileMapCamera = cameras[0];
}

void CTileScript::update()
{
	ClickTileSetTile();
	EditMoveTileMap();
}

void CTileScript::EditMoveTileMap()
{

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_HOLD)
	{
		Vec3 ObjectPosition = tileMapCamera->Object()->Transform()->GetLocalPos();
		ObjectPosition.x += TILE_MOVE_SPEED * DT;
		tileMapCamera->Object()->Transform()->SetLocalPos(ObjectPosition);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_HOLD)
	{
		Vec3 ObjectPosition = tileMapCamera->Object()->Transform()->GetLocalPos();
		ObjectPosition.x -= TILE_MOVE_SPEED * DT;
		tileMapCamera->Object()->Transform()->SetLocalPos(ObjectPosition);
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W) == KEY_STATE::STATE_HOLD)
	{
		Vec3 ObjectPosition = tileMapCamera->Object()->Transform()->GetLocalPos();
		ObjectPosition.y -= TILE_MOVE_SPEED * DT;
		tileMapCamera->Object()->Transform()->SetLocalPos(ObjectPosition);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S) == KEY_STATE::STATE_HOLD)
	{
		Vec3 ObjectPosition = tileMapCamera->Object()->Transform()->GetLocalPos();
		ObjectPosition.y += TILE_MOVE_SPEED * DT;
		tileMapCamera->Object()->Transform()->SetLocalPos(ObjectPosition);
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Q) == KEY_STATE::STATE_TAB)
	{
		float nowCameraScale = tileMapCamera->GetScale();
		nowCameraScale *= TILE_SCALE_MULTI_VALUE;
		tileMapCamera->SetScale(nowCameraScale);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_E) == KEY_STATE::STATE_TAB)
	{
		float nowCameraScale = tileMapCamera->GetScale();
		nowCameraScale /= TILE_SCALE_MULTI_VALUE;
		tileMapCamera->SetScale(nowCameraScale);
	}

}

void CTileScript::ClickTileSetTile()
{
	if (CSceneMgr::GetInst()->GetMousePickingObject() == Object())
	{
		if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_TAB)
		{
			DirectX::XMVECTOR mousePickingPosition = CSceneMgr::GetInst()->GetMousePickingPosition();
			Vec3 objectScale = Object()->Transform()->GetLocalScale();
			Vec3 objectPosition = Object()->Transform()->GetLocalPos();

			int gridX = mousePickingPosition.vector4_f32[0] + objectScale.x / 2;
			int gridY = (mousePickingPosition.vector4_f32[1] - objectScale.y / 2)*(-1);

			gridX -= objectPosition.x;
			gridY += objectPosition.y;

			float gridSizeX = objectScale.x / gridCount;
			float gridSizeY = objectScale.y / gridCount;

			int gridColumn = gridX / gridSizeX;
			int gridRow = gridY / gridSizeY;

			selectTileX = gridColumn;
			selectTileY = gridRow;

			selectTileIndex = gridColumn + gridCount * gridRow;
			Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_2, &selectTileIndex);
		}
	}
}
