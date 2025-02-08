#pragma once

#include "Biblioteca.h"
#include "Observer.h"

#include <QtWidgets/QMainWindow>
#include <QtCore/QString>

class View;
using ViewPtr = std::shared_ptr<View>;

class View: public QMainWindow, public Observer<ModelData> {
	Q_OBJECT

	public:

        View(ModelPtr model);

		void init();

        virtual void update(const ModelData& data) override;


	signals:

		void addBookButtonClicked();
		void addFilmButtonClicked();
		void addMusicAlbumButtonClicked();
		
		void saveButtonClicked(const QString& path);
		void loadButtonClicked(const QString& path);

		void searchButtonClicked(const QString& query);
		void resetButtonClicked();

		void removeMedia(const MediaPtr& media);


	private:

		void clearLayout(class QLayout* layout);


	private:

		ModelPtr pModel;
		QWidget* pContent { nullptr };

};
