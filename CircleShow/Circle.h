#pragma once
struct Circle
{
    void Load(char* p);//ネットワークから受信したデータを変換して受け取る
    void Store(char* p);//ネットワークに送信するデータを変換して送る
    int color;
    int x;
    int y;
    int r;
};
