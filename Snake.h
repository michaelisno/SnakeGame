#pragma once
#include <vector>
#include <utility>

class Snake
{
private:
	std::vector<std::pair<int, int>> m_snakeBody;
	int m_directionX, m_directionY;

public:
	Snake(int startX, int startY);

	void ChangeDirection(char input);
	void Move(int amount);
	void AddBodySegment(int numberOfSegments);

	bool CheckCollision(int width, int height) const;

	const std::vector<std::pair<int, int>>& GetBody() const { return m_snakeBody; }
	std::pair<int, int> GetHead() const { return m_snakeBody[0]; }

};