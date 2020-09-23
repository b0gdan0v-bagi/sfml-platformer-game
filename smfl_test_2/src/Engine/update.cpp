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

    playerBars[0]->update("Volodya", players[0]->getHealth(), players[0]->ammo, time);
    playerBars[1]->update("Volodya 2", players[1]->getHealth(), players[1]->ammo, time);
    //gameInterface.update(window, returnToMainMenu);
    if (!gameInterface.getActive()) window.setMouseCursorVisible(false);
}