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
                animationManagerList["bullet"], "Bullet", *lvl[0], (*itPlayer)->getPos().x, (*itPlayer)->getPos().y + 50,
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
            if (((*it)->getType() == "enemy") && (players[0]->getLife() ))
            {
                /*if (players[0]->getSpeed().y > 0)
                {
                    //(*it)->dx = 0;
                    players[0]->setSpeedY(-0.2);
                    (*it)->setHealth(0);
                }
                else {*/
                    players[0]->setSpeedX((*it)->getSpeed().x*3);
                    players[0]->setSpeedY(-0.1);
                    players[0]->takeDamage(5);
                    if (players[0]->getHealth() == 0) players[0]->setSpeedX(0.f);
                    (*it)->setHealth(0);
                    (*it)->setDamage(0);
                //}
            }
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
        if (pvp)
        {
            for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
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
                if ((*it)->getRect().intersects((*itPlayer)->getRect()))
                {
                    if (((*it)->getName() == "Bullet") && ((*it)->getType() != (*itPlayer)->getName()) && ((*itPlayer)->getHealth() > 0))
                    {
                        (*itPlayer)->takeDamage((*it)->getDamage());
                        (*it)->setDamage(0);
                        (*it)->setHealth(0); // kill bullet
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
        if (numberLevel < numberLevelMax)
        {
            numberLevel++;
            levelChanger = true;
        }
        return true;
    }
}

void Engine::checkDefeat()
{
    if ((!pvp) && (!players[0]->getLife()))
    {
        inGameKeyInputs = false;
        gameInterface.setDefeatTextVisible(true);
        gameInterface.callInGameMenu();
        levelChanger = true;
        //returnToMainMenu = true;
    }

}