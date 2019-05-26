
#include <graphics.h>

 

#include <stdio.h>

 

int main()

{

    initgraph(640, 480);

 

    setfont(18, 0, "宋体");

 

    mouse_msg msg = {0};

    /*mouse_msg是一个结构体

    typedef struct mouse_msg

    {

        UINT msg;

        INT  x;

        INT  y;

        UINT flags;

        INT  wheel;

    }mouse_msg;

    这一步操作和memset(&msg,0,sizeof(struct mouse_msg));是一个意思*/

    for ( ; is_run(); delay_fps(60))

    {

 

        while (mousemsg())//获取鼠标消息，这个函数会等待，等待到有消息为止

        {

            msg = getmouse();//将鼠标信息存入鼠标结构体

        }

 

 

        cleardevice();//清空前景,即清空上次的结果

        xyprintf(0, 0, "x = %10d  y = %10d",

                 msg.x, msg.y);

                 //第一行显示鼠标x,y位置.

        xyprintf(0, 20, "move  = %d down  = %d up    = %d",

                 (int)msg.is_move(),

                 (int)msg.is_down(),

                 (int)msg.is_up());

                 //第二行显示鼠标是否有动作,按键状态

        xyprintf(0, 40, "left  = %d mid   = %d right = %d",

                 (int)msg.is_left(),

                 (int)msg.is_mid(),

                 (int)msg.is_right());

                 //第三行显示鼠标被按下的按键(左,中,右)

        xyprintf(0, 60, "wheel = %d  wheel rotate = %d",

                 (int)msg.is_wheel(),

                 msg.wheel);

                 //第四行显示滚轮位置

    }

 

    closegraph();

    return 0;

}

