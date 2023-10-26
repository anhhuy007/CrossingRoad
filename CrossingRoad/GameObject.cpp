#include "GameObject.h"

#include <iostream>

int GameObject::getWidth() {
	return width;
}

int GameObject::getHeight() {
	return height;
}

COORD GameObject::getPosition() {
	return position;
}

void GameObject::setPosition(COORD _position) {
	position = _position;
}



