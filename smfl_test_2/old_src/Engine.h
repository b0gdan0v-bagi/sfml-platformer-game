//#ifndef ENGINE_H
//#define ENGINE_H
#include <SFML/Graphics.hpp>
#include "creatures.h"
#include "level.h"
#include <vector>
#include <list>


using namespace sf;

class Engine
{
public:

    //RenderWindow m_Window;
    RenderWindow window;
    TileMap lvl;
    Sprite m_SpriteVodka;
    Texture m_TextureVodka;
    // Declaring the sprite and texture for the background
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;
    Vector2u TextureSize;  //Added to store texture size.
    Vector2u WindowSize;   //Added to store window size.
    View view;
    // creation of volodya
    Image heroImage;

    Image easyEnemyImage;
 //   Player p_Player;
    Object player;
    Object easyEnemyObject;

    Engine();

    
  //  MapBlock blockTEST;
    /*
    void input();
    void update(float dtAsSeconds);
    void draw();
    void blocks();*/
    //void setPlayerCoordinateForView(float x, float y);




    // engine constructor


    // start call all private functions
    void start();

};

//#endif