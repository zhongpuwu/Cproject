/*
         written by dfdfdfff
*/



#include "graphics.h"                  // 需要引用的图形库
#include <stdio.h>                     // 不必要的字符串处理
#include <stdlib.h>
#include <math.h>                      // 数学函数
#define Number 50                      // 球球缓冲区的大小 够用了 再大要卡的 
#define Ro 12                          // 用于计算球的半径的密度系数 公式为r=Ro*log(m) 



struct ball{
	int color;                         // 小球的颜色 
	float m;                           // 小球的质量
	float r;                           // 小球的半径 和质量有关 
	float x;                           // 横坐标 
	float y;                           // 纵坐标 
	float vx;                          // x向速度 
	float vy;                          // y向速度 
	float ax;                          // x向加速度 
	float ay;                          // y向加速度 
} *a[Number];                   // 小球的结构 同时生成一个存放所有球的指针数组 是游戏的主体 

struct boardaa{                        //
	float m;
	int y;
	float v;
	float a;
	color_t color;
	int able;
} boarda={3,360,0,0,EGERGB(0xff,0x80,0x26),1};  // a板的结构
 
struct boardbb{                        //
	float m;
	int y;
	color_t color;
	int able;
} boardb={3,360,EGERGB(0x4f,0xff,0xf9),1};      // b板的结构


                                       // 全局变量表
int gamemode=0;                        // 用于存放引力模式
int gravity=1;                         // 存放引力大小
int timer=20;                          // 板生长的缓时
float scorea=0;                        // a的得分 
float scoreb=0;                        // b的得分 


                                       // 函数的原型声明
void howtoplay();                      // 全屏显示游戏的操作方法
void drawTriangle(int *a);             // 绘制设置指针图形
void up(int *a);                       // 初始界面的up响应
void down(int *a);                     // 初始界面的down响应
void enter(int *a);                    // 初始界面的enter响应
void esc(int *a);					   // 初始界面esc的响应			    
void draw_1_all(int *a);               // 画出初始界面一帧所有元素 
void setfirstfont();                   // 设置初始界面的字体和颜色 
void mystart();                        // 初始界面的主函数 
void drawYellowords();                 // 打印gamemode和gravity 
void startgame();                      // 正式开始游戏 
void drawfps();                        // 左上角打印帧率
void ifcollide();                      // 碰撞检测
void draw_balls();                     // 绘制所有小球
void draw_boards();                    // 绘制两个挡板
void draw_background();                // 绘制背景
void ball_createnewa(float x,float y,float vx,float vy,float m,int color);                 // 发射一个balla对象
void ball_createnewb(float x,float y,float vx,float vy,float m,int color);                 // 发射一个balla对象
void ball_create(float x1,float x2,float y1,float y2,float vx1,float vx2,float vy1,float vy2,float m1,float m2,int color);
void calculateboarda();                // 计算板a的位置
void calculateboardb();                // 计算板b的位置
void ball_go();                        // 小球的移动 
void createa();                        // 生成a
void showscoreb();                     // 展示ab的得分
void countgravity();                   // 计算引力

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

void ifcollide(){                      // 碰撞检测 
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

void draw_balls(){                    // 画出小球
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
			a[i]=(struct ball*)malloc(sizeof(struct ball));    // 为球球分配内存空间 
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
			a[i]=(struct ball*)malloc(sizeof(struct ball));    // 为球球分配内存空间 
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

void draw_boards(){                    // 绘制两个板
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

void calculateboarda(){                // 板a的物理引擎 
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

void calculateboardb(){                  // 板b的边界检测
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
		a[i]=(struct ball*)malloc(sizeof(struct ball));    // 为球球分配内存空间 
		a[i]->x=x3;
		a[i]->y=y3;
		a[i]->vx=vx;
		a[i]->vy=vy;
		a[i]->m=m1+m2;
		if(a[i]->m>20) a[i]->m=20;                         // 限制球球的大小8 
		a[i]->r=Ro*log10(a[i]->m+1);
		a[i]->color=color;
		break;
	}
	return;
}                                        // 根据动量守恒求解生成的球位置和速度 

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

void drawfps()                            // 左上角打印帧率
{
	char str[8];
	LOGFONTA f;                           // 定义字体格式的结构体 
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight=20;                        // 设置字体高度为36
	f.lfWidth=0;                          // 宽度为默认
	setcolor(YELLOW);
	strcpy(f.lfFaceName, "微软雅黑");     // 设置字体为“微软雅黑”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式
	sprintf(str,"%.2f",getfps());
	outtextxy(10,10,str);
	return;
}
void howtoplay()                       // 载入说明界面 
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

void drawTriangle(int *a)              // 画复合三角形用于定位选项
{
	setcolor(BLUE);
	int p[6]={900-20,100+18,900+10,100+18-16,900+10,100+18+16};
	int q[6]={900-10,100+18,900+5,100+18-8,900+5,100+18+8};
	setfillcolor(BLUE);               // 设置填充色
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
	setcolor(YELLOW);                      // 设置字体颜色为黄色嘻嘻 
	switch(gamemode)
	{
		case 0: outtextxy(400,250,"①   同色相吸异色相吸"); break;  //gamemode的提示字符串的区别 
		case 1: outtextxy(400,250,"②   同色相吸异色相斥"); break;
		case 2: outtextxy(400,250,"③   同色相斥异色相吸"); break;
		case 3: outtextxy(400,250,"④   同色相斥异色相斥"); break;
	}
	switch(gravity)
	{
		case 1: outtextxy(400,350,"①   小行星"); break;           //gravity的提示字符串区别 
		case 2: outtextxy(400,350,"②   行星");   break;
		case 3: outtextxy(400,350,"③   恒星");   break;
		case 4: outtextxy(400,350,"④   中子星"); break;
		case 5: outtextxy(400,350,"⑤   黑洞");   break;
	}
	return;
	
}
void up(int *a)                           // up的事件 
{
	if(*a-1<0) *a=4;
	else *a-=1;
	return;
}

void down(int *a)                         // down的事件 
{
	if(*a+1>4) *a=0;
	else *a+=1;	
	return;
}

void enter(int *a)                        // enter的事件 
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

void startgame()                          // 正式游戏开始
{ 
	key_msg key_1={0};                    // 用于存储键盘1消息
	mouse_msg mouse_1={0};                // 
	int mouse_x=0;                        //   
	int mouse_y;
	char key;
//	char str1[10],str2[10];


	boarda.y=360;
	scorea=0;
	scoreb=0;                             // 初始化一些参数 
	while(1)                              // 这个循环用于处理键盘操作的消息 
	{
		cleardevice();                    // 清除整个界面
		draw_background();
		if(timer<0){
			boarda.m+=1;
			boardb.m+=1;
			timer=20;
		}
		

		if(kbmsg())  key_1=getkey();
		while(mousemsg()) mouse_1=getmouse();
		mousepos(&mouse_x,&boardb.y);
		
		ifcollide();                       // 碰撞检测 
		
		countgravity();                    // 计算引力 
			
		if(key_1.msg==key_msg_down){
			switch(key_1.key){
				case 'W': boarda.a=-3;           break;  // a板上移
				case 'S': boarda.a+=3;           break;  // a板下移
				case 'D': createa();             break;  // 生成球a
			}			
		}
		
		

		drawfps();
		calculateboarda();
		calculateboardb();
		
		
		
		if(mouse_1.is_down()&&boardb.m>3) {
			ball_createnewb(1100-boardb.m,boardb.y,-1-sqrt(boardb.m-2)*3.0,0,boardb.m-3,2);
		}
		
		if(kbhit())  key=getch();         // 捕获esc专用 
		if(key==key_esc){                 // 如果按了esc就退出到上一界面
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
	outtextxy(200,100,"这游戏怎么玩");    // 输出提示字体 
	outtextxy(200,200,"设置引力模式");
	outtextxy(200,300,"设置引力大小");
	outtextxy(200,400,"开始游戏");
	outtextxy(200,500,"返回桌面");
	drawTriangle(a);                      // 输出光标 
	drawYellowords();                     // 输出gamemode和gravity 
	return;	
}

void setfirstfont()
{                      // 字体总设置函数 
	setlinewidth(0);
	setcolor(GREEN);                      // 设置字体颜色为“绿色”
	LOGFONTA f;                           // 定义字体格式的结构体 
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight=36;                        // 设置字体高度为36
	f.lfWidth=0;                          // 宽度为默认 
	strcpy(f.lfFaceName, "微软雅黑");     // 设置字体为“微软雅黑”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式
	return;	
}
void mystart()                            // 生成启动选单的函数 
{
	int a=0;                              // a是设置指针的当前位置，起始位置为0即第一个设置
	char key;                             // 存储短的键盘敲击


	while(1)                              // 这个循环用于接收键盘消息来切换设置项目
	{
		
		cleardevice();                    // 清除整个界面 

        switch(key)
		{
        	case key_up:     up(&a);     break;
        	case key_down:   down(&a);   break;
        	case key_enter:  enter(&a);  break;
        	case key_esc:    return;
        }
        drawfps();                            // 左上角打印帧率
		setfirstfont();                       // 字体总设置
		draw_1_all(&a);                       // 画出当前界面所有元素
		key=getch();                          // 获取一次
		delay_fps(60);                        // 设置刷新率同时产生延时效果
		                                      // 注意延时一定要放在动画绘制完成后否则会发生闪屏
	}
}



	
int main()
{	
//	setinitmode(INIT_NOBORDER);        // 除去边框
	initgraph(1280, 720);              // 生成一个720P的画面
    setrendermode(RENDER_MANUAL);      // 设置手动刷新屏幕
	mystart();                         // 打开启动选单
	closegraph();                      // 关闭画板 
	return 0;
}

