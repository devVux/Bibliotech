#pragma once

#include "Observer.h"
#include "Biblioteca.h"

#include <QtCore/QObject>

class Controller: public QObject {
	Q_OBJECT

	public:

		Controller(ModelPtr model): pModel(model) { }
		
		void init();
	

	private:
		
		ModelPtr pModel;

};
