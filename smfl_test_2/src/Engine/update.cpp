#include "engine.h"

using namespace sf;

void Engine::update(float time)
{
    for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
    {
        (*itPlayer)->update(time);
    }

    if (sounds["gameover"].getStatus() == 2) sounds["masilina"].stop();


    if (addNewWave) loadEnemyWave(1);
    // all entities update
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();)
    {
        (*it)->update(time);
        if ((*it)->getLife() == false)
        {
            if ((*it)->getName() == "feel")
            {
                entities.push_back(new Trigger(animationManagerList["key"],
                    "key", *lvl[0], (*it)->getRect().left + (*it)->getRect().width / 2, (*it)->getRect().top + (*it)->getRect().height / 2));
                newMessage("He dropped key, EZ!", 0);
            }
            if ((*it)->getType() == "enemy")
            {
                sounds["priunil"].play();
                data.numberOfKilled++;
            }
            delete* it;
            it = entities.erase(it);
        }
        else it++;
    }
   // REMEMBER playerBars size must be <= players size
    for (int i = 0; i < playerBars.size(); ++i)
    {
        playerBars[i]->update(data.playersName[i], players[i]->getHealth(), players[i]->ammo, time);
    }

    for (std::vector<Message*>::iterator itM = messages.begin(); itM != messages.end();)
    {
        int pN = (*itM)->getPlayerN();
        (*itM)->update(time, players[pN]->getRect().left + players[pN]->getRect().width, players[pN]->getRect().top - 20);
        if ((*itM)->getLife() == false)
        {
            delete *itM;
            itM = messages.erase(itM);
        }
        else ++itM;
    }

    if (data.showFps) fpsbar.update(time, data.fpsBarId);
    if (!gameInterface.getActive()) window.setMouseCursorVisible(false);
    gameInterface.update(window, gameSTATE);
    if (scenario.active) scenarioPlay(time);
}

bool Engine::checkSTATE()
{
    switch (gameSTATE)
    {
    case 0: {
        return false;
        break;
    }
    case 1: {
        levelChanger = false;
        return true;
        break;
    }
    case 2: {
        levelChanger = true;
        return true;
    }
    default:
        break;
    }
    return false;
}

void Engine::scenarioPlay(float time)
{
    switch (scenario.id)
    {
    case 1: {
        inGameKeyInputs = false;
        scenario.timerIncreas(time);
        if ((scenario.timer[0].first > 100) && (scenario.timer[0].second))
        {
            newMessage("Welcome to " + data.name + " " + data.version, 0);
            scenario.timer[0].second = false;
            scenario.timer[1].second = true;
        }
        if ((scenario.timer[1].first > 3500) && (scenario.timer[1].second))
        {
            newMessage("To skip tutorial press SPACE", 0);
            scenario.timer[1].second = false;
            scenario.timer[2].second = true;
        }
        if ((scenario.timer[2].first > 3500) && (scenario.timer[2].second))
        {
            newMessage("Use WASD to move, SPACE for shooting", 0);
            scenario.timer[2].second = false;
            scenario.timer[3].second = true;
        }
        if ((scenario.timer[3].first > 3500) && (scenario.timer[3].second))
        {
            newMessage("Use Q to ask task", 0);
            scenario.timer[3].second = false;
            scenario.timer[4].second = true;
        }
        if ((scenario.timer[4].first > 3500) && (scenario.timer[4].second))
        {
            newMessage("Go FORWARD and PLAY!", 0);
            scenario.stop();
        }

        if ((Keyboard::isKeyPressed(Keyboard::Space)) || (Keyboard::isKeyPressed(Keyboard::Escape))) scenario.stop();
        break;
    }
    case 2: {
        inGameKeyInputs = false;
        
        
        scenario.timerIncreas(time);

        if ((scenario.timer[0].first > 100) && (scenario.timer[0].second))
        {
            addNewWave = true;
            music["lvl1"].stop();
            music["chimai"].play();
            music["chimai"].setPlayingOffset(seconds(7));
            loadEnemyWave(2);
            scenario.timer[0].second = false;
            scenario.timer[1].second = true;
        }
        if ((scenario.timer[1].first > 3500) && (scenario.timer[1].second))
        {
            newMessage("Oh, that man stole my mom", 0);
            scenario.timer[1].second = false;
            scenario.timer[2].second = true;
        }
        if ((scenario.timer[2].first > 3500) && (scenario.timer[2].second))
        {
            newMessage("I must find him!", 0);
            scenario.timer[2].second = false;
            scenario.timer[3].second = true;
        }
        if ((scenario.timer[3].first > 4500) && (scenario.timer[3].second))
        {
            players[0]->win = true;
            scenario.stop();
        }

        break;

    }
    case 3:
    {
        inGameKeyInputs = false;
        
        scenario.timerIncreas(time);
        
        if ((scenario.timer[0].first > 100) && (scenario.timer[0].second))
        {
            newMessage("I havent find my mom!", 0);
            scenario.timer[0].second = false;
            scenario.timer[1].second = true;
            music["lvl3"].stop();
            sounds["wearenoslaves"].play();
            sounds["wearenoslaves"].setPlayingOffset(seconds(4));
        }
        if ((scenario.timer[1].first > 3500) && (scenario.timer[1].second))
        {
            newMessage("But I have vodka and dotka", 0);
            scenario.timer[1].second = false;
            scenario.timer[2].second = true;
        }
        if ((scenario.timer[2].first > 3500) && (scenario.timer[2].second))
        {
            newMessage("Thank you for playing!", 0);
            scenario.timer[2].second = false;
            scenario.timer[3].second = true;
            
        }
        if ((scenario.timer[3].first > 7500) && (scenario.timer[3].second))
        {
            players[0]->win = true;
            scenario.stop();
        }

        break;
    }
    default:
        break;
    }
}
