#pragma once

namespace Bullets
{
    struct BulletsSystemConfig 
    {
        sf::String Bulletss_texture_path;

        float Bulletss_sprite_width;
        float Bulletss_sprite_height;

        float tile_width;
        float tile_height;

        int number_of_animation_frames;
        float frame_duration;

        BulletsSystemConfig() {};

        BulletsSystemConfig(sf::String texture_path, float sprite_width, float sprite_height, float tile_width, float tile_height, int frames, float duration) :
            Bulletss_texture_path(texture_path),
            Bulletss_sprite_width(sprite_width),
            Bulletss_sprite_height(sprite_height),
            tile_width(tile_width),
            tile_height(tile_height),
            number_of_animation_frames(frames),
            frame_duration(duration) {}  
    };
}