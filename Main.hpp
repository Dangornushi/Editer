#pragma once

#ifndef Main_H
#define Main_H


// include
#include <termios.h>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <thread>
#include <fstream>
#include <stdio.h>

class EditWindow {
    std::vector<std::string> putStrings;
    public:
        int w;
        int h;
        int cursX;
        int cursY;
        std::string drawData;
        std::string drawCommand;
        std::string drawOutCommand;
        std::vector<std::string> drawingData;
        void drawDataLine();
        void drawCommandLine();
        void drawOutCommandLine();
        void drawWindow();
};

class Io {
    std::string openData;
};

class Command {
    public:
        std::vector<std::string>command;
        std::vector<std::string>commandHistroy;
        std::string inputCommand;
        std::string runCommand();
};


class MainWindow {
    public:
        EditWindow ew;
        Command cd;
        EditWindow *editWindow = &ew;
        Command *command = &cd;
        std::string openFileName;
        void MainInit();
        void Main();
};

int getche(void);
int getch(void);
int kbhit(void);

inline std::vector<std::string> fileData;
inline int lineNum;
inline int mode;
inline int cX;
inline int cY;
inline std::string openFileName;

#endif
