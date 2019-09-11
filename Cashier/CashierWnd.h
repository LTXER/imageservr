#pragma once
#include "Common.h"

class CCashierWnd : public WindowImplBase
{
public:
	CCashierWnd(MySQL* pMySQL);
	~CCashierWnd();

	virtual void Notify(TNotifyUI& msg);

protected:
	// WindowImplBase���ṩ���������麯��
	// xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	// xml�ļ�������
	virtual CDuiString GetSkinFile();

	// ����������֣���ע�ᴰ��ʱ�����ṩ
	virtual LPCTSTR GetWindowClassName(void) const;

	void SelectGoods();
	void AddGoodsCount();
	void SubGoodsCount();
	void InsertGoodsList();
	void CancelOrder();
	void CommitOrder();
private:
	MySQL* m_pMySQL;
};

