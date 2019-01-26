#include "stdafx.h"
#include "HawkGene.h"
#include "Hawk.h"

HawkGene::HawkGene()
{
}


HawkGene::~HawkGene()
{
}

bool HawkGene::Start()
{
	return true;
}

void HawkGene::Update()
{
	m_AppearCount++;
	if (m_AppearCount >= 500) {
		m_Hawk1 = NewGO<Hawk>(0, GameObjectNames::HAWK);
		m_AppearCount = 0;
	}
	if (m_Hawk1 != NULL) {
		m_HitCount++;
		if (m_HitCount >= 100) {
			m_Hawk2 = NewGO<Hawk>(0, GameObjectNames::HAWK);
			m_HitCount = 0;
		}
	}
}
