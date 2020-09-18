#pragma once
#include "Engine.h"

//hallo

Engine::Engine()
 {

}
/*Engine::Engine()
{
    // Get screen resolution, make window SFML and View
   /* Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Volodya",
        Style::Default);
    m_Window.setFramerateLimit(60);
    view.reset(FloatRect(0, 0, resolution.x, resolution.y));
    TileMap lvl;
    lvl.load("map.tmx");
    Image player1Image;
    player1Image.loadFromFile("volodya.png");
    Object player = lvl.getObject("player");
    Player
    // load texture
  //  m_BackgroundTexture.loadFromFile("background.jpg");
    //m_TextureVodka.loadFromFile("vodka.png");
    //m_SpriteVodka.setTexture(m_TextureVodka);
    m_TextureVodka.loadFromFile("walls.png");
    m_SpriteVodka.setTexture(m_TextureVodka);
    
    m_SpriteVodka.setTextureRect(IntRect(432, 0, 32, 32));
    //block[1][1].set(m_TextureVodka, 400, 400);
    //block[1][2].set(m_TextureVodka, 400, 500);
   // TileMap lvl;
    blocks();
   // blockTEST.set(m_TextureVodka, 500, 500);
 //   TextureSize = m_BackgroundTexture.getSize(); //Get size of texture.
  //  WindowSize = m_Window.getSize();             //Get size of window.
 //   float ScaleXBackground = (float)WindowSize.x / TextureSize.x;
 //   float ScaleYBackground = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
    // link texture and sprite
    
  //  m_BackgroundSprite.setTexture(m_BackgroundTexture);
  //  m_BackgroundSprite.setScale(ScaleXBackground, ScaleYBackground);



}*/

void Engine::start()
{
    // Calculationg of time
    Clock clock;
    RenderWindow window(VideoMode(640, 480), "Lesson 22. kychka-pc.ru");
    view.reset(FloatRect(0, 0, 640, 480));

    lvl.load("map.tmx");
    player = lvl.getObject("player");
    easyEnemyObject = lvl.getObject("easyEnemy");
    heroImage.loadFromFile("images/MilesTailsPrower.gif");
    easyEnemyImage.loadFromFile("images/shamaich.png");
    easyEnemyImage.createMaskFromColor(Color(255, 0, 0));
    Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 30);
    Enemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 200, 97);
      player = lvl.getObject("player");
    easyEnemyObject = lvl.getObject("easyEnemy");
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)  window.close();
        }
        // Restart the timer and write the measured time in dt
        /*Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();*/
        p.update(time);
        easyEnemy.update(time);
        window.setView(view);
        window.clear(Color(77, 83, 140));
        window.draw(lvl);

        window.draw(easyEnemy.sprite);
        window.draw(p.sprite);
        window.display();

       /* input();
        update(dtAsSeconds);
        draw();
       // intersects();*/
    }
}

/*void Engine::draw()
{
    // Erasing the previous frame
    m_Window.clear(Color::White);
    m_Window.setMouseCursorVisible(false);

    // Rendering
    m_Window.draw(p_Player.getSprite());
    for (int i = 0; i < m_Map.H; i++)
        for (int j = 0; j < m_Map.W; j++)
        {
            m_Window.draw(block[i][j].getSprite());
        }
    m_Window.display();
    m_Window.setView(view);
}

void Engine::blocks()
{
    for (int i = 0; i < m_Map.H; i++)
        for (int j = 0; j < m_Map.W; j++)
        {
            //  if (m_Map.TileMapC[i][j] == 'B')
            {
                block[i][j].passability = false;
                block[i][j].set(m_TextureVodka, j * 32, i * 32);
            }
            //   else
            {
                block[i][j].set(m_TextureVodka, 1000, 1000);
            }
        }
}

void Engine::input()
{
    // Escape Press
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        m_Window.close();
    }

    // Press moving keys
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        p_Player.moveLeft();
    }
    else
    {
        p_Player.stopLeft();
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        p_Player.moveRight();
    }
    else
    {
        p_Player.stopRight();
    }

    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        p_Player.moveTop();
    }
    else
    {
        p_Player.stopTop();
    }

    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        p_Player.moveBot();
    }
    else
    {
        p_Player.stopBot();
    }

}

void Engine::update(float dtAsSeconds)
{
    p_Player.update(dtAsSeconds);
    setPlayerCoordinateForView(p_Player.p_rect.left, p_Player.p_rect.top);
    m_Map.update(dtAsSeconds);
    for (int i = 0; i < m_Map.H; i++)
        for (int j = 0; j < m_Map.W; j++)
        {
            block[i][j].update(dtAsSeconds);
        }
}
View view;
void Engine::setPlayerCoordinateForView(float x, float y) {
    float tempX = x; float tempY = y;
    //if (x < 320) tempX = 320;
    //if (y < 240) tempY = 240;//верхнюю сторону
    if (y > 624) tempY = 624;//нижнюю стороню.для новой карты
    view.setCenter(tempX, tempY);
}
*/