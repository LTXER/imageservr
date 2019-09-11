#include "LogIn.h"
#include "MainWnd.h"
#include "CashierWnd.h"


LogInWnd::LogInWnd(MySQL* pMySQL)
: m_pMySQL(pMySQL)
{}

// xml�ļ���Ӧ��Ŀ¼
CDuiString LogInWnd::GetSkinFolder()
{
	return _T("");
}

// xml�ļ�������
CDuiString LogInWnd::GetSkinFile()
{
	return _T("loginWnd.xml");
}

// ����������֣���ע�ᴰ��ʱ�����ṩ
LPCTSTR LogInWnd::GetWindowClassName(void) const
{
	return _T("LogInWnd");
}

void LogInWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName =  msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strName == _T("BTN_MIN"))
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
			//SendMessage(WM_SYSCOMMAND,SW_MINIMIZE);
		else if (strName == _T("BTN_CLOSE"))
			Close();
		else if (strName == _T("BTN_LOGIN"))
			LogIn();
	}
}

void LogInWnd::LogIn()
{
	// �ӱ༭���л�ȡ�û����Լ�����
	CEditUI* pEditUserName = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_NAME"));
	CDuiString strUserName = pEditUserName->GetText();
	
	CEditUI* pEditPassword = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_PASSWORD"));
	CDuiString strUserPassWord = pEditPassword->GetText();

	if (strUserName.IsEmpty())
	{
		MessageBox(m_hWnd, _T("�������û���"), _T("Cashier"), IDOK);
		return;
	}

	if (strUserPassWord.IsEmpty())
	{
		MessageBox(m_hWnd, _T("�������û�����"), _T("Cashier"), IDOK);
		return;
	}

	// ��ѯ���ݿ⣬�����û��Ƿ����
	string strSQL("select * from  employee where Name = '");
	// ascII   UNICODE
	strSQL += UnicodeToANSI(strUserName);
	strSQL += "';";

	vector<vector<string>> vRet = m_pMySQL->Select(strSQL);
	if (vRet.empty())
	{
		MessageBox(m_hWnd, _T("�û�������"), _T("Caisher"), IDOK);
		return;
	}

	string userpassward = UnicodeToANSI(strUserPassWord);
	if (userpassward != vRet[0][4])
	{
		MessageBox(m_hWnd, _T("�û��������"), _T("Caisher"), IDOK);
		return;
	}

	// ���ص�¼����
	ShowWindow(false);

	if (vRet[0][5] == "����Ա")
	{
		// ����������
		MainWnd mianWnd(m_pMySQL);
		mianWnd.Create(NULL, _T("MainWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
		mianWnd.CenterWindow();
		mianWnd.ShowModal();
	}
	else
	{
		// ����������
		CCashierWnd mianWnd(m_pMySQL);
		mianWnd.Create(NULL, _T("CashierWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
		mianWnd.CenterWindow();
		mianWnd.ShowModal();
	}
}