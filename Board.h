#pragma once

#include "Matrix.h"
#include "Base_piece.h"
#include <vector>

const int chessboard_size_X = 8;
const int chessboard_size_Y = 8;

class Board:public Matrix<int>{
	public:
		Board() = delete;
		Board(int,int);
		~Board() override = default;
		Board(const Board&) = delete;
		Board& operator = (const Board&) = delete;
		Board(Board&&) = delete;
		Board& operator = (Board&&) = delete;
};

class ChessBoard:public Board{
	public:
		ChessBoard();
		~ChessBoard() override = default;
		ChessBoard(const ChessBoard&) = delete;
		ChessBoard& operator = (const ChessBoard&) = delete;
		ChessBoard(ChessBoard&&) = delete;
		ChessBoard& operator = (ChessBoard&&) = delete;
	public:
		std::vector<Base_piece*> m_pieces_on_board;
		void init(Base_piece*,int,int);
};