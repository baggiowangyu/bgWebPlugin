
## 基于NPAPI框架实现的npGxxGmPlayer项目说明文档

### NPAPI架构的概要说明：

https://blog.csdn.net/yuan_lo/article/details/51553933

1. 三个导出接口：

- NP_GetEntryPoints： 在插件加载之后立即调用该接口，用于浏览器获取所有可能需要调用的API函数的指针。
- NP_Initialize： 为插件提供全局初始化。
- NP_Shutdown： 为插件提供全局反初始化。
	
2. NP_GetEntryPoints

- 内部调用了 ```static NPError fillPluginFunctionTable(NPPluginFuncs* aNPPFuncs)```

  - fillPluginFunctionTable函数设置了一系列的函数入口，都是很熟悉的在mozilla的开发文档中经常提到的以NPP开头的函数。
  - 这些函数是需要在插件中加以实现的。
  
3. 

在def里面只定义了三个接口，但实际上却包括浏览器实现的由浏览器调用的接口21个以及浏览器要调用的由插件实现的接口13个
（实际上NPNetscapeFuncs结构定义了55个函数指针，NPPluginFuncs结构定义了19个函数指针）。

换句话说，我们开发插件就是要来实现这13个接口。

接口的标准已经由浏览器定义好了，我们怎么去实现以及要实现什么样的功能就全凭我们自己了。




| NPP接口函数       | nsPluginInstanceBase成员函数或全局函数                                         | 备注                                                                                 |
|:-----------------:|:------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------:|
| NPP_New           | NS_NewPluginInstance                                                           | 创建插件实例                                                                         |
| NPP_Destroy       | NS_DestroyPluginInstance、plugin->shut                                         | 删除插件实例                                                                         |
| NPP_SetWindow     | plugin->SetWindowplugin->isInitialized、plugin->init、NS_DestroyPluginInstance | 窗口创建、移动、改变大小或销毁时调用                                                 |
| NPP_NewStream     | plugin->NewStream                                                              | 通知插件实例有新的数据流                                                             |
| NPP_WriteReady    | plugin->WriteReady                                                             | 确定插件是否准备好接收数据（以及其准备接收的最大字节数）                             |
| NPP_Write         | plugin->Write                                                                  | 调用以将数据读入插件this might be better named “NPP_DataArrived”                   |
| NPP_DestroyStream | plugin->DestroyStream                                                          | 通知插件实例数据流将要关闭或销毁                                                     |
| NPP_StreamAsFile  | plugin->StreamAsFile                                                           | 为创建流数据提供本地文件名                                                           |
| NPP_Print         | plugin->Print                                                                  | 为嵌入或全屏插件请求平台特定的打印操作                                               |
| NPP_URLNotify     | plugin->URLNotify                                                              | 通知插件已完成URL请求                                                                |
| NPP_GetValue      | plugin->GetValue                                                               | 调用以查询插件信息（还用来获取NPObject/Scriptable 插件的实例）                       |
| NPP_SetValue      | plugin->SetValue                                                               | 这是用来为浏览器提供插件变量信息的                                                   |
| NPP_HandleEvent   | plugin->HandleEvent                                                            | 事件处理函数，对windowed的插件只在MAC操作系统上可用，对于winless的插件所有平台都可用 |


4. Windows 平台 NPAPI 插件的初始化接口调用顺序

	1. NP_GetEntryPoints – 插件用NPP_New, NPP_Destroy, NPP_SetWindow等函数的入口地址填充一个函数表。
	2. NP_Initialize – 插件存储一个NPN_CreateObject, NPN_MemAlloc,等函数入口地址组成的函数表的拷贝。
	3. NPP_New – 插件创建一个新的插件实例并初始化
	4. NPP_SetWindow – 每个实例都会多次调用这个函数——每次实例窗口创建、改变大小或者其他变化都会调用。
	5. NPP_GetValue (Variable = NPPVpluginScriptableNPObject) – 插件创建一个支持脚本的NPObject并返回其指针（调用NPN_RetainObject）。
	6. — 标准的插件活动 —
	7. NPP_Destroy – 销毁插件实例
	8. NP_Shutdown – 销毁所有遗留的插件资源