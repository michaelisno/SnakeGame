#include "Interactable.h"

void Interactable::RandomisePosition(int width, int height, const std::vector<std::pair<int,int>> &occupied)
{
	bool validPosition = false;

	while (!validPosition)
	{
		m_xPosition = rand() % width;
		m_yPosition = rand() % height;

		validPosition = true;

		for (const auto &position : occupied)
		{
			if (position.first == m_xPosition && position.second == m_yPosition)
			{
				validPosition = false;
				break;
			}
		}
	}
}