#include "animation.h"

using namespace sf;

AnimationHelp::AnimationHelp()
{
	speed = 0;
	currentFrame = 0;
	isPlaying = true;
	flip = false;
	loop = true;
}

void AnimationHelp::tick(float time)
{
	if (!isPlaying) return;

	currentFrame += speed * time;
	if (currentFrame > frames.size())
	{
		currentFrame -= frames.size();
		if (!loop)
		{
			isPlaying = false;
			return;
		}
	}
	int i = currentFrame;
	sprite.setTextureRect(frames[i]);
	if (flip) sprite.setTextureRect(frames_flip[i]);
}

AnimationManager::AnimationManager() {}

void AnimationManager::create(std::string name, Image& image, int x, int y, int w, int h, int count, float speed, int step, bool Loop)
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

void AnimationManager::loadFromXML(std::string fileName, Image& image)
{
	tinyxml2::XMLDocument document;
	texture.loadFromImage(image);
	if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Loading file " << fileName << " failed..." << std::endl;
		//return false;
	}

	tinyxml2::XMLElement* head = document.FirstChildElement("sprites");
	tinyxml2::XMLElement* animElement = head->FirstChildElement("animation");

	while (animElement)
	{
		AnimationHelp anim;
		currentAnim = animElement->Attribute("title");
		//std::cout << "currentAnim " << currentAnim << std::endl;
		int delay = atoi(animElement->Attribute("delay"));
		anim.speed = 1.0 / delay; anim.sprite.setTexture(texture);

		tinyxml2::XMLElement* cut = animElement->FirstChildElement("cut");

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

void AnimationManager::draw(RenderWindow& window, int x, int y)
{
	animList[currentAnim].sprite.setPosition(x, y);
	window.draw(animList[currentAnim].sprite);
}