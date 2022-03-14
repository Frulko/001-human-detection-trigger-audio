#ifndef PLAYER_H /* include guards */
#define PLAYER_H

class Player
{
  private: 
    bool fadeStarted = false;
    int volume = 0;
    int maxVolume = 30;
    int currentFadeStep = 0;
    int maxFadeStep = 30 * 2;
    int fadeDirection = 1;
  public: 
    Player();
    void play();
    void fadeIn();
    void fadeOut();
    void tick();
    void stopFade();
};

#endif /* PLAYER_H */