/*
         written by dfdfdfff û����Ȩ��ֹת�� 
*/



#include "graphics.h"                  // ��Ҫ���õ�ͼ�ο�
#include <stdio.h>                     // ����Ҫ���ַ�������
#include <stdlib.h>
#include <math.h>                      // ��ѧ����
#include <time.h>                      // �����������Ҫ 
#define Number 50                      // ���򻺳����Ĵ�С ������ �ٴ�Ҫ���� 
#define Ro 15                          // ���ڼ�����İ뾶���ܶ�ϵ�� ��ʽΪr=Ro*log10(m) 



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
	int explode;                       // �Ƿ�ը 
} *a[Number];                          // С��Ľṹ ͬʱ����һ������������ָ������ ����Ϸ���������ݽṹ
                                       // ���ǲ������ڴ�ռ� ����Ҫ�ڷ���Ͳ���С��ʱʹ��malloc����Ϊÿ��С������ڴ� 
                                       // �����Ҫfree�����ڴ�����ڴ�й¶
                                        
struct boardaa{                        // a��Ľṹ�� 
	float m;                           // a������� 
	float y;                           // a�������λ�� 
	float v;                           // a��������ٶ� 
	float a;                           // a���������ٶ� 
	color_t color;                     // a�����ɫ 
	int able;                          // a����Ƿ�̱����״̬ 
} boarda={3,360,0,0,EGERGB(0xff,0x80,0x26),1};      // a���ʵ�����������ڴ�ռ��a�� 
 
struct boardbb{                        // b��Ľṹ��
	float m;                           // b�������          
	float y;                           // b�������λ��      
	float v;                           // b��������ٶ�      
	float a;                           // b���������ٶ�    
	color_t color;                     // b�����ɫ          
	int able;                          // b����Ƿ�̱����״̬
} boardb={3,360,0,0,EGERGB(0x4f,0xff,0xf9),1};      // b���ʵ�����������ڴ�ռ��b�� 


                                       // ȫ�ֱ�����
int gamemode=0;                        // ���ڴ������ģʽ
int gravity=3;                         // ���������С
int timer=20;                          // �������Ļ�ʱ
int timera=-1;
int timerb=-1;                         // ab��̱�������ȴʱ��
int win=0;                             // �ж�ʤ�� 
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
void awin();                           // aӮʱչʾ�Ľ���
void bwin();                           // bӮʱչʾ�Ľ���


/*-------------------------------�����ṹ���岿���Լ�����ԭ�Ͳ��ֽ���----------------------------------*/ 
/*-----------------------------------------��������Ϸ���ⲿ��------------------------------------------*/ 


void awin(){
    setfontbkcolor(EGERGB(0x00,0x00,0x66));// �������ֵı���ɫ 
    setcolor(EGERGB(0xff,0x80,0x26));      // ����������ɫΪa����ɫ
	LOGFONTA f;                            // ���������ʽ�Ľṹ�� 
	getfont(&f);                           // ��ȡ��ǰ��������
	f.lfHeight=80;                         // ��������߶�Ϊ36
	f.lfWidth=0;                           // ���ΪĬ�� 
	strcpy(f.lfFaceName, "����_GB2312");   // ��������Ϊ������_GB2312��
	f.lfQuality = ANTIALIASED_QUALITY;     // �������Ч��Ϊ�����  
	setfont(&f);                           // ����������ʽ
	outtextxy(480,200,"��ɫӮ��");
	outtextxy(280,400,"��esc��enter���˳�"); 
    return;                                //��ɫ����a��Ӯ��ʱ���������� 
}

void bwin(){
    setfontbkcolor(EGERGB(0x00,0x00,0x66));// �������ֵı���ɫ
	setcolor(EGERGB(0x4b,0xff,0xf9));      // ����������ɫΪa����ɫ
	LOGFONTA f;                            // ���������ʽ�Ľṹ�� 
	getfont(&f);                           // ��ȡ��ǰ��������
	f.lfHeight=80;                         // ��������߶�Ϊ100
	f.lfWidth=0;                           // ���ΪĬ�� 
	strcpy(f.lfFaceName, "����_GB2312");   // ��������Ϊ������_GB2312��
	f.lfQuality = ANTIALIASED_QUALITY;     // �������Ч��Ϊ�����  
	setfont(&f);                           // ����������ʽ
	outtextxy(480,200,"��ɫӮ��");
	outtextxy(280,400,"��esc��enter���˳�"); 
    return;                                // ��ɫ����b��Ӯ��ʱ����������
}

void showscoreab(){
	setfillcolor(BLACK);
	bar(120,40,160,680);
	bar(1120,40,1160,680);
	if(scoreb>=100){
	    win=2;
	    scoreb=100;
    }
	setfillcolor(EGERGB(0x4b,0xff,0xf9));
	bar(120,680-640*scoreb/100,160,680);
	if(scorea>=100){
	    win=1;
	    scorea=100;
    }
	setfillcolor(EGERGB(0xff,0x80,0x26));
	bar(1120,680-640*scorea/100,1160,680);
	return;
}                                      // ���������������ʽչʾab�ĵ÷� 

void countgravity(){
	float gx,gy,F,x;
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;       // ���е�continue����Ϊ�˱���Ƿ����ڴ���� �����ʵ�û���κ����ݵġ�С�� 
		a[i]->ax=0;
		a[i]->ay=0;
		for(int j=0;j<Number;j++){
			if(a[j]==NULL||j==i) continue;     // ��ֹ�Լ����Լ������������ų�i==jʱ����� 
			x=pow((a[i]->x-a[j]->x),2)+pow((a[i]->y-a[j]->y),2);
			gx=a[j]->m*gravity*(a[j]->x-a[i]->x)/x;
			gy=a[j]->m*gravity*(a[j]->y-a[i]->y)/x;
			switch(gamemode){
				case 0: a[i]->ax+=gx; a[i]->ay+=gy; break;
				case 1: a[i]->color==a[j]->color? a[i]->ax+=gx,a[i]->ay+=gy:a[i]->ax-=gx,a[i]->ay-=gy; break;
				case 2: a[i]->color==a[j]->color? a[i]->ax-=gx,a[i]->ay-=gy:a[i]->ax+=gx,a[i]->ay+=gy; break;
				case 3: a[i]->ax-=gx; a[i]->ay-=gy; break;
				case 4: break;                 // ����gamemode��ֵ�ж����������ǳ���gamemode==4��ʾû������ ���Բ���������ֱ��break 
			}			
		}
	}
	return;                            // �������� ��������С������������� 
} 

void ifcollide(){                      // ���ӵ���ײ��� 
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		if(a[i]->y-a[i]->r<20) a[i]->vy=fabs(a[i]->vy);
		if(a[i]->y+a[i]->r>700) a[i]->vy=-fabs(a[i]->vy);// ���±߽����ײ��� 
		if(a[i]->x-a[i]->r<180&&a[i]->y>boarda.y-80&&a[i]->y<boarda.y+80) {
		    if(a[i]->explode){                           // ��������ײ���
		        boarda.able=0;                           // Ϊ�˴ﵽ��ϷЧ��ÿ������Ҫ��������ײ��� 
		        timera=120;                              // Ҫʵ�ֱ�ը������޵�״̬ 
			    scoreb+=a[i]->m;                         // û�б����ס��С�򽫱� �����ڴ沢�Ʒ� 
			    free(a[i]);
			    a[i]=NULL;
			    continue;
            }
			a[i]->vx=fabs(a[i]->vx);
			a[i]->color=1;
			goto pos_1;
		}
		else if(a[i]->x-a[i]->r<180){
		    if(a[i]->explode){
		        boarda.able=0;
		        timera=120;
		    }
			scoreb+=a[i]->m;
			free(a[i]);
			a[i]=NULL;
			continue;                  //д��ô���޷�����ʵ����Ͱ����ײ �ͼƷ�Ч�� 
		}
		//-----------------------------�ֽ��� ������a�����ײ��� ������b�����ײ��� 
		if(a[i]->x+a[i]->r>1100&&a[i]->y>boardb.y-60&&a[i]->y<boardb.y+60) {
		    if(a[i]->explode){
		        boardb.able=0;
		        timerb=120;
			    scorea+=a[i]->m;
			    free(a[i]);
		        a[i]=NULL;
		        continue;
            }
			a[i]->vx=-fabs(a[i]->vx);
			a[i]->color=2;
			goto pos_1;
		}
		else if(a[i]->x+a[i]->r>1100){
		    if(a[i]->explode){
		        boardb.able=0;
		        timerb=120;
		    }
			scorea+=a[i]->m;
			free(a[i]);
			a[i]=NULL;
			continue;
		}
		pos_1:
		for(int j=0;j<Number;j++){       // ����һ���µ�ѭ�����ڼ����֮�����ײ 
			if(j==i||a[j]==NULL||a[i]==NULL) continue;
			if(sqrt(pow(a[i]->x-a[j]->x,2)+pow(a[i]->y-a[j]->y,2))<a[i]->r+a[j]->r){
				if(a[i]->m<a[j]->m||a[i]->color==a[j]->color){
					ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,a[j]->color);
				}else if(a[i]->m>a[j]->m){
					ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,a[i]->color);
				}else if(a[i]->color!=a[j]->color){
				    ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,rand()%2+1);
                }                        // ������������Ⱦ������ɫ 
				free(a[i]);              // д��ô���޷Ǿ���Ϊ���ж���ײ�ںϺ��С�����ɫ ����û������ 
				a[i]=NULL;
				free(a[j]);
				a[j]=NULL;               // ����ͷ��໥��ײ��С��Ĵ洢�ռ� 
				continue;                // ���õ�����ײ�ںϺ���������µĲ������������� 
			}
		}
	}
	return;
}

void draw_balls(){                       // ����С��
	setlinewidth(0);                     // С��ʹ����Բ�������� ����Ҫ�涨����ߵ�״̬ 
	color_t b;
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		if(a[i]->m>18) {
		    a[i]->explode=1;             // �������˱�ը 
		    a[i]->m=18;                  // ��������Ĵ�С8
        }
		if(a[i]->color==1){
			if(a[i]->explode){
			    b=RGB(rand()%256,rand()%256,rand()%256);
			    setcolor(b);
			    setfillcolor(b);
            }else{
			    setcolor(boarda.color);
			    setfillcolor(boarda.color);             
            }
			fillellipse(a[i]->x,a[i]->y,a[i]->r,a[i]->r);
		}else{
            if(a[i]->explode){           // ��˸��ʾ��ը״̬�ĵ��� 
			    b=RGB(rand()%256,rand()%256,rand()%256);
			    setcolor(b);             // ��ʵ���������һ����ɫֵ���ٱ仯������˸��Ч�� 
			    setfillcolor(b);
            }else{
			    setcolor(boardb.color);
			    setfillcolor(boardb.color);              
            }
			fillellipse(a[i]->x,a[i]->y,a[i]->r,a[i]->r);
		}

	}
	return;                              // ��ը״̬�ĵ�����Ҫ��˸��ʾ 
}                                        // �������� ���Ƴ���Ļ�ϵ����е��� ����Ҫ�ж��ǲ��Ǳ�ը״̬ 

void ball_go(){
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		a[i]->vx+=a[i]->ax;
		a[i]->vy+=a[i]->ay;
		a[i]->x+=a[i]->vx;
		a[i]->y+=a[i]->vy;
		a[i]->ax=0;a[i]->ay=0;
	}
	return;                              // �������� ���㵯����˶��켣 ����������ײ��� 
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
		    a[i]->explode=0; 
			break;
		}	
	}
	boarda.m=3;	
	return;                                                    // ���b����ķ��亯�� ����û������ 
}
void ball_createnewb(float x,float y,float vx,float vy,float m,int color){ 
	for(int i=0;i<Number;i++){                                 // �������нṹ��ָ������ 
		if(a[i]==NULL){                                        // �����ǰ�ṹ��ָ�������ڴ�Ŀռ�Ϊ���оʹ����ڵ�ǰλ�� 
			a[i]=(struct ball*)malloc(sizeof(struct ball));    // Ϊ��������ڴ�ռ� 
			a[i]->x=x;
			a[i]->y=y;
			a[i]->vx=vx;
			a[i]->vy=vy;               // �������õĸ������� 
			a[i]->m=m;                 // ����������ڰ�������� ����ٶ�ȡ���ڰ��ʱ���ƶ��ٶ� 
			a[i]->r=Ro*log10(m+1);     // �������õĵ����С 
			a[i]->color=color;         // ������ɫ 
			a[i]->explode=0;           // �����ж���ը��ϵ�� 
			break;
		}	
	}
	boardb.m=3;	
	return;                            // �������ר����b�巢�䵯��ʱʹ�� 
}

void draw_boards(){                    // ����������
	if(boarda.m>8){
		boarda.m=8;
	}
	if(boardb.m>8){                                                  // ���������������� 
		boardb.m=8;
	}
	                                                                 // �ж�ab���ǲ���̱���� 
	if(boarda.able) setfillcolor(YELLOW);                            // ̱���Ͳ�����˸Ч�� 
    else setfillcolor(RGB(rand()%256,rand()%256,rand()%256));
    
	bar(181-boarda.m,boarda.y-82,180+boarda.m,boarda.y+82);
	
	if(boardb.able) setfillcolor(LIGHTBLUE);
    else setfillcolor(RGB(rand()%256,rand()%256,rand()%256));        // ���ð�����ɫ	
	
	bar(1101-boardb.m,boardb.y-82,1100+boardb.m,boardb.y+82);
	return;
}

void calculateboarda(){                // ��a���˶��켣 �����b���˶��켣˵�� ����û������ 
	if(boarda.a==0){
		if(boarda.v<0) boarda.a=3.0;
		else if(boarda.v>0) boarda.a=-3.0;
		else boarda.a=0;
	}
	boarda.v+=boarda.a;
	if(fabs(boarda.v)>27){
		if(boarda.v>0) boarda.v=27;
		else boarda.v=-27;
	}
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

void calculateboardb(){                // ��b���˶��켣�ļ��� ����ּ�ڵõ�ab��Ĵ�ֱ����λ�� 
	if(boardb.a==0){
		if(boardb.v<0) boardb.a=3.0;
		else if(boardb.v>0) boardb.a=-3.0;
		else boardb.a=0;               // ����Ħ�����ٵ�Ч�� 
	}
	boardb.v+=boardb.a;                // ���ٶ�ֵ���ص��ٶ�ֵ�� 
	if(fabs(boardb.v)>27){
		if(boardb.v>0) boardb.v=27;
		else boardb.v=-27;
	}
	boardb.y+=boardb.v;                // �ٶ�ֵ���ص�λ��ֵ�� 
	boardb.a=0;                        // ���ٶ���˲ʱ�������������� 
	if(boardb.y>694-80) {              // ab�������߽���Ч�� 
		boardb.y=694-80;
		boardb.v=0;
		boardb.a=0;
	}
	if(boardb.y<25+80) {
		boardb.y=25+80;
		boardb.v=0;
		boardb.a=0;
	}
	return;
}

void ball_create(float x1,float x2,float y1,float y2,float vx1,float vx2,float vy1,float vy2,float m1,float m2,int color)
{
	float m_vx1=m1*vx1,m_vx2=m2*vx2,m_vy1=m1*vy1,m_vy2=m2*vy2,x3,y3;
	float vx=(m_vx1+m_vx2)/(m1+m2),vy=(m_vy1+m_vy2)/(m1+m2);// �������ʱ��ʹ�ö����غ�����������ٶ� 
	if(m1>m2){
		x3=x1;y3=y1;
	}else if(m2>m1){
		x3=x2;y3=y2;
	}else{                                                 // �ж���ײ���С��˭������ �ʹ�ԭ�� ���ȡ�м�ֵ 
		x3=(x1+x2)/2;                                      // x3��y3���ڴ�������λ�� 
		y3=(y1+y2)/2;
	}
	for(int i=0;i<Number;i++){
		if(a[i]!=NULL) continue;                           // ����ṹ��ָ�������ΪNULL������ ����Ƿ����ڴ���� 
		a[i]=(struct ball*)malloc(sizeof(struct ball));    // Ϊ��������ڴ�ռ� 
		a[i]->x=x3;
		a[i]->y=y3;
		a[i]->vx=vx;
		a[i]->vy=vy;
		a[i]->m=m1+m2; 
		if(a[i]->m>18) a[i]->m=19;
		a[i]->r=Ro*log10(a[i]->m+1);
		a[i]->color=color;
		a[i]->explode=0;                 // Ϊ�����������õĲ��� 
		break;
	}
	return;                              // �������ר�������ɻ�����ײ��������� 
}                                        // ���ݶ����غ�������ɵ���λ�ú��ٶ� 

void draw_background(){                  // ������Ϸ�ı����� ������ɫ���� ���ο�߽��ab��Ĺ�� 
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

void drawfps()                          // ���ϽǴ�ӡ֡��
{
	char str[8];
	setfontbkcolor(BLACK);              // �������ֵı���ɫ
	LOGFONTA f;                         // ���������ʽ�Ľṹ�� 
	getfont(&f);                        // ��ȡ��ǰ��������
	f.lfHeight=20;                      // ��������߶�Ϊ36
	f.lfWidth=0;                        // ���ΪĬ��
	setcolor(YELLOW);                   // ����������ɫ 
	strcpy(f.lfFaceName, "΢���ź�");   // ��������Ϊ��΢���źڡ�
	f.lfQuality = ANTIALIASED_QUALITY;  // �������Ч��Ϊ�����  
	setfont(&f);                        // ����������ʽ
	sprintf(str,"%.2f",getfps());
	outtextxy(10,10,str);
	return;
}
void howtoplay()                        // ����˵������ 
{
	char key; 
	outtextxy(10,10,"1 �������� w  s  d �ͷ���������� ���� d ��������������С�� �ƶ�����Ը�С���ṩ������ٶȡ�\n");
	outtextxy(10,50,"2 ���㲻����С���ʱ�������� ��һ�η��������С����ٶȺʹ�С����ʱ������ƶ����\n");
	outtextxy(10,90,"3 ����򵽰�����ʱ�������ۻ��ռ�С������� ����һ���������ۼ���ʱ�Է���Ӯ����Ϸ������\n");
	outtextxy(10,130,"4 ����Ϸ���Ե���С��֮�����������⻹������ ���������Ĵ�С���ṩ�����淨��\n");
	while(1){
		key=getch();                    // ���ռ�����Ϣ�����˳�˵������ 
		if(key==key_esc||key==key_enter) break;
	}
	cleardevice();
	return; 
}

void drawTriangle(int *a)               // ����ɫָ�����ڶ�λѡ��
{
	setcolor(BLUE);
	int p[6]={900-20,100+18,900+10,100+18-16,900+10,100+18+16};
	int q[6]={900-10,100+18,900+5,100+18-8,900+5,100+18+8};
	setfillcolor(BLUE);                 // �������ɫΪ��ɫָ���λ�ú�*a��ֵ�й� 
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

void drawYellowords(){                     // ��ӡ����ɫ��gamemode��gravity��ֵ 
	setcolor(YELLOW);                      // ����������ɫΪ��ɫ���� 
	switch(gamemode)                                                // ��ֻ��ȫ�ֲ�����gamemode��gravity����ֵ�й� 
	{
		case 0: outtextxy(400,250,"��   ͬɫ������ɫ����"); break;  // gamemode��ѡ��
		case 1: outtextxy(400,250,"��   ͬɫ������ɫ���"); break;
		case 2: outtextxy(400,250,"��   ͬɫ�����ɫ����"); break;
		case 3: outtextxy(400,250,"��   ͬɫ�����ɫ���"); break;
		case 4: outtextxy(400,250,"��   ������"); break;
	}
	switch(gravity)
	{
		case 1: outtextxy(400,350,"��   С����"); break;            // gravity�ĵȼ� 
		case 2: outtextxy(400,350,"��   ����");   break;
		case 3: outtextxy(400,350,"��   ����");   break;
		case 4: outtextxy(400,350,"��   ������"); break;
		case 5: outtextxy(400,350,"��   �ڶ�");   break;
	}
	return;
	
}
void up(int *a)                            // up���¼�����ɫָ������ 
{
	if(*a-1<0) *a=4;
	else *a-=1;
	return;
}

void down(int *a)                          // down���¼�����ɫָ������ 
{
	if(*a+1>4) *a=0;
	else *a+=1;	
	return;
}

void enter(int *a)                         // enter���¼� 
{
	if(*a==0){                             // ��ɫָ���ڡ�����Ϸ��ô�桰λ�� 
		howtoplay();                       // �л�����Ϸ˵������ 
	}else if(*a==1){                       // ��ɫָ���ڡ���������ģʽ��λ�� 
		if(gamemode+1>4) gamemode=0;
		else gamemode+=1;
	}else if(*a==2){                       // ��ɫָ���ڡ�����������С��λ�� 
		if(gravity+1>5) gravity=1;         // �л�������С 
		else gravity+=1;
	}else if(*a==3){                       // ��ɫָ���ڡ���ʼ��Ϸλ�á� 
		startgame();
		cleardevice();
		setfirstfont();                    // ���������ò˵���������ʽ 
	}else if(*a==4) exit(0);               // ��ɫָ���ڡ�������Ϸ��λ�� 
	return;
}

void createa(){                            // ����a�� 
	if(boarda.m>3)  ball_createnewa(180+boarda.m,boarda.y,pow(boarda.m-2,1.7),boarda.v/2,boarda.m-3,1);
	return;
}

void createb(){                            // ����b�� 
	if(boardb.m>3)  ball_createnewb(1100-boardb.m,boardb.y,-pow(boardb.m-2,1.7),boardb.v/2,boardb.m-3,2);
	return;
}

void startgame()                           // ��ʽ��Ϸ��ʼ
{
	char key;                              // ���ڲ���esc��enter����Ϣ 
//	char str1[10],str2[10];

    srand(time(NULL));                     // ��ʼ����������� 
	boarda.y=360;boarda.able=1;boarda.m=3;
	boardb.y=360;boardb.able=1;boardb.m=3;
	scorea=0;                             
	scoreb=0;                              // ��ʼ��ab�ĵ÷� 
    win=0;                                 // ��ʼ��һЩ����������ĳ�ʼλ�� ��ķ�̱��״̬�Ͱ������ 
	while(1)                               // ���ѭ�����ڴ�����̲�������Ϣ 
	{
		cleardevice();                     // �����������
		draw_background();
		if(win){                           // �ж��ǲ��ǲ�����Ӯ������Ǿ�ִ��if�µ����� 
		    cleardevice();                 // �����������
		    draw_background();
		    if(win==1)  awin();            // �ж�aӮ����bӮ 
		    else bwin();
		    draw_boards();
		    showscoreab();
		    drawfps();
		    if(kbhit())  key=getch();      // ����esc��enterר�� 
		    if(key==key_esc||key==key_enter) goto pos_2; // �������esc��enter���˳�����һ����
		    delay_fps(60);                 // ��Ҫ����ʱ��ʾ 
		    continue;
        }
		
		if(timer<0){                       // ab���������ʱ 
			boarda.m+=1;
			boardb.m+=1;
			timer=20;
		}
		if(timera<0) boarda.able=1;
		else timera--;                    
		if(timerb<0) boardb.able=1;        // ���ab���ڲ�̱��״̬�Ͳ���ʱ 
		else timerb--;                     // ab��̱���ļ�ʱ�� 
		
		ifcollide();                       // ��ײ���+��������+��ը������ռ�� 
		
		countgravity();                    // �������� 
			

		
		drawfps();                         // ���ϽǴ�ӡ֡�� ���������Ϊ59~61֡ �鹦�ڼ�����Ϣ���ղ��õĶ��Ƿ��������� 
		calculateboarda();
		calculateboardb();                 // ����ab���˶��켣 
		
		if(kbhit())  key=getch();          // ����escר�� ���������ĺ���kbhit() 
		if(key==key_esc){                  // �������esc���˳�����һ����
		    pos_2:
			for(int i=0;i<Number;i++){     // �ͷ�����С��ռ�õ��ڴ� 
				free(a[i]);
				a[i]=NULL;
			}
			return;
		}
		
		if(GetAsyncKeyState('W')&0x8000&&boarda.able) boarda.a=-3;
		if(GetAsyncKeyState('S')&0x8000&&boarda.able) boarda.a=+3;
		if(GetAsyncKeyState('D')&0x8000&&boarda.able) createa();
		if(GetAsyncKeyState(VK_UP)&0x8000&&boardb.able) boardb.a=-3;
		if(GetAsyncKeyState(VK_DOWN)&0x8000&&boardb.able) boardb.a=+3;
		if(GetAsyncKeyState(VK_LEFT)&0x8000&&boardb.able) createb();           //��ȡ���̵�״̬
		
        // ����˵��ʵ̫��ͳ ��ʵ���������ֱ�Ӷ�ȡ������̵�״̬ ��ָ�������»���̧��
        // Ȼ��ʹ��ϵͳ�������߼����̽�����Ϣ ���Ա����˳�ͻ���� ˳��֧�����������뷨�µĲ���
        // ����������ǰ�ķ�����getch()���ָ���ַ� ���򽫻�������صļ�����Ϣ��ͻ���� ���Ҳ�������������� ����ͳ��֡�� 
 

		showscoreab();                     // չʾab�ĵ÷�
	
		ball_go();                         // ����С����˶��켣 
			
		draw_balls();                      // ��������С�� 
		
		draw_boards();                     // �������а�
         	
//		sprintf(str1,"%d",boarda.y);
//	    sprintf(str2,"%d",boardb.y);
//	    outtextxy(100,boarda.y,str1);
//	    outtextxy(1000,boardb.y,str2);

		timer--;                           // ab�������ļ�ʱ���Լ� 

		delay_fps(60);                     // ��Ҫ����ʱ��ʾ 
	}
}

void draw_1_all(int *a)                    // ���ѡ��˵���ȫ������ 
{
	outtextxy(200,100,"����Ϸ��ô��");     // �����ʾ���� 
	outtextxy(200,200,"��������ģʽ");
	outtextxy(200,300,"����������С");
	outtextxy(200,400,"��ʼ��Ϸ");
	outtextxy(200,500,"��������");         // ������ı����ɫ��ǩ�� 
	drawTriangle(a);                       // ������ 
	drawYellowords();                      // ���gamemode��gravityֵ�Ļ��� 
	return;
}

void setfirstfont()
{                      // ���������ú���
    setfontbkcolor(BLACK);                 // �������ֱ���ɫ 
	setlinewidth(0);                       // �����߿� 
	setcolor(GREEN);                       // ����������ɫΪ����ɫ��
	LOGFONTA f;                            // ���������ʽ�Ľṹ�� 
	getfont(&f);                           // ��ȡ��ǰ��������
	f.lfHeight=36;                         // ��������߶�Ϊ36
	f.lfWidth=0;                           // ���ΪĬ�� 
	strcpy(f.lfFaceName, "΢���ź�");      // ��������Ϊ��΢���źڡ�
	f.lfQuality = ANTIALIASED_QUALITY;     // �������Ч��Ϊ�����  
	setfont(&f);                           // ����������ʽ
	return;	
}
void mystart()                             // ��������ѡ���ĺ��� 
{
	int a=0;                               // a������ָ��ĵ�ǰλ�ã���ʼλ��Ϊ0����һ������
	char key;                              // �洢�̵ļ����û�


	while(1)                               // ���ѭ�����ڽ��ռ�����Ϣ���л�������Ŀ
	{
		
		cleardevice();                     // ����������� 

        switch(key)                              // �Խ��յ��ļ����ַ������ж� 
		{
        	case key_up:     up(&a);     break;  // ������ɫָ�� 
        	case key_down:   down(&a);   break;  // ������ɫָ�� 
        	case key_enter:  enter(&a);  break;  // enter��ѡ����л���ɫָ��ָ���ѡ�� 
        	case key_esc:    return;          // �������esc���˳��������Ȼ�������˳����� 
        }                                  //getch()��ͨ������������ȡ�ַ�����ͳ��֡��û������ 
         
        drawfps();                         // ���ϽǴ�ӡ֡��
		setfirstfont();                    // ����������
		draw_1_all(&a);                    // ������ǰ��������Ԫ��
		key=getch();                       // ��ȡһ��
		delay_fps(60);                     // ����ˢ����ͬʱ������ʱЧ��
		                                   // ע����ʱһ��Ҫ���ڶ���������ɺ����ᷢ������
	}
}




int main()
{
//	setinitmode(INIT_NOBORDER);            // ��ȥds�߿�
	initgraph(1280, 720);                  // ����һ��720P�Ļ���
    setrendermode(RENDER_MANUAL);          // �����ֶ�ˢ����Ļ
	mystart();                             // ������ѡ��
	closegraph();                          // �رջ��� 
	return 0;                              // �����˳����� 
}

