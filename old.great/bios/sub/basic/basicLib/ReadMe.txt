
基本 模块、库 处理库

〉清理库现状
〉安装库
〉拆卸库

〉支持DLL库
〉支持COM库

basicLib库本身以DLL形式实现。

〉接受来自核心的MFS(memory file-system, 作为his的内存管理服务)根目录，
	这涉及到文件系统。
	核心可以传递字符串描述，也可以传给目录对象。( IOeFS )
	当前只能用字符串描述。
	这样basicLib还需要知道MFS/的相对路径，这样才能将信息写入正确位置。

〉
