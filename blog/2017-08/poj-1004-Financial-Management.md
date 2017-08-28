# poj-1004-Financial Management

## 作者语

深知自己的代码能力太差，开始在poj水第五题

## Description

Larry graduated this year and finally has a job. He's making a lot of money, but somehow never seems to have enough. Larry has decided that he needs to grab hold of his financial portfolio and solve his financing problems. The first step is to figure out what's been going on with his money. Larry has his bank account statements and wants to see how much money he has. Help Larry by writing a program to take his closing balance from each of the past twelve months and calculate his average account balance.

## Input

The input will be twelve lines. Each line will contain the closing balance of his bank account for a particular month. Each number will be positive and displayed to the penny. No dollar sign will be included.

## Output

The output will be a single number, the average (mean) of the closing balances for the twelve months. It will be rounded to the nearest penny, preceded immediately by a dollar sign, and followed by the end-of-line. There will be no other spaces or characters in the output.

## Sample Input

    100.00
    489.12
    12454.12
    1234.10
    823.05
    109.20
    5.27
    1542.25
    839.18
    83.99
    1295.01
    1.75

## Sample Output

    $1581.42

## AC代码(一)

    import java.text.DecimalFormat;
    import java.util.Scanner;
    public class Main {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            double sum = 0.0;
            for(int i = 0 ; i < 12 ; i ++){
                sum += sc.nextDouble();
            }
            DecimalFormat df=new DecimalFormat();
            df.setMaximumFractionDigits(2);
            df.setMinimumFractionDigits(2);
            System.out.println("$"+df.format(sum/12).replaceAll(",", ""));
            sc.close();
        }
    }

## AC代码(二)

    #include<iostream>
    #include<iomanip>
    using namespace std;

    int main(void)
    {
        double sum=0.0;
        for(int i=1;i<=12;i++)
        {
            double temp;
            cin>>temp;
            sum+=temp;
        }
        cout<<fixed<<setprecision(2)<<'$'<<sum/12.0<<endl;
        return 0;
    }

## WA代码

    #include <iostream>
    #include <stdio.h>

    using namespace std;

    int main()
    {
        double sum=0.0,tmp;
        for(int i=0;i<12;i++)
        {
            cin>>tmp;
            sum+=tmp;
        }
        printf("$%.2lf\n",sum/12.0);
        return 0;
    }
## 总结

我现在还是搞不懂我的代码为什么WA了 我记得%.2lf也是保留两位小数的啊
太坑了啊