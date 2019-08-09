// This program requires the bounce2 library 
// https://github.com/thomasfredericks/Bounce2
// http://theamateurmaker.com/the-bounce2-library/
#include <Bounce2.h>

// ***DIO Pins***
#define RedUpperKey 2
#define RedUpperElevatorEnable_A 3
#define RedUpperElevatorEnable_B 4
#define RedUpperMoveUp 5
#define RedUpperMoveDown 6
#define RedUpperTopLimit 7
#define RedUpperBottomLimit 8

#define RedLowerKey 9
#define RedLowerElevatorEnable_A 10
#define RedLowerElevatorEnable_B 11
#define RedLowerMoveUp 12
#define RedLowerMoveDown 13
#define RedLowerTopLimit 14
#define RedLowerBottomLimit 15

#define BlueUpperKey 16
#define BlueUpperElevatorEnable_A 17
#define BlueUpperElevatorEnable_B 18
#define BlueUpperMoveUp 19
#define BlueUpperMoveDown 22
#define BlueUpperTopLimit 23
#define BlueUpperBottomLimit 24

#define BlueLowerKey 25
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
#define GameModeStop 0
#define GameModeMatch 1
#define GameModeReset 2

#define DebounceMilliseconds 25


Bounce GameModeStartSwitch = Bounce();
Bounce GameModeResetSwitch = Bounce();

// Game state 
int currentGameMode = GameModeStop;
int lastGameMode = -1;
bool RedUpperKeyActive = false;
bool RedLowerKeyActive = false;
bool BlueUpperKeyActive = false;
bool BlueLowerKeyActive = false;

//static String pinText = "Pin: ";
//static String valueText = "Value: "; 
  
void setup() {
  //Serial.begin(9600);
  //Serial.println("Init");
  
  pinMode(RedUpperKey, INPUT);
  pinMode(RedUpperElevatorEnable_A, OUTPUT);
  pinMode(RedUpperElevatorEnable_B, OUTPUT);
  pinMode(RedUpperMoveUp, INPUT);
  pinMode(RedUpperMoveDown, INPUT);
  pinMode(RedUpperTopLimit, INPUT);
  pinMode(RedUpperBottomLimit, INPUT);  

  pinMode(RedLowerKey, INPUT);
  pinMode(RedLowerElevatorEnable_A, OUTPUT);
  pinMode(RedLowerElevatorEnable_B, OUTPUT);
  pinMode(RedLowerMoveUp, INPUT);
  pinMode(RedLowerMoveDown, INPUT);
  pinMode(RedLowerTopLimit, INPUT);
  pinMode(RedLowerBottomLimit, INPUT);  

  pinMode(BlueUpperKey, INPUT);
  pinMode(BlueUpperElevatorEnable_A, OUTPUT);
  pinMode(BlueUpperElevatorEnable_B, OUTPUT);
  pinMode(BlueUpperMoveUp, INPUT);
  pinMode(BlueUpperMoveDown, INPUT);
  pinMode(BlueUpperTopLimit, INPUT);
  pinMode(BlueUpperBottomLimit, INPUT);  

  pinMode(BlueLowerKey, INPUT);
  pinMode(BlueLowerElevatorEnable_A, OUTPUT);
  pinMode(BlueLowerElevatorEnable_B, OUTPUT);
  pinMode(BlueLowerMoveUp, INPUT);
  pinMode(BlueLowerMoveDown, INPUT);
  pinMode(BlueLowerTopLimit, INPUT);
  pinMode(BlueLowerBottomLimit, INPUT);

  pinMode(GameModeInputStart, INPUT_PULLUP);
  pinMode(GameModeInputReset, INPUT_PULLUP);

  GameModeStartSwitch.attach(GameModeInputStart);
  GameModeStartSwitch.interval(DebounceMilliseconds);
  GameModeResetSwitch.attach(GameModeInputReset);
  GameModeResetSwitch.interval(DebounceMilliseconds);
}

void loop() {
  // Updates required by bounce2 library
  GameModeStartSwitch.update();
  GameModeResetSwitch.update();

  bool startSwitchActive = GameModeStartSwitch.fell();
  bool resetSwitchActive = GameModeResetSwitch.fell();

  switch(currentGameMode) {
    case GameModeStop:
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
        currentGameMode = GameModeStop;
      } else {
        RunMatch();
      }
      break;
    
    case GameModeReset:
      if(resetSwitchActive) {
        StopAllElevator(); 
        currentGameMode = GameModeStop;
      } else {
        ResetMatch();
      }      
      break;
  }

  UpdateGameDisplay();
}

void RunMatch() {
  UpdateGameState();



  RunElevators();    
}


void UpdateGameState() {
  RedUpperKeyActive = digitalRead(RedUpperKey) == HIGH;
  RedLowerKeyActive = digitalRead(RedLowerKey) == HIGH;
  BlueUpperKeyActive = digitalRead(BlueUpperKey) == HIGH;
  BlueLowerKeyActive = digitalRead(BlueLowerKey) == HIGH;  
}



void RunElevators() {
  // Red upper
  if(RedUpperKeyActive && digitalRead(RedUpperMoveUp) == HIGH) { 
    SetElevatorState(RedAlliance, UpperLevel, ElevatorMoveUp); 
  } else {
    SetElevatorState(RedAlliance, UpperLevel, ElevatorStop);
  }
 
  if(RedUpperKeyActive && digitalRead(RedUpperMoveDown) == HIGH) { 
    SetElevatorState(RedAlliance, UpperLevel, ElevatorMoveDown); 
  } else {
    SetElevatorState(RedAlliance, UpperLevel, ElevatorStop);
  }

  // Red lower
  if(RedLowerKeyActive && digitalRead(RedLowerMoveUp) == HIGH) { 
    SetElevatorState(RedAlliance, LowerLevel, ElevatorMoveUp); 
  } else {
    SetElevatorState(RedAlliance, LowerLevel, ElevatorStop);
  }
 
  if(RedLowerKeyActive && digitalRead(RedLowerMoveDown) == HIGH) { 
    SetElevatorState(RedAlliance, LowerLevel, ElevatorMoveDown); 
  } else {
    SetElevatorState(RedAlliance, LowerLevel, ElevatorStop);
  }

  // Blue upper
  if(BlueUpperKeyActive && digitalRead(BlueUpperMoveUp) == HIGH) { 
    SetElevatorState(BlueAlliance, UpperLevel, ElevatorMoveUp); 
  } else {
    SetElevatorState(BlueAlliance, UpperLevel, ElevatorStop);
  }
 
  if(BlueUpperKeyActive && digitalRead(BlueUpperMoveDown) == HIGH) { 
    SetElevatorState(BlueAlliance, UpperLevel, ElevatorMoveDown); 
  } else {
    SetElevatorState(BlueAlliance, UpperLevel, ElevatorStop);
  }

  // Blue lower
  if(BlueLowerKeyActive && digitalRead(BlueLowerMoveUp) == HIGH) { 
    SetElevatorState(BlueAlliance, LowerLevel, ElevatorMoveUp); 
  } else {
    SetElevatorState(BlueAlliance, LowerLevel, ElevatorStop);
  }
 
  if(BlueLowerKeyActive && digitalRead(BlueLowerMoveDown) == HIGH) { 
    SetElevatorState(BlueAlliance, LowerLevel, ElevatorMoveDown); 
  } else {
    SetElevatorState(BlueAlliance, LowerLevel, ElevatorStop);
  }
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
    currentGameMode = GameModeStop;
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
      EnableVal_A = HIGH;
      EnableVal_B = LOW;
      break;
    case ElevatorMoveDown:
      EnableVal_A = LOW;
      EnableVal_B = HIGH;
      break;
    case ElevatorStop:
      EnableVal_A = LOW;
      EnableVal_B = LOW;
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


void UpdateGameDisplay() {
  if(lastGameMode != currentGameMode) {
    lastGameMode = currentGameMode;
    //Serial.println(GetGameModeDescription());
  }
  
  //currentGameMode;
  //RedUpperKeyActive;
  //RedLowerKeyActive;
  //BlueUpperKeyActive;
  //BlueLowerKeyActive;
}

String GetGameModeDescription() {
  switch(currentGameMode){
    case GameModeStop:
      return F("Stop");
      break;

    case GameModeMatch:
      return F("Match");
      break;

    case GameModeReset:
      return F("Reset");
      break;
  }
}
