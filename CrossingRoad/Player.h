#pragma once

#include "GameObject.h";

class Player : public GameObject {
public: 
	enum class PlayerState {
		STATE_ALIVE, 
		STATE_DEAD
	};
};

