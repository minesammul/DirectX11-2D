
// 03. Tool.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ToolApp.h"
#include "MainFrm.h"
#include "HierachyView.h"

#include <core.h>
#include <TimeMgr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolApp

BEGIN_MESSAGE_MAP(CToolApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CToolApp::OnAppAbout)
END_MESSAGE_MAP()


// CToolApp 생성

CToolApp::CToolApp() noexcept
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 응용 프로그램을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("My03Tool.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CToolApp 개체입니다.

CToolApp theApp;


// CToolApp 초기화

BOOL CToolApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	//_CrtSetBreakAlloc(122303);



	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));


	// 주 창을 만들기 위해 이 코드에서는 새 프레임 창 개체를
	// 만든 다음 이를 응용 프로그램의 주 창 개체로 설정합니다.
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 프레임을 만들어 리소스와 함께 로드합니다.
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);


	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	
	HWND hGameViewHwnd = ((CMainFrame*)pFrame)->GetGameView()->m_hWnd;

	// Engine 초기화
	CCore::GetInst()->init(hGameViewHwnd, true);

	

	// Engine 초기화 후에 FrameWindow 초기화
	((CMainFrame*)pFrame)->init();
	CreateTestScene();

	// HierachyView 초기화
	CHierachyView* pView = (CHierachyView*)((CMainFrame*)pFrame)->GetHierachyView();
	pView->init_object();
	return TRUE;
}

int CToolApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

#include <ResMgr.h>
#include <Texture.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneMgr.h>
#include <CollisionMgr.h>

#include <Transform.h>
#include <MeshRender.h>
#include <Camera.h>
#include <Animator2D.h>
#include <Collider2D.h>

#include <PlayerScript.h>
#include <HilightScript.h>

void CToolApp::CreateTestScene()
{
	return;

	CResMgr::GetInst()->Load<CTexture>(L"Player", L"Texture\\00.png");
	CResMgr::GetInst()->Load<CTexture>(L"Effect", L"Texture\\Effect.png");
	CResMgr::GetInst()->Load<CTexture>(L"Link", L"Texture\\Animation\\Link\\link_0.png");


	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	pCurScene->AddLayer(L"Player", 1);
	pCurScene->AddLayer(L"Bullet", 2);
	pCurScene->AddLayer(L"Monster", 3);

	// Camera Object 만들기
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);

	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetFOV(XM_PI / 4.f);
	pCamObj->Camera()->SetScale(1.f);
	pCamObj->Camera()->CheckLayer(pCurScene->FindLayer(L"Player")->GetLayerIdx());
	pCamObj->Camera()->CheckLayer(pCurScene->FindLayer(L"Bullet")->GetLayerIdx());
	pCamObj->Camera()->CheckLayer(pCurScene->FindLayer(L"Monster")->GetLayerIdx());
	pCamObj->Camera()->CheckLayer(pCurScene->FindLayer(L"Default")->GetLayerIdx());

	pCurScene->AddObject(L"Default", pCamObj);

	// Player Object 만들기
	CGameObject* pParent = new CGameObject;
	pParent->SetName(L"Player");

	CTransform* pTransform = new CTransform;
	CMeshRender* pMeshRender = new CMeshRender;
	CCollider2D* pCollider2D = new CCollider2D;
	CAnimator2D* pAnimator2D = new CAnimator2D;

	pTransform->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pTransform->SetLocalScale(Vec3(100.f, 100.f, 1.f));
	pTransform->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));	
	pMeshRender->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &CResMgr::GetInst()->FindRes<CTexture>(L"Player"));
	
	// Animation 로드
	CResPtr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"Link");
		
	pAnimator2D->AddAnimation(L"Player_Right_Walk", pTex, Vec2(0, 455), Vec2(60, 65), 10, 0.08f);
	pAnimator2D->PlayAnimation(L"Player_Right_Walk", false);


	pAnimator2D->SetAnimPlayFirst(false);

	pParent->AddComponent(pTransform);
	pParent->AddComponent(pMeshRender);
	pParent->AddComponent(pCollider2D);
	pParent->AddComponent(pAnimator2D);
	pParent->AddComponent(new CPlayerScript);
	pParent->AddComponent(new CHilightScript);
	

	// ChildObject
	CGameObject* pChild = new CGameObject;
	pChild->SetName(L"Child");

	pTransform = new CTransform;
	pMeshRender = new CMeshRender;
	pCollider2D = new CCollider2D;

	pTransform->SetLocalPos(Vec3(2.f, 0.f, 0.f));
	pTransform->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	pTransform->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TextureMtrl"));
	pMeshRender->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &CResMgr::GetInst()->FindRes<CTexture>(L"Player"));

	pChild->AddComponent(pTransform);
	pChild->AddComponent(pMeshRender);
	pChild->AddComponent(pCollider2D);
	
	pParent->AddChild(pChild);
	pCurScene->AddObject(L"Player", pChild);
	pCurScene->AddObject(L"Player", pParent);
	
	wchar_t szName[50] = {};
	for (int i = 0; i < 5; ++i)
	{
		wsprintf(szName, L"CloneObject_%d", i, 50);

		CGameObject* pClone = pChild->Clone();
		pClone->SetName(szName);
		pClone->Transform()->SetLocalPos(Vec3(-500.f + 150.f * (float)i, 250.f, 500.f));
		pClone->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		pCurScene->AddObject(L"Monster", pClone);
	}	

	// 충돌 지정
	CCollisionMgr::GetInst()->CollisionCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->CollisionCheck(L"Default", L"Player");
	CCollisionMgr::GetInst()->CollisionCheck(L"Default", L"Monster");

	if (CCore::GetInst()->GetState() == SCENE_STATE::PLAY)
	{
		pCurScene->awake();
		pCurScene->start();
	}
}

// CToolApp 메시지 처리기
BOOL CToolApp::OnIdle(LONG lCount)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CCore::GetInst()->progress();

	((CMainFrame*)m_pMainWnd)->update();	

	return CWinApp::OnIdle(0); // 지연시간 제거
}



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CToolApp 메시지 처리기



