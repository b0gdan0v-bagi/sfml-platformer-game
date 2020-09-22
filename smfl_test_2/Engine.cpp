#include "engine.h"

using namespace sf;

Engine::Engine()
{
    GlobalData data;
    numberLevel = data.numberLevel;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    resolution.x = 1280;
    resolution.y = 720;
    //resolution.x = 1920;
    //resolution.y = 1080;
    window.create(VideoMode(resolution.x, resolution.y), "privet");
    font.loadFromFile("images/TimesNewRoman.ttf");
    menu.setFont(font);
    view.setCenter(resolution.x / 2, resolution.y / 2);
    view.setSize(resolution);
    player1View.reset(FloatRect(-resolution.x / 2, -resolution.y / 2,
        resolution.x / 2, resolution.y / 2));
    player2View.reset(FloatRect(-resolution.x / 2, -resolution.y / 2,
        resolution.x / 2, resolution.y / 2));
    if (loadImages()) std::cout << "All images succsesfully loaded!\n";
    if (loadAnimations()) std::cout << "All animations succsesfully loaded!\n";

}


bool Engine::startGame()
{
    window.setMouseCursorVisible(false);

    TileMap lvl;

    if (numberLevel != 0) changeLevel(lvl);
    else return false;

    Object player = lvl.getObject("player");
    Object player2 = lvl.getObject("player2");

    Clock clock;

    std::vector<Object> easyEnemy = lvl.getObjectsByName("easyEnemy");
    std::vector<Object> skelleton = lvl.getObjectsByName("skelleton");

    for (int i = 0; i < easyEnemy.size(); i++)
    {
        entities.push_back(new Enemy(animationManagerList["easyEnemy"],
            "EasyEnemy", lvl, easyEnemy[i].rect.left, easyEnemy[i].rect.top));
    }
    for (int i = 0; i < skelleton.size(); i++)
    {
        entities.push_back(new Enemy(animationManagerList["skelleton"],
            "Skelleton", lvl, skelleton[i].rect.left, skelleton[i].rect.top));
    }

    players.push_back(new Player(animationManagerList["player"], "Player1", lvl, player.rect.left, player.rect.top));
    players.push_back(new Player(animationManagerList["player"], "Player2", lvl, player2.rect.left, player2.rect.top));

    playerBars.push_back(new statBar(font, 1, true));
    playerBars.push_back(new statBar(font, 2));
    std::cout << "\n=========================\n";
    std::cout << "Level number : " << numberLevel << " is succsessfully loaded\n" << "pvp set : " << pvp << "\n";
    std::cout << "=========================\n";

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)  window.close();
            playersShooting(lvl); // in event while
        }

        if (input()) return true; // to end if menu = true
        update(time);
        entitiesInteractions(lvl); // interaction of all things
        if (checkWin()) return true;
        if (checkDefeat()) return true;
        draw(lvl); // draw all things

    }
}

