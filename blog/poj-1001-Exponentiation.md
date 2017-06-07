# poj-1001-Exponentiation
## 作者语

深知自己的代码能力太差，开始在poj水第四题

## Description

Problems involving the computation of exact values of very large magnitude and precision are common. For example, the computation of the national debt is a taxing experience for many computer systems. 

This problem requires that you write a program to compute the exact value of Rn where R is a real number ( 0.0 < R < 99.999 ) and n is an integer such that 0 < n <= 25.

## Input

The input will consist of a set of pairs of values for R and n. The R value will occupy columns 1 through 6, and the n value will be in columns 8 and 9.

## Output

The output will consist of one line for each line of input giving the exact value of R^n. Leading zeros should be suppressed in the output. Insignificant trailing zeros must not be printed. Don't print the decimal point if the result is an integer.

## Sample Input

    95.123 12
    0.4321 20
    5.1234 15
    6.7592  9
    98.999 10
    1.0100 12

## Sample Output

    548815620517731830194541.899025343415715973535967221869852721
    .00000005148554641076956121994511276767154838481760200726351203835429763013462401
    43992025569.928573701266488041146654993318703707511666295476720493953024
    29448126.764121021618164430206909037173276672
    90429072743629540498.107596019456651774561044010001
    1.126825030131969720661201
## AC代码

    import java.math.BigDecimal;
    import java.util.*;
    import java.io.*;

    public class Main{
        public static void main(String args[]){
            Scanner cin=new Scanner(System.in);
            while(cin.hasNext()){
                BigDecimal ans=cin.nextBigDecimal();
                int n=cin.nextInt();
                String res=ans.pow(n).stripTrailingZeros().toPlainString();
                    res=res.substring(1);
                }
                System.out.println(res);
            }
            
            
        }
    }
## 总结

* 这一题题意好理解就是pow(a,b)
* 大数问题就想到了用JAVA来解决因为C的话特别的烦

JAVA 大数模板整理
    
    stripTrailingZeros() 这个函数是用来去除一个BigDecimal数的所有后导0
    toPlainString() 类似与toString() 把一个BigDecimal数转换为String
    public BigDecimal(double val) 将double表示形式转换为BigDecimal
    public BigDecimal(int val) 将int表示形式转换为BigDecimal
    public BigDecimal(String val) 将字符串表示形式转换为BigDecimal
    public BigDecimal add(BigDecimal augend) 加法
    public BigDecimal subtract(BigDecimal subtrahend) 减法
    public BigDecimal multiply(BigDecimal multiplicand) 乘法
    public BigDecimal divide(BigDecimal divisor) 除法
    

