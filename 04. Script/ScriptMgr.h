#pragma once

#include <vector>
#include <string>

enum class SCRIPT_TYPE
{
	ATTACKBOXSCRIPT,
	BOTTOMWALLCOLLISIONSCRIPT,
	BULLETSCRIPT,
	CAMERASCRIPT,
	EFFECTSCRIPT,
	EVENTQUEUESCRIPT,
	EVENTSCRIPT,
	GRAVITYSCRIPT,
	HILIGHTSCRIPT,
	ITEMSCRIPT,
	LEFTBOTTOMWALLCOLLISIONSCRIPT,
	LEFTWALLCOLLISIONSCRIPT,
	MONSTERRESPONSESCRIPT,
	MONSTERSCRIPT,
	OBJECTEDITSCRIPT,
	PLATFORMCOLLISIONSCRIPT,
	PLATFORMLEFTCOLLISIONSCRIPT,
	PLATFORMRIGHTCOLLISIONSCRIPT,
	PLAYERSCRIPT,
	POTALSCRIPT,
	POTALVERTICALSCRIPT,
	RIGHTBOTTOMWALLCOLLISIONSCRIPT,
	RIGHTWALLCOLLISIONSCRIPT,
	TEXTURESCRIPT,
	TILEMAPSCRIPT,
	TILESCRIPT,
	TOPWALLCOLLISIONSCRIPT,
	UISCRIPT,
	Z1MONSTEREXISTFINDSCRIPT,
	Z2FADESCRIPT,
	Z3CAMERABOTTOMCHECKSCRIPT,
	Z4CAMERAFRAMESCRIPT,
	Z5CAMERATOPCHECKSCRIPT,
	Z6CAMERARIGHTCHECKSCRIPT,
	Z7CAMERALEFTCHECKSCRIPT,
	Z8BACKGROUNDUVANISCRIPT,
	Z9BUTTONCLICKSCRIPT,
	ZZ1MOUSETRACESCRIPT,
	ZZ2AFTERIMAGESCRIPT,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static const wchar_t * GetScriptName(CScript * _pScript);
};