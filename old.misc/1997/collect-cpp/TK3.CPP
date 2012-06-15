
// Article Test King 	Ver 1.00  // By DanSei  46K MEM
//1996

#include<stdio.h>
#include<io.h>
#include<fcntl.h>
#include<conio.h>
#include<stdlib.h>
static int _num_info_lost = 0;

// ��������ڴ�
void stream_comp_memreset(void *mem, size_t s) {
	char *p = (char *)mem; 
	for (size_t i = 0; i < s; i++) p[i] = 0; 
}

// ���Ƚ�
// ref[]	�ο���, ����size_ref
// obj[]	ʵ����, ����size_obj
// search_depth	�Ƚ���� (�������0)
// same_size	��Ϊ������ͬ����С����
// cr		�ȽϽ�����ݵ��б�, ���ΪNULL�򲻴洢�ȽϽ��
//			�洢�ȽϽ��, ��Ϊ��������: 
//				��ͬ(1): ����Ϊ�ǲ���ͬ������
//				����(2): ����Ϊ�Ƕ��������
//				ȱ��(3): ����Ϊ��ȱ�ٵ�����
//				����(0): ��ʾ�б�����
//			����ʱ�� (����, refλ��, objλ��, ����, refλ��, objλ��...), ���б������4���������ڴ��
//				��ͬ�� ��ͬ�� ������ ȱ����
//			������ռ������λ��
// psize_cr	cr�ṩ�ĳ���, ͬʱ���ڷ���ʵ��ʹ�õĳ���(����������)
//
// ��������ʱ����STREAM_COMP_ERROR, ���򷵻� 0

// ���ڲ�ͬ���͵�������, Ӧ���ṩ��ͬ���ͼ�����(==)������Ķ���
// ������������(��Ƕ�����, ϡ�������), �����ṩ��������Ԫ����ȡ����([])�����ͼ�����(==)����

#define STREAM_COMP_UNMATCH		0x1
#define STREAM_COMP_EXTRA		0x2
#define STREAM_COMP_LOST		0x3

#define STREAM_COMP_UNMATCH_C		'x'
#define STREAM_COMP_EXTRA_C		'e'
#define STREAM_COMP_LOST_C		'l'

#define STREAM_COMP_FILLBLANK_C		' '

#define STREAM_COMP_ERROR		-1

int  InfoHeight=7;

void CLVersion(int k);

typedef long		LONG;
typedef unsigned char	BYTE;
typedef BYTE		*LPBYTE;
typedef char 		CHAR;
typedef CHAR		*LPSTR, *LPCTSTR, *LPTSTR;
typedef unsigned long	DWORD;

// ���Ƚ� Ex

// ���ֽڴ����ִ������͡����ڱȽ϶����Լ����ִ�
struct MBCS {
	LPBYTE	_str;

	LONG operator =(LPBYTE o_o) { return (LONG)(_str = o_o); }
	LONG operator =(LPCTSTR o_o) { return (LONG)(_str = (LPBYTE)o_o); }
	LONG operator [](int index);

	MBCS(LPBYTE o_o) { _str = o_o; }
	MBCS(LPCTSTR o_o) { _str = (LPBYTE)o_o; }
};

LONG MBCS::operator [](int index) {
	DWORD r;
	LPBYTE p = _str;

	if (index != 0) {
		if (index > 0) for (int i = 0; i < index; i++) {
			if (p[0] & 0x80) p++;
			p++;
		} else for (int i = 0; i > index; i--) {
			if (p[-1] & 0x80) p--;
			p--;
		}
	}
	r = p[0];
	if (r & 0x80) r = (r << 8) | p[1];

	return (LONG)r;
}

int  stream_comp_pretty_result(size_t *cr, size_t size_cr, char *rbuf, size_t *psize_rbuf, char *obuf, size_t *psize_obuf);

int  reset_num_info_lost();

#include <stddef.h>

int stream_comp(MBCS ref, MBCS obj, size_t size_ref, size_t size_obj, size_t search_depth, size_t same_size, size_t *cr, size_t *psize_cr) {
	size_t	pr_press = 0;		// ref��ȷ��λ�� (��δʹ��)
	size_t	po_press = 0;		// obj��ȷ��λ�� (��δʹ��)
	size_t	pr_cur = 0;		// ref�ĵ�ǰλ��
	size_t	po_cur = 0;		// obj�ĵ�ǰλ��
	LONG	rd;			// ref�ĵ�ǰ����
	LONG	od;			// obj�ĵ�ǰ����
	size_t	pr_f, po_f;		// ���ڲ��ҵ�λ�ñ���
	size_t	pcr = 0;		// �б��ĵ�ǰλ��
	int	same = 0;
	size_t	*save_match	= cr;
	size_t	*save_unmatch	= cr + 1;
	size_t	*save_extra	= cr + 2;
	size_t	*save_lost	= cr + 3;
	size_t	size_cr = 0;
	size_t	cr_used = 0;

	// ��ʼ������

	if (psize_cr) size_cr = *psize_cr;
	if (search_depth < 1) return STREAM_COMP_ERROR;

	switch (size_cr) {
	case 0: save_match	= NULL;
	case 1: save_unmatch	= NULL;
	case 2: save_extra	= NULL;
	case 3: save_lost	= NULL;
		cr = NULL;
		cr_used = size_cr;
	default:
		cr_used = 4;
		pcr = 4;
	}
	if (pcr + 3 >= size_cr) cr = NULL;
	if (save_lost)		*save_lost	= 0;
	if (save_extra)		*save_extra	= 0;
	if (save_unmatch)	*save_unmatch	= 0;
	if (save_match)		*save_match	= 0;

	// �Ƚϸ��ǲ��� (���������ص����ֲ�����min(size_ref,size_obj), ��Ҫ����ʵ�����)

	while (pr_cur < size_ref && po_cur < size_obj) {
		rd = ref[pr_cur];
		od = obj[po_cur];

		if (rd == (LONG)od) {
			if (save_match) (*save_match)++;
			goto moveright;
		}

		// �Ƿ�ȱ��?
		for (pr_f = pr_cur; pr_f < pr_cur + search_depth && pr_f < size_ref; pr_f++) {
			LONG rd = ref[pr_f];
			if (rd == (LONG)od) {
				// �ҵ�һ����ͬ��, �жϸõ㸽���Ƿ���ͬ
				same = 1;
				for (size_t pr_f2 = pr_f; pr_f2 < pr_f + same_size && pr_f2 < size_ref; pr_f2++) {
					LONG rd = ref[pr_f2];
					LONG od = obj[po_cur + pr_f2 - pr_f];
					if (!(rd == (LONG)od)) same = 0;
				}
				if (same) {
					// ��ָ��������ҵ�����ͬ��, ��Ϊȱ��.
					// ȱ�ٵĲ�����pr_cur...pr_f(����pr_cur)
					for (pr_f2 = pr_cur; pr_f2 < pr_f; pr_f2++) {
						if (save_lost) (*save_lost)++;
						if (cr != NULL) {
							cr[pcr++] = STREAM_COMP_LOST;
							cr[pcr++] = pr_f2;
							cr[pcr++] = po_cur;
							cr_used += 3;
							if (pcr + 3 >= size_cr) cr = NULL;
						} else _num_info_lost++;
					}
					// ��Ϊ�ⲿ��ȱ��, ��������ȥ
					pr_cur = pr_f;
					goto moveright;
				}
				// ������ͬ
				continue;
			}
		}

		// �Ƿ����?
		for (po_f = po_cur; po_f < po_cur + search_depth && po_f < size_obj; po_f++) {
			LONG od = obj[po_f];
			if (rd == (LONG)od) {
				// �ҵ�һ����ͬ��, �жϸõ㸽���Ƿ���ͬ
				same = 1;
				for (size_t po_f2 = po_f; po_f2 < po_f + same_size && po_f2 < size_obj; po_f2++) {
					LONG od = obj[po_f2];
					LONG rd = ref[pr_cur + po_f2 - po_f];
					if (!(rd == (LONG)od)) same = 0;
				}
				if (same) {
					// ��ָ��������ҵ�����ͬ��, ��Ϊ����.
					// ����Ĳ�����po_cur...po_f(����po_cur)
					for (po_f2 = po_cur; po_f2 < po_f; po_f2++) {
						if (save_extra) (*save_extra)++;
						if (cr != NULL) {
							cr[pcr++] = STREAM_COMP_EXTRA;
							cr[pcr++] = pr_cur;
							cr[pcr++] = po_f2;
							cr_used += 3;
							if (pcr + 3 >= size_cr) cr = NULL;
						} else _num_info_lost++;
					}
					// ��Ϊ�ⲿ�ֶ���, ���زο�����ȥ
					po_cur = po_f;
					goto moveright;
				}
				// ������ͬ
				continue;
			}
		}

		// ������
		if (save_unmatch) (*save_unmatch)++;
		if (cr != NULL) {
			cr[pcr++] = STREAM_COMP_UNMATCH;
			cr[pcr++] = pr_cur;
			cr[pcr++] = po_cur;
			cr_used += 3;
			if (pcr + 3 >= size_cr) cr = NULL;
		} else _num_info_lost++;

moveright:	// ����ȷ��
		pr_cur++;
		po_cur++;
		if (pr_press + search_depth <= pr_cur) {
			pr_press++;
			po_press++;
		}
	} // while

	// ���ǲ��ֱȽ����, Ȼ��ȽϽ�β

	if (pr_cur < size_ref) {
		// �ο������ж���, ��ȱ�ٴ���
		// ȱ�ٵĲ�����pr_cur...size_ref(����pr_cur, ������size_ref)
		for (pr_f = pr_cur; pr_f < size_ref; pr_f++) {
			if (save_lost) (*save_lost)++;
			if (cr != NULL) {
				cr[pcr++] = STREAM_COMP_LOST;
				cr[pcr++] = pr_f;
				cr[pcr++] = po_cur;
				cr_used += 3;
				if (pcr + 3 >= size_cr) cr = NULL;
			} else _num_info_lost++;
		}
	}
	if (po_cur < size_obj) {
		// ʵ�������ж���, �����ദ��
		// ����Ĳ�����po_cur...size_obj(����po_cur, ������size_obj)
		for (po_f = po_cur; po_f < size_obj; po_f++) {
			if (save_extra) (*save_extra)++;
			if (cr != NULL) {
				cr[pcr++] = STREAM_COMP_EXTRA;
				cr[pcr++] = pr_cur;
				cr[pcr++] = po_f;
				cr_used += 3;
				if (pcr + 3 >= size_cr) cr = NULL;
			} else _num_info_lost++;
		}
	}

	// ���ӽ�����
	if (cr != NULL) {
		cr[pcr++] = 0;
		cr[pcr++] = 0;
		cr[pcr++] = 0;
		cr_used += 3;
		if (pcr + 3 >= size_cr) cr = NULL;
	} else _num_info_lost++;

	if (psize_cr) *psize_cr = cr_used;
	return 0;
}

/*
 * �������ȽϽ��
 *
 * cr		���ȽϽ��
 * size_cr	���ȽϽ���ĳ���(����ͷ��4����Ԫ�ͽ�����3����Ԫ)
 * rbuf		�ο����������ȽϽ��
 * psize_rbuf	rbuf�ṩ�ĳ���, ͬʱ���ڷ���ʵ��ʹ�õĳ���. ��� <= 0 ������Ҫ�ĳ���
 * obuf		ʵ�����������ȽϽ��
 * psize_obuf	obuf�ṩ�ĳ���, ͬʱ���ڷ���ʵ��ʹ�õĳ���. ��� <= 0 ������Ҫ�ĳ���
 *
 * �����ȽϽ���и��ӽ�����'\0'
 */
int	 stream_comp_pretty_result(size_t *cr, size_t size_cr, char *rbuf, size_t *psize_rbuf, char *obuf, size_t *psize_obuf) {
	size_t size_rbuf, size_obuf;
	size_t size_rbuf_used = 0, size_obuf_used = 0; 
	size_t size_rbuf_needed = 0, size_obuf_needed = 0;
	size_t pcr;

	if (cr == NULL) return STREAM_COMP_ERROR;
	if (psize_rbuf == NULL || psize_obuf == NULL) return STREAM_COMP_ERROR;

	size_rbuf = *psize_rbuf; 
	size_obuf = *psize_obuf; 

	pcr = 4; 
	
	if ((size_rbuf == 0) || (size_obuf == 0)) {
		while (pcr + 2 < size_cr && cr[pcr] != 0) {
			size_t rp	= cr[pcr + 1]; 
			size_t op	= cr[pcr + 2]; 
			if (size_rbuf_needed < rp) size_rbuf_needed = rp;
			if (size_obuf_needed < op) size_obuf_needed = op; 
			pcr += 3; 
		}
		*psize_rbuf = size_rbuf_needed + 1; 
		*psize_obuf = size_obuf_needed + 1;
		return 0; 
	}

	if (rbuf != NULL) stream_comp_memreset(rbuf, sizeof(char) * size_rbuf);
	if (obuf != NULL) stream_comp_memreset(obuf, sizeof(char) * size_obuf);
	if (size_cr < 7) return 0;

	while (pcr + 2 < size_cr && cr[pcr] != 0) {
		size_t type	= cr[pcr]; 
		size_t rp	= cr[pcr + 1]; 
		size_t op	= cr[pcr + 2]; 
		switch (type) {
		case STREAM_COMP_UNMATCH:
			if (rp < size_rbuf) { 
				rbuf[rp] = STREAM_COMP_UNMATCH_C;
				if (size_rbuf_used < rp) size_rbuf_used = rp; 
			} else _num_info_lost++; 
			if (op < size_obuf) {
				obuf[op] = STREAM_COMP_UNMATCH_C;
				if (size_obuf_used < op) size_obuf_used = op;
			} else _num_info_lost++; 
			break; 
		case STREAM_COMP_EXTRA:
			if (rp < size_rbuf) {
				rbuf[rp] = STREAM_COMP_LOST_C;
				if (size_rbuf_used < rp) size_rbuf_used = rp; 
			} else _num_info_lost++; 
			if (op < size_obuf) {
				obuf[op] = STREAM_COMP_EXTRA_C;
				if (size_obuf_used < op) size_obuf_used = op; 
			} else _num_info_lost++; 
			break; 
		case STREAM_COMP_LOST:
			if (rp < size_rbuf) { 
				rbuf[rp] = STREAM_COMP_EXTRA_C;
				if (size_rbuf_used < rp) size_rbuf_used = rp; 
			} else _num_info_lost++; 
			if (op < size_obuf) {
				obuf[op] = STREAM_COMP_LOST_C;
				if (size_obuf_used < op) size_obuf_used = op;
			} else _num_info_lost++; 
			break; 
		default: ; 
		}
		pcr += 3; 
	}

	for (pcr = 0; pcr < size_rbuf_used; pcr++)
		if (rbuf[pcr] == 0) rbuf[pcr] = STREAM_COMP_FILLBLANK_C;
	for (pcr = 0; pcr < size_obuf_used; pcr++)
		if (obuf[pcr] == 0) obuf[pcr] = STREAM_COMP_FILLBLANK_C;

	// ������'\0' (�����Ѿ�������memset����, ����ֻ�����Ӽ���
	if (size_rbuf_used < size_rbuf) size_rbuf_used++; 
	if (size_obuf_used < size_obuf) size_obuf_used++;

	*psize_rbuf = size_rbuf_used;
	*psize_obuf = size_obuf_used; 

	return 0;
}

int  stream_comp_mbcs(LPBYTE ref, LPBYTE obj, size_t size_ref, size_t size_obj, size_t search_depth, size_t same_size, size_t *cr, size_t *psize_cr) {
	MBCS _ref(ref);
	MBCS _obj(obj);
	return stream_comp
		(_ref, _obj, size_ref, size_obj, search_depth, same_size, cr, psize_cr);
}

int	 reset_num_info_lost() {
	int i = _num_info_lost;
	_num_info_lost = 0;
	return i;
}

struct CResult {
// engChr, engSym, chnChr * 2, chnSym * 2, other, space, total
	unsigned rec, res, rcc, rcs, rot, rsp, rtot; /* right */
	unsigned wec, wes, wcc, wcs, wot, wsp, wtot; /* wrong */
	unsigned eec, ees, ecc, ecs, eot, esp, etot; /* extra */
	unsigned lec, les, lcc, lcs, lot, lsp, ltot; /* lost  */
};

struct CInfo {
// engChr, engSym, chnChr * 2, chnSym * 2, space, other, total */
	unsigned nec, nes, ncc, ncs, nsp, not, ntot;
};

int compfile(FILE *tmpl, FILE *each, CResult &r, CInfo &itmpl, CInfo &ieach) {
	char *t = new char[16384];
	char *e = new char[16384];
	size_t *rr = new size_t[2048];
	size_t nt, ne;
	size_t rrsize = 2000;
	if (t == NULL || e == NULL || rr == NULL) return 0;
	MBCS ref(t);
	MBCS obj(e);
	fseek(tmpl, 0, SEEK_END);
	nt = (size_t)ftell(tmpl);
	fseek(tmpl, 0, SEEK_SET);
	fseek(each, 0, SEEK_END);
	ne = (size_t)ftell(each);
	fseek(each, 0, SEEK_SET);
	if (nt > 16000) nt = 16000;
	if (ne > 16000) ne = 16000;
	fread(t, 1, nt, tmpl);
	fread(e, 1, ne, each);
	stream_comp(ref, obj, nt, ne, 20, 4, rr, &rrsize);
	r.rcc = rr[0];
	r.wcc = rr[1];
	r.ecc = rr[2];
	r.lcc = rr[3];
	itmpl.ncc = nt;
	ieach.ncc = ne;
	return 1;
}

int main(int argc, char **argv) {
	FILE *feach, *ftmpl;
	CResult r;
	CInfo itmpl, ieach;

	printf("fuzzy compare ģ�����Ƚ�[MBCS/ANSI] л����/�ҿ����� 2001\n"); 
	if ((argc <= 1) || (argc >= 4)) { CLVersion(0); return 2; }
	if (argc >= 3) {
		if ((ftmpl = fopen(argv[2], "rb")) == NULL) {
			perror("Error in source file ");
			return 4;
		}
	} else {
		if ((ftmpl = fopen("TKSource.TXT", "rb"))== NULL) {
			perror("Error in open TKSource.TXT\n");
			return 5;
		}
	}
n:
	if ((feach = fopen(argv[1], "rb")) == NULL) {
		perror("Error in test file ");
		return 10;
	}

 //fsrc

	compfile(ftmpl, feach, r, itmpl, ieach);

	fclose(ftmpl);
	fclose(feach);

	float ss = 0.00;
	ss =
		(float)(r.rcc) / itmpl.ncc -
		(float)(r.wcc + r.ecc + r.lcc) / itmpl.ncc * 5;
	ss *= 100;
	if (ss < 0) ss = 0;

 //Print Result...

	printf("right:%d wrong:%d extra:%d lost:%d\n��ȷ:%d ����:%d ����:%d ȱ��:%d\n",
		r.rcc, r.wcc, r.ecc, r.lcc, 
		r.rcc, r.wcc, r.ecc, r.lcc
		);

 return (int)ss;
}

void CLVersion(int k)
{
	printf("syntax:tk3 <dest> [<src=\"tksource.txt\">]\n\
��ʽ:  tk3 <�Ƚ��ļ�> [<ģ���ļ�,Ĭ��tksource.txt>]\n"); 
}