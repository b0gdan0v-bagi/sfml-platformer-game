#include "engine.h"

using namespace sf;

Engine::Engine()
{
    data.readConfig();
    window.create(VideoMode(data.resolution.x, data.resolution.y), data.name + " " + data.version, Style::Close);
    //window.setMouseCursorGrabbed(true);
    font.loadFromFile("resourses/TimesNewRoman.ttf");
    fpsbar.setFont(font);
    menu.create(window, font, data);
    data.setViewInterface();
    playerViews.push_back(new View); //creating 2 view for split screen
    playerViews.push_back(new View); // in future add "for" for number of split screens and logic if needed
    Clock timeForLoad;
    timeForLoad.restart();
    if (loadImages()) std::cout << "All images succsesfully loaded!\n";
    if (loadAnimations()) std::cout << "All animations succsesfully loaded!\n";
    if (loadSounds()) std::cout << "All sounds succsesfully loaded\n";
    std::cout << "Resourses have been loaded in " << timeForLoad.getElapsedTime().asMilliseconds() << " milliseconds!\n";
    gameInterface.create(window, font);
    menu.setSound(sounds["intersect"]);
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
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::R) std::cout << players[0]->ifDuck() << "\n";
        }

        input();
        update(time);
        entitiesInteractions(); // interaction of all things
        if (checkSTATE()) return true;
        if (checkWin()) return true;
        checkDefeat();
        draw(); // draw all things

    }
}

