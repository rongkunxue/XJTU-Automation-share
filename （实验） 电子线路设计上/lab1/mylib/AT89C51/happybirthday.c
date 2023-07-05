#include <reg51.h>
sbit K0=P1^0;
sbit SOND=P1^7;
unsigned char i,j;
unsigned char code  th[22]={
  0,196,202,208,211,216,220,224,226,229,232,233,236,238,240,241,242,244,244,246,247,248};
unsigned char code  tl[22]={
  0,12,27,21,7,4,16,12,4,12,9,20,2,8,6,2,22,5,26,1,4,3};
unsigned char code  s[26]={
  12,12,13,12,15,14,12,12,13,12,16,15,12,12,19,17,15,14,13,0,18,18,17,15,16,15};
unsigned char code  L[26]={
  4,4,8,8,8,16,4,4,8,8,8,16,4,4,8,8,8,8,16,8,4,4,8,8,8,16};
void main(){
  unsigned int  t;
  TMOD =0x10;
  TH1 =0x3c;TL1=0xb0;
  IP =0x02;
  IE =0x8a;
  while(1){
    while(K0==1);
	  while(K0==0);
	  for(i=0;i<26;i++){
	  if(s[i]==0) {SOND=0;
	    TR0=0;}
	  else  {TH0=th[s[i]];
	    TL0=tl[s[i]];
		TR0=1;}
	  j=L[i];TR1=1;
	  while(TR1==1);
	  TR0=0;
	  SOND=0;
	  for(t=0;t<2000;t++);}}}
void t0()  interrupt 1{
  SOND=~SOND;
  TH0=th[s[i]];TL0=tl[s[i]];}
void t1()  interrupt 3{
  TH1=0x3c;TL1=0xb0;
  if((j--)==0) TR1=0;}