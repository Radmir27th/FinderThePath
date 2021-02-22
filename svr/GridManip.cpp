#include "GridManip.h"


GridManip::GridManip(RenderWindow *win)
	:Grid(win)
{
	m_MouseX = m_mouse.getPosition(*m_window).x;
	m_MouseY = m_mouse.getPosition(*m_window).y;
}

void GridManip::run() 
{
	m_MouseX = m_mouse.getPosition(*m_window).x;
	m_MouseY = m_mouse.getPosition(*m_window).y;

	if (m_MouseX / 30 <= 0 || m_MouseX / 30 >= m_GridX || m_MouseY / 30 <= 0 || m_MouseY / 30 >= m_GridY)
	{
		m_MouseX = 1;
		m_MouseY = 1;
	}

	if (m_MouseX / 30 == int(m_Aim.getPosition().x / 30) && m_MouseY / 30 == int(m_Aim.getPosition().y / 30) && Mouse::isButtonPressed(Mouse::Left) && m_Grid[m_MouseY / 30][m_MouseX / 30 - 1].mark == 'A')
	{
		m_mode = AIM;
	}
	if (m_mode == AIM) {
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			m_Aim.setPosition(m_MouseX, m_MouseY);
			m_Aim.setPosition(int(m_Aim.getPosition().x / 30) * 30 + 3, int(m_Aim.getPosition().y / 30) * 30 + 15);
			m_Grid[m_MouseY / 30][m_MouseX / 30 - 1].mark = ' ';

		}
		else
		{

			m_Grid[int(m_Aim.getPosition().y / 30)][int(m_Aim.getPosition().x / 30) - 1].mark = 'A';
			m_mode = MAZE;
		}
		

	}
	if (m_MouseX / 30 == int(m_Runer.getPosition().x / 30) && m_MouseY / 30 == int(m_Runer.getPosition().y / 30) && Mouse::isButtonPressed(Mouse::Left) && m_Grid[m_MouseY / 30][m_MouseX / 30 - 1].mark == 'B')
	{
		m_mode = START;
	}
	if (m_mode == START)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			m_Runer.setPosition(m_MouseX, m_MouseY);
			m_Runer.setPosition(int(m_Runer.getPosition().x / 30) * 30 + 3, int(m_Runer.getPosition().y / 30) * 30 + 15);
			m_Grid[m_MouseY / 30][m_MouseX / 30 - 1].mark = ' ';

		}
		else {
			m_Grid[int(m_Runer.getPosition().y / 30)][int(m_Runer.getPosition().x / 30) - 1].mark = 'B';
			m_mode = MAZE;
		}

	}
	if (m_mode == MAZE)
	{
		if (Mouse::isButtonPressed(Mouse::Left) && m_Grid[m_MouseY / m_rect.getSize().x][m_MouseX / m_rect.getSize().x - 1].mark != 'B' && m_Grid[m_MouseY / m_rect.getSize().x][m_MouseX / m_rect.getSize().x - 1].mark != 'A') {
			m_Grid[m_MouseY / m_rect.getSize().x][m_MouseX / m_rect.getSize().x - 1].square.setFillColor(Color::Black);
			m_Grid[m_MouseY / m_rect.getSize().x][m_MouseX / m_rect.getSize().x - 1].square.setOutlineColor(Color::Black);
			m_Grid[m_MouseY / m_rect.getSize().x][m_MouseX / m_rect.getSize().x - 1].mark = 'W';
			m_Grid[m_MouseY / m_rect.getSize().x][m_MouseX / m_rect.getSize().x - 1].flag = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
			m_mode = SEARCH;

	}


}