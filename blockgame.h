#ifndef BLOCKGAME_H
#define BLOCKGAME_H
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QTimer>
#include <QTime>
#include <QDebug>

#include "block.h"
class QWidget;
class BlockGame : public QWidget
{
    Q_OBJECT
public:
    explicit BlockGame(QWidget *parent = 0);
    void newBlock();  //生成方块
    void getnext();   //随机取得下一个方块，显示在副窗口
    void updatefUI(); //更新副窗口显示
    void updateUI(); //更新主窗口显示
    void showblock();//显示方块
    bool checkok(int id,int type,int x,int y); //检查是否违规
    void checkscore(); //检查是否有得分
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void downBlock();
    void initgame();
private:
    QList <QLabel *> m_lablist;
    QList <QLabel *> m_flablist;
    QTimer *m_timer;
    block *m_block;
    QLabel *label;
    int m_workarea[X_MAX][Y_MAX];
    int m_cworkarea[X_MAX][Y_MAX];
    int m_fworkarea[4][4];
    int nn;
    int fn;
    int score;

};

#endif // BLOCKGAME_H
