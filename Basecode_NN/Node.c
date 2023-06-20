#include "Node.h"

Node* Node_New(void)
{
	Node* node = (Node*)calloc(1, sizeof(Node));
	assert(node);

	for (int k = 0; k < NODE_PER_LAYER; k++)
	{
		node->w[k] = Float_Random(-1.0f, +1.0f);
	}

	node->b = Float_Random(-1.0f, +1.0f);

	return node;
}

Node* Node_Copy(Node* node)
{
	if (!node) return NULL;

	Node* res = (Node*)calloc(1, sizeof(Node));
	assert(res);

	*res = *node;

	return res;
}

void Node_Destroy(Node* node)
{
	if (!node) return;

	free(node);
}
