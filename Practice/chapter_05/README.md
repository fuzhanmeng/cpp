### 5.8 复习题

1. 
  入口条件循环和出口条件循环之间的区别是什么？各种 C++ 循环分别属于其中的哪一种？

  入口条件循环：在进入循环之前进行判断  true进入  flase不进入
  出口条件循环：先执行一次循环 在执行完毕时去做判断
  for循环：条件入口
  while循环“条件入口
  do while循环：条件出口

2. 
  如果下面的代码片段是有效程序的组成部分,它将打印什么内容？
  int i;
  for (i = 0; i < 5; i++)
      cout << i;
  cout << endl;
0 1 2 3 4 

3. 
  如果下面的代码片段是有效程序的组成部分,它将打印什么内容？
  int j;
  for (j = 0; j < 11; j += 3)
      cout << j;
  cout << endl << j << endl;
0 3 6 9 
12

4. 
  如果下面的代码片段是有效程序的组成部分,它将打印什么内容？
  int j = 5;
  while (++j < 9)
      cout << j++ << endl;
6 8

5. 
  如果下面的代码片段是有效程序的组成部分,它将打印什么内容？
  int k = 8;
  do
      cout << "k = " << k << endl;
  while (++k < 5);
8

6. 
  编写一个打印 1, 2, 4, 8, 16, 32, 64 的 for 循环,每轮循环都将计数变量的值乘以 2。
  #include <iostream>
  
  int main ()
  {
      int a[7];
      a[0] = 1;
      for (int i = 0; i < 8; i++)
      {
          a[i + 1] = 2 * a[i];
          std::cout << a[i] << std::endl;
      }
      return 0;
  }
  
7. 
  如何在循环中包括多条语句？
  可以使用,  如 for (int i = 0, j = 8; i < 11, j > 1; i++, j--)
  i < 11, j > 1- 使用逗号运算符
  ​​有陷阱​​：逗号运算符会计算所有表达式,但只返回最后一个表达式的结果
  实际上只检查 j > 1,忽略 i < 11  
  
  // 正确方式
  for (int i = 0, j = 8; i < 11 && j > 1; i++, j--) {
     // 循环体
  }

8. 
  下面的语句是否有效？如果无效,原因是什么？如果有效,它将完成什么工作？
  int x = (1,024);
  result = (exprA, exprB);
  对于逗号运算符 
  计算 exprA(丢弃其结果)
  计算 exprB
  整个表达式的结果为 exprB的值和类型
  所以这个表达式的值是024  
  下面的语句又如何呢？
  int y;
  y = 1,024;
  对于y = 1,024; 来说
  先是 y = 1 

9. 
  在获取输入方面,cin >> ch 同 cin.get(ch) 和 cin.get() 有什么不同？
  std::cin >> ch     读取非空白字符 跳过所有前导空白字符 将字符存储到 ch
  std::cin.get(ch)   读取包括空白字符的任何字符 读取任何字符（包括空白字符） 将字符存储到 ch
  std::cin.get()     读取字符并检查值  读取任何字符（包括空白字符）返回字符的整数值（ASCII码）

### 5.9 编程练习

1. 
  编写一个要求用户输入两个整数的程序,该程序将计算并输出这两个整数之间(包括这两个整数)所有整数的和.这很假设先输入较小的整数。例如,如果用户输入2和9,则程序将输出2~9之间所有整数的和为44

  #include <iostream>
  int main()
  {
      int num1;
      int num2;
      int sum = 0;
  
      std::cout << "输入第一个数: ";
      std::cin >> num1;
  
      std::cout << "输入第二个数: ";
      std::cin >> num2;
  
      if (num1 > num2)
      {
          // 从大到小循环，包含 num2
          for (int i = num1; i >= num2; i--)
          {
              sum += i;
          }
      }
      else // 包含 num1 < num2 和 num1 == num2 的情况
      {
          // 从小到大循环，包含 num2
          for (int i = num1; i <= num2; i++)
          {
              sum += i;
          }
      }
  
      std::cout << "两数之间的整数和为: " << sum << std::endl;
      return 0;
  }

2. 
  使用array对象(而不是数组)和`long double`(而不是`long long`)重新编写程序清单5.4,并计算100的阶乘
  #include <iostream>
  #include <array>
  
  const int ArSize = 101;
  
  int main()
  {
      std::array<long double, ArSize> Array;
      Array[0] = Array[1] = 1LL;
  
      for (int i = 2; i < ArSize; i++)
      {
          Array[i] = i * Array[i - 1];
      }
  
      for (int i = 0; i < ArSize; i++)
      {
          std::cout << i << "的阶乘是" << Array[i] << std::endl;
      }
  
      return 0;
  }
  
3. 
  编写一个要求用户输入数字的程序.每次输入后,程序将报告到目前为止所有输入的累计和.当用户输入0时,程序结束
  #include <iostream>
  
  int main()
  {
      std::cout << "enter sum number: ";
      int num;
      int sum = 0;
      do
      {
          std::cin >> num;
          // sum = sum + num;
          sum += num;
          std::cout << sum << std::endl;
      } while (num != 0);
      return 0;
  }
  
  
4. 
  Daphne以10%的单利投资了100美元。也就是说,每一年的利润都是投资额的10%,即每年10美元
  - 利息 = 0.10 × 原始存款  
  Cleo以5%的复利投资了100美元.也就是说,利息是当前存款(包括利息)的5%
  - 利息 = 0.05 × 当前存款  
  Cleo在第一年投资100美元的利润是5美元。下一年为105美元的5%,即5.25美元。依此类推
  请编写一个程序,计算多少年后Cleo的投资价值能超过Daphne的,并显示两人的投资价值

  int main()
  {
      double Daphne = 100.0;
      double Cleo = 100.0;
  
      int year = 0; // 从第0年开始
  
      // 当Cleo小于或等于Daphne时继续循环
      while (Cleo <= Daphne)
      {
          year++; // 年份增加
  
          // 计算当前年度的投资价值
          Daphne = 100.0 + 10 * year; // 单利公式
          Cleo = Cleo * 1.05;         // 复利公式
      }
  
      // 输出结果
      std::cout << "After " << year << " years, Cleo's investment exceeds Daphne's." << std::endl;
      std::cout << std::fixed << std::setprecision(2);
      std::cout << "Daphne's balance: $" << Daphne << std::endl;
      std::cout << "Cleo's balance: $" << Cleo << std::endl;
  
      return 0;
  }
  
  
5. 
  假设要编写《C++ For Fools》一书.请编写一个程序,输入全年的每个月份的销售量(图书数量,而不是销售额).
  程序通过循环,使用初始化为月份名字的字符的char*数组(或string对象数组)逐月进行提示,并将输入的销售数据存储在一个int数组中
  然后,程序将数据输出显示在屏幕上,并报告这一年的销售情况
  #include <iostream>
  int main()
  {
      std::string month[12] = {"Jan", "Feb", "Mar", "Apr",
                               "May", "Jun", "Jul", "Aug",
                               "Sep", "Oct", "Nov", "Dec"};
      int sum = 0;
      int number[12];
      for (int i = 0; i < 12; i++)
      {
          std::cout << month[i] << "  ";
          std::cin >> number[i];
          sum += number[i];
      }
      std::cout << sum << std::endl;
  }
  
  
6. 
  完成编程练习5,但这一次使用一个二维数组来存储输入 —— 3年中每个月的销售量。程序将报告每年销售情况以及三年的总销售量
  #include <iostream>
  int main()
  {
      const int YEARS = 3;
      const int MONTHS = 12;
  
      int sales[YEARS][MONTHS];
      int total = 0;
  
      std::string Month[12] = {"Jan", "Feb", "Mar", "Apr",
                               "May", "Jun", "Jul", "Aug",
                               "Sep", "Oct", "Nov", "Dec"};
  
      for (int year = 0; year < YEARS; year++)
      {
          std::cout << "===== 输入第 " << year + 1 << " 年的销售量 =====" << std::endl;
          for (int month = 0; month < MONTHS; month++)
          {
              std::cout << "请输入 " << Month[month] << " 的销售量: ";
              std::cin >> sales[year][month];
          }
      }
  
      for (int i = 0; i < YEARS; i++)
      {
          int yearTotal = 0;
          for (int j = 0; j < MONTHS; j++)
          {
              // total += Month[i][j]; 这里有问题 Month[i][j]不是销售数额的二维数组
              yearTotal += sales[i][j];
          }
          total += yearTotal;
      }
      std::cout << "三年的总销售量: " << total << std::endl;
  }
  
7. 
   设计一个名为car的结构,用它存储下述有关汽车的信息：  
   生产商(存储在字符数组或string对象中的字符串)
   生产年份(整数)
  
   编写程序,询问用户有多少辆车。随后使用new创建一个由相应数量的car结构体组成的动态数组。接下来,提示用户输入每辆车的生产者(可能是多个词组成)和生产年份。注意,这将需要特别小心,因为它将交替读取数组值和字符串(第4  章)。最后,程序将显示结构内容
   程序运行示例：  
   ```
   How many cars do you wish to catalog? 2  
   Car #1:  
   Please enter the make: Hudson Hornet  
   Please enter the year made: 1952  
   Car #2:  
   Please enter the make: Kaiser  
   Please enter the year made: 1951  
   Here is your collection:  
   1952 Hudson Hornet  
   1951 Kaiser 

   #include <iostream>
   #include <cstring>
   #include <limits>
   
   struct car_Info
   {
       int year;
       std::string make;
   };
  
   int main()
   {
       int num;
       std::cout << "How many cars do you wish to catalog? ";
       // std::cin.get() >> num; // 错误用法
       std::cin >> num;
       // 清楚换行符
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::cout << "Car #1:" << std::endl;
   
       car_Info *ptr = new car_Info[num];
   
       for (int i = 0; i < num; i++)
       {
           std::cout << "Please enter the make: ";
           std::getline(std::cin, ptr[i].make);
   
           std::cout << "Please enter the year made: ";
           // std::cin.get() >> ptr[i].year; // 错误用法
           std::cin >> ptr[i].year;
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除换行符
       }
   
       // 输出结果
       for (int i = 0; i < num; i++)
       {
           std::cout << ptr[i].year << " " << ptr[i].make << std::endl;
       }
   
       delete[] ptr;
       return 0;
   }
  
8. 
  编写一个程序,使用`char`数组和循环依次读取单词,直到用户输入“done”为止。随后,程序将显示用 户输入了多少个单词(不包括“done”)
  示例输出：  
  Enter words (to stop, type the word done):  
  anteater birthday category dumpster  
  entry finagle ganery done for sure  
  You entered a total of 7 words.  
  程序应包含头文件`cstring`并使用`strcmp()`函数进行比较
  
  #include <iostream>
  #include <cstring>
  
  int main()
  {
      char ch[20] = "";
      int sum = 0;
      std::cout << "Enter words (to stop, type the word done): " << std::endl;
  
      //  先读取一个单词 才能做判断
      std::cin >> ch;
      while (strcmp(ch, "done")) // trcmp(ch, "done")在相等时返回0(假),不相等时返回非0(真)
      {
          std::cin >> ch;
          sum++;
      }
  
      std::cout << "You entered a total of " << sum << " words.  " << std::endl;
  }
  
  
9. 
  编写一个更通用的字符串练习程序,使用string对象代替字符数组程序应包含头文件string,并使用关系运算符进行比较
  #include <iostream>
  #include <string>
  
  int main()
  {
      std::cout << "Enter words (to stop, type the word done): " << std::endl;
  
      std::string str;
      std::getline(std::cin, str);
      int sum = 0;
  
      while (str != "done")
      {
          std::getline(std::cin, str);
          sum++;
      }
      std::cout << "You entered a total of " << sum << " words." << std::endl;
  }
  
10. 
  编写一个使用嵌套循环的程序,要求用户输入一个值,输出星号图案
  第一行包括一个星号,第二行两个星号,以此类推。每一行前面加句点,字符数等于行数。示例输出:
  Enter number of rows: 5  
  .*  
  ..**  
  ...***  
  ....****  
  .....*****

  #include <iostream>
  int main()
  {
      int rows = 0;
      std::cout << "Enter number of rows: ";
      std::cin >> rows;
  
      for (int i = 1; i <= rows; i++) // 行号从1开始
      {
          // 输出句点：每行i个句点
          for (int j = 1; j <= i; j++)
          {
              std::cout << ".";
          }
  
          // 输出星号：每行i个星号
          for (int k = 1; k <= i; k++)
          {
              std::cout << "*";
          }
  
          // 每行结束后换行
          std::cout << std::endl;
      }
  
      return 0;
  }