#include "stdafx.h"
#include "ItemImage.h"
#include <ResPtr.h>
#include <Texture.h>
#include <ResMgr.h>


ItemImage::ItemImage()
{
}


ItemImage::~ItemImage()
{
}

void ItemImage::Action(CItemScript* item)
{

}

void ItemImage::Init(CItemScript * item)
{
	//임시코드 나중에 플레이어한테 아이템 정보를 받아와서 이미지를 바뀌야한다.	
	CResPtr<CTexture> itemTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Item\\BasicShortSword\\BasicShortSword.png");
	Vec3 itemScale = item->Object()->Transform()->GetLocalScale();
	itemScale.x = 100.f;
	itemScale.y = 100.f;
	item->Object()->Transform()->SetLocalScale(itemScale);

	float textureWitdh = itemTexture->GetWidth();
	float textureHeight = itemTexture->GetHeight();

	float textureHegihtRation = textureHeight / textureWitdh;
	itemScale = item->Object()->Transform()->GetLocalScale();
	itemScale.y *= textureHegihtRation;

	itemScale.x /= 3.5f;
	itemScale.y /= 3.5f;

	Vec3 rotateObjectScale = item->Object()->GetParent()->Transform()->GetLocalScale();
	Vec3 playerObjectScale = item->Object()->GetParent()->GetParent()->Transform()->GetLocalScale();

	itemScale.x /= rotateObjectScale.x;
	itemScale.y /= rotateObjectScale.y;

	itemScale.x /= playerObjectScale.x;
	itemScale.y /= playerObjectScale.y;

	item->Object()->Transform()->SetLocalScale(itemScale);


	Vec3 playerObjectPosition = item->Object()->GetParent()->GetParent()->Transform()->GetLocalPos();

	Vec3 itemPosition = Vec3(0.f, 15.f, -0.1f);

	item->Object()->Transform()->SetLocalPos(itemPosition);
}

void ItemImage::Update(CItemScript * item)
{
	item->Object()->MeshRender()->SetMaterial(item->GetItemMtrl());
	if (nullptr != item->GetItemMtrl())
	{
		CResPtr<CTexture> itemTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Item\\BasicShortSword\\BasicShortSword.png");
		item->GetItemMtrl()->SetData(SHADER_PARAM::TEX_0, &itemTexture);
	}
}
