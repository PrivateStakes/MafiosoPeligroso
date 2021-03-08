#include "Soldier.h"

class NPC : public Soldier
{

public:
	NPC(std::string name = "Joe", int health = 3, float speed = 5.0);
	~NPC();

	// Inherited via Soldier
	virtual void update(const float deltaTime) override;
	void move();
};