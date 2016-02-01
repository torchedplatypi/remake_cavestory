/*
 * animatedsprite.h
 *
 *  Created on: Dec 28, 2015
 *      Author: torchedplatypi
 */

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>
#include <string>
#include <vector>
#include "sprite.h"
#include "globals.h"

class Graphics;

/* AnimatedSprite class
 * Holds logic for animating sprites
 */

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
			int width, int height, float posX, float posY, float timeToUpdate);

	/* void playAnimation
	 * Plays the animation provided it's not already playing
	 */
	void playAnimation(std::string animation, bool once = false);

	/* void update
	 * Updates the animated sprite (depending on timer)
	 */
	void update(int elapsedTime);

	void draw(Graphics &graphics, int x, int y);

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	/* void resetAnimations
	 * Resets all animations associated with the sprite
	 */
	void resetAnimations();

	void stopAnimation();

	/* void setVisible
	 * changes the visibility of the animated sprite
	 */
	void setVisible(bool);

	/* void animationDone
	 * Logic that happens when an animation finishes
	 */
	virtual void animationDone(std::string currentAnimation) = 0;

	/* void setupAnimations
	* A required function that sets up all animations for a sprite
	*/
	virtual void setupAnimations() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect> > _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
};

#endif /* ANIMATEDSPRITE_H */
