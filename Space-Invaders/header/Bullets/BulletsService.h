#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "../../header/Bullets/BulletsSystem.h"

namespace Bullets
{
	enum class BulletsType
	{
		SIMPLE_BULLETS,
		FROST_BEAMS,
		TORPEDOES,
		LOCKED_MISSILES
	};

	class BulletsService
	{
	private:
		std::vector<BulletsSystem*> Bullets_system_list;
		std::vector<BulletsSystem*> flagged_Bullets_system_list;

		BulletsSystemConfig getBulletsSystemConfig(BulletssType Bulletss_type);
		void destroyFlaggedBulletsSystem();
		void destroy();

	public:
		BulletsService();
		virtual ~BulletsService();

		void initialize();
		void update();
		void render();

		void reset();

		void spawnBulletsSystem(sf::Vector2f position, BulletssType Bulletss_type);
		void destroyBulletsSystem(BulletsSystem* Bullets_system);
	};
}