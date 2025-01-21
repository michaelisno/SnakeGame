#include "Snake.h"

Snake::Snake(int startX, int startY)
{
	m_snakeBody.push_back({ startX, startY });

	m_directionX = 1;
	m_directionY = 0;
}

void Snake::ChangeDirection(char input)
{
	if (input == 'w' && m_directionY == 0) { m_directionX = 0; m_directionY = -1; }
	else if (input == 'a' && m_directionX == 0) { m_directionX = -1; m_directionY = 0; }
	else if (input == 's' && m_directionY == 0) { m_directionX = 0; m_directionY = 1; }
	else if (input == 'd' && m_directionX == 0) { m_directionX = 1; m_directionY = 0; }

	// debug growing
	else if (input == 'g') { AddBodySegment(1); }
}

void Snake::Move()
{
	std::pair<int, int> newHead = { m_snakeBody[0].first + m_directionX, m_snakeBody[0].second + m_directionY };
	
	m_snakeBody.insert(m_snakeBody.begin(), newHead);
	m_snakeBody.pop_back();
}

void Snake::AddBodySegment(int numberOfSegments)
{
	for (int i = 0; i < numberOfSegments; i++)
	{
		m_snakeBody.push_back(m_snakeBody.back());
	}
}

bool Snake::CheckCollision(int width, int height) const
{
	std::pair<int, int> head = m_snakeBody[0];

	if (head.first < 0 || head.second < 0 || head.first >= width || head.second >= height)
	{
		return true;
	}

	if (GetCurrentPowerUp() != 3)
	{
		for (int i = 1; i < m_snakeBody.size(); i++)
		{
			if (m_snakeBody[i] == head)
			{
				return true;
			}
		}
	}

	return false;
}