#include "Rope.h"
#define SIMULATION_STEPS 3


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
	Vec2 nextPos = current->pos.lerp(follow, dT * 10.f);
	while (current != nullptr)
	{
		Vec2 deltaP = (nextPos - current->pos) / SIMULATION_STEPS;
		for (int i = 0; i < SIMULATION_STEPS; i++)
		{
			current->pos += deltaP;
			Collisions(current);

			// Resolve collision with pins
			for (const Pin* pin : pins)
			{
				if (Vec2::dist(current->pos, pin->pos) < current->radius + pin->radius)
				{
					current->pos = pin->pos + (current->pos - pin->pos).norm() * (current->radius + pin->radius);
				}
			}
		}

		if (current->next != nullptr)
			nextPos = current->next->pos.lerp(current->pos - (current->pos - current->next->pos).norm() * 2.f * current->radius, 1.f);
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

void Rope::Collisions(Node* node)
{
	// Shapes
	Vec2 edge;
	for (const Shape* shape : shapes)
	{
		// Test each edge
		for (int i = 0; i < shape->sides; i++)
		{
			int nextI = (i + 1) % shape->sides;
			Vec2 currentV = shape->center + shape->vertices[i];						// Absolute
			Vec2 nextV = shape->center + shape->vertices[nextI];					// Absolute
			edge = nextV - currentV;	// points from first point to second, etc.
			
			// Test against each node
			Vec2 nodeRel = node->pos - currentV;								// Relative to currentV
			double dp = nodeRel.dot(edge) / pow(edge.mag(), 2);
			dp = fmax(0, fmin(1, dp));
				
			Vec2 closestP = currentV + (edge * dp);
			//DrawLine(closestP.x, closestP.y, (closestP + shape->normals[i] * 20.).x, (closestP + shape->normals[i] * 20.).y, RED);
			// Collision?
			if (Vec2::dist(node->pos, closestP) < node->radius)
			{
				// Resolve
				node->pos = closestP + (node->pos - closestP).norm() * node->radius;
			}

		}
	}
}