#include "Main.hpp"

std::string tmp1, tmp2, tmp3,tmp4, tmp5;

int digit(int n) {
    int c = 0;
    while (1) {
        if (n < 10) break;
        n /= 10;
        c++;
    }
    return c+1;

}

void EditWindow::colorScheme() {
    std::smatch m;
    if (std::isdigit(fileChar[0]))
        charC = numC;
    else {
        switch (fileChar[0]) {
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
            default :
                charC = textC;
                break;
        }
    }
}

void EditWindow::drawDataLine() {
    int empLines = h - (size(fileData));
    int numS = 0;
    // = textC;
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
            for (int i=0;i<cX;i++) {
                fileChar = data[i];
                colorScheme();
                printf("\x1b[38;5;%dm%c", charC, data[i]);
            }
        }
        if (cY==i) {

            // カーソル
            if (data[cX] == 0)
                printf("\x1b[48;5;%dm ",cursC);      /* 反転（背景色と前景色の入れ替え*/
            else
                printf("\x1b[48;5;%dm%c",cursC,  fileData[i][cX]);      /* 反転（背景色と前景色の入れ替え） */

            printf("\x1b[48;5;%dm\x1b[38;5;%dm", backC, textC); /* デフォルトに戻す */

            // カーソルより後の文字たち
            for (int i=cX+1;i<w-numS;i++) {
                if (i > fileData[cY].length()) std::cout << " " << std::flush;
                else {
                    fileChar = data[i];
                    colorScheme();
                    printf("\x1b[38;5;%dm%c", charC, data[i]);
                }
            }

            printf("\x1b[48;5;%dm\x1b[38;5;%dm", backC, textC); /* デフォルトに戻す */
            std::cout << std::endl;
        }
        else {
            for (int c=0;c<data.length();c++) {
                    fileChar = data[c];
                    colorScheme();
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
        std::cout << "-" << std::flush;
        for (int j=1;j<w/3;j++) {
            std::cout << "   " << std::flush;
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

