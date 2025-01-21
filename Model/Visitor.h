#pragma once

#include "Book.h"
#include "Film.h"
#include "MusicAlbum.h"

class Visitor {

	public:

		~Visitor() = default;

		virtual void visit(Film& film) = 0;
		virtual void visit(Book& book) = 0;
		virtual void visit(MusicAlbum& album) = 0;


};
