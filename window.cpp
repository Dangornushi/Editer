#include "Main.hpp"

void EditWindow::drawDataLine() {
    int empLines = h - size(fileData);
    int i=0;

    std::cout << std::endl;

    // ファイルの内容
    for (auto data : fileData) {
        if (cY == i) {
                printf("\x1b[4m");
        }
        std::cout << "   " << i+1 << "  " << std::flush;
        if (cY == i && cX > 0) {
            // カーソルより前の文字たち
            for (int i=0;i<cX;i++) {
                std::cout << data[i] << std::flush;
            }
            // カーソル
            if (data[cX] == 0)
                printf("\x1b[7m ");      /* 反転（背景色と前景色の入れ替え） */
            else
                printf("\x1b[7m%c", data[cX]);      /* 反転（背景色と前景色の入れ替え） */
            printf("\x1b[0m");      /* デフォルトに戻す */

            // カーソルより後の文字たち
            for (int i=cX+1;i<data.length()+1;i++) {
                std::cout << data[i] << std::flush;
            }
            std::cout << std::endl;
        }
        else if (cY==i && data.length() > 0) {
            // カーソル
            if (data[cX] == 0)
                printf("\x1b[7m ");      /* 反転（背景色と前景色の入れ替え） */
            else
                printf("\x1b[7m%c", data[cX]);      /* 反転（背景色と前景色の入れ替え） */
            printf("\x1b[0m");      /* デフォルトに戻す */
            // カーソルより後の文字たち
            for (int i=cX+1;i<data.length()+1;i++) {
                std::cout << data[i] << std::flush;
            }
            std::cout << std::endl;
        }
        else if (cY == i) {
            // カーソル
            if (data[cX] == 0)
                printf("\x1b[7m ");      /* 反転（背景色と前景色の入れ替え） */
            else
                printf("\x1b[7m%c", data[cX]);      /* 反転（背景色と前景色の入れ替え） */
            printf("\x1b[0m\n");      /* デフォルトに戻す */
        }
        else {
            std::cout << data << std::endl;
        }
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
