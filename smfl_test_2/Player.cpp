#include "Player.h"


Player::Player()
{
    // Speed
    p_Speed = 400;
    // Connect texture
    p_Texture.loadFromFile("volodya.png");
    p_Sprite.setTexture(p_Texture);

    // start position
    p_Position.x = 300;
    p_Position.y = 300;
    p_Velocity.x = 0.1;
    p_Velocity.y = 0.1;
    onGround = false;
    p_rect = FloatRect(300, 600, 40, 80);
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
}

void Player::moveBot()
{
    p_BotPressed = true;
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
    }

    if (p_LeftPressed)
    {
        p_Velocity.x -= p_Speed;
    }

    if (p_TopPressed)
    {
        p_Velocity.y -= p_Speed;
    }

    if (p_BotPressed)
    {
        p_Velocity.y += p_Speed;
    }

    // gravity tests
    
  
    // collisions
    p_rect.left += p_Velocity.x * elapsedTime;
    collision(0);
    if (!onGround) p_Velocity.y = p_Speed / 2;
  //  onGround = false;
    p_rect.top += p_Velocity.y * elapsedTime;
    p_Velocity.x = p_Velocity.y = 0;
    onGround = false;
    collision(1);

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

void Player::collision(int dir)
{
    for (int i = p_Position.y / 40; i < (p_Position.y + p_rect.height) / 40; i++)
        for (int j = p_Position.x / 40; j < (p_Position.x + p_rect.width) / 40; j++)
        {
            if (TileMap[i][j] == 'B')
            {
                if ((p_Velocity.x > 0) && (dir == 0)) p_Position.x = j * 40 - p_rect.width;
                if ((p_Velocity.x < 0) && (dir == 0)) p_Position.x = j * 40 + 40;
                if ((p_Velocity.y > 0) && (dir == 1)) { p_Position.y = i * 40 - p_rect.height; p_Velocity.y = 0;   onGround = true; }
                if ((p_Velocity.y < 0) && (dir == 1)) { p_Position.y = i * 40 + 40;   p_Velocity.y = 0; }

            }

        }
}

