#pragma once
#include "Script.h"

enum class COLOR_TYPE
{
	R,
	G,
	B,
	END,
};

class CHilightScript :
	public CScript
{
private:
	float		m_fAddRatio;	
	float		m_fCurAddRatio;
	int			m_iAddDir;

	float		m_fSubRatio;
	float		m_fCurSubRatio;

	float		m_fDuration;
	COLOR_TYPE	m_eType;

	bool		m_bOn;
	
public:
	virtual void update();	

public:
	void EffectOn() { m_bOn = true; }

	CLONE(CHilightScript);
public:
	CHilightScript();
	virtual ~CHilightScript();
};

