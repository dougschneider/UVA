// STRINGS
// This solution works by reading the notes in. Each is converted into a number
// representing it's value on the musical scale, between 0 and 11.  Then the
// string of notes is converted into a diff, where each note is the difference
// between it and the note before it. The first note is always 0.  This value
// is adjusted via modulo to always be in [0,11]. Finally the pattern is
// searched for in the input music.
#include <cstdio>
#include <map>
#include <iostream>

using namespace std;

// mapping of standard notes to their values
map<char, int> notesMap = {{'C', 0}, {'D', 2}, {'E', 4}, {'F', 5},
                           {'G', 7}, {'A', 9}, {'B', 11}};

// get the value of the input note. The note value is taken from the notesMap
// and 'b's subtract 1 and '#'s add 1. The result is in the range [0,11]
char getNoteValue(char* note)
{
    return (notesMap[note[0]] + (note[1] == '#') - (note[1] == 'b') + 12) % 12;
}

// return true if the pattern is in the music, otherwise false
bool find(char* music, int musicLength, char* pattern, int patternLength)
{
    int j = 1;
    // iterate through all of the music notes
    for(int i = 1; i < musicLength; ++i)
    {
        if(music[i] == pattern[j])
        {
            // if we have a match move to the next note in the pattern
            ++j;
        }
        else
        {
            // if we have matched part of the pattern, move back a note
            // in the music
            if(j > 1)
                --i;
            // restart matching the pattern
            j = 1;
        }
        // if we've matched the entire pattern, its a match
        if(j == patternLength)
            return true;
    }
    return false;
}

int main()
{
    int dummy;
    int musicLength, patternLength;
    while(true)
    {
        dummy = scanf("%d %d\n", &musicLength, &patternLength);
        // break out at the end
        if(musicLength == 0 && patternLength == 0)
            break;
        char music[musicLength];
        char pattern[patternLength];
        char note[4];
        int last = -1;
        // read in all the music
        for(int i = 0; i < musicLength; ++i)
        {
            dummy = scanf("%s", note);
            music[i] = getNoteValue(note);
            // set the first note to 0 as its diff
            if(last == -1)
            {
                last = music[i];
                music[i] = 0;
            }
            else
            {
                // set each note as the diff between it and
                // the last note
                int tmp = music[i];
                music[i] = (music[i] - last + 12) % 12;
                last = tmp;
            }
        }
        last = -1;
        // read in the pattern
        for(int i = 0; i < patternLength; ++i)
        {
            dummy = scanf("%s", note);
            pattern[i] = getNoteValue(note);
            // set the first note to 0 as its diff
            if(last == -1)
            {
                last = pattern[i];
                pattern[i] = 0;
            }
            else
            {
                // set each note as the diff between it and
                // the last note
                int tmp = pattern[i];
                pattern[i] = (pattern[i] - last + 12) % 12;
                last = tmp;
            }
        }

        // print the result
        if(find(music, musicLength, pattern, patternLength))
            printf("S\n");
        else
            printf("N\n");
    }
}
