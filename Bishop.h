#pragma once

#include "Base_piece.h"

class Bishop:public Base_piece{
	public:
		Bishop() = delete;
		Bishop(Piece_Id);
		~Bishop() override = default;
		Bishop(const Bishop&) = delete;
		Bishop& operator =(const Bishop&) = delete;
		Bishop(Bishop&&) = delete;
		Bishop& operator =(Bishop&&) = delete;
	public:
		void move(std::vector<Base_piece*>) override;
};