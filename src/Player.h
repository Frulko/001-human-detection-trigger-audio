#ifndef PLAYER_H /* include guards */
#define PLAYER_H

#include <DFPlayerMini_Fast.h>

class Player
{
  private: 
    bool fadeStarted = false;
    int volume = 0;
    int maxVolume = 30;
    int currentFadeStep = 0;
    int maxFadeStep = 30;
    int fadeDirection = 1;
    bool autoplay = true;
    DFPlayerMini_Fast dfPlayer;
  public: 
    Player();
    void init();
    void play();
    void fadeIn();
    void fadeOut();
    void tick();
    void stopFade();
    bool isFaded();
};

#endif /* PLAYER_H */