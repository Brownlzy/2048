#pragma once
#include <list>
#include <vector>

class Operate
{ 
public:
	std::vector<int> vec;
	enum OperateMethod{MOVE,MERGE,NEW};
	Operate(std::vector<int> vector){vec = vector;}
	virtual OperateMethod getMethod()=0;
	virtual std::vector<int> getPoint1()=0;
	virtual std::vector<int> getPoint2()=0;
	virtual std::vector<int> getPoint3()=0;
	virtual int getValue()=0;
};
class MoveTo :protected Operate {
public:
	MoveTo(int fx,int fy,int tx,int ty,int value) 
		:Operate(std::vector<int>{ fx,fy,tx,ty,value }){}
	std::vector<int> getPoint1() { return std::vector<int>{vec.at(0),vec.at(1) }; }
	std::vector<int> getPoint2() { return std::vector<int>{vec.at(2),vec.at(3) }; }
	std::vector<int> getPoint3() { return std::vector<int>{0,0};}
	int getValue() { return vec.at(4); }
	OperateMethod getMethod() {
		return MOVE;
	}
};
class MergeTo :protected Operate {
public:
	MergeTo(int x1,int y1,int x2,int y2,int dx,int dy,int value)
		:Operate(std::vector<int>{ x1,y1,x2,y2,dx,dy,value }){}
	std::vector<int> getPoint1() { return std::vector<int>{vec.at(0), vec.at(1) }; }
	std::vector<int> getPoint2() { return std::vector<int>{vec.at(2), vec.at(3) }; }
	std::vector<int> getPoint3() { return std::vector<int>{vec.at(4), vec.at(5) }; }
	int getValue() { return vec.at(6); }
	OperateMethod getMethod() {
		return MERGE;
	}
};
class NewIn :protected Operate {
public:
	NewIn(int x,int y,int value)
		:Operate(std::vector<int>{ x,y,value }){}
	std::vector<int> getPoint1() { return std::vector<int>{vec.at(0), vec.at(1) }; }
	std::vector<int> getPoint2() { return std::vector<int>{0, 0}; }
	std::vector<int> getPoint3() { return std::vector<int>{0, 0}; }
	int getValue() { return vec.at(2); }
	OperateMethod getMethod() {
		return NEW;
	}
};
class OperateList
{
private:
	std::list<Operate*> operateList;

public:
	void clear();
	void addOperate(Operate* p);
	int getCount();
};

