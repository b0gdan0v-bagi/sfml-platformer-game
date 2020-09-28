#include "engine.h"

using namespace sf;

void Engine::update(float time)
{
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
            it = entities.erase(it);
        }
        else it++;
    }
   // REMEMBER playerBars size must be <= players size
    for (int i = 0; i < playerBars.size(); ++i)
    {
        playerBars[i]->update("Volodya", players[i]->getHealth(), players[i]->ammo, time);
    }

    for (std::vector<Message*>::iterator itM = messages.begin(); itM != messages.end();)
    {
        int pN = (*itM)->getPlayerN();
        (*itM)->update(time, players[pN]->getRect().left + players[pN]->getRect().width, players[pN]->getRect().top - 20);
        if ((*itM)->getLife() == false)
        {
            itM = messages.erase(itM);
        }
        else ++itM;
    }

    if (data.showFps) fpsbar.update(time, data.fpsBarId);
    if (!gameInterface.getActive()) window.setMouseCursorVisible(false);
    gameInterface.update(window, gameSTATE);
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