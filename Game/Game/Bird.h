#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class GameCamera;
class Feed;
class Fade;
class Bird : public IGameObject
{
public:
	Bird();
	~Bird();
	bool Start() override;
	void Update() override;
	void Turn();
	void SetAnimation();
	void AnimationController();
	void Move();
	void Animation();
	void Sound();
	void GameOver();
	//�v���C���[�̍��W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�v���C���[�̍��W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�v���C���[���~������
	void SetStop()
	{
		m_stop = true;
	}
	//�v���C���[�̐^�E�̃x�N�g�����擾
	CVector3 GetRight() const
	{
		return m_birdright;
	}
	//�v���C���[�̌���̃x�N�g�����擾
	CVector3 GetBack() const
	{
		return m_birdback;
	}
	//�H�������ǂ�����Ԃ�
	bool GetEat() const
	{
		return m_state == enState_Eat;
	}
	//���̂��ǂ���
	bool isAdult() const
	{
		return m_adult;
	}
	//�_���[�W
	void Damage()
	{
		if (m_state == enState_Damage || m_adult) {
			return;
		}
		m_state = enState_Damage;
		m_life--;
	}
	//����
	void Death()
	{
		m_gameover = true;
	}
	//�Q�[���I�[�o�[���ǂ���
	bool isGameOver()
	{
		return m_gameover;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = { 00.0f,00.0f,0.0f };
	CVector3 m_movespeed = { 0.0f,0.0f,0.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	CQuaternion m_rotation2 = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One;
	//�v���C���[�̌����ƕ��s�ȃx�N�g��
	CVector3 m_player_heikou;
	CVector3 m_birdright;
	CVector3 m_birdback;
	CVector3 m_rot;
	CCharacterController m_charaCon;
	//�A�j���[�V����
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
		enState_Walk,
		enState_GameOver,
		enState_Damage,
		enState_Eat,
	};
	CAnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	float m_degree = 180.0f;
	float m_radian = 0;
	bool m_stop = false;
	float m_multiply = 220.0f;
	float m_damagetimer = 0.0f;
	float m_blinktimer = 0.0f;
	float m_eattime = 40.0f;
	float m_eattimer = 0.0f;
	float m_degreey = 0.0f;
	bool m_eat = false;
	bool m_eating = false;
	bool m_adult = false;
	int m_adultcondions = 5;
	int m_feedcount = 0;
	bool m_large = false;
	float m_largetimer = 0.0f;
	float m_largetime = 15.0f;
	float m_soundtimer = 0.0f;
	float m_walktime = 30.0f;
	float m_eatingtime = 20.0f;
	float m_waittimer = 0.0f;
	float m_waittime = 100.0f;
	float m_degreegameover = 0.0f;
	int m_life = 5;
	bool m_gameover = false;
	GameCamera* m_gamecamera = nullptr;
	Feed* m_feed=nullptr;
	prefab::CFontRender* m_stageFontRender = nullptr;
	std::unique_ptr<DirectX::SpriteFont > m_stageNoFont;
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	bool m_gameoversound = false;
};

