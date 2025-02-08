#pragma once

#include "Biblioteca.h"
#include "View.h"
#include "Observer.h"
#include <QtCore/QObject>

/// Assumiamo che il tipo del modello sia Biblioteca.
/// Il Controller eredita da Observer<Biblioteca> e Subject<Biblioteca>.
class Controller : public QObject, public Observer<Biblioteca>, public Subject<Biblioteca> {
    Q_OBJECT
public:
    Controller(ModelPtr model, ViewPtr view)
        : pModel(model), pView(view)
    { }

    void init();

protected:
    // Notifica tutti gli osservatori (eccetto se stesso), passando l'indirizzo di mQuery.
    virtual void notifyAll() override {
        for (Observer<Biblioteca>* observer : mObservers) {
            if (observer != this) {
                observer->update(&mQuery);
            }
        }
    }
    
    // Il metodo update non deve fare nulla qui per evitare loop
    virtual void update(void* data) override { (void)data; }

private:
    ModelPtr pModel;
    ViewPtr pView;
    QString mQuery;
};
