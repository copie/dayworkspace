#include  <bits/stdc++.h>

using namespace std;

void sort(int a[], int n);//实现数组的排序，排序方法是冒泡，选择或插入。

struct Point
{
	double x;//x轴坐标
	double y;//y轴坐标
};

class Line
{
    Point c;
	double a;//直线y = a*x + b中的a
	double b;//直线y = a*x + b中的b

public:
	Line();//通常设置的空构造函数
	Line(Point A,Point B);
//该构造函数实现由AB两点确定一条直线方程y = a*x + b
	~Line();//析构函数，打印析构信息
	void print();//打印直线方程
	friend bool isLine(Point A, Point B, Point C);
//判断三点是否能连成直线
	friend Point twoLine(Line L1, Line L2);
//求L1,L2两条直线交点，注意返回值
	friend double width(Line L1, Line L2, double a);
	//求L1,L2两条直线在x=a处的宽度（即距离）
	friend double area(Line one, Line two, double x1, double x2);
	//求L1,L2两条直线与x=x1和x=x2围成的面积，选作
};
Line::Line()
{

}
Line::Line(Point A,Point B){
    a = (A.y-B.y)/(A.x-B.x);
    b = (A.x*B.y+B.x*A.y)/(A.x-B.x);
}
Line::~Line(){
    cout <<"Line::~Line()"<< endl;
}
void Line::print(){
   cout<<"y"<<"="<<a<<"x"<<b<<endl;
}
bool isLine(Point A, Point B, Point C){
    double a = (A.y-B.y)/(A.x-B.x);
    double b = (A.x*B.y+B.x*A.y)/(A.x-B.x);
    if((a*C.x+b) == C.y)
      return true;
    return false;
}
Point twoLine(Line L1 , Line L2){
    Point p;
    p.x = 0,p.y = 0;
    p.x = (L2.b-L1.b)/(L1.a-L2.b);
    p.y = (L1.a*L2.b - L1.b*L2.a)/(L1.a - L2.a);
    return p;
}
double width(Line L1,Line L2,double a){
    double L = 0;
    L1.c.x = a;
    L2.c.x = a;
    L1.c.y = L1.c.x*L1.a + L1.b;
    L2.c.y = L2.c.x*L2.a + L2.b;
    L = abs(L1.c.y - L2.c.y);
    return L;
}
double area(Line one, Line two, double x1, double x2)
{   //这里少一个函数
    return 23.0;
}
void sort(int a[], int n){
     int min,t;
     for(int i=0;i<n-1;i++)
     {
         t=i;
         for(int j = i+1;j<n;j++)
             if(a[j]<a[t])
             t=j;
             if(t!=i)
             {
                 min = a[i];
                 a[i] = a[t];
                 a[t] = min;
             }
     }
     return;
}//冒泡排序
void init()
{
    int i ,a[10];
    srand(int(time(0)));
    for(i=0;i<10;i++)
    {
        a[i] = rand()%100;
    }
    for(i=0;i<10;i++)
    {
          cout<<a[i]<<endl;
    }
    sort(a,10);
    for(i=0;i<10;i++)
    {
         cout<<a[i]<<endl;
    }
    return;
}

int main() {
   Point A{10, 10},B{20, 20},C{50, 50};
   Line l = Line(A, B);
   l.print();
   cout<<isLine(A, B, C)<<endl;;

   cout<<twoLine(Line(A,B),Line(B,C)).x<<"   "<<twoLine(Line(A,B),Line(B,C)).y<<endl;
   cout<<width(Line(C,B), Line(A,B), 20);
   cout<<area(Line(A,B), Line(B,C), 20, 30);
   int a[10]={1,2,3,4,5,6,7,8,9,0};
   sort(a, 10);
   for(auto num:a)
    cout<<num<<endl;
   return 0;
}
