#include "stdafx.h"
#include "Bird.h"
#include "GameCamera.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 		

Bird::Bird()
{
}


Bird::~Bird()
{
	DeleteGO(m_skinModelRender);
}
void Bird::SetAnimation()
{
	m_animClip[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);

}

bool Bird::Start()
{
	//SetAnimation();
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::BIRD);
	//�V���h�E�L���X�^�[�ƃV���h�E���V�[�o�[�̃t���O�𗧂Ă�B
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		30.0f,			//�����B
		m_position		//�����ʒu�B
	);
	return true;
}
void Bird::Update()
{
	AnimationController();
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_movespeed.y = 0.0f;
	}
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPosition(m_position);
}

void Bird::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��擾
	CVector3 stickL;
	//�_���[�W���󂯂Ă���Ƃ��A�Q�[���I�[�o�[�̎��A�Q�[���N���A�̎��͉E�X�e�B�b�N�̓��͂𖳌��ɂ���
	if (m_state == enState_Damage || m_state == enState_GameOver || m_state == enState_Eat) {
		stickL.x = 0.0f;
		stickL.y = 0.0f;
	}
	else {
		stickL.y = Pad(0).GetLStickYF();
		stickL.x = -Pad(0).GetLStickXF();	//�A�i���O�X�e�B�b�N�̓��͗ʂ��擾�B
	}
	//���X�e�B�b�N
	//�X�e�B�b�N�̍��E���͂̏���
	m_movespeed.z = 0.0f;
	m_movespeed.x = 0.0f;
	m_movespeed.z = +sin(m_radian)*stickL.x * m_multiply;
	m_movespeed.x = -cos(m_radian)*stickL.x * m_multiply;
	//�X�e�B�b�N�̏㉺���͂̏���
	m_movespeed.z += cos(m_radian)*stickL.y * m_multiply;
	m_movespeed.x += sin(m_radian)*stickL.y * m_multiply;
	//�d��
	//m_movespeed.y -= 800.0f *GameTime().GetFrameDeltaTime();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_charaCon.Execute(m_movespeed, GameTime().GetFrameDeltaTime());
}

void Bird::Turn()
{
	m_gamecamera = FindGO<GameCamera>(GameObjectNames::CAMERA);
	if (m_gamecamera == nullptr) {
		return;
	}
	CVector3 rotation = { 0.0f,0.0f,0.0f };
	//���@�̊p�x�̍���
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
	//�E�X�e�B�b�N
	CVector2 stickR;
	stickR.x = -Pad(0).GetRStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.y = Pad(0).GetRStickYF();
	//����
	//�E�X�e�B�b�N
	sdegree = -stickR.x * 2.0f;
	//��]����
	m_degree += sdegree;
	m_rotation.SetRotationDeg(CVector3::AxisY, m_degree);
	m_skinModelRender->SetRotation(m_rotation);
	CVector3 moveSpeedXZ = { 0.0f,0.0f,1.0f };
	m_rotation.Multiply(moveSpeedXZ);
	m_player_heikou = moveSpeedXZ;
	m_birdright = moveSpeedXZ;
	m_birdback = moveSpeedXZ;
	//�v���C���[�̉E�̃x�N�g��
	m_birdright = moveSpeedXZ;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 90.0f);
	qRot.Multiply(m_birdright);
	//�v���C���[�̌��̃x�N�g��
	CQuaternion qRot2;
	qRot2.SetRotationDeg(CVector3::AxisY, 180.0f);
	qRot2.Multiply(m_birdback);
	//m_movespeed����L�����N�^�[����]������
	/*auto moveSpeedXZ = m_movespeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	moveSpeedXZ.y = 0;
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	m_player_heikou = moveSpeedXZ;
	m_birdright = moveSpeedXZ;
	m_birdback = moveSpeedXZ;
	//�v���C���[�̉E�̃x�N�g��
	m_birdright= moveSpeedXZ;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 90.0f);
	qRot.Multiply(m_birdright);
	//�v���C���[�̌��̃x�N�g��
	CQuaternion qRot2;
	qRot2.SetRotationDeg(CVector3::AxisY, 180.0f);
	qRot2.Multiply(m_birdback);
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRotation(m_rotation);*/
}

void Bird::Animation()
{
	if (Pad(0).IsTrigger(enButtonX)) {
		m_state = enState_Damage;
	}
}

void Bird::AnimationController()
{
	//�X�e�[�g����ɂ���ăA�j���[�V�����Đ��𕪊�
	switch (m_state) {
	case enState_Walk:
	case enState_Idle:
		if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//�������[�V�����B
			//m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2f);
		}
		else {
			//�ҋ@���[�V����
			//m_skinModelRender->PlayAnimation(enAnimationClip_idle, 0.2f);
		}
		if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			m_state = enState_Walk;
		}
		else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
			m_state = enState_Idle;
		}
		Move();
		Turn();
		Animation();
		break;
	case enState_Damage:
		/*if (m_skinModelRender->IsPlayingAnimation()) {
			//m_skinModelRender->PlayAnimation(enAnimationClip_damage, 0.2f);
		}
		else {
			//�A�j���[�V�����̍Đ����I�������A�ĂуA�j���[�V��������
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Walk;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}*/
		m_damagetimer += GameTime().GetFrameDeltaTime();
		m_blinktimer += GameTime().GetFrameDeltaTime();
		if (m_blinktimer >= 0.05f) {
			//0.2�b�o��
			bool isActive = m_skinModelRender->IsActive();
			m_skinModelRender->SetActiveFlag(!isActive);
			m_blinktimer = 0.0f;
		}
		if (m_damagetimer >= 0.7f) {
			//2�b�o�߂����̂Ń_���[�W�\���I���B
			m_skinModelRender->SetActiveFlag(true);
			m_damagetimer = 0.0f;
			m_blinktimer = 0.0f;
			//�A�j���[�V�����̍Đ����I�������A�ĂуA�j���[�V��������
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Walk;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}
		Move();
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
	case enState_Eat:

		Move();
		Turn();
		break;
	}
}