#ifndef CPEOPLE_H
#define CPEOPLE_H

class CPEOPLE {
    int mX, mY;
    bool mState;
public:
    CPEOPLE();
    CPEOPLE(int startX, int startY);
    void Up();
    void Left();
    void Right();
    void Down();
};

#endif