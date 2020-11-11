#include "Process.h"

Process::Process() {
    pepe.resize(128);
    pepeMoveLeft.resize(128);
    pepeMoveRight.resize(128);
    a = to_string(score);
    t1.loadFromFile("background.png");
    t2.loadFromFile("platform.png");
    t3.loadFromFile("platform1.png");
    for (int i = 1; i <= 127; i++) {
        pepe[i].loadFromFile("animation/" + to_string(i) + ".png");
    }
    sBackgorund.setTexture(t1);
    sPlat.setTexture(t2);
    sPlat1.setTexture(t3);
    for (int i = 1; i <= 64; i++) {
        pepeMoveRight[i].setTexture(pepe[i]);
    }
    for (int i = 65; i <= 127; i++) {
        pepeMoveLeft [i - 64] .setTexture(pepe[i]);
    }
    if (!font.loadFromFile("FFF_Tusj.ttf"))
    {
        //error
    }
    text.setFont(font);
    text.setString(a);
    text.setCharacterSize(50);
    text.setFillColor(Color::Red);
}
void Process::moveRight() {
	x += 2;
}
void Process::moveLeft() {
	x -= 2;
}
void Process::setBegin() {
	x = 250;
	y = 0;
	h = 200;
	dx = 0;
	dy = 0;
}
    
void Process::setPlat() {
    for (int i = 0; i < 20; i++)
    {
        if (i < 15) {
            plat[i].x = rand() % 560;
            plat[i].y = rand() % 740;
        }
        else {
            dead[i].x = rand() % 560;
            dead[i].y = rand() % 740;
        }
    }
}
void Process::movePlat() {
    dy += 0.3;
    y += dy;
    if (y < h) {
        y = h;
        for (int i = 0; i < 20; i++)
        {
           
            if (i < 15) {
                plat[i].y = plat[i].y-dy;
                if (plat[i].y > 800) { plat[i].y = 0; plat[i].x = rand() % 560; }
            }
            else {
                dead[i].y = dead[i].y -dy;
                if (dead[i].y > 800) { dead[i].y = 0; dead[i].x = rand() % 740; }
            }
        }
    }
}
int Process::checkz() {
    for (int i = 0; i < 20; i++) {
        if (i >= 15) {
            if ( x > 600 || x < 0 || y>800) {
                return 0;
            }
        }
    }
    return 1;
}
void Process::posMain() {
    for (int i = 0; i < 20; i++) {
        if (i < 15) {
            if ((x > plat[i].x - 40) && (x < plat[i].x + 60)
                && (y > plat[i].y - 80) && (y < plat[i].y - 60) && dy>0) {
                dy = -14;
                score += 10;
                a = to_string(score);
                text.setString(a);
            }
        }
        else {
            if ((x > dead[i].x - 40) && (x < dead[i].x + 60)
                && (y > dead[i].y - 80) && (y < dead[i].y - 60) && (dy > 0)) {
                x = 1000;
            }
        }
    }
}
void Process::setStringz() {
    score = 0;
    a = to_string(score);
    text.setString(a);
}
void Process::setHScore() {
    if (score > highscore) highscore = score;
    b = to_string(highscore);
}
void Process::setPos() {
    for (int i = 1; i <= 64; i++) {
        pepeMoveRight[i].setPosition(x, y);
    }
    for (int i = 65; i <= 127; i++) {
        pepeMoveLeft[i - 64].setPosition(x, y);
    }
}
void Process::nextpepeRight() {
    countRight++;
}
void Process::nextpepeLeft() {
    countLeft++;
}
void Process::draw(RenderWindow& app) {
    app.draw(sBackgorund);
    for (int i = 0; i < 20; i++)
    {
        if (i < 15) {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
        }
        else {
            sPlat1.setPosition(dead[i].x, dead[i].y);
            app.draw(sPlat1);
        }
    }
}

void Process::setpepe() {
    if (countRight > 64) {
        countRight = 1;
    }
    if (countLeft > 62) {
        countLeft = 1;
    }
}
void Process::draw1(RenderWindow& app) {
    if(countRight>0 && countRight <=64) app.draw(pepeMoveRight[countRight]);
}
void Process::draw2(RenderWindow& app) {
    if (countLeft > 0 && countLeft <= 62) app.draw(pepeMoveLeft[countLeft]);
}
void Process::drawScore(RenderWindow& app) {
    app.draw(text);
}
int Process::score = 0;
int Process::highscore = 0;
int Process::countRight = 1;
int Process::countLeft = 1;
