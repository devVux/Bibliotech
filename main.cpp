#include <QApplication>
#include <QGuiApplication>
#include <QFile>
#include <QDebug>
#include "Biblioteca.h"
#include "View.h"
#include "Controller.h"
#include <memory>

int main(int argc, char *argv[])
{

    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication app(argc, argv);

   
    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
    } 

    auto model = std::make_shared<Model>();
    auto view = std::make_shared<View>(model);
    auto controller = std::make_shared<Controller>(model, view);

    view->init();
    controller->init();

    model->registerObserver(controller.get());
    controller->registerObserver(view.get());

    view->show();
    return app.exec();
}
