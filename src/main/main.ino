#include "M5Atom.h"

/* ジャイロセンサ */
float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

/* ドットマトリックスLED */
int led_arr[2][5][5][5] = {
  {
    {
      {0, 1, 0, 1, 0},
      {1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1},
      {0, 1, 1, 1, 0},
      {0, 0, 1, 0, 0}
    },
    {
      {3, 0, 0, 0, 3},
      {3, 0, 0, 0, 3},
      {3, 0, 0, 0, 3},
      {3, 3, 0, 3, 3},
      {0, 3, 3, 3, 0}
    },
    {
      {3, 3, 3, 3, 3},
      {0, 0, 3, 0, 0},
      {0, 0, 3, 0, 0},
      {0, 0, 3, 0, 0},
      {0, 0, 3, 0, 0}
    },
    {
      {0, 0, 3, 0, 0},
      {0, 3, 0, 3, 0},
      {3, 0, 0, 0, 3},
      {3, 3, 3, 3, 3},
      {3, 0, 0, 0, 3}
    },
    {
      {0, 0, 5, 0, 0},
      {0, 0, 5, 5, 0},
      {5, 5, 5, 0, 5},
      {5, 5, 5, 0, 0},
      {5, 5, 5, 0, 0}
    }
  },
  {
    {
      {0, 2, 0, 2, 0},
      {2, 2, 2, 2, 2},
      {2, 2, 2, 2, 2},
      {0, 2, 2, 2, 0},
      {0, 0, 2, 0, 0}
    },
    {
      {4, 0, 0, 0, 4},
      {4, 4, 0, 0, 4},
      {4, 0, 4, 0, 4},
      {4, 0, 0, 4, 4},
      {4, 0, 0, 0, 4}
    },
    {
      {0, 0, 4, 0, 0},
      {0, 4, 0, 4, 0},
      {4, 0, 0, 0, 4},
      {4, 4, 4, 4, 4},
      {4, 0, 0, 0, 4}
    },
    {
      {0, 4, 4, 4, 0},
      {4, 0, 0, 0, 4},
      {4, 0, 0, 0, 4},
      {4, 0, 0, 0, 4},
      {0, 4, 4, 4, 0}
    },
    {
      {1, 1, 0, 1, 1},
      {1, 2, 2, 2, 1},
      {0, 1, 0, 1, 0},
      {1, 1, 0, 1, 1},
      {1, 0, 0, 0, 1}
    }
  }
};

int clr_arr[6] = {CRGB::Black, CRGB::Red, CRGB::DeepPink, CRGB::SkyBlue, CRGB::Blue, CRGB::Navy};
int mod_num = 0;
int sts_num = 1;


/* ドットマトリックスLED表示関数 */
void dispLED(int m, int n){
  for(int i = 0; i < 5; i ++){
    for(int j = 0; j < 5; j ++){
      M5.dis.drawpix(i*5 + j, clr_arr[led_arr[m][n][i][j]]);
    }
  }
}


void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  dispLED(0, 0);
}

void loop() {
  if (M5.Btn.wasPressed()){
    mod_num = 1 - mod_num;
    sts_num = 1;
    dispLED(mod_num, 0);
  }
  
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  if (gyroZ <= -250){
    switch (sts_num){
    case 0:
      dispLED(mod_num, 0);
      break;
    case 1:
      dispLED(mod_num, 1);
      break;
    case 2:
      dispLED(mod_num, 2);
      break;
    case 3:
      dispLED(mod_num, 3);
      break;
    case 4:
      dispLED(mod_num, 4);
      break;
    case 5:
      dispLED(mod_num, 1);
      break;
    case 6:
      dispLED(mod_num, 2);
      break;
    case 7:
      dispLED(mod_num, 3);
      break;
    }
    sts_num ++;
    if (sts_num >= 8){
       sts_num = 0;
    }
    delay(100);
  }
  
  delay(10);
  M5.update();
}
