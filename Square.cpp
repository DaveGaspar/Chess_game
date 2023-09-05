#include "Square.h"

bool Square::operator==(const Square& obj){
	return (this->m_letter == obj.m_letter && this->m_number == obj.m_number);
}