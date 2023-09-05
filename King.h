#pragma once

#include "Base_piece.h"

class King:public Base_piece{
	public:
		King() = delete;
		King(Piece_Id);
		~King() override = default;
		King(const King&) = delete;
		King& operator =(const King&) = delete;
		King(King&&) = delete;
		King& operator =(King&&) = delete;
	public:
		void move(std::vector<Base_piece*>) override;
};