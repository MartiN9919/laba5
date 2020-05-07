#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

using namespace std;

//��������� �� ������� ���
typedef HANDLE(_cdecl* LPFNDLLinit)(char *, char *);//���������� � ������� �� ��������� ��� �������� �� C � C ++

int main()
{
	char directory[MAX_PATH];
	char outputFileName[11] = "output.txt";

	GetCurrentDirectory(MAX_PATH, directory);
	strcat(directory, "\\"); // �������� � ������ str ������, ������������ �� ������ ���������

	HINSTANCE hLib = LoadLibrary("Lab5Dll.dll");		//��������� dll    �������� ������������ ���������� ���� (��� ����� ��� ������� ���������, �������������, �� ������� �� ����� �������� � �� ��������� ����).
	if (!hLib)
	{
		cout << "To work we need Lab5Dll.dll!\n";
		exit(0);
	}

	//LPFNDLLinit init = (LPFNDLLinit)GetProcAddress(hLib, TEXT("init"));//�������� ����� ���������� ��� ������� �� ����������
	//HANDLE WriteOffEvent = init(directory, outputFileName);

	if (WriteOffEvent == 0)
	{
		cout << "Error of input information!\n";
		exit(0);
	}
	//��������� ������� ��� ������
	LPTHREAD_START_ROUTINE  reader = (LPTHREAD_START_ROUTINE)GetProcAddress(hLib, TEXT("ThreadReader"));//�������� ����� ���������� ��� ������� �� ���������� ��������� �� �������, ������� ���������� ���� � ���, ��� ����� ����� �����������.
	LPTHREAD_START_ROUTINE  writer = (LPTHREAD_START_ROUTINE)GetProcAddress(hLib, TEXT("ThreadWriter"));//�������� ����� ���������� ��� ������� �� ����������

	//������ ������ ������ � ������
	HANDLE threadReader = CreateThread(NULL, 0, reader, NULL, 0, 0);//�������� ������������ ������;������ �����, ����������� ��� �����;����� ��������� �������.��������� �� ���������,���� �������� ������,���������, �� �������� ����� ������� �������������.
	HANDLE threadWriter = CreateThread(NULL, 0, writer, NULL, 0, 0);

	//������� ����� �������� � ����� �������
	WaitForSingleObject(threadReader, INFINITE);
	WaitForSingleObject(WriteOffEvent, INFINITE);

	CloseHandle(threadReader);						//������� ����������� �������
	CloseHandle(threadWriter);

	cout << "Combining completed successfully!\n";
	FreeLibrary(hLib);								//������� �� ������ dll
	//system("pause");
	//exit(0);

}