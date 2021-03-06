#include "player.h"
#include "graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = .002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint) :
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_grounded(false)
	{
		graphics.loadImage("content/sprites/MyChar.png");
		this->setupAnimations();
	}

void Player::setupAnimations() {
	this->addAnimation(1,0,0,"idle_left",16,16,Vector2().zero());
	this->addAnimation(1,0,16,"idle_right",16,16,Vector2());
	this->addAnimation(3,0,0,"run_left",16,16, Vector2(0,0));
	this->addAnimation(3,0,16,"run_right",16,16,Vector2(0,0));
}

void Player::animationDone(std::string currentAnimation) {}

const float Player::getX() const {
	return this->_x;
}

const float Player::getY() const {
	return this->_y;
}

void Player::moveLeft() {
	this->_dx = -player_constants::WALK_SPEED;
	this->playAnimation("run_left");
	this->_facing = LEFT;
}

void Player::moveRight() {
	this->_dx = player_constants::WALK_SPEED;
	this->playAnimation("run_right");
	this->_facing = RIGHT;
}

void Player::stopMoving() {
	this->_dx = 0.0f;
	this->playAnimation(this->_facing == RIGHT ? "idle_right" : "idle_left");
}

void Player::handleTileCollisions(std::vector<Rectangle> &others){
	//Figure out what side the collision happened on and move the player accordingly
	for(int i = 0; i < others.size(); i++){
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if(collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->_y = others.at(i).getBottom() + 1;
				this->_dy = 0;
				break;
			case sides::BOTTOM:
				this->_y = others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
				this->_dy = 0;
				this->_grounded = true;
				break;
			case sides::RIGHT:
				this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
				break;
			case sides::LEFT:
				this->_x = others.at(i).getRight() + 1;
				break;
			}
		}
	}
}

void Player::update(float elapsedTime) {
	//apply gravity
	if (this->_dy <= player_constants::GRAVITY_CAP) {
		this->_dy += player_constants::GRAVITY * elapsedTime;
	}

	//move by dx
	this->_x += this->_dx * elapsedTime;
	//move by dy
	this->_y += this->_dy * elapsedTime;
	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}
