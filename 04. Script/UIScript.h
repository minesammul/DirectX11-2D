#pragma once
#include <Script.h>

class CUIScript : public CScript
{
private:
	int maxHp;
	int nowHp;

	Vector3 maxHpBarScale;
	Vector3 maxHPBarPosition;

public:
	CUIScript();
	~CUIScript();

private:
	void ReadjustHpBarPosition(void);
	void RepeatHpBarAnimation(void);

public:
	virtual void start();
	virtual void update();

	void SetHp(int maxHp, int nowHp)
	{
		this->maxHp = maxHp;
		this->nowHp = nowHp;
	}
};

