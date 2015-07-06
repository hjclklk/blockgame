/*
 * 1 对于俄罗斯方块游戏的布局
 *       QLabel，Qlist
 * 2 对于方块的旋转等操作
 *      利用二进制存储
 *      QTimer 定时下移
 *
 * 3 对于游戏过程的判断，下一步是否合理
 *
    主要是对于QT gui 编程的熟悉
                2015.3.22
                hjclklk
*/
#include "mainwindow.h"
#include <QApplication>
#include "blockgame.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlockGame blockgame;
    blockgame.show();
    return a.exec();
}
