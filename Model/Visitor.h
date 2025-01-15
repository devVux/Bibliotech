#pragma once

#include "Book.h"
#include "Film.h"

class Visitor {

	public:

		~Visitor() = default;

		virtual void visit(Film& film) = 0;
		virtual void visit(Book& book) = 0;

};
