#include "Main.hpp"

std::string tmp1, tmp2, tmp3,tmp4, tmp5;
int F = 0;
int inComment = 0;

int digit(int n) {
    int c = 0;
    while (1) {
        if (n < 10) break;
        n /= 10;
        c++;
    }
    return c+1;

}

void EditWindow::colorScheme(std::string fileStrS, int num) {
    std::smatch m;
    char fileChar = fileStrS[num];
    if (std::isdigit(fileChar))
        charC = numC;
    if (fileChar == ' ');
    else {
        switch (fileChar) {
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
            case '<':
            case '>':
                charC = symbolbracketC;
                break;
            case '\'':
            case '"': {
                          if (inComment == 0) {
                              charC = strC;
                              inComment = 1;
                              break;
                          }
                          else if (inComment == 1) {
                              inComment = 0;
                          }
                          break;
                      }

            default : {
                          if (F > 1) {
                              charC = FC;
                              F--;
                          }
                          else if (fileStrS.substr(num, num+3) == "if ") {
                              charC = ifC;
                              FC = ifC;
                              F = 2;
                          }
                          else if (fileStrS.substr(num, num+4) == "int ") {
                              charC = typeC;
                              FC = typeC;
                              F = 3;
                          }
                          else if (fileStrS.substr(num, num+4) == "for ") {
                              charC = reservC;
                              FC = reservC;
                              F = 3;
                          }
                          else if (fileStrS.substr(num, num+5) == "char ") {
                              charC = typeC;
                              FC = typeC;
                              F = 4;
                          }
                          else if (fileStrS.substr(num, num+5) == "void ") {
                              charC = typeC;
                              FC = typeC;
                              F = 4;
                          }
                          else if (fileStrS.substr(num, num+5) == "else " ||
                                  fileStrS.substr(num, num+5) == "case " ||
                                  fileStrS.substr(num, num+5) == "elif ") {
                              charC = ifC;
                              FC = ifC;
                              F = 4;
                          }
                          else if (fileStrS.substr(num, num+6) == "while ") {
                              charC = reservC;
                              FC = reservC;
                              F = 5;
                          }
                          else if (fileStrS.substr(num, num+7) == "string ") {
                              charC = typeC;
                              FC = typeC;
                              F = 6;
                          }
                          else if (fileStrS.substr(num, num+8) == "#include ") {
                              charC = typeC;
                              FC = typeC;
                              F = 8;
                          }
                          else {
                              charC = textC;
                              F = 0;
                          }
                      }
        }
    }
}

void EditWindow::drawDataLine() {
    int empLines = h - bestLine;
    int numS = 0;
    std::string data ;

//    std::cout << std::endl;

    // ファイルの内容
    for (int i=fileDataC;i<bestLine;i++) {
        data = fileData[i];
        if (cY == i) {
            printf("\x1b[48;5;%dm",backC+1); // 下線
        }
        std::cout << "  "<< i+1 << std::flush;
        numS = 2 + digit(i+1);
        for (int c=0;c<3-digit(i+1);c++) {
            std::cout << " "<< std::flush;
            numS++;
        }

        if (cY==i) {
            if (cX > 0) {
                // カーソルより前の文字たち
                for (int j=0;j<cX;j++) {
                    colorScheme(data, j);
                    std::cout << "\x1b[38;5;" << charC << "m" << data[j] << std::flush;
                }
            }

            // カーソル
            if (data[cX] == 0)
                printf("\x1b[48;5;%dm ",cursC);      /* 反転（背景色と前景色の入れ替え*/
            else
                printf("\x1b[48;5;%dm%c",cursC,  data[cX]);      /* 反転（背景色と前景色の入れ替え） */

            printf("\x1b[48;5;%dm\x1b[38;5;%dm", backC, textC); /* デフォルトに戻す */

//            if (fileData[i].length() > 1) {
                // カーソルより後の文字たち
                for (int j=cX+1;j<w-numS;j++) {
                    if (j > fileData[cY].length()) std::cout << " " << std::flush;
                    else {
                        colorScheme(data, j);
                        std::cout << "\x1b[38;5;" << charC << "m" << data[j] << std::flush;
                    }
                }

            printf("\x1b[48;5;%dm\x1b[38;5;%dm", backC, textC); /* デフォルトに戻す */
            std::cout << std::endl;
        }
        else {
            for (int c=0;c<data.length();c++) {
                colorScheme(data, c);
                std::cout << "\x1b[38;5;" << charC << "m" << data[c] << std::flush;
            }
            for (int c=data.length();c<w-numS;c++) {
                std::cout << " " << std::flush;
            }
            printf("\x1b[48;5;%dm\x1b[38;5;%dm", backC, textC); /* デフォルトに戻す */
            std::cout << std::endl;
        }
       if (i>h+fileDataC) {
            break;
        }
    }
    // 下の余白
    for (int i=0;i<empLines+1;i++) {
        std::cout << "-" << std::flush;
        for (int j=1;j<w;j++) {
            std::cout << " " << std::flush;
        }
        std::cout << std::endl;
    }
}

void EditWindow::drawCommandLine() {
    if (mode==0) {
        std::cout << "\x1b[48;5;" << nomalC << "m" <<  "== Nomel ==" << "\x1b[48;5;" << backC << "m" << std::endl;
    }
    if (mode==2) {
        std::cout << "\x1b[48;5;" << commandC << "m" <<  "==Command==" << "\x1b[48;5;" << backC << "m" << std::endl;
    }
    std::cout << "\033[31m:" << drawCommand << "\033[m" << std::endl;
}

void EditWindow::drawOutCommandLine() {
    std::cout << "\033[34m" << drawOutCommand << "\033[m" << std::flush;
}

void EditWindow::drawWindow() {
    for (int i=0;i<h;i++) {
        std::cout << "\n" << std::endl;
    }
}

