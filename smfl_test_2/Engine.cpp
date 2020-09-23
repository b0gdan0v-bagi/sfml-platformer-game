#include "engine.h"

using namespace sf;

Engine::Engine()
{
    GlobalData data;
    numberLevel = data.numberLevel;
    resolution = data.resolution;
    inGameKeyInputs = true;
    window.create(VideoMode(resolution.x, resolution.y), data.name + " " + data.version, Style::Close);
    font.loadFromFile("images/TimesNewRoman.ttf");
    menu.create(window, font, data);
    //menu.setAboutVer(data.version, data.email);
    view.setCenter(resolution.x / 2, resolution.y / 2);
    view.setSize(resolution);
    playerViews.push_back(new View); //creating 2 view for split screen
    playerViews.push_back(new View); // in future add "for" for number of split screens and logic if needed
    if (loadImages()) std::cout << "All images succsesfully loaded!\n";
    if (loadAnimations()) std::cout << "All animations succsesfully loaded!\n";
    gameInterface.create(window, font);
}


bool Engine::startGame()
{
    window.setMouseCursorVisible(false);

    //TileMap lvl;
    lvl.push_back(new TileMap);

    if (numberLevel != 0) changeLevel();
    else return false;

    Object player = lvl[0]->getObject("player");
    Object player2 = lvl[0]->getObject("player2");

    Clock clock;

    std::vector<Object> easyEnemy = lvl[0]->getObjectsByName("easyEnemy");
    std::vector<Object> skelleton = lvl[0]->getObjectsByName("skelleton");

    for (int i = 0; i < easyEnemy.size(); i++)
    {
        entities.push_back(new Enemy(animationManagerList["easyEnemy"],
            "EasyEnemy", *lvl[0], easyEnemy[i].rect.left, easyEnemy[i].rect.top));
    }
    for (int i = 0; i < skelleton.size(); i++)
    {
        entities.push_back(new Enemy(animationManagerList["skelleton"],
            "Skelleton", *lvl[0], skelleton[i].rect.left, skelleton[i].rect.top));
    }

    players.push_back(new Player(animationManagerList["player"], "Player1", *lvl[0], player.rect.left, player.rect.top));
    players.push_back(new Player(animationManagerList["player"], "Player2", *lvl[0], player2.rect.left, player2.rect.top));

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
            playersShooting(); // in event while
        }

        input();
        if (returnToMainMenu) return true;
        if (!gameInterface.getActive()) inGameKeyInputs = true;
        update(time);

        //gameInterface.update(window);
        
        
        entitiesInteractions(); // interaction of all things
        if (returnToMainMenu) return true;
        if (checkWin()) return true;
        if (checkDefeat()) return true;
        draw(); // draw all things

    }
}

