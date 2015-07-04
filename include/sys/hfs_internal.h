
#ifndef HFS_INTERNAL_H
#define HFS_INTERNAL_H

// BGH - Definitions of HFS vnops that we will need to emulate
// including supporting structures.

struct hfs_journal_info {
	off_t	jstart;
	off_t	jsize;
};

struct user32_access_t {
	uid_t     uid;              /* IN: effective user id */
	short     flags;            /* IN: access requested (i.e. R_OK) */
	short     num_groups;       /* IN: number of groups user belongs to */
	int       num_files;        /* IN: number of files to process */
	user32_addr_t      file_ids;        /* IN: array of file ids */
	user32_addr_t      groups;          /* IN: array of groups */
	user32_addr_t      access;          /* OUT: access info for each file (0 for 'has access') */
};

struct user64_access_t {
	uid_t           uid;                    /* IN: effective user id */
	short           flags;                  /* IN: access requested (i.e. R_OK) */
	short           num_groups;             /* IN: number of groups user belongs to */
	int             num_files;              /* IN: number of files to process */
	user64_addr_t   file_ids;               /* IN: array of file ids */
	user64_addr_t   groups;                 /* IN: array of groups */
	user64_addr_t   access;                 /* OUT: access info for each file (0 for 'has access') */
};

struct user32_ext_access_t {
	uint32_t   flags;           /* IN: access requested (i.e. R_OK) */
	uint32_t   num_files;       /* IN: number of files to process */
	uint32_t   map_size;        /* IN: size of the bit map */
	user32_addr_t  file_ids;        /* IN: Array of file ids */
	user32_addr_t     bitmap;          /* OUT: hash-bitmap of interesting directory ids */
	user32_addr_t access;          /* OUT: access info for each file (0 for 'has access') */
	uint32_t   num_parents;   /* future use */
	user32_addr_t parents;   /* future use */
};

struct user64_ext_access_t {
	uint32_t      flags;        /* IN: access requested (i.e. R_OK) */
	uint32_t      num_files;    /* IN: number of files to process */
	uint32_t      map_size;     /* IN: size of the bit map */
	user64_addr_t   file_ids;     /* IN: array of file ids */
	user64_addr_t   bitmap;       /* IN: array of groups */
	user64_addr_t   access;       /* OUT: access info for each file (0 for 'has access') */
	uint32_t      num_parents;/* future use */
	user64_addr_t   parents;/* future use */
};

/*
 * HFS specific fcntl()'s
 */
#define HFS_BULKACCESS      (FCNTL_FS_SPECIFIC_BASE + 0x00001)
#define HFS_GET_MOUNT_TIME  (FCNTL_FS_SPECIFIC_BASE + 0x00002)
#define HFS_GET_LAST_MTIME  (FCNTL_FS_SPECIFIC_BASE + 0x00003)
#define HFS_GET_BOOT_INFO   (FCNTL_FS_SPECIFIC_BASE + 0x00004)
#define HFS_SET_BOOT_INFO   (FCNTL_FS_SPECIFIC_BASE + 0x00005)

/* HFS FS CONTROL COMMANDS */

#define HFSIOC_RESIZE_PROGRESS  _IOR('h', 1, u_int32_t)
#define HFS_RESIZE_PROGRESS  IOCBASECMD(HFSIOC_RESIZE_PROGRESS)

#define HFSIOC_RESIZE_VOLUME  _IOW('h', 2, u_int64_t)
#define HFS_RESIZE_VOLUME  IOCBASECMD(HFSIOC_RESIZE_VOLUME)

#define HFSIOC_CHANGE_NEXT_ALLOCATION  _IOWR('h', 3, u_int32_t)
#define HFS_CHANGE_NEXT_ALLOCATION  IOCBASECMD(HFSIOC_CHANGE_NEXT_ALLOCATION)
/* Magic value for next allocation to use with fcntl to set next allocation
 * to zero and never update it again on new block allocation.
 */
#define HFS_NO_UPDATE_NEXT_ALLOCATION 	0xffffFFFF

#define HFSIOC_GETCREATETIME  _IOR('h', 4, time_t)
#define HFS_GETCREATETIME  IOCBASECMD(HFSIOC_GETCREATETIME)

#define HFSIOC_SETBACKINGSTOREINFO  _IOW('h', 7, struct hfs_backingstoreinfo)
#define HFS_SETBACKINGSTOREINFO  IOCBASECMD(HFSIOC_SETBACKINGSTOREINFO)

#define HFSIOC_CLRBACKINGSTOREINFO  _IO('h', 8)
#define HFS_CLRBACKINGSTOREINFO  IOCBASECMD(HFSIOC_CLRBACKINGSTOREINFO)

#define HFSIOC_BULKACCESS _IOW('h', 9, struct user32_access_t)
#define HFS_BULKACCESS_FSCTL IOCBASECMD(HFSIOC_BULKACCESS)

#define HFSIOC_SETACLSTATE  _IOW('h', 10, int32_t)
#define HFS_SETACLSTATE  IOCBASECMD(HFSIOC_SETACLSTATE)

#define HFSIOC_PREV_LINK  _IOWR('h', 11, u_int32_t)
#define HFS_PREV_LINK  IOCBASECMD(HFSIOC_PREV_LINK)

#define HFSIOC_NEXT_LINK  _IOWR('h', 12, u_int32_t)
#define HFS_NEXT_LINK  IOCBASECMD(HFSIOC_NEXT_LINK)

#define HFSIOC_GETPATH  _IOWR('h', 13, pathname_t)
#define HFS_GETPATH  IOCBASECMD(HFSIOC_GETPATH)

/* Enable/disable extent-based extended attributes */
#define HFSIOC_SET_XATTREXTENTS_STATE  _IOW('h', 14, u_int32_t)
#define HFS_SET_XATTREXTENTS_STATE  IOCBASECMD(HFSIOC_SET_XATTREXTENTS_STATE)

#define HFSIOC_EXT_BULKACCESS _IOW('h', 15, struct user32_ext_access_t)
#define HFS_EXT_BULKACCESS_FSCTL IOCBASECMD(HFSIOC_EXT_BULKACCESS)

#define HFSIOC_MARK_BOOT_CORRUPT _IO('h', 16)
#define HFS_MARK_BOOT_CORRUPT IOCBASECMD(HFSIOC_MARK_BOOT_CORRUPT)

#define HFSIOC_GET_JOURNAL_INFO	_IOR('h', 17, struct hfs_journal_info)
#define	HFS_FSCTL_GET_JOURNAL_INFO	IOCBASECMD(HFSIOC_GET_JOURNAL_INFO)

#define HFSIOC_SET_VERY_LOW_DISK _IOW('h', 20, u_int32_t)
#define HFS_FSCTL_SET_VERY_LOW_DISK IOCBASECMD(HFSIOC_SET_VERY_LOW_DISK)

#define HFSIOC_SET_LOW_DISK _IOW('h', 21, u_int32_t)
#define HFS_FSCTL_SET_LOW_DISK IOCBASECMD(HFSIOC_SET_LOW_DISK)

#define HFSIOC_SET_DESIRED_DISK _IOW('h', 22, u_int32_t)
#define HFS_FSCTL_SET_DESIRED_DISK IOCBASECMD(HFSIOC_SET_DESIRED_DISK)

#define HFSIOC_SET_ALWAYS_ZEROFILL _IOW('h', 23, int32_t)
#define HFS_SET_ALWAYS_ZEROFILL IOCBASECMD(HFSIOC_SET_ALWAYS_ZEROFILL)

#define HFSIOC_VOLUME_STATUS  _IOR('h', 24, u_int32_t)
#define HFS_VOLUME_STATUS  IOCBASECMD(HFSIOC_VOLUME_STATUS)

/* Disable metadata zone for given volume */
#define HFSIOC_DISABLE_METAZONE	_IO('h', 25)
#define HFS_DISABLE_METAZONE	IOCBASECMD(HFSIOC_DISABLE_METAZONE)

/* Change the next CNID value */
#define HFSIOC_CHANGE_NEXTCNID	_IOWR('h', 26, u_int32_t)
#define HFS_CHANGE_NEXTCNID		IOCBASECMD(HFSIOC_CHANGE_NEXTCNID)

/* Get the low disk space values */
#define	HFSIOC_GET_VERY_LOW_DISK	_IOR('h', 27, u_int32_t)
#define	HFS_FSCTL_GET_VERY_LOW_DISK	IOCBASECMD(HFSIOC_GET_VERY_LOW_DISK)

#define	HFSIOC_GET_LOW_DISK	_IOR('h', 28, u_int32_t)
#define	HFS_FSCTL_GET_LOW_DISK	IOCBASECMD(HFSIOC_GET_LOW_DISK)

#define	HFSIOC_GET_DESIRED_DISK	_IOR('h', 29, u_int32_t)
#define	HFS_FSCTL_GET_DESIRED_DISK	IOCBASECMD(HFSIOC_GET_DESIRED_DISK)

// END of definitions

#endif
