#pragma once
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    // Metodo di aggiornamento: non riceve parametri
    virtual void update() = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    
    void registerObserver(Observer* observer) {
        mObservers.push_back(observer);
    }
    
    void removeObserver(Observer* observer) {
        mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
    }
    
protected:
    // Notifica tutti gli osservatori registrati
    void notifyAll() {
        for (Observer* observer : mObservers) {
            if (observer) {
                observer->update();
            }
        }
    }
    
    std::vector<Observer*> mObservers;
};
