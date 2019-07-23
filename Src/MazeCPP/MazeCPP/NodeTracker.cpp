#include "NodeTracker.h"

//define a padding of 2
#define PAD 2

NodeTracker::NodeTracker(int w, int h, uint32_t seed = 0) {
	InitializeRandom32(seed);
	visited.resize(w + 2*PAD, std::vector<bool>(h + 2*PAD, false)); //paded by 2 in each direction, cause steping by 2

	//padding
	for (int i = 0; i < w + 4; ++i) {
		//col-row
		visited[i][0] = visited[i][1] = true;
		visited[i][h + PAD+1] = visited[i][h + PAD] = true;
	}
	for (int j = 0; j < h + 4; ++j) {
		visited[0][j] = visited[1][j] = true;
		visited[w + PAD+1][j] = visited[w + PAD][j] = true;
	}
}

NodeTracker::~NodeTracker() {}

bool NodeTracker::IsVisited(int x, int y) {
	return visited[x + PAD][y + PAD]; // take padding into account
}

void NodeTracker::setVisited(int x, int y) {
	visited[x + PAD][y + PAD] = true;
}

unsigned char NodeTracker::GetUnvisitedNeighbour(int x, int y){
	bool neighbour[4]; // 4 directions
	unsigned int unvisited = 0;
	neighbour[0] = IsVisited(x - 2, y); // left
	neighbour[1] = IsVisited(x, y - 2); // up
	neighbour[2] = IsVisited(x + 2, y); // right
	neighbour[3] = IsVisited(x, y + 2); // down
	for (int i = 0; i < 4; ++i) {
		if (!neighbour[i]) {
			++unvisited;
		}
	}
	if (unvisited == 0) return 0;

	unsigned int randomPick = rng() % unvisited;
	unsigned int i = 0;
	unsigned char dir;
	for (dir = 0; dir < 4; ++dir) {
		if (!neighbour[dir]) {
			//unvisited
			if (i == randomPick) break;
			++i;
		}
	}
	return (1 << dir);
}

void NodeTracker::InitializeRandom32(uint32_t seed) {
	if (seed == 0) { // default seed
		std::random_device rd; // machine entropy to create a non-determienistic number
		seed = rd();
	}
	rng.seed(seed);
}