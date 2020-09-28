#include "engine.h"

using namespace sf;

void Engine::input()
{
    if (!gameInterface.getActive()) inGameKeyInputs = true;
    if (inGameKeyInputs)
    {
        if (Keyboard::isKeyPressed(Keyboard::A)) players[0]->setKey("L");
        if (Keyboard::isKeyPressed(Keyboard::D)) players[0]->setKey("R");
        if (Keyboard::isKeyPressed(Keyboard::W)) players[0]->setKey("Up");
        if (Keyboard::isKeyPressed(Keyboard::S)) players[0]->setKey("Down");
        if (Keyboard::isKeyPressed(Keyboard::Space)) players[0]->setKey("Space");

        if (players.size() > 1)
        {
            if (Keyboard::isKeyPressed(Keyboard::Left)) players[1]->setKey("L");
            if (Keyboard::isKeyPressed(Keyboard::Right)) players[1]->setKey("R");
            if (Keyboard::isKeyPressed(Keyboard::Up)) players[1]->setKey("Up");
            if (Keyboard::isKeyPressed(Keyboard::Down)) players[1]->setKey("Down");
            if (Keyboard::isKeyPressed(Keyboard::Enter)) players[1]->setKey("Space");
        }

        if (Keyboard::isKeyPressed(Keyboard::Q)) 
        { 
            newMessage(task, 0);
        }
        //if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) 
        {
            inGameKeyInputs = false;
            gameInterface.callInGameMenu();
        }
    }

}

