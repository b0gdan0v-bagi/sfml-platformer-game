#include "engine.h"

using namespace sf;

void Engine::playersShooting()
{
    for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
    {
        if (((*itPlayer)->isShoot == true) && ((*itPlayer)->canShoot == true) && ((*itPlayer)->ammo > 0))
        {
            (*itPlayer)->ammo -= 1; // !!!! FOR TEST !!!!
            (*itPlayer)->isShoot = false;
            (*itPlayer)->canShoot = false;
            entities.push_back(new Bullet(
                animationManagerList["bullet"], "Bullet", *lvl[0], (*itPlayer)->getPos().x,
                (*itPlayer)->getPos().y + (*itPlayer)->getRect().height / 2,
                (*itPlayer)->getDir(), (*itPlayer)->getName()));
        }//if shoot - making bullet
    }
}

void Engine::entitiesInteractions()
{
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        if ((*it)->getRect().intersects(players[0]->getRect()))
        {

        }
        for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
        {
            if ((*it)->getRect() != (*it2)->getRect()) //different rectanglles
            {
                //if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "Bullet"))// intersects of bullet and enemy
                if (((*it)->getRect().intersects((*it2)->getRect())) &&
                    ((*it)->getType() == "enemy") &&
                    ((*it2)->getName() == "Bullet") &&
                    ((*it2)->getDamage() != 0))// intersects of bullet and enemy
                {
                    //(*it)->dx = 0;//stop enemy
                    (*it)->takeDamage((*it2)->getDamage()); // damage enemy
                    (*it2)->setDamage(0);
                    (*it2)->setHealth(0); // kill bullet
                }
            }

        }
        for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
        {
            if ((*it)->getRect().intersects((*itPlayer)->getRect()))
            {
                /*if (((*itPlayer)->ifDuck()) && ((*it)->getRect().intersects((*itPlayer)->getDuckRect())))
                {
                    if (((*it)->getName() == "Bullet") && ((*it)->getType() != (*itPlayer)->getName()) && ((*itPlayer)->getHealth() > 0))
                    {
                        (*itPlayer)->takeDamage((*it)->getDamage());
                        (*it)->setDamage(0);
                        (*it)->setHealth(0); // kill bullet
                        std::cout << "abs";
                    }
                }*/
                //if ((!(*itPlayer)->ifDuck()) && (*it)->getRect().intersects((*itPlayer)->getRect()))
                if (pvp)
                {
                    if (((*it)->getName() == "Bullet") && ((*it)->getType() != (*itPlayer)->getName()) && ((*itPlayer)->getHealth() > 0))
                    {
                        (*itPlayer)->takeDamage((*it)->getDamage());
                        (*it)->setDamage(0);
                        (*it)->setHealth(0); // kill bullet
                    }
                }
                if (((*it)->getType() == "enemy") && ((*itPlayer)->getLife()))
                {
                    (*itPlayer)->setSpeedX((*it)->getSpeed().x * 3);
                    (*itPlayer)->setSpeedY(-0.1);
                    (*itPlayer)->takeDamage(5);
                    if ((*itPlayer)->getHealth() == 0) (*itPlayer)->setSpeedX(0.f);
                    (*it)->setHealth(0);
                    (*it)->setDamage(0);
                }
                if (((*it)->getName() == "vodka") && ((*itPlayer)->getLife()) && ((*it)->getLife()))
                {
                    if ((*itPlayer)->getSpeed().y > 0)
                    {
                        (*itPlayer)->takeHP(10);
                        (*itPlayer)->ammo += 10;
                        newMessage("I got health and ammo!", std::distance(players.begin(), itPlayer));
                        (*it)->kill();
                    }
                }
                if (((*it)->getName() == "key") && ((*itPlayer)->getLife()) && ((*it)->getLife()))
                {
                    {// all players get key
                        for (std::vector<Player*>::iterator itPlayer2 = players.begin(); itPlayer2 != players.end(); ++itPlayer2)
                        {
                            (*itPlayer2)->setDoorKey(true);
                        }
                        (*it)->kill(); // kill key
                        newMessage("I got key!\n Go back to the door!", std::distance(players.begin(), itPlayer));
                        addNewWave = true;
                    }
                }
                if (((*it)->getName() == "door") && ((*itPlayer)->getLife()) && ((*it)->getLife()) && ((*itPlayer)->getDoorKey()))
                { //destroy the door if we have key
                    {
                        task = "Door is opened!";
                        newMessage(task, std::distance(players.begin(), itPlayer));
                        (*it)->kill();
                    }
                }
                if (((*it)->getName() == "trigger") && ((*itPlayer)->getLife()) && ((*it)->getLife()))
                { 
                    {
                        task = (*it)->getType(); // change output message for help
                        newMessage(task, std::distance(players.begin(), itPlayer));
                        (*it)->kill();
                        
                    }
                }
            }

        }

    }
}

bool Engine::checkWin()
{
    if ((players[0]->win) && (players[0]->getLife()))
    {
        players[0]->win = false;
        sleep(milliseconds(50));
        if (data.numberLevel < data.numberLevelMax)
        {
            data.numberLevel++;
            levelChanger = true;
            for (int i = 0; i < players.size(); ++i)
            {
                data.playersAMMO[i] = players[i]->ammo;
                data.playersHP[i] = players[i]->getHealth();
            }
        }
        return true;
    }
}

void Engine::checkDefeat()
{
    if ((!pvp) && (!players[0]->getLife()))
    {
        newMessage("WASTED", 0);
        inGameKeyInputs = false;
        gameInterface.setDefeatTextVisible(true);
        gameInterface.callInGameMenu();

        levelChanger = true;
    }
}


