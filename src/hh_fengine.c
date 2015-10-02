#include "fengin.h"
#include "stdio.h"
#include "windows"
HANDLE hFile;
void init(char *fileName)  
{
	//char *pBuffer;
	//DWORD RSize;
	//int filesize=0;
	char path[100];
	_tcspy(path,fileName)
	hFile=CreataFile(path, GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hOpenFile==INVALLD_HANDLE_VALUE)
	{
		hFile=NULL;
		printf("Can not open the file!");
    }

    //fileSize = GetFileSize(hOpenFile, NULL);
    //pBuffer = (CHAR *) malloc(fileSize);
    //ReadFile(hOpenFile,pBuffer,fileSize,&RSize,NULL);
	//free(pBuffer);
}
int read_dos_head(pfile_entity dosHeader)
{
	if(dosHeader->_dos_header==NULL)
	{
		dosHeader->_dos_header=(IMANG_DOS_HEADER *)malloc(sizeof(IMANG_DOS_HEADER));
		DWORD dwRead;
		//读取DOS头
		ReadFile(hFile,&(dosHeader->_dos_header),sizeof(dosHeader->_dos_header),dwRead,NULL)
			if(dwRead==sizeof(dosHeader->_dos_header))
		{
			return dwRead;
		}
	}
	return sizeof(dosHeader->_dos_header);
}
int read_NT_head(pfile_entity ntHeader)
{
	if(ntHeader->_nt_headers==NULL)
	{
		DWORD dwRead;
	ntHeader->_nt_headers=(IMAGE_NT_HEADERS *)malloc(sizeof(IMAGE_NT_HEADERS));
	//DWORD dwRead;
	if(dosHeader->_dos_header.e_magic==IMAGE_DOS_SINGATURE)  //是不是有效的DOS头
		{   //定位NT头
			if(SetFilePointer(hFile,dosHeader->_dos_header.e_lfanew,NULL,FILE_BEGIN)!=-1)
			{  //读取NT头
				ReadFile(hFile,&ntHeader->_nt_headers,sizeof(ntHeader->_nt_headers),dwRead,NULL)
					if(dwRead==sizeof(ntHeader->_nt_headers))
				{
					return dwRead;
				}
			}
		}
	}
	return sizeof(ntHeader->_nt_headers);
}
int read_segment_header(pfile_entity segHeader)
{
	if(segHeader->_sec_header==NULL)
	{
		DWORD dwRead;
		segHeader->_sec_header_=(IMAGE_SECTION_HEADER *)malloc(sizeof(IMAGE_SECTION_HEADER)*3);
		//定位节区头
		if(SetFilePointer(hFile,dosHeader->_dos_header.e_lfanew+sizeof(IMAGE_NT_HEADERS ),NULL,FILE_BEGIN)!=-1)
		{  //读取节区头
			ReadFile(hFile,&segHeader_>_sec_header,sizeof(IMAGE_SECTION_HEADER)*3,NULL,NULL)
				if(dwRead==sizeof(segHeader->_sec_header))
			{
				return dwRead;
			}
		}
	}
	return sizeof(segHeader->_sec_header）；
}
void desponse(pfile_entity free)
{
	free(dosHeader->_dos_header);
	free(ntHeader->_nt_header);
	free(segHeader->_sec_header_);
}
