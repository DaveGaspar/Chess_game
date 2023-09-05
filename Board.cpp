#include "Board.h"

Board::Board(int x, int y):Matrix(x,y){

}

ChessBoard::ChessBoard():Board(chessboard_size_X, chessboard_size_Y){
	m_pieces_on_board.push_back(nullptr);
	for (int i = 0; i < chessboard_size_Y; i++){
		for (int j = 0; j < chessboard_size_X; j++){
			m_arr_2d[i][j] = 0;
		}
	}
}

void ChessBoard::init(Base_piece* piece, int letter, int number){
	m_pieces_on_board.push_back(piece);
	letter -= 1;
	number = 8 - number;
	m_arr_2d[number][letter] = m_pieces_on_board.size()-1;
	piece->m_position.m_letter = letter;
	piece->m_position.m_number = number;
}