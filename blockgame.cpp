#include "blockgame.h"
#include <iostream>
#include <QPushButton>
#include <QMessageBox>

extern unsigned int g_Blocks[7][4];

BlockGame::BlockGame(QWidget *parent)
    :QWidget(parent)
{
    for (int i = 0; i < X_MAX; i++)
        for (int j = 0; j < Y_MAX; j++)
        {
            QLabel *temp = new QLabel(this);
            temp->setGeometry(i*15,j*15,14,14);
            temp->setStyleSheet("background-color:white");
            m_lablist.append(temp);
            m_workarea[i][j] = 0;
            m_cworkarea[i][j] = 0;
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4;j++)
        {
            QLabel *temp = new QLabel(this);
            temp->setGeometry(i*15+180,j*15,14,14);
            temp->setStyleSheet("background-color:white");
            m_flablist.append(temp);
            m_fworkarea[i][j] = 0;
        }
    score = 0;
    label = new QLabel(this);
    label->setText(QString("<h3><b>Score</b>: %1</h3>").arg(QString::number(score)));
    label->setGeometry(180,100,label->sizeHint().width(),label->sizeHint().height());

    QPushButton *resetbutton = new QPushButton(this);
    QPushButton *exitbutton = new QPushButton(this);
    resetbutton->setText(QString("reset"));
    exitbutton->setText(QString("exit"));
    resetbutton->setGeometry(180,230,resetbutton->sizeHint().width(),resetbutton->sizeHint().height());
    exitbutton->setGeometry(180,280,exitbutton->sizeHint().width(),exitbutton->sizeHint().height());
    resetbutton->setFocusPolicy(Qt::NoFocus);
    exitbutton->setFocusPolicy(Qt::NoFocus);

    connect(exitbutton,SIGNAL(clicked()),this,SLOT(close()));
    connect(resetbutton,SIGNAL(clicked()),this,SLOT(initgame()));

    m_timer = new QTimer();
    m_timer->setInterval(200);
    QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(downBlock()));
    newBlock();
}
void BlockGame::initgame()
{
    for (int i = 0; i < X_MAX; i++)
        for (int j = 0; j < Y_MAX; j++)
        {
            m_workarea[i][j] = 0;
            m_cworkarea[i][j] = 0;
        }
    score = 0;
    label->setText(QString("<h3><b>Score</b>: %1</h3>").arg(QString::number(score)));
    newBlock();
}

void BlockGame::newBlock()
{
    /**/
    nn = fn;
    m_block = new block(nn%7,nn%4,4,0);
    if (!checkok(m_block->id,m_block->type,m_block->x,m_block->y))
    {
        QMessageBox::information(this,"haha","<h3>Game Over</h3>");
        m_timer->stop();
    }
    else
    {
        getnext();
        showblock();
        m_timer->start();
    }
}

void BlockGame::getnext()
{
    QTime t;
    t = QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    fn = qrand();
    int id,type;
    unsigned int fblock;
    id = fn % 7;
    type = fn % 4;
    fblock = g_Blocks[id][type];
    //qDebug() << fblock;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
    {
        if (fblock & 0x0001)
            m_fworkarea[i][j] = 1;
        else
            m_fworkarea[i][j] = 0;
        fblock >>= 1;
    }
    updatefUI();
}


void BlockGame::showblock()
{

    unsigned int temp = g_Blocks[m_block->id][m_block->type];
    for (int i = 0; i < X_MAX; i++)
        for (int j = 0; j < Y_MAX; j++)
            m_workarea[i][j] = m_cworkarea[i][j];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            int x = m_block->x+i;
            int y = m_block->y+j;
            if (temp & 0x0001)
                m_workarea[x][y] = 1;
           temp >>= 1;
        }

    updateUI();
}



void BlockGame::updatefUI()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m_fworkarea[i][j])
                m_flablist.at(i*4+j)->setStyleSheet("background-color:black");
            else
                m_flablist.at(i*4+j)->setStyleSheet("background-color:white");
}

void BlockGame::updateUI()
{
    for (int i = 0; i < X_MAX; i++)
        for (int j = 0; j < Y_MAX; j++)
            if (m_workarea[i][j])
                m_lablist.at(i*Y_MAX+j)->setStyleSheet("background-color:black");
            else
                m_lablist.at(i*Y_MAX+j)->setStyleSheet("background-color:white");
}


void BlockGame::downBlock()
{
    int type = m_block->type;
    int id = m_block->id;

    if (checkok(id,type,m_block->x,m_block->y+1))
    {

        m_block->y++;
        showblock();
        m_timer->start();
    }
    else
    {
        //qDebug() << m_block->x << ' ' <<m_block->y;
        for (int i = 0; i < X_MAX; i++)     
            for (int j = 0; j < Y_MAX; j++)       
                m_cworkarea[i][j] = m_workarea[i][j];
        checkscore();
        newBlock();
    }

}

bool BlockGame::checkok(int id, int type, int x, int y)
{

    unsigned int temp = g_Blocks[id][type];
    //qDebug() << x <<' ' << y <<' ' <<temp <<' ' << id << ' ' << type;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            int X = x+i;
            int Y = y+j;
            if (temp & 0x0001)
            {
                if ( X < 0 || X >= X_MAX || Y < 0 || Y >= Y_MAX)
                    return false;
                if (m_cworkarea[X][Y] == 1)
                    return false;
            }
            temp >>= 1;
        }
    return true;
}

void BlockGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        if (checkok(m_block->id,m_block->type,m_block->x-1,m_block->y))
        {
            m_block->x--;
            showblock();
        }
    }
    if (event->key() == Qt::Key_Right)
    {
        if (checkok(m_block->id,m_block->type,m_block->x+1,m_block->y))
        {
            m_block->x++;
            showblock();
        }
    }
    if (event->key() == Qt::Key_Space)
    {
        if (checkok(m_block->id,(m_block->type+1)%4,m_block->x,m_block->y))
        {
            m_block->type = (m_block->type+1)%4;
            showblock();
        }
    }
    if (event->key() == Qt::Key_Down)
    {
        while (checkok(m_block->id,m_block->type,m_block->x,m_block->y+1))
        {
            m_block->y++;
        }
        showblock();
    }
    if (event->key() == Qt::Key_Up)
    {
        if (m_timer->isActive()) m_timer->stop();
            else m_timer->start();
    }
}

void BlockGame::checkscore()
{
    int temp[Y_MAX] = {0};
    for (int i = Y_MAX-1; i>=0; i--)
    {
        int flag = 1;
        for (int j = 0; j < X_MAX; j++)
        {
            if (m_cworkarea[j][i] == 0)
            {
                flag = 0;
                break;
            }
        }
        if (flag) {
            temp[i] = 1;
            score++;
        }
    }
    label->setText(QString("<h3><b>Score</b>: %1</h3>").arg(QString::number(score)));
    int k = Y_MAX-1;
    for (int i = Y_MAX-1; i>=0; i--)
    {
        if (temp[i]) continue;
        for (int j = 0; j < X_MAX; j++)
            m_cworkarea[j][k] = m_cworkarea[j][i];
        k--;
    }
}
