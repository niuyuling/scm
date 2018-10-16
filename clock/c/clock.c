#include <AT89X51.H>
#define uint unsigned int
#define uchar unsigned char

sbit k1=P1^1;
sbit k2=P1^2;
sbit k3=P1^3;
sbit k4=P1^4;
sbit k5=P1^5;
sbit k6=P1^6;

void display();
uchar code duan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code wei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
uint second, minute, hour, one, ten, hundred, thousand, tthousand, oht, t;

void times(uint z)
{
	uint i,j;
	for(i=0; i<z; i++)
		for(j=0; j<121; j++);
}

void display()
{
	one=second%10;
	ten=second/10;
	hundred=minute%10;
	thousand=minute/10;
	tthousand=hour%10;
	oht=hour/10;

	P0=duan[one];
	P2=wei[7];
	times(1);
	P2=0xff;

	P0=duan[ten];
	P2=wei[6];
	times(1);
	P2=0xff;

	P0=duan[hundred];
	P2=wei[5];
	times(1);
	P2=0xff;

	P0=duan[thousand];
	P2=wei[4];
	times(1);
	P2=0xff;

	P0=duan[tthousand];
	P2=wei[3];
	times(1);
	P2=0xff;

	P0=duan[oht];
	P2=wei[2];
	times(1);
	P2=0xff;
}

void main()
{
	TR0=1;
	EA=1;
	TMOD=0x01;
	ET0=1;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;

	while(1)
	{
		display();

		if(k1==0)
			TR0=1;
		else if(k2==0)
				TR0=0;
		else if(k3==0) {
			second=0;
			minute=0;
			hour=0;
		}
		else if(TR0==0 && k4==0)
		{
			second=second+1;
			while(!k4) {
				display();
			}
		}
		else if(TR0==0 && k5==0) {
			minute=minute+1;
			while(!k5) {
				display();
			}
		}
		else if(TR0==0 && k6==0) {
			hour=hour+1;
			while(!k6) {
				display();
			}
		}


		if(t==20){
			t=0;
			second=second+1;
		}
		else if(second==60) {
			second=0;
			minute=minute+1;
		}
		else if(minute==60) {
			minute=0;
			hour=hour+1;
		}
		else if(hour==24) {
			hour=0;
		}
		
		display();
	}
}

void int0() interrupt 1
{
	t++;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
}