# UnitTestDoctest

c++ unit testing for doctest

# 首次使用

执行InitProject.sh创建测试文件的依赖源码(比如parser的代码)，使用方法如下：

```
shell
	./InitProject.sh 项目根目录
```

# 添加配置字

修改vehicle_name.cpp文件，例子如下:

```
C++
    if(ECU_TABLE_USER_DA_SOLUTION == id)
    {
        return 1;
    }
```

# 添加测试源码

```
python
	./InitProject.py -t 源码目录
```

# 编译

```
shell
	./build.sh all	#编译所有
	./build.sh apps #编译变更
```

# 运行

./build/maintest

# 添加测试用例

修改maintest.cpp文件

## 1、包含module的头文件

```
C++
#include "chimeform/fds_can_chimeform_module.hpp"
```

## 2、初始化module

```
C++
    auto chimegen_gen_module = std::make_shared<ChimeformGenModule>();
    chimegen_gen_module->link_signal_item_module(signal_modules_map);
    chimegen_gen_module->start();
```

## 3、发送CAN信号

```
C++
 IC_SINGLE_SET_UINT32_T(CANSIG_GW_1F3__MdcNicaReminderAcoustic_g,1);
```

## 4、CAN信号超时

```
C++
	IC_SINGLE_TIMEOUTIC_SINGLE_TIMEOUT(CANSIG_GW_1F3__MdcNicaReminderAcoustic_g,1);
```

## 5、检查发送的值

```
C++
	IC_CHECK_CHIME 		#检查蜂鸣音，接收两个参数，第一个是topic，第二个是值
	IC_CHECK_TEXT		#检查文本提示，接收两个参数，第一个是topic，第二个是值
	IC_CHECK_TELLTALE	#检查指示灯，接收三个参数，第一个是topic，第二个是值，第三个是指示灯信息
	IC_CHECK_VALUE		#检查PayLoad里面value值，接收两个参数，第一个是topic，第二个是值
	IC_CHECK_STRING		#检查topic对应的字符串，接收两个参数，第一个是topic，第二个是值
	IC_CHECK_FLOAT		#检查topic对应的float，接收两个参数，第一个是topic，第二个是值
```
