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
            sounds["magnum"].play();
            entities.push_back(new Bullet(
                animationManagerList["bullet"], "Bullet", *lvl[0], (*itPlayer)->getPos().x,
                (*itPlayer)->getPos().y + (*itPlayer)->getRect().height / 2,
                (*itPlayer)->getDir(), (*itPlayer)->getName()));
            data.numberOfShots++;
        }//if shoot - making bullet
    }
}

void Engine::entitiesInteractions()
{
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {//boss shooting
        if (((*it)->getName() == "feel") && (data.numberLevel != 1))
        {
            if ((*it)->canShoot)
            {
                float y_for_bullet;
                bool find_direction;
                (*it)->canShoot = false;
                switch ((*it)->gun_number)
                {
                    
                case 0:
                {
                    if ((*it)->getRect().left < players[0]->getRect().left) find_direction = false;
                    else find_direction = true;
                    y_for_bullet = (*it)->getPos().y;
                    break;
                }
                case 1: {find_direction = true; y_for_bullet = (*it)->getPos().y + (*it)->getRect().height / 2; break; }
                case 2: {find_direction = false; y_for_bullet = (*it)->getPos().y + (*it)->getRect().height / 2; break; }
                case 3: {find_direction = true; y_for_bullet = (*it)->getPos().y + (*it)->getRect().height - 15; break; }
                case 4: {find_direction = false; y_for_bullet = (*it)->getPos().y; break; }
                case 5: {find_direction = true; y_for_bullet = (*it)->getPos().y; break; }
                case 6: {find_direction = false; y_for_bullet = (*it)->getPos().y + (*it)->getRect().height - 15; break; }
                default:
                    break;
                }  
                if ((*it)->gun_number != 0) 
                {
                    entities.push_back(new Bullet(
                        animationManagerList["bullet"], "Bullet", *lvl[0], (*it)->getPos().x,
                        y_for_bullet,
                        find_direction, (*it)->getName()));
                }
            }
        }
        for (std::list<Entity*>::iterator bullet = entities.begin(); bullet != entities.end(); bullet++)
        {
            if ((*it)->getRect() != (*bullet)->getRect()) //different rectanglles
            {
                //if (((*it)->getRect().intersects((*bullet)->getRect())) && ((*it)->name == "EasyEnemy") && ((*bullet)->name == "Bullet"))// intersects of bullet and enemy
                if (((*it)->getRect().intersects((*bullet)->getRect())) &&
                    ((*it)->getType() == "enemy") &&
                    ((*bullet)->getName() == "Bullet") && 
                    ((*bullet)->getType() != "feel") &&
                    ((*bullet)->getDamage() != 0))// intersects of bullet and enemy
                {
                    //(*it)->dx = 0;//stop enemy
                    (*it)->takeDamage((*bullet)->getDamage()); // damage enemy
                    (*bullet)->setDamage(0);
                    (*bullet)->setHealth(0); // kill bullet
                }
                if (((*it)->getRect().intersects((*bullet)->getRect())) &&
                    ((*it)->getType() == "boss") &&
                    ((*bullet)->getName() == "Bullet") && ((*bullet)->getType() != "feel") &&
                    ((*bullet)->getDamage() != 0))// intersects of bullet and enemy
                {
                    //(*it)->dx = 0;//stop enemy
                    (*it)->takeDamage((*bullet)->getDamage()); // damage enemy
                    (*bullet)->setDamage(0);
                    (*bullet)->setHealth(0); // kill bullet
                }
            }

        }
        for (std::vector<Player*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
        {
            if ((*it)->getRect().intersects((*itPlayer)->getRect()))
            {
                if (pvp)
                {
                    if (((*it)->getName() == "Bullet") && ((*it)->getType() != (*itPlayer)->getName()) && ((*itPlayer)->getHealth() > 0))
                    {
                        if ((*itPlayer)->ifDuck() == false) //players get normal bullet if he staying
                        {
                            (*itPlayer)->takeDamage((*it)->getDamage());
                            (*it)->setDamage(0);
                            (*it)->setHealth(0); // kill bullet
                        }
                        else
                        { // player was sitting and we need to calculate his new rect which is lower in y then original
                            if ((*it)->getRect().intersects(FloatRect((*itPlayer)->getRect().left,
                                (*itPlayer)->getRect().top + (*itPlayer)->getDuckDiff().y,
                                (*itPlayer)->getRect().width, (*itPlayer)->getRect().height)))
                            {
                                (*itPlayer)->takeDamage((*it)->getDamage());
                                (*it)->setDamage(0);
                                (*it)->setHealth(0); // kill bullet
                            }
                        }
                    }
                }
                if (((*itPlayer)->getLife()) && ((*it)->getLife())) collission_EvsP(it, itPlayer);
                if (((*it)->getName() == "vodka") && ((*itPlayer)->getLife()) && ((*it)->getLife()))
                {
                    if ((*itPlayer)->getSpeed().y > 0)
                    {
                        (*itPlayer)->takeHP(5);
                        (*itPlayer)->ammo += 7;
                        newMessage("I got health and ammo!", std::distance(players.begin(), itPlayer));
                        (*it)->kill();
                        sounds["kick"].play();
                        data.numberOfBottlesGained++;
                    }
                }
                if (((*it)->getName() == "key") && ((*itPlayer)->getLife()) && ((*it)->getLife()))
                {
                    {// all players get key
                        for (std::vector<Player*>::iterator itPlayer2 = players.begin(); itPlayer2 != players.end(); ++itPlayer2)
                        {
                            (*itPlayer2)->setDoorKey(true);
                        }
                        sounds["enhance_success"].play();
                        sounds["enhance_success"].setVolume(15.f);
                        (*it)->kill(); // kill key
                        if (data.numberLevel == 2) newMessage("I got key!\n Go back to the door!", std::distance(players.begin(), itPlayer));
                        if (data.numberLevel == 1) newMessage("I got key!\n Beware another enemy", std::distance(players.begin(), itPlayer));
                            
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
                if (((*it)->getName() == "scenario") && ((*itPlayer)->getLife()) && ((*it)->getLife()))
                {
                    {
                        scenario.set(std::stoi((*it)->getType()));
                        (*it)->kill();
                    }
                }

                if (((*it)->getName() == "Bullet") && ((*it)->getType() == "feel") && ((*itPlayer)->getHealth() > 0))
                {
                    if ((*itPlayer)->ifDuck() == false) //players get normal bullet if he staying
                    {
                        (*itPlayer)->takeDamage((*it)->getDamage());
                        (*it)->setDamage(0);
                        (*it)->setHealth(0); // kill bullet
                        if (sounds["maslina"].getStatus() != 2) sounds["maslina"].play();
                    }
                    else
                    { // player was sitting and we need to calculate his new rect which is lower in y then original
                        if ((*it)->getRect().intersects(FloatRect((*itPlayer)->getRect().left,
                            (*itPlayer)->getRect().top + (*itPlayer)->getDuckDiff().y,
                            (*itPlayer)->getRect().width, (*itPlayer)->getRect().height)))
                        {
                            (*itPlayer)->takeDamage((*it)->getDamage());
                            (*it)->setDamage(0);
                            (*it)->setHealth(0); // kill bullet
                            if (sounds["maslina"].getStatus() != 2) sounds["maslina"].play();
                        }
                    }
                }
                

            }
            if (((*it)->getName() == "feel") && ((*it)->getHealth() < 50) && (bossFight_2nd_phase_dont_repeat))
            {
                newMessage("Cmon he is almost dead!", 0);
                bossFight_2nd_phase_dont_repeat = false;
                addNewWave = true;
            }
        }

    }
}

void Engine::collission_EvsP(std::list<Entity*>::iterator& ent, std::vector<Player*>::iterator& plr)
{
    if ((*ent)->getType() == "enemy")
    {
        (*plr)->setSpeedX((*ent)->getSpeed().x * 3);
        (*plr)->setSpeedY(-0.1);
        (*plr)->takeDamage(5);
        if ((*plr)->getHealth() == 0) (*plr)->setSpeedX(0.f);
        (*ent)->setHealth(0);
        (*ent)->setDamage(0);
        sounds["kick"].play();
    }
    if ((*ent)->getName() == "feel")
    {
        (*plr)->setSpeedX((*ent)->getSpeed().x * 3);
        (*plr)->takeDamage(5);
        if ((*plr)->getHealth() == 0) (*plr)->setSpeedX(0.f);
    }
}

bool Engine::checkWin()
{
    if ((players[0]->win) && (players[0]->getLife()))
    {
        players[0]->win = false;
        sleep(milliseconds(50));
        data.numberLevel++;
        levelChanger = true;
        levelNexter = true;
        for (int i = 0; i < players.size(); ++i)
        {
            data.playersAMMO[i] = players[i]->ammo;
            data.playersHP[i] = players[i]->getHealth();
        }
        return true;
    }
}

void Engine::checkDefeat()
{
    if ((!pvp) && (!players[0]->getLife()))
    {
        newMessage("WASTED", 0);
        for (auto i = music.begin(); i != music.end(); i++) (*i).second.stop();
        inGameKeyInputs = false;
        gameInterface.setDefeatTextVisible(true);
        gameInterface.callInGameMenu();
        if ((sounds["gameover"].getStatus() != 2) && (!defeatSoundsPlay))
        {
            defeatSoundsPlay = true;
            sounds["gameover"].play();
        }
        levelChanger = true;
    }
}





