typedef struct 
{
	unsigned  __int64		inode;
	WCHAR	*uni_name;
	char	*ans_name; // file name + ext
	char	*ans_ext; // file ext
	DWORD	len; // nam len
	DWORD	sz;
	__int64 file_data_size; // file size
	__int64 file_last_change_date; // file size
}FS_FILE;

typedef struct
{
	FS_FILE *fle;
	DWORD	fl_c;
	FS_FILE *fld;
	DWORD	fd_c;
}FS_FF;

typedef struct
{
	char		*pth;	// ������� ���� ������� ������ 
	FS_FILE		*token; // ������ �������� ����� (�:\temp\dir) 
	DWORD		t_cnt; // ���������� ��������� � ������ token

}PATH_TOKEN;
