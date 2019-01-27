#include "RCoord.h"

RCoord::RCoord(int x, int y) : m_x(x), m_y(y)
{


}

RCoord::RCoord() : m_x(0), m_y(0)
{


}

void RCoord::printCoord()
{
	std::cout << '(' << m_x << ", " << m_y << ')' << std::endl;

}

RCoord RCoord::operator+(RCoord coord)
{
	RCoord temp;
	temp.m_x = m_x + coord.m_x;
	temp.m_y = m_y + coord.m_y;
	return temp;
}
RCoord RCoord::operator+=(RCoord coord)
{
	RCoord temp;
	temp.m_x = m_x += coord.m_x;
	temp.m_y = m_y += coord.m_y;
	return temp;
}

RCoord RCoord::operator-(RCoord coord)
{
	RCoord temp;
	temp.m_x = m_x - coord.m_x;
	temp.m_y = m_y - coord.m_y;
	return temp;
}

RCoord RCoord::operator-=(RCoord coord)
{
	RCoord temp;
	temp.m_x = m_x -= coord.m_x;
	temp.m_y = m_y -= coord.m_y;
	return temp;
}

RCoord RCoord::operator-()
{
	RCoord temp;
	temp.m_x = -m_x;
	temp.m_y = -m_y;
	return temp;
}

RCoord RCoord::operator*(int n)
{
	RCoord temp;
	temp.m_x = m_x * n;
	temp.m_y = m_y * n;
	return temp;
}

RCoord RCoord::operator*=(int n)
{
	RCoord temp;
	temp.m_x = m_x *= n;
	temp.m_y = m_y *= n;
	return temp;
}

RCoord operator*(int n, RCoord coord)
{
	return coord * n;
}

RCoord RCoord::operator/(int n)
{
	RCoord temp;
	temp.m_x = m_x / n;
	temp.m_y = m_y / n;
	return temp;
}

RCoord RCoord::operator/=(int n)
{
	RCoord temp;
	temp.m_x = m_x /= n;
	temp.m_y = m_y /= n;
	return temp;
}

RCoord RCoord::operator++()
{
	RCoord temp;
	temp.m_x = ++m_x;
	temp.m_y = ++m_y;
	return temp;
}

RCoord RCoord::operator++(int dummy)
{
	RCoord temp;
	temp.m_x = m_x++;
	temp.m_y = m_y++;	
	return temp;
}

RCoord RCoord::operator--()
{
	RCoord temp;
	temp.m_x = --m_x;
	temp.m_y = --m_y;
	return temp;
}

RCoord RCoord::operator--(int dummy)
{
	RCoord temp;
	temp.m_x = m_x--;
	temp.m_y = m_y--;
	return temp;
}

RCoord RCoord::operator!()
{
	RCoord temp;
	temp.m_x = m_y;
	temp.m_y = m_x;
	return temp;
}

bool RCoord::operator==(RCoord coord)
{
	return m_x == coord.m_x && m_y == coord.m_y;
}

bool RCoord::operator!=(RCoord coord)
{
	return m_x != coord.m_x || m_y != coord.m_y;
}


bool RCoord::operator<(RCoord coord)
{
	return m_x + m_y < coord.m_x + coord.m_y;
}

bool RCoord::operator>(RCoord coord)
{
	return m_x + m_y > coord.m_x + coord.m_y;
}

std::ostream& operator<<(std::ostream& outstream, const RCoord coord)
{
	outstream << "(" << coord.m_x << ", " << coord.m_y << ")" << std::endl;
	return outstream;
}
