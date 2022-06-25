#include "LevelMap.h"

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]) {
	//Allocate memory for the level tile map
	mMap = new int* [MAP_HEIGHT];

	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		mMap[i] = new int[MAP_WIDTH];
	}

	//Populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		for (unsigned int j = 0; j < MAP_WIDTH; j++) {
			mMap[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap() {
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		delete[] mMap[i];
	}
	delete[] mMap;
}

//Gets a tile at a position on the screen
int LevelMap::GetTileAt(unsigned int h, unsigned int w) {
	if (h < MAP_HEIGHT && w < MAP_WIDTH) {
		return mMap[h][w];
	}
	return 0;
}

//Changes a tile value at a point in the screen
void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue) {
	if (row < MAP_HEIGHT && column < MAP_WIDTH) {
		mMap[row][column] = newValue;
	}
}