#include <intr.h>
#include <pic.h>
#include <fbcon.h>

#define SYSCALL_INTR_NO	0x80

enum SYSCCALL_NO {
	SYSCALL_PUTC,
	MAX_SYSCALL_NUM
};

unsigned long long do_syscall_interrupt(
	unsigned long long syscall_id, unsigned long long arg1,
	unsigned long long arg2 __attribute__((unused)),
	unsigned long long arg3 __attribute__((unused)))
{
	unsigned long long ret_val = 0;

	switch (syscall_id) {
	case SYSCALL_PUTC:
		putc((char)arg1);
		break;
	}

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
