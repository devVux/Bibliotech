#pragma once

#include "Biblioteca.h"
#include "View.h"
#include "Observer.h"
#include <QtCore/QObject>


class Controller: public QObject {
    Q_OBJECT
public:
    Controller(ModelPtr model, ViewPtr view)
        : pModel(model), pView(view)
    { }

    void init();

private:
    ModelPtr pModel;
    ViewPtr pView;
};
