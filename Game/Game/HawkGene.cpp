#include "stdafx.h"
#include "HawkGene.h"
#include "Hawk.h"
#include "AtkHawk.h"

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
	if (m_AppearCount == 500) {
		m_Hawk1 = NewGO<Hawk>(0, GameObjectNames::HAWK);
	}
	if (m_Hawk1 != NULL) {
		m_HitCount++;
	}
	if (m_HitCount == 90) {
		m_Hawk2 = NewGO<AtkHawk>(0, GameObjectNames::HAWK);

		DeleteGO(m_Hawk1);
		m_Hawk1 = NULL;
		m_AppearCount = 0;
		m_HitCount = 0;
		
	}
}
