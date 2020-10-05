#include "engine.h"

using namespace sf;

void Engine::update(float time)
{
    if (addNewWave) loadEnemyWave(1);

    for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
    {
        (*itPlayer)->update(time);
    }

    // all entities update
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();)
    {
        (*it)->update(time);
        if ((*it)->getLife() == false)
        {
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
       
        if ((scenario.timer[0].first > time * 1000) && (scenario.timer[0].second))
        {
            newMessage("Welcome to " + data.name + " " + data.version, 0);
            scenario.timer[0].second = false;
        }
        if ((scenario.timer[1].first > time * 4000) && (scenario.timer[1].second))
        {
            newMessage("To skip tutorial press SPACE", 0);
            scenario.timer[1].second = false;
            scenario.stop();
        }
        break;
    }
    default:
        break;
    }
}
