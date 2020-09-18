#include "engine.h"

using namespace sf;

bool Engine::input(Player& p, Player& p2)
{
    if (Keyboard::isKeyPressed(Keyboard::A)) p.key["L"] = true;
    if (Keyboard::isKeyPressed(Keyboard::D)) p.key["R"] = true;
    if (Keyboard::isKeyPressed(Keyboard::Left)) p2.key["L"] = true;
    if (Keyboard::isKeyPressed(Keyboard::Right)) p2.key["R"] = true;
    if (Keyboard::isKeyPressed(Keyboard::Up)) p2.key["Up"] = true;
    if (Keyboard::isKeyPressed(Keyboard::Down)) p2.key["Down"] = true;
    if (Keyboard::isKeyPressed(Keyboard::Enter)) p2.key["Space"] = true;
    if (Keyboard::isKeyPressed(Keyboard::W)) p.key["Up"] = true;
    if (Keyboard::isKeyPressed(Keyboard::S)) p.key["Down"] = true;
    if (Keyboard::isKeyPressed(Keyboard::Space)) p.key["Space"] = true;
    if (Keyboard::isKeyPressed(Keyboard::Q)) { std::cout << numberLevel << " " << time << std::endl; }
    //if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.setView(view);
        //Menu menu2(window);
        //if (!menu2.mainMenu(window, numberLevel, true)) {
        std::cout << "current numberLevel = " << numberLevel << "\n";
        return true;
    }
}