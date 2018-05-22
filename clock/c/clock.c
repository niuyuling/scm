#include <AT89X51.H>
#define uint unsigned int
#define uchar unsigned char
sbit led1=P1^0;
sbit k1=P1^1;
sbit k2=P1^2;
sbit k3=P1^3;
sbit k4=P1^4;
sbit k5=P1^5;

void xiaoai();
uchar code duan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code wei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
uint miao,fen,xiaoshi,ge,shi,bai,qian,wan,shiwan,t;

void times(uint z)
{
	uint i,j;
	for(i=0; i<z; i++)
		for(j=0; j<121; j++);
}

void xiaoai()
{
	ge=miao%10;
	shi=miao/10;
	bai=fen%10;
	qian=fen/10;
	wan=xiaoshi%10;
	shiwan=xiaoshi/10;

	P0=duan[ge];
	P2=wei[7];
	times(1);
	P2=0xff;

	P0=duan[shi];
	P2=wei[6];
	times(1);
	P2=0xff;

	P0=duan[bai];
	P2=wei[5];
	times(1);
	P2=0xff;

	P0=duan[qian];
	P2=wei[4];
	times(1);
	P2=0xff;

	P0=duan[wan];
	P2=wei[3];
	times(1);
	P2=0xff;

	P0=duan[shiwan];
	P2=wei[2];
	times(1);
	P2=0xff;
}

void main()
{
	EA=1;
	TMOD=0x01;
	ET0=1;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;

while(1)
{
	xiaoai();

	if(k1==0)
		TR0=1;
	else if(k2==0)
			TR0=0;
	else if(k3==0) {
		miao=0;
		fen=0;
		xiaoshi=0;
	}
	else if(TR0==0&&k4==0)
	{
		fen=fen+1;
		while(!k4) {
			xiaoai();
		}
	}
	else if(TR0==0&&k5==0) {
		xiaoshi=xiaoshi+1;
		while(!k5) {
			xiaoai();
		}
	}


	if(t==20){
		t=0;
		miao=miao+1;
	}
	else if(miao==60) {
		miao=0;
		fen=fen+1;
	}
	else if(fen==60) {
		fen=0;
		xiaoshi=xiaoshi+1;
	}
	else if(xiaoshi==24)
		xiaoshi=0;
	
	xiaoai();
}
}

void int0() interrupt 1
{
	t++;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
}