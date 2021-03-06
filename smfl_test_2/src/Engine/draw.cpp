#include "engine.h"

using namespace sf;

void Engine::draw()
{
    window.clear(Color(77, 83, 140));
    drawSplitHelp(0);
    // for split screen
    if (pvp) drawSplitHelp(1); 
    window.setView(data.viewInterface);
    //gameInterface.update(window, returnToMainMenu);
    gameInterface.draw(window);
    if (data.showFps) fpsbar.draw(window);
    window.display();
}

void Engine::drawSplitHelp(int viewId)
{
    playerViews[viewId]->setCenter(players[viewId]->getPos());

    window.setView(*playerViews[viewId]);
    window.draw(*lvl[0]);
    
    // draw all entites
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        (*it)->draw(window);
    }

    for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
    {
        (*itPlayer)->draw(window);
    }
    
    if (pvp) playerBars[viewId]->draw(window);
    else
    {
        for (int i = 0; i < playerBars.size(); ++i)
        {
            playerBars[i]->draw(window);
        }
    }
    

    for (std::vector<Message*>::iterator itM = messages.begin(); itM != messages.end(); ++itM)
    {
        (*itM)->draw(window);
    }
    
}

void Engine::viewChanges()
{
    if (pvp)
    {
        playerViews[0]->setSize(data.resolution.x / 2, data.resolution.y);
        playerViews[1]->setSize(data.resolution.x / 2, data.resolution.y);
        playerViews[0]->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
        playerViews[1]->setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
    }
    else
    {
        playerViews[0]->setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        playerViews[0]->setSize(data.resolution.x, data.resolution.y);
    }
}

void Engine::newMessage(String MESSAGE, int PLAYER_N, float MESSAGE_TIMER)
{
    // delete previvous messages
    for (std::vector<Message*>::iterator itM = messages.begin(); itM != messages.end(); itM++)
    {
        if ((*itM)->getPlayerN() == PLAYER_N) (*itM)->setLife(false);
    }
    // create new
    messages.push_back(new Message(MESSAGE, MESSAGE_TIMER, font, window, PLAYER_N));
}
