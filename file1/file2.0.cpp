/*
         written by dfdfdfff 没有授权禁止转载 
*/



#include "graphics.h"                  // 需要引用的图形库
#include <stdio.h>                     // 不必要的字符串处理
#include <stdlib.h>
#include <math.h>                      // 数学函数
#include <time.h>                      // 随机数生成需要 
#define Number 50                      // 球球缓冲区的大小 够用了 再大要卡的 
#define Ro 15                          // 用于计算球的半径的密度系数 公式为r=Ro*log10(m) 



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
	int explode;                       // 是否爆炸 
} *a[Number];                          // 小球的结构 同时生成一个存放所有球的指针数组 是游戏的主体数据结构
                                       // 但是不分配内存空间 所以要在发射和产生小球时使用malloc函数为每个小球分配内存 
                                       // 最后还需要free回收内存避免内存泄露
                                        
struct boardaa{                        // a板的结构体 
	float m;                           // a板的质量 
	float y;                           // a板的纵向位置 
	float v;                           // a板的纵向速度 
	float a;                           // a板的纵向加速度 
	color_t color;                     // a板的颜色 
	int able;                          // a板的是否瘫痪的状态 
} boarda={3,360,0,0,EGERGB(0xff,0x80,0x26),1};      // a板的实例即分配了内存空间的a板 
 
struct boardbb{                        // b板的结构体
	float m;                           // b板的质量          
	float y;                           // b板的纵向位置      
	float v;                           // b板的纵向速度      
	float a;                           // b板的纵向加速度    
	color_t color;                     // b板的颜色          
	int able;                          // b板的是否瘫痪的状态
} boardb={3,360,0,0,EGERGB(0x4f,0xff,0xf9),1};      // b板的实例即分配了内存空间的b板 


                                       // 全局变量表
int gamemode=0;                        // 用于存放引力模式
int gravity=3;                         // 存放引力大小
int timer=20;                          // 板生长的缓时
int timera=-1;
int timerb=-1;                         // ab板瘫痪后的冷却时间
int win=0;                             // 判断胜负 
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
void awin();                           // a赢时展示的界面
void bwin();                           // b赢时展示的界面


/*-------------------------------变量结构定义部分以及函数原型部分结束----------------------------------*/ 
/*-----------------------------------------以下是游戏主题部分------------------------------------------*/ 


void awin(){
    setfontbkcolor(EGERGB(0x00,0x00,0x66));// 设置文字的背景色 
    setcolor(EGERGB(0xff,0x80,0x26));      // 设置字体颜色为a的颜色
	LOGFONTA f;                            // 定义字体格式的结构体 
	getfont(&f);                           // 获取当前字体设置
	f.lfHeight=80;                         // 设置字体高度为36
	f.lfWidth=0;                           // 宽度为默认 
	strcpy(f.lfFaceName, "楷体_GB2312");   // 设置字体为“楷体_GB2312”
	f.lfQuality = ANTIALIASED_QUALITY;     // 设置输出效果为抗锯齿  
	setfont(&f);                           // 保存字体样式
	outtextxy(480,200,"红色赢了");
	outtextxy(280,400,"按esc或enter键退出"); 
    return;                                //红色方即a方赢了时的字体设置 
}

void bwin(){
    setfontbkcolor(EGERGB(0x00,0x00,0x66));// 设置文字的背景色
	setcolor(EGERGB(0x4b,0xff,0xf9));      // 设置字体颜色为a的颜色
	LOGFONTA f;                            // 定义字体格式的结构体 
	getfont(&f);                           // 获取当前字体设置
	f.lfHeight=80;                         // 设置字体高度为100
	f.lfWidth=0;                           // 宽度为默认 
	strcpy(f.lfFaceName, "楷体_GB2312");   // 设置字体为“楷体_GB2312”
	f.lfQuality = ANTIALIASED_QUALITY;     // 设置输出效果为抗锯齿  
	setfont(&f);                           // 保存字体样式
	outtextxy(480,200,"蓝色赢了");
	outtextxy(280,400,"按esc或enter键退出"); 
    return;                                // 蓝色方即b方赢了时的字体设置
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
}                                      // 以纵向进度条的形式展示ab的得分 

void countgravity(){
	float gx,gy,F,x;
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;       // 所有的continue都是为了避免非法的内存访问 即访问到没有任何数据的”小球“ 
		a[i]->ax=0;
		a[i]->ay=0;
		for(int j=0;j<Number;j++){
			if(a[j]==NULL||j==i) continue;     // 防止自己和自己产生引力即排除i==j时的情况 
			x=pow((a[i]->x-a[j]->x),2)+pow((a[i]->y-a[j]->y),2);
			gx=a[j]->m*gravity*(a[j]->x-a[i]->x)/x;
			gy=a[j]->m*gravity*(a[j]->y-a[i]->y)/x;
			switch(gamemode){
				case 0: a[i]->ax+=gx; a[i]->ay+=gy; break;
				case 1: a[i]->color==a[j]->color? a[i]->ax+=gx,a[i]->ay+=gy:a[i]->ax-=gx,a[i]->ay-=gy; break;
				case 2: a[i]->color==a[j]->color? a[i]->ax-=gx,a[i]->ay-=gy:a[i]->ax+=gx,a[i]->ay+=gy; break;
				case 3: a[i]->ax-=gx; a[i]->ay-=gy; break;
				case 4: break;                 // 根据gamemode的值判断是引力还是斥力gamemode==4表示没有引力 所以不载入数据直接break 
			}			
		}
	}
	return;                            // 字如其名 计算所有小球间的引力或斥力 
} 

void ifcollide(){                      // 复杂的碰撞检测 
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		if(a[i]->y-a[i]->r<20) a[i]->vy=fabs(a[i]->vy);
		if(a[i]->y+a[i]->r>700) a[i]->vy=-fabs(a[i]->vy);// 上下边界的碰撞检测 
		if(a[i]->x-a[i]->r<180&&a[i]->y>boarda.y-80&&a[i]->y<boarda.y+80) {
		    if(a[i]->explode){                           // 球与板的碰撞检测
		        boarda.able=0;                           // 为了达到游戏效果每个板需要做两次碰撞检测 
		        timera=120;                              // 要实现爆炸弹球的无敌状态 
			    scoreb+=a[i]->m;                         // 没有被板接住的小球将被 回收内存并计分 
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
			continue;                  //写这么长无非是想实现球和板的碰撞 和计分效果 
		}
		//-----------------------------分界线 上面是a板的碰撞检测 下面是b板的碰撞检测 
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
		for(int j=0;j<Number;j++){       // 开启一个新的循环用于检测球之间的碰撞 
			if(j==i||a[j]==NULL||a[i]==NULL) continue;
			if(sqrt(pow(a[i]->x-a[j]->x,2)+pow(a[i]->y-a[j]->y,2))<a[i]->r+a[j]->r){
				if(a[i]->m<a[j]->m||a[i]->color==a[j]->color){
					ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,a[j]->color);
				}else if(a[i]->m>a[j]->m){
					ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,a[i]->color);
				}else if(a[i]->color!=a[j]->color){
				    ball_create(a[i]->x,a[j]->x,a[i]->y,a[j]->y,a[i]->vx,a[j]->vx,a[i]->vy,a[j]->vy,a[i]->m,a[j]->m,rand()%2+1);
                }                        // 两个球质量相等就随机颜色 
				free(a[i]);              // 写这么长无非就是为了判断碰撞融合后的小球的颜色 其他没有区别 
				a[i]=NULL;
				free(a[j]);
				a[j]=NULL;               // 最后释放相互碰撞的小球的存储空间 
				continue;                // 不用担心碰撞融合后的新球将以新的参数加入数组中 
			}
		}
	}
	return;
}

void draw_balls(){                       // 画出小球
	setlinewidth(0);                     // 小球使用椭圆函数画出 所以要规定非描边的状态 
	color_t b;
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		if(a[i]->m>18) {
		    a[i]->explode=1;             // 球球发生了爆炸 
		    a[i]->m=18;                  // 限制球球的大小8
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
            if(a[i]->explode){           // 闪烁显示爆炸状态的弹球 
			    b=RGB(rand()%256,rand()%256,rand()%256);
			    setcolor(b);             // 其实是随机产生一个颜色值快速变化产生闪烁的效果 
			    setfillcolor(b);
            }else{
			    setcolor(boardb.color);
			    setfillcolor(boardb.color);              
            }
			fillellipse(a[i]->x,a[i]->y,a[i]->r,a[i]->r);
		}

	}
	return;                              // 爆炸状态的弹球需要闪烁显示 
}                                        // 字如其名 绘制出屏幕上的所有弹球 但是要判断是不是爆炸状态 

void ball_go(){
	for(int i=0;i<Number;i++){
		if(a[i]==NULL) continue;
		a[i]->vx+=a[i]->ax;
		a[i]->vy+=a[i]->ay;
		a[i]->x+=a[i]->vx;
		a[i]->y+=a[i]->vy;
		a[i]->ax=0;a[i]->ay=0;
	}
	return;                              // 字如其名 计算弹球的运动轨迹 但不包含碰撞检测 
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
		    a[i]->explode=0; 
			break;
		}	
	}
	boarda.m=3;	
	return;                                                    // 详见b板球的发射函数 两者没有区别 
}
void ball_createnewb(float x,float y,float vx,float vy,float m,int color){ 
	for(int i=0;i<Number;i++){                                 // 遍历所有结构体指针数组 
		if(a[i]==NULL){                                        // 如果当前结构体指针数组内存的空间为空闲就储存在当前位置 
			a[i]=(struct ball*)malloc(sizeof(struct ball));    // 为球球分配内存空间 
			a[i]->x=x;
			a[i]->y=y;
			a[i]->vx=vx;
			a[i]->vy=vy;               // 载入计算好的各个参数 
			a[i]->m=m;                 // 球的质量等于板的生长量 球的速度取决于板此时的移动速度 
			a[i]->r=Ro*log10(m+1);     // 载入计算好的弹球大小 
			a[i]->color=color;         // 载入颜色 
			a[i]->explode=0;           // 载入判定爆炸的系数 
			break;
		}	
	}
	boardb.m=3;	
	return;                            // 这个函数专用于b板发射弹球时使用 
}

void draw_boards(){                    // 绘制两个板
	if(boarda.m>8){
		boarda.m=8;
	}
	if(boardb.m>8){                                                  // 限制两个板的最大宽度 
		boardb.m=8;
	}
	                                                                 // 判断ab板是不是瘫痪了 
	if(boarda.able) setfillcolor(YELLOW);                            // 瘫痪就产生闪烁效果 
    else setfillcolor(RGB(rand()%256,rand()%256,rand()%256));
    
	bar(181-boarda.m,boarda.y-82,180+boarda.m,boarda.y+82);
	
	if(boardb.able) setfillcolor(LIGHTBLUE);
    else setfillcolor(RGB(rand()%256,rand()%256,rand()%256));        // 设置板的填充色	
	
	bar(1101-boardb.m,boardb.y-82,1100+boardb.m,boardb.y+82);
	return;
}

void calculateboarda(){                // 板a的运动轨迹 详见板b的运动轨迹说明 两者没有区别 
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

void calculateboardb(){                // 板b的运动轨迹的计算 最终旨在得到ab板的垂直方向位置 
	if(boardb.a==0){
		if(boardb.v<0) boardb.a=3.0;
		else if(boardb.v>0) boardb.a=-3.0;
		else boardb.a=0;               // 产生摩擦减速的效果 
	}
	boardb.v+=boardb.a;                // 加速度值加载到速度值上 
	if(fabs(boardb.v)>27){
		if(boardb.v>0) boardb.v=27;
		else boardb.v=-27;
	}
	boardb.y+=boardb.v;                // 速度值加载到位置值上 
	boardb.a=0;                        // 加速度是瞬时产生的所以清零 
	if(boardb.y>694-80) {              // ab板碰到边界后的效果 
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
	float vx=(m_vx1+m_vx2)/(m1+m2),vy=(m_vy1+m_vy2)/(m1+m2);// 定义变量时就使用动量守恒计算出新球的速度 
	if(m1>m2){
		x3=x1;y3=y1;
	}else if(m2>m1){
		x3=x2;y3=y2;
	}else{                                                 // 判断碰撞后的小球谁被吸收 就大原则 相等取中间值 
		x3=(x1+x2)/2;                                      // x3还y3用于存放新球的位置 
		y3=(y1+y2)/2;
	}
	for(int i=0;i<Number;i++){
		if(a[i]!=NULL) continue;                           // 如果结构体指针的内容为NULL就跳过 避免非法的内存访问 
		a[i]=(struct ball*)malloc(sizeof(struct ball));    // 为球球分配内存空间 
		a[i]->x=x3;
		a[i]->y=y3;
		a[i]->vx=vx;
		a[i]->vy=vy;
		a[i]->m=m1+m2; 
		if(a[i]->m>18) a[i]->m=19;
		a[i]->r=Ro*log10(a[i]->m+1);
		a[i]->color=color;
		a[i]->explode=0;                 // 为新球载入计算好的参数 
		break;
	}
	return;                              // 这个函数专用于生成互相碰撞后产生新球 
}                                        // 根据动量守恒求解生成的球位置和速度 

void draw_background(){                  // 画出游戏的背景板 包括蓝色画布 矩形框边界和ab板的轨道 
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

void drawfps()                          // 左上角打印帧率
{
	char str[8];
	setfontbkcolor(BLACK);              // 设置文字的背景色
	LOGFONTA f;                         // 定义字体格式的结构体 
	getfont(&f);                        // 获取当前字体设置
	f.lfHeight=20;                      // 设置字体高度为36
	f.lfWidth=0;                        // 宽度为默认
	setcolor(YELLOW);                   // 设置字体颜色 
	strcpy(f.lfFaceName, "微软雅黑");   // 设置字体为“微软雅黑”
	f.lfQuality = ANTIALIASED_QUALITY;  // 设置输出效果为抗锯齿  
	setfont(&f);                        // 设置字体样式
	sprintf(str,"%.2f",getfps());
	outtextxy(10,10,str);
	return;
}
void howtoplay()                        // 载入说明界面 
{
	char key; 
	outtextxy(10,10,"1 操作键有 w  s  d 和方向键上下左 其中 d 和左是用来发射小球 移动板可以给小球提供纵向的速度。\n");
	outtextxy(10,50,"2 当你不发射小球的时候板会蓄力 下一次发射出来的小球的速度和大小会随时间的推移而变大。\n");
	outtextxy(10,90,"3 当球打到板后面的时候能量槽会收集小球的能量 当有一方的能量槽集满时对方就赢了游戏结束。\n");
	outtextxy(10,130,"4 本游戏可以调节小球之间的作用是相斥还是相吸 还有引力的大小以提供多种玩法。\n");
	while(1){
		key=getch();                    // 接收键盘消息用于退出说明界面 
		if(key==key_esc||key==key_enter) break;
	}
	cleardevice();
	return; 
}

void drawTriangle(int *a)               // 画蓝色指针用于定位选项
{
	setcolor(BLUE);
	int p[6]={900-20,100+18,900+10,100+18-16,900+10,100+18+16};
	int q[6]={900-10,100+18,900+5,100+18-8,900+5,100+18+8};
	setfillcolor(BLUE);                 // 设置填充色为蓝色指针的位置和*a的值有关 
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

void drawYellowords(){                     // 打印出黄色的gamemode和gravity的值 
	setcolor(YELLOW);                      // 设置字体颜色为黄色嘻嘻 
	switch(gamemode)                                                // 都只与全局部变量gamemode和gravity的数值有关 
	{
		case 0: outtextxy(400,250,"①   同色相吸异色相吸"); break;  // gamemode的选择
		case 1: outtextxy(400,250,"②   同色相吸异色相斥"); break;
		case 2: outtextxy(400,250,"③   同色相斥异色相吸"); break;
		case 3: outtextxy(400,250,"④   同色相斥异色相斥"); break;
		case 4: outtextxy(400,250,"⑤   无引力"); break;
	}
	switch(gravity)
	{
		case 1: outtextxy(400,350,"①   小行星"); break;            // gravity的等级 
		case 2: outtextxy(400,350,"②   行星");   break;
		case 3: outtextxy(400,350,"③   恒星");   break;
		case 4: outtextxy(400,350,"④   中子星"); break;
		case 5: outtextxy(400,350,"⑤   黑洞");   break;
	}
	return;
	
}
void up(int *a)                            // up的事件：蓝色指针上移 
{
	if(*a-1<0) *a=4;
	else *a-=1;
	return;
}

void down(int *a)                          // down的事件：蓝色指针下移 
{
	if(*a+1>4) *a=0;
	else *a+=1;	
	return;
}

void enter(int *a)                         // enter的事件 
{
	if(*a==0){                             // 蓝色指针在“这游戏怎么玩“位置 
		howtoplay();                       // 切换进游戏说明界面 
	}else if(*a==1){                       // 蓝色指针在“设置引力模式”位置 
		if(gamemode+1>4) gamemode=0;
		else gamemode+=1;
	}else if(*a==2){                       // 蓝色指针在“设置引力大小”位置 
		if(gravity+1>5) gravity=1;         // 切换引力大小 
		else gravity+=1;
	}else if(*a==3){                       // 蓝色指针在“开始游戏位置” 
		startgame();
		cleardevice();
		setfirstfont();                    // 清屏和设置菜单的字体样式 
	}else if(*a==4) exit(0);               // 蓝色指针在“结束游戏”位置 
	return;
}

void createa(){                            // 发射a球 
	if(boarda.m>3)  ball_createnewa(180+boarda.m,boarda.y,pow(boarda.m-2,1.7),boarda.v/2,boarda.m-3,1);
	return;
}

void createb(){                            // 发射b球 
	if(boardb.m>3)  ball_createnewb(1100-boardb.m,boardb.y,-pow(boardb.m-2,1.7),boardb.v/2,boardb.m-3,2);
	return;
}

void startgame()                           // 正式游戏开始
{
	char key;                              // 用于捕获esc和enter的消息 
//	char str1[10],str2[10];

    srand(time(NULL));                     // 初始化随机数种子 
	boarda.y=360;boarda.able=1;boarda.m=3;
	boardb.y=360;boardb.able=1;boardb.m=3;
	scorea=0;                             
	scoreb=0;                              // 初始化ab的得分 
    win=0;                                 // 初始化一些参数包括板的初始位置 板的非瘫痪状态和板的质量 
	while(1)                               // 这个循环用于处理键盘操作的消息 
	{
		cleardevice();                     // 清除整个界面
		draw_background();
		if(win){                           // 判断是不是产生了赢家如果是就执行if下的内容 
		    cleardevice();                 // 清除整个界面
		    draw_background();
		    if(win==1)  awin();            // 判断a赢还是b赢 
		    else bwin();
		    draw_boards();
		    showscoreab();
		    drawfps();
		    if(kbhit())  key=getch();      // 捕获esc和enter专用 
		    if(key==key_esc||key==key_enter) goto pos_2; // 如果按了esc或enter就退出到上一界面
		    delay_fps(60);                 // 必要的延时显示 
		    continue;
        }
		
		if(timer<0){                       // ab板的生长计时 
			boarda.m+=1;
			boardb.m+=1;
			timer=20;
		}
		if(timera<0) boarda.able=1;
		else timera--;                    
		if(timerb<0) boardb.able=1;        // 如果ab处于不瘫痪状态就不计时 
		else timerb--;                     // ab板瘫痪的计时器 
		
		ifcollide();                       // 碰撞检测+生成新球+爆炸球的吸收检测 
		
		countgravity();                    // 计算引力 
			

		
		drawfps();                         // 左上角打印帧率 正常情况下为59~61帧 归功于键盘消息接收采用的都是非阻塞函数 
		calculateboarda();
		calculateboardb();                 // 计算ab的运动轨迹 
		
		if(kbhit())  key=getch();          // 捕获esc专用 避免阻塞的函数kbhit() 
		if(key==key_esc){                  // 如果按了esc就退出到上一界面
		    pos_2:
			for(int i=0;i<Number;i++){     // 释放所有小球占用的内存 
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
		if(GetAsyncKeyState(VK_LEFT)&0x8000&&boardb.able) createb();           //读取键盘的状态
		
        // 这样说其实太笼统 其实这个函数是直接读取物理键盘的状态 即指定键按下还是抬起
        // 然后使用系统的虚拟逻辑键盘接收消息 所以避免了冲突问题 顺便支持了中文输入法下的操作
        // 而不是用以前的方法用getch()获得指定字符 否则将会产生严重的键盘消息冲突问题 而且不阻塞程序的运行 方便统计帧率 
 

		showscoreab();                     // 展示ab的得分
	
		ball_go();                         // 计算小球的运动轨迹 
			
		draw_balls();                      // 画出所有小球 
		
		draw_boards();                     // 画出所有板
         	
//		sprintf(str1,"%d",boarda.y);
//	    sprintf(str2,"%d",boardb.y);
//	    outtextxy(100,boarda.y,str1);
//	    outtextxy(1000,boardb.y,str2);

		timer--;                           // ab板生长的计时器自减 

		delay_fps(60);                     // 必要的延时显示 
	}
}

void draw_1_all(int *a)                    // 输出选项菜单的全部内容 
{
	outtextxy(200,100,"这游戏怎么玩");     // 输出提示字体 
	outtextxy(200,200,"设置引力模式");
	outtextxy(200,300,"设置引力大小");
	outtextxy(200,400,"开始游戏");
	outtextxy(200,500,"返回桌面");         // 输出不改变的绿色标签字 
	drawTriangle(a);                       // 输出光标 
	drawYellowords();                      // 输出gamemode和gravity值的黄子 
	return;
}

void setfirstfont()
{                      // 字体总设置函数
    setfontbkcolor(BLACK);                 // 设置文字背景色 
	setlinewidth(0);                       // 设置线宽 
	setcolor(GREEN);                       // 设置字体颜色为“绿色”
	LOGFONTA f;                            // 定义字体格式的结构体 
	getfont(&f);                           // 获取当前字体设置
	f.lfHeight=36;                         // 设置字体高度为36
	f.lfWidth=0;                           // 宽度为默认 
	strcpy(f.lfFaceName, "微软雅黑");      // 设置字体为“微软雅黑”
	f.lfQuality = ANTIALIASED_QUALITY;     // 设置输出效果为抗锯齿  
	setfont(&f);                           // 设置字体样式
	return;	
}
void mystart()                             // 生成启动选单的函数 
{
	int a=0;                               // a是设置指针的当前位置，起始位置为0即第一个设置
	char key;                              // 存储短的键盘敲击


	while(1)                               // 这个循环用于接收键盘消息来切换设置项目
	{
		
		cleardevice();                     // 清除整个界面 

        switch(key)                              // 对接收到的键盘字符进行判断 
		{
        	case key_up:     up(&a);     break;  // 上移蓝色指针 
        	case key_down:   down(&a);   break;  // 下移蓝色指针 
        	case key_enter:  enter(&a);  break;  // enter键选择或切换蓝色指针指向的选项 
        	case key_esc:    return;          // 如果按了esc就退出这个函数然后正常退出程序 
        }                                  //getch()是通过阻塞方法读取字符所以统计帧率没有意义 
         
        drawfps();                         // 左上角打印帧率
		setfirstfont();                    // 字体总设置
		draw_1_all(&a);                    // 画出当前界面所有元素
		key=getch();                       // 获取一次
		delay_fps(60);                     // 设置刷新率同时产生延时效果
		                                   // 注意延时一定要放在动画绘制完成后否则会发生闪屏
	}
}




int main()
{
//	setinitmode(INIT_NOBORDER);            // 除去ds边框
	initgraph(1280, 720);                  // 生成一个720P的画面
    setrendermode(RENDER_MANUAL);          // 设置手动刷新屏幕
	mystart();                             // 打开启动选单
	closegraph();                          // 关闭画板 
	return 0;                              // 正常退出程序 
}

