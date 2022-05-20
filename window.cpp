#include "Main.hpp"

void EditWindow::drawDataLine() {
    int empLines = h - (lineNum+cY);
    int i=0;

    std::cout << std::endl;

    // ファイルの内容
    for (auto data : fileData) {
        if (cY == i) {
                printf("\x1b[7m");      /* 反転（背景色と前景色の入れ替え） */
        }
        std::cout << "   " << i+1 << "  " << data << std::endl;
        printf("\x1b[0m");      /* デフォルトに戻す */
        i++;
        if (i>h) {
            break;
        }
    }
    // 下の余白
    for (int i=0;i<empLines;i++)
        std::cout << std::endl;
}

void EditWindow::drawCommandLine() {
    std::cout << "\033[31m" << drawCommand << " \033[m " << std::flush;
}

void EditWindow::drawOutCommandLine() {
    std::cout << "\033[34m" << drawOutCommand << " \033[m " << std::endl;
}

void EditWindow::drawWindow() {
    for (int i=0;i<h;i++) {
        std::cout << "\n" << std::endl;
    }
}
