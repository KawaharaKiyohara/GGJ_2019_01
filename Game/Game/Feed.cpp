#include "stdafx.h"
#include "Feed.h"
#include "Bird.h"

Feed::Feed()
{
}


Feed::~Feed()
{
	DeleteGO(m_skinModelRender);
}

bool Feed::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(CmoFilePaths::FEED);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);

	return true;
}

void Feed::Update()
{
	if (m_timer >= m_time) {
		m_skinModelRender->SetEmissionColor({ 1.5f,1.5f,0.0f });
		m_timer2 += 60.0f*GameTime().GetFrameDeltaTime();
		if (m_timer2 >= m_time2) {
			m_skinModelRender->SetEmissionColor({ 0.0f,0.0f,0.0f });
			m_timer = 0.0f;
			m_timer2 = 0.0f;
		}
	}
	m_timer += 60.0f*GameTime().GetFrameDeltaTime();
}