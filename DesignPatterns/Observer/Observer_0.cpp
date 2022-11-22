#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <utility>

class Subject;

class Observer
{
public:
	virtual ~Observer() = default;

	virtual void Update(Subject&) = 0;
};

class Subject
{
public:
	void Attach(std::weak_ptr<Observer> observer)
	{
		auto sp = observer.lock();
		// Ensure that the same observer is not added repeatedly.
		if (std::find_if(observers_.begin(), observers_.end(), [&](const std::weak_ptr<Observer>& wp) { return sp == wp.lock(); })
			== observers_.end())
		{
			observers_.push_back(observer);
		}
	}

	void Detach(std::weak_ptr<Observer> observer)
	{
		auto sp = observer.lock();
		std::erase_if(observers_, [&](const std::weak_ptr<Observer>& wp) { return sp == wp.lock(); });
	}

	void Notify()
	{
		for (auto it = observers_.begin(); it != observers_.end();)
		{
			if (auto sp = it->lock())
			{
				sp->Update(*this);
				++it;
			}
			else
			{
				// Erase the expired weak_ptr.
				it = observers_.erase(it);
			}
		}
	}

	void ChangeWeather(std::string weather)
	{
		weather_ = std::move(weather);
		Notify();
	}

	std::string GetWeather()
	{
		return weather_;
	}

private:
	std::vector<std::weak_ptr<Observer>> observers_;
	std::string weather_;
};

class HumanObserver : public Observer
{
public:
	void Update(Subject& subject) override
	{
		std::cout << "The human are facing " << subject.GetWeather() << " weather now." << std::endl;
	}
};

class OrcsObserver : public Observer
{
public:
	void Update(Subject& subject) override
	{
		std::cout << "The orcs are facing " << subject.GetWeather() << " weather now." << std::endl;
	}
};

class HobbitsObserver : public Observer
{
public:
	void Update(Subject& subject) override
	{
		std::cout << "The hobbits are facing " << subject.GetWeather() << " weather now." << std::endl;
	}
};

int main()
{
	Subject subject;

	auto human_observer = std::make_shared<HumanObserver>();
	subject.Attach(human_observer);
	subject.ChangeWeather("windy");

	{
		auto orcs_observer = std::make_shared<OrcsObserver>();
		subject.Attach(orcs_observer);
		subject.ChangeWeather("rainy");
	}

	auto hobbits_observer = std::make_shared<HobbitsObserver>();
	subject.Attach(hobbits_observer);
	subject.Attach(hobbits_observer);
	subject.ChangeWeather("storm");

	subject.Detach(human_observer);
	subject.ChangeWeather("sunny");

	return 0;
}
