/*
         written by dfdfdfff
*/



#include "graphics.h"                  // ��Ҫ���õ�ͼ�ο�
#include <stdio.h>                     // ����Ҫ���ַ�������
#include <stdlib.h>
#include <math.h>                      // ��ѧ����
#define Number 50                      // ���򻺳����Ĵ�С ������ �ٴ�Ҫ���� 
#define Ro 12                          // ���ڼ�����İ뾶���ܶ�ϵ�� ��ʽΪr=Ro*log(m) 



struct ball{
	int color;                         // С�����ɫ 
	float m;                           // С�������
	float r;                           // С��İ뾶 �������й� 
	float x;                           // ������ 
	float y;                           // ������ 
	float vx;                          // x���ٶ� 
	float vy;                          // y���ٶ� 
	float ax;                          // x����ٶ� 
	float ay;                          // y����ٶ� 
} *a[Number];                   // С��Ľṹ ͬʱ����һ������������ָ������ ����Ϸ������ 

struct boardaa{                        //
	float m;
	int y;
	float v;
	float a;
	color_t color;
	int able;
} boarda={3,360,0,0,EGERGB(0xff,0x80,0x26),1};  // a��Ľṹ
 
struct boardbb{                        //
	float m;
	int y;
	color_t color;
	int able;
} boardb={3,360,EGERGB(0x4f,0xff,0xf9),1};      // b��Ľṹ


                                       // ȫ�ֱ�����
int gamemode=0;                        // ���ڴ������ģʽ
int gravity=1;                         // ���������С
int timer=20;                          // �������Ļ�ʱ
float scorea=0;                        // a�ĵ÷� 
float scoreb=0;                        // b�ĵ÷� 


                                       // ������ԭ������
void howtoplay();                      // ȫ����ʾ��Ϸ�Ĳ�������
void drawTriangle(int *a);             // ��������ָ��ͼ��
void up(int *a);                       // ��ʼ�����up��Ӧ
void down(int *a);                     // ��ʼ�����down��Ӧ
void enter(int *a);                    // ��ʼ�����enter��Ӧ
void esc(int *a);					   // ��ʼ����esc����Ӧ			    
void draw_1_all(int *a);               // ������ʼ����һ֡����Ԫ�� 
void setfirstfont();                   // ���ó�ʼ������������ɫ 
void mystart();                        // ��ʼ����������� 
void drawYellowords();                 // ��ӡgamemode��gravity 
void startgame();                      // ��ʽ��ʼ��Ϸ 
void drawfps();                        // ���ϽǴ�ӡ֡��
void ifcollide();                      // ��ײ���
void draw_balls();                     // ��������С��
void draw_boards();                    // ������������
void draw_background();                // ���Ʊ���
void ball_createnewa(float x,float y,float vx,float vy,float m,int color);                 // ����һ��balla����
void ball_createnewb(float x,float y,float vx,float vy,float m,int color);                 // ����һ��balla����
void ball_create(float x1,float x2,float y1,float y2,float vx1,float vx2,float vy1,float vy2,float m1,float m2,int color);
void calculateboarda();                // �����a��λ��
void calculateboardb();                // �����b��λ��
void ball_go();                        // С����ƶ� 
void createa();                        // ����a
void showscoreb();                     // չʾab�ĵ÷�
void countgravity();                   // ��������

void showscoreab(){
	setfillcolor(BLACK);
	bar(120,40,160,680);
	bar(1120,40,1160,680);
	setfillcolor(EGERGB(0x4b,0xff,0xf9));
	bar(120,680-640*scoreb/200,160,680);
	setfillcolor(EGERGB(0xff,0x80,0x26));
	bar(1120,680-640*scorea/200,1160,680);
	return;
}

void countgravity(){
	float gx,gy,F,x;
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		a[i]->ax=0;
		a[i]->ay=0;
		for(int j=0;j<Number;j++){
			if(a[j]==NULL||j==i) continue;
			x=pow((a[i]->x-a[j]->x),2)+pow((a[i]->y-a[j]->y),2);
			gx=a[j]->m*gravity*(a[j]->x-a[i]->x)/x;
			gy=a[j]->m*gravity*(a[j]->y-a[i]->y)/x;
			a[i]->ax+=gx;
			a[i]->ay+=gy;			
		}
	}
	return;
} 

void ifcollide(){                      // ��ײ��� 
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		if(a[i]->y-a[i]->r<20) a[i]->vy=fabs(a[i]->vy);
		if(a[i]->y+a[i]->r>700) a[i]->vy=-fabs(a[i]->vy);
		if(a[i]->x-a[i]->r<180&&a[i]->y>boarda.y-80&&a[i]->y<boarda.y+80) {
			a[i]->vx=fabs(a[i]->vx);
			a[i]->color=1;
			goto pos_1;
		}
		else if(a[i]->x-a[i]->r<180){
			scoreb+=a[i]->m;
			free(a[i]);
			a[i]=NULL;
			continue;
		}
		if(a[i]->x+a[i]->r>1100&&a[i]->y>boardb.y-60&&a[i]->y<boardb.y+60) {
			a[i]->vx=-fabs(a[i]->vx);
			a[i]->color=2;
			goto pos_1;
		}
		else if(a[i]->x+a[i]->r>1100){
			scorea+=a[i]->m;
			free(a[i]);
			a[i]=NULL;
			continue;
		}
		pos_1:
		for(int j=0;j<Number;j++){
			if(j==i||a[j]==NULL||a[i]==NULL) continue;
			if(sqrt(pow(a[i]->x-a[j]->x,2)+pow(a[i]->y-a[j]->y,2))<a[i]->r+a[j]->r){
				if(a[i]->m<a[j]->m){
					ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,a[j]->color);
				}else{
					ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,a[i]->color);
				}
				free(a[i]);
				a[i]=NULL;
				free(a[j]);
				a[j]=NULL;
				continue;
			}
		}
	}
	return;
}

void draw_balls(){                    // ����С��
	setlinewidth(0);
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		if(a[i]->color==1){
			setcolor(boarda.color);
			setfillcolor(boarda.color);
			fillellipse(a[i]->x,a[i]->y,a[i]->r,a[i]->r);
		}else{
			setcolor(boardb.color);
			setfillcolor(boardb.color);
			fillellipse(a[i]->x,a[i]->y,a[i]->r,a[i]->r);
		}

	}
	return;
}

void ball_go(){
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		a[i]->vx+=a[i]->ax;
		a[i]->vy+=a[i]->ay;
		a[i]->x+=a[i]->vx;
		a[i]->y+=a[i]->vy;
		a[i]->ax=0;a[i]->ay=0;
	}
	return;
}

void ball_createnewa(float x,float y,float vx,float vy,float m,int color){
	for(int i=0;i<Number;i++){
		if(a[i]==NULL){
			a[i]=(struct ball*)malloc(sizeof(struct ball));    // Ϊ��������ڴ�ռ� 
			a[i]->x=x;
			a[i]->y=y;
			a[i]->vx=vx;
			a[i]->vy=vy;
			a[i]->m=m;
			a[i]->r=Ro*log10(m+1);
			a[i]->color=color;
			break;
		}	
	}
	boarda.m=3;	
	return;
}
void ball_createnewb(float x,float y,float vx,float vy,float m,int color){
	for(int i=0;i<Number;i++){
		if(a[i]==NULL){
			a[i]=(struct ball*)malloc(sizeof(struct ball));    // Ϊ��������ڴ�ռ� 
			a[i]->x=x;
			a[i]->y=y;
			a[i]->vx=vx;
			a[i]->vy=vy;
			a[i]->m=m;
			a[i]->r=Ro*log10(m+1);
			a[i]->color=color;
			break;
		}	
	}
	boardb.m=3;	
	return;
}

void draw_boards(){                    // ����������
	if(boarda.m>8){
		boarda.m=8;
	}
	if(boardb.m>8){
		boardb.m=8;
	}
	setfillcolor(YELLOW);
	bar(181-boarda.m,boarda.y-82,180+boarda.m,boarda.y+82);
	setfillcolor(LIGHTBLUE);
	bar(1101-boardb.m,boardb.y-62,1100+boardb.m,boardb.y+62);
	return;
}

void calculateboarda(){                // ��a���������� 
	if(boarda.a==0){
		if(boarda.v<0) boarda.a=3.0;
		else if(boarda.v>0) boarda.a=-3.0;
		else boarda.a=0;
	}
	boarda.v+=boarda.a;
	boarda.y+=boarda.v;
	boarda.a=0;
	if(boarda.y>694-80) {
		boarda.y=694-80;
		boarda.v=0;
		boarda.a=0;
	}
	if(boarda.y<25+80) {
		boarda.y=25+80;
		boarda.v=0;
		boarda.a=0;
	}
	return;
}

void calculateboardb(){                  // ��b�ı߽���
	if(boardb.y>694-60) boardb.y=694-60;

	if(boardb.y<25+60) boardb.y=25+60;
	return;
}

void ball_create(float x1,float x2,float y1,float y2,float vx1,float vx2,float vy1,float vy2,float m1,float m2,int color)
{
	float m_vx1=m1*vx1,m_vx2=m2*vx2,m_vy1=m1*vy1,m_vy2=m2*vy2,x3,y3;
	float vx=(m_vx1+m_vx2)/(m1+m2),vy=(m_vy1+m_vy2)/(m1+m2);
//    float vx,vy,x3,y3; 
	if(m1>m2){
		x3=x1;y3=y1;vx=vx1;vy=vy1;
	}else if(m2>m1){
		x3=x2;y3=y2;vx=vx2;vy=vy2;
	}else{
		x3=(x1+x2)/2;
		y3=(y1+y2)/2;
		vx=(vx1+vx2)/2;
		vy=(vy1+vy2)/2;
	}
	for(int i=0;i<Number;i++){
		if(a[i]!=NULL) continue;
		a[i]=(struct ball*)malloc(sizeof(struct ball));    // Ϊ��������ڴ�ռ� 
		a[i]->x=x3;
		a[i]->y=y3;
		a[i]->vx=vx;
		a[i]->vy=vy;
		a[i]->m=m1+m2;
		if(a[i]->m>20) a[i]->m=20;                         // ��������Ĵ�С8 
		a[i]->r=Ro*log10(a[i]->m+1);
		a[i]->color=color;
		break;
	}
	return;
}                                        // ���ݶ����غ�������ɵ���λ�ú��ٶ� 

void draw_background(){
	setlinewidth(5);
	setfillcolor(EGERGB(0x00,0x00,0x66));
	bar(80,0,1200,720);
	setcolor(LIGHTGRAY);
	rectangle(100,20,1180,700);
	setcolor(EGERGB(0xff,0x80,0x26));
	line(180,25,180,694);
	setcolor(EGERGB(0x4b,0xff,0xf9));
	line(1100,25,1100,694);
	return;
}

void drawfps()                            // ���ϽǴ�ӡ֡��
{
	char str[8];
	LOGFONTA f;                           // ���������ʽ�Ľṹ�� 
	getfont(&f);                          // ��ȡ��ǰ��������
	f.lfHeight=20;                        // ��������߶�Ϊ36
	f.lfWidth=0;                          // ���ΪĬ��
	setcolor(YELLOW);
	strcpy(f.lfFaceName, "΢���ź�");     // ��������Ϊ��΢���źڡ�
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	setfont(&f);                          // ����������ʽ
	sprintf(str,"%.2f",getfps());
	outtextxy(10,10,str);
	return;
}
void howtoplay()                       // ����˵������ 
{
	char key; 
	outtextxy(640,360,"futyutyutwerwe");
	while(1){
		key=getch();
		if(key==key_esc||key==key_enter) break;
	}
	cleardevice();
	return; 
}

void drawTriangle(int *a)              // ���������������ڶ�λѡ��
{
	setcolor(BLUE);
	int p[6]={900-20,100+18,900+10,100+18-16,900+10,100+18+16};
	int q[6]={900-10,100+18,900+5,100+18-8,900+5,100+18+8};
	setfillcolor(BLUE);               // �������ɫ
	if(*a==0){
		fillpoly(3,p);
		setfillcolor(BLACK);
		fillpoly(3,q);
		setfillcolor(BLUE);
	}else if(*a==1){
		p[1]+=100;p[3]+=100;p[5]+=100;
		q[1]+=100;q[3]+=100;q[5]+=100;
		fillpoly(3,p);
		setfillcolor(BLACK);
		fillpoly(3,q);
		setfillcolor(BLUE);
	}else if(*a==2){
		p[1]+=200;p[3]+=200;p[5]+=200;
		q[1]+=200;q[3]+=200;q[5]+=200;
		fillpoly(3,p);
		setfillcolor(BLACK);
		fillpoly(3,q);
		setfillcolor(BLUE);		
	}else if(*a==3){
		p[1]+=300;p[3]+=300;p[5]+=300;
		q[1]+=300;q[3]+=300;q[5]+=300;
		fillpoly(3,p);
		setfillcolor(BLACK);
		fillpoly(3,q);
		setfillcolor(BLUE);
	}else if(*a==4){
		p[1]+=400;p[3]+=400;p[5]+=400;
		q[1]+=400;q[3]+=400;q[5]+=400;
		fillpoly(3,p);
		setfillcolor(BLACK);
		fillpoly(3,q);
		setfillcolor(BLUE);
	}
	return;
}

void drawYellowords(){
	setcolor(YELLOW);                      // ����������ɫΪ��ɫ���� 
	switch(gamemode)
	{
		case 0: outtextxy(400,250,"��   ͬɫ������ɫ����"); break;  //gamemode����ʾ�ַ��������� 
		case 1: outtextxy(400,250,"��   ͬɫ������ɫ���"); break;
		case 2: outtextxy(400,250,"��   ͬɫ�����ɫ����"); break;
		case 3: outtextxy(400,250,"��   ͬɫ�����ɫ���"); break;
	}
	switch(gravity)
	{
		case 1: outtextxy(400,350,"��   С����"); break;           //gravity����ʾ�ַ������� 
		case 2: outtextxy(400,350,"��   ����");   break;
		case 3: outtextxy(400,350,"��   ����");   break;
		case 4: outtextxy(400,350,"��   ������"); break;
		case 5: outtextxy(400,350,"��   �ڶ�");   break;
	}
	return;
	
}
void up(int *a)                           // up���¼� 
{
	if(*a-1<0) *a=4;
	else *a-=1;
	return;
}

void down(int *a)                         // down���¼� 
{
	if(*a+1>4) *a=0;
	else *a+=1;	
	return;
}

void enter(int *a)                        // enter���¼� 
{
	if(*a==0){
		howtoplay();
	}else if(*a==1){
		if(gamemode+1>3) gamemode=0;
		else gamemode+=1;
	}else if(*a==2){
		if(gravity+1>5) gravity=1;
		else gravity+=1;
	}else if(*a==3){
		startgame();
		cleardevice();
		setfirstfont();
	}else if(*a==4) exit(0);
	return;
}

void createa(){
	if(boarda.m>3)  ball_createnewa(180+boarda.m,boarda.y,1+sqrt(boarda.m-2)*3.0,boarda.v/5,boarda.m-3,1);
	return;
} 

void startgame()                          // ��ʽ��Ϸ��ʼ
{ 
	key_msg key_1={0};                    // ���ڴ洢����1��Ϣ
	mouse_msg mouse_1={0};                // 
	int mouse_x=0;                        //   
	int mouse_y;
	char key;
//	char str1[10],str2[10];


	boarda.y=360;
	scorea=0;
	scoreb=0;                             // ��ʼ��һЩ���� 
	while(1)                              // ���ѭ�����ڴ�����̲�������Ϣ 
	{
		cleardevice();                    // �����������
		draw_background();
		if(timer<0){
			boarda.m+=1;
			boardb.m+=1;
			timer=20;
		}
		

		if(kbmsg())  key_1=getkey();
		while(mousemsg()) mouse_1=getmouse();
		mousepos(&mouse_x,&boardb.y);
		
		ifcollide();                       // ��ײ��� 
		
		countgravity();                    // �������� 
			
		if(key_1.msg==key_msg_down){
			switch(key_1.key){
				case 'W': boarda.a=-3;           break;  // a������
				case 'S': boarda.a+=3;           break;  // a������
				case 'D': createa();             break;  // ������a
			}			
		}
		
		

		drawfps();
		calculateboarda();
		calculateboardb();
		
		
		
		if(mouse_1.is_down()&&boardb.m>3) {
			ball_createnewb(1100-boardb.m,boardb.y,-1-sqrt(boardb.m-2)*3.0,0,boardb.m-3,2);
		}
		
		if(kbhit())  key=getch();         // ����escר�� 
		if(key==key_esc){                 // �������esc���˳�����һ����
			for(int i=0;i<Number;i++){
				free(a[i]);
				a[i]=NULL;
			}
			return;
		}
			
		ball_go();
		
		
		
		draw_balls();
		
		draw_boards();
		
		showscoreab();
			
//		sprintf(str1,"%d",boarda.y);
//	    sprintf(str2,"%d",boardb.y);
//	    outtextxy(100,boarda.y,str1);
//	    outtextxy(1000,boardb.y,str2);

		timer--;

		delay_fps(60);
	}
}

void draw_1_all(int *a)
{
	outtextxy(200,100,"����Ϸ��ô��");    // �����ʾ���� 
	outtextxy(200,200,"��������ģʽ");
	outtextxy(200,300,"����������С");
	outtextxy(200,400,"��ʼ��Ϸ");
	outtextxy(200,500,"��������");
	drawTriangle(a);                      // ������ 
	drawYellowords();                     // ���gamemode��gravity 
	return;	
}

void setfirstfont()
{                      // ���������ú��� 
	setlinewidth(0);
	setcolor(GREEN);                      // ����������ɫΪ����ɫ��
	LOGFONTA f;                           // ���������ʽ�Ľṹ�� 
	getfont(&f);                          // ��ȡ��ǰ��������
	f.lfHeight=36;                        // ��������߶�Ϊ36
	f.lfWidth=0;                          // ���ΪĬ�� 
	strcpy(f.lfFaceName, "΢���ź�");     // ��������Ϊ��΢���źڡ�
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	setfont(&f);                          // ����������ʽ
	return;	
}
void mystart()                            // ��������ѡ���ĺ��� 
{
	int a=0;                              // a������ָ��ĵ�ǰλ�ã���ʼλ��Ϊ0����һ������
	char key;                             // �洢�̵ļ����û�


	while(1)                              // ���ѭ�����ڽ��ռ�����Ϣ���л�������Ŀ
	{
		
		cleardevice();                    // ����������� 

        switch(key)
		{
        	case key_up:     up(&a);     break;
        	case key_down:   down(&a);   break;
        	case key_enter:  enter(&a);  break;
        	case key_esc:    return;
        }
        drawfps();                            // ���ϽǴ�ӡ֡��
		setfirstfont();                       // ����������
		draw_1_all(&a);                       // ������ǰ��������Ԫ��
		key=getch();                          // ��ȡһ��
		delay_fps(60);                        // ����ˢ����ͬʱ������ʱЧ��
		                                      // ע����ʱһ��Ҫ���ڶ���������ɺ����ᷢ������
	}
}



	
int main()
{	
//	setinitmode(INIT_NOBORDER);        // ��ȥ�߿�
	initgraph(1280, 720);              // ����һ��720P�Ļ���
    setrendermode(RENDER_MANUAL);      // �����ֶ�ˢ����Ļ
	mystart();                         // ������ѡ��
	closegraph();                      // �رջ��� 
	return 0;
}

