/*#pragma once
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
    const int H = 12;
    const int W = 40;


    String TileMapC[12] = {

    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                B     B",
    "B                                B     B",
    "B                                B     B",
    "B                                B     B",
    "B         0000                BBBB     B",
    "B                                B     B",
    "BBB                              B     B",
    "B              BB                BB    B",
    "B              BB                      B",
    "B    B         BB         BB           B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

    };
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
    void checkCollisionWithMap(float Dx, float Dy);
    // This function will be called every frame
    void update(float elapsedTime);

};*/