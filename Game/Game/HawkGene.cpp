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
		m_AppearCount = 0;
	}
	

	
		
	
}
