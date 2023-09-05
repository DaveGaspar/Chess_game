#pragma once

#include <iostream>

class Game{
	public:
		virtual ~Game() = default;
		virtual void start() = 0;
		virtual void finish() = 0;
};