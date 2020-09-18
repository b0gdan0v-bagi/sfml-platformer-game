#include "engine.h"

using namespace sf;

void Engine::update(float time, Player& p, Player& p2)
{
    p.update(time);
    p2.update(time);

    // all entities update
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();)
    {
        (*it)->update(time);
        if ((*it)->life == false)
        {
            it = entities.erase(it);
        }
        else it++;
    }
}