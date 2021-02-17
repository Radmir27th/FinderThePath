//Project: "Нахождение пути в лабиринте"
//Author: Who doesn't know how to code (Radmir)
//Start coding: 05.02.2021
//End coding, but not completed : 12.02.2021


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <ctime>



using namespace sf;


struct cell 
{
	RectangleShape paint;
	char mark;
	int flag;
	int weight;
	cell() {
		weight = 0;
		mark = ' ';
		flag = 10000;
	}
};

struct coor
{
	int x;
	int y;
};
std::vector<coor> queue; // Очередь графа
std::vector<coor>theWay; // Для храниения кратчайшего пути 

bool isPressed = false;
bool found = false;
bool some = false;

// Алгоритм Дейикстры


void searchDijkstra(int &x, int &y, std::vector<std::vector <cell>> &grid1)
{
	
	int i = -1;
	static const int dx = x, dy = y;
	while (grid1[y][x].mark != 'A') {
		if (x > 0 && x < grid1[0].size() - 1 && y > 0 && y < grid1.size() - 1) {
			if (grid1[y + 1][x].mark != 'V' && grid1[y + 1][x].mark != 'W')
			{

				if (grid1[y + 1][x].flag > grid1[y][x].flag + grid1[y + 1][x].weight)
				{
					grid1[y + 1][x].flag = grid1[y][x].flag + grid1[y + 1][x].weight;
					queue.push_back({ x, y + 1 });
				}
			}
			if ( grid1[y - 1][x].mark != 'V' && grid1[y - 1][x].mark != 'W')
			{
				if (grid1[y - 1][x].flag > grid1[y][x].flag + grid1[y - 1][x].weight) {
					grid1[y - 1][x].flag = grid1[y][x].flag + grid1[y - 1][x].weight;
					queue.push_back({ x , y - 1 });
				}
			}
			if ( grid1[y][x + 1].mark != 'V' && grid1[y][x + 1].mark != 'W');
			{
				if (grid1[y][x + 1].flag > grid1[y][x].flag + grid1[y][x + 1].weight) {
					grid1[y][x + 1].flag = grid1[y][x].flag + grid1[y][x + 1].weight;
					queue.push_back({ x + 1, y });
				}
			}
			if ( grid1[y][x - 1].mark != 'V' && grid1[y][x - 1].mark != 'W') {
				if (grid1[y][x - 1].flag > grid1[y][x].flag + grid1[y][x - 1].weight) {
					grid1[y][x - 1].flag = grid1[y][x].flag + grid1[y][x - 1].weight;
					queue.push_back({ x - 1, y });
				}
			}
			
		}
		grid1[y][x].mark = 'V';
		i++;
		x = queue[i].x;
		y = queue[i].y;
				
	}

	grid1[dy][dx].mark = 'B';

	while (grid1[y][x].mark != 'B') 
	{

		if ( grid1[y][x].flag - grid1[y][x].weight == grid1[y + 1][x].flag) {
			theWay.push_back({x , y+1});
			y++;
		}
		if (grid1[y][x].flag - grid1[y][x].weight == grid1[y - 1][x].flag) {
			theWay.push_back({ x , y - 1 });
			y--;
		}
		if (grid1[y][x].flag - grid1[y][x].weight == grid1[y][x + 1].flag) {
			theWay.push_back({ x + 1 , y });
			x++;
		}
		if (grid1[y][x].flag - grid1[y][x].weight == grid1[y][x - 1].flag) {
			theWay.push_back({ x - 1 , y });
			x--;
		}
	
	}
} 

void clearTheGrid(std::vector<std::vector <cell>> &grid) 
{
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[0].size(); ++j)
		{
		
			if (grid[i][j].mark != 'A' && grid[i][j].mark != 'B') {
				if (grid[i][j].mark == 'W')
					grid[i][j].mark = 'W';
				else
					grid[i][j].mark = ' ';
			}
			if (grid[i][j].mark != 'W') {
				grid[i][j].flag = 10000;
				grid[i][j].paint.setFillColor(Color::White);
				grid[i][j].paint.setOutlineColor(Color::Black);
			}
			else {
				grid[i][j].flag = -1;
				grid[i][j].paint.setFillColor(Color::Black);
				grid[i][j].paint.setOutlineColor(Color::Black);
			}

			
			
		}
	}
}

void manip(CircleShape &tri, RectangleShape &rect, std::vector<std::vector <cell>> &grid) {
	int gx = int(tri.getPosition().x / rect.getSize().x - 1);
	int gy = int(tri.getPosition().y / rect.getSize().y);
	clearTheGrid(grid);
	queue.clear();
	theWay.clear();
	grid[gy][gx].flag = 0;
	searchDijkstra(gx, gy, grid);

	for (int i = 0; i < queue.size(); ++i) {
		grid[queue[i].y][queue[i].x].paint.setFillColor(Color::Green);
	}
	for (int j = 0; j < theWay.size(); ++j) {
		grid[theWay[j].y][theWay[j].x].paint.setFillColor(Color::Yellow);
		grid[theWay[j].y][theWay[j].x].paint.setOutlineColor(Color::Yellow);
	}
}


int main() {
	
	ContextSettings settings; // сглаживание
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(1500, 900), "Maze");// Объект, главное окно приложения
;

	RectangleShape rect;
	rect.setSize(Vector2f(30, 30));
	rect.setFillColor(Color::White);
	rect.setOutlineThickness(3.f);
	rect.setOutlineColor(Color::Black);

	CircleShape tri(10, 3);
	tri.setFillColor(Color::Black);
	tri.setPosition(rect.getSize().x * 20 + 3, rect.getSize().y * 10 - 15);

	enum // Режим настройки 
	{
		AIM, // Цель 
		MAZE, // Стены лабиринта
 		BEGIN, // Точка с которой начнется поиск
		SEARCH, // Режим поиска
		END
	} 
	mode = MAZE; // Начинаем с настройки цели

	CircleShape aim(10);
	aim.setFillColor(Color::Black);
	aim.setPosition(rect.getSize().x * 30 + 3 , rect.getSize().y * 10 - 15);
	int sizeX = window.getSize().x / (rect.getSize().x + 1);
	int sizeY = window.getSize().y / (rect.getSize().x + 1);
	std::vector<std::vector <cell>> grid(sizeY);
	
	srand(time(0));
	for (int i = 0; i < sizeY; ++i) 
	{
		
		grid[i].resize(sizeX);
		for (int j = 0; j < sizeX; ++j)
		{
			if (i == 0 || j == 0 || j == sizeX - 1 || i == sizeY - 1) {
				grid[i][j].paint = rect;
				grid[i][j].paint.setFillColor(Color::Black);
				grid[i][j].paint.setOutlineColor(Color::Transparent);
				grid[i][j].mark = 'W';
				grid[i][j].flag = -1;
			}
			else {
				grid[i][j].paint = rect;
				grid[i][j].weight = 1 + rand() % 60;
			}
			if (i == int(tri.getPosition().y / 30) && j == int(tri.getPosition().x / 30)) {
				grid[i][j - 1].mark = 'B';

			}
			if (i == int(aim.getPosition().y / 30) && j == int(aim.getPosition().x / 30))
				grid[i][j - 1].mark = 'A';
		}
	}
	int x = rect.getSize().x, y = 10;
	Mouse mouse;

	int time = 0;
	int f = 0;
	int s = 1;
	int t = 2;
	int ft = 3;
	int w = 0;
	while (window.isOpen()) // Main Loop
	{

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		//Update
		int mX = mouse.getPosition(window).x;
		int mY = mouse.getPosition(window).y;
	
		if (mX / 30 == int(aim.getPosition().x / 30) && mY / 30 == int(aim.getPosition().y / 30) && Mouse::isButtonPressed(Mouse::Left) && grid[mY / 30][mX / 30 - 1].mark == 'A')
		{
			mode = AIM;
		}
		if (mode == AIM) {
			if (Mouse::isButtonPressed(Mouse::Left) )
			{
				aim.setPosition(mX, mY);
				aim.setPosition(int(aim.getPosition().x / 30) * 30 + 3, int(aim.getPosition().y / 30) * 30 + 15);
				grid[mY / 30][mX / 30 - 1].mark = ' ';
				isPressed = false;
			}
			else {
				isPressed = true;
				grid[int(aim.getPosition().y / 30)][int(aim.getPosition().x / 30) - 1].mark = 'A';
				mode = MAZE;
				
			}
			if (found == true && isPressed == true) {
				manip(tri, rect, grid);
			}

		}
		if (mX / 30 <= 0 || mX / 30 >= sizeX || mY / 30 <= 0 || mY / 30 >= sizeY)
		{
			mX = 1;
			mY = 1;
		}

		if (mX / 30 == int(tri.getPosition().x / 30) && mY / 30 == int(tri.getPosition().y / 30) && Mouse::isButtonPressed(Mouse::Left) && grid[mY / 30][mX / 30 - 1].mark == 'B')
		{
			mode = BEGIN;
		}
		if (mode == BEGIN)
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				tri.setPosition(mX, mY);
				tri.setPosition(int(tri.getPosition().x / 30) * 30 + 3, int(tri.getPosition().y / 30) * 30 + 15);
				grid[mY / 30][mX / 30 - 1].mark = ' ';

			}
			else {
				grid[int(tri.getPosition().y / 30)][int(tri.getPosition().x / 30) - 1].mark = 'B';
				mode = MAZE;
			}
			if (isPressed == true && found == true)
				manip(tri, rect, grid);


		}
		if (mode == MAZE) 
		{
			if (Mouse::isButtonPressed(Mouse::Left) && grid[mY / rect.getSize().x][mX / rect.getSize().x - 1].mark != 'B' && grid[mY / rect.getSize().x][mX / rect.getSize().x - 1].mark != 'A') {
				grid[mY / rect.getSize().x][mX / rect.getSize().x - 1].paint.setFillColor(Color::Black);
				grid[mY / rect.getSize().x][mX / rect.getSize().x - 1].paint.setOutlineColor(Color::Black);
				grid[mY / rect.getSize().x][mX / rect.getSize().x - 1].mark = 'W';
				grid[mY / rect.getSize().x][mX / rect.getSize().x - 1].flag = -1;
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
				mode = SEARCH;
			if (isPressed == true && found == true) {
				manip(tri, rect, grid);
			}
		}
		if (mode == SEARCH) 
		{
			int gx = int(tri.getPosition().x / rect.getSize().x - 1);
			int gy = int(tri.getPosition().y / rect.getSize().y);
		
			grid[gy][gx].flag = 0;
			grid[int(tri.getPosition().y  / rect.getSize().y)][int(tri.getPosition().x  / rect.getSize().x - 1)].paint.setFillColor(Color::Blue);
			searchDijkstra(gx, gy, grid);
			mode = END;
			w = theWay.size() - 1;
			found = true;			
		}
		time++;
		
		//Draw

		window.clear(Color::White);

	
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[0].size(); ++j) 
			{
				
				grid[i][j].paint.setPosition(x, y);
				window.draw(grid[i][j].paint);
				x += rect.getSize().x;

			}

			y += rect.getSize().y;
			x = rect.getSize().x;
		}
		y = 10;
		if (time >= 1 && queue.size() != 0 && some == false)
		{
			grid[queue[f].y][queue[f].x].paint.setFillColor(Color::Green);
			window.draw(grid[queue[f].y][queue[f].x].paint);
			grid[queue[s].y][queue[s].x].paint.setFillColor(Color::Green);
			window.draw(grid[queue[s].y][queue[s].x].paint);
			grid[queue[t].y][queue[t].x].paint.setFillColor(Color::Green);
			window.draw(grid[queue[t].y][queue[t].x].paint);
			grid[queue[ft].y][queue[ft].x].paint.setFillColor(Color::Green);
			window.draw(grid[queue[ft].y][queue[ft].x].paint);
			f++;
			s++;
			t++;
			ft++;
			time = 0;
			if (ft == queue.size())
				queue.clear();
		}
		
		if (time >= 5 && queue.size() == 0 && theWay.size()!=0 && some == false)
		{
			grid[theWay[w].y][theWay[w].x].paint.setFillColor(Color::Yellow);
			grid[theWay[w].y][theWay[w].x].paint.setOutlineColor(Color::Yellow);
			time = 0;
			if (w == 0) {
				grid[aim.getPosition().y / 30][aim.getPosition().x / 30 - 1].paint.setFillColor(Color::Yellow);
				grid[aim.getPosition().y / 30][aim.getPosition().x / 30 - 1].paint.setOutlineColor(Color::Yellow);
				theWay.clear();
				some = true;
			}	
			w--;
		}
		window.draw(aim);
		window.draw(tri);
		window.display();
	}
	return 0;
}