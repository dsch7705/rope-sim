#include "Rope.h"


Rope::Rope(int size, double thickness)
{
	if (size == 0)
	{
		head = nullptr;
		return;
	}

	head = new Node();
	head->radius = thickness / 2.f;

	Node* current = head;
	for (int i = 1; i < size; i++)
	{
		current->next = new Node();
		current->next->radius = head->radius;
		current = current->next;
	}
}
void Rope::Update(float dT, const Vec2& follow)
{
	Node* current = head;
	while (current != nullptr)
	{
		// Lerp each node to its parent
		if (current == head)
		{
			current->pos = current->pos.lerp(follow, dT * 10.f);
		}
		if (current->next != nullptr)
			current->next->pos = current->next->pos.lerp(current->pos - (current->pos - current->next->pos).norm() * 2.f * current->radius, 1.f);
		// Resolve collision with pins
		for (const Pin* pin : pins)
		{
			if (Vec2::dist(current->pos, pin->pos) < current->radius + pin->radius)
			{
				current->pos = pin->pos + (current->pos - pin->pos).norm() * (current->radius + pin->radius);
			}
		}

		current = current->next;
	}
}
void Rope::extend(int n)
{
	Node* last = head;
	while (last->next != nullptr)
	{
		last = last->next;
	}

	for (int i = 0; i < n; i++)
	{
		last->next = new Node(last->pos, last->radius);
		last = last->next;
	}
}
void Rope::shrink(int n)
{
	int newLastIdx = count() - (n+1);
	if (newLastIdx < 0)
		throw std::invalid_argument("Cannot shrink linked list into negative length!");

	Node* newLast = head;
	int currentIdx = 0;
	// Iterate over rope to to-be last element
	while (currentIdx != newLastIdx)
	{
		++currentIdx;
		newLast = newLast->next;
	}
	// Free memory for shrunken nodes
	Node* current = newLast->next;
	while (current != nullptr)
	{
		Node* temp = current;
		current = current->next;
		delete(temp);
	}

	newLast->next = nullptr;
}
int Rope::count()
{
	if (head == nullptr)
		return 0;

	Node* current = head;
	int len = 1;
	while (current->next != nullptr)
	{
		current = current->next;
		++len;
	}

	return len;
}