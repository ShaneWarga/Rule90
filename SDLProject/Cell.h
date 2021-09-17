#pragma once
#include "GameObject.h"
#include "CellStates.h"
#include "Circle.h"
#include <vector>
#include <stdexcept>

class Cell : public GameObject
{
private:
	std::unique_ptr<SDL_Rect> cell;
	std::unique_ptr<Circle> cell_circ;
	bool rect;
public:
	Cell(std::unique_ptr<Vector2> initialPosition, int size, bool isRect);
	~Cell();
	void Render() override;
	void Update() override;
};


