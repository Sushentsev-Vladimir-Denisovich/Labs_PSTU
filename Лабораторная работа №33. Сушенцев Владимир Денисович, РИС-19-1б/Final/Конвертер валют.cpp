#include "��������� �����.h"
#include <Windows.h>
#include <iostream>

using namespace Final;

int main()
{
    setlocale(LC_ALL, "rus");

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MyForm);
    return 0;
}
//������� ����� ��������, ���� � �������
//������ ��������� ��������
//����� ����������



//�������� �������� ������ ����                                                 +
//����� ���������� � ����� ����� �� ���������
//��������� ����� � ���� ����� � � ���� ������                                  +
//������������ ToolTip�                                                         +
//������� 2-3 ����� ����� ������� � ������                                      + (3 �����)