4.12 复习题

1. 如何声明下述数据？
   a. actor 是由 30 个 char 组成的数据组
   b. betsie 是由 100 个 short 组成的数据组
   c. chuck 是由 13 个 float 组成的数据组
   d. dipsea 是由 64 个 long double 组成的数据组

   char actor[30]
   short betsie[100]
   float chunk[13]
   long double dipsea[64]

2. 使用模板类 array 而不是数组来完成问题 1
   #include <array>

   int main ()
   {
      std::array<char,30> actor;
      std::array<short,100> setsie;
      std::array<float,13> chunk;
      std::array<double long, 64> dipsea;
   }

3. 声明一个包含 5 个元素的 int 数组，并将它初始化为前 5 个正整数
   int array[5] = {1, 2, 3, 4, 5,}

4. 编写一条语句，将问题 3 中数组第一个元素和最后一个元素的和赋给变量 even
   int array[5] = {1, 2, 3, 4, 5,};
   int even = array[0] + array[4];

5. 编写一条语句，显示 float 数组 ideas 中的第 2 个元素的值
   std::cout << ideas[1] << std::endl;

6. 声明一个 char 数组，并将其初始化为字符串 "cheeseburger"
   char array[20] = "cheeseburger";

7. 声明一个 string 对象，并将其初始化为字符串 "Waldorf Salad"
   std::string str = "Waldorf Salad";

8. 设计一个描述鱼的结构声明。结构内应当包含品种、重量（整数，单位为盎司）和长度（英寸，包含小数）
   struct fish
   {
      <!-- int variety;   // int 有问题 -->
      std::string variety;
      int weight;
      double length;
   }

9. 声明一个问题 8 中定义的结构的变量，并对它进行初始化
   fish st;
   st = {"BigFish", 12, 23,2};
   
10. 用 enum 定义一个名为 Response 的类型，它包含 Yes, No 和 Maybe 等枚举量，其中 Yes 的值为 1, No 为 0, Maybe 为 2
   enum Resopnse
   {
      YES = 1;
      NO = 0;
      Maybe = 2;
   }

11. 假设 ted 是一个 double 变量，请声明一个指向 ted 的指针，并使用该指针来显示 ted 的值
   double* ptr = &ted;

12. 假设 treacle 是一个包含 10 个元素的 float 数组，请声明一个指向 treacle 的第一个元素的指针，并使用该指针来显示数组的第一个元素和最后一个元素
   float treacle[10];
   float* ptr = treacle;
   ptr 
   ptr + = 9

13. 编写一段代码，要求用户输入一个正整数，然后创建一个动态的 int 数组，其中包含的元素数目等于用户输入的值。首先使用 new 来完成这项任务，再使用 vector 对象来完成这项任务
   int main ()
   {
      int num;
      std::cin >> unm;
      <!-- int array = new array[unm]; -->
      int* array = new int[num];
   }

14. 下面的代码是否有效？如果有效，它将打印出什么结果？
   cout << "(int*) Home of the jolly bytes";

15. 编写一段代码，给问题 8 中描述的结构动态分配内存，再读取该结构的成员的值
   struct fish
   {
      std::string variety;
      int weight;
      double length;
   }

   fish *pt = new fish;
   st.variety
   st.weight
   st.length

16. 程序清单 4.6 指出混合输入数字和一行字符串时存储的问题。如果将下面的代码：
    cin.getline(address,80);
    替换为：
    cin >> address;
    将对程序的运行带来什么影响？

    cin.getline  会读取空格
    cin          不会读取空格

17. 声明一个 vector 对象和一个 array 对象，它们都包含 10 个 string 对象。指出所需的头文件，但不要使用 using。使用 const 来指定要包含的 string 对象数

   #include <string>
   #include <vector>
   #include <array>

   int main ()
   {
      const int size = 10;
      std::vector<std::string> vec[size];
      std::array <std::string,size>  array;
   }

4.13 编程练习

1. 编写一个 C++ 程序，如下途输显示示例所示并显示信息:

   What is your first name? Betty Sue  
   What is your last name? Yewe  
   What letter grade do you deserve? B  
   What is your age? 22  
   Name: Yewe, Betty Sue  
   Grade: C  
   Age: 22  

   注意，该程序应接受的名字包含多个单词。另外，程序将向下调整成绩，即向上调一个字母。假设用户请求 A、B 或 C，所以不必担心 D 和 F 之间的空档

   #include <iostream>

   int main()
   {
      std::string first_name;
      char last_name[20];
      char grade;
      int age;

      std::cout << " What is your first name?";
      std::getline(std::cin, first_name);

      std::cout << " What is your last name?";
      std::cin.getline(last_name, 20);

      std::cout << " What letter grade do you deserve?";
      std::cin >> grade;

      std::cout << " What is your age?";
      std::cin >> age;

      std::cout << " Name: " << last_name << " , " << first_name << std::endl;

      std::cout << " Grade: " << char(grade + 1) << std::endl;

      std::cout << " Age: " << age << std::endl;

      return 0;
   }
2. 修改程序清单 4.4，使⽤ C++ string 类⽽不是 char 数组

   #include <iostream>

   int main()
   {
      std::string name;
      std::string dessert;

      const int ArSize = 20;

      std::cout << "Enter your name:\n";
      std::getline(std::cin, name);

      std::cout << "Enter your favorite dessert:\n";
      std::getline(std::cin, dessert);
      std::cout << "I have some delicious " << dessert;
      std::cout << " for you, " << name << ".\n";

      return 0;
   }

3. 编写一个程序，它要求用户首先输入其名，然后输入其姓；然后程序使用一个逗号和空格将姓名组合起来，并存储和显示组合结果。请使用 char 数组和头文件 cstring 中的函数。下面是该程序运行时的情形:

   Enter your first name: Flip  
   Enter your last name: Fleming  
   Here’s the information in a single string: Fleming, Flip  

   #include <iostream>
   #include <cstring>

   int main()
   {
      char first_name[20];
      char last_name[20];
      char full_name[20];

      std::cout << "Enter your first name:";
      std::cin.getline(first_name, 20);

      std::cout << "Enter your last name:";
      std::cin.getline(last_name, 20);

      strcpy(full_name, first_name);
      strcat(full_name, ", ");
      strcat(full_name, last_name);

      std::cout << "Here's the information in a single string: " << full_name << std::endl;

      return 0;
   }

4. 编写一个程序，它要求用户首先输入其名，再输入其姓；然后程序使用一个逗号和空格将姓名组合起来，并存储和显示组合结果。请使用 string 对象和头文件 string 中的函数。下面是该程序运行时的情形:

   Enter your first name: Flip  
   Enter your last name: Fleming  
   Here’s the information in a single string: Fleming, Flip  

   #include <iostream>
   #include <string>

   int main()
   {
      std::string first_name;
      std::string last_name;

      std::cout << "Enter your first name:";
      std::getline(std::cin, first_name);

      std::cout << "Enter your last name:";
      std::getline(std::cin, last_name);

      std::cout << "Here’s the information in a single string:" << first_name << ", " << last_name << std::endl;

      return 0;
   }

5. 结构 CandyBar 包含 3 个成员:第一个成员存储糖块的品牌，第二个成员存储糖块的重量（可以有小数），第三个成员存储糖块的卡路里含量（整数）
   请编写一个程序，声明这个结构，创建一个名为 snack 的 CandyBar 变量，并将其成员分别初始化为 “Mocha Munch”、2.3 和 350 初始化应在声明 snack 时进行 最后，程序显示 snack 变量的内容

   #include <iostream>
   #include <string>

   struct CandyBar
   {
      std::string brand;
      float weigth;
      int calorice;
   };

   int main()
   {
      CandyBar snack = {"Mocha Munch", 2.3, 350};
      std::cout << snack.brand << " " << snack.weigth << " " << snack.calorice << std::endl;

      return 0;
   }

6. 结构 CandyBar 包含 3 个成员，如编程练习 5 所示。请编写一个程序，创建一个包含 3 个元素的 CandyBar 数组，并将它们初始化为所选的值，然后显示每个结构的内容

   #include <iostream>
   #include <string>

   struct CandyBar
   {
      std::string variety;
      float weigth;
      int Calories;
   };

   int main()
   {
      // CandyBar snack[3];
      // snack[0] = {"Mocha Munch", 2.3, 350};
      // snack[1] = {"defu", 44.1, 110};
      // snack[2] = {"feililuo", 2.21, 2220};
      CandyBar snack[3] = {{"Mocha Munch", 2.3, 350}, {"defu", 44.1, 110}, {"feililuo", 2.21, 2220}};

      std::cout << snack[0].variety << " " << snack[0].weigth << " " << snack[0].Calories << std::endl;
      std::cout << snack[1].variety << " " << snack[1].weigth << " " << snack[1].Calories << std::endl;
      std::cout << snack[2].variety << " " << snack[2].weigth << " " << snack[2].Calories << std::endl;

      CandyBar *pt = new CandyBar[3];
      pt->Calories = 22;
      pt->weigth = 3.22;
      pt->variety = "hao chi de ";

      std::cout << pt->variety << " " << pt->weigth << " " << pt->Calories << " " << std::endl;

      return 0;
   }

7. William Wingate 从事比萨饼分析服务。对于每个披萨，他都需要记录以下信息：  
   • 披萨公司的名称，可以有多个单词组成。  
   • 披萨的直径。  
   • 披萨的重量。  
   请设计一个能存储这些信息的结构，并编写一个使用这种结构变量的程序。程序将请求用户输入上述信息，然后显示这些信息。请使用 cin（或它的方法）和 cout

   #include <iostream>
   #include <string>

   struct Pizza
   {
      std::string Company_name;
      double diameter;
      float weigth;
   };

   int main()
   {
      std::cout << "William Wingate" << " Pizza Analysis Services " << std::endl;
      Pizza p;
      p.Company_name = "apple";
      p.diameter = 11.0;
      p.weigth = 4.8;

      std::cout << p.Company_name << " " << p.diameter << " " << p.weigth << " " << std::endl;

      std::cout << "Please Enter Pizza's company name: ";
      std::getline(std::cin, p.Company_name);
      // std::cin.get(p.diameter);
      // std::cin.getline(p.weigth);
      std::cout << "Please Enter Pizza's diameter: ";
      std::cin >> p.diameter;

      std::cout << "Please Enter Pizza's weigth: ";
      std::cin >> p.weigth;

      std::cout << p.Company_name << " " << p.diameter << " " << p.weigth << " " << std::endl;

      return 0;
   }

8. 完成编程练习 7，但使用 new 来为结构分配内存，而不是声明一个结构变量。另外，让程序在请求用户输入披萨公司名称之前输入披萨的直径

   #include <iostream>
   #include <string>

   struct Pizza
   {
      std::string Company_name;
      double diameter;
      float weigth;
   };

   int main()
   {
      std::cout << "William Wingate" << " Pizza Analysis Services " << std::endl;

      Pizza *p = new Pizza;
      // p->diameter = 11;

      std::cout << "Please Enter Pizza's diameter: ";
      std::cin >> p->diameter;

      std::cin.get();

      std::cout << "Please Enter Pizza's company name: ";
      std::getline(std::cin, p->Company_name);

      std::cout << "Please Enter Pizza's weigth: ";
      std::cin >> p->weigth;
      std::cout << p->Company_name << " " << p->diameter << " " << p->weigth << " " << std::endl;

      //
      delete p;
      return 0;
   }

9. 修改编程练习 6，但使用 new 来动态分配数组，而不是声明一个包含 3 个元素的 CandyBar 数组

   #include <iostream>
   #include <string>

   struct CandyBar
   {
      std::string variety;
      float weigth;
      int Calories;
   };

   int main()
   {
      CandyBar *pt = new CandyBar;      // ✅ 分配一个 CandyBar 对象
      CandyBar *ptr = new CandyBar[10]; // ✅ 分配一个包含 10 个 CandyBar 的数组

      pt->variety = "apple";
      pt->weigth = 22.3;
      pt->Calories = 1552;

      ptr[2].variety = "hahaha";
      ptr[2].weigth = 2323;
      ptr[2].Calories = 5746;

      std::cout << pt->variety << " " << pt->weigth << " " << pt->Calories << std::endl;
      std::cout << ptr[2].variety << " " << ptr[2].weigth << " " << ptr[2].Calories << std::endl;

      delete pt;
      delete[] ptr;
      return 0;
   }

10. 编写一个程序，让用户输入至多 10 个高尔夫成绩（如果愿意，也可以让用户输入 0 来提前结束），并显示这些成绩的平均成绩。请使用一个 array 对象来存储成绩（如果编译器不支持 array 类，请使用数组）
   #include <iostream>
   #include <array>
   #include <string>

   int main()
   {
      std::array<float, 3> grade;

      std::cout << "Please Enter grade[0]: ";
      std::cin >> grade[0];

      std::cout << "Please Enter grade[0]: ";
      std::cin >> grade[1];

      std::cout << "Please Enter grade[0]: ";
      std::cin >> grade[2];

      std::cout << " 3 times the results are : " << grade[0] << " " << grade[1] << " " << grade[2] << std::endl;

      float avg = (grade[0] + grade[1] + grade[2]) / 3;
      std::cout << "Average Grade is : " << avg << std::endl;

      return 0;
   }