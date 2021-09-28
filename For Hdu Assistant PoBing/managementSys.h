//PoBingSystem
// Created by Fre_Melody on 2021/9/25.
//9.25 简单定义, 网上各种找资料，c++基本没有什么好的方法，还是不会, 估计只能做最基础的部分，
// 菜菜，没有学过go\java\数据库\各种框架，也没学过计网（总计4h，好像没有搜索到什么有用的）
//9.26 读取数据的函数，= 重载, 有个问题, 设计简陋的交互simplePrintOne（群里面全大佬，反正跪下就行了。。。。）
//9.27 设计并测试随机函数QandA(并没有测试，好吧）
//9.28 完成了我目前水平能做到的，基本上还是菜鸡水平；主要进行了部分修改，测试
//不会数据库，或者其他的存储方式，只能读取文本，太菜了，目前c++水平实现，基本就这样了

#ifndef POBING_MANAGEMENTSYS_H
#define POBING_MANAGEMENTSYS_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <random>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Person
{
public:
    Person(){};

    Person(string oneId, string oneName, string oneDepartment, string oneStuNumber, string oneImg);

    void operator=(const Person &one); //问题：传引用时，结合sort函数会报错，现在加了const 貌似又可以了

    friend bool Initial(vector<Person> &rhs);

    string GetID();

    string GetName();

    string GetImg();

    string GetStuNumber();

    string GetDepartment();

    bool FindName(const vector<Person> &ones, string &value);

    //实际上，这个应该没有意义，不可能utl比较，也不可能用来查找
    bool FindImgUrl(const vector<Person> &ones, string &value);

    bool FindID(const vector<Person> &ones, string &value);

    bool FindStuNumber(const vector<Person> &ones, string &value);

    bool FindDepartment(const vector<Person> &ones, string &value);

    bool Find(vector<Person> &ones, string &key, string &value);

    friend bool cmp(Person a, Person b); //用于按学号排序

    friend bool ReadData(vector<Person> &ones);

    ~Person(){};

private:
    string ID;
    string name;
    string department;
    string stuNumber;
    string imgUrl; //图像地址，不会处理图像，应该可以通过网页打开
};

bool MainFunc(vector<Person> &wrongChoose, map<char, Person> ans);

//vector<Person> Rand(vector<Person> &ones);//可以不用这种方法实现

vector<int> Random(int n);

Person displays(vector<Person> &ones); //好像没有用来着

bool IfContinue();

#endif //POBING_MANAGEMENTSYS_H
