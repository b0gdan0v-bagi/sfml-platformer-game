#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"
#include "tinyxml2.h"
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
		//std::cout << "animation " << name << " sucsesfully created!" << std::endl;
		//std::cout << "x: " << x << " y: " << y << " w: " << w << " h: " << h << " count: " << count << " step: " << step << "loop: " << Loop << std::endl;

	}

	void loadFromXML(std::string fileName, Image& image)
	{
		tinyxml2::XMLDocument document;
		texture.loadFromImage(image);
		if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
		{
			std::cout << "Loading file " << fileName << " failed..." << std::endl;
			//return false;
		}

		//TiXmlDocument animFile(fileName.c_str());
		
		//animFile.LoadFile();

		tinyxml2::XMLElement* head = document.FirstChildElement("sprites");
		//TiXmlElement* head;
		//head = animFile.FirstChildElement("sprites");
		
		tinyxml2::XMLElement* animElement = head->FirstChildElement("animation");
		//TiXmlElement* animElement;
		//animElement = head->FirstChildElement("animation");
		while (animElement)
		{
			AnimationHelp anim;
			currentAnim = animElement->Attribute("title");
			std::cout << "currentAnim " << currentAnim << std::endl;
			int delay = atoi(animElement->Attribute("delay"));
			anim.speed = 1.0 / delay; anim.sprite.setTexture(texture);

			tinyxml2::XMLElement* cut = animElement->FirstChildElement("cut");
			//TiXmlElement* cut;
			//cut = animElement->FirstChildElement("cut");
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));

				anim.frames.push_back(IntRect(x, y, w, h));
				anim.frames_flip.push_back(IntRect(x + w, y, -w, h));
				cut = cut->NextSiblingElement("cut");
			}

			anim.sprite.setOrigin(0, anim.frames[0].height);

			animList[currentAnim] = anim;
			animElement = animElement->NextSiblingElement("animation");
		}
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
