#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

class MovingObject : public Sprite {
    vector<Sprite*> parts;
    double vx, vy;
    double ax, ay;
    bool paused;
    void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
        vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
    }
    public:
        MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)                                                       //1st Constructor
            : Sprite() {
                initMO(argvx, argvy, argax, argay, argpaused);
        }
        MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {                              //2nd Constructor
            double angle_rad = angle_deg*PI/180.0;
            double argvx = speed*cos(angle_rad);
            double argvy = -speed*sin(angle_rad);
            initMO(argvx, argvy, argax, argay, argpaused);
        }
        void set_vx(double argvx) { vx = argvx; }                                                                                                       //If we want to change speed or acceleration in between
        void set_vy(double argvy) { vy = argvy; }
        void set_ax(double argax) { ax = argax; }
        void set_ay(double argay) { ay = argay; }
        double getXPos();
        double getYPos();
        void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);              //Reset function declared

        void pause() { paused = true; }                                                                                                                 //Function to pause lasso
        void unpause() { paused = false; }
        bool isPaused() { return paused; }                                                                                                              //Check if lasso is paused

        void addPart(Sprite* p) {
            parts.push_back(p);
        }
        void nextStep(double t);
        void getAttachedTo(MovingObject *m);
};


#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
    if(paused) { return; }
    //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
    //cerr << "vx=" << vx << ",vy=" << vy << endl;
    //cerr << "ax=" << ax << ",ay=" << ay << endl;

    for(size_t i=0; i<parts.size(); i++){
        parts[i]->move(vx*t, vy*t);
    }
    vx += ax*t;                                                                            //Motion described
    vy += ay*t;
}   // End MovingObject::nextStep()

double MovingObject::getXPos() {
    return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
    return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
    for(size_t i=0; i<parts.size(); i++){
        parts[i]->moveTo(argx, argy);
    }
    double angle_rad = angle_deg*PI/180.0;
    double argvx = speed*cos(angle_rad);
    double argvy = -speed*sin(angle_rad);
    vx = argvx;
    vy = argvy;
    ax = argax;
    ay = argay;
    paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
    double xpos = m->getXPos();
    double ypos = m->getYPos();
    for(size_t i=0; i<parts.size(); i++){
        parts[i]->moveTo(xpos, ypos);
    }
    initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h
#ifndef __COIN_H__
#define __COIN_H__



class Coin : public MovingObject {
    double coin_start_x;
    double coin_start_y;
    double release_speed;
    double release_angle_deg;
    double coin_ax;
    double coin_ay;
    double coin_vx;
    double coin_vy;
    bool coin_paused;

  // Moving parts
    Circle coin_circle;                                                                                                                                   //Declaring coin

    public:
        Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {                 //constructor of class coin
        double angle_rad = angle_deg*PI/180.0;
        double argvx = speed*cos(angle_rad);                                                                                             //Declaring vx and vy
        double argvy = -speed*sin(angle_rad);
        release_speed = speed;
        release_angle_deg = angle_deg;
        coin_ax = argax;
        coin_ay = argay;
        initCoin(argvx, argvy, argax, argay, argpaused);                                                                                           //Since downward is +ve                                                                                            //Declaring vx and vy
                                                                                      //Putting values in vx, vy
  }//End of Constructor

        void initCoin(double argvx, double argvy, double argax, double argay, bool argpaused=true);

        void resetCoin();                                                   //to reset all values to initial
        void resetCoin_parabola();                                          //for moving coin in parabola



}; // End class Coin

#endif

class Coin_black : public MovingObject {                                    //Class for black coin
    double coin_start_x;
    double coin_start_y;
    double release_speed;
    double release_angle_deg;
    double coin_ax;
    double coin_ay;
    double coin_vx;
    double coin_vy;
    bool coin_paused;
    // Moving parts
    Circle coin_black_circle;                                                                                                          //Declaring black coin

    public:
    Coin_black(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {        //COnstructor of class Coin_black
        double angle_rad = angle_deg*PI/180.0;
        double argvx = speed*cos(angle_rad);                                                                                             //Declaring vx and vy
        double argvy = -speed*sin(angle_rad);
        release_speed = speed;
        release_angle_deg = angle_deg;
        coin_ax = argax;
        coin_ay = argay;
        initCoin_black(argvx, argvy, argax, argay, argpaused);
  }//Constructor ends

        void initCoin_black(double argvx, double argvy, double argax, double argay, bool argpaused=true);
        void resetCoin_black();

};//Ends class Coin_black

class Bomb : public MovingObject {                                    //Class for bomb
    double bomb_start_x;
    double bomb_start_y;
    double release_speed;
    double release_angle_deg;
    double bomb_ax;
    double bomb_ay;
    double bomb_vx;
    double bomb_vy;
    bool bomb_paused;
    // Moving parts
    Circle bomb_circle;                                                                                                          //Declaring bomb

    public:
    Bomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {        //COnstructor of class Bomb
        double angle_rad = angle_deg*PI/180.0;
        double argvx = speed*cos(angle_rad);                                                                                             //Declaring vx and vy
        double argvy = -speed*sin(angle_rad);
        release_speed = speed;
        release_angle_deg = angle_deg;
        bomb_ax = argax;
        bomb_ay = argay;
        initBomb(argvx, argvy, argax, argay, argpaused);
  }//Constructor ends

        void initBomb(double argvx, double argvy, double argax, double argay, bool argpaused=true);
        void resetBomb();
};

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90
#define COIN_ANGLE_DEG_PARABOLA 105
#define COIN_ANGLE_DEG_PARABOLA_FRONT 75

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5

#define TARGET 3

class Lasso : public MovingObject {
    double lasso_start_x;
    double lasso_start_y;
    double release_speed;
    double release_angle_deg;
    double lasso_ax;
    double lasso_ay;
    int level=1;                                                                   //declaring the level
    bool level_change = false;
    int failed_attempt = 0;

    // Moving parts
    Circle lasso_circle;
    Circle lasso_loop;

    // Non-moving parts
    Line lasso_line;                                                               //Rope
    Line lasso_band;

    // State info
    bool lasso_looped;
    Coin *the_coin;                                                                //pointers of class Coin
    Coin *the_coin2;
    Coin_black *the_coin_b;                                                        //A pointer of class Coin_black
    Bomb *the_bomb;                                                                 //A pointer for class Bomb
    int num_coins;                                                                 //for counting number of coins

    void initLasso();
    public:
        Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
        release_speed = speed;                                                                                                          //Constructor declared
        release_angle_deg = angle_deg;
        lasso_ax = argax;
        lasso_ay = argay;
        initLasso();
    } //End constructor

    void draw_lasso_band();
      void yank();
      void loopit();
      void addAngle(double angle_deg);
      void addSpeed(double speed);

      void nextStep(double t);
      void check_for_coin(Coin *coin);
      void check_for_coin2(Coin *coin2);
      void check_for_coin_b(Coin_black *coin_b);
      void check_for_bomb(Bomb *bomb);
      int getNumCoins() { return num_coins; }
      void reset_coin_num(){ num_coins=0; }

      int getLevel();
      void changeLevel();
      void applyLevel(int);
      bool get_level_change(){ return level_change; }                                                                                            //to check whether level changes

      int get_failed_attempts(){ return failed_attempt; }                                                                                                 //gives number of continuous failed attempts
}; // End class Lasso


void Coin_black::initCoin_black(double argvx, double argvy, double argax, double argay, bool argpaused) {

      coin_start_x = (PLAY_X_START+WINDOW_X)/2 + 100;                                                                              //position of black coin
      coin_start_y = PLAY_Y_HEIGHT;
      coin_black_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);                                                             //Coin_black_circle - the black coin
      coin_black_circle.setColor(COLOR("black"));
      coin_black_circle.setFill(true);
      addPart(&coin_black_circle);
      coin_vx=argvx;
      coin_vy=argvy;
      coin_ax=argax;
      coin_ay=argay;
      coin_paused=argpaused;
} //End Coin_black::initCoin_black()

void Coin_black::resetCoin_black() {

      double coin_speed = COIN_SPEED;
      double coin_angle_deg_parabola = COIN_ANGLE_DEG_PARABOLA;
      coin_ax = 0;
      coin_ay = COIN_G;
      bool paused = true, rtheta = true;
      reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg_parabola, coin_ax, coin_ay, paused, rtheta);
}//resets coin_black back to original position

void Bomb::resetBomb() {

      double bomb_speed = COIN_SPEED;
      double bomb_angle_deg_parabola = COIN_ANGLE_DEG_PARABOLA_FRONT;
      bomb_ax = 0;
      bomb_ay = COIN_G;
      bool paused = true, rtheta = true;
      reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg_parabola, bomb_ax, bomb_ay, paused, rtheta);
}

void Bomb::initBomb(double argvx, double argvy, double argax, double argay, bool argpaused) {

      bomb_start_x = (PLAY_X_START+WINDOW_X)/2 - 100;                                                                              //position of bomb
      bomb_start_y = PLAY_Y_HEIGHT;
      bomb_circle.reset(bomb_start_x, bomb_start_y, COIN_SIZE);                                                             //bomb_circle - the bomb
      bomb_circle.setColor(COLOR("red"));
      bomb_circle.setFill(true);
      addPart(&bomb_circle);
      bomb_vx=argvx;
      bomb_vy=argvy;
      bomb_ax=argax;
      bomb_ay=argay;
      bomb_paused=argpaused;
}

void Lasso::changeLevel(){
    if(getNumCoins()==TARGET){
        level++;
        reset_coin_num();
        level_change = true;
    }
    if(level >= 5){
        cout<<"Congratulations! you won the game";
        exit(0);
    }
}//for going to next level

int Lasso::getLevel(){ return level; }

#endif

//coin.h

void Coin::initCoin(double argvx, double argvy, double argax, double argay, bool argpaused) {

    coin_start_x = (PLAY_X_START+WINDOW_X)/2;                               //position of golden coin
    coin_start_y = PLAY_Y_HEIGHT;
    coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
    coin_circle.setColor(COLOR("yellow"));
    coin_circle.setFill(true);
    addPart(&coin_circle);
    coin_vx=argvx;
    coin_vy=argvy;
    coin_ax=argax;
    coin_ay=argay;
    coin_paused=argpaused;
} //End Coin::initCoin()

void Coin::resetCoin() {
                                                                                                         //Resets coin
      double coin_speed = COIN_SPEED;
      double coin_angle_deg = COIN_ANGLE_DEG;
      coin_ax = 0;
      coin_ay = COIN_G;
      bool paused = true, rtheta = true;
      reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
} //End Coin::resetCoin()

void Coin::resetCoin_parabola() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg_parabola = COIN_ANGLE_DEG_PARABOLA_FRONT;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg_parabola, coin_ax, coin_ay, paused, rtheta);
}//for coin moving in parabola

//lasso.cpp

void Lasso::draw_lasso_band() {                                                                                                     //Line controlling motion
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {

      lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);                                                                                    //Initial position of lasso
      lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
      lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);                                                                     //Outer red circle
      lasso_circle.setColor(COLOR("red"));
      lasso_circle.setFill(true);
      lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);                                                                     //Inner circle
      lasso_loop.setColor(COLOR("green"));
      lasso_loop.setFill(true);
      addPart(&lasso_circle);
      addPart(&lasso_loop);
      lasso_looped = false;

      the_coin = NULL;
      the_coin2 = NULL;
      the_coin_b=NULL;
      the_bomb = NULL;                                                                                                          //setting pointers storing coin details to NULL
      num_coins = 0;

      lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);                                                     //Rope
      lasso_line.setColor(COLOR("green"));

      lasso_band.setColor(COLOR("blue"));                                                                                         //Behind line for controlling start
      draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
      bool paused = true, rtheta = true;
      reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
      lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
      lasso_loop.setFill(true);
      lasso_looped = false;

      if(the_coin != NULL) {
        num_coins++;
        the_coin->resetCoin();
      }//for straight moving coin
      if(the_coin2 !=NULL){
        num_coins++;
        the_coin2->resetCoin_parabola();
      }//for coin in parabola

      if(the_coin_b !=NULL){                                                         //when you catch black coin
        num_coins--;
        the_coin_b->resetCoin_black();
      }//for black coin

      if(the_bomb !=NULL){                                                          //when you catch bomb
        cout<<"!! Bomb blast !!\n";
        cout<<"You lost";
        exit(0);
      }

      if(the_coin ==NULL && the_coin2 == NULL && the_coin_b == NULL){
        failed_attempt++;
      }                                                                                             //to count failed attempts
      else{
        failed_attempt = 0;
      }
      the_coin = NULL;
      the_coin2 = NULL;
      the_coin_b=NULL;

} // End Lasso::yank()

void Lasso::loopit() {

  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;

} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {

  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr) {         //for straight moving golden coin
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()

void Lasso::check_for_coin_b(Coin_black *coinPtr_b) {       //for black coin
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x_b = coinPtr_b->getXPos();
  double coin_y_b = coinPtr_b->getYPos();
  double xdiff_b = (lasso_x - coin_x_b);
  double ydiff_b = (lasso_y - coin_y_b);
  double distance_b = sqrt((xdiff_b*xdiff_b)+(ydiff_b*ydiff_b));
  if(distance_b <= LASSO_RADIUS) {
    the_coin_b = coinPtr_b;
    the_coin_b->getAttachedTo(this);
  }
} //end Lasso::check_for_coin_b()

void Lasso::check_for_coin2(Coin *coinPtr2) {               //for golden coin in parabola
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x2 = coinPtr2->getXPos();
  double coin_y2 = coinPtr2->getYPos();
  double xdiff2 = (lasso_x - coin_x2);
  double ydiff2 = (lasso_y - coin_y2);
  double distance2 = sqrt((xdiff2*xdiff2)+(ydiff2*ydiff2));
  if(distance2 <= LASSO_RADIUS) {
    the_coin2 = coinPtr2;
    the_coin2->getAttachedTo(this);
  }
} //End Lasso::check_for_coin2()

void Lasso::check_for_bomb(Bomb *bombPtr) {       //for bomb
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bomb_x = bombPtr->getXPos();
  double bomb_y = bombPtr->getYPos();
  double xdiff = (lasso_x - bomb_x);
  double ydiff = (lasso_y - bomb_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_bomb = bombPtr;
    the_bomb->getAttachedTo(this);
  }
} //End Lasso::check_for_bomb()

main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;


  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);


  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);                                                   //Drawing 2 blue lines
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");                                                                                 //Printing Cmd
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);

  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());                                              //Printing Coins and numbers
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

  char LevelStr[256];                                                                                   //Printing level
  sprintf(LevelStr, "Level: %d", lasso.getLevel());
  Text displayLevel(PLAY_X_START+50, PLAY_Y_HEIGHT+80, LevelStr);

  char contFailedAttempts[256];                                                                         //printing number of failed attempts
  sprintf(contFailedAttempts, "Continuous failed Attempts: %d", lasso.get_failed_attempts());
  Text failedAttempts(PLAY_X_START+500, PLAY_Y_HEIGHT+80, contFailedAttempts);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_angle_deg_parabola = COIN_ANGLE_DEG_PARABOLA;
  double coin_angle_deg_parabola_front = COIN_ANGLE_DEG_PARABOLA_FRONT;
  double coin_ax = 0;
  double coin_ay = COIN_G;

  double bomb_speed = COIN_SPEED;
  double bomb_angle_deg = COIN_ANGLE_DEG_PARABOLA_FRONT;
  double bomb_ax = 0;
  double bomb_ay = COIN_G;

  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Coin coin2(coin_speed, coin_angle_deg_parabola_front, coin_ax, coin_ay, paused, rtheta);
  Coin_black coin_b(coin_speed, coin_angle_deg_parabola, coin_ax, coin_ay, paused, rtheta);
  Bomb bomb(bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit

  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {

      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);

      switch(c) {
        case 't':                                                                   //triggering
            lasso.unpause();
            break;
        case 'y':                                                                   //yanks lasso and level adjustment
            lasso.yank();
            lasso.changeLevel();
            if(lasso.get_failed_attempts()>=3){
                //exit(0);
                cout<<"Sorry, you lost";
                exit(0);
            }
            break;
        case 'l':
            lasso.loopit();
            lasso.check_for_coin(&coin);
            lasso.check_for_coin2(&coin2);
            lasso.check_for_coin_b(&coin_b);
            lasso.check_for_bomb(&bomb);
            wait(STEP_TIME*5);
            break;
        case '[':
            if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
            break;
        case ']':
            if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
            break;
        case '-':
            if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
            break;
        case '=':
            if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
            break;
        case 'q':
            exit(0);
        default:
            break;
      }
    }

    lasso.nextStep(stepTime);

    switch(lasso.getLevel()){
        case 1:                                                                     //level 1
            coin.nextStep(stepTime);
            if(coin.isPaused()) {
                if((currTime-last_coin_jump_end) >= COIN_GAP) {
                    coin.unpause();
                }
            }
            if(coin.getYPos() > PLAY_Y_HEIGHT) {
                coin.resetCoin();
                last_coin_jump_end = currTime;
            }
            break;
        case 2:                                                                     //level 2
            coin2.nextStep(stepTime);
            if(coin2.isPaused()) {
                if((currTime-last_coin_jump_end) >= COIN_GAP) {
                    coin2.unpause();
                }
            }
            if(coin2.getYPos() > PLAY_Y_HEIGHT) {
                coin2.resetCoin_parabola();
                last_coin_jump_end = currTime;
            }
            break;

        case 3:                                                                     //level 3
            coin2.nextStep(stepTime);
            if(coin2.isPaused()) {
                if((currTime-last_coin_jump_end) >= COIN_GAP) {
                    coin2.unpause();
                }
            }
            if(coin2.getYPos() > PLAY_Y_HEIGHT) {
                coin2.resetCoin_parabola();
                last_coin_jump_end = currTime;
            }                                                                   //reset golden coin
            coin_b.nextStep(stepTime);
            if(coin_b.isPaused()) {
                if((currTime-last_coin_jump_end) >= COIN_GAP) {
                    coin_b.unpause();
                }
            }
            if(coin_b.getYPos() > PLAY_Y_HEIGHT) {
                coin_b.resetCoin_black();
                last_coin_jump_end = currTime;
            }                                                                   //reset black coin
            break;
        case 4:                                                                            //level 4
            coin2.nextStep(stepTime);
            if(coin2.isPaused()) {
                if((currTime-last_coin_jump_end) >= COIN_GAP) {
                    coin2.unpause();
                }
            }
            if(coin2.getYPos() > PLAY_Y_HEIGHT) {
                coin2.resetCoin_parabola();
                last_coin_jump_end = currTime;
            }                                               //reset golden coin
            coin_b.nextStep(stepTime);
            if(coin_b.isPaused()) {
                if((currTime-last_coin_jump_end) >= COIN_GAP) {
                    coin_b.unpause();
                }
            }
            if(coin_b.getYPos() > PLAY_Y_HEIGHT) {
                coin_b.resetCoin_black();
                last_coin_jump_end = currTime;
            }                                               //reset black coin
            bomb.nextStep(stepTime);
            if(bomb.isPaused()) {
                if((currTime-last_coin_jump_end) >= COIN_GAP) {
                    bomb.unpause();
                }
            }
            if(bomb.getYPos() > PLAY_Y_HEIGHT) {
                bomb.resetBomb();
                last_coin_jump_end = currTime;
            }       //to reset the bomb
            break;
    }
    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    sprintf(LevelStr, "Level: %d", lasso.getLevel());
    displayLevel.setMessage(LevelStr);

    sprintf(contFailedAttempts, "Continuous failed Attempts: %d", lasso.get_failed_attempts());
    failedAttempts.setMessage(contFailedAttempts);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for(;;)

  wait(3);
} // End main_program


