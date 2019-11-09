#pragma once
#include "Component.h"

class CTransform :
	public CComponent
{
private:
	Vec3		m_vLocalPos;
	Vec3		m_vLocalScale;
	Vec3		m_vLocalRot;


	Matrix		m_matWorld;

public:
	void SetLocalPos(const Vec3& _vPos) { m_vLocalPos = _vPos; }
	void SetLocalScale(const Vec3& _vScale) { m_vLocalScale = _vScale; }
	void SetLocalRot(const Vec3& _vRot) { m_vLocalRot = _vRot; }
	
	const Vec3& GetLocalPos() {		return m_vLocalPos ; }
	const Vec3& GetLocalScale() {	return m_vLocalScale; }
	const Vec3& GetLocalRot() {		return m_vLocalRot ; }

	const Matrix& GetWorldMat() { return m_matWorld; }

public:
	virtual void update();
	virtual void finalupdate();
	void UpdateData();

	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

public:
	CLONE(CTransform);
	
public:
	CTransform();
	virtual ~CTransform();
};

