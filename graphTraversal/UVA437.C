// GRAPH THEORY
// This algorithm works by creating the set of all possible
// blocks by rotating the input blocks. It then performs a
// depth first search on the blocks to find the length of
// the longest path of blocks that can be stacked on each
// other. In addition branches are cached so they don't need
// to be recomputed.
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

int numBlocks;
map<int, int> cache;

struct Block
{
    int height, width, length;
};

int buildGraph(int current, vector<Block>& blocks)
{
    int max = -1;
    // look at each possible next block
    for(int i = 0; i < numBlocks*3; ++i)
    {
        // if the blocks can be stacked, explore it
        if(blocks[i].width < blocks[current].width &&
                blocks[i].length < blocks[current].length)
        {
            int length;
            // if this branch hasn't been cached yet, find it
            if(cache.find(i) == cache.end())
            {
                length = buildGraph(i, blocks);
                cache[i] = length;
            }
            else// use the cached value
            {
                length = cache[i];
            }
            // if this is better than the best so far, use it
            if(length > max)
                max = length;
        }
    }

    // if we haven't found a block to put on top, we're at a leaf
    if(max == -1)
        return blocks[current].height;
    return blocks[current].height + max;
}

int main()
{
    int count = 0;
    while(true)
    {
        cache.clear();
        ++count;
        cin >> numBlocks;
        if(numBlocks == 0)
            break;

        // create the list of blocks and add the root
        vector<Block> blocks(numBlocks*3+1);
        Block root;
        root.height = 0;
        root.width = 1000000000;
        root.length = 1000000000;
        blocks[numBlocks*3] = root;

        // read in the blocks and add all possible dimensions
        int height, width, length;
        for(int i = 0; i < numBlocks; ++i)
        {
            cin >> height >> width >> length;
            blocks[i*3].height = height;
            blocks[i*3].width = min(width, length);
            blocks[i*3].length = max(width, length);
            blocks[i*3+1].height = width;
            blocks[i*3+1].width = min(height, length);
            blocks[i*3+1].length = max(height, length);
            blocks[i*3+2].height = length;
            blocks[i*3+2].width = min(height, width);
            blocks[i*3+2].length = max(height, width);
        }

        // build the graph and get the solution
        int longestPath = buildGraph(numBlocks*3, blocks);

        // print the solution
        cout << "Case " << count << ": maximum height = " << longestPath << endl;
    }
    return 0;
}
