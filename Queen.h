#pragma once

#include "Base_piece.h"

class Queen:public Base_piece{
	public:
		Queen() = delete;
		Queen(Piece_Id);
		~Queen() override = default;
		Queen(const Queen&) = delete;
		Queen& operator =(const Queen&) = delete;
		Queen(Queen&&) = delete;
		Queen& operator =(Queen&&) = delete;
	public:
		void move(std::vector<Base_piece*>) override;
};