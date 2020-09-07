#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <list>
#include <iostream>
using namespace sf;

class AnimationHelp
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool flip, isPlaying, loop;
	Sprite sprite;

	//AnimationHelp(Image& image, int x, int y, int w, int h, int count, float Speed, int step)
	AnimationHelp()
	{
		speed = 0;
		currentFrame = 0;
		isPlaying = true;
		flip = false;
		loop = true;
	}

	void tick(float time)
	{
		if (!isPlaying) return;

		currentFrame += speed * time;
		if (currentFrame > frames.size())
		{
			currentFrame -= frames.size();
		}
		//std::cout << "current Frame :" << currentFrame << std::endl;
		int i = currentFrame;
		sprite.setTextureRect(frames[i]);
		if (flip) sprite.setTextureRect(frames_flip[i]);
		//sprite.setTextureRect(IntRect())
		//frames.
	}
};

class AnimationManager
{
public:

	std::string currentAnim;
	Texture texture;

	std::map<String, AnimationHelp> animList;
	AnimationManager()
	{}

	void create(std::string name, Image& image, int x, int y, int w, int h, int count, float speed, int step=0, bool Loop=true)
	{
		AnimationHelp a;
		a.speed = speed;
		a.loop = Loop;
		texture.loadFromImage(image);
		a.sprite.setTexture(texture);
		a.sprite.setOrigin(0, h);
		for (int i = 0; i < count; i++)
		{
			a.frames.push_back(IntRect(x + i * step, y, w, h));
			
			a.frames_flip.push_back(IntRect(x + i * step + w, y, -w, h));
		}
		animList[name] = a;
		currentAnim = name;


	}
	void draw(RenderWindow& window, int x = 0, int y = 0)
	{
		animList[currentAnim].sprite.setPosition(x, y);
		window.draw(animList[currentAnim].sprite);
	}

	void set(std::string name)
	{
		currentAnim = name;
	}
	void flip(bool b=1)
	{
		animList[currentAnim].flip = b;
	}
	void tick(float time)
	{
		animList[currentAnim].tick(time);
	}
	void pause()
	{
		animList[currentAnim].isPlaying = false;
	}
	void play()
	{
		animList[currentAnim].isPlaying = true;
	}
	void play(std::string name) { animList[name].isPlaying = true; }

	float getH() { return animList[currentAnim].frames[0].height; }

	float getW() { return animList[currentAnim].frames[0].width; }
};

#endif // ANIMATION_H
