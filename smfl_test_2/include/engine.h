#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "Scenario.h"

using namespace sf;


class Engine
{
private:
    Scenario scenario;
    GlobalData data;
    RenderWindow window;
    Font font;
    Menu menu;
    GameInterface gameInterface;
    bool pvp, inGameKeyInputs = { true }, returnToMainMenu, addNewWave;
    bool levelChanger = { false };
    bool levelNexter = { false }; // if level is increasing cause of end of map -> win
    bool defeatSoundsPlay;
    std::string task;
    int gameSTATE = { 0 };
    std::vector<View*> playerViews; // for split screen, id 0 for first player
    std::map<String, Image> imageList;
    std::map<String, AnimationManager> animationManagerList;
    std::map<String, SoundBuffer> soundsBuffer;
    std::map<String, Sound> sounds;
    std::map<String, Music> music;
    FpsBar fpsbar;
    std::list<Entity*> entities;
    std::vector<Player*> players;
    std::vector<statBar*> playerBars;
    std::vector<Message*> messages;
    std::vector<TileMap*> lvl; //its a vector for expansion for multiple levels 
                               //(for example if split screen or future network),
                               //now it have only 1 lvl in storage
    bool bossFight_2nd_phase_dont_repeat;
    void loadLevel();
    void loadEnemyWave(int waveN);
    void input();
    bool loadImages();
    bool loadAnimations();
    bool loadSounds();
    void update(float time);
    void draw();
    void drawSplitHelp(int viewId);
    void viewChanges(); // take view ports if screen splited or not
    void playersShooting();
    void entitiesInteractions();
    void collission_EvsP(std::list<Entity*>::iterator &ent, std::vector<Player*>::iterator &plr);
    bool checkWin();
    void checkDefeat();
    void newMessage(String MESSAGE, int PLAYER_N, float MESSAGE_TIMER = 3000);
    void scenarioPlay(float time);
    bool startGame();
    bool checkSTATE(); //take gameSTATE, if 0 -> continue, if 1 -> exit main cycle to main menu, if 2 -> exit main cycle and reload

public:
    Engine();
    void gameRunning();

};


#endif ENGINE_H