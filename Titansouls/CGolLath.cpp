#include "stdafx.h"
#include "CGolLath.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "GolLathArm.h"
#include "ObjMgr.h"
#include "Player.h"
#include "TitanKillBox.h"

CGolLath::CGolLath()
	:m_fMaxShoulderY( 3.0f ), m_fMaxBodyY( 7.f ), m_fBodyY( 0.f ), m_fShoulderY( 0.f ), m_fRenderModelY( 0.f ), m_fHeadY( 0.f ), m_iAttackStartFrame( 0 ), m_iShieldStartFrame( 0 )
{
	m_bPatterning[0] = false;
	m_bPatterning[1] = false;
}

CGolLath::~CGolLath()
{
}

void CGolLath::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_Gol-Lath.bmp", L"Gol_Lath" );

	m_tInfo.fX = 39.5f * DEFAULTCX;
	m_tInfo.fY = 57.5f * DEFAULTCY;
	m_tInfo.iCX = DEFAULTCX * 4;
	m_tInfo.iCY = DEFAULTCY * 5;
	Update_Rect();
	m_pImageKey = L"Gol_Lath";
	m_eRenderID = RENDERID::OBJECT;
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );

	
	m_pArm[LEFT] = static_cast<CGolLathArm*>(CAbstractFactory<CGolLathArm>::Create( m_tInfo.fX - (DEFAULTCX * 3), m_tInfo.fY + (DEFAULTCY * 3) ));
	m_pArm[LEFT]->Set_IsFliped( false );
	m_pArm[LEFT]->Set_pGolLath( this );
	m_pArm[RIGHT] = static_cast<CGolLathArm*>(CAbstractFactory<CGolLathArm>::Create( m_tInfo.fX + (DEFAULTCX * 3), m_tInfo.fY + (DEFAULTCY * 3) ));
	m_pArm[RIGHT]->Set_IsFliped( true );
	m_pArm[RIGHT]->Set_pGolLath( this );
	CObjMgr::Get_Instance()->Add_Object( m_pArm[LEFT], OBJID::TITAN );
	CObjMgr::Get_Instance()->Add_Object( m_pArm[RIGHT], OBJID::TITAN );
	m_pKillBox = static_cast<CTitanKillBox*>(CAbstractFactory<CTitanKillBox>::Create( m_tInfo.fX, m_tInfo.fY + (DEFAULTCY * 1.3f) ));
	m_pKillBox->Set_iC( DEFAULTCX, DEFAULTCY );
	m_pKillBox->Set_Titan( this );
	CObjMgr::Get_Instance()->Add_Object( m_pKillBox, OBJID::TITANKILLBOX );
}

int CGolLath::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	if ( !m_bDead )
	{
		Update_Pattern();
		Update_DamageCollision();
		Update_Animation_Frame();
	}
	else
	{
		Update_Dead();
	}

	

	return OBJ_NOEVENT;
}

void CGolLath::Late_Update()
{
}

void CGolLath::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );
	if ( m_iPatternFrame >= 140 )
	{
		m_fBodyY = m_fMaxBodyY * 0.7f;
		m_fShoulderY = m_fMaxShoulderY;
	}
	else if ( m_iPatternFrame > 30 )
	{
		m_fShoulderY = m_fMaxShoulderY;

		if ( m_iPatternFrame >= 80 )
		{
			m_fBodyY = m_fMaxBodyY - ((m_iPatternFrame - 80) * 0.033f);
		}
		else if ( m_iPatternFrame >= 70 )
		{
			m_fBodyY = m_fMaxBodyY;
		}
		else
		{
			m_fBodyY = m_iPatternFrame * 0.1f;
		}
	}
	else
	{
		m_fShoulderY = m_iPatternFrame * 0.1f;
		m_fBodyY = m_iPatternFrame * 0.1f;
	}
	if ( m_bDead )
	{
		m_iFrameidx = 3;
	}
	else if ( m_iPatternFrame >= 30 )
	{
		m_fHeadY = 2.0f;
	}
	else if ( m_iPatternFrame >= 1 )
	{
		m_fHeadY += 0.0666f;
	}
	if ( m_iPatternFrame == 0 )
	{
		m_iFrameidx = 1;
	}
	else if ( m_iPatternFrame < 150 )
	{
		m_iFrameidx = 4;
	}
	else if ( m_iPatternFrame < 230 )
	{
		m_iFrameidx = 2;

		if ( m_pKillBox )
			m_pKillBox->Set_Active();
	}
	else if ( !m_bDead )
	{
		m_iFrameidx = 0;
	}
	// 어께 왼쪽
	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX - 3 * DEFAULTCX, (int)(m_tRect.top + iScrollY + (DEFAULTCY * 3.5f) - (m_fBodyY * DEFAULTCY))
					   , 3 * DEFAULTCX, (int)(DEFAULTCY * m_fShoulderY)
					   , hMemDC
					   , 9 * PIXELCX, 6 * PIXELCY
					   , PIXELCX * 3, (int)(PIXELCY * m_fShoulderY) // 애니메이션에 따라서 이 값을 변경시키면 밑에서 위로 솟아오르는 느낌을 줄 수 잇다.
					   , RGB( 255, 0, 255 ) );

	// 어께 오른쪽
	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX + 4 * DEFAULTCX, (int)(m_tRect.top + iScrollY + (DEFAULTCY * 3.5f) - (m_fBodyY * DEFAULTCY))
					   , 3 * DEFAULTCX, (int)(DEFAULTCY * m_fShoulderY)
					   , hMemDC
					   , 12 * PIXELCX, 6 * PIXELCY
					   , PIXELCX * 3, (int)(PIXELCY * m_fShoulderY)// 애니메이션에 따라서 이 값을 변경시키면 밑에서 위로 솟아오르는 느낌을 줄 수 잇다.
					   , RGB( 255, 0, 255 ) );


	// 몸통
	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX - DEFAULTCX , (int)(m_tRect.top + iScrollY + (DEFAULTCY * 3) - (m_fBodyY * DEFAULTCY))
					   , 6 * DEFAULTCX, (int)(DEFAULTCY * m_fBodyY)
					   , hMemDC
					   , 0 * PIXELCX, 7 * PIXELCY
					   , PIXELCX * 6, (int)(PIXELCY * m_fBodyY) // 애니메이션에 따라서 이 값을 변경시키면 밑에서 위로 솟아오르는 느낌을 줄 수 잇다.
					   , RGB( 255, 0, 255 ) );
	// 머리
	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX , (int)(m_tRect.top + iScrollY - ((m_fBodyY + 1 - m_fHeadY) * DEFAULTCY))
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , m_iFrameidx * 4 * PIXELCX, m_tFrame.iModelY * PIXELCY
					   , PIXELCX * 4, PIXELCY * 5
					   , RGB( 255, 0, 255 ) );

	RenderCollision( _DC );
}

void CGolLath::Release()
{
}

void CGolLath::Update_Pattern()
{
	if ( !m_bActive )
		return;

	++m_iPatternFrame;
	if ( m_iPatternFrame > 10 )
	{
		if ( m_bPatterning[LEFT] )
		{
			AttackPattern( LEFT );
			ShieldPattern( RIGHT );
			return;
		}
		else if (m_bPatterning[RIGHT] )
		{
			AttackPattern( RIGHT );
			ShieldPattern( LEFT );
			return;
		}
	}


	if ( m_iPatternFrame > 300 ) // 공격 패턴의 시작
	{
		if ( m_tInfo.fX < m_pPlayer->Get_Info().fX ) // RIGHT
		{
			AttackPattern( RIGHT );
			ShieldPattern( LEFT );
		}
		else // LEFT
		{
			AttackPattern( LEFT );
			ShieldPattern( RIGHT );
		}
	}
	else if ( m_iPatternFrame < 30 ) // 손모으기
	{
		float fX = MyMath::FInterpTo( m_pArm[LEFT]->Get_Info().fX, m_tInfo.fX, DELTATIME_S, 8.f );
		float fY = MyMath::FInterpTo( m_pArm[LEFT]->Get_Info().fY, m_pKillBox->Get_Info().fY, DELTATIME_S, 8.f );
		m_pArm[LEFT]->Set_Pos( fX, fY );
		m_pArm[LEFT]->Set_iFrameX( 2 );
	}
}

void CGolLath::AttackPattern( Arm _arm )
{
	if ( !m_bPatterning[_arm] )
	{
		m_bPatterning[_arm] = true;
		m_iAttackStartFrame = m_iPatternFrame;
		m_iShieldStartFrame = m_iPatternFrame; // 한번에 해줘야함 -ㅅ-
	}
		

	if ( m_iPatternFrame < m_iAttackStartFrame + 20 ) //손 올림
	{
		m_pArm[_arm]->Set_iFrameX( 0 );
		float fX = MyMath::FInterpTo( m_pArm[_arm]->Get_Info().fX, m_pPlayer->Get_Info().fX, DELTATIME_S, 8.f );
		float fY = MyMath::FInterpTo( m_pArm[_arm]->Get_Info().fY, m_pPlayer->Get_Info().fY, DELTATIME_S, 8.f );
		m_pArm[_arm]->Set_Pos( fX, fY );
		m_pArm[_arm]->Set_PosZ(DEFAULTCY * 5 * sinf( (m_iPatternFrame - (m_iAttackStartFrame + 0)) * PI / 40 ));
	}
	else if ( m_iPatternFrame < m_iAttackStartFrame + 40 ) // 조준
	{
		float fX = MyMath::FInterpTo( m_pArm[_arm]->Get_Info().fX, m_pPlayer->Get_Info().fX, DELTATIME_S, 8.f );
		float fY = MyMath::FInterpTo( m_pArm[_arm]->Get_Info().fY, m_pPlayer->Get_Info().fY, DELTATIME_S, 8.f );
		m_pArm[_arm]->Set_Pos( fX, fY );
	}
	else if ( m_iPatternFrame < m_iAttackStartFrame + 60 )// 내려찍기!
	{
		m_pArm[_arm]->Set_PosZ( DEFAULTCY * 5 * sinf( (m_iPatternFrame - (m_iAttackStartFrame + 40)) * PI / 40 + PI / 2  ) );
	}
	else
	{
		m_pArm[_arm]->Set_PosZ( 0.f );
	}



	if ( m_iPatternFrame >= m_iAttackStartFrame + 100 )
	{
		m_bPatterning[_arm] = false;
	}
}

void CGolLath::ShieldPattern( Arm _arm )
{
	if ( m_iShieldStartFrame + 15 < m_iPatternFrame )
	{
		float fX = MyMath::FInterpTo( m_pArm[_arm]->Get_Info().fX, m_tInfo.fX, DELTATIME_S, 8.f );
		float fY = MyMath::FInterpTo( m_pArm[_arm]->Get_Info().fY, m_pKillBox->Get_Info().fY, DELTATIME_S, 8.f );
		m_pArm[_arm]->Set_Pos( fX, fY );
		m_pArm[_arm]->Set_iFrameX( 2 );
	}
}

void CGolLath::Update_ColisionRect()
{
	m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1) - 2.5f * DEFAULTCX);
	m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1) + 2.5f * DEFAULTCX);
	m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1) - DEFAULTCY);
}

void CGolLath::Update_Dead()
{
	m_pArm[LEFT]->Set_PosZ( MyMath::FInterpTo( m_pArm[LEFT]->Get_PosZ(), 0.f, DELTATIME_S, 1.f ));
	m_pArm[RIGHT]->Set_PosZ( MyMath::FInterpTo( m_pArm[RIGHT]->Get_PosZ(), 0.f, DELTATIME_S, 1.f ) );
	m_iFrameidx = 3;
}
