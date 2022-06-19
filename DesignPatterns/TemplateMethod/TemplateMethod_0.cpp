#include <iostream>
#include <string>

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

int main()
{
	SubtleMethod subtle_method;
	HitAndRunMethod hit_and_run_method;
	subtle_method.Steal();
	hit_and_run_method.Steal();

	return 0;
}
