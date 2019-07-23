#ifndef NODETRACKER_H
#define NODETRACKER_H

#include <vector>
#include <random>

class NodeTracker {
private:
	std::vector<std::vector<bool>> visited;
	std::mt19937 rng;

public:
	NodeTracker(int w, int h, uint32_t seed);
	~NodeTracker();

	bool IsVisited(int x, int y);
	void setVisited(int x, int y);
	unsigned char GetUnvisitedNeighbour(int x, int y);
	void InitializeRandom32(uint32_t seed);
};

#endif // !NODETRACKER_H

