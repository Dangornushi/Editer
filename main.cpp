#include "Main.hpp"

std::string lineData;

void MainWindow::MainInit(void) {

    system("clear");

    MainWindow::Main();
}

void MainWindow::Main(void) {
    struct winsize ws;
    int inputData;

    if (~ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)) {
        editWindow->w = ws.ws_col;
        editWindow->h = ws.ws_row ;
    }
    else {
        perror("ioctl");
    }
    editWindow->h-=3;
    editWindow->drawDataLine();
    editWindow->drawCommandLine();
    editWindow->drawOutCommandLine();

    while (1) {
        if (kbhit()) {
            inputData = getch();
            break;
        }
    }

    if (inputData == '\n') {
        cX = 0;
        switch (mode) {
            case 0: {
                        //cursXを正しい値にする（global変数使う）
                        editWindow->drawOutCommand = command->runCommand();
                        command->inputCommand.resize(0);//内部データ
                        editWindow->drawCommand.resize(0);//表示用
                        break;
                    }
            case 1: {
                        fileData.resize(size(fileData)+1);
                        cY++;
                        break;
                    }
        }
    }
    // Backspace
    else if (inputData == 127) {
        if (cX > 0) {
            cX--;
            if (mode==1) {
                fileData[cY].resize(cX);
            }
        }
    }
    else if (inputData == 27) {
        editWindow->drawOutCommand = "mode = Nomal";
        mode = 0;
    }
    else {
        switch (mode) {
            // command
            case 0: {
                        switch (inputData) {
                            // h
                            case 104: {
                                          cX--;
                                          break;
                                      }
                            // j
                            case 106: {
                                          if (cY < lineNum) cY++;
                                          break;
                                      }
                            // k
                            case 107: {
                                          if (cY > 0) cY--;
                                          break;
                                      }
                            // l
                            case 108: {
                                          cX++;
                                          break;
                                      }
                            default: {
                                         editWindow->drawCommand += inputData;
                                         command->inputCommand += inputData;
                                         cX++;
                                         break;
                                     }
                        }
                        break;
                    }
            // insert
            case 1: {
                        //fileData[cY].resize(cX);
                        fileData[cY].push_back(inputData);
                        cX++;
                        break;
                    }
        }
    }
    system("clear");
    Main();
}

int main(void) {
    MainWindow mw;
    MainWindow *mainWindow = &mw;

    cY = 1;
    cX = 0;

    mainWindow->MainInit();

    return 0;
}
