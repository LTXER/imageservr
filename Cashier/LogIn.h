#include "Common.h"


class LogInWnd : public WindowImplBase
{
public:
	LogInWnd(MySQL* pMySQL);

	virtual void Notify(TNotifyUI& msg);

	void LogIn();
protected:
	// WindowImplBase���ṩ���������麯��
	// xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	// xml�ļ�������
	virtual CDuiString GetSkinFile();

	// ����������֣���ע�ᴰ��ʱ�����ṩ
	virtual LPCTSTR GetWindowClassName(void) const;

	MySQL* m_pMySQL;
};