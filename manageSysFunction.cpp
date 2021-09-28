// poBingSys（并不是）
// Created by MelodyInFolwingTime on 2021/9/25.
//  实际上叫：随机抽卡，选择题程序比较好

#include "managementSys.h"

Person::Person(string oneId, string oneName, string oneDepartment,
               string oneStuNumber, string oneImg) : ID(oneId), name(oneName),
                                                     department(oneDepartment), stuNumber(oneStuNumber),
                                                     imgUrl(oneImg) {}

void Person::operator=(const Person &ones)
{
    ID = ones.ID;
    name = ones.name;
    department = ones.department;
    stuNumber = ones.stuNumber;
    imgUrl = ones.imgUrl;
}

string Person::GetID()
{
    return ID;
}

string Person::GetName()
{
    return name;
}

string Person::GetImg()
{
    return imgUrl;
}

string Person::GetStuNumber()
{
    return stuNumber;
}

string Person::GetDepartment()
{
    return department;
}

bool Person::FindName(const vector<Person> &ones, string &value)
{
    for (int i = 0; i < ones.size(); ++i)
    {
        if (ones[i].name == value)
            return true;
    }
    return false;
}

bool Person::FindID(const vector<Person> &ones, string &value)
{
    for (int i = 0; i < ones.size(); ++i)
    {
        if (ones[i].ID == value)
            return true;
    }
    return false;
}

bool Person::FindImgUrl(const vector<Person> &ones, string &value)
{
    for (int i = 0; i < ones.size(); ++i)
    {
        if (ones[i].imgUrl == value)
            return true;
    }
    return false;
}

bool Person::FindStuNumber(const vector<Person> &ones, string &value)
{
    for (int i = 0; i < ones.size(); ++i)
    {
        if (ones[i].stuNumber == value)
            return true;
    }
    return false;
}

bool Person::FindDepartment(const vector<Person> &ones, string &value)
{
    for (int i = 0; i < ones.size(); ++i)
    {
        if (ones[i].department == value)
            return true;
    }
    return false;
}

bool Person::Find(vector<Person> &ones, string &key, string &value)
{
    if (key == "name")
        return FindName(ones, value);
    else if (key == "ID")
        return FindID(ones, value);
    else if (key == "Img")
        return FindImgUrl(ones, value);
    else if (key == "StuNumber")
        return FindStuNumber(ones, value);
    //    else if (key == "Department")//只有这几个数据
    else
        return FindDepartment(ones, value);
}

//用于ID排序
bool cmp(Person a, Person b) { return a.ID < b.ID; }

//以下两种方法可以暂时不用

// Person Random(const vector<Person> &ones) {
//    default_random_engine e;
//    uniform_int_distribution<unsigned> x;
//    int i = x(e) % ones.size();
//    return ones[i];
// }

// Person Random(const vector<Person> &ones)
// {
//     time_t t;
//     srand((unsigned)time(&t));
//     int i = rand() % (ones.size());
//     return ones[i];
// }

vector<int> Random(int n)
{
    srand((unsigned)time(0));
    vector<int> r(4);
    for (int i = 0; i < 4; ++i)
    {
        r[i] = rand() % n;
        for (int j = 0; j < i; j++)
        {
            while (r[i] == r[j])
                r[i] = rand() % n;
        }
    }

    return r;
}

//使用了不同函数

// vector<int> Random(int n)
// {
//     default_random_engine e;
//     uniform_int_distribution<unsigned> x;
//     vector<int> r(4);
//     for (int i = 0; i < 4; ++i)
//     {
//         for (int j = 0; j < i; j++)
//         {
//             while (r[i] == r[j])
//                 r[i] = x(e) % n;
//         }
//     }
//     return r;
// }

bool Initial(vector<Person> &ones)
{
    bool flag = ReadData(ones);
    //按Id排个序
    sort(ones.begin(), ones.end(), cmp);
    return flag;
}

bool ReadData(vector<Person> &ones)
{
    Person temp;
    // 以读模式打开文件
    ifstream infile;
    cout << "Reading from the file" << endl;
    infile.open("persons.txt", ios::in);
    if (!infile)
    {
        cerr << "error: unable to open result file" << endl;
        return false;
    }
    while (!infile.eof())
    {
        string lineText;
        getline(infile, lineText);
        temp.ID = lineText;
        getline(infile, lineText);
        temp.name = lineText;
        getline(infile, lineText);
        temp.department = lineText;
        getline(infile, lineText);
        temp.stuNumber = lineText;
        getline(infile, lineText);
        temp.imgUrl = lineText;
        ones.push_back(temp);
    }
    // 关闭打开的文件
    infile.close();
    cout << "Successfully Get the Data!" << endl;
    cout << "push Enter to continue...";
    system("pause");
    return true;
}

bool IfContinue()
{
    system("cls");
    cout << "cin 'e' to exit or Press any other key to continue..." << endl;
    //    string key;
    char key;
    cin >> key;
    //    if (key == "END" || key == "end" || key == "End")
    system("pause");
    if (key == 'e' || key == 'E')
    {
        cout << "结束啦" << endl;
        system("pause");
        return false;
    }
    return true;
}

vector<Person> Rand(vector<Person> &ones)
{
    vector<Person> wrongChoose;

    bool flag = true;
    while (flag)
    {
        int i = 0;
        map<char, Person> ans;
        vector<int> r = Random(ones.size());
        ans['A'] = ones[r[i++]];
        ans['B'] = ones[r[i++]];
        ans['C'] = ones[r[i++]];
        ans['D'] = ones[r[i++]];
        flag = MainFunc(wrongChoose, ans);
    }
    return wrongChoose;
}

//结合另一个Random函数应该也可以用
// vector<Person> Rand(vector<Person> &ones)
// {
//     vector<Person> wrongChoose;
//     bool flag = true;
//     while (flag)
//     {
//         map<char, Person> ans;
//         //以下方法需要调用另一个函数
//         ans['A'] = Random(ones);
//         ans['B'] = Random(ones);
//         while (ans['B'].GetID() != ans['A'].GetID())
//             ans['B'] = Random(ones);
//         ans['C'] = Random(ones);
//         while (ans['C'].GetID() != ans['A'].GetID() && ans['C'].GetID() != ans['B'].GetID())
//             ans['C'] = Random(ones);
//         ans['D'] = Random(ones);
//         while (ans['D'].GetID() != ans['A'].GetID() && ans['D'].GetID() != ans['B'].GetID() &&
//                ans['D'].GetID() != ans['C'].GetID())
//             ans['D'] = Random(ones);
//         flag = MainFunc(wrongChoose, ans);
//     }
//     return wrongChoose;
// }

bool MainFunc(vector<Person> &wrongChoose, map<char, Person> ans)
{
    bool flag = true;
    char answer = rand() % 4 + 'A';
    system("cls");
    cout << "我是谁?" << endl;
    cout << ans[answer].GetImg() << endl
         << endl;
    cout << "A." << ans['A'].GetName() << endl;
    cout << "B." << ans['B'].GetName() << endl;
    cout << "C." << ans['C'].GetName() << endl;
    cout << "D." << ans['D'].GetName() << endl;
    char choose;
    cin >> choose;
    while (choose != 'A' && choose != 'B' && choose != 'C' && choose != 'D' && choose != 'a' && choose != 'b' && choose != 'c' && choose != 'd')
    {
        cout << "没有这个选项吧，请重新输入" << endl;
        cin >> choose;
    }
    if (choose == answer || choose == (answer - 'A' + 'a'))
    {
        cout << "正确的" << endl;
        system("pause");
    }
    if (choose != answer && choose != (answer - 'A' + 'a'))
    {
        cout << "选错啦!!" << endl
             << "这是" << ans[answer].GetName() << endl;
        wrongChoose.push_back(ans[answer]);
        system("pause");
    }
    flag = IfContinue();
    system("cls");
    return flag;
}