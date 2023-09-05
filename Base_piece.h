#pragma once

#include "Square.h"
#include <iostream>
#include <vector>

struct Base_piece{
	enum Piece_Id{
		b_king = -1,
		no_piece = 0,
		w_king = 1,
		w_queen = 2,
		w_bishop = 3,
		w_knight = 4
	};
	Piece_Id m_id;
	Square m_position;
	std::vector<Square> m_sq_that_can_move;
	virtual void move(std::vector<Base_piece*>) = 0;
	virtual bool check_available_square(Square);
	virtual ~Base_piece() = default;
};