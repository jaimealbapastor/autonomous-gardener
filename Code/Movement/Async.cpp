#include "Async.h"

Task::Task(unsigned int last_chrono)
{
	this->id = id;
	this->last_chrono = last_chrono;
	this->next = nullptr;
	this->can_be_destroyed = false;
}

Task::~Task()
{
}

Task *Async::first_task = nullptr;
uint8_t last_id = 0;

void Async::add()
{
	if (Async::first_task == nullptr)
	{
		// TODO change id generation method
		Async::first_task = new Task(++last_id, 0);
	}
}