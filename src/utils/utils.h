#ifndef UTILS_H
#define UTILS_H
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "http/http_conn.h"
#include "log/log.h"
#include "tinywebserver/global.h"
BEGIN_TINYWEBSERVER_NAMESPACE
class UtilTimer;
struct ClientData
{
    sockaddr_in address;
    int sockfd;
    UtilTimer* timer;
};

class UtilTimer
{
  public:
    UtilTimer()
        : prev(NULL)
        , next(NULL)
    {
    }

  public:
    time_t expire;

    void (*cb_func)(ClientData*);
    ClientData* user_data;
    UtilTimer* prev;
    UtilTimer* next;
};
class TimerManager
{
  public:
    TimerManager();
    ~TimerManager();

    void add_timer(UtilTimer* timer);
    void adjust_timer(UtilTimer* timer);
    void del_timer(UtilTimer* timer);
    void tick();

  private:
    void add_timer(UtilTimer* timer, UtilTimer* lst_head);

    UtilTimer* head;
    UtilTimer* tail;
};

class Utils
{
  public:
    Utils() = default;
    ~Utils() {}

    void init(int timeslot);

    //对文件描述符设置非阻塞
    int setnonblocking(int fd);

    //将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
    void addfd(int epollfd, int fd, bool one_shot, int TRIGMode);

    //信号处理函数
    static void sig_handler(int sig);

    //设置信号函数
    void addsig(int sig, void(handler)(int), bool restart = true);

    //定时处理任务，重新定时以不断触发SIGALRM信号
    void timer_handler();

    void show_error(int connfd, const char* info);

  public:
    TimerManager m_timer_lst;

    int m_TIMESLOT;
    static int* u_pipefd;
    static int u_epollfd;
};

// void cb_func(ClientData* user_data);

void inline cb_func(ClientData* user_data)
{
    epoll_ctl(Utils::u_epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    close(user_data->sockfd);
    HttpConn::m_user_count--;
}
END_TINYWEBSERVER_NAMESPACE
#endif