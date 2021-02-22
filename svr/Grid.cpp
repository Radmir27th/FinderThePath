#include "Grid.h"


Grid::Grid(RenderWindow *win):m_window(win)
{
	m_itQue = 0;
	m_time = 0;
	m_rect.setSize(Vector2f(30, 30));
	m_rect.setFillColor(Color::White);
	m_rect.setOutlineThickness(3.f);
	m_rect.setOutlineColor(Color::Black);

	m_GridX = m_window->getSize().x / (m_rect.getSize().x + 1);
	m_GridY = m_window->getSize().y / (m_rect.getSize().x + 1);

	m_Aim.setRadius(10);
	m_Aim.setFillColor(Color::Black);
	m_Aim.setPosition(m_rect.getSize().x * 30 + 3, m_rect.getSize().y * 10 - 15);

	m_Runer.setPointCount(3);
	m_Runer.setRadius(10);
	m_Runer.setFillColor(Color::Black);
	m_Runer.setPosition(m_rect.getSize().x * 20 + 3, m_rect.getSize().y * 10 - 15);
	m_Grid.resize(m_GridY);

	for (int i = 0; i < m_GridY; ++i)
	{

		m_Grid[i].resize(m_GridX);
		for (int j = 0; j < m_GridX; ++j)
		{
			if (i == 0 || j == 0 || j == m_GridX - 1 || i == m_GridY - 1) {
				m_Grid[i][j].square = m_rect;
				m_Grid[i][j].square.setFillColor(Color::Black);
				m_Grid[i][j].square.setOutlineColor(Color::Transparent);
				m_Grid[i][j].mark = 'W';
				m_Grid[i][j].flag = -1;
			}
			else {
				m_Grid[i][j].square = m_rect;
				m_Grid[i][j].weight = 2 + rand() % 10;
			}
			if (i == int(m_Runer.getPosition().y / 30) && j == int(m_Runer.getPosition().x / 30)) {
				m_Grid[i][j - 1].mark = 'B';

			}
			if (i == int(m_Aim.getPosition().y / 30) && j == int(m_Aim.getPosition().x / 30))
				m_Grid[i][j - 1].mark = 'A';
		}
	}
}
void Grid::drawGrid() {

	m_x = m_rect.getSize().x;
	m_y = 10;

	for (int i = 0; i < m_GridY; ++i)
	{
		for (int j = 0; j < m_GridX; ++j)
		{

			m_Grid[i][j].square.setPosition(m_x, m_y);
			m_window->draw(m_Grid[i][j].square);
			m_x += m_rect.getSize().x;

		}

		m_y += m_rect.getSize().y;
		m_x = m_rect.getSize().x;
	}
}
void Grid::drawNode() 
{
	m_window->draw(m_Runer);
	m_window->draw(m_Aim);
}
