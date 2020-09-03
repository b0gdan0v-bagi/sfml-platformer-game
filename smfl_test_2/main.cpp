﻿#pragma once
#include "Engine.h"
#include "level.h"
//#include "view.h"

int main()
{
    // Declaring an instance of the Engine class
    Engine engine;

    // call start
    engine.start();

    // stop
    return 0;
}

/*#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>
using namespace sf;
////////////////////////////////////Общий класс-родитель//////////////////////////
class Entity {
public:
    std::vector<Object> obj;//вектор объектов карты
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life, isMove, onGround;
    Texture texture;
    Sprite sprite;
    String name;
    Entity(Image& image, String Name, float X, float Y, int W, int H) {
        x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
        speed = 0; health = 100; dx = 0; dy = 0;
        life = true; onGround = false; isMove = false;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }
    FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
        return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
    }
};
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player :public Entity {
public:
    enum { left, right, up, down, jump, stay } state;
    int playerScore;
    Player(Image& image, String Name, TileMap& lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
        playerScore = 0; state = stay; obj = lev.getAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
        if (name == "Player1") {
            sprite.setTextureRect(IntRect(4, 19, w, h));
        }
    }
    void control() {
        if (Keyboard::isKeyPressed) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                state = left; speed = 0.1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                state = right; speed = 0.1;
            }
            if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
                state = jump; dy = -0.6; onGround = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                state = down;
            }
        }
    }
    void checkCollisionWithMap(float Dx, float Dy)
    {

        for (int i = 0; i < obj.size(); i++)//проходимся по объектам
            if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
            {
                if (obj[i].name == "solid")//если встретили препятствие
                {
                    if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
                    if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                    if (Dx > 0) { x = obj[i].rect.left - w; }
                    if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
                }
            }
    }
    void update(float time)
    {
        control();
        switch (state)
        {
        case right:dx = speed; break;
        case left:dx = -speed; break;
        case up: break;
        case down: dx = 0; break;
        case stay: break;
        }
        x += dx * time;
        checkCollisionWithMap(dx, 0);
        y += dy * time;
        checkCollisionWithMap(0, dy);
        sprite.setPosition(x + w / 2, y + h / 2);
        if (health <= 0) { life = false; }
        if (!isMove) { speed = 0; }
        setPlayerCoordinateForView(x, y);
        if (life) { setPlayerCoordinateForView(x, y); }
        dy = dy + 0.0015 * time;
    }
};
class Enemy :public Entity {
public:
    Enemy(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
        obj = lvl.getObjectsByType("solid");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
        if (name == "EasyEnemy") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
            dx = 0.1;
        }
    }
    void checkCollisionWithMap(float Dx, float Dy)
    {
        for (int i = 0; i < obj.size(); i++)//проходимся по объектам
            if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
            {
                //if (obj[i].name == "solid"){//если встретили препятствие (объект с именем solid)
                if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
                if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
                if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
                //}
            }
    }
    void update(float time)
    {
        if (name == "EasyEnemy") {
            //moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
            checkCollisionWithMap(dx, 0);
            x += dx * time;
            sprite.setPosition(x + w / 2, y + h / 2);
            if (health <= 0) { life = false; }
        }
    }
};
int main()
{
    RenderWindow window(VideoMode(640, 480), "Lesson 22. kychka-pc.ru");
    view.reset(FloatRect(0, 0, 640, 480));
    TileMap lvl;
    //Level lvl;//создали экземпляр класса уровень
    lvl.load("map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.

    Image heroImage;
    heroImage.loadFromFile("images/MilesTailsPrower.gif");
    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/shamaich.png");
    easyEnemyImage.createMaskFromColor(Color(255, 0, 0));
    Object player = lvl.getObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
    Object easyEnemyObject = lvl.getObject("easyEnemy");//объект легкого врага на нашей карте.задаем координаты игроку в начале при помощи него
    Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 30);//передаем координаты прямоугольника player из карты в координаты нашего игрока
    Enemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 200, 97);//передаем координаты прямоугольника easyEnemy из карты в координаты нашего врага
    Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        p.update(time);
        easyEnemy.update(time);
        window.setView(view);
        window.clear(Color(77, 83, 140));
        window.draw(lvl);//рисуем новую карту

        window.draw(easyEnemy.sprite);
        window.draw(p.sprite);
        window.display();
    }
    return 0;
}*/