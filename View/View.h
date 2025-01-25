#pragma once

#include "Biblioteca.h"
#include "Observer.h"

#include <QtWidgets/QMainWindow>

class View;
using ViewPtr = std::shared_ptr<View>;
using ConstViewPtr = std::shared_ptr<const View>;

class View: public QMainWindow, public Observer {
	Q_OBJECT

	public:

        View(ModelPtr model): pModel(model), pContent(new QWidget(this)) { }

		void init();

		virtual void update(void* data) override;
		void display(const std::vector<MediaPtr>& medias);


	signals:

		void addBookButtonClicked();
		void addFilmButtonClicked();
		void addMusicAlbumButtonClicked();  //
		
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
