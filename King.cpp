#include "King.h"

King::King(Piece_Id id){
	m_id = id;
}

void King::move(std::vector<Base_piece*> vec){
	if (!m_sq_that_can_move.empty()){
		m_sq_that_can_move.clear();
	}
	
	Square temp;
	temp.m_letter = m_position.m_letter - 1;
	temp.m_number = m_position.m_number + 1;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
	temp.m_letter = m_position.m_letter - 1;
	temp.m_number = m_position.m_number;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
	temp.m_letter = m_position.m_letter - 1;
	temp.m_number = m_position.m_number - 1;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
	temp.m_letter = m_position.m_letter;
	temp.m_number = m_position.m_number - 1;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
	temp.m_letter = m_position.m_letter + 1;
	temp.m_number = m_position.m_number - 1;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
	temp.m_letter = m_position.m_letter + 1;
	temp.m_number = m_position.m_number;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
	temp.m_letter = m_position.m_letter + 1;
	temp.m_number = m_position.m_number + 1;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
	temp.m_letter = m_position.m_letter;
	temp.m_number = m_position.m_number + 1;
	if (check_available_square(temp)){
		m_sq_that_can_move.push_back(temp);
	}
}