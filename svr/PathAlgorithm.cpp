#include "PathAlgorithm.h"

PathAlgorithm::PathAlgorithm(RenderWindow *win):GridManip(win)
{
	
}
 void PathAlgorithm::DijkstrasAlgo() {
	int i = -1;
	m_gx = int(m_Runer.getPosition().x / m_rect.getSize().x - 1);
	m_gy = int(m_Runer.getPosition().y / m_rect.getSize().y);
	m_Grid[m_gy][m_gx].flag = 0;
	static const int dx = m_gx, dy = m_gy;
	while (m_Grid[m_gy][m_gx].mark != 'A') {
		m_Grid[m_gy][m_gx].mark = 'V';
		if (m_gx > 0 && m_gx < m_Grid[0].size() - 1 && m_gy > 0 && m_gy < m_Grid.size() - 1) 
		{
			if (m_Grid[m_gy + 1][m_gx].mark != 'V' && m_Grid[m_gy + 1][m_gx].mark != 'W')
			{

				if (m_Grid[m_gy + 1][m_gx].flag > m_Grid[m_gy][m_gx].flag + m_Grid[m_gy + 1][m_gx].weight)
				{
					m_Grid[m_gy + 1][m_gx].flag = m_Grid[m_gy][m_gx].flag + m_Grid[m_gy + 1][m_gx].weight;
					m_queue.push_back({ m_gx, m_gy + 1 });
				}
			}
			if (m_Grid[m_gy - 1][m_gx].mark != 'V' && m_Grid[m_gy - 1][m_gx].mark != 'W')
			{
				if (m_Grid[m_gy - 1][m_gx].flag > m_Grid[m_gy][m_gx].flag + m_Grid[m_gy - 1][m_gx].weight) {
					m_Grid[m_gy - 1][m_gx].flag = m_Grid[m_gy][m_gx].flag + m_Grid[m_gy - 1][m_gx].weight;
					m_queue.push_back({ m_gx , m_gy - 1 });
				}
			}
			if (m_Grid[m_gy][m_gx + 1].mark != 'V' && m_Grid[m_gy][m_gx + 1].mark != 'W');
			{
				if (m_Grid[m_gy][m_gx + 1].flag > m_Grid[m_gy][m_gx].flag + m_Grid[m_gy][m_gx + 1].weight) {
					m_Grid[m_gy][m_gx + 1].flag = m_Grid[m_gy][m_gx].flag + m_Grid[m_gy][m_gx + 1].weight;
					m_queue.push_back({ m_gx + 1, m_gy });
				}
			}
			if (m_Grid[m_gy][m_gx - 1].mark != 'V' && m_Grid[m_gy][m_gx - 1].mark != 'W') {
				if (m_Grid[m_gy][m_gx - 1].flag > m_Grid[m_gy][m_gx].flag + m_Grid[m_gy][m_gx - 1].weight) {
					m_Grid[m_gy][m_gx - 1].flag = m_Grid[m_gy][m_gx].flag + m_Grid[m_gy][m_gx - 1].weight;
					m_queue.push_back({ m_gx - 1, m_gy });
				}
			}

		}
	
		i++;
		m_gx = m_queue[i].x;
		m_gy = m_queue[i].y;

	}

	m_Grid[dy][dx].mark = 'B';

	while (m_Grid[m_gy][m_gx].mark != 'B')
	{

		if (m_Grid[m_gy][m_gx].flag - m_Grid[m_gy][m_gx].weight == m_Grid[m_gy + 1][m_gx].flag) {
			m_thePath.push_back({ m_gx , m_gy + 1 });
			m_gy++;
		}
		if (m_Grid[m_gy][m_gx].flag - m_Grid[m_gy][m_gx].weight == m_Grid[m_gy - 1][m_gx].flag) {
			m_thePath.push_back({ m_gx , m_gy - 1 });
			m_gy--;
		}
		if (m_Grid[m_gy][m_gx].flag - m_Grid[m_gy][m_gx].weight == m_Grid[m_gy][m_gx + 1].flag) {
			m_thePath.push_back({ m_gx + 1 , m_gy });
			m_gx++;
		}
		if (m_Grid[m_gy][m_gx].flag - m_Grid[m_gy][m_gx].weight == m_Grid[m_gy][m_gx - 1].flag) {
			m_thePath.push_back({ m_gx - 1 , m_gy });
			m_gx--;
		}

	}
	m_path = m_thePath.size() - 1;

}

void PathAlgorithm::drawTheSearch() 
{
	if (m_time >= 1 && m_queue.size() != 0 )
	{
		m_Grid[m_queue[m_itQue].y][m_queue[m_itQue].x].square.setFillColor(Color::Blue);
		m_window->draw(m_Grid[m_queue[m_itQue].y][m_queue[m_itQue].x].square);
		m_itQue++;
		m_time = 0;
		if (m_itQue == m_queue.size())
			m_queue.clear();
	}
}

void PathAlgorithm::drawThePath() {
	if (m_time >= 5 && m_queue.size() == 0 && m_thePath.size() != 0 )
	{
		m_Grid[m_thePath[m_path].y][m_thePath[m_path].x].square.setFillColor(Color::Yellow);
		m_Grid[m_thePath[m_path].y][m_thePath[m_path].x].square.setOutlineColor(Color::Yellow);
		m_time = 0;
		if (m_path == 0) {
			m_Grid[m_Aim.getPosition().y / 30][m_Aim.getPosition().x / 30 - 1].square.setFillColor(Color::Yellow);
			m_Grid[m_Aim.getPosition().y / 30][m_Aim.getPosition().x / 30 - 1].square.setOutlineColor(Color::Yellow);
			m_thePath.clear();
		}
		m_path--;
	}
}