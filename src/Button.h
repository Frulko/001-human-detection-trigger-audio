#ifndef BUTTON_H /* include guards */
#define BUTTON_H

class Button
{
  private:
    int pin;
  public: 
    Button(int aPin);
    void debug();
};

#endif /* BUTTON_H */