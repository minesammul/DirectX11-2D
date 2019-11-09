#include "stdafx.h"
#include "ScriptMgr.h"

#include "AttackBoxScript.h"
#include "BottomWallCollisionScript.h"
#include "BulletScript.h"
#include "CameraScript.h"
#include "EffectScript.h"
#include "EventQueueScript.h"
#include "EventScript.h"
#include "GravityScript.h"
#include "HilightScript.h"
#include "ItemScript.h"
#include "LeftBottomWallCollisionScript.h"
#include "LeftWallCollisionScript.h"
#include "MonsterResponseScript.h"
#include "MonsterScript.h"
#include "ObjectEditScript.h"
#include "PlatformCollisionScript.h"
#include "PlatformLeftCollisionScript.h"
#include "PlatformRightCollisionScript.h"
#include "PlayerScript.h"
#include "PotalScript.h"
#include "PotalVerticalScript.h"
#include "RightBottomWallCollisionScript.h"
#include "RightWallCollisionScript.h"
#include "TextureScript.h"
#include "TileMapScript.h"
#include "TileScript.h"
#include "TopWallCollisionScript.h"
#include "UIScript.h"
#include "Z1MonsterExistFindScript.h"
#include "Z2FadeScript.h"
#include "Z3CameraBottomCheckScript.h"
#include "Z4CameraFrameScript.h"
#include "Z5CameraTopCheckScript.h"
#include "Z6CameraRightCheckScript.h"
#include "Z7CameraLeftCheckScript.h"
#include "Z8BackgroundUVAniScript.h"
#include "Z9ButtonClickScript.h"
#include "ZZ1MouseTraceScript.h"
#include "ZZ2AfterImageScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"AttackBoxScript");
	_vec.push_back(L"BottomWallCollisionScript");
	_vec.push_back(L"BulletScript");
	_vec.push_back(L"CameraScript");
	_vec.push_back(L"EffectScript");
	_vec.push_back(L"EventQueueScript");
	_vec.push_back(L"EventScript");
	_vec.push_back(L"GravityScript");
	_vec.push_back(L"HilightScript");
	_vec.push_back(L"ItemScript");
	_vec.push_back(L"LeftBottomWallCollisionScript");
	_vec.push_back(L"LeftWallCollisionScript");
	_vec.push_back(L"MonsterResponseScript");
	_vec.push_back(L"MonsterScript");
	_vec.push_back(L"ObjectEditScript");
	_vec.push_back(L"PlatformCollisionScript");
	_vec.push_back(L"PlatformLeftCollisionScript");
	_vec.push_back(L"PlatformRightCollisionScript");
	_vec.push_back(L"PlayerScript");
	_vec.push_back(L"PotalScript");
	_vec.push_back(L"PotalVerticalScript");
	_vec.push_back(L"RightBottomWallCollisionScript");
	_vec.push_back(L"RightWallCollisionScript");
	_vec.push_back(L"TextureScript");
	_vec.push_back(L"TileMapScript");
	_vec.push_back(L"TileScript");
	_vec.push_back(L"TopWallCollisionScript");
	_vec.push_back(L"UIScript");
	_vec.push_back(L"Z1MonsterExistFindScript");
	_vec.push_back(L"Z2FadeScript");
	_vec.push_back(L"Z3CameraBottomCheckScript");
	_vec.push_back(L"Z4CameraFrameScript");
	_vec.push_back(L"Z5CameraTopCheckScript");
	_vec.push_back(L"Z6CameraRightCheckScript");
	_vec.push_back(L"Z7CameraLeftCheckScript");
	_vec.push_back(L"Z8BackgroundUVAniScript");
	_vec.push_back(L"Z9ButtonClickScript");
	_vec.push_back(L"ZZ1MouseTraceScript");
	_vec.push_back(L"ZZ2AfterImageScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"AttackBoxScript" == _strScriptName)
		return new CAttackBoxScript;
	if (L"BottomWallCollisionScript" == _strScriptName)
		return new CBottomWallCollisionScript;
	if (L"BulletScript" == _strScriptName)
		return new CBulletScript;
	if (L"CameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"EffectScript" == _strScriptName)
		return new CEffectScript;
	if (L"EventQueueScript" == _strScriptName)
		return new CEventQueueScript;
	if (L"EventScript" == _strScriptName)
		return new CEventScript;
	if (L"GravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"HilightScript" == _strScriptName)
		return new CHilightScript;
	if (L"ItemScript" == _strScriptName)
		return new CItemScript;
	if (L"LeftBottomWallCollisionScript" == _strScriptName)
		return new CLeftBottomWallCollisionScript;
	if (L"LeftWallCollisionScript" == _strScriptName)
		return new CLeftWallCollisionScript;
	if (L"MonsterResponseScript" == _strScriptName)
		return new CMonsterResponseScript;
	if (L"MonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"ObjectEditScript" == _strScriptName)
		return new CObjectEditScript;
	if (L"PlatformCollisionScript" == _strScriptName)
		return new CPlatformCollisionScript;
	if (L"PlatformLeftCollisionScript" == _strScriptName)
		return new CPlatformLeftCollisionScript;
	if (L"PlatformRightCollisionScript" == _strScriptName)
		return new CPlatformRightCollisionScript;
	if (L"PlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"PotalScript" == _strScriptName)
		return new CPotalScript;
	if (L"PotalVerticalScript" == _strScriptName)
		return new CPotalVerticalScript;
	if (L"RightBottomWallCollisionScript" == _strScriptName)
		return new CRightBottomWallCollisionScript;
	if (L"RightWallCollisionScript" == _strScriptName)
		return new CRightWallCollisionScript;
	if (L"TextureScript" == _strScriptName)
		return new CTextureScript;
	if (L"TileMapScript" == _strScriptName)
		return new CTileMapScript;
	if (L"TileScript" == _strScriptName)
		return new CTileScript;
	if (L"TopWallCollisionScript" == _strScriptName)
		return new CTopWallCollisionScript;
	if (L"UIScript" == _strScriptName)
		return new CUIScript;
	if (L"Z1MonsterExistFindScript" == _strScriptName)
		return new CZ1MonsterExistFindScript;
	if (L"Z2FadeScript" == _strScriptName)
		return new CZ2FadeScript;
	if (L"Z3CameraBottomCheckScript" == _strScriptName)
		return new CZ3CameraBottomCheckScript;
	if (L"Z4CameraFrameScript" == _strScriptName)
		return new CZ4CameraFrameScript;
	if (L"Z5CameraTopCheckScript" == _strScriptName)
		return new CZ5CameraTopCheckScript;
	if (L"Z6CameraRightCheckScript" == _strScriptName)
		return new CZ6CameraRightCheckScript;
	if (L"Z7CameraLeftCheckScript" == _strScriptName)
		return new CZ7CameraLeftCheckScript;
	if (L"Z8BackgroundUVAniScript" == _strScriptName)
		return new CZ8BackgroundUVAniScript;
	if (L"Z9ButtonClickScript" == _strScriptName)
		return new CZ9ButtonClickScript;
	if (L"ZZ1MouseTraceScript" == _strScriptName)
		return new CZZ1MouseTraceScript;
	if (L"ZZ2AfterImageScript" == _strScriptName)
		return new CZZ2AfterImageScript;
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::ATTACKBOXSCRIPT:
		return L"AttackBoxScript";
		break;

	case SCRIPT_TYPE::BOTTOMWALLCOLLISIONSCRIPT:
		return L"BottomWallCollisionScript";
		break;

	case SCRIPT_TYPE::BULLETSCRIPT:
		return L"BulletScript";
		break;

	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CameraScript";
		break;

	case SCRIPT_TYPE::EFFECTSCRIPT:
		return L"EffectScript";
		break;

	case SCRIPT_TYPE::EVENTQUEUESCRIPT:
		return L"EventQueueScript";
		break;

	case SCRIPT_TYPE::EVENTSCRIPT:
		return L"EventScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"GravityScript";
		break;

	case SCRIPT_TYPE::HILIGHTSCRIPT:
		return L"HilightScript";
		break;

	case SCRIPT_TYPE::ITEMSCRIPT:
		return L"ItemScript";
		break;

	case SCRIPT_TYPE::LEFTBOTTOMWALLCOLLISIONSCRIPT:
		return L"LeftBottomWallCollisionScript";
		break;

	case SCRIPT_TYPE::LEFTWALLCOLLISIONSCRIPT:
		return L"LeftWallCollisionScript";
		break;

	case SCRIPT_TYPE::MONSTERRESPONSESCRIPT:
		return L"MonsterResponseScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"MonsterScript";
		break;

	case SCRIPT_TYPE::OBJECTEDITSCRIPT:
		return L"ObjectEditScript";
		break;

	case SCRIPT_TYPE::PLATFORMCOLLISIONSCRIPT:
		return L"PlatformCollisionScript";
		break;

	case SCRIPT_TYPE::PLATFORMLEFTCOLLISIONSCRIPT:
		return L"PlatformLeftCollisionScript";
		break;

	case SCRIPT_TYPE::PLATFORMRIGHTCOLLISIONSCRIPT:
		return L"PlatformRightCollisionScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"PlayerScript";
		break;

	case SCRIPT_TYPE::POTALSCRIPT:
		return L"PotalScript";
		break;

	case SCRIPT_TYPE::POTALVERTICALSCRIPT:
		return L"PotalVerticalScript";
		break;

	case SCRIPT_TYPE::RIGHTBOTTOMWALLCOLLISIONSCRIPT:
		return L"RightBottomWallCollisionScript";
		break;

	case SCRIPT_TYPE::RIGHTWALLCOLLISIONSCRIPT:
		return L"RightWallCollisionScript";
		break;

	case SCRIPT_TYPE::TEXTURESCRIPT:
		return L"TextureScript";
		break;

	case SCRIPT_TYPE::TILEMAPSCRIPT:
		return L"TileMapScript";
		break;

	case SCRIPT_TYPE::TILESCRIPT:
		return L"TileScript";
		break;

	case SCRIPT_TYPE::TOPWALLCOLLISIONSCRIPT:
		return L"TopWallCollisionScript";
		break;

	case SCRIPT_TYPE::UISCRIPT:
		return L"UIScript";
		break;

	case SCRIPT_TYPE::Z1MONSTEREXISTFINDSCRIPT:
		return L"Z1MonsterExistFindScript";
		break;

	case SCRIPT_TYPE::Z2FADESCRIPT:
		return L"Z2FadeScript";
		break;

	case SCRIPT_TYPE::Z3CAMERABOTTOMCHECKSCRIPT:
		return L"Z3CameraBottomCheckScript";
		break;

	case SCRIPT_TYPE::Z4CAMERAFRAMESCRIPT:
		return L"Z4CameraFrameScript";
		break;

	case SCRIPT_TYPE::Z5CAMERATOPCHECKSCRIPT:
		return L"Z5CameraTopCheckScript";
		break;

	case SCRIPT_TYPE::Z6CAMERARIGHTCHECKSCRIPT:
		return L"Z6CameraRightCheckScript";
		break;

	case SCRIPT_TYPE::Z7CAMERALEFTCHECKSCRIPT:
		return L"Z7CameraLeftCheckScript";
		break;

	case SCRIPT_TYPE::Z8BACKGROUNDUVANISCRIPT:
		return L"Z8BackgroundUVAniScript";
		break;

	case SCRIPT_TYPE::Z9BUTTONCLICKSCRIPT:
		return L"Z9ButtonClickScript";
		break;

	case SCRIPT_TYPE::ZZ1MOUSETRACESCRIPT:
		return L"ZZ1MouseTraceScript";
		break;

	case SCRIPT_TYPE::ZZ2AFTERIMAGESCRIPT:
		return L"ZZ2AfterImageScript";
		break;

	}
	return nullptr;
}