#include<Windows.h>
#include<string>
#include<iostream>
#include<stdio.h>
#include <stdlib.h>

using namespace std;

std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

//	createDirectory
void createDirector()
{
	string path;
	cout << " enter path of dirctory to create \n ";
	cin >>path;

	int test = CreateDirectoryA(path.data(), NULL);
	if(test==0)
	{ 
		printf("CreateDirectory error: %s\n", GetLastErrorAsString().data());
		return;
	}
	cout << "creeate dircetory sccessfull \n";
}
//	deleteDirectory
/*
	ÈÚÏ ÇÐä ÍÖÑÊß íÇÈÔãåäÏÓ ÇáßæÏ ÈÊÇÚ ÇáÏÇáå Ïí ÇáãÝÑæÖ ÕÍ æÇäÇ ÍÇæáÊ ÇÚãáåÇ ÈßÐí ØÑíÞå
	ÈÓ ÇáßæÏ ãÔ ÔÛÇá ßæíÓ ãÚ ÇáÚáã Çä ÇáØÑíÞå ÕÍ
	ÇäÇ ßäÊ ÓÃáß Ýíå ÈÓ ÇáÓÇÚÇÊ ÇáãßÊÈíå ÈÚÏ ÇáÓßÔä íÚäí åßæä ÓáãÊ ÇáÈÑäÇãÌ
	https://www.daniweb.com/programming/software-development/threads/254165/how-to-delete-a-whole-folder
*/
void deleteDirctor()
{
	cout << "enter path of director to deleted \n";
	wstring path;
	WIN32_FIND_DATA FindFileData;
	wcin >> path;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFileW(path.data() , &FindFileData);
	cout << FindFileData.cFileName << endl;
	cout << hFind << endl;
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Input file error:%x\n",
			GetLastError());
		return;
	}


	/*DWORD dwError;
	wstring FileName;
	FileName = FindFileData.cFileName;
	printf("First file name is %s\n", FindFileData.cFileName);
	while (FindNextFile(hFind, &FindFileData) != 0)
	{
		FileName = FindFileData.cFileName;
		printf("Next file name is %s\n", FindFileData.cFileName);
	}
	dwError = GetLastError();
	FindClose(hFind);
	if (dwError != ERROR_NO_MORE_FILES)
	{
		printf("FindNextFile error. Error is %u\n", dwError);
		return;
	}*/
	/*LPWIN32_FIND_DATA data;
	LPWIN32_FIND_DATA (hFind,data);*/
	/*HANDLE hIn;
	hIn = CreateFile	//function return handle of file is created
	(hFind,		//name of file to read
		GENERIC_READ,             // open for reading
		0,                        // do not share
		NULL,                     // no security
		OPEN_EXISTING,            // existing file only
		FILE_ATTRIBUTE_NORMAL,    // normal file
		NULL);                    // no attr. template
	if (hIn == INVALID_HANDLE_VALUE) {
		printf("Input file error:%x\n",
			GetLastError());
		return;
	}*/

	do
	{
		bool test = DeleteFile(FindFileData.cFileName);
		if (test == 0)
		{
			printf("RemoveFile error: %s\n", GetLastErrorAsString().data());
			return;
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);

	int test = RemoveDirectoryW(path.data());
	if (test == 0)
	{
		printf("RemoveDirectory error: %s\n", GetLastErrorAsString().data());
		return;
	}
}
//	createFile
void createFile()
{
	cout << "enter name of file to create \n";
	string f;
	cin >> f;
	HANDLE hIn;

	hIn = CreateFileA	//function return handle of file is created
		(f.data(),		//name of file to read
		GENERIC_READ,             // open for reading
		0,                        // do not share
		NULL,                     // no security
		CREATE_NEW,            // existing file only
		FILE_ATTRIBUTE_NORMAL,    // normal file
		NULL);                    // no attr. template
	 
	if (hIn == INVALID_HANDLE_VALUE) {
		printf("Input file error:%x\n",
			GetLastError());
		return;
	}
	CloseHandle(hIn);
}
//	deleteFile
void deleteFile()
{
	cout << "enter name of file to delete \n";
	wstring fileName;
	wcin >> fileName;
	int test = DeleteFile(fileName.data());
	if (test == 0)
	{
		printf("DeleteFile error: %s\n", GetLastErrorAsString().data());
		return;
	}

}
//	search
void search()
{
	cout << "This order not emplemented in my program ( For lack of time ) \n";
}

//	mainFunction

int main()
{
	bool cont = false;
	int order;

	cout << "\n \t welecome in my program (assignment 1 ) \n \n";
	do
	{
	system("COLOR FC");
	cout << " 1) to create directory \n 2) to delet directory \n 3) to create file \n 4) to delet file \n 5) to search \n";
	cin >> order;

	switch (order)
	{
	case 1:	createDirector();
		break;
	case 2:	deleteDirctor();
		break;
	case 3:	createFile();
		break;
	case 4:	deleteFile();
		break;
	case 5:
		break; search();
	default:
		cout << "ERROR ORDER \n";
	}
	cout << string(4, '\n');
	system("COLOR 0A");
	cout << "do you need any another order (  1 -> YES  or  0 -> NO ) \n";
	cin >> cont;

	} while (cont);
}