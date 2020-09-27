#include "engine.h"

using namespace sf;

Engine::Engine()
{
    data.loadGlobalData();
    numberLevel = data.numberLevel;
    numberLevelMax = data.numberLevelMax;
    readConfig();
    inGameKeyInputs = true; // make sure that keyboard will work
    levelChanger = false; // we dont want up level at initialise
    //std::cout << 10 / 100 << "\n" << 101 / 100 << "\n";
    window.create(VideoMode(resolution.x, resolution.y), data.name + " " + data.version, Style::Close);
    font.loadFromFile("resourses/TimesNewRoman.ttf");
    fpsbar.setFont(font);
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
    loadLevel(); // this will load all things to containers

    Clock clock;

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
        update(time);
        entitiesInteractions(); // interaction of all things
        if (returnToMainMenu) return true;
        if (checkWin()) return true;
        checkDefeat();
        draw(); // draw all things

    }
}
