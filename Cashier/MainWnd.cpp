#include "MainWnd.h"


MainWnd::MainWnd(MySQL* pMySQL)
: m_pMySQL(pMySQL)
{
}

MainWnd::~MainWnd()
{

}

// xml�ļ���Ӧ��Ŀ¼
CDuiString MainWnd::GetSkinFolder()
{
	return _T("");
}

// xml�ļ�������
CDuiString MainWnd::GetSkinFile()
{
	return _T("MainWnd.xml");
}

// ����������֣���ע�ᴰ��ʱ�����ṩ
LPCTSTR MainWnd::GetWindowClassName(void) const
{
	return _T("MainWnd");
}

void MainWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strName == _T("BTN_CLOSE"))
			PostQuitMessage(0); //Close();
		else if (strName == _T("BTN_MIN"))
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		else if (strName == _T("BTN_SELECT"))
			SelectEmployeeInfo();
		else if (strName == _T("BTN_INSERT"))
			InsertEmployeeInfo();
		else if (strName == _T("BTN_UPDATE"))
			MessageBox(NULL, _T("UpdateBTN"), _T("Cashier"), IDOK);
		else if (strName == _T("BTN_DELETE"))
			DeleteEmployeeInfo();
		else if (strName == _T("BTN_SELL_RECORD"))
			MessageBox(NULL, _T("SELLBTN"), _T("Cashier"), IDOK);
	}
	else if (msg.sType == _T("selectchanged"))
	{
		CTabLayoutUI* pTab = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tablayout"));
		if (strName == _T("OPTION_EMPLOYEE"))
			pTab->SelectItem(0);
		else
			pTab->SelectItem(1);
	}
	else if (msg.sType == _T("windowinit"))
	{
		// �����ڴ����ڼ䣬��һЩ�ռ��ʼ��
		CComboBoxUI* pGender =  (CComboBoxUI*)m_PaintManager.FindControl(_T("usergender"));
		pGender->SelectItem(0);

		CComboBoxUI* pPosition = (CComboBoxUI*)m_PaintManager.FindControl(_T("position"));
		pGender->SelectItem(0);

		CComboBoxUI* pSelect = (CComboBoxUI*)m_PaintManager.FindControl(_T("COMOB_SELECT"));
		pSelect->SelectItem(0);
	}
}

void MainWnd::SelectEmployeeInfo()
{
	string strSQL("select * from employee");

	CComboBoxUI* pCombo = (CComboBoxUI*)m_PaintManager.FindControl(_T("COMOB_SELECT"));
	CDuiString strStyle = pCombo->GetText();
	if (strStyle == _T("��"))
		strSQL += ";";
	else if (strStyle == _T("����"))
	{
		strSQL += " where Name = '";
		CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();
		if (strName.IsEmpty())
		{
			MessageBox(m_hWnd, _T("�������ѯ�û�������"), _T("Cashier"), IDOK);
			return;
		}

		strSQL += UnicodeToANSI(strName);
		strSQL += "';";
	}
	else if (strStyle == _T("�Ա�"))
		;
	else if (strStyle == _T("н��"))
		;

	vector<vector<string>> vRet = m_pMySQL->Select(strSQL);
	if (vRet.empty())
		return;

	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployeeInfo"));
	pListUI->RemoveAll();

	for (size_t i = 0; i < vRet.size(); ++i)
	{
		vector<string>& strItem = vRet[i];
		CListTextElementUI* pData = new CListTextElementUI;
		pData->SetAttribute(_T("align"), _T("center"));
		
		pListUI->Add(pData);
		
		// ����
		pData->SetText(0, ANSIToUnicode(strItem[1]));
		pData->SetText(1, ANSIToUnicode(strItem[2]));
		pData->SetText(2, ANSIToUnicode(strItem[3]));
		pData->SetText(3, ANSIToUnicode(strItem[5]));
		pData->SetText(4, ANSIToUnicode(strItem[6]));
		pData->SetText(5, ANSIToUnicode(strItem[7]));		
	}
}

void MainWnd::DeleteEmployeeInfo()
{
	// ��ȡ��ǰѡ��
	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployeeInfo"));
	int lineNo = pListUI->GetCurSel();
	CListTextElementUI* pRow = (CListTextElementUI*)pListUI->GetItemAt(lineNo);

	// �����ݿ��н���Ա������Ϣɾ��
	// ����SQL���
	string strSQL("delete ");

	CDuiString strName = pRow->GetText(0);

	// �����ݿ��н�������¼ɾ��
	//m_pMySQL->Delete(strSQL);

	// ��List���Ƴ�
	pListUI->RemoveAt(lineNo);
}

void MainWnd::InsertEmployeeInfo()
{
	// �ӽ����л�ȡԱ����Ϣ
	CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();
	CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("usergender")))->GetText();
	CDuiString strBirthday = ((CEditUI*)m_PaintManager.FindControl(_T("userbirthday")))->GetText();
	CDuiString strPosition = ((CComboBoxUI*)m_PaintManager.FindControl(_T("position")))->GetText();
	CDuiString strTel = ((CEditUI*)m_PaintManager.FindControl(_T("telphone")))->GetText();
	CDuiString strSalary = ((CEditUI*)m_PaintManager.FindControl(_T("salary")))->GetText();
	
	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployeeInfo"));
	char szCount[32] = { 0 };
	_itoa(pListUI->GetCount()+1, szCount, 10);
	// ����SQL����
	string strSQL("insert into employee values(");
	strSQL += szCount;
	strSQL += ",'";
	strSQL += UnicodeToANSI(strName);
	strSQL += "','";
	strSQL += UnicodeToANSI(strGender);
	strSQL += "','";
	strSQL += UnicodeToANSI(strBirthday);
	strSQL += "','000000','";
	strSQL += UnicodeToANSI(strPosition);
	strSQL += "','";
	strSQL += UnicodeToANSI(strTel);
	strSQL += "','";
	strSQL += UnicodeToANSI(strSalary);
	strSQL += "');";

	// ��ӦSQL����
	m_pMySQL->Insert(strSQL);

	// ����Ա������Ϣ���뵽List
	CListTextElementUI* pItem = new CListTextElementUI;
	pListUI->Add(pItem);
	pItem->SetText(0, strName);
	pItem->SetText(1, strGender);
	pItem->SetText(2, strBirthday);
	pItem->SetText(3, strPosition);
	pItem->SetText(4, strTel);
	pItem->SetText(5, strSalary);
}
