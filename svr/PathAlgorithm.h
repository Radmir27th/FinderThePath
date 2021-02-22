#pragma once

#include "GridManip.h"

class PathAlgorithm : public GridManip
{
public:

	struct coor
	{
		int x;
		int y;
	};

	int m_gx;
	int m_gy;
	int m_path;
	std::vector<coor> m_queue; 
	std::vector<coor>m_thePath;

	

public:
	PathAlgorithm(RenderWindow *win);

	void DijkstrasAlgo();

	void drawTheSearch();

	void drawThePath();

};

