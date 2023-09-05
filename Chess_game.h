#pragma once

#include <string>
#include "Game.h"
#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"

#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <iostream>

enum class Board_status{
	Nothing,
	Check,
	Checkmate,
	Stalemate
};

class Chess_game:public Game, public ChessBoard{
	public:
		Chess_game() = default;
		~Chess_game() override = default;
		Chess_game(const Chess_game&) = delete;
		Chess_game& operator = (const Chess_game&) = delete;
		Chess_game(Chess_game&&) = delete;
		Chess_game& operator = (Chess_game&&) = delete;
	public:
		void start() override;
		void finish() override;
};

class Chess_minigame:public Chess_game{
	public:
		Chess_minigame();
		~Chess_minigame() override;
		Chess_minigame(const Chess_minigame&) = delete;
		Chess_minigame& operator = (const Chess_minigame&) = delete;
		Chess_minigame(Chess_minigame&&) = delete;
		Chess_minigame& operator = (Chess_minigame&&) = delete;
	public:
		void start() override;
		void finish() override;
		Board_status check();
		void input();
		std::pair<Base_piece::Piece_Id, Square> look_for_mate_in_1();
	public:
		Board_status board_status = Board_status::Nothing;
		std::string b_k_position;
		std::string w_k_position;
		std::string w_q_position;
		std::string w_b_position;
		std::string w_n_position;
};