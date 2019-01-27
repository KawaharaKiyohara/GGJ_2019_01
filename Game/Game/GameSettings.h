#pragma once

//�ւ̐������B�l��傫������Ǝւ�������B�f�t�H���g0.01
static const float SNAKE_GEN_RATE = 0.012f;

//�a�̐������B�l��傫����Ɖa��������B�f�t�H���g0.01
static const float FEED_GEN_RATE = 0.016f;

//�����������邽�߂ɕK�v�ȉa�̐��B
static const float GROWUP_FEED_COUNT = 6;

//���̈ړ����x(�n�ʂɂ���Ƃ�)
static const float BIRD_MOVE_SPEED = 200.0f;

//���̈ړ����x(���ł���Ƃ�)
//80.0f�̕���ύX����Ƃ悢�ł��B
static const float BIRD_FLY_MOVE_SPEED = 220.0f * 180.0f;

/// <summary>
/// �Q�[���̐ݒ�N���X�B
/// </summary>
class GameSettings
{
private:
	GameSettings();
public:
	~GameSettings();
	
	/// <summary>
	/// �Q�[���̓�Փx���擾
	/// </summary>
	/// <returns></returns>
	static int GetLevel() 
	{
		return m_level;
	}
	/// <summary>
	/// ��Փx��ݒ肷��B
	/// </summary>
	/// <param name="level">��Փx</param>
	static void SetLevel(int level)
	{
		m_level = level;
	}
	/// <summary>
	/// ��Փx�̐����擾����B
	/// </summary>
	/// <returns></returns>
	static constexpr int GetNumLevel()
	{
		return 5;
	}
	/// <summary>
	/// �}�b�v�̃T�C�Y���擾�B
	/// </summary>
	/// <returns></returns>
	static float GetMapSize() 
	{
		const float MAP_SIZE[GameSettings::GetNumLevel()] = {
			//������������������ŏI�X�e�[�W�̐ݒ�ɂȂ�
			10000.0f,
			12500.0f,
			15000.0f,
			17500.0f,
			50000.0f,
		};
		return MAP_SIZE[GetLevel()];
	}
	static void SetStartPosition(CVector3 pos)
	{
		m_startPosition = pos;
	}
	/// <summary>
	/// �Q�[���J�n���W�擾�B
	/// </summary>
	/// <returns></returns>
	static CVector3 GetStartPosition()
	{
		return m_startPosition;
	}
	/// <summary>
	/// �S�[�����W�B
	/// </summary>
	/// <returns></returns>
	static CVector3 GetGoalPosition()
	{
		return m_goalPosition;
	}
	/// <summary>
	/// �S�[���̍��W��ݒ肷��B
	/// </summary>
	/// <param name="pos"></param>
	static void SetGoalPosition(CVector3 pos)
	{
		m_goalPosition = pos;
	}
	/// <summary>
	/// �V���h�E�}�b�v�̃��C�g�̃C���Q�[�����̍������擾�B
	/// </summary>
	/// <returns></returns>
	static float GetShadowMapLightHeightInGame()
	{
		return UnitM(15.0f);
	}
	/// <summary>
	/// �X�^�[�g�J�b�g�̎��̃V���h�E�}�b�v�̃��C�g�̍������擾�B
	/// </summary>
	/// <returns></returns>
	static float GetShadowMapLightHeightInStartCut()
	{
		return UnitM(60.0f);
	}
private:
	static int m_level;			//��Փx�B
	static CVector3 m_startPosition;	//�Q�[���J�n���W�B
	static CVector3 m_goalPosition;		//�S�[�����W�B
};


