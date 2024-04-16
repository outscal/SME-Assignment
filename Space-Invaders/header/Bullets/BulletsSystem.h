#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Bullets/BulletsSystemConfig.h"
#include "../../header/UI/UIElement/ImageView.h"

namespace Bullets
{
    class BulletsSystem
    {
    private:    
        BulletsSystemConfig Bullets_system_config;
        
        sf::Vector2f Bulletss_position;
        UI::UIElement::ImageView* Bullets_image;

        void createUIElements();
        void initializeImage();

        int current_frame;
        sf::Clock clock;
        sf::Time frame_time;
      
    public:
        BulletsSystem(BulletsSystemConfig config);
        ~BulletsSystem();

        void initialize(sf::Vector2f position);
        void update();
        void render();

        void destroy();
    };
}