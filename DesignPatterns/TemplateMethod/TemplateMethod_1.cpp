#include <iostream>
#include <string>
#include <memory>

class StealingMethod
{
public:
	virtual ~StealingMethod() = default;

	void Steal()
	{
		auto target = PickTarget();
		std::cout << "The target has been chosen as the " << target << "." << std::endl;
		ConfuseTarget(target);
		StealTheItem(target);
	}

protected:
	StealingMethod() = default;
	StealingMethod(const StealingMethod&) = default;
	StealingMethod(StealingMethod&&) = default;
	StealingMethod& operator=(const StealingMethod&) = default;
	StealingMethod& operator=(StealingMethod&&) = default;

private:
	virtual std::string PickTarget() = 0;
	virtual void ConfuseTarget(const std::string&) = 0;
	virtual void StealTheItem(const std::string&) = 0;
};

class SubtleMethod : public StealingMethod
{
private:
	std::string PickTarget() override
	{
		return "shopkeeper";
	}

	void ConfuseTarget(const std::string& target) override
	{
		std::cout << "Approach the " << target << " with running tears and hug him!" << std::endl;
	}

	void StealTheItem(const std::string& target) override
	{
		std::cout << "While in close contact, grab the " << target << "'s wallet." << std::endl;
	}
};

class HitAndRunMethod : public StealingMethod
{
private:
	std::string PickTarget() override
	{
		return "old goblin woman";
	}

	void ConfuseTarget(const std::string& target) override
	{
		std::cout << "Approach the " << target << " from behind." << std::endl;
	}

	void StealTheItem(const std::string& target) override
	{
		std::cout << "Grab the handbag and run away fast!" << std::endl;
	}
};

class HalflingThief
{
public:
	explicit HalflingThief(std::unique_ptr<StealingMethod> method) : method_{ std::move(method) } {  }

	void Steal()
	{
		method_->Steal();
	}

	void ChangeMethod(std::unique_ptr<StealingMethod> method)
	{
		method_ = std::move(method);
	}

private:
	std::unique_ptr<StealingMethod> method_;
};

int main()
{
	HalflingThief thief{ std::make_unique<SubtleMethod>() };
	thief.Steal();
	thief.ChangeMethod(std::make_unique<HitAndRunMethod>());
	thief.Steal();

	return 0;
}
