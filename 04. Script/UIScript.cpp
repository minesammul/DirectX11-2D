#include "stdafx.h"
#include "UIScript.h"


CUIScript::CUIScript():
	CScript((UINT)SCRIPT_TYPE::UISCRIPT)
{
	maxHp = 1;
	nowHp = 1;
}


CUIScript::~CUIScript()
{
}

void CUIScript::ReadjustHpBarPosition(void)
{
	float nowHpBarScaleValue = maxHpBarScale.x / maxHp;
	nowHpBarScaleValue *= nowHp;

	Vector3 nowHpBarScale = maxHpBarScale;
	nowHpBarScale.x = nowHpBarScaleValue;

	float nowHpBarPositionValue = maxHpBarScale.x - nowHpBarScaleValue;
	nowHpBarPositionValue /= 2;
	Vector3 nowHpBarPosition = maxHPBarPosition;
	nowHpBarPosition.x -= nowHpBarPositionValue;

	vector<CGameObject*> childObject = Object()->GetChild();
	for (int index = 0; index < childObject.size(); index++)
	{
		if (childObject[index]->GetName().compare(L"HpBar") == 0)
		{
			childObject[index]->Transform()->SetLocalScale(nowHpBarScale);
			childObject[index]->Transform()->SetLocalPos(nowHpBarPosition);
		}
		if (childObject[index]->GetName().compare(L"HpBarAnimation") == 0)
		{
			Vector3 nowHpBarAnimationPosition = nowHpBarPosition;
			nowHpBarAnimationPosition.x += nowHpBarScale.x / 2;
			nowHpBarAnimationPosition.x += childObject[index]->Transform()->GetLocalScale().x / 2;
			childObject[index]->Transform()->SetLocalPos(nowHpBarAnimationPosition);
		}
	}
}

void CUIScript::RepeatHpBarAnimation(void)
{
	vector<CGameObject*> childObject = Object()->GetChild();
	for (int index = 0; index < childObject.size(); index++)
	{
		if (childObject[index]->GetName().compare(L"HpBarAnimation") == 0)
		{
			if (childObject[index]->Animator2D()->GetCurAnim()->IsPlay() == false)
			{
				childObject[index]->Animator2D()->GetCurAnim()->Play();
			}
		}
	}
}

void CUIScript::start()
{
	vector<CGameObject*> childObject = Object()->GetChild();
	for (int index = 0; index < childObject.size(); index++)
	{
		if (childObject[index]->GetName().compare(L"HpBar") == 0)
		{
			maxHpBarScale = childObject[index]->Transform()->GetLocalScale();
			maxHPBarPosition = childObject[index]->Transform()->GetLocalPos();
			break;
		}
	}
}

void CUIScript::update()
{
	if (nowHp <= 0)
	{
		vector<CGameObject*> childObject = Object()->GetChild();
		for (int index = 0; index < childObject.size(); index++)
		{
			if (childObject[index]->GetName().compare(L"HpBar") == 0)
			{
				childObject[index]->Active(false);
			}
			if (childObject[index]->GetName().compare(L"HpBarAnimation") == 0)
			{
				childObject[index]->Active(false);
			}
		}
		return;
	}

	ReadjustHpBarPosition();
	RepeatHpBarAnimation();
}
