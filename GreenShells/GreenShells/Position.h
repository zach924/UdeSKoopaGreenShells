#pragma once
#include <string>

class Position
{
public:

    int Column;
    int Row;

    Position(int column = -1, int row = -1);
    ~Position();
    std::string ToString() const;

    friend bool operator==(const Position& obj1, const Position& obj2)
    {
        return obj1.Column == obj2.Column && obj1.Row == obj2.Row;
    }

    friend std::ostream& operator<<(std::ostream& os, const Position& obj)
    {
        os << obj.ToString();
        return os;
    }

	inline bool operator == (const Position& other) { return Row == other.Row && Column == other.Column; }
	inline bool operator!=( const Position& other) { return !(*this == other); }
};