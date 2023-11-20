#include "GameObject.h"

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

void GameObject::setCollisionPoints(std::vector<CollisionPoint>_collisionPoints) {
	collisionPoints = _collisionPoints;
}

void GameObject::WriteCollisionPoints() {
	for (int i = 0; i < collisionPoints.size(); i++) {
		COORD pos = {
			short(collisionPoints[i].first.X + position.X),
			short(collisionPoints[i].first.Y + position.Y)
		};
		int type = collisionPoints[i].second;
		game->AddCollisionPoint(pos, type);

		//std::cout << pos.X << " " << pos.Y << " " << type << std::endl;
	}
	//system("pause");
}



