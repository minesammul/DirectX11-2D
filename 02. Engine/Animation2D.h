#pragma once
#include "Entity.h"

#include "ResPtr.h"
#include "Texture.h"

// Animation Frame
struct tAnim2DFrm
{
	CResPtr<CTexture>   pTex;
	Vec2				vLT;
	Vec2				vSize;	
	float				fTerm;
	Vec2 LTOffset;
};

class CAnimation2D :
	public CEntity
{
private:
	vector<tAnim2DFrm>  m_vecFrm;
	int					m_iCurFrm;	
	float				m_fAccTime;

	bool				m_bPlay;
	bool				m_bFinish;

	int repeatStartFrame;
	int repeatEndFrame;

public:
	int GetMaxFrameCount() { return m_vecFrm.size(); }
	int GetNowFrameCount() { return m_iCurFrm; }
	tAnim2DFrm GetNowFrameData() { return m_vecFrm[m_iCurFrm]; }
	void SetNowFrameOffset(Vec2 offset);

	int GetRepeatStartFrame(void) { return repeatStartFrame; }
	void SetRepeatStartFrame(int frame) { repeatStartFrame = frame; }

	int GetRepeatEndFrame(void) { return repeatEndFrame; }
	void SetRepeatEndFrame(int frame) { repeatEndFrame = frame; }

public:
	void update();
	void lateupdate();
	void finalupdate();
	void UpdateData();

public:
	void Create(const wstring& _strName, CResPtr<CTexture> _pTex, Vec2 _vLT, Vec2 _vCropSize, int _iFrmCount, float _fTerm);
	void Create(const wstring& _strName, CResPtr<CTexture> _pTex, Vec2 _vLT, Vec2 _vCropSize, Vec2 offset, int _iFrmCount, float _fTerm);
	void Create(const wstring& _strName, const wstring& _strFolderPath, float _fTerm);
	void Play();
	void Pause() { m_bPlay = false; }

	bool IsFinish() { return m_bFinish; }
	bool IsPlay() { return m_bPlay; }

	void SetFrm(UINT _iFrm) {
		m_iCurFrm = _iFrm; m_fAccTime = 0.f;
		if (m_vecFrm.size() - 1 != m_iCurFrm)
			m_bFinish = false;
		else
			m_bFinish = true;
	}


	void SaveToScene(FILE* _pFile);
	void LoadFromScene(FILE* _pFile);

public:
	static void ClearRegister();

public:
	CLONE(CAnimation2D);

public:
	CAnimation2D();
	virtual ~CAnimation2D();
};

