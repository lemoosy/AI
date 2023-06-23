#include "Node.h"

Node* Node_New(void)
{
	Node* node = (Node*)calloc(1, sizeof(Node));
	assert(node);

	for (int k = 0; k < NODE_PER_LAYER; k++)
	{
		node->w[k] = float_random(-1.0f, +1.0f);
	}

	node->b = float_random(-1.0f, +1.0f);

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

void Node_ExportBin(Node* node, FILE* file)
{
	fwrite(node, sizeof(Node), 1, file);
}

Node* Node_ImportBin(FILE* file)
{
	Node* node = (Node*)calloc(1, sizeof(Node));
	assert(node);
	
	fread(node, sizeof(Node), 1, file);
	
	return node;
}
