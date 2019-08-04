// This program requires the bounce2 library 
// https://github.com/thomasfredericks/Bounce2
// http://theamateurmaker.com/the-bounce2-library/
#include <Bounce2.h>

// ***DIO Pins***
#define RedUpperKeySwitchSwitch_up 0
#define RedUpperKeySwitchSwitch_down 1
#define RedUpperElevatorEnable_A 2
#define RedUpperElevatorEnable_B 3
#define RedUpperMoveUp 4
#define RedUpperMoveDown 5
#define RedUpperTopLimit 6
#define RedUpperBottomLimit 7

#define RedLowerKeySwitchSwitch_up 8
#define RedLowerKeySwitchSwitch_down 9
#define RedLowerElevatorEnable_A 10
#define RedLowerElevatorEnable_B 11
#define RedLowerMoveUp 12
#define RedLowerMoveDown 13
#define RedLowerTopLimit 14
#define RedLowerBottomLimit 15

#define BlueUpperKeySwitchSwitch_up 16
#define BlueUpperKeySwitchSwitch_down 17
#define BlueUpperElevatorEnable_A 18
#define BlueUpperElevatorEnable_B 19
#define BlueUpperMoveUp 20
#define BlueUpperMoveDown 21
#define BlueUpperTopLimit 22
#define BlueUpperBottomLimit 23

#define BlueLowerKeySwitchSwitch_up 24
#define BlueLowerKeySwitchSwitch_down 25
#define BlueLowerElevatorEnable_A 26
#define BlueLowerElevatorEnable_B 27
#define BlueLowerMoveUp 28
#define BlueLowerMoveDown 29
#define BlueLowerTopLimit 30
#define BlueLowerBottomLimit 31

#define GameModeInputStart 32
#define GameModeInputReset 33

// ***Configuration***
#define RedAlliance 0
#define BlueAlliance 1
#define UpperLevel 0
#define LowerLevel 1
#define ElevatorMoveUp 0
#define ElevatorMoveDown 1
#define ElevatorStop 2
#define TopLimit 0
#define BottomLimit 1
#define GameModeNone 0
#define GameModeMatch 1
#define GameModeReset 2

#define DebounceMilliseconds 25

Bounce RedUpperKeySwitch_up = Bounce(); 
Bounce RedUpperKeySwitch_down = Bounce(); 
Bounce RedLowerKeySwitch_up = Bounce(); 
Bounce RedLowerKeySwitch_down = Bounce(); 
Bounce BlueUpperKeySwitch_up = Bounce(); 
Bounce BlueUpperKeySwitch_down = Bounce(); 
Bounce BlueLowerKeySwitch_up = Bounce();
Bounce BlueLowerKeySwitch_down = Bounce();

Bounce GameModeStartSwitch = Bounce();
Bounce GameModeResetSwitch = Bounce();

int currentGameMode = GameModeNone;


void setup() {
  pinMode(RedUpperKeySwitchSwitch_up, INPUT_PULLUP);
  pinMode(RedUpperKeySwitchSwitch_down, INPUT_PULLUP);
  pinMode(RedUpperElevatorEnable_A, OUTPUT);
  pinMode(RedUpperElevatorEnable_B, OUTPUT);
  pinMode(RedUpperMoveUp, INPUT);
  pinMode(RedUpperMoveDown, INPUT);
  pinMode(RedUpperTopLimit, INPUT);
  pinMode(RedUpperBottomLimit, INPUT);  

  pinMode(RedLowerKeySwitchSwitch_up, INPUT_PULLUP);
  pinMode(RedLowerKeySwitchSwitch_down, INPUT_PULLUP);
  pinMode(RedLowerElevatorEnable_A, OUTPUT);
  pinMode(RedLowerElevatorEnable_B, OUTPUT);
  pinMode(RedLowerMoveUp, INPUT);
  pinMode(RedLowerMoveDown, INPUT);
  pinMode(RedLowerTopLimit, INPUT);
  pinMode(RedLowerBottomLimit, INPUT);  

  pinMode(BlueUpperKeySwitchSwitch_up, INPUT_PULLUP);
  pinMode(BlueUpperKeySwitchSwitch_down, INPUT_PULLUP);
  pinMode(BlueUpperElevatorEnable_A, OUTPUT);
  pinMode(BlueUpperElevatorEnable_B, OUTPUT);
  pinMode(BlueUpperMoveUp, INPUT);
  pinMode(BlueUpperMoveDown, INPUT);
  pinMode(BlueUpperTopLimit, INPUT);
  pinMode(BlueUpperBottomLimit, INPUT);  

  pinMode(BlueLowerKeySwitchSwitch_up, INPUT_PULLUP);
  pinMode(BlueLowerKeySwitchSwitch_down, INPUT_PULLUP);
  pinMode(BlueLowerElevatorEnable_A, OUTPUT);
  pinMode(BlueLowerElevatorEnable_B, OUTPUT);
  pinMode(BlueLowerMoveUp, INPUT);
  pinMode(BlueLowerMoveDown, INPUT);
  pinMode(BlueLowerTopLimit, INPUT);
  pinMode(BlueLowerBottomLimit, INPUT);

  pinMode(GameModeInputStart, INPUT_PULLUP);
  pinMode(GameModeInputReset, INPUT_PULLUP);

  RedUpperKeySwitch_up.attach(RedUpperKeySwitchSwitch_up);
  RedUpperKeySwitch_up.interval(DebounceMilliseconds);
  RedUpperKeySwitch_down.attach(RedUpperKeySwitchSwitch_down);
  RedUpperKeySwitch_down.interval(DebounceMilliseconds);
  
  
  RedLowerKeySwitch_up.attach(RedLowerKeySwitchSwitch_up);
  RedLowerKeySwitch_up.interval(DebounceMilliseconds);  
  RedLowerKeySwitch_down.attach(RedLowerKeySwitchSwitch_down);
  RedLowerKeySwitch_down.interval(DebounceMilliseconds);  
  
  
  BlueUpperKeySwitch_up.attach(BlueUpperKeySwitchSwitch_up);
  BlueUpperKeySwitch_up.interval(DebounceMilliseconds);
  BlueUpperKeySwitch_down.attach(BlueUpperKeySwitchSwitch_down);
  BlueUpperKeySwitch_down.interval(DebounceMilliseconds);
  
  
  BlueLowerKeySwitch_up.attach(BlueLowerKeySwitchSwitch_up);
  BlueLowerKeySwitch_up.interval(DebounceMilliseconds); 
  BlueLowerKeySwitch_down.attach(BlueLowerKeySwitchSwitch_down);
  BlueLowerKeySwitch_down.interval(DebounceMilliseconds); 
  
  
  GameModeStartSwitch.attach(GameModeInputStart);
  GameModeStartSwitch.interval(DebounceMilliseconds);
  GameModeResetSwitch.attach(GameModeInputReset);
  GameModeResetSwitch.interval(DebounceMilliseconds);
}

void loop() {
  // Updates required by bounce2 libraray
  RedUpperKeySwitch_up.update();
  RedUpperKeySwitch_down.update();
  RedLowerKeySwitch_up.update(); 
  RedLowerKeySwitch_down.update(); 
  BlueUpperKeySwitch_up.update();
  BlueUpperKeySwitch_down.update();
  BlueLowerKeySwitch_up.update();
  BlueLowerKeySwitch_down.update();
  GameModeStartSwitch.update();
  GameModeResetSwitch.update();

  bool startSwitchActive = (GameModeStartSwitch.read() == LOW);
  bool resetSwitchActive = (GameModeResetSwitch.read() == LOW);

  switch(currentGameMode) {
    case GameModeNone:
      if(startSwitchActive){ 
        currentGameMode = GameModeMatch;
      } else if(resetSwitchActive) { 
        currentGameMode = GameModeReset;
      } else {
        StopAllElevator();
      }
      break;
    
    case GameModeMatch:
      if(resetSwitchActive) {
        StopAllElevator(); 
        currentGameMode = GameModeNone;
      } else {
        RunMatch();
      }
      break;
    
    case GameModeReset:
      if(resetSwitchActive) {
        StopAllElevator(); 
        currentGameMode = GameModeNone;
      } else {
        ResetMatch();
      }      
      break;
  }
}

void RunMatch() {
  RunElevators();    
  
  
}


void RunElevators() {
  if(RedUpperKeySwitch_up.read() == LOW) { SetElevatorState(RedAlliance, UpperLevel, ElevatorMoveUp); }
  if(RedUpperKeySwitch_down.read() == LOW) { SetElevatorState(RedAlliance, UpperLevel, ElevatorMoveDown); }
  if(RedLowerKeySwitch_up.read() == LOW) { SetElevatorState(RedAlliance, LowerLevel, ElevatorMoveUp); }
  if(RedLowerKeySwitch_down.read() == LOW) { SetElevatorState(RedAlliance, LowerLevel, ElevatorMoveDown); }
    
  if(BlueUpperKeySwitch_up.read() == LOW) { SetElevatorState(BlueAlliance, UpperLevel, ElevatorMoveUp); }
  if(BlueUpperKeySwitch_down.read() == LOW) { SetElevatorState(BlueAlliance, UpperLevel, ElevatorMoveDown); }
  if(BlueLowerKeySwitch_up.read() == LOW) { SetElevatorState(BlueAlliance, LowerLevel, ElevatorMoveUp); }
  if(BlueLowerKeySwitch_down.read() == LOW) { SetElevatorState(BlueAlliance, LowerLevel, ElevatorMoveDown); }
}


void ResetMatch() {
  HomeAllElevator(TopLimit);
}


void HomeAllElevator(int WhichLimit) {
  bool redUpperDone = HomeElevator(RedAlliance, UpperLevel, WhichLimit);  
  bool redLowerdone = HomeElevator(RedAlliance, LowerLevel, WhichLimit);  

  bool blueUpperDone = HomeElevator(BlueAlliance, UpperLevel, WhichLimit);
  bool blueLowerDone = HomeElevator(BlueAlliance, LowerLevel, WhichLimit);

  if(redUpperDone && redLowerdone && blueUpperDone && blueLowerDone) {
    currentGameMode = GameModeNone;
  }
}


bool HomeElevator(int alliance, int level, int endStop) {
  bool isHome = false;
  int pin;
  int dir;

  if(alliance == RedAlliance) {
    if(level == UpperLevel) {
      if(endStop == TopLimit) {
        pin = RedUpperTopLimit;
      } else {
        pin = RedUpperBottomLimit;
      }
    } else {
      if(endStop == TopLimit) {
        pin = RedLowerTopLimit;
      } else {
        pin = RedLowerBottomLimit;
      }
    }
  } else {
    if(level == UpperLevel) {
      if(endStop == TopLimit) {
        pin = BlueUpperTopLimit;
      } else {
        pin = BlueUpperBottomLimit;
      }
    } else {
      if(endStop == TopLimit) {
        pin = BlueLowerTopLimit;
      } else {
        pin = BlueLowerBottomLimit;
      }
    }

    if(endStop == TopLimit) {
      dir = ElevatorMoveUp;
    } else {
      dir = ElevatorMoveDown;
    }
    
    int val = digitalRead(pin);

    if(val == LOW) {
      SetElevatorState(alliance, level, dir);
      return false;
    } else {
      SetElevatorState(alliance, level, ElevatorStop);
      return true;
    }
  }
}


void SetElevatorState(int alliance, int level, int dir) {
  int EnablePin_A;
  int EnablePin_B;
  int EnableVal_A;
  int EnableVal_B;
  
  if(alliance == RedAlliance) {
    if(level == UpperLevel) {
      EnablePin_A = RedUpperElevatorEnable_A;
      EnablePin_B = RedUpperElevatorEnable_B;
    } else {
      EnablePin_A = RedLowerElevatorEnable_A;
      EnablePin_B = RedLowerElevatorEnable_B;
    }
  } else {
    if(level == UpperLevel) {
      EnablePin_A = BlueUpperElevatorEnable_A;
      EnablePin_B = BlueUpperElevatorEnable_B;
    } else {
      EnablePin_A = BlueLowerElevatorEnable_A;
      EnablePin_B = BlueLowerElevatorEnable_B;
    }
  }

  switch(dir) {
    case ElevatorMoveUp:
      EnableVal_A = true;
      EnableVal_B = false;
      break;
    case ElevatorMoveDown:
      EnableVal_A = false;
      EnableVal_B = true;
      break;
    case ElevatorStop:
      EnableVal_A = false;
      EnableVal_B = false;
      break;
  }

  digitalWrite(EnablePin_A, EnableVal_A);
  digitalWrite(EnablePin_B, EnableVal_B);
}


void StopAllElevator() {
  SetElevatorState(RedAlliance, UpperLevel, ElevatorStop);
  SetElevatorState(RedAlliance, LowerLevel, ElevatorStop);
  SetElevatorState(BlueAlliance, UpperLevel, ElevatorStop);
  SetElevatorState(BlueAlliance, LowerLevel, ElevatorStop);
}
