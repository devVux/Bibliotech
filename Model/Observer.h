#pragma once
#include <memory>
#include <vector>
#include <algorithm>

template <class T>
class Observer {

	public:

		virtual ~Observer() = default;

		virtual void update(const T& data) = 0;

};

template <class T>
class Subject {

	public:
		
		virtual ~Subject() = default;

		void registerObserver(Observer<T>* observer) {
			if (observer == nullptr)
				return;

			mObservers.push_back(observer);
		}

		void removeObserver(Observer<T>* observer) {
			mObservers.erase(
				std::remove(mObservers.begin(), mObservers.end(), observer),
				mObservers.end()
			);
		}


	protected:

		virtual void notifyAll(const T& data) {
			for (const auto& observer : mObservers)
				observer->update(data);
		}

		
	protected:

		std::vector<Observer<T>*> mObservers;

};



template <>
class Observer<void> {
	public:

		virtual ~Observer() = default;

		virtual void update() = 0;
};

template <>
class Subject<void> {

	public:

		virtual ~Subject() = default;

		void registerObserver(Observer<void>* observer) {
			if (observer == nullptr)
				return;

			mObservers.push_back(observer);
		}

		void removeObserver(Observer<void>* observer) {
			mObservers.erase(
				std::remove(mObservers.begin(), mObservers.end(), observer),
				mObservers.end()
			);
		}

	protected:

		virtual void notifyAll() {
			for (auto observer : mObservers)
				observer->update();
		}

	protected:

		std::vector<Observer<void>*> mObservers;

};

using SubjectNoParameters = Subject<void>;
using ObserverNoParameters = Observer<void>;

