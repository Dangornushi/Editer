#include "Main.hpp"

std::string tmp1, tmp2, tmp3,tmp4, tmp5;
int F = 0;

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
            default : {
                          if (F > 0) {
                              charC = FC;
                              F--;
                          }
                          else if (fileStrS.substr(num, num+4) == "for ") {
                              charC = reservC;
                              FC = reservC;
                              F = 3;
                          }
                          else if (fileStrS.substr(num, num+6) == "while ") {
                              charC = reservC;
                              FC = reservC;
                              F = 5;
                          }
                          else if (fileStrS.substr(num, num+4) == "int ") {
                              charC = typeC;
                              FC = typeC;
                              F = 3;
                          }
                          else if (fileStrS.substr(num, num+5) == "char ") {
                              charC = typeC;
                              FC = typeC;
                              F = 4;
                          }
                          else if (fileStrS.substr(num, num+7) == "string ") {
                              charC = typeC;
                              FC = typeC;
                              F = 6;
                          }
                          else {
                              charC = textC;
                          }
                      }
                      break;
        }
    }
}

void EditWindow::drawDataLine() {
    int empLines = h - size(fileData);
    int numS = 0;
    std::string data ;

    // ファイルの内容
    for (int i=fileDataC;i<size(fileData);i++) {
        data = fileData[i];
        printf("\x1b[48;5;%dm", backC);
        if (cY == i) {
            printf("\x1b[48;5;%dm",backC+1); // 下線
        }
        std::cout << "  "<< i+1 << std::flush;
        numS = 2 + digit(i+1);
        for (int c=0;c<3-digit(i+1);c++) {
            std::cout << " "<< std::flush;
            numS++;
        }

        if (cY == i && cX > 0) {
            // カーソルより前の文字たち
            for (int j=0;j<cX;j++) {
                colorScheme(data, j);
                printf("\x1b[38;5;%dm%c", charC, data[j]);
            }
        }
        if (cY==i) {

            // カーソル
            if (data[cX] == 0)
                printf("\x1b[48;5;%dm ",cursC);      /* 反転（背景色と前景色の入れ替え*/
            else
                printf("\x1b[48;5;%dm%c",cursC,  fileData[i][cX]);      /* 反転（背景色と前景色の入れ替え） */

            printf("\x1b[48;5;%dm\x1b[38;5;%dm", backC, textC); /* デフォルトに戻す */

//            if (fileData[i].length() > 1) {
                // カーソルより後の文字たち
                for (int j=cX+1;j<w-numS;j++) {
                    if (j > fileData[cY].length()) std::cout << " " << std::flush;
                    else {
                        colorScheme(data, j);
                        printf("\x1b[38;5;%dm%c", charC, data[j]);
                    }
                }
 //           }
  //          else {
//                for (int j=numS;j<w-1;j++)
//                    std::cout << " " << std::flush;
//            }

            printf("\x1b[48;5;%dm\x1b[38;5;%dm", backC, textC); /* デフォルトに戻す */
            std::cout << std::endl;
        }
        else {
            for (int c=0;c<data.length();c++) {
                colorScheme(data, c);
                printf("\x1b[38;5;%dm%c", charC, data[c]);
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
        std::cout << "- " << std::flush;
        for (int j=1;j<w/2;j++) {
            std::cout << "  " << std::flush;
        }
        std::cout << std::endl;
    }
}

void EditWindow::drawCommandLine() {
    if (mode==0) {
        printf("\x1b[48;5;%dm",nomalC);
        std::cout << "== Nomel ==" << std::endl;
    }
    printf("\x1b[48;5;%dm",backC);
    std::cout << "\033[31m" << drawCommand << " \033[m " << std::endl;
}

void EditWindow::drawOutCommandLine() {
    std::cout << "\033[34m" << drawOutCommand << " \033[m " << std::flush;
}

void EditWindow::drawWindow() {
    for (int i=0;i<h;i++) {
        std::cout << "\n" << std::endl;
    }
}

