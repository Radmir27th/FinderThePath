


#include "PathAlgorithm.h"

int main()
{
	RenderWindow *window = new RenderWindow(VideoMode(1500, 900), "PathFinder");
	
	PathAlgorithm grid(window);
	
	while (window->isOpen()) // Main Loop
	{

		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed)
				window->close();
		}

		grid.run();
		grid.m_time++;
		if (grid.m_mode == GridManip::SEARCH)
		{
			grid.DijkstrasAlgo();
			grid.m_mode = GridManip::END;

		}
		window->clear(Color::White);

		grid.drawTheSearch();
		grid.drawThePath();
		grid.drawGrid();
		grid.drawNode();


		window->display();
	}
	return 0;
    
}

