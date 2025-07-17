#include <iostream>

// 8
// int main()
// {
//     struct fish
//     {
//         char variety[20];
//         int weight;
//         double length;
//     };

//    fish st;
//    st.variety = "liyu"; //  在C++中，数组名（如 variety）本质上是一个常量指针，表示数组的首地址。它​​不能被重新赋值
//    st.weight = 2;
//    st.length = 34.2;

//    st = { "liyu", 2, 24.4 };
// }

// 13
//    int main ()
//    {
//       int num;
//       std::cin >> num;
//     //   int array = new int[num]; //  new int[num]返回一个指向整型数组的​​指针​​（int*类型）
//       int* array = new int[num];
//     std::cout << "Home of the jolly bytes";
//    }

// 15
// int main()
// {
//     struct fish
//     {
//         std::string variety;
//         int weight;
//         double length;
//     };

//     // fish st = new fish[];   //  new 返回一个指向结构体数组的​​指针​
//     fish *ptr = new fish;
// }

   #include <string>
   #include <vector>
   #include <array>

   int main ()
   {
      const int size = 10;
      std::vector<std::string> vec[size];
      std::array <std::string,size>  array;
   }
