#pragma once

#include "Biblioteca.h"
#include "View.h"
#include "Observer.h"
#include <QtCore/QObject>


class Controller: public QObject, public Observer, public Subject {
    Q_OBJECT
public:
    Controller(ModelPtr model, ViewPtr view)
        : pModel(model), pView(view)
    { }

    void init();

protected:
    
    virtual void notifyAll() override {
        
        for (Observer* observer : mObservers) {
            if (observer != this) {
                observer->update(&mQuery);
            }
        }
    }

    
    virtual void update(void* data) override { (void)data; }

private:
    ModelPtr pModel;
    ViewPtr pView;
    QString mQuery;
};
