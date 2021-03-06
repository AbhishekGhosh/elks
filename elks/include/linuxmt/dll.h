#ifndef LX86_LINUXMT_DLL_H
#define LX86_LINUXMT_DLL_H

/*
 *	DLL structures
 */

#define MAX_DLLS	8

#define DLL_USED	1
#define DLL_UNUSED	0

struct dll_entry {
    int 		d_state;
    struct inode	*d_inode;
    unsigned short	d_cseg;
};

#endif
