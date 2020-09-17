#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "level.h"
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

using namespace sf;

void changeLevel(TileMap& lvl, int& numberLevel)
{
    switch (numberLevel)
    {

    case 1:  lvl.load("map1.tmx"); break;
    case 2:  lvl.load("map1.tmx"); break;
    case 3:  lvl.load("map_test2.tmx"); break;
    default: // в противном случае, возвращаем false
        break;
    }
}

//bool startGame(RenderWindow &window,int &numberLevel) 
bool startGame(int& numberLevel)
{
    bool pvp = false;
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    
    resolution.x = 1280;
    resolution.y = 720;
    //resolution.x = 1920;
    //resolution.y = 1080;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "privet");

    //window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("images/TimesNewRoman.ttf");
    Menu menu(window);
    //if (numberLevel == 1) menu.mainMenu(window, numberLevel); 
    if (!menu.mainMenu(window, numberLevel)) return false;
    window.setMouseCursorVisible(false);
    //menu(window);
    if (numberLevel == 3) pvp = true;
    std::cout << numberLevel << "\n";
    //View player2View(FloatRect(-resolution.x / 2, -resolution.y / 2, resolution.x / 2, resolution.y / 2));
    //View view (FloatRect(-resolution.x / 2, -resolution.y / 2, resolution.x / 2, resolution.y / 2));
    //View view(FloatRect(-resolution.x / 2, -resolution.y / 2, resolution.x / 2, resolution.y / 2));
    View view, player1View, player2View;
    view.setCenter(resolution.x / 2, resolution.y / 2);
    view.setSize(resolution);
    player1View.reset(FloatRect(-resolution.x / 2, -resolution.y / 2, resolution.x / 2, resolution.y / 2));
    //view.setSize(resolution.x, resolution.y);
    //player2View.setSize(resolution.x, resolution.y);
    if (pvp)
    {
        player2View.setSize(resolution.x / 2, resolution.y);
        player1View.setSize(resolution.x / 2, resolution.y);
        player1View.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
        player2View.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
    }

    TileMap lvl;

    if (numberLevel != 0)
    { 
        changeLevel(lvl, numberLevel); 
    }
    else
    {
        return false;
    }

    Image heroImage;
    Image easyEnemyImage;
    Image BulletImage;
    Image SkeletonImage;
    BulletImage.loadFromFile("images/bullet.png");
    BulletImage.createMaskFromColor(Color(0, 0, 0));

    Object player = lvl.getObject("player");
    Object player2 = lvl.getObject("player2");
    Object easyEnemyObject = lvl.getObject("easyEnemy");
    Object skelletonObject = lvl.getObject("skelleton");
    Clock clock;

    heroImage.loadFromFile("images/volodya.png");
    heroImage.createMaskFromColor(Color(255, 255, 255));
    easyEnemyImage.loadFromFile("images/kvak.png");
    easyEnemyImage.createMaskFromColor(Color(0, 0, 0));
    SkeletonImage.loadFromFile("images/SkeletonWalk.png");
    SkeletonImage.createMaskFromColor(Color(255, 255, 255));


    std::list<Entity*> entities;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;

    std::vector<Object> e = lvl.getObjectsByName("easyEnemy");
    std::vector<Object> skelleton = lvl.getObjectsByName("skelleton");
    //std::cout << "easy enemy numbers: " << e.size() << std::endl;
    //std::cout << "skelleton numbers: " << skelleton.size() << std::endl;

    AnimationManager anim;
    anim.create("walk", heroImage, 0, 0, 40, 80, 3, 0.01, 40);
    anim.create("stay", heroImage, 0, 0, 40, 80, 1, 0);
    anim.create("jump", heroImage, 0, 241, 40, 80, 1, 0);
    anim.create("duck", heroImage, 0, 161, 40, 80, 1, 0);
    anim.create("die", heroImage, 0, 81, 40, 80, 3, 0.01, 40, false);


    AnimationManager animEasyEnemy;
    animEasyEnemy.create("move", easyEnemyImage, 0, 0, 32, 32, 1, 0.005);

    AnimationManager animSkelleton;
    animSkelleton.loadFromXML("images/skelleton.xml", SkeletonImage);

    AnimationManager animBullet;
    animBullet.create("move", BulletImage, 7, 10, 8, 8, 1, 0);
    animBullet.create("explode", BulletImage, 27, 7, 18, 18, 4, 0.01, 29, false);

    for (int i = 0; i < e.size(); i++)
    {
        entities.push_back(new Enemy(animEasyEnemy, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top));
    }
    for (int i = 0; i < skelleton.size(); i++)
    {
        entities.push_back(new Enemy(animSkelleton, "Skelleton", lvl, skelleton[i].rect.left, skelleton[i].rect.top));
        //std::cout << "skelleton number: " << i << " created!" << std::endl;
    }

    Player p(anim, "Player1", lvl, player.rect.left, player.rect.top);
    Player p2(anim, "Player2", lvl, player2.rect.left, player2.rect.top);
    statBar player1StatBar(font, 1), player2StatBar(font, 2);

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
                entities.push_back(new Bullet(animBullet, "Bullet", lvl, p.x, p.y + 50, p.direction));
            }//if shoot - making bullet
            if ((p2.isShoot == true) && (p2.canShoot == true) && (p2.ammo > 0))
            {
                p2.ammo -= 1; // !!!! FOR TEST !!!!
                p2.isShoot = false;
                p2.canShoot = false;
                entities.push_back(new Bullet(animBullet, "Bullet", lvl, p2.x, p2.y + 50, p2.direction, "player2"));
            }//if shoot - making bullet
        }
        //if (Keyboard::isKeyPressed(Keyboard::U)) view.zoom(1.0040f); //масштабируем, уменьшение
        //if (Keyboard::isKeyPressed(Keyboard::P)) view.zoom(0.990f); //масштабируем, уменьшение
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
        if (Keyboard::isKeyPressed(Keyboard::Q)) { std::cout << numberLevel << " " << time << std::endl;}
        //if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.setView(view);
            Menu menu2(window);
            if (!menu2.mainMenu(window, numberLevel, true)) {
                std::cout << "current numberLevel = " << numberLevel << "\n";
                return true;
            }
            }

        // updates
        p.update(time);
        p2.update(time);
        
        // all entities update
        for (it = entities.begin(); it != entities.end();)
        {
            (*it)->update(time);
            if ((*it)->life == false)
            { 
                it = entities.erase(it);
            }
            else it++;
        }

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
        
        player1StatBar.update("Volodya" ,p.health, p.ammo);
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

        window.clear(Color(77, 83, 140));
        player1View.setCenter(p.x, p.y);
       
        window.setView(player1View);
        
        window.draw(lvl);

        // draw all entites
        for (it = entities.begin(); it != entities.end(); it++) 
        {
            (*it)->draw(window);
        }
        p2.draw(window);
        p.draw(window);
        player1StatBar.draw(window);
                
        if (pvp) // for split screen
        {
            player2View.setCenter(p2.x, p2.y);
            window.setView(player2View);

            window.draw(lvl);

            // draw all entites
            for (it = entities.begin(); it != entities.end(); it++)
            {
                (*it)->draw(window);
            }
            p2.draw(window);
            p.draw(window);
            player2StatBar.draw(window);
        }

        window.display();
    }
}

void gameRunning(int& numberLevel)
//void gameRunning(RenderWindow& window, int& numberLevel)
{

    if (startGame(numberLevel))
    {
        //numberLevel++;
        //gameRunning(window, numberLevel);
        gameRunning(numberLevel);
    }
}



#endif GAME_H