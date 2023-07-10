#include "AI.h"

#ifdef GAME_CONNECT4

// ------------------------------ Minimax ------------------------------

void TreeAI_DestroyRec(NodeAI* node)
{
    if (!node) return;

    for (int i = 0; i < GRID_W; i++)
    {
        TreeAI_DestroyRec(node->children[i]);
    }

    Game_Destroy(node->game);
    free(node);
}

void TreeAI_Destroy(TreeAI* tree)
{
    if (!tree) return;

    TreeAI_DestroyRec(tree->root);
    free(tree);
}

NodeAI* TreeAI_Minimax_CreateRec(Game* game, PlayerID turn, int depth, bool minLayer, int A, int B)
{
    NodeAI* node = (NodeAI*)calloc(1, sizeof(NodeAI));
    assert(node);

    node->game = game;

    int state = game->state;

    if (state != GAME_IN_PROGRESS)
    {
        if (state == GAME_IS_TIED)
        {
            node->score = 0;
        }
        else if (state == turn)
        {
            node->score = +1000;
        }
        else
        {
            node->score = -1000;
        }

        return node;
    }

    if (depth == 0)
    {
        node->score = Game_Heuristic(game, turn);

        return node;
    }

    node->score = ((minLayer) ? +1000 : -1000);
    node->move = -1;

    for (int i = 0; i < GRID_W; i++)
    {
        if (!Game_CanPlayAt(game, i)) continue;

        Game* copy = Game_Copy(game);
        Game_PlayAt(copy, i);

        node->children[i] = TreeAI_Minimax_CreateRec(
            copy,
            turn,
            depth - 1,
            !minLayer,
            A,
            B
        );

        if (minLayer)
        {
            if (node->children[i]->score < node->score)
            {
                node->score = node->children[i]->score;
                node->move = i;

                B = node->score;
            }
        }
        else
        {
            if (node->children[i]->score > node->score)
            {
                node->score = node->children[i]->score;
                node->move = i;

                A = node->score;
            }
        }

        TreeAI_DestroyRec(node->children[i]);
        node->children[i] = NULL;

        if (A >= B) return node;
    }

    while (!Game_CanPlayAt(game, node->move))
    {
        node->move++;
    }

    return node;
}

TreeAI* TreeAI_Minimax_Create(Game* game)
{
    TreeAI* tree = (TreeAI*)calloc(1, sizeof(TreeAI));
    assert(tree);
    tree->root = TreeAI_Minimax_CreateRec(Game_Copy(game), game->turn, DEPTH_MAX, false, -1000, +1000);
    return tree;
}

// ------------------------------ AI ------------------------------

Mat* __Game_GetMatInputs(Game* game)
{
    int size = GRID_W * GRID_H;

    Mat* m = Mat_Create(1, size * 2);

    data* values = m->values;

    for (int j = 0; j < GRID_H; j++)
    {
        for (int i = 0; i < GRID_W; i++)
        {
            TokenID token = game->grid[j][i];

            if (token == TOKEN_EMPTY) continue;

            if (token == game->turn)
            {
                values[GRID_W * j + i] = 1.0f;
            }
            else
            {
                values[GRID_W * j + i + size] = 1.0f;
            }
        }
    }

    return m;
}

Mat* __Game_GetMatOutputs(Game* game)
{
    int move = AI_Minimax_GetMove(game, game->turn);

    Mat* outputs = Mat_Create(1, GRID_W);
    outputs->values[move] = 1.0f;

    return outputs;
}

int AI_Minimax_GetMove(Game* game)
{
    TreeAI* tree = TreeAI_Minimax_Create(game);
    int res = tree->root->move;
    TreeAI_Destroy(tree);
    return res;
}

int AI_NN_GetMove(Game* game, Network* net)
{
    Mat* inputs = __Game_GetMatInputs(game);
    Mat* outputs = __Game_GetMatOutputs(game);

    Network_Forward(net, inputs);
    Network_Backward(net, outputs);

    Layer* layerOutput = (Layer*)DList_Get(net->layers, -1);
    
    int res = 0;

    for (int i = 1; i < GRID_W; i++)
    {
        if (layerOutput->A->values[i] > layerOutput->A->values[res])
        {
            res = i;
        }
    }

    if (!Game_CanPlayAt(game, res))
    {
        res = AI_Random_GetMove(game);
    }

    Mat_Destroy(outputs);
    Mat_Destroy(inputs);

    return res;
}

int AI_Random_GetMove(Game* game)
{
    int* moves = Int_TabRandomNoRep(GRID_W);

    int index = 0;

    while (!Game_CanPlayAt(game, moves[index]))
    {
        index += 1;
    }

    int res = moves[index];

    free(moves);

    return res;
}

#endif // GAME_CONNECT4
