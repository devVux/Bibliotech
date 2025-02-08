#include <QApplication>
#include <QGuiApplication>
#include <QFile>
#include <QDebug>
#include "Biblioteca.h"  // Include il modello (in questo esempio, Biblioteca)
#include "View.h"
#include "Controller.h"
#include <memory>

int main(int argc, char *argv[])
{
    // In Qt6 l'alta densità è abilitata di default, ma possiamo impostare la politica di arrotondamento se necessario:
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication app(argc, argv);

    // Carica lo stylesheet dalle risorse (assicurati che style.qss sia correttamente referenziato nel file resources.qrc)
    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
    } else {
        qDebug() << "Impossibile aprire il file style.qss";
    }

    // Crea il modello, la view e il controller utilizzando smart pointer.
    // Assumiamo che il modello sia di tipo Biblioteca.
    auto model = std::make_shared<Biblioteca>();
    auto view = std::make_shared<View>(model);
    auto controller = std::make_shared<Controller>(model, view);

    // Inizializza View e Controller
    view->init();
    controller->init();

    // Registra gli observer: il modello notifica il Controller, che notifica la View.
    model->registerObserver(controller.get());
    controller->registerObserver(view.get());

    view->show();

    return app.exec();
}
