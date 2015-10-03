#include "hh_fengine.h"
#include "stdio.h"
#include "windows.h"

HANDLE hFile;  //可访问的文件句柄
pfile_entity peHeader;  // The header of PE file
void hh_init(char *fileName)
{
	char path[100];
	strcpy(path, fileName);
	//返回一个可访问的文件句柄
	hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		hFile = NULL;
		printf("Can not open the file!");
	}
	peHeader->_dos_header = (IMAGE_DOS_HEADER *)malloc(sizeof(IMAGE_DOS_HEADER));
	peHeader->_nt_headers = (IMAGE_NT_HEADERS *)malloc(sizeof(IMAGE_NT_HEADERS));
	peHeader->_sec_header = (IMAGE_SECTION_HEADER *)malloc(sizeof(IMAGE_SECTION_HEADER) * 3);
}

int hh_read_dos_head(pfile_entity dosHeader)
{
	if (dosHeader->_dos_header == NULL)
	{
		dosHeader->_dos_header = (IMAGE_DOS_HEADER *)malloc(sizeof(IMAGE_DOS_HEADER));
		LPDWORD dwRead;
		//读取DOS头
		ReadFile(hFile, &(dosHeader->_dos_header), sizeof(dosHeader->_dos_header), dwRead, NULL);
		if (*dwRead == sizeof(dosHeader->_dos_header))
		{
			peHeader->_dos_header = dosHeader->_dos_header;
			return *dwRead;
		}
	}
	return sizeof(dosHeader->_dos_header);
}

int hh_read_NT_head(pfile_entity ntHeader)
{
	if (ntHeader->_nt_headers == NULL)
	{
		LPDWORD dwRead;
		ntHeader->_nt_headers = (IMAGE_NT_HEADERS *)malloc(sizeof(IMAGE_NT_HEADERS));
		if (peHeader->_dos_header->e_magic == IMAGE_DOS_SIGNATURE)  //是不是有效的DOS头
		{   //定位NT头
			if (SetFilePointer(hFile, peHeader->_dos_header->e_lfanew, NULL, FILE_BEGIN) != -1)
			{  //读取NT头
				ReadFile(hFile, &ntHeader->_nt_headers, sizeof(ntHeader->_nt_headers), dwRead, NULL);
				if (*dwRead == sizeof(ntHeader->_nt_headers))
				{
					peHeader->_nt_headers = ntHeader->_nt_headers;
					return *dwRead;
				}
			}
		}
		return 0;
	}
	return sizeof(ntHeader->_nt_headers);
}

int hh_read_segment_header(pfile_entity segHeader)
{
	if (segHeader->_sec_header == NULL)
	{
		LPDWORD dwRead;
		segHeader->_sec_header = (IMAGE_SECTION_HEADER *)malloc(sizeof(IMAGE_SECTION_HEADER) * 3);
		//定位节区头
		if (SetFilePointer(hFile, peHeader->_dos_header->e_lfanew + sizeof(IMAGE_NT_HEADERS), NULL, FILE_BEGIN) != -1)
		{  //读取节区头
			ReadFile(hFile, &segHeader->_sec_header, sizeof(IMAGE_SECTION_HEADER) * 3, NULL, NULL);
			if (*dwRead == sizeof(segHeader->_sec_header))
			{
				peHeader->_sec_header = segHeader->_sec_header;
				return *dwRead;
			}
		}
	}
	return sizeof(segHeader->_sec_header);
}
void hh_desponse(pfile_entity header)
{
	free(header->_dos_header);
	free(header->_nt_headers);
	free(header->_sec_header);
	free(peHeader->_dos_header);
	free(peHeader->_nt_headers);
	free(peHeader->_sec_header);
}

pfile_export hh_PrintExportTable(pfile_entity nt)
{
	if (nt->_nt_headers != NULL)
	{
		DWORD RAWOfExportTable = RVAToRAW(nt->_nt_headers->
			OptionalHeader.DataDirectory[0].VirtualAddress);

		DWORD sizeOfExportTable = nt->_nt_headers->
			OptionalHeader.DataDirectory[0].Size;

		//struct export table
		pfile_export exTable;
		exTable = (file_export *)malloc(sizeof(file_export));

		// for the function load EXPORT_TABLE
		PIMAGE_EXPORT_DIRECTORY export_directory;
		export_directory = (IMAGE_EXPORT_DIRECTORY *)malloc
			(sizeof(IMAGE_EXPORT_DIRECTORY));

		//select export table section
		if (SetFilePointer(hFile, RAWOfExportTable, NULL, FILE_BEGIN) != -1)
		{  //read export table
			ReadFile(hFile, &export_directory, sizeOfExportTable, NULL, NULL);

			// struct export function
			pthunk export_function;
			export_function = (thunk *)malloc(sizeof(thunk)
				*export_directory->NumberOfFunctions);

			exTable->_funcs = export_function;

			//load export table 
			SetFilePointer(hFile, hh_RVAToRAW(export_directory->Name), NULL, FILE_BEGIN) != -1 && 
				ReadFile(hFile, &exTable->_name, 40, NULL, NULL);
			exTable->_total_funcs = export_directory->NumberOfFunctions;
			exTable->_named_funcs = export_directory->NumberOfNames;

			for (int i = 0; i < export_directory->NumberOfFunctions; i++)
			{
				//load thunk
				SetFilePointer(hFile, hh_RVAToRAW(export_directory->AddressOfFunctions), NULL, FILE_BEGIN) != -1 &&
					ReadFile(hFile, &export_function->_func_addr, export_directory->NumberOfFunctions, NULL, NULL);
				SetFilePointer(hFile, hh_RVAToRAW(export_directory->AddressOfNames), NULL, FILE_BEGIN) != -1 &&
					ReadFile(hFile, &export_function->_func_name, export_directory->NumberOfNames, NULL, NULL);
				SetFilePointer(hFile, hh_RVAToRAW(export_directory->AddressOfNameOrdinals), NULL, FILE_BEGIN) != -1 &&
					ReadFile(hFile, &export_function->_number._origin, export_directory->NumberOfNames, NULL, NULL);
			}
		}
	}
}
//RVAToRAW
DWORD hh_RVAToRAW(DWORD virtualAddress)
{
	DWORD RAW;
	//The numbers of section
	WORD numberOfSections = peHeader->
		_nt_headers->FileHeader.NumberOfSections;

	for (int i = 0; i < numberOfSections; i++)
	{
		if (virtualAddress >= peHeader->_sec_header[i].VirtualAddress&&
			virtualAddress <= peHeader->_sec_header[i].VirtualAddress +
			peHeader->_sec_header[i].Misc.VirtualSize)
		{
			RAW = peHeader->_sec_header[i].PointerToRawData;
			return RAW;
		}
	}
	return 0;
}