#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Player
{

private:

    
    Sprite p_Sprite;
    Texture p_Texture;
    

    // tracking the direction of travel
    bool p_LeftPressed;
    bool p_RightPressed;
    bool p_TopPressed;
    bool p_BotPressed;

    // speed in pixels
    float p_Speed;
public:
    
    Player();

    // To send a sprite to the main function
    Sprite getSprite();
    FloatRect p_rect;
    IntRect p_texture_rect;
    Vector2f p_Position, p_Velocity, p_Direction;
    bool onGround;

    // For moving Volodya
    void moveLeft();
    void moveTop();
    void moveBot();
    void moveRight();

    // Stop moving
    void stopLeft();
    void stopTop();
    void stopRight();
    void stopBot();

    // This function will be called every frame
    void update(float elapsedTime);

};