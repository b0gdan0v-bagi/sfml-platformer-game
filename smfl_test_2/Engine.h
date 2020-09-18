#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
//#include "level.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "animation.h"
#include <vector>
#include <list>
#include "menu.h"
#include <iostream>
#include <sstream>
#include "statBar.h"
#include "GlobalData.h"

using namespace sf;

class Engine
{
public:
    int numberLevel;
    RenderWindow window;
    Vector2f resolution;
    Font font;
    Menu menu;
    bool pvp;
    View view, player1View, player2View;
    std::map<String, Image> imageList;
    std::map<String, AnimationManager> animationManagerList;
    std::list<Entity*> entities;

    //std::vector<Player*> players;

    Engine()
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
        imageList["bullet"].loadFromFile("images/bullet.png");
        imageList["hero"].loadFromFile("images/volodya.png");
        imageList["hero"].loadFromFile("images/volodya.png");
        imageList["hero"].createMaskFromColor(Color(255, 255, 255));
        imageList["easyEnemy"].loadFromFile("images/kvak.png");
        imageList["easyEnemy"].createMaskFromColor(Color(0, 0, 0));
        imageList["skeletonEnemy"].loadFromFile("images/SkeletonWalk.png");
        imageList["skeletonEnemy"].createMaskFromColor(Color(255, 255, 255));
        animationManagerList["player"].create("walk", imageList["hero"], 0, 0, 40, 80, 3, 0.01, 40);
        animationManagerList["player"].create("stay", imageList["hero"], 0, 0, 40, 80, 1, 0);
        animationManagerList["player"].create("jump", imageList["hero"], 0, 241, 40, 80, 1, 0);
        animationManagerList["player"].create("duck", imageList["hero"], 0, 161, 40, 80, 1, 0);
        animationManagerList["player"].create("die", imageList["hero"], 0, 81, 40, 80, 3, 0.01, 40, false);
        animationManagerList["easyEnemy"].create("move", imageList["easyEnemy"], 0, 0, 32, 32, 1, 0.005);
        animationManagerList["skelleton"].loadFromXML("images/skelleton.xml", imageList["skeletonEnemy"]);
        animationManagerList["bullet"].create("move", imageList["bullet"], 7, 10, 8, 8, 1, 0);
        animationManagerList["bullet"].create("explode", imageList["bullet"], 27, 7, 18, 18, 4, 0.01, 29, false);
        
    }
    void changeLevel(TileMap& lvl, int numberLevel)
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

    bool input(Player& p, Player& p2)
    {
        if (Keyboard::isKeyPressed(Keyboard::A)) p.key["L"] = true;
        if (Keyboard::isKeyPressed(Keyboard::D)) p.key["R"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Left)) p2.key["L"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Right)) p2.key["R"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Up)) p2.key["Up"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Down)) p2.key["Down"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Enter)) p2.key["Space"] = true;
        if (Keyboard::isKeyPressed(Keyboard::W)) p.key["Up"] = true;
        if (Keyboard::isKeyPressed(Keyboard::S)) p.key["Down"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Space)) p.key["Space"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Q)) { std::cout << numberLevel << " " << time << std::endl; }
        //if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.setView(view);
            //Menu menu2(window);
            //if (!menu2.mainMenu(window, numberLevel, true)) {
            std::cout << "current numberLevel = " << numberLevel << "\n";
            return true;
        }
    }



    void update(float time, Player &p, Player &p2)
    {
        p.update(time);
        p2.update(time);

        // all entities update
        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();)
        {
            (*it)->update(time);
            if ((*it)->life == false)
            {
                it = entities.erase(it);
            }
            else it++;
        }
    }
    void draw(Player& p, Player& p2, TileMap &lvl, statBar &bar1, statBar& bar2)
    {
        window.clear(Color(77, 83, 140));
        player1View.setCenter(p.x, p.y);

        window.setView(player1View);

        window.draw(lvl);

        // draw all entites
        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
        {
            (*it)->draw(window);
        }
        p2.draw(window);
        p.draw(window);
        //players[0]->update(time);
        //players[0]->draw(window);
        bar1.draw(window);

        if (pvp) // for split screen
        {
            player2View.setCenter(p2.x, p2.y);
            window.setView(player2View);

            window.draw(lvl);

            // draw all entites
            for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
            {
                (*it)->draw(window);
            }
            p2.draw(window);
            p.draw(window);
            bar2.draw(window);
        }

        window.display();
    }

    bool startGame(int numberLevel)
    {
        
        window.setMouseCursorVisible(false);
        std::cout << "\n=========================\n";
        std::cout << "Level number : " << numberLevel << " is loaded\n" << "pvp set : " << pvp << "\n";
        std::cout << "\n=========================\n";

        TileMap lvl;
      
        if (numberLevel != 0) changeLevel(lvl, numberLevel);
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
        statBar player1StatBar(font, 1), player2StatBar(font, 2);
        //std::vector<Player*>::iterator itPlayer;
   

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
            for (it = entities.begin(); it != entities.end(); it++)//проходимся по эл-там списка
            {
                /*if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
                {
                    //if (((*it)->name == "EasyEnemy") || ((*it)->name == "Skelleton")) //и при этом имя объекта EasyEnemy,то..
                    if ((*it)->type == "enemy")  //и при этом имя объекта EasyEnemy,то..
                    {
                        if (p.dy > 0)
                        {
                            (*it)->dx = 0;
                            p.dy = -0.2;
                            (*it)->health = 0;
                        }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
                        else {
                            //p.health -= 5;	//иначе враг подошел к нам сбоку и нанес урон
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

            player1StatBar.update("Volodya", p.health, p.ammo);
            player2StatBar.update("Volodya 2", p2.health, p2.ammo);

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

    void gameRunning(int numberLevel)
        //void gameRunning(RenderWindow& window, int& numberLevel)
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
        
        if (startGame(numberLevel))
        {
            //numberLevel++;
            //gameRunning(window, numberLevel);
            gameRunning(numberLevel);
        }
    }

};




#endif ENGINE_H