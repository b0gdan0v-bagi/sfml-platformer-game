#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Trigger.h"
#include "Message.h"
#include "animation.h"
#include <vector>
#include <list>
#include "menu.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "statBar.h"
#include "GlobalData.h"
#include "interface.h"

using namespace sf;

class Engine
{
private:
    GlobalData data;
    int numberLevel, numberLevelMax;
    RenderWindow window;
    Vector2f resolution;
    Font font;
    Menu menu;
    GameInterface gameInterface;
    bool pvp, inGameKeyInputs, returnToMainMenu;
    bool levelChanger;
    View view; // special view for menu
    std::vector<View*> playerViews; // for split screen, id 0 for first player
    std::map<String, Image> imageList;
    std::map<String, AnimationManager> animationManagerList;
    FpsBar fpsbar;
    std::list<Entity*> entities;
    std::vector<Player*> players;
    std::vector<statBar*> playerBars;
    std::vector<Message*> messages;
    //std::map<String, std::vector<Object>*> loadObjects;
    std::vector<TileMap*> lvl; //its a vector for expansion for multiple levels 
                               //(for example if split screen or future network),
                               //now it have only 1 lvl in storage
 
        
    void loadLevel();
    void input();
    void readConfig();
    bool loadImages();
    bool loadAnimations();
    void update(float time);
    void draw();
    void drawSplitHelp(int viewId);
    void viewChanges(); // take view ports if screen splited or not
    void playersShooting();
    void entitiesInteractions();
    bool checkWin();
    void checkDefeat();
    void newMessage(String MESSAGE, int PLAYER_N, float MESSAGE_TIMER = 3000);
    bool startGame();
public:
    Engine();
    void gameRunning();

};


#endif ENGINE_H