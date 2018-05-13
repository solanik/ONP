#include <iostream>
#include <cctype>

int kol_znak(char a);
void add_to_exit(char * exit,int  & i_exit , char ch);
void add_to_sign(char * sign, int & i_sig, char ch);
void sign_to_exit(char *exit, int & i_exit, char *sign, int & i_sign);

int main()
{
    using namespace std;

    char tab[100];
    char odp[100];
    int i_odp = 0;
    char znak[100] = { '\0' };
    int i_znak = 0;
    cout << "Podaj dane w standardowej notacji <bez spacji>,\nznaki operacji matematycznych to: ( ) ^ * / % + -\n";
    cin.getline(tab, 100);
    int i;
    for ( i = 0; tab[i] != '\0'; i++)
    {
        switch (tab[i])
        {
            case '(':
                add_to_sign(znak, i_znak, tab[i]);
                break;
            case '^':
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                if (i_znak == 1 || kol_znak(tab[i]) > kol_znak(znak[i_znak - 1]))
                    add_to_sign(znak, i_znak, tab[i]);
                else
                {
                    while (kol_znak(tab[i]) <= kol_znak(znak[i_znak - 1]))
                        sign_to_exit(odp, i_odp, znak, i_znak);
                    add_to_sign(znak, i_znak, tab[i]);
                }
                break;
            case ')':
                while (znak[i_znak-1] != '(')
                    sign_to_exit(odp, i_odp, znak, i_znak);
                znak[i_znak - 1] = '\0';
                --i_znak;
                break;
            default:
                add_to_exit(odp, i_odp, tab[i]);
                if (isdigit(tab[i - 1]))
                    add_to_exit(odp, i_odp, ' ');
                break;
        }

    }
    while (i_znak!=0)
        sign_to_exit(odp, i_odp, znak, i_znak);
    cout << "W odwroconej notacji polskiej to bedzie:\n";
    for (int j = 0; j < i_odp; j++)
        cout << odp[j];
    cout <<endl<< "Do widzenia!";

    return 0;
}

int kol_znak(char a)
{
    if (a == '^')
        return 3;
    else if (a == '*' || a == '/'||a=='%')
        return 2;
    else if (a == '+' || a == '-')
        return 1;
    else
        return 0;
}


void add_to_exit(char * exit, int  & i_exit, char ch)
{
    *(exit+i_exit) = ch;
    ++i_exit;
}

void add_to_sign(char * sign, int & i_sig, char ch)
{
    *(sign + i_sig) = ch;
    ++i_sig;
}

void sign_to_exit(char *exit, int & i_exit, char *sign, int & i_sign)
{
    i_sign--;
    *(exit + i_exit) = *(sign + i_sign);
    *(sign + i_sign) = '\0';
    ++i_exit;
}