#pragma once

#include "Visitor.h"
#include "MediaWidget.h"

class QtVisitor: public Visitor {

	public:

		QtVisitor(QWidget* parent): pParent(parent) { }
		virtual ~QtVisitor() = default;

		virtual void visit(Film& film) override;
		virtual void visit(Book& book) override;

		MediaWidget* widget() const { return pWidget; }


	private: 

		MediaWidget* pWidget { nullptr };
		QWidget* pParent { nullptr };

};