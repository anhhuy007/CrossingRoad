#include "GameObject.h"

#include <iostream>

short GameObject::getWidth() {
	return width;
}

short GameObject::getHeight() {
	return height;
}

COORD GameObject::getPosition() {
	return position;
}

void GameObject::setPosition(COORD _position) {
	position = _position;
}



