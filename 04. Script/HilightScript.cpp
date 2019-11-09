#include "stdafx.h"
#include "HilightScript.h"

CHilightScript::CHilightScript()
	: CScript((UINT)SCRIPT_TYPE::HILIGHTSCRIPT)
	, m_fAddRatio(2.5f)
	, m_fCurAddRatio(1.f)
	, m_iAddDir(1)
	, m_fSubRatio(0.8f)
	, m_fCurSubRatio(1.f)
	, m_fDuration(0.2f)
	, m_eType(COLOR_TYPE::R)
{
}

CHilightScript::~CHilightScript()
{
}

void CHilightScript::update()
{
	float fAddSpeed = (m_fAddRatio - 1.f) * 2.f * (1 / m_fDuration);

	if (m_bOn)
	{
		m_fCurAddRatio += m_iAddDir * DT * fAddSpeed;

		if (1 == m_iAddDir)
		{
			if (m_fCurAddRatio >= m_fAddRatio)
			{
				m_fCurAddRatio -= (m_fCurAddRatio - m_fAddRatio);
				m_iAddDir = -1;
			}
		}
		else
		{
			if (m_fCurAddRatio <= 1.f)
			{
				m_fCurAddRatio = 1.f;
				m_iAddDir = 1;
				m_bOn = false;
			}
		}		
	}

	Vec2 vRatio = Vec2(m_fCurAddRatio, m_fCurSubRatio);
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::VEC2_0, &vRatio);
}
