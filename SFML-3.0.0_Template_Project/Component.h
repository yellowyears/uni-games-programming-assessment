#include <iostream>

class Player; //forward declare Player class

class Component
{

protected:
    std::string name;
public:
	Player* parent = nullptr;
    Component(std::string name = "default") : name(name) {}

    void SetParent(Player* p)
    {
		parent = p;
    }

    // Called when the component is updated. Each component needs to implement this differently
    virtual void Update(float dt) {}
    
    // Called when the component is initialised
    virtual void Init() {}

    std::string getName() { return name; }
};