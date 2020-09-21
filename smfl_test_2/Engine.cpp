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
void Engine::changeLevel(TileMap& lvl)
{
    switch (numberLevel)
    {
    case 1:  lvl.load("map1.tmx"); break;
    case 2:  lvl.load("map1.tmx"); break;
    case 3:  lvl.load("map_test2.tmx"); break;
    default:
        break;
    }
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


    //std::list<Entity*> entities;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;
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

    statBar player1StatBar(font, 1, true), player2StatBar(font, 2);
    std::vector<Player*>::iterator itPlayer;
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
            for (itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
            {
                if (((*itPlayer)->isShoot == true) && ((*itPlayer)->canShoot == true) && ((*itPlayer)->ammo > 0))
                {
                    (*itPlayer)->ammo -= 1; // !!!! FOR TEST !!!!
                    (*itPlayer)->isShoot = false;
                    (*itPlayer)->canShoot = false;
                    entities.push_back(new Bullet(
                        animationManagerList["bullet"], "Bullet", lvl, (*itPlayer)->getPos().x, (*itPlayer)->getPos().y + 50,
                        (*itPlayer)->getDir(), (*itPlayer)->getName()));
                }//if shoot - making bullet
            }
        }
        // inputs
        if (input()) return true;

        update(time);

        // interactions
        for (it = entities.begin(); it != entities.end(); it++)
        {
            /*if ((*it)->getRect().intersects(players[0]->getRect()))
            {
                //if (((*it)->name == "EasyEnemy") || ((*it)->name == "Skelleton")) 
                if ((*it)->type == "enemy")  
                {
                    if (players[0]->dy > 0)
                    {
                        (*it)->dx = 0;
                        players[0]->dy = -0.2;
                        (*it)->health = 0;
                    }
                    else {
                        //players[0]->health -= 5;	
                    }
                }
            }*/
            for (it2 = entities.begin(); it2 != entities.end(); it2++)
            {
                if ((*it)->getRect() != (*it2)->getRect()) //different rectanglles
                {
                    //if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "Bullet"))// intersects of bullet and enemy
                    if (((*it)->getRect().intersects((*it2)->getRect())) &&
                        ((*it)->getType() == "enemy") &&
                        ((*it2)->getName() == "Bullet") &&
                        ((*it2)->getDamage() != 0))// intersects of bullet and enemy
                    {
                        //(*it)->dx = 0;//stop enemy
                        (*it)->takeDamage((*it2)->getDamage()); // damage enemy
                        (*it2)->setDamage(0);
                        (*it2)->setHealth(0); // kill bullet
                    }
                }

            }
            if (pvp)
            {
                for (itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
                {
                    if ((*it)->getRect().intersects((*itPlayer)->getRect()))
                    {
                        if (((*it)->getName() == "Bullet") && ((*it)->getType() != (*itPlayer)->getName()) && ((*itPlayer)->getHealth() > 0))
                        {
                            (*itPlayer)->takeDamage((*it)->getDamage());
                            (*it)->setDamage(0);
                            (*it)->setHealth(0); // kill bullet
                        }
                    }
                }
            }

        }

        player1StatBar.update("Volodya", players[0]->getHealth(), players[0]->ammo, time);
        player2StatBar.update("Volodya 2", players[1]->getHealth(), players[1]->ammo, time);

        // win condition
        if (players[0]->win)
        {
            players[0]->win = false;
            sleep(milliseconds(50));
            numberLevel++;
            return true;
        } // next level
        // loose condition
        /*if (!players[0]->life)
        {
            numberLevel = 1;
            return true;
        }*/
        draw(lvl, player1StatBar, player2StatBar);


    }
}

void Engine::gameRunning()

{
    window.setView(view);
    if (!menu.mainMenu(window, numberLevel)) return;
    if (numberLevel == 3) pvp = true;
    else pvp = false;
    if (pvp)
    {
        player2View.setSize(resolution.x / 2, resolution.y);
        player1View.setSize(resolution.x / 2, resolution.y);
        player1View.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
        player2View.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
    }
    else
    {
        player1View.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        player1View.setSize(resolution.x, resolution.y);
    }
    entities.clear();
    players.clear();

    if (startGame())
    {
        //numberLevel++;
        //gameRunning(window, numberLevel);
        gameRunning();
    }
}