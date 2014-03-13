// NONTRIVIAL
// SIMULATION
// This algorithm performs the defined actions using a structure similar to a
// doubly linked list. The configuration of blocks is updated after each
// command until quit is encountered.
#include <iostream>
#include <string>

using namespace std;

// a block represenation useable as a doubly linked list
struct Block
{
    int num;
    Block* prev;
    Block* next;
};

// the blocks and their configuration
int numBlocks;
Block blocks[26];
Block* configuration[26];

// return the pointer to the base block that
// the given block is stacked on. If the block is in its
// original position, it's pointer is returned.
Block* find(Block* block)
{
    Block* next = block;
    while(true)
    {
        // stop when we get to the first block
        if(next->prev == NULL)
            return next;
        // iterate through previous blocks
        next = next->prev;
    }
}

// return all of the blocks stacked on top
// of the given block to their original places. all
// prev and next links are removed in the process.
void returnAll(Block* block)
{
    Block* next = block;
    while(true)
    {
        // return required blocks to their start position
        if(next != block)
            configuration[next->num] = next;
        // stop at the end
        if(next->next == NULL)
            return;
        
        // break the link and get the next block
        next->next->prev = NULL;
        Block* tmp = next->next;
        next->next = NULL;
        next = tmp;
    }
}

// stack the block b (and blocks on top of it) on the bottom
// block, or top-most block on top of it if there is one.
void stack(Block* bottom, Block* b)
{
    Block* next = bottom;
    while(true)
    {
        // find the last block on top of bottom
        if(next->next == NULL)
        {
            // place b on top of the top block
            next->next = b;
            // link the blocks
            b->prev = next;
            break;
        }
        // move to the next block
        next = next->next;
    }
}

// print the stack of blocks on top of the given
// block including the given block
void printStack(Block* block)
{
    Block* next = block;
    while(true)
    {
        // print spaces between blocks
        cout << " ";
        cout << next->num;
        // stop at the last block
        if(next->next == NULL)
            break;

        // move to the next block
        next = next->next;
    }
}

// print the block configuration with the required
// output specification.
void print()
{
    // print each blocks stack
    for(int i = 0; i < numBlocks; ++i)
    {
        cout << i << ":";
        if(configuration[i] != NULL)
            printStack(blocks+i);
        cout << endl;
    }
}

// remove the given block from being on top
// of its current base block
void remove(Block* block)
{
    if(block->prev != NULL)
        block->prev->next = NULL;
}

int main()
{
    string movement, style;
    int a, b;

    // read in the number of blocks
    cin >> numBlocks;

    // read in each block
    for(int i = 0; i < numBlocks; ++i)
    {
        blocks[i].num = i;
        blocks[i].prev = NULL;
        blocks[i].next = NULL;
        configuration[i] = blocks+i;
    }

    // handle each command
    while(true)
    {
        cin >> movement >> a >> style >> b;

        // stop on quit command
        if(movement == "quit")
            break;

        // skip invalid commands
        if(a == b || find(blocks+a) == find(blocks+b))
            continue;

        if(movement == "move")
        {
            // move a onto b
            if(style == "onto")
            {
                returnAll(blocks+a);
                returnAll(blocks+b);
            }
            // move a over b
            else if(style == "over")
            {
                returnAll(blocks+a);
            }
        }
        // pile a onto b
        else if(movement == "pile" && style == "onto")
        {
            returnAll(blocks+b);
        }

        // update the configuration
        remove(blocks+a);
        stack(blocks+b, blocks+a);
        configuration[a] = NULL;
    }

    // print the resulting configuration
    print();

    return 0;
}
