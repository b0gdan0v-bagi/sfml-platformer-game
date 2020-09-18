#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
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

    Engine();
    void changeLevel(TileMap& lvl);
    bool input(Player& p, Player& p2);
    bool loadImages();
    bool loadAnimations();
    void update(float time, Player& p, Player& p2);
    void draw(Player& p, Player& p2, TileMap& lvl, statBar& bar1, statBar& bar2);
    bool startGame();
    void gameRunning();

};


#endif ENGINE_H