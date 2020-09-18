#include "engine.h"

using namespace sf;

void Engine::draw(Player& p, Player& p2, TileMap& lvl, statBar& bar1, statBar& bar2)
{
    window.clear(Color(77, 83, 140));
    player1View.setCenter(p.x, p.y);

    window.setView(player1View);

    window.draw(lvl);

    // draw all entites
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        (*it)->draw(window);
    }
    p2.draw(window);
    p.draw(window);
    //players[0]->update(time);
    //players[0]->draw(window);
    bar1.draw(window);

    if (pvp) // for split screen
    {
        player2View.setCenter(p2.x, p2.y);
        window.setView(player2View);

        window.draw(lvl);

        // draw all entites
        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
        {
            (*it)->draw(window);
        }
        p2.draw(window);
        p.draw(window);
        bar2.draw(window);
    }

    window.display();
}