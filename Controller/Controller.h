#pragma once

#include "Biblioteca.h"
#include "View.h"
#include "Observer.h"
#include <QtCore/QObject>

class Controller : public QObject, public Observer, public Subject {
    Q_OBJECT
public:
    Controller(ModelPtr model, ViewPtr view)
        : pModel(model), pView(view)
    { }

    void init();

    // Observer override (qui non serve fare nulla)
    virtual void update() override { /* Nessuna azione specifica per il Controller */ }

    // Metodo per notificare gli osservatori
    void notifyAllObservers() {
        for (Observer* observer : mObservers) {
            if (observer != this)
                observer->update();
        }
    }

private:
    ModelPtr pModel;
    ViewPtr pView;
    QString mQuery;  // Il filtro corrente (gestito dal Controller)
};
