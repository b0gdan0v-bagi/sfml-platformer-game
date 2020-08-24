#include "Engine.h"


Engine::Engine()
{
    // Get screen resolution, make window SFML and View
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Volodya",
        Style::Default);
    m_Window.setFramerateLimit(60);
    // load texture
  //  m_BackgroundTexture.loadFromFile("background.jpg");
    m_TextureVodka.loadFromFile("vodka.png");
    m_SpriteVodka.setTexture(m_TextureVodka);
 //   TextureSize = m_BackgroundTexture.getSize(); //Get size of texture.
  //  WindowSize = m_Window.getSize();             //Get size of window.
 //   float ScaleXBackground = (float)WindowSize.x / TextureSize.x;
 //   float ScaleYBackground = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
    // link texture and sprite
    
  //  m_BackgroundSprite.setTexture(m_BackgroundTexture);
  //  m_BackgroundSprite.setScale(ScaleXBackground, ScaleYBackground);
}

void Engine::start()
{
    // Calculationg of time
    Clock clock;

    while (m_Window.isOpen())
    {
        // Restart the timer and write the measured time in dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}