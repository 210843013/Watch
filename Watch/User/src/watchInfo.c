#include "includes.h"
u8 WatchInfo_init(void)
{
  WatchInfo_setUserInfo(170,134); //������ߡ��������ڼ��㿨·������
	return 0;  //��ʼ���ɹ�����0
}
 personInfo_t user_info;
u8 WatchInfo_setUserInfo(u8 height,u8 weight)
{
	user_info.height = ((float)height)/100;
	user_info.weight = ((float)weight)/2;
  return 0;//�ɹ� 0
}

personInfo_t * WatchInfo_getUserInfo(u8 *error)
{
	u8 err;
	err = 0;//0��ʾ��ȡ�ɹ�
	error = &err;
  return &user_info;
}
