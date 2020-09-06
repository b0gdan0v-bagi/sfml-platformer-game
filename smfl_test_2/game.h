#include <SFML/Graphics.hpp>
#include "creatures.h"
#include "level.h"
#include <vector>
#include <list>
#include "menu.h"
#include <iostream>
#include <sstream>

using namespace sf;

void changeLevel(TileMap& lvl, int& numberLevel)
{
    switch (numberLevel)
    {

    case 1:  lvl.load("map1.tmx"); break;
    case 2:  lvl.load("map2.tmx"); break;
    case 3:  lvl.load("map_test.tmx"); break;
    default: // в противном случае, возвращаем false
        break;
    }
}

//bool startGame(RenderWindow &window,int &numberLevel) 
bool startGame(int& numberLevel)
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "privet");
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("images/TimesNewRoman.ttf");
    if (numberLevel == 1) { menu(window, resolution, numberLevel, font); }
    window.setMouseCursorVisible(false);
    //menu(window);
    view.reset(FloatRect(-resolution.x / 2, -resolution.y / 2, resolution.x/2, resolution.y/2));
    TileMap lvl;

    if (numberLevel != 0)
    { 
        changeLevel(lvl, numberLevel); 
    }
    else
    {
        return false;
    }

    //lvl.load("map3.tmx");
    Image heroImage;
    Image easyEnemyImage;
    Image BulletImage;//изображение для пули
    BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения
    BulletImage.createMaskFromColor(Color(0, 0, 0));//маска для пули по черному цвету
    Object player = lvl.getObject("player");
    Object easyEnemyObject = lvl.getObject("easyEnemy");
    Clock clock;

    RectangleShape polosa;
    //std::ostringstream playerHealthString;
    Text playerHealthText("", font, 30);

    //heroImage.loadFromFile("images/MilesTailsPrower.gif");
    heroImage.loadFromFile("images/volodya.png");
    heroImage.createMaskFromColor(Color(255, 255, 255));
    easyEnemyImage.loadFromFile("images/kvak.png");
    easyEnemyImage.createMaskFromColor(Color(0, 0, 0));

    std::list<Entity*> entities;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;

    std::vector<Object> e = lvl.getObjectsByName("easyEnemy");

    for (int i = 0; i < e.size(); i++)
    {
        entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 32, 32));
    }
    Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 80);
    //Enemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 200, 97);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)  window.close();
            if (p.isShoot == true)
            {
                p.health -= 1; // !!!! FOR TEST !!!!
                p.isShoot = false;
                entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y+40, 16, 16, p.direction));
            }//если выстрелили, то появляется пуля. enum передаем как int 
        }
        if (Keyboard::isKeyPressed(Keyboard::U)) {
            view.zoom(1.0040f); //масштабируем, уменьшение
        }
        if (Keyboard::isKeyPressed(Keyboard::P)) {
            view.zoom(0.990f); //масштабируем, уменьшение
        }

        if (Keyboard::isKeyPressed(Keyboard::Q)) { std::cout << numberLevel << " " << time << std::endl;}
        if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }

        p.update(time);

        for (it = entities.begin(); it != entities.end();)
        {
            (*it)->update(time);
            if ((*it)->life == false)
            { 
                it = entities.erase(it);
            }
            else it++;
        }

        for (it = entities.begin(); it != entities.end(); it++)//проходимся по эл-там списка
        {
            if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
            {
                if ((*it)->name == "EasyEnemy") //и при этом имя объекта EasyEnemy,то..
                {
                    if ((p.dy > 0) && (p.onGround == false)) 
                    {
                        (*it)->dx = 0; 
                        p.dy = -0.2; 
                        (*it)->health = 0; 
                    }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
                    else {
                        //p.health -= 5;	//иначе враг подошел к нам сбоку и нанес урон
                    }
                }
            }
            for (it2 = entities.begin(); it2 != entities.end(); it2++) {
                if ((*it)->getRect() != (*it2)->getRect())//different rectanglles
                    if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "Bullet"))// intersects of bullet and EasyEnemy
                    {
                        (*it)->dx = 0;//stop enemy
                        (*it)->health = 0;// kill enemy
                        (*it2)->dx = 0;
                        (*it2)->life = false; // kill bullet
                    }
            }
        }
        
        if (p.win) { p.win = false; p.speed = 0; sleep(milliseconds(50)); numberLevel++; return true; } // next level

        window.setView(view);
        window.clear(Color(77, 83, 140));
        window.draw(lvl);

        // draw all entites
        for (it = entities.begin(); it != entities.end(); it++) 
        {
            window.draw((*it)->sprite);
        }

        window.draw(p.sprite);
        // make interface agreed with camera
        polosa = RectangleShape(Vector2f(view.getSize().x, view.getSize().y / 10));
        polosa.setFillColor(Color::Black);
        polosa.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y + view.getSize().y / 2 - polosa.getSize().y);
        std::ostringstream playerHealthString;
        playerHealthString << p.health;
        playerHealthText.setString("Volodya HP : " + playerHealthString.str());
        playerHealthText.setPosition(polosa.getPosition().x - 100, view.getCenter().y + view.getSize().y / 2 - polosa.getSize().y);
        playerHealthText.setFillColor(Color::White);
        window.draw(polosa);
        window.draw(playerHealthText);
        window.display();
    }
}

void gameRunning(int& numberLevel)
//void gameRunning(RenderWindow& window, int& numberLevel)
{
    //if (startGame(window, numberLevel))
    if (startGame(numberLevel))
    {
        //numberLevel++;
        //gameRunning(window, numberLevel);
        gameRunning(numberLevel);
    }
}
