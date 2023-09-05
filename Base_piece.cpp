#include "Base_piece.h"

bool Base_piece::check_available_square(Square sq){
	if (sq.m_letter < 0 || sq.m_letter > 7 || sq.m_number < 0 || sq.m_number > 7){
		return false;
	}
	return true;
}