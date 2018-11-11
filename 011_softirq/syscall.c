#include <intr.h>
#include <pic.h>
#include <fbcon.h>

#define SYSCALL_INTR_NO	0x80

unsigned long long do_syscall_interrupt(
	unsigned long long syscall_id, unsigned long long arg1,
	unsigned long long arg2, unsigned long long arg3)
{
	unsigned long long ret_val = 0xbeefcafe01234567;

	puth(syscall_id, 16);
	puts("\r\n");
	puth(arg1, 16);
	puts("\r\n");
	puth(arg2, 16);
	puts("\r\n");
	puth(arg3, 16);
	puts("\r\n");

	/* PICへ割り込み処理終了を通知(EOI) */
	set_pic_eoi(SYSCALL_INTR_NO);

	return ret_val;
}

void syscall_handler(void);
void syscall_init(void)
{
	set_intr_desc(SYSCALL_INTR_NO, syscall_handler);
	enable_pic_intr(SYSCALL_INTR_NO);
}
