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
private:
    int numberLevel;
    RenderWindow window;
    Vector2f resolution;
    Font font;
    Menu menu;
    bool pvp;
    View view; // special view for menu
    std::vector<View*> playerViews; // for split screen, id 0 for first player
    std::map<String, Image> imageList;
    std::map<String, AnimationManager> animationManagerList;
    std::list<Entity*> entities;
    std::vector<Player*> players;
    std::vector<statBar*> playerBars;

 
        
    void changeLevel(TileMap& lvl);
    bool input();
    bool loadImages();
    bool loadAnimations();
    void update(float time);
    void draw(TileMap& lvl);
    void drawSplitHelp(TileMap& lvl, int viewId);
    void viewChanges(); // take view ports if screen splited or not
    void playersShooting(TileMap& lvl);
    void entitiesInteractions(TileMap& lvl);
    bool checkWin();
    bool checkDefeat();
    bool startGame();
public:
    Engine();
    void gameRunning();

};


#endif ENGINE_H