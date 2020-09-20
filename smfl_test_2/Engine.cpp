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

    //players.push_back(new Player(animationManagerList["player"], "Player1", lvl, player.rect.left, player.rect.top));
    //players.push_back(new Player(animationManagerList["player"], "Player2", lvl, player2.rect.left, player2.rect.top));
    Player p(animationManagerList["player"], "Player1", lvl, player.rect.left, player.rect.top);
    Player p2(animationManagerList["player"], "Player2", lvl, player2.rect.left, player2.rect.top);
    statBar player1StatBar(font, 1, true), player2StatBar(font, 2);
    //std::vector<Player*>::iterator itPlayer;
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
            if ((p.isShoot == true) && (p.canShoot == true) && (p.ammo > 0))
            {
                p.ammo -= 1; // !!!! FOR TEST !!!!
                p.isShoot = false;
                p.canShoot = false;
                entities.push_back(new Bullet(animationManagerList["bullet"], "Bullet", lvl, p.x, p.y + 50, p.direction));
            }//if shoot - making bullet
            if ((p2.isShoot == true) && (p2.canShoot == true) && (p2.ammo > 0))
            {
                p2.ammo -= 1; // !!!! FOR TEST !!!!
                p2.isShoot = false;
                p2.canShoot = false;
                entities.push_back(new Bullet(animationManagerList["bullet"], "Bullet", lvl, p2.x, p2.y + 50, p2.direction, "player2"));
            }//if shoot - making bullet
        }
        // inputs
        if (input(p, p2)) return true;

        update(time, p, p2);

        // interactions
        for (it = entities.begin(); it != entities.end(); it++)
        {
            /*if ((*it)->getRect().intersects(p.getRect()))
            {
                //if (((*it)->name == "EasyEnemy") || ((*it)->name == "Skelleton")) 
                if ((*it)->type == "enemy")  
                {
                    if (p.dy > 0)
                    {
                        (*it)->dx = 0;
                        p.dy = -0.2;
                        (*it)->health = 0;
                    }
                    else {
                        //p.health -= 5;	
                    }
                }
            }*/
            for (it2 = entities.begin(); it2 != entities.end(); it2++)
            {
                if ((*it)->getRect() != (*it2)->getRect()) //different rectanglles
                {
                    //if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "Bullet"))// intersects of bullet and enemy
                    if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->type == "enemy") && ((*it2)->name == "Bullet") && ((*it2)->damage != 0))// intersects of bullet and enemy
                    {
                        //(*it)->dx = 0;//stop enemy
                        (*it)->health -= (*it2)->damage; // damage enemy
                        (*it2)->damage = 0;
                        (*it2)->health = 0; // kill bullet
                    }
                }

            }
            if (pvp)
            {
                if ((*it)->getRect().intersects(p2.getRect()))
                {
                    if (((*it)->name == "Bullet") && ((*it)->type == "player1") && (p2.health > 0))
                    {
                        p2.health -= (*it)->damage;
                        (*it)->damage = 0;
                        (*it)->health = 0; // kill bullet
                    }
                }
                if ((*it)->getRect().intersects(p.getRect()))
                {
                    if (((*it)->name == "Bullet") && ((*it)->type == "player2") && (p.health > 0))
                    {
                        p.health -= (*it)->damage;
                        (*it)->damage = 0;
                        (*it)->health = 0; // kill bullet
                    }
                }
            }

        }

        player1StatBar.update("Volodya", p.health, p.ammo, time);
        player2StatBar.update("Volodya 2", p2.health, p2.ammo, time);

        // win condition
        if (p.win)
        {
            p.win = false;
            sleep(milliseconds(50));
            numberLevel++;
            return true;
        } // next level
        // loose condition
        /*if (!p.life)
        {
            numberLevel = 1;
            return true;
        }*/
        draw(p, p2, lvl, player1StatBar, player2StatBar);

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
        player1View.setSize(resolution.x / 2, resolution.y / 2);
    }
    entities.clear();
    //players.clear();

    if (startGame())
    {
        //numberLevel++;
        //gameRunning(window, numberLevel);
        gameRunning();
    }
}