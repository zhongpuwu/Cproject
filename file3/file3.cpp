
#include <graphics.h>

 

#include <stdio.h>

 

int main()

{

    initgraph(640, 480);

 

    setfont(18, 0, "����");

 

    mouse_msg msg = {0};

    /*mouse_msg��һ���ṹ��

    typedef struct mouse_msg

    {

        UINT msg;

        INT  x;

        INT  y;

        UINT flags;

        INT  wheel;

    }mouse_msg;

    ��һ��������memset(&msg,0,sizeof(struct mouse_msg));��һ����˼*/

    for ( ; is_run(); delay_fps(60))

    {

 

        while (mousemsg())//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ

        {

            msg = getmouse();//�������Ϣ�������ṹ��

        }

 

 

        cleardevice();//���ǰ��,������ϴεĽ��

        xyprintf(0, 0, "x = %10d  y = %10d",

                 msg.x, msg.y);

                 //��һ����ʾ���x,yλ��.

        xyprintf(0, 20, "move  = %d down  = %d up    = %d",

                 (int)msg.is_move(),

                 (int)msg.is_down(),

                 (int)msg.is_up());

                 //�ڶ�����ʾ����Ƿ��ж���,����״̬

        xyprintf(0, 40, "left  = %d mid   = %d right = %d",

                 (int)msg.is_left(),

                 (int)msg.is_mid(),

                 (int)msg.is_right());

                 //��������ʾ��걻���µİ���(��,��,��)

        xyprintf(0, 60, "wheel = %d  wheel rotate = %d",

                 (int)msg.is_wheel(),

                 msg.wheel);

                 //��������ʾ����λ��

    }

 

    closegraph();

    return 0;

}

