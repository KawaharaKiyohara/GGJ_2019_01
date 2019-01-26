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
	return true;
}

void Feed::Update()
{

}