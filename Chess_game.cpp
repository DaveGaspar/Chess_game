#include "Chess_game.h"

//Chess Game

void Chess_game::start(){

}

void Chess_game::finish(){
	
}

//Chess Minigame

Chess_minigame::Chess_minigame(){
	try{
		b_k_position = "0";
		w_k_position = "0";
		w_q_position = "0";
		w_b_position = "0";
		w_n_position = "0";
		input();
	}
	catch(const std::exception & ex){
		std::cerr << "Error: " << ex.what() << std::endl;
		exit(1);
	}
}

Chess_minigame::~Chess_minigame(){
	for (auto in = ++m_pieces_on_board.begin(); in != m_pieces_on_board.end(); ++in){
		delete (*in);
	}
}

void Chess_minigame::input(){
	std::ifstream txt;
	txt.open("Positions.txt");
	if (!txt.is_open()){
		throw std::runtime_error("Error, file did not open!");
	}
	while (txt.good()){
		std::string temp;
		std::getline(txt,temp);
		if (temp.at(0) == 'B'){
			if (temp.at(1) == 'K'){
				if (temp.at(2) >= 97 && temp.at(2) <= 104){
					if (temp.at(3) - '0' <= 0 || temp.at(3) - '0' >= 9){
						throw std::logic_error("Invalid piece position!");
					}
					else{
						b_k_position = temp;
					}
				}
				else{
					throw std::logic_error("Invalid piece position!");
				}				
			}
			else{
				throw std::logic_error("Invalid piece position!");
			}
		}
		else if (temp.at(0) == 'W'){
			if (temp.at(2) >= 97 && temp.at(2) <= 104){
				if (temp.at(3) - '0' > 0 && temp.at(3) - '0' < 9){
					if (temp.at(1) == 'K'){
						w_k_position = temp;
					}
					else if (temp.at(1) == 'Q'){
						w_q_position = temp;
					}
					else if (temp.at(1) == 'B'){
						w_b_position = temp;
					}
					else if (temp.at(1) == 'N'){
						w_n_position = temp;
					}
					else{
						throw std::logic_error("Invalid piece position!");
					}
				}
				else{
					throw std::logic_error("Invalid piece position!");
				}
			}
			else{
				throw std::logic_error("Invalid piece position!");
			}
		}
		else{
			throw std::logic_error("Invalid piece position!");
		}
	}
	

	std::vector<std::string> vec = {b_k_position, w_k_position, w_q_position, w_b_position, w_n_position};
	
	for (auto in : vec){
		if (in == "0"){
			throw std::logic_error("Invalid input, missing a piece postion!");
		}
	}

	for (auto in_1 : vec){
		for (auto in_2 : vec){
			if (in_1 != in_2){
				if (in_1.at(2) == in_2.at(2) && in_1.at(3) == in_2.at(3)){
					throw std::logic_error("Invalid piece position, there can only be one piece on one square!");
				}
			}
		}
	}

	Base_piece* black_king = new King(Base_piece::Piece_Id::b_king);
	Base_piece* white_king = new King(Base_piece::Piece_Id::w_king);
	Base_piece* white_queen = new Queen(Base_piece::Piece_Id::w_queen);
	Base_piece* white_bishop = new Bishop(Base_piece::Piece_Id::w_bishop);
	Base_piece* white_knight = new Knight(Base_piece::Piece_Id::w_knight);


	init(black_king,b_k_position.at(2) - 96,b_k_position.at(3) - '0');
	init(white_king,w_k_position.at(2) - 96,w_k_position.at(3) - '0');
	init(white_queen,w_q_position.at(2) - 96,w_q_position.at(3) - '0');
	init(white_bishop,w_b_position.at(2) - 96,w_b_position.at(3) - '0');
	init(white_knight,w_n_position.at(2) - 96,w_n_position.at(3) - '0');

	black_king->move(this->m_pieces_on_board);
	white_king->move(this->m_pieces_on_board);
	
	for (auto b_in : black_king->m_sq_that_can_move){
		if (white_king->m_position == b_in){
			throw std::logic_error("Invalid piece position, Kings can't be close to each other!");
		}
	}
	for (auto w_in : white_king->m_sq_that_can_move){
		if (black_king->m_position == w_in){
			throw std::logic_error("Invalid piece position, Kings can't be close to each other!");
		}
	}

	txt.close();
}

Board_status Chess_minigame::check(){
	Base_piece* black_king;
	std::vector<Base_piece *>::iterator iterator;
	for (auto it = ++m_pieces_on_board.begin(); it != m_pieces_on_board.end(); ++it){
		if ((*it)->m_id == Base_piece::Piece_Id::b_king){
			black_king = (*it);
			iterator = it;
			break;
		}
	}
	bool is_under_check = false;
	bool has_escape_square = true;

	std::vector<Square> vec;

	for (auto b = black_king->m_sq_that_can_move.begin(); b != black_king->m_sq_that_can_move.end(); ++b){
		vec.push_back((*b));
	}

	//Checking if black king has escape squares or not
	for (auto it = ++m_pieces_on_board.begin(); it != m_pieces_on_board.end(); ++it){
		if (it != iterator){
			for (auto in :(*it)->m_sq_that_can_move){
				for (auto v_in : vec){
					if (v_in.m_letter == in.m_letter && v_in.m_number == in.m_number){
						auto i = std::remove(vec.begin(), vec.end(), v_in);
						vec.erase(i,vec.end());
					}
				}
			}
		}
		if (vec.empty()){
			has_escape_square = false;
			break;
		}
	}

	//Checking if black king is under check or not
	for (auto it = ++m_pieces_on_board.begin(); it != m_pieces_on_board.end(); ++it){
		if (it != iterator){
			if (is_under_check == false){
				for (auto in : (*it)->m_sq_that_can_move){
					if (black_king->m_position.m_letter == in.m_letter && black_king->m_position.m_number == in.m_number){
						is_under_check = true;
						break;
					}
				}
			}
		}
	}

	if (is_under_check == false && has_escape_square == false){
		return Board_status::Stalemate;
	}
	else if (is_under_check == true && has_escape_square == true){
		return Board_status::Check;
	}
	else if (is_under_check == true && has_escape_square == false){
		return Board_status::Checkmate;
	}
	//if (is_under_check == false && has_escape_square == true){
	else{
		return Board_status::Nothing;
	}

}

std::pair<Base_piece::Piece_Id, Square> Chess_minigame::look_for_mate_in_1(){
	if (board_status == Board_status::Stalemate || board_status == Board_status::Nothing){
		// int i = 0;
		Board_status temp_board_status = Board_status::Nothing;

		Base_piece* bk;

		for (auto it = ++m_pieces_on_board.begin(); it != m_pieces_on_board.end(); ++it){
			if ((*it)->m_id == Base_piece::Piece_Id::b_king){
				bk = (*it);
			}
		}

		for (auto it = ++m_pieces_on_board.begin(); it != m_pieces_on_board.end(); ++it){

			if ((*it)->m_id == Base_piece::Piece_Id::b_king) {
				continue;
			}

			for (auto in : (*it)->m_sq_that_can_move){
				// i++;	
				bool temp = false;
				if ((*it)->m_id == Base_piece::Piece_Id::w_king) {
					for (auto b_sq : bk->m_sq_that_can_move){
						if (in == b_sq){
							temp = true;
							break;
						}
					}
				}
				
				for (auto it_2 = ++m_pieces_on_board.begin(); it_2 != m_pieces_on_board.end(); ++it_2){
					if (it == it_2){
						continue;
					}
					else{
						if (in == (*it_2)->m_position){
							temp = true;
							break;
						}
					}
				}
				
				if (temp){
					continue;
				}

				

				auto* temp_board = new Chess_minigame;

				temp_board->b_k_position = this->b_k_position;
				temp_board->w_k_position = this->w_k_position;
				temp_board->w_q_position = this->w_q_position;
				temp_board->w_b_position = this->w_b_position;
				temp_board->w_n_position = this->w_n_position;

				std::string str = std::to_string(8 - in.m_number);
				str = (char)(97+in.m_letter) + str;

				switch ((*it)->m_id)
				{
				case Base_piece::Piece_Id::w_king:
					temp_board->w_k_position = "WK" + str;
					break;
				case Base_piece::Piece_Id::w_queen:
					temp_board->w_q_position = "WQ" + str;
					break;
				case Base_piece::Piece_Id::w_bishop:
					temp_board->w_b_position = "WB" + str;
					break;
				case Base_piece::Piece_Id::w_knight:
					temp_board->w_n_position = "WN" + str;
					break;
				default:
					break;
				}

				Base_piece* black_king = new King(Base_piece::Piece_Id::b_king);
				Base_piece* white_king = new King(Base_piece::Piece_Id::w_king);
				Base_piece* white_queen = new Queen(Base_piece::Piece_Id::w_queen);
				Base_piece* white_bishop = new Bishop(Base_piece::Piece_Id::w_bishop);
				Base_piece* white_knight = new Knight(Base_piece::Piece_Id::w_knight);

				temp_board->m_pieces_on_board.erase(++temp_board->m_pieces_on_board.begin(), temp_board->m_pieces_on_board.end());

				temp_board->init(black_king,temp_board->b_k_position.at(2) - 96,temp_board->b_k_position.at(3) - '0');
				temp_board->init(white_king,temp_board->w_k_position.at(2) - 96,temp_board->w_k_position.at(3) - '0');
				temp_board->init(white_queen,temp_board->w_q_position.at(2) - 96,temp_board->w_q_position.at(3) - '0');
				temp_board->init(white_bishop,temp_board->w_b_position.at(2) - 96,temp_board->w_b_position.at(3) - '0');
				temp_board->init(white_knight,temp_board->w_n_position.at(2) - 96,temp_board->w_n_position.at(3) - '0');

				for (auto piece = ++temp_board->m_pieces_on_board.begin(); piece != temp_board->m_pieces_on_board.end(); ++piece){
					(*piece)->move(temp_board->m_pieces_on_board);
					// for (auto p : (*piece)->m_sq_that_can_move){
					// 	std::cout << (char)(97+p.m_letter) << 8 - p.m_number << std::endl;
					// }
				}
				
				temp_board_status = temp_board->check();

				// std::cout << temp_board->b_k_position << std::endl;
				// std::cout << temp_board->w_k_position << std::endl;
				// std::cout << temp_board->w_q_position << std::endl;
				// std::cout << temp_board->w_b_position << std::endl;
				// std::cout << temp_board->w_n_position << std::endl;

				switch (temp_board_status)
				{
				case Board_status::Checkmate:
					// std::cout << "\n\n\n" << i << "\n\n\n";
					
					// for (auto popo = ++temp_board->m_pieces_on_board.begin(); popo != temp_board->m_pieces_on_board.end(); ++popo){
					// 	std::cout << (*popo)->m_id << " " << (char)(97+(*popo)->m_position.m_letter) << 8 - (*popo)->m_position.m_number << std::endl;
					// 	for (auto p : (*popo)->m_sq_that_can_move){
					// 		std::cout << (char)(97+p.m_letter) << 8 - p.m_number << std::endl;
					// 	}
					// }

					delete temp_board;
					return std::make_pair((*it)->m_id,in);
				case Board_status::Check:
					delete temp_board;
					break;
				case Board_status::Stalemate:
					delete temp_board;
					break;
				case Board_status::Nothing:
					delete temp_board;
					break;
				default:
					delete temp_board;
					break;
				}

			}


		}
		for (auto it = ++m_pieces_on_board.begin(); it != m_pieces_on_board.end(); ++it){
			(*it)->move(m_pieces_on_board);
		}

	}
	return std::make_pair(Base_piece::Piece_Id::no_piece, Square());
}

void Chess_minigame::start(){
	std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "------------Welcome to is the position checkmate or not------------" << std::endl;
    std::cout << "-----------------------------Have fun!-----------------------------" << std::endl;    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


	
	std::cout << "Black King: " << b_k_position.at(2) << b_k_position.at(3) << std::endl;
	std::cout << "White King: " << w_k_position.at(2) << w_k_position.at(3) << std::endl;
	std::cout << "White Queen: " << w_q_position.at(2) << w_q_position.at(3) << std::endl;
	std::cout << "White Bishop: " << w_b_position.at(2) << w_b_position.at(3) << std::endl;
	std::cout << "White Knight: " << w_n_position.at(2) << w_n_position.at(3) << std::endl;

	std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

	std::cout << "\t";
	for (int i = 0; i < 8; i++){
		printf("\e[1;34m%c\t\e[0m",(char)(97+i));
		// std::cout << (char)(97+i) << "\t";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (j == 0){
				printf("\e[1;34m%d\t\e[0m",8-i);
				// std::cout << 8 - i << "\t";
			}
			if (m_arr_2d[i][j] > 0){
				switch (m_pieces_on_board[m_arr_2d[i][j]]->m_id)
				{
				case -1:
					// printf("\033[30;48;5;15mK\033[0m\t");
					std::cout << "K" << "\t";
					break;
				case 1:
					printf("\033[30;48;5;15mK\033[0m\t");
					// std::cout << "K" << "\t";
					break;
				case 2:
					printf("\033[30;48;5;15mQ\033[0m\t");
					// std::cout << "Q" << "\t";
					break;
				case 3:
					printf("\033[30;48;5;15mB\033[0m\t");
					// std::cout << "B" << "\t";
					break;
				case 4:
					printf("\033[30;48;5;15mN\033[0m\t");
					// std::cout << "N" << "\t";
					break;
				default:
					break;
				}
			}
			else{
				printf("\033[32;1m#\033[0m\t");
				// std::cout << "#" << "\t";
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}


	std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


	for (auto it = ++m_pieces_on_board.begin(); it != m_pieces_on_board.end(); ++it){
		(*it)->move(m_pieces_on_board);
	}

	board_status = check();

	switch (board_status){
		case Board_status::Nothing:
			std::cout << "The position you entered is not check, checkmate or stalemate" << std::endl;
			break;
		case Board_status::Check:
			std::cout << "The position you entered is check, the black king is under check, but he can escape" << std::endl;
			break;
		case Board_status::Stalemate:
			std::cout << "The position you entered is stalemate, the black king has no legal moves" << std::endl;
			break;
		case Board_status::Checkmate:
			std::cout << "The position you entered is checkmate, the black king is under check and has no legal moves" << std::endl;
			break;
		default:
			break;
	}

	std::pair<Base_piece::Piece_Id, Square> mate_in_1 = look_for_mate_in_1();

	switch (mate_in_1.first)
	{
	case Base_piece::Piece_Id::no_piece:
		
		switch (board_status)
		{
		case Board_status::Check:
		case Board_status::Checkmate:
			break;
		default:
			std::cout << "There is no mate in one!" << std::endl;
			break;
		}
		break;
	case Base_piece::Piece_Id::w_king:
		std::cout << "Mate in one: White King " <<  (char)(97+mate_in_1.second.m_letter) << 8 - mate_in_1.second.m_number << std::endl;
		break;
	case Base_piece::Piece_Id::w_queen:
		std::cout << "Mate in one: White Queen " <<  (char)(97+mate_in_1.second.m_letter) << 8 - mate_in_1.second.m_number << std::endl;
		break;
	case Base_piece::Piece_Id::w_bishop:
		std::cout << "Mate in one: White Bishop " <<  (char)(97+mate_in_1.second.m_letter) << 8 - mate_in_1.second.m_number << std::endl;
		break;
	case Base_piece::Piece_Id::w_knight:
		std::cout << "Mate in one: White Knight " <<  (char)(97+mate_in_1.second.m_letter) << 8 - mate_in_1.second.m_number << std::endl;
		break;
	default:
		// std::cout << "default" << std::endl;
		break;
	}

}

void Chess_minigame::finish(){
	for (auto in = ++m_pieces_on_board.begin(); in != m_pieces_on_board.end(); ++in){
		delete (*in);
	}
	std::cout << std::endl << "Thanks for playing!!!" << std::endl;
}