#include "stdafx.h"
#include "ItemSwordKindStrategy.h"


ItemSwordKindStrategy::ItemSwordKindStrategy()
{
	swordState = SWORD_STATE::UP;
}


ItemSwordKindStrategy::~ItemSwordKindStrategy()
{
}

void ItemSwordKindStrategy::Action(ItemKind* itemKind)
{
	Vec3 itemPosition = itemKind->GetItemPosition();

	if (swordState == SWORD_STATE::UP)
	{
		swordState = SWORD_STATE::DOWN;
		itemPosition.z = -0.1;
	}
	else if (swordState == SWORD_STATE::DOWN)
	{
		swordState = SWORD_STATE::UP;
		itemPosition.z = 0.1;
	}

	itemKind->SetItemPosition(itemPosition);
}

void ItemSwordKindStrategy::Update(ItemKind* itemKind)
{
	Vec3 nowItemDirection = itemKind->GetItemDirection();
	Vec3 nowMouseDirection = itemKind->GetMouseDirection();

	nowItemDirection = XMVector3Normalize(nowItemDirection);
	nowMouseDirection = XMVector2Normalize(nowMouseDirection);

	Vec3 dotValue = XMVector3Dot(nowItemDirection, nowMouseDirection);
	float radian = acos(dotValue.x);


	Vec3 itemRotate = Vec3(0.f, 0.f, 0.f);


	if (nowMouseDirection.x > 0)
	{
		radian = 3.14 * 2 - radian;

		if (swordState == SWORD_STATE::UP)
		{
			if (radian < (3.14 * 2) / 4 * 3)
			{
				radian = (3.14 * 2) / 4 * 3;
			}

			itemRotate.z = XMConvertToRadians(60.f);
		}
		else if(swordState == SWORD_STATE::DOWN)
		{
			if (radian > (3.14 * 2) / 4 * 3)
			{
				radian = (3.14 * 2) / 4 * 3;
			}

			itemRotate.z = XMConvertToRadians(300.f);
		}
	}
	else
	{
		if (swordState == SWORD_STATE::UP)
		{
			if (radian > (3.14 * 2) / 4 * 1)
			{
				radian = (3.14 * 2) / 4 * 1;
			}

			itemRotate.z = XMConvertToRadians(300.f);
		}
		else if (swordState == SWORD_STATE::DOWN)
		{
			if (radian < (3.14 * 2) / 4 * 1)
			{
				radian = (3.14 * 2) / 4 * 1;
			}

			itemRotate.z = XMConvertToRadians(60.f);
		}
	}

	Vec3 itemAxisRotate = Vec3(0.f, 0.f, radian);
	itemKind->SetItemAxisRotate(itemAxisRotate);
	
	itemKind->SetItemRotate(itemRotate);
}
