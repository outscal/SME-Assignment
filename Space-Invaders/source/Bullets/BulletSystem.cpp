#include "../../header/Bullets/BulletsSystem.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Bullets/BulletsService.h"

namespace Bullets
{
	using namespace Global;
	using namespace UI::UIElement;

	BulletsSystem::BulletsSystem(BulletsSystemConfig config)
	{
		Bullets_system_config = config; 
		createUIElements();
	}

	BulletsSystem::~BulletsSystem() 
	{
		delete(Bullets_image);
	}

	void BulletsSystem::initialize(sf::Vector2f position)
	{
		Bulletss_position = position;
		current_frame = 0;
		frame_time = sf::seconds(Bullets_system_config.frame_duration);

		initializeImage();
	}

	void BulletsSystem::createUIElements()
	{
		Bullets_image = new ImageView();
	}

	void BulletsSystem::initializeImage()
	{
		Bullets_image->initialize(Config::explosion_texture_path, 0, 0, Bulletss_position);
		Bullets_image->setTextureRect(sf::IntRect(0, 0, Bullets_system_config.tile_width, Bullets_system_config.tile_height));

		Bullets_image->setScale(Bullets_system_config.Bulletss_sprite_width, 
			Bullets_system_config.Bulletss_sprite_height, 
			Bullets_system_config.tile_width,
			Bullets_system_config.tile_height);
	}

	void BulletsSystem::update()
	{
		if (clock.getElapsedTime() >= frame_time)
		{
			if (current_frame + 1 >= Bullets_system_config.number_of_animation_frames) 
				destroy();

			current_frame = (current_frame + 1) % Bullets_system_config.number_of_animation_frames;
			clock.restart();

			Bullets_image->setTextureRect(sf::IntRect(
				current_frame * Bullets_system_config.tile_width, 
				0, 
				Bullets_system_config.tile_width,
				Bullets_system_config.tile_height));
		}
		Bullets_image->update();
	}

	void BulletsSystem::render()
	{
		Bullets_image->render();
	}

	void BulletsSystem::destroy()
	{
		ServiceLocator::getInstance()->getBulletsService()->destroyBulletsSystem(this);
	}
}