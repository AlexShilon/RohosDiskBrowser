#include "pub.h"

struct jmp_far
{
  BYTE instr_push;  // push
  DWORD arg;         //�������� push
  BYTE  instr_ret;    // ret
};


char old[6]; // 6 ���������� ���� ������ �������
DWORD adr_fnx; //������� ����� ������������ �������
DWORD written; 
jmp_far jump; 
HANDLE h_proc;

void inj_code(char *lib,char *fnx,long addr_new_fnx)
{

  //char buf[256];
  //������� ������� ���������� ����� ������� ��� ���������
	adr_fnx = (DWORD)GetProcAddress(GetModuleHandle(lib),fnx);
/*
  if(!adr_fnx)
  {
    sprintf(buf,"������ ����� ����� ������� \" %s \" � \" %s\"",fnx,lib);
    MessageBox(0, buf, "Error!", MB_OK );
    return;
  }*/
	h_proc = GetCurrentProcess();
	jump.instr_push = 0x68;
	jump.arg = (DWORD)addr_new_fnx;
	jump.instr_ret = 0xC3;
	ReadProcessMemory(h_proc,(void*) adr_fnx,(void*)&old, 6, &written);
	WriteProcessMemory(h_proc, (void*)adr_fnx,(void*)&jump, sizeof(jmp_far), &written);
}

void make_real_rf(void)
{
	WriteProcessMemory(h_proc, (void*)adr_fnx,(void*)&old, 6, &written);
}

void make_virtual_rf()
{
	WriteProcessMemory(h_proc, (void*)adr_fnx,(void*)&jump, sizeof(jmp_far), &written);
}
