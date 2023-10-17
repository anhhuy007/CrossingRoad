#include "GameObject.h"

#include <iostream>

GameObject::GameObject(short _width, short _height) {
	width = _width;
	height = _height;
	wrappedBox = { 0, 0, short(width - 1), short(height - 1) };
	sprite = Graphic::Sprite(width, height);
}

GameObject::GameObject(Graphic::Sprite _sprite) {
	width = _sprite.getWidth();
	height = _sprite.getHeight();
	wrappedBox = { 0, 0, short(width - 1), short(height - 1) };
	sprite = _sprite;
}

GameObject::~GameObject() {
	
}

short GameObject::getWidth() {
	return width;
}

short GameObject::getHeight() {
	return height;
}

SMALL_RECT GameObject::getWrappedBox() {
	return wrappedBox;
}

COORD GameObject::getPosition() {
	SMALL_RECT box = getWrappedBox();
	return { box.Left, box.Top };
}

Graphic::Sprite GameObject::getSprite()
{
	return sprite;
}

void GameObject::setPosition(COORD coord) {
	wrappedBox = { coord.X, coord.Y, short(coord.X + width - 1), short(coord.Y + height - 1) };
}



