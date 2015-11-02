#include "hh_fengine.h"
#include "stdio.h"
#include "windows.h"

HANDLE hFile;  //可访问的文件句柄
pfile_entity peHeader;  // The header of PE file

pfile_entity hh_init (char *fileName)
{
	/*char path [100];
	strcpy (path, fileName);*/
//#ifdef UNICODE
//	wchar_t path [100];
//	size_t n = MultiByteToWideChar (CP_ACP, 0, 
//		(const char*)fileName, strlen (fileName), NULL, 0);
//	MultiByteToWideChar (CP_ACP, 0, 
//		fileName, strlen (fileName), path, n);	
//#else
//	char path [100];
//	strcpy (path, fileName);
//#endif

	hFile = CreateFileA (fileName, 
			GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 
			NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		printf ("Can not open the file!\n");
		return NULL; 
	}

	// for file engine..
	peHeader = (pfile_entity) calloc (1, sizeof (file_entity));

	// peHeader->_dos_header = 
	// 	(IMAGE_DOS_HEADER *) calloc (sizeof(IMAGE_DOS_HEADER));

	// peHeader->_nt_headers = 
	// 	(IMAGE_NT_HEADERS *) calloc (sizeof(IMAGE_NT_HEADERS));

	return peHeader;

	// peHeader->_sec_header = 
	// 	(IMAGE_SECTION_HEADER *) malloc (sizeof(IMAGE_SECTION_HEADER));
}


int hh_read_dos_head (pfile_entity dosHeader)
{
	DWORD dwRead = 0; // = malloc (sizeof (DWORD));
	int beRead = sizeof (IMAGE_DOS_HEADER);

	if (dosHeader -> _dos_header)
		return beRead;

	dosHeader -> _dos_header = (PIMAGE_DOS_HEADER) 
			calloc (1, beRead);

	if (! dosHeader -> _dos_header)
		return 0;

	ReadFile (hFile, (dosHeader -> _dos_header), 
			beRead, &dwRead, NULL);

	if (dwRead == beRead) 
		return dwRead;

	return 0;
}

pfile_import ez_read_import_tables (pfile_entity _imp, int* _imp_num) {

	return NULL;
}

int hh_read_NT_head(pfile_entity ntHeader)
{
	DWORD dwRead = 0;
	int beRead = sizeof (IMAGE_NT_HEADERS);
	if (ntHeader -> _nt_headers)
		return beRead;

	ntHeader->_nt_headers = (PIMAGE_NT_HEADERS)
		calloc(1, beRead);
	if (! ntHeader -> _nt_headers)
		return 0;

	if (hh_read_dos_head (ntHeader) && 
		peHeader-> _dos_header -> e_magic == 
			IMAGE_DOS_SIGNATURE)
	{   //定位NT头
		if (SetFilePointer (hFile, 
					peHeader -> _dos_header -> 
					e_lfanew,
					NULL, FILE_BEGIN) != -1)
		{  //读取NT头
			ReadFile (hFile, 
					ntHeader -> _nt_headers, 
					beRead, &dwRead, NULL);

			if (dwRead == beRead)
				return dwRead;
		}
	}

	return 0;
}

int hh_read_segment_header (pfile_entity segHeader)
{
	int section_hdr_num = 0,
		tmp = 0,
		beRead = 0;
	DWORD dwRead = 0;

	tmp = segHeader -> _nt_headers == NULL ||
		!! hh_read_NT_head (segHeader);

	if (tmp && segHeader -> _nt_headers != NULL)
		section_hdr_num = segHeader -> 
			_nt_headers -> 
			FileHeader.NumberOfSections;
	else
		return 0; // read NT header error ...

	beRead = sizeof (IMAGE_SECTION_HEADER) * 
		section_hdr_num;

	if (segHeader -> _sec_header)
		return beRead;
	
	segHeader->_sec_header = 
		(PIMAGE_SECTION_HEADER) calloc(1, beRead);

	if (SetFilePointer (hFile, 
			peHeader -> _dos_header -> 
			e_lfanew + sizeof (IMAGE_NT_HEADERS), 
			NULL, FILE_BEGIN) != -1)
	{  //读取节区头
		ReadFile (hFile, segHeader -> _sec_header,
			beRead, &dwRead, NULL);
		if (dwRead == beRead)
			return beRead;
			// peHeader->_sec_header = segHeader->_sec_header;
	}
	return 0; // sizeof();
}

/*
   the argument is out of usage :-(
*/
void hh_desponse(pfile_entity header)
{
	if (peHeader) {

		if (peHeader -> _dos_header)
			free (peHeader -> _dos_header);

		if (peHeader -> _dos_stub)
			free (peHeader -> _dos_stub);

		if (peHeader -> _nt_headers)
			free (peHeader -> _nt_headers);

		if (peHeader -> _sec_header)
			free (peHeader -> _sec_header);

		peHeader -> _dos_header = NULL;
		peHeader -> _nt_headers = NULL;
		peHeader -> _dos_stub   = NULL;
		peHeader -> _sec_header = NULL;

		free (peHeader);
		peHeader = NULL;
	}

	if (hFile != INVALID_HANDLE_VALUE) CloseHandle (hFile);
}

pfile_export hh_PrintExportTable(pfile_entity nt)
{
	pfile_export exTable = NULL;
	if (nt->_nt_headers != NULL)
	{
		PIMAGE_EXPORT_DIRECTORY export_directory;
		DWORD RAWOfExportTable = hh_RVAToRAW(nt->_nt_headers->
			OptionalHeader.DataDirectory[0].VirtualAddress);

		DWORD sizeOfExportTable = nt->_nt_headers->
			OptionalHeader.DataDirectory[0].Size;

		//struct export table
		exTable = (file_export *)malloc(sizeof(file_export));

		// for the function load EXPORT_TABLE
		export_directory = (IMAGE_EXPORT_DIRECTORY *)malloc
			(sizeof(IMAGE_EXPORT_DIRECTORY));

		//select export table section
		if (SetFilePointer(hFile, RAWOfExportTable, NULL, FILE_BEGIN) != -1)
		{
			int i = 0;
			pthunk export_function;
			//read export table
			ReadFile(hFile, &export_directory, sizeOfExportTable, NULL, NULL);

			// struct export function
			
			export_function = (thunk *) malloc(sizeof(thunk)
				* export_directory -> NumberOfFunctions);

			exTable->_funcs = export_function;

			//load export table 
			SetFilePointer(hFile, hh_RVAToRAW(export_directory->Name), NULL, FILE_BEGIN) != -1 && 
				ReadFile(hFile, &exTable->_name, 40, NULL, NULL);
			exTable->_total_funcs = export_directory->NumberOfFunctions;
			exTable->_named_funcs = export_directory->NumberOfNames;

			for (; i < (int) export_directory->NumberOfFunctions; i++)
			{
				//load thunk
				SetFilePointer (hFile, hh_RVAToRAW(export_directory->AddressOfFunctions), NULL, FILE_BEGIN) != -1 &&
					ReadFile (hFile, &export_function->_func_addr, export_directory->NumberOfFunctions, NULL, NULL);
				SetFilePointer (hFile, hh_RVAToRAW(export_directory->AddressOfNames), NULL, FILE_BEGIN) != -1 &&
					ReadFile (hFile, &export_function->_func_name, export_directory->NumberOfNames, NULL, NULL);
				SetFilePointer (hFile, hh_RVAToRAW(export_directory->AddressOfNameOrdinals), NULL, FILE_BEGIN) != -1 &&
					ReadFile (hFile, &export_function->_number._origin, export_directory->NumberOfNames, NULL, NULL);
			}
		}
		return exTable;
	}
	return exTable;
}
//RVAToRAW
DWORD hh_RVAToRAW(DWORD virtualAddress)
{
	DWORD RAW;
	int i = 0;
	//The numbers of section
	WORD numberOfSections = peHeader->
		_nt_headers->FileHeader.NumberOfSections;

	for (; i < numberOfSections; i++)
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
