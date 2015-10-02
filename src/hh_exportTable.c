#include <stdio.h>

void PrintExportTable(pfile_entity nt)
{
	if (nt->_nt_headers != NULL)
	{
		//struct export table
		pfile_export exTable;
		exTable=(file_export *)malloc(sizeof(file_export));

		//struct export function
		pthunk export_function;
		export_function=(thunk *)malloc(sizeof(thunk));

		//load EXPORT_TABLE
		PIMAGE_EXPORT_DIRECTORY export_directory;
		export_directory=(IMAGE_EXPORT_DIRECTORY *)malloc
			(sizeof(IMAGE_EXPIRT_DIRECTORY));

			//The numbers of section
			WORD numberOfSections = nt->
			_nt_headers_.FileHeader.NumberOfSections;

		DWORD virtualAddress = nt->_nt_headers->
			OptionalHeader.DataDirectory[0].VirtualAddress;
		DWORD sizeOfExportTable = nt->_nt_headers->
			OptionalHeader.DataDirectory[0].Size;

		for (int i = 0; i < numberOfSections; i++)
		{
			if (virtualAddress >= nt->_sec_header[i].VirtualAddress&&
				virtualAddress <= nt->(_sec_header[0].VirtualAddress +
				nt->_sec_header[i].Misc > VirtualSize))
			{   //select export table section
				if (SetFilePointer(hFile, nt->_secheader[0].PointerToRawData,
					NULL, FILE_BEGIN) != -1)
				{  //read export table
					ReadFile(hFile, &export_directory, sizeOfExportTable, NULL, NULL)
						
				}
			}
		}
	}
}
void RVAToRAW()
{

}