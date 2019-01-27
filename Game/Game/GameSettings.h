#pragma once
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
private:
	static int m_level;			//��Փx�B
	static CVector3 m_startPosition;	//�Q�[���J�n���W�B
	static CVector3 m_goalPosition;		//�S�[�����W�B
};


