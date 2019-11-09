#pragma once

#include "Component.h"


#include "ResPtr.h"

#include "Mesh.h"
#include "Material.h"

class CMeshRender :
	public CComponent
{
private:
	CResPtr<CMesh>		m_pMesh;
	CResPtr<CMaterial>	m_pMtrl;

public:
	void SetMesh(CResPtr<CMesh>	_pMesh) { m_pMesh = _pMesh; }
	void SetMaterial(CResPtr<CMaterial> _pMtrl) { m_pMtrl = _pMtrl; }

	CResPtr<CMesh> GetMesh() { return m_pMesh; }
	CResPtr<CMaterial> GetCloneMaterial();
	CResPtr<CMaterial> GetSharedMaterial() { return m_pMtrl; }

public:
	virtual void update();
	void render();

	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

	CLONE(CMeshRender);

public:
	CMeshRender();
	virtual ~CMeshRender();
};

