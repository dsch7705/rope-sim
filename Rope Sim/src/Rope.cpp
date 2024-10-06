#include "Rope.h"


Rope::Rope(int size, double thickness)
{
	if (size == 0)
	{
		head = nullptr;
		return;
	}
	
	head = (Node*)malloc(sizeof(Node) * size);
	if (head == nullptr)
		return;

	Node* current = head;
	for (int i = 0; i < size; i++)
	{
		new (current) Node(Vec2(0.f, 0.f), thickness / 2.f);
		if (i + 1 < size)
		{
			current->next = current + 1;
			current = current->next;
		}
		else
		{
			current->next = nullptr;
		}
	}
	current = nullptr;
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
		Collisions();

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
		len++;
	}

	return len;
}

void Rope::Collisions()
{
	// Shapes
	Vec2 edge;
	for (const Shape* shape : shapes)
	{
		// Test each edge
		for (int i = 0; i < 1;i++)//shape->sides; i++)
		{
			int nextI = (i + 1) % shape->sides;
			Vec2 currentV = shape->vertices[i];
			Vec2 nextV = shape->vertices[nextI];
			edge = nextV - currentV;	// points from first point to second, etc.
			DrawLine(0, 0, edge.x, edge.y, SKYBLUE);
			
			// Test against each node
			Node* current = head;
			while (current != nullptr)
			{
				Vec2 nodeRel = current->pos - (shape->center + currentV);
				double dp = (nodeRel.norm().dot(edge.norm()) + 1) / 2;
				//std::cout << dp << '\n';
				Vec2 closestP = (shape->center + currentV) + (edge * dp);
				if (current == head)
					DrawCircle(closestP.x, closestP.y, 10, RED);

				// Collision?
				if (Vec2::dist(current->pos, closestP) < current->radius)
				{
					// Resolve
					current->pos = closestP + (current->pos - closestP).norm() * current->radius;
				}

				current = current->next;
			}
		}
	}
}