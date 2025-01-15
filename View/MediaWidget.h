#pragma once

#include <QtWidgets/QWidget>

class MediaWidget: public QWidget {
	Q_OBJECT

	public:

		MediaWidget(QWidget* parent): QWidget(parent) { }


	signals:

		void deleteButtonClicked();
		void editButtonClicked();


};