#ifndef _ppMediaQueue_H_
#define _ppMediaQueue_H_

#include <queue>

struct AVPacket;
struct AVFrame;

template <class T>
class ppMediaPacketQueue<T>
{
public:
	ppMediaPacketQueue();
	~ppMediaPacketQueue();

public:
	std::queue<T *> pkts;

public:
	void push(T *pkt);
	T * top();
	void pop();

private:
};

#endif//_ppMediaQueue_H_
