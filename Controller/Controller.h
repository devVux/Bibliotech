#pragma once

#include "Biblioteca.h"
#include "View.h"
#include "Observer.h"
#include <QtCore/QObject>

/// Il Controller eredita da Observer e Subject (oltre a QObject)
class Controller: public QObject, public Observer, public Subject {
    Q_OBJECT
public:
    Controller(ModelPtr model, ViewPtr view)
        : pModel(model), pView(view)
    { }

    void init();

protected:
    // Override di notifyAll() per trasmettere il filtro di ricerca
    virtual void notifyAll() override {
        // Notifica tutti gli osservatori (es. la View), passando l'indirizzo di mQuery
        for (Observer* observer : mObservers) {
            if (observer != this) {
                observer->update(&mQuery);
            }
        }
    }

    // Il metodo update del Controller non deve eseguire alcuna azione per evitare loop
    virtual void update(void* data) override { (void)data; }

private:
    ModelPtr pModel;
    ViewPtr pView;
    QString mQuery;
};
