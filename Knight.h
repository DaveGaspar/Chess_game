#pragma once

#include "Base_piece.h"

class Knight:public Base_piece{
	public:
		Knight() = delete;
		Knight(Piece_Id);
		~Knight() override = default;
		Knight(const Knight&) = delete;
		Knight& operator =(const Knight&) = delete;
		Knight(Knight&&) = delete;
		Knight& operator =(Knight&&) = delete;
	public:
		void move(std::vector<Base_piece*>) override;
};