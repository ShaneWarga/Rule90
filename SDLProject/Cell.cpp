#include "Cell.h"


// USER INPUT CHANGE TO RANDOM STATE ON CLICK
 

Cell::Cell(std::unique_ptr<Vector2> initialPosition, int size, bool isRect) {
	objectColor = std::unique_ptr<ColorData>(new ColorData());
	position = std::move(initialPosition);
	rect = isRect;
	if (rect) {
		cell = std::unique_ptr<SDL_Rect>(new SDL_Rect());
		cell.get()->x = position.get()->x;
		cell.get()->y = position.get()->y;
		cell.get()->w = size;
		cell.get()->h = size;
	}
	else {
		std::unique_ptr<Vector2> pos = std::unique_ptr<Vector2>(new Vector2());
		pos.get()->x = position.get()->x;
		pos.get()->y = position.get()->y;
		cell_circ = std::unique_ptr<Circle>(new Circle(std::move(pos), size, true));
	}
}

Cell::~Cell() {
	delete position.get();
	delete objectColor.get();
	delete state.get();
	delete cell.get();
}


void Cell::Render() {
	if (rect) {
		SDL_SetRenderDrawColor(mRenderer, objectColor.get()->RED, objectColor.get()->GREEN, objectColor.get()->BLUE, objectColor.get()->ALPHA);
		SDL_RenderFillRect(mRenderer, cell.get());
	}
	else {
			cell_circ.get()->SetRenderer(mRenderer);
			cell_circ.get()->SetColorData(objectColor.get()->RED, objectColor.get()->GREEN, objectColor.get()->BLUE, objectColor.get()->ALPHA);
			cell_circ.get()->Render();
			cell_circ.get()->SetColorData(objectColor.get()->RED, objectColor.get()->GREEN, objectColor.get()->BLUE, objectColor.get()->ALPHA);
			cell_circ.get()->Render();
	}
}

//Rule 90
void Cell::Update() {
	int nextState = 0;
	std::vector<bool> neighborStates;
	if (state.get()->INIT) {
		state.get()->INIT = false;
		int init = rand() % 100 + 1;
		if (init <= 1) {
			state.get()->STATE_0 = true;
			return;
		}
	}
	for (auto currentNeighbor : neighbors) {
		CellStates* states = currentNeighbor->state.get();
		neighborStates.push_back(states->STATE_0);
	}
	//000
	if (neighborStates.size() != 3) { return; }
	if (neighborStates[0] == false && neighborStates[1] == false && neighborStates[2] == false) {
		state.get()->STATE_0 = false;
		this->SetColorData(0, 0, 0, 255);
		return;
	}
	//100
	if (neighborStates[0] == true && neighborStates[1] == false && neighborStates[2] == false) {
		state.get()->STATE_0 = true;
		this->SetColorData(255, 255, 255, 255);
		return;
	}
	//010
	if (neighborStates[0] == false && neighborStates[1] == true && neighborStates[2] == false) {
		state.get()->STATE_0 = false;
		this->SetColorData(0, 0, 0, 255);
		return;
	}
	//001
	if (neighborStates[0] == false && neighborStates[1] == false && neighborStates[2] == true) {
		state.get()->STATE_0 = true;
		this->SetColorData(255, 255, 255, 255);
		return;
	}
	//011
	if (neighborStates[0] == false && neighborStates[1] == true && neighborStates[2] == true) {
		state.get()->STATE_0 = false;
		this->SetColorData(0, 0, 0, 255);
		return;
	}
	//110
	if (neighborStates[0] == true && neighborStates[1] == true && neighborStates[2] == false) {
		state.get()->STATE_0 = true;
		this->SetColorData(255, 255, 255, 255);
		return;
	}
	//101
	if (neighborStates[0] == true && neighborStates[1] == false && neighborStates[2] == true) {
		state.get()->STATE_0 = false;
		this->SetColorData(0, 0, 0, 255);
		return;
	}
	//111
	if (neighborStates[0] == true && neighborStates[1] == true && neighborStates[2] == true) {
		state.get()->STATE_0 = false;
		this->SetColorData(0, 0, 0, 255);
		return;
	}

}