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
                        if (cX == fileData[cY].length()) {
                            fileData.resize(size(fileData)+1);
                            for (int i=cY+1;i<size(fileData);i++) {
                                fileData[i] = fileData[i+1];
                            }
                            cY++;
                        }
                        else {
                            fileData.resize(size(fileData)+1);
                            cY++;
                            bestLine++;
                            cX = 0;
                        }
                        break;
                    }
        }
    }
    // Backspace
    else if (inputData == 127) {
        if (cX > 0) {
            if (mode==1) {
                fileData[cY].resize(fileData[cY].length()-1);
                for (int s=cX-1;s<fileData[cY].length();s++) {
                    fileData[cY][s] = fileData[cY][s+1];
                }
                bestLine--;
            }
            cX--;
        }
        else if (cX == 0){
            for (int i=cY;i<size(fileData);i++) {
                fileData[i] = fileData[i+1];
            }
            fileData.resize(size(fileData)-1);
            cY--;
            cX = fileData[cY].length();
            editWindow->drawOutCommand = "OK";
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
                                          if (bestLine > cY) cY++;
                                          cX = fileData[cY].length();
                                          break;
                                      }
                            // k
                            case 107: {
                                          if (cY > 0) cY--;
                                          cX = fileData[cY].length();
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
                        std::string addStr(1, inputData);
                        //fileData[cY].resize(fileData[cY].length()+1);
                        fileData[cY].insert(cX, addStr);
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
            cY = 1;
            cX = 0;
            input_file.close();
        }
    }
    bestLine = size(fileData)-1;

    cY = 1;
    cX = 0;

    mainWindow->MainInit();

    return 0;
}
