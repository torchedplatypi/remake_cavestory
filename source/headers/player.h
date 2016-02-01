/*
 * player.h
 *
 *  Created on: Dec 29, 2015
 *      Author: torchedplatypi
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#include "animatedsprite.h"

class Graphics;

class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, Vector2 spawnPoint);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	/* void moveFunctions()
	 * Moves the player left or right by dx
	 * or
	 * Stops moving the player and preserves direction
	 */
	void moveLeft();
	void moveRight();
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	void handleTileCollisions(std::vector<Rectangle> &others);

	const float getX() const;
	const float getY() const;
private:
	float _dx, _dy;
	Direction _facing;
	bool _grounded;
};



#endif /* PLAYER_H */
