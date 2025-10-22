# 编译器设置
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g

# 最终生成的可执行文件的名字
TARGET = stock00

# 列出构建此目标所需的所有 .cpp 源文件
SRCS = 10.8_stock20.cpp 10.9_usestock2.cpp

# 自动生成对应的 .o 对象文件列表：将 SRCS 中所有 .cpp 后缀替换为 .o
OBJS = $(SRCS:.cpp=.o)

# 默认目标：当在终端只输入 `make` 命令时，将执行此目标
all: $(TARGET)

# 链接规则：将所有的 .o 文件链接成最终的可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# 使用自动变量：
#   $@ 代表当前规则的目标（即 $(TARGET)）
#   $(OBJS) 代表所有 .o 文件

# 编译规则：一条模式规则，告诉 make 如何将任意的 .cpp 文件编译成同名的 .o 文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
#   $< 代表当前规则的第一个依赖文件（即 %.cpp）
#   $@ 代表当前规则的目标（即 %.o）

# 自动包含依赖信息（防止第一次编译时报错用 -include）
-include $(OBJS:.o=.d)

# 清理规则：删除编译过程中生成的所有 .o 文件和最终的可执行文件
clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TARGET)

# 声明 all 和 clean 为“伪目标”
# 这能防止当前目录下恰好有名为 "all" 或 "clean" 的文件时，make 命令出现逻辑错误[4](@ref)

.PHONY: all clean