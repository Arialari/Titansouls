#include "stdafx.h"
#include "Slime.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SlimeShadow.h"
#include "ObjMgr.h"

const int CSlime::m_iSizeStartX[5] = { 0, 10, 15, 18, 20 };
const int CSlime::m_iSize[5] = { 8, 5, 3, 2, 1 };
CSlime::CSlime()
	:m_pShadow(nullptr), m_iSizeLv(0)
{
}

CSlime::~CSlime()
{
	Release();
}

void CSlime::Initialize()
{
	m_tInfo.iCX = DEFAULTCX * 7;
	m_tInfo.iCY = DEFAULTCY * 5;
	Update_Rect();
	m_pImageKey = L"Sludge";
	m_eRenderID = RENDERID::OBJECT;
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );

	m_pShadow = static_cast<CSlimeShadow*>(CAbstractFactory<CSlimeShadow>::Create( m_tInfo.fX, m_tInfo.fY ));
	CObjMgr::Get_Instance()->Add_Object( m_pShadow, OBJID::SHADOW );
}

int CSlime::Update()
{

	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	return OBJ_NOEVENT;
}

void CSlime::Late_Update()
{
}

void CSlime::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY)
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , m_iSizeStartX[m_iSizeLv] * PIXELCX, 0 
					   , PIXELCX * m_iSize[m_iSizeLv], PIXELCY * m_iSize[m_iSizeLv]
					   , RGB( 255, 0, 255 ) );
	RenderCollision(_DC);
}

void CSlime::Release()
{
}

void CSlime::Update_DamageCollision()
{

}

void CSlime::Update_Dead()
{
}

void CSlime::Update_Pattern()
{
}
