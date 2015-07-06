#ifndef BLOCK_H
#define BLOCK_H
#define X_MAX 10
#define Y_MAX 20
class BlockGame;
class block
{
private:
    int id;
    int type;
    int x;
    int y;
    //int f[4][4];
public:
    block();
    block(int id, int type,int x,int y);
    /*void Check();
    void Down();
    void Up();
    void Left();
    void Right();
    void Sink();
    void Show();*/
    friend class BlockGame;
};

#endif // BLOCK_H
