#pragma once

// union °ø¿ëÃ¼
union COL_ID
{
	struct {
		DWORD left;
		DWORD right;
	};
	unsigned long long ID;
};

class CCollider2D;
class CCollider3D;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	UINT							m_arrCheck[MAX_LAYER];
	map<unsigned long long, bool>	m_mapID2D;
	map<unsigned long long, bool>	m_mapID3D;


public:
	void update();

public:
	void CollisionCheck(const wstring& _strLayerName1, const wstring& _strLayerName2);
	void CollisionCheck(int _iLayerIdx1, int _iLayerIdx2);
	
	void ClearCheck() { memset(m_arrCheck, 0, sizeof(UINT) * MAX_LAYER); }

	bool IsCollisionLayers(const wstring& _strLayerName1, const wstring& _strLayerName2);

	void CollisionUnCheck(const wstring& _strLayerName1, const wstring& _strLayerName2);

private:
	void CollisionGroup(int _leftIdx, int _rightIdx);	
	
	// 2D Collision Check
	bool IsCollision(CCollider2D* _pLeft, CCollider2D* _pRight);
	bool CollisionRect(CCollider2D* _pLeft, CCollider2D* _pRight);
	bool CollisionCircle(CCollider2D* _pLeft, CCollider2D* _pRight);

	// 3D Collision Check
	bool IsCollision(CCollider3D* _pLeft, CCollider3D* _pRight);
	bool CollisionCube(CCollider3D* _pLeft, CCollider3D* _pRight);
	bool CollisionSphere(CCollider3D* _pLeft, CCollider3D* _pRight);
};

