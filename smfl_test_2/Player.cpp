#include "Player.h"


Player::Player()
{
    // Speed
    p_Speed = 400;
    // Connect texture
    p_Texture.loadFromFile("volodya.png");
    p_Sprite.setTexture(p_Texture);

    // start position
    p_Position.x = 100;
    p_Position.y = 100;
    p_Velocity.x = 0.1;
    p_Velocity.y = 0.1;
    onGround = false;
    p_rect = FloatRect(100, 100, 40, 80);
    p_texture_rect = IntRect(0, 0, 40, 80);
    //p_Sprite.setScale(1/p_rect.width, 1/p_rect.height);
    p_Sprite.setTextureRect(IntRect(p_texture_rect));

}

// make sprite aviliable for draw()
Sprite Player::getSprite()
{
    return p_Sprite;
}

void Player::moveLeft()
{
    p_LeftPressed = true;
    p_texture_rect.left += 40;
    p_texture_rect.top = 81;
    if (p_texture_rect.left > 80)
    {
        p_texture_rect.left = 0;
    }
    p_Sprite.setTextureRect(IntRect(p_texture_rect));

}

void Player::moveRight()
{
    p_RightPressed = true;
    p_texture_rect.left += 40;
    p_texture_rect.top = 0;
    if (p_texture_rect.left > 80)
    {
        p_texture_rect.left = 0;
    }
    p_Sprite.setTextureRect(IntRect(p_texture_rect));


}

void Player::moveTop()
{
    p_TopPressed = true;
    p_texture_rect.left += 40;
    p_texture_rect.top = 0;
    if (p_texture_rect.left > 80)
    {
        p_texture_rect.left = 0;
    }
    p_Sprite.setTextureRect(IntRect(p_texture_rect));
}

void Player::moveBot()
{
    p_BotPressed = true;
    p_texture_rect.left += 40;
    p_texture_rect.top = 0;
    if (p_texture_rect.left > 80)
    {
        p_texture_rect.left = 0;
    }
    p_Sprite.setTextureRect(IntRect(p_texture_rect));
}

void Player::stopLeft()
{
    p_LeftPressed = false;
}

void Player::stopRight()
{
    p_RightPressed = false;
}

void Player::stopTop()
{
    p_TopPressed = false;
}

void Player::stopBot()
{
    p_BotPressed = false;
}

// moving of Player
void Player::update(float elapsedTime)
{
    if (p_RightPressed)
    {
        p_Velocity.x += p_Speed;
        p_Direction.x = 1;
        p_Direction.y = 0;
        p_TopPressed = false;
        p_BotPressed = false;
    }

    if (p_LeftPressed)
    {
        p_Velocity.x -= p_Speed;
        p_Direction.x = -1;
        p_Direction.y = 0;
        p_TopPressed = false;
        p_BotPressed = false;
    }

    if (p_TopPressed)
    {
        p_Velocity.y -= p_Speed;
        p_Direction.y = -1;
        p_Direction.x = 0;
        p_RightPressed = false;
        p_LeftPressed = false;
    }

    if (p_BotPressed)
    {
        p_Velocity.y += p_Speed;
        p_Direction.y = 1;
        p_Direction.x = 0;
        p_RightPressed = false;
        p_LeftPressed = false;
    }

    // gravity tests
    
  
    // collisions
    p_rect.left += p_Velocity.x * elapsedTime;
  //  collision(0);
    /*if (!onGround)
    {
        p_Velocity.y = p_Speed*0.05;
        p_Direction.y = 1;
    }*/
        
  //  onGround = false;
    p_rect.top += p_Velocity.y * elapsedTime;
    p_Velocity.x = p_Velocity.y = 0;
    onGround = false;
 //   collision(1);

    if (p_Position.x < 0)
    {
        p_Position.x += 1;
    }

    if (p_Position.y < 0)
    {
        p_Position.y += 1;
    }

    if (p_Position.x > VideoMode::getDesktopMode().width-40)
    {
        p_Position.x -= 1;
    }

    if (p_Position.y > VideoMode::getDesktopMode().height-80)
    {
        p_Position.y -= 1;
        onGround = true;
    }

    // move sprite
    p_Sprite.setPosition(p_rect.left, p_rect.top);

}

