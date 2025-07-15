此模块为笔记 

1、字符串std::string 和char[]以及char的的区别
char 单个字符 不能表述字符串  char a = 'A'
char[] C风格的字符串数组  以\0结束  char str[5] = "hi" 有越界风险
std::string C++字符串类 它是一个类  std::string str = "hello world" 

std::string 和 char[] 可以通过 c_str()进行转换  c_str()返回一个const char* 类型的指针(C风格的字符串指针) 返回的字符串以/0结尾


2、几种输入方式的对比
std::cin >> str      ---    
std::cin.get(char)   --- 
std::cin.get(buffer,size)
std::cin.get(buffer,size).get() ---
std::cin.getline(buffer,size)   ---
std::getline(std::string,str)   ---
