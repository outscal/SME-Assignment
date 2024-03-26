#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Particle/ParticleSystemConfig.h"
#include "../../header/UI/UIElement/ImageView.h"

namespace Particle
{
    class ParticleSystem
    {
    private:    
        ParticleSystemConfig particle_system_config;
        
        sf::Vector2f particles_position;
        UI::UIElement::ImageView* particle_image;

        void createUIElements();
        void initializeImage();

        int current_frame;
        sf::Clock clock;
        sf::Time frame_time;
      
    public:
        ParticleSystem(ParticleSystemConfig config);
        ~ParticleSystem();

        void initialize(sf::Vector2f position);
        void update();
        void render();

        void destroy();
    };
}