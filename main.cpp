#include "Main.hpp"

void MainWindow::clear() {
    for (int i=0;i<editWindow->h;i++)
        printf("");
}

void MainWindow::MainInit(void) {

    //system("clear");
    //printf("\e[?25l");
    clear();

    backC = 236;
    cursC = 7;
    textC = 188;
    numC = 13;
    nomalC = 34;
    loopC = 123;
    symbolbracketC = 228;
    reservC = 75;
    typeC = 46;
    strC = 26;
    ifC = 160;
    commandC = 129;

    fileDataC = 0;
    command->inputCommand = "";

    MainWindow::Main();
}

void MainWindow::Main(void) {
    struct winsize ws;
    int inputData = 0;

    if (~ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)) {
        editWindow->w = ws.ws_col;
        editWindow->h = ws.ws_row-3; // コマンド列分マイナス
    }
    else {
        perror("ioctl");
    }

    editWindow->drawDataLine();
    editWindow->drawCommandLine();
    editWindow->drawOutCommandLine();

    inputData = getch();

    if (inputData == 13 || inputData == '\n') {
        switch (mode) {
            case 0: {
                        //cursXを正しい値にする（global変数使う）
                        editWindow->drawOutCommand = command->runCommand();
                        command->inputCommand = "";//内部データ
                        editWindow->drawCommand = "";//表示用
                        break;
                    }
            case 1: {
                        bestLine++; // ラインの最大値を上げる
                        if (cX < fileData[cY].length()) {
                            // 行の途中で改行された場合
                            std::string str1 = fileData[cY].substr(cX);
                            fileData[cY].erase(cX, fileData[cY].length()-cX);
                            cY++;
                            // ファイル容量を一つ増やす
                            fileData.resize(bestLine+1);
                            fileData[cY] = str1;
                            cY++;

                            std::string tmp = "";
                            std::string tmp2 = "";

                            // ファイル容量を一つ増やす
                            fileData.resize(bestLine+1);

                            for (int i=cY;i<size(fileData);i++) { // ファイルの終了まで
                                tmp = fileData[i]; // 今の行のデータ
                                fileData[i] = tmp2; // 初回は空、二回目以降前の行のデータが格納される
                                tmp2 = tmp; // 初回は空、二回目からデータありを実現するカラクリ
                            }

                            cX = str1.length();
                        } else {
                            cY++; // カーソルを一つ下げる
                            // 行で最後の文字のところで改行された場合
                            if (bestLine == cY) {
                                // 一番下のラインを追加hした場合
                                editWindow->drawOutCommand = "Add New Line!";
                                // ファイル容量を一つ増やす
                                fileData.resize(bestLine+1);
                            }

                            else {
                                // カーソルを途中追加した場合
                                std::string tmp = "";
                                std::string tmp2 = "";

                                // ファイル容量を一つ増やす
                                fileData.resize(bestLine+1);

                                for (int i=cY;i<size(fileData);i++) { // ファイルの終了まで
                                    tmp = fileData[i]; // 今の行のデータ
                                    fileData[i] = tmp2; // 初回は空、二回目以降前の行のデータが格納される
                                    tmp2 = tmp; // 初回は空、二回目からデータありを実現するカラクリ
                                }
                            }
                        }
                        cX = 0; // カーソルを先頭に持ってくる

                        break;
                    }
            case 2: {
                        // ファイル容量を一つ増やす
                        editWindow->drawOutCommand = command->runCommand();
                        command->inputCommand = "";//内部データ
                        editWindow->drawCommand = "";//表示用
                        cX = 0;
                        mode = 0;

                        break;
                    }
            default:
                    break;
        }
    }
    // Backspace
    else if (inputData == 127) {
        if (cX > 0) {
            if (mode==0) {}
            if (mode==1) {
                fileData[cY][cX-1] = ' ';
                fileData[cY].resize(fileData[cY].length()-1);
                for (int s=cX-1;s<fileData[cY].length();s++) {
                    fileData[cY][s] = fileData[cY][s+1];
                }
            }
            cX--;
        }
        else if (cX == 0){
            // 行をひとつ削除する場合

            fileData[cY-1] += fileData[cY];
            editWindow->drawOutCommand = fileData[cY-1];

            cY--;
            bestLine--;
            std::string tmp = "";
            std::string tmp2 = "";

            for (int i=cY+1;i<size(fileData)-1;i++) { // ファイルの終了まで
                fileData[i] = fileData[i+1];
            }

            // ファイル容量を一つ減らす
            fileData.resize(size(fileData)-1);
            cX = fileData[cY].length();
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
                                          if (cX > 0) {
                                              cX--;
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
                                          // ファイル下限
                                          if (size(fileData) > cY) {
                                              if (editWindow->h+fileDataC == cY ) {
                                                  fileDataC++;
                                                  bestLine++;
                                                  newC++;
                                              }
                                              else cY++;
                                              if (cX > fileData[cY].length())
                                                  cX = fileData[cY].length();
                                          }
                                          break;
                                      }
                            // k
                            case 107: {
                                          // ファイル上限
                                          if (cY > 0) {
                                              if (fileDataC == cY) {
                                                  newC--;
                                                  fileDataC--;
                                                  bestLine--;
                                                  newC--;
                                              }
                                              else cY--;
                                              if (cX > fileData[cY].length())
                                                  cX = fileData[cY].length();
                                          }
                                          break;
                                      }
                                      // l
                            case 108: {
                                          if (cX < fileData[cY].length())
                                              cX++;
                                          break;
                                      }
                             // ESC
                            case 58: {
                                         mode = 2;
                                         cX = 0;
                                         break;
                                     }
                            default:
                                     break;
                        }
                        break;
                    }
            // insert
            case 1: {
                        if (inputData == 9) {
                            for (int i=4;i>0;i--) {
                                std::string addStr(1, ' ');
                                fileData[cY].insert(cX, addStr);
                                cX++;
                            }
                        }
                        else {
                            std::string addStr(1, inputData);
                            fileData[cY].insert(cX, addStr);
                            cX++;
                        }
                        break;
                    }
            // prompt
            case 2: {
                        std::string addStr(1, inputData);
                        editWindow->drawCommand.insert(cX, addStr);
                        command->inputCommand.insert(cX, addStr);
                        cX++;
                        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
                        break;
                    }
            default:
                    break;
        }
    }

    /*claer window */

    /*
     * if it has bug:
     * printf("\033[2J");
     * printf("\033[1J");
     * system("clear");
    */

    clear();
    Main();
}

int main(int argc, char*argv[]) {
    /* Main class */
    MainWindow mw;
    MainWindow *mainWindow = &mw;

    if ( argc > 1) {
        std::string line;
        lineNum = 0;
        openFileName = argv[1];
        std::ifstream input_file(openFileName, std::ios::in);
        if (!input_file) {
            std::cout << "Could not open the file : '" << openFileName <<  "'" << std::endl;
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
    else {
        mode = 2;
        fileData = {
            "_____________________________",
            "|                           |",
            "|                           |",
            "|          _________________|",
            "|          |",
            "|          |",
            "|          |________________",
            "|                          |",
            "|                          |",
            "|           _______________|",
            "|          |",
            "|          |",
            "|          |________________",
            "|                          |",
            "|                          |",
            "|__________________________|",
        };
        cY = 1;
        cX = 0;
            fileDataC = 0;
    }
    bestLine = size(fileData)-1;

    /* cursol */
    cY = 1;
    cX = 0;
    fileDataC = 0;
    newC = 0;

    mainWindow->MainInit();

    return 0;
}

/*
 */
