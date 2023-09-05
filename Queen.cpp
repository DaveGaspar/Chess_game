#include "Queen.h"

Queen::Queen(Piece_Id id){
	m_id = id;
}

void Queen::move(std::vector<Base_piece*> vec){
	if (!m_sq_that_can_move.empty()){
		m_sq_that_can_move.clear();
	}
	
	// diagonal moves
	
	Square temp;
	bool flag;

	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter - i;
		temp.m_number = m_position.m_number + i;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}
	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter - i;
		temp.m_number = m_position.m_number - i;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}
	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter + i;
		temp.m_number = m_position.m_number - i;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}
	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter + i;
		temp.m_number = m_position.m_number + i;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}
	
	//horizontal and vertical moves

	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter;
		temp.m_number = m_position.m_number + i;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}
	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter + i;
		temp.m_number = m_position.m_number;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}
	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter;
		temp.m_number = m_position.m_number - i;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}
	for (int i = 1; i < 8; i++){
		flag = false;
		temp.m_letter = m_position.m_letter - i;
		temp.m_number = m_position.m_number;
		if (check_available_square(temp)){
			for (std::vector<Base_piece*>::iterator it = ++vec.begin(); it != vec.end(); ++it){
				if ((*it)->m_id != Base_piece::Piece_Id::b_king){
					if((*it)->m_position == temp){	
						flag = true;
						m_sq_that_can_move.push_back(temp);
						break;
					}
				}
			}
			if (!flag){
				m_sq_that_can_move.push_back(temp);
			}
		}
		if (flag){
			break;
		}
	}

}