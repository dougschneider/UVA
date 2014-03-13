// NONTRIVIAL
// COMBINATORICS
// This algorithm works by applying the given set of rotations to a Rubiks
// Cube. It then creates a map of transformations. Where the key is the
// starting tile, and the value is the tile that the starting tile ended up in
// after the rotations were applied. It then computes the permutation cycle
// length of each tile of the rubiks cube. The answer to the problem is the
// Lowest Common Multiple of all the permutation cycle lengths.
#include <map>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

// a face of of the Rubik's Cube
struct Face
{
    Face()
    {
    }

    // Make a face with the given character
    // as its name
    Face(char name) :
        name(name)
    {
        // create each tile
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                initTile(i, j);
    }

    // give the given tile a name
    void initTile(int row, int col)
    {
        stringstream ss;
        ss << name << (row*3 + col + 1);
        string tileName;
        ss >> tileName;
        tiles[row][col] = tileName;
    }

    // print out this face
    void print()
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
                cout << tiles[i][j] << " ";
            cout << endl;
        }
    }

    // rotate this face ClockWise, including the tiles
    // on adjacent faces that will move when this face is rotated
    void rotateCW()
    {
        // rotate our face first
        string t1, t2, t3;

        // store the top row
        t1 = tiles[0][0];
        t2 = tiles[0][1];
        t3 = tiles[0][2];

        // left side to the top
        tiles[0][2] = tiles[0][0];
        tiles[0][0] = tiles[2][0];
        tiles[0][1] = tiles[1][0];

        // bottom to the left side
        tiles[0][0] = tiles[2][0];
        tiles[1][0] = tiles[2][1];
        tiles[2][0] = tiles[2][2];

        // right side to the bottom
        tiles[2][0] = tiles[2][2];
        tiles[2][1] = tiles[1][2];
        tiles[2][2] = tiles[0][2];

        // top to right side
        tiles[2][2] = t3;
        tiles[1][2] = t2;
        tiles[0][2] = t1;

        // rotate surrounding faces
        
        // store the top faces row
        string upTiles[3];
        up->getTilesFacing(this, upTiles);

        string tmpTiles[3];
        // rotate left tiles up
        left->getTilesFacing(this, tmpTiles);
        up->setTilesFacing(this, tmpTiles);

        // rotate down tiles left
        down->getTilesFacing(this, tmpTiles);
        left->setTilesFacing(this, tmpTiles);

        // rotate right tiles down
        right->getTilesFacing(this, tmpTiles);
        down->setTilesFacing(this, tmpTiles);

        // rotate up tiles right
        right->setTilesFacing(this, upTiles);
    }

    // rotate this face CounterClockWise, including the tiles
    // on adjacent faces that will move when this face is rotated
    void rotateCCW()
    {
        // rotate our face first
        string t1, t2, t3;

        // store the top row
        t1 = tiles[0][0];
        t2 = tiles[0][1];
        t3 = tiles[0][2];

        // right side to the top
        tiles[0][0] = tiles[0][2];
        tiles[0][1] = tiles[1][2];
        tiles[0][2] = tiles[2][2];

        // bottom side to the right
        tiles[0][2] = tiles[2][2];
        tiles[1][2] = tiles[2][1];
        tiles[2][2] = tiles[2][0];

        // left side to the bottom
        tiles[2][2] = tiles[2][0];
        tiles[2][1] = tiles[1][0];
        tiles[2][0] = tiles[0][0];

        // top to the left side 
        tiles[2][0] = t1;
        tiles[1][0] = t2;
        tiles[0][0] = t3;

        // rotate surrounding faces
        
        // store the top faces row
        string upTiles[3];
        up->getTilesFacing(this, upTiles);

        string tmpTiles[3];
        // rotate the right tiles up
        right->getTilesFacing(this, tmpTiles);
        up->setTilesFacing(this, tmpTiles);

        // rotate the down tiles right
        down->getTilesFacing(this, tmpTiles);
        right->setTilesFacing(this, tmpTiles);

        // rotate the left tiles down
        left->getTilesFacing(this, tmpTiles);
        down->setTilesFacing(this, tmpTiles);

        // rotate up tiles left
        left->setTilesFacing(this, upTiles);
    }

    // Populate the given array with the tiles that are facing
    // the given face.
    void getTilesFacing(Face* face, string* tarr)
    {
        if(face == up)
        {
            // top three tiles
            tarr[0] = tiles[0][2];
            tarr[1] = tiles[0][1];
            tarr[2] = tiles[0][0];
        }
        else if(face == down)
        {
            // bottom three tiles
            tarr[0] = tiles[2][0];
            tarr[1] = tiles[2][1];
            tarr[2] = tiles[2][2];
        }
        else if(face == right)
        {
            // right three tiles
            tarr[0] = tiles[2][2];
            tarr[1] = tiles[1][2];
            tarr[2] = tiles[0][2];
        }
        else if(face == left)
        {
            // left three tiles
            tarr[0] = tiles[0][0];
            tarr[1] = tiles[1][0];
            tarr[2] = tiles[2][0];
        }
        else
            throw exception();
    }

    // set the tiles facing the given face with the tiles
    // in the given array
    void setTilesFacing(Face* face, string* tarr)
    {
        if(face == up)
        {
            // the top three tiles
            tiles[0][2] = tarr[0];
            tiles[0][1] = tarr[1];
            tiles[0][0] = tarr[2];
        }
        else if(face == down)
        {
            // the bottom three tiles
            tiles[2][0] = tarr[0];
            tiles[2][1] = tarr[1];
            tiles[2][2] = tarr[2];
        }
        else if(face == right)
        {
            // the right three tiles
            tiles[2][2] = tarr[0];
            tiles[1][2] = tarr[1];
            tiles[0][2] = tarr[2];
        }
        else if(face == left)
        {
            // the left three tiles
            tiles[0][0] = tarr[0];
            tiles[1][0] = tarr[1];
            tiles[2][0] = tarr[2];
        }
        else
            throw exception();
    }

    Face* up;
    Face* down;
    Face* right;
    Face* left;

    string tiles[3][3];
    char name;
};

// a Rubik's Cube
struct Cube
{
    // Create a Rubik's cube with all 6 faces.
    Cube()
    {
        F = Face('F');
        B = Face('B');
        R = Face('R');
        L = Face('L');
        U = Face('U');
        D = Face('D');

        // connect the faces
        connectFaces();
    }

    // Connect the faces of the Rubiks cube.
    void connectFaces()
    {
        // connect the front face to the four sides
        F.up    = &U;
        F.down  = &D;
        F.right = &R;
        F.left  = &L;

        // connect the back face to the four sides
        B.up    = &U;
        B.down  = &D;
        B.right = &L;
        B.left  = &R;

        // connect the right face to the four sides
        R.up    = &U;
        R.down  = &D;
        R.right = &B;
        R.left  = &F;

        // connect the left face to the four sides
        L.up    = &U;
        L.down  = &D;
        L.right = &F;
        L.left  = &B;

        // connect the top face to the four sides
        U.up    = &B;
        U.down  = &F;
        U.right = &R;
        U.left  = &L;

        // connect the bottom face to the four sides
        D.up    = &F;
        D.down  = &B;
        D.right = &R;
        D.left  = &L;
    }

    // Rotate a face on the Rubik's cube based on the given
    // character.
    void rotate(char rotation)
    {
        switch(rotation)
        {
            case 'F':
                F.rotateCW();
                break;
            case 'f':
                F.rotateCCW();
                break;
            case 'B':
                B.rotateCW();
                break;
            case 'b':
                B.rotateCCW();
                break;
            case 'R':
                R.rotateCW();
                break;
            case 'r':
                R.rotateCCW();
                break;
            case 'L':
                L.rotateCW();
                break;
            case 'l':
                L.rotateCCW();
                break;
            case 'U':
                U.rotateCW();
                break;
            case 'u':
                U.rotateCCW();
                break;
            case 'D':
                D.rotateCW();
                break;
            case 'd':
                D.rotateCCW();
                break;
            default:
                throw exception();
        };
    }

    // Create a map of the transformations that have occurred for each tile of
    // this Rubik's cube. The transformations are based on a solved Rubik's Cube.
    map<string, string> createTransformationMap()
    {
        map<string, string> transformations;

        // populate the transformations for each face.
        createTransformationForFace(F, transformations);
        createTransformationForFace(B, transformations);
        createTransformationForFace(R, transformations);
        createTransformationForFace(L, transformations);
        createTransformationForFace(U, transformations);
        createTransformationForFace(D, transformations);

        return transformations;
    }

    void createTransformationForFace(const Face& face, map<string, string>& transformations)
    {
        // populate the transformation for each tile
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                stringstream ss;
                ss << face.name << ((i*3) + j + 1);
                string tile;
                ss >> tile;
                // set the location of this tile after the transformation
                transformations[tile] = face.tiles[i][j];
            }
        }
    }

    Face F, B, R, L, U, D;

    map<char, Face> faces;
};

// return the GCD for the two inputs
ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// return the LCM for the two inputs
ll lcm(ll a, ll b)
{
    return a * (b / gcd(a, b));
}

// return the LCM for a list of numbers
ll lcm_list(vector<ll>& cycleLengths)
{
    if(cycleLengths.size() == 2)
        return lcm(cycleLengths[0], cycleLengths[1]);

    ll next = cycleLengths.back();
    cycleLengths.pop_back();
    return lcm(next, lcm_list(cycleLengths));
}

// get the length of the cycle given the start location and a map of
// the transformations
int getCycleLength(map<string, string>& transformations, string start)
{
    string next;
    next = start;
    int count = 0;
    // loop until we reach the start
    while(true)
    {
        // follow the transformation
        next = transformations[next];
        ++count;
        // we're back at the start so we're done
        if(next == start)
            break;
    }
    return count;
}

// get the numbers of transformations required for all tiles to be
// put back to where they started based on the input transformations
// map.
int getNumTransformations(map<string, string>& transformations)
{
    vector<ll> cycleLengths;
    map<string, string>::const_iterator it = transformations.begin(),
                                        end = transformations.end();
    // look at each tiles transformations
    for(; it != end; ++it)
    {
        // add the new cycle length to the list
        cycleLengths.push_back(getCycleLength(transformations, it->first));
    }

    // return the Lowest Common Multiple
    return lcm_list(cycleLengths);
}

int main()
{
    string sequence;
    // read input until EOF
    while(true)
    {
        cin >> sequence;
        // EOF so we're done
        if(!cin)
            break;

        Cube cube;
        // perform the given rotation sequence
        for(int i = 0; i < sequence.length(); ++i)
            cube.rotate(sequence[i]);

        // get the transformations after the sequence is complete
        map<string, string> transformations = cube.createTransformationMap();
        // print the number of times the transformations have to be applied to
        // bring us back to the start.
        cout << getNumTransformations(transformations) << endl;
    }
    return 0;
}
