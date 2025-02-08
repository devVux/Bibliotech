#pragma once
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
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
    std::vector<Observer*> mObservers;
};
