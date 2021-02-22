#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <ctime>

using namespace sf;

class Grid
{
public:
	RectangleShape m_rect;

	struct m_cell
	{
		RectangleShape square;
		char mark;
		int flag;
		int weight;
		m_cell() {
			mark = ' ';
			flag = 10000;
		}
	};

	int m_GridX;
	int m_GridY;
	int m_time;
	int m_itQue;

	std::vector<std::vector <m_cell>> m_Grid;

	CircleShape m_Aim;
	CircleShape m_Runer;

	int m_x;
	int m_y;

	RenderWindow* m_window;
public:

	Grid() {};

	Grid(RenderWindow *win);

	void drawGrid();

	void drawNode();
};



