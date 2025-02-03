#include<stdio.h>
#include<stdlib.h>

#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>

#include"util/util.h"
#include"database/database.h"
#include"database/construct.h"

#include<string.h>
#include"database/binj.h"
#include<locale.h>
#include<wchar.h>
#include<iostream>
#include"ui/test.hpp"

#include"test/test.h"

int main(int argc, char *argv[])
{    
    Application App;
    App.run();

    return 0;
}