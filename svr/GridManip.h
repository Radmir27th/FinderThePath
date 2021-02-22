#pragma once
#include "Grid.h"

class GridManip: public Grid
{
public:
	enum Mode
	{
		AIM, // Цель 
		MAZE, // Стены лабиринта
		START, // Точка с которой начнется поиск
		SEARCH, // Режим поиска
		END
	};

public:
	Mode  m_mode = MAZE;
	Mouse m_mouse;
	int	  m_MouseX;
	int   m_MouseY;

public:
	GridManip() {}
	GridManip(RenderWindow* win);

	void run();
};

