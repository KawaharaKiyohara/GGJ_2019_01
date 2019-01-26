#include "stdafx.h"
#include "GameCamera.h"
#include "Bird.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	//�j�A�N���b�v�ƃt�@�[�N���b�v�̊Ԃ��J�����̉f���͈͂ɂȂ�
	MainCamera().SetNear(1.0f);     //�j�A�N���b�v�@�J��������߂��ق��̖�
	MainCamera().SetFar(100000.0f);  //�t�@�[�N���b�v�@�J�������牓���ق��̖�
	return true;
}

void GameCamera::Update()
{
	if (m_bird == nullptr) {
		m_bird = FindGO<Bird>(GameObjectNames::BIRD);
	}
	TPS();
	//���_
	MainCamera().SetTarget(m_target);
	//���W
	MainCamera().SetPosition(m_position);
	//�J�����̍X�V�B
	MainCamera().Update();
}

void GameCamera::TPS()
{
	if (!m_bird->isAdult()) {
		CVector3 stickR;
		stickR.x = -Pad(0).GetRStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
		stickR.y = Pad(0).GetRStickYF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
		stickR.z = 0.0f;
		//�E�X�e�B�b�N�̓���
		//�E�X�e�B�b�N
		m_sdegreexz = -stickR.x * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
		m_sdegreey = -stickR.y * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
	}
	else {
		CVector3 stickL;
		stickL.x = -Pad(0).GetLStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
		stickL.y = Pad(0).GetLStickYF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
		stickL.z = 0.0f;
		//�E�X�e�B�b�N�̓���
		//�E�X�e�B�b�N
		m_sdegreexz = -stickL.x * 2.0f*30.0f*GameTime().GetFrameDeltaTime();
		m_sdegreey = -stickL.y*2.0f*30.0f*GameTime().GetFrameDeltaTime();
	}
	//��]�x���Z
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
	//�㉺�����̃J�����ړ��𐧌�
	if (m_degreey >= 70.0f) {
		m_degreey = 70.0f;
	}
	if (m_degreey <= -15.0f) {
		m_degreey = -15.0f;
	}
	//�p�x�����W�A���P�ʂɒ���
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	m_target = m_bird->GetPosition() + m_bird->GetRight()*30.0f;
	m_target.y += 40.0f;
	//Y������ɉ�]������B
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, m_radianx);
	m_topos = { 0.0f, 0.0f, 1.0f };
	qRot.Multiply(m_topos);
	//�㉺�̉�]�B
	//�܂��͉񂷎����v�Z����B
	CVector3 rotAxis;
	rotAxis.Cross(m_topos, CVector3::AxisY);
	//�x�N�g���𐳋K������B
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(m_topos);
	m_topos *= m_r;
	m_position = m_target + m_topos;
}
