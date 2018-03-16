
## ����NPAPI���ʵ�ֵ�npGxxGmPlayer��Ŀ˵���ĵ�

### NPAPI�ܹ��ĸ�Ҫ˵����

https://blog.csdn.net/yuan_lo/article/details/51553933

1. ���������ӿڣ�

- NP_GetEntryPoints�� �ڲ������֮���������øýӿڣ������������ȡ���п�����Ҫ���õ�API������ָ�롣
- NP_Initialize�� Ϊ����ṩȫ�ֳ�ʼ����
- NP_Shutdown�� Ϊ����ṩȫ�ַ���ʼ����
	
2. NP_GetEntryPoints

- �ڲ������� ```static NPError fillPluginFunctionTable(NPPluginFuncs* aNPPFuncs)```

  - fillPluginFunctionTable����������һϵ�еĺ�����ڣ����Ǻ���Ϥ����mozilla�Ŀ����ĵ��о����ᵽ����NPP��ͷ�ĺ�����
  - ��Щ��������Ҫ�ڲ���м���ʵ�ֵġ�
  
3. 

��def����ֻ�����������ӿڣ���ʵ����ȴ���������ʵ�ֵ�����������õĽӿ�21���Լ������Ҫ���õ��ɲ��ʵ�ֵĽӿ�13��
��ʵ����NPNetscapeFuncs�ṹ������55������ָ�룬NPPluginFuncs�ṹ������19������ָ�룩��

���仰˵�����ǿ����������Ҫ��ʵ����13���ӿڡ�

�ӿڵı�׼�Ѿ��������������ˣ�������ôȥʵ���Լ�Ҫʵ��ʲô���Ĺ��ܾ�ȫƾ�����Լ��ˡ�




| NPP�ӿں���       | nsPluginInstanceBase��Ա������ȫ�ֺ���                                         | ��ע                                                                                 |
|:-----------------:|:------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------:|
| NPP_New           | NS_NewPluginInstance                                                           | �������ʵ��                                                                         |
| NPP_Destroy       | NS_DestroyPluginInstance��plugin->shut                                         | ɾ�����ʵ��                                                                         |
| NPP_SetWindow     | plugin->SetWindowplugin->isInitialized��plugin->init��NS_DestroyPluginInstance | ���ڴ������ƶ����ı��С������ʱ����                                                 |
| NPP_NewStream     | plugin->NewStream                                                              | ֪ͨ���ʵ�����µ�������                                                             |
| NPP_WriteReady    | plugin->WriteReady                                                             | ȷ������Ƿ�׼���ý������ݣ��Լ���׼�����յ�����ֽ�����                             |
| NPP_Write         | plugin->Write                                                                  | �����Խ����ݶ�����this might be better named ��NPP_DataArrived��                   |
| NPP_DestroyStream | plugin->DestroyStream                                                          | ֪ͨ���ʵ����������Ҫ�رջ�����                                                     |
| NPP_StreamAsFile  | plugin->StreamAsFile                                                           | Ϊ�����������ṩ�����ļ���                                                           |
| NPP_Print         | plugin->Print                                                                  | ΪǶ���ȫ���������ƽ̨�ض��Ĵ�ӡ����                                               |
| NPP_URLNotify     | plugin->URLNotify                                                              | ֪ͨ��������URL����                                                                |
| NPP_GetValue      | plugin->GetValue                                                               | �����Բ�ѯ�����Ϣ����������ȡNPObject/Scriptable �����ʵ����                       |
| NPP_SetValue      | plugin->SetValue                                                               | ��������Ϊ������ṩ���������Ϣ��                                                   |
| NPP_HandleEvent   | plugin->HandleEvent                                                            | �¼�����������windowed�Ĳ��ֻ��MAC����ϵͳ�Ͽ��ã�����winless�Ĳ������ƽ̨������ |


4. Windows ƽ̨ NPAPI ����ĳ�ʼ���ӿڵ���˳��

	1. NP_GetEntryPoints �C �����NPP_New, NPP_Destroy, NPP_SetWindow�Ⱥ�������ڵ�ַ���һ��������
	2. NP_Initialize �C ����洢һ��NPN_CreateObject, NPN_MemAlloc,�Ⱥ�����ڵ�ַ��ɵĺ�����Ŀ�����
	3. NPP_New �C �������һ���µĲ��ʵ������ʼ��
	4. NPP_SetWindow �C ÿ��ʵ�������ε��������������ÿ��ʵ�����ڴ������ı��С���������仯������á�
	5. NPP_GetValue (Variable = NPPVpluginScriptableNPObject) �C �������һ��֧�ֽű���NPObject��������ָ�루����NPN_RetainObject����
	6. �� ��׼�Ĳ��� ��
	7. NPP_Destroy �C ���ٲ��ʵ��
	8. NP_Shutdown �C �������������Ĳ����Դ