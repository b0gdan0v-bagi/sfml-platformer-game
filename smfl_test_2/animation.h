#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"
#include "tinyxml2.h"
#include <vector>
#include <list>
#include <iostream>
//#include "level.h"
using namespace sf;

class AnimationHelp
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool flip, isPlaying, loop;
	Sprite sprite;
	AnimationHelp();
	void tick(float time);
};

class AnimationManager
{
public:

	std::string currentAnim;
	Texture texture;

	std::map<String, AnimationHelp> animList;
	AnimationManager();

	void create(std::string name, Image& image, int x, int y, int w, int h, int count, float speed, int step = 0, bool Loop = true);

	void loadFromXML(std::string fileName, Image& image);

	void draw(RenderWindow& window, int x = 0, int y = 0);

	void set(std::string name) { currentAnim = name; }

	void flip(bool b = 1) { animList[currentAnim].flip = b; }

	void tick(float time) { animList[currentAnim].tick(time); }

	void pause() { animList[currentAnim].isPlaying = false; }

	void play() { animList[currentAnim].isPlaying = true; }

	void setLoop(std::string name) { animList[name].loop = false; }

	void play(std::string name) { animList[name].isPlaying = true; }

	bool isPlaying() { return animList[currentAnim].isPlaying; }

	float getH() { return animList[currentAnim].frames[0].height; }

	float getW() { return animList[currentAnim].frames[0].width; }
};

#endif ANIMATION_H
