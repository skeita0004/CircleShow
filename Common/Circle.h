#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
struct Circle
{
    void Load(const char* p)//ネットワークから受信したデータを変換して受け取る
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
        //コピーしたデータをホストに変換して自身に代入
        color = htonl(color);
        x = htonl(x);
        y = htonl(y);
        r = htonl(r);

        memcpy(p,&color, sizeof(color));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(p, &x, sizeof(x));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(p, &y, sizeof(y));
        for (int i = 0; i < sizeof(int);i++)
        {
            p++;
        }
        memcpy(p, &r, sizeof(r));
    }

    unsigned int color;
    int x;
    int y;
    int r;
};
