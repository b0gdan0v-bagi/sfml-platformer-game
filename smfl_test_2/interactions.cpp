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
        /*if ((*it)->getRect().intersects(players[0]->getRect()))
        {
            //if (((*it)->name == "EasyEnemy") || ((*it)->name == "Skelleton"))
            if ((*it)->type == "enemy")
            {
                if (players[0]->dy > 0)
                {
                    (*it)->dx = 0;
                    players[0]->dy = -0.2;
                    (*it)->health = 0;
                }
                else {
                    //players[0]->health -= 5;
                }
            }
        }*/
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
    if (players[0]->win)
    {
        players[0]->win = false;
        sleep(milliseconds(50));
        numberLevel++;
        return true;
    }
}

bool Engine::checkDefeat()
{
    return false;
}