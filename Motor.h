/*
 * Auther: Ryan Cooke
 * Subject: Concordia Eng Games Machine Motor header
 * save date:11/29/2015
 */

const int N_MOTORS = 2;

const int PORT_PWM  = 5;
const int STARBOARD_PWM = 6;


const int PORT_DIR  = 3;// PWM PIN BUT NOT NEEDED TO BE
const int STARBOARD_DIR = 4;

#define MOVE_WHEEL_FWD(SIDE, AMOUNT) do { \
  analogWrite (SIDE ## _PWM, (AMOUNT)); \
  digitalWrite(SIDE ## _DIR, HIGH); \
} while(0)

#define MOVE_WHEEL_BAK(SIDE, AMOUNT) do { \
  analogWrite (SIDE ## _PWM, (AMOUNT)); \
  digitalWrite(SIDE ##_DIR, LOW); \
} while(0)


#define SPIN_PS(AMOUNT) do {  \
  MOVE_WHEEL_BAK(PORT, AMOUNT); \
  MOVE_WHEEL_FWD(STARBOARD, AMOUNT);  \
} while(0)


#define SPIN_SB(AMOUNT) do {  \
  MOVE_WHEEL_FWD(PORT, AMOUNT); \
  MOVE_WHEEL_BAK(STARBOARD, AMOUNT);  \
} while(0)

#define FWD(AMOUNT) do {  \
  MOVE_WHEEL_FWD(PORT, AMOUNT); \
  MOVE_WHEEL_FWD(STARBOARD, AMOUNT);  \
} while(0)

#define BAK(AMOUNT) do {  \
  MOVE_WHEEL_BAK(PORT, AMOUNT); \
  MOVE_WHEEL_BAK(STARBOARD, AMOUNT);  \
} while(0)

#define TURN_PS(AMOUNT) do {  \
  MOVE_WHEEL_FWD(PORT, 0); \
  MOVE_WHEEL_FWD(STARBOARD, AMOUNT);  \
} while(0

#define TURN_SB(AMOUNT) do {  \
  MOVE_WHEEL_FWD(PORT, AMOUNT); \
  MOVE_WHEEL_FWD(STARBOARD, 0); \
} while(0)

