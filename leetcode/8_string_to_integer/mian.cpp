/*************************************************************************
	> File Name: mian.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 15 Mar 2015 04:10:50 PM CST
 ************************************************************************/

#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

int atoi(string str)
{
	string::iterator iter = str.begin();
    int minusflag = 0;
    int size = 0;
    int number = 0;
    int max = 2147483647;
    int min = -2147483648;
       
	//del space
    while(*iter == ' '){
        str.erase(iter);
    }
        
	// '+'  '-'
    if(str[0] == '-'){
        minusflag = 1;
        ++iter;
    }else if(str[0] == '+'){
        ++iter;
    }
        
	// '+' and not digit
    if(!isdigit(*iter)){
        return 0;
    }
        
	//pos first char
    string num("1234567890-+");    
    size = str.find_first_not_of(num);

	//if not find
    if(size < 0){
        size = str.size();
    }

	//init size
    if(str[0] == '-' || str[0] == '+'){
        --size;
    }
        
	//if number overflow
    if(size > 10){
        if(!minusflag){
            return max;
        }else{
            return min;
        }
    }

    //to integer    
    ++size;   
    while(--size){
        if(isdigit(*iter)){
            number = number * 10 + *iter - '0';
        }
        ++iter;
    }

    //if overflow    
    if(number < 0 && !minusflag){
        return max;
    }else if(-1 * number > 0 && minusflag){
        return min;
    }
        
	//if '+' '-'
    if(minusflag){
        number *= -1;
    }
        
    return number;
}

int main(void)
{
	string str("   03245c34");

	cout << "str: " << str << endl
		 << "int: " << atoi(str) << endl;

	return 0;
}
