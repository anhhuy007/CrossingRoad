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

ObjectType GameObject::getObjType() const
{
	return objType;
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

void GameObject::SetCollisionPoints(std::vector<CollisionPoint>_collisionPoints) {
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

void GameObject::MoveDown(int &planePos) {
	position.X += moveDownSpeed.X_VERTICAL;
	position.Y += moveDownSpeed.Y_VERTICAL;
	if (planePos % 3 == 0) {
		position.X += 1;
		position.Y += 1;
	}
	planePos += 1;
}



