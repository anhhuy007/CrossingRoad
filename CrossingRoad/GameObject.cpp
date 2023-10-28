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

void GameObject::setHeight(int _height) {
	height = _height;
}

void GameObject::setWidth(int _width) {
	width = _width;
}



