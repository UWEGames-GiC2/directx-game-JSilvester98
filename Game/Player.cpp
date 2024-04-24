#include "pch.h"
#include "Player.h"
#include <dinput.h>
#include "GameData.h"

Player::Player(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	//any special set up for Player goes here
	m_fudge = Matrix::CreateRotationY(XM_PI);

	m_pos.y = 0.1f;

	SetDrag(1);
	SetPhysicsOn(true);
}

Player::~Player()
{
	//tidy up anything I've created
}


void Player::Tick(GameData* _GD)
{
	switch (_GD->m_GS)
	{
	
		{
		
			//MOUSE CONTROL SCHEME HERE
			float speed = 1000.0f;
			m_acc.x += speed * _GD->m_MS.x;
			m_acc.z += speed * _GD->m_MS.y;
			break;
		
		}
	case GS_PLAY:
	{
		//TURN AND FORWARD CONTROL HERE
		Vector3 forwardMove = 40.0f * Vector3::Forward;
		Matrix rotMove = Matrix::CreateRotationY(m_yaw);
		forwardMove = Vector3::Transform(forwardMove, rotMove);
		if (_GD->m_KBS.W)
		{
			m_acc += forwardMove;
		}
		if (_GD->m_KBS.S)
		{
			m_acc -= forwardMove;
		}


		//change orinetation of player
		float rotSpeed = 2.0f * _GD->m_dt;
		if (_GD->m_KBS.A)
		{
			m_yaw += rotSpeed;
		}
		if (_GD->m_KBS.D)
		{
			m_yaw -= rotSpeed;
		}


		if (_GD->m_MS.x > 0.5)
		{
			m_yaw -= rotSpeed;
		}

		if (_GD->m_MS.x < -0.5)
		{
			m_yaw += rotSpeed;
		}

		break;
	}
	}

	//limit motion of the player
	//float length = m_pos.Length();
	//float maxLength = 500.0f;
	//if (length > maxLength)
	//{
	//	m_pos.Normalize();
	//	m_pos *= maxLength;
	//	m_vel *= -0.9; //VERY simple bounce back
	//}

	m_acc += Vector3(m_grav);

	if (m_pos.y < 0)
	{
		//m_grav = Vector3(0, 0, 0);
		m_acc.y = 0;
		m_pos.y = 0;
	}

	//apply my base behaviour
	CMOGO::Tick(_GD);
}