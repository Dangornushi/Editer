#include "Main.hpp"

std::string lineData;

void MainWindow::MainInit(void) {

    system("clear");

    MainWindow::Main();
}

void MainWindow::Main(void) {
    struct winsize ws;
    int inputData = 0;

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
                        cX = 0;
                        break;
                    }
        }
    }
    // Backspace
    else if (inputData == 127) {
        if (cX > 0) {
            if (mode==1) {
                fileData[cY][cX-1] = ' ';
            }
            cX--;
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
                                          if (cX > 0) cX--;
                                          else {
                                              cY--;
                                              cX = fileData[cY].length();
                                          }
                                          break;
                                      }
                            // i
                            case 105: {
                                          mode = 1;
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
                                          if (cX < fileData[cY].length()) {
                                              cX++;
                                          }
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
                        fileData[cY].resize(cX);
                        fileData[cY].push_back(inputData);
                        cX++;
                        break;
                    }
        }
    }
    system("clear");
    Main();
}

int main(int argc, char*argv[]) {
    MainWindow mw;
    MainWindow *mainWindow = &mw;

    if (argc > 1) {
        std::string line;
        lineNum = 0;
        openFileName = argv[1];
        std::ifstream input_file(openFileName, std::ios::in);
        if (!input_file) {
            std::cout << "Could not open the file -> '" << openFileName <<  "'" << std::endl;
            return 0;
        }
        else {
            while (getline(input_file, line)) {
                fileData.push_back(line);
                lineNum++;
            }
            if (lineNum == 0) {
                lineNum++;
                fileData.push_back("\n");
            }
            lineNum--;
            cY = 0;
            cX = 0;
            input_file.close();
        }
    }

    cY = 1;
    cX = 0;

    mainWindow->MainInit();

    return 0;
}
