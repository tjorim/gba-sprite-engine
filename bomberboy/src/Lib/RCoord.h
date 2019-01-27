#ifndef RCOORD_H
#define RCOORD_H

#include <iostream>

class RCoord {

public:
	
    //at least 4 useful const (4/4) 24
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
	void SetX(int x) {m_x = x;}
	void SetY(int y) {m_y = y;}
	void printCoord();


    //operator overloading 19

    RCoord operator+(const RCoord coord2);
    RCoord operator+=(const RCoord coord2);
	RCoord operator-(RCoord coord2);
	RCoord operator-=(RCoord coord2);
	RCoord operator-();
	RCoord operator*(int n);
	RCoord operator*=(int n);
	RCoord operator/(int n);
	RCoord operator/=(int n);
	RCoord operator++();
	RCoord operator++(int dummy);
	RCoord operator--();
	RCoord operator--(int dummy);
	RCoord operator!();


    //at least 4 useful bool (6/4) 25
	bool operator==(RCoord coord);
	bool operator!=(RCoord coord);
	bool operator<(RCoord coord);
	bool operator>(RCoord coord);
	
	RCoord(int x, int y);
	RCoord();

private:
	int m_x;
	int m_y;

    //2 (modern) call-by-references 28 (27 niet)
    //friend function or class 34
friend std::ostream& operator<<(std::ostream& outstream, const RCoord coord);
friend RCoord operator*(int n, RCoord coord);
};

RCoord operator*(int n, RCoord coord);
std::ostream& operator<<(std::ostream& outstream, const RCoord coord);



#endif //RCOORD_H
