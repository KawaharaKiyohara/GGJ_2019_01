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
private:
	static int m_level;			//��Փx�B
	
};


