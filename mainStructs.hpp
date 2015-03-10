#ifndef MAINSTRUCTS_HPP_INCLUDED
#define MAINSTRUCTS_HPP_INCLUDED

#include <windows.h>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>

using namespace std;

typedef unsigned char Flags;
typedef unsigned short EFlags; // Extended Flags

#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define BACKGROUND_WHITE BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define FOREGROUND_WHITE_INTENSITY FOREGROUND_WHITE | FOREGROUND_INTENSITY
#define BACKGROUND_WHITE_INTENSITY BACKGROUND_WHITE | BACKGROUND_INTENSITY

#define F_DL_NOWARN 1

enum class HelpNext{None, Haylp, Fomayday, Ausekoure};

struct Track{
    sf::Music* music;
    string path;
    unsigned char flags;
};

struct ReturnedError{
    bool isError;
    DWORD winId;
    string errorMsg;
};

#endif // MAINSTRUCTS_HPP_INCLUDED
