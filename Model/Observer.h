#pragma once

#include <memory>
#include <vector>
#include <algorithm>

class Observer {
	
	public:

		virtual ~Observer() = default;
		
		virtual void update(void* data) = 0;

};


class Subject {
	
	public:

		virtual ~Subject() = default;
	
		void registerObserver(Observer* observer) {
			mObservers.push_back(observer);
		}

		void removeObserver(Observer* observer) {
			mObservers.erase(
				std::remove(mObservers.begin(), mObservers.end(), observer),
				mObservers.end()
			);
		}


	protected:

		virtual void notifyAll() = 0;


	protected:
		
		std::vector<Observer*> mObservers;

};
