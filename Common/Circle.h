#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
struct Circle
{
    void Load(char* p)//ネットワークから受信したデータを変換して受け取る
    {
        Circle circle;//ネットワークのデータを入れる仮の構造体

        p++; // 受信データの先頭部分を無視する

        memcpy(&circle.color,p,sizeof(circle.color));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(&circle.x, p, sizeof(circle.x));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(&circle.y, p, sizeof(circle.y));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(&circle.r, p, sizeof(circle.r));

        //コピーしたデータをホストに変換して自身に代入
        color = ntohl(circle.color);
        x = ntohl(circle.x);
        y = ntohl(circle.y);
        r = ntohl(circle.r);
    }

    void Store(char* p)//ネットワークに送信するデータを変換して送る
    {
        Circle circle;//ネットワークのデータを入れる仮の構造体
        memcpy(p,&circle.color, sizeof(circle.color));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(p, &circle.x, sizeof(circle.x));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(p, &circle.y, sizeof(circle.y));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(p, &circle.r, sizeof(circle.r));

        //コピーしたデータをホストに変換して自身に代入
        color = htonl(circle.color);
        x = htonl(circle.x);
        y = htonl(circle.y);
        r = htonl(circle.r);
    }

    int color;
    int x;
    int y;
    int r;
};
