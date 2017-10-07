//#define DEBUG
#ifdef DEBUG
#define DEBUG_LOG(str) Serial.println(String()+str);
#define DEBUG_SETUP() Serial.begin(115200);
#else
#define DEBUG_LOG(str)
#define DEBUG_SETUP()
#endif
