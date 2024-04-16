#include "../../header/Bullets/BulletsService.h"
#include "../../header/Bullets/BulletsSystemConfigData.h"

namespace Bullets
{
	BulletsService::BulletsService() { }

	BulletsService::~BulletsService() { destroy(); }

	void BulletsService::initialize() { }

	void BulletsService::update()
	{
		for (BulletsSystem* Bullets_system : Bullets_system_list) 
			Bullets_system->update();

		destroyFlaggedBulletsSystem();
	}

	void BulletsService::render()
	{
		for (BulletsSystem* Bullets_system : Bullets_system_list)
			Bullets_system->render();
	}

	void BulletsService::spawnBulletsSystem(sf::Vector2f position, BulletsType Bulletss_type)
	{
		BulletsSystem* Bullets_system = new BulletsSystem(getBulletsSystemConfig(Bulletss_type));
		Bullets_system->initialize(position);
		Bullets_system_list.push_back(Bullets_system);
	}

	void BulletsService::destroyBulletsSystem(BulletsSystem* Bullets_system)
	{
		flagged_Bullets_system_list.push_back(Bullets_system);
		Bullets_system_list.erase(std::remove(Bullets_system_list.begin(), Bullets_system_list.end(), Bullets_system), Bullets_system_list.end());
	}

	BulletsSystemConfig BulletsService::getBulletsSystemConfig(BulletsType Bulletss_type)
	{
		switch (Bulletss_type)
		{
			case Bullets::BulletsType::EXPLOSION:
				return explosion_Bullets_system_config;
		}
	}

	void BulletsService::destroyFlaggedBulletsSystem()
	{
		for (BulletsSystem* Bullets_system : flagged_Bullets_system_list)
			delete (Bullets_system);

		flagged_Bullets_system_list.clear();
	}

	void BulletsService::reset() { destroy(); }

	void BulletsService::destroy()
	{
		for (BulletsSystem* Bullets_system : Bullets_system_list)
			delete (Bullets_system);
	}
}