#include <iostream>

using namespace std;

int main()
{
    while (1)
    {
        char c;
        scanf("%c", &c);
        if (c == '\n')
            break;
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'Y' || c == 'y')
            continue;
        if (c >= 'A' && c <= 'Z')
            c = c + 'a' - 'A';
        cout << '.' << c;
    }
    cout << endl;
}