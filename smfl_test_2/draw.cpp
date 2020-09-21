#include "engine.h"

using namespace sf;

void Engine::draw(TileMap& lvl, statBar& bar1, statBar& bar2)
{
    window.clear(Color(77, 83, 140));
    player1View.setCenter(players[0]->getPos().x, players[0]->getPos().y);

    window.setView(player1View);

    window.draw(lvl);

    // draw all entites
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        (*it)->draw(window);
    }

    bar1.draw(window);
    for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
    {
        (*itPlayer)->draw(window);
    }

    if (pvp) // for split screen
    {
        player2View.setCenter(players[1]->getPos().x, players[1]->getPos().y);
        window.setView(player2View);

        window.draw(lvl);

        // draw all entites
        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
        {
            (*it)->draw(window);
        }

        for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
        {
            (*itPlayer)->draw(window);
        }

        bar2.draw(window);
    }


    window.display();
}