#pragma once

#include "Visitor.h"

#include <QtXml/QDomElement>

class XMLVisitor: public Visitor {

	public:

		void visit(Film& film) override;
		void visit(Book& book) override;
	    void visit(MusicAlbum& album) override; //
		
		QDomElement element() const { return mElement; }


	private:

		QDomDocument mDocument;
		QDomElement mElement;

};
