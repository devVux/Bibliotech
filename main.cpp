#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <memory>

#include "Biblioteca.h"
#include "View.h"
#include "Controller.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	
	auto model = std::make_shared<Model>();
	auto view = std::make_shared<View>(model);
	auto controller = std::make_shared<Controller>(model);

	view->init();
	controller->init();
	
	view->show();
	return app.exec();
}
