#pragma once

#include <QtWidgets/QWidget>
#include "Visitor.h"

class QDialog;

class FormVisitor: public Visitor {
	
	public:
		
		FormVisitor(QWidget* parent): pParent(parent), pDialog(nullptr) { }
		
		virtual void visit(Film& film) override;
		virtual void visit(Book& book) override;

		QDialog* dialog() const { return pDialog; }


	private:
		
		QWidget* pParent { nullptr };
		QDialog* pDialog { nullptr };

};