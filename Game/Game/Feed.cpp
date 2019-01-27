#include "stdafx.h"
#include "Feed.h"
#include "Bird.h"
#include "Game.h"

Feed::Feed()
{
}


Feed::~Feed()
{

}

bool Feed::Start()
{
	m_game = FindGO < Game>(GameObjectNames::GAME);
	return true;
}

void Feed::Update()
{
	m_game->UpdateFeedInstancingData(
		m_position,
		CQuaternion::Identity,
		m_scale
	);
	if (m_timer >= m_time) {
		m_game->SetFeedEmissionColor({ 1.5f,1.5f,0.0f });
		
		m_timer2 += 60.0f*GameTime().GetFrameDeltaTime();
		if (m_timer2 >= m_time2) {
			m_game->SetFeedEmissionColor({ 0.0f,0.0f,0.0f });
			
			m_timer = 0.0f;
			m_timer2 = 0.0f;
		}
	}
	m_timer += 60.0f*GameTime().GetFrameDeltaTime();
}