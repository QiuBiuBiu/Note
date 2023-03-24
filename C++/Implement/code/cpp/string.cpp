#include <iostream>


class string
{
private:
    int len = 0;
    char * str = NULL;

public:
    string()
    {
        len = 0;
        str = new char[len + 1];
        str[0] = '\0';
    }
    string(char * s)
    {
        delete [] str;
        len = std::strlen(s);
        str = new char[len + 1];
        std::strcpy(str, s);
    }
    string(const string & s)
    {
        if (this == &s)
            return ;

        delete [] str;
        len = s.len;
        str = new char[len + 1];
        std::strcpy(str, s.str);
    }
    string& operator = (const string & s)
    {
        if (this == &s)
            return *this;

        delete [] str;
        len = s.len;
        std::strcpy(str, s.str);
        return *this;
    }
    string& operator += (const string & s)
    {
        char * tmp = str;
        delete [] str;
        len = std::strlen(str) + std::strlen(s.str);
        str = new char[len + 1];
        str = std::strcpy(str, tmp);
        str = std::strcat(str, s.str);
        
        return *this;
    }
    ~string()
    {
        len = 0;
        delete [] str;
        str = NULL;
    }
    void print()
    {
        std::cout << "string's len is: " << std::strlen(str) << std::endl;
        std::cout << "string's len is: " << len << std::endl;
        std::cout << "string is " << str << std::endl;
    }
};


int main()
{
    char t1[] = "hello";
    char t2[] = "world";
    string s1(t1);
    string s2(t2);
    s1 += s2;
    s1.print();
   
    // string s(str);

    // string s2(s);
    // s2.print();


    // string s;
    // s.print();
    return 0;
}