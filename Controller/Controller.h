#pragma once

#include "Observer.h"
#include "Biblioteca.h"
#include "View.h"

#include <QtCore/QObject>

class Controller: public QObject, public Observer, public Subject {
	Q_OBJECT

	public:

		Controller(ModelPtr model, ViewPtr view): pModel(model), pView(view) { }
		
		void init();

		void addMusicAlbum(); //agg
	
	protected:

		virtual void notifyAll() override {
			for (Observer* observer : mObservers)
				observer->update(&mQuery);
		}

        virtual void update(void*) override { notifyAll(); }


	private:
		
		ModelPtr pModel;
		ViewPtr pView;

		QString mQuery; // filtro per ricerche

};
