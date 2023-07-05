#include <reg52.h>
#define RldTmr(fr) 65536 - (11059200 / 12) / (fr << 1)
#define FuDian(n) (n << 1) / 3    //附点n分音符的换算
 
typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef unsigned long ULONG;
 
sbit BUZZ = P1^6;
 
UINT code noteFreq[] = {    //中音 1-7 和高音 1-7对应的频率列表
    523, 587, 659, 698, 784, 880, 988,
    1047, 1175, 1319, 1397, 1568, 1760, 1976
};
UINT code tmrRld[] = {      //中音 1-7 和高音 1-7对应的定时器重载值
    RldTmr(523), RldTmr(587), RldTmr(659), RldTmr(698), RldTmr(784), RldTmr(880), RldTmr(988),
    RldTmr(1047), RldTmr(1175), RldTmr(1319), RldTmr(1397), RldTmr(1568), RldTmr(1760), RldTmr(1976),
};
UCHAR code musicNote[] = {      //音名
    1, 2, 3, 1,
    1, 2, 3, 1,
    3, 4, 5,
    3, 4, 5,
    5, 6, 5, 4, 3, 1,
    5, 6, 5, 4, 3, 1,
    1, 5, 1,
    1, 5, 1
};
UCHAR code noteDuration[] = {       //音名对应的时值，4表示4分音符，8表示8分音符，16表示16分音符
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 2,
    4, 4, 2,
   FuDian(8), 16, FuDian(8), 16, 4, 4, 
   FuDian(8), 16, FuDian(8), 16, 4, 4, 
    4, 4, 2,	   
    4, 4, 2
};
bit enable = 1, tmrFlg = 0;
UCHAR T0RH = 0XFF, T0RL = 0X00;
 
void Delay(UINT n);
void PlayMusic(UCHAR speed);    //固定标准为4分音符的速度：例如speed = 108 表示一分钟扫过108个4分音符
 
void main() {
    EA = 1;
    TMOD = 0X01;
    TH0 = T0RH;
    TL0 = T0RL;
    ET0 = 1;
    TR0 = 1;
    while (1) {
        PlayMusic(72);
        Delay(40000u);
    }
}
 
void Delay(UINT n) {
    UINT i;
    for (i = 0; i < n; i++) ;
}
 
void PlayMusic(UCHAR speed) {
    UCHAR i;
    UCHAR idx;
    UINT cnt = 0;
    UINT durationCnt = 0;	//当前音符的时值对应的定时器计数
    UINT soundCnt = 0;		//当前音符的发声时值对应的计数值
    for (i = 0; i < sizeof (musicNote); ) {
        while (!tmrFlg) ;
        tmrFlg = 0;
        if (cnt == 0) {
            idx = musicNote[i] - 1;
            T0RH = tmrRld[idx] >> 8;
            T0RL = tmrRld[idx];
            durationCnt = (ULONG)240 * (ULONG)noteFreq[idx] / ((ULONG)noteDuration[i] * (ULONG)speed);
            soundCnt = durationCnt - (durationCnt >> 2);	//当前音符时值的前3/4发声，后1/4静音
            enable = 1;
            cnt++;
        }
        else {
            if (cnt == durationCnt) {
                cnt = 0;
                i++;
            }
            else {
                cnt++;
                if (cnt == soundCnt) {
                    enable = 0;
                }
            }
        }
    }
}
 
void InterruptTmr0() interrupt 1 {
    TH0 = T0RH;
    TL0 = T0RL;
    tmrFlg = 1;
    if (enable)
        BUZZ = ~BUZZ;
    else
        BUZZ = 1;
}