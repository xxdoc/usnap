
typedef struct _nssvc_t nssvc_t;
typedef struct _nsdrv_t nsdrv_t;

typedef enum _param_type_t param_type_t;
typedef struct _nscmd_t nscmd_t;
typedef struct _nsmod_t nsmod_t; 

struct _nssvc_t {
    const char *name;
    nsdrv_t *drv;
    
    /* binary encoded */
    void (_stdcall *pkt_in)(nssvc_t *, x32_t, void *, size_t);
    void (_stdcall *pkt_out)(nssvc_t *, x32_t, void *, size_t);
    
    /* includes escaping-chars and control-chars */
    void (_stdcall *bin_in)(nssvc_t *, x32_t, void *, size_t); 
    void (_stdcall *bin_out)(nssvc_t *, x32_t, void *, size_t);
    
    /* EOL of command-line is parsed, text components are encoded in utf-8 */
    void (_stdcall *line_in)(nssvc_t *, x32_t, void *, size_t);
    void (_stdcall *line_out)(nssvc_t *, x32_t, void *, size_t);
    
    /* texts are decoded to native charset, the line is converted to object */
    void (_stdcall *cmd_in)(nssvc_t *, x32_t, nscmd_t *, void **, int);
    void (_stdcall *cmd_out)(nssvc_t *, x32_t, nscmd_t *, void **, int);
    
    list_t mods; 
};

struct _nsdrv_t {
    void (_stdcall *pkt_out)(x32_t, void *, size_t);
    void (_stdcall *close)(); 
};

struct _nscodec_t {
    const char *name;
    size_t rest_size; 
    void *rest_data; 
};

#define NSCMDF_HIDDEN 1                 /* invisible in high-level prog-lang */
#define NSCMDF_ASYNC 2                  /* asynchronized command */

struct _nscmd_t {
    const char *name;
    u32_t flags;
    u32_t (_stdcall *cmdmain)(nssvc_t *svc, void **args, int nopts); 
    const param_type_t *args;
    u32_t nargs; 
    const param_type_t *opts;           /* optional parameters */
    u32_t nopts;
    nscmd_t *subcmds;                   /* load into sub symbol table */
    u32_t nsubcmds; 
    const char *help;
    const char *version;
};

enum _param_type_t {
    PARAMTYPE_INT,                      /* int */
    PARAMTYPE_LONG,                     /* long */
    PARAMTYPE_SHORT,                    /* short */
    PARAMTYPE_CHAR,                     /* char */
    PARAMTYPE_FLOAT,                    /* float */
    PARAMTYPE_DOUBLE,                   /* double */
    PARAMTYPE_BOOL,                     /* char (format: 'true', 'false') */
    PARAMTYPE_STRING = 0,               /* const char * */
    PARAMTYPE_BIN,                      /* const void *, size_t */
    PARAMTYPE_ARRAY = 0x1000,           /* (<type> *) */
    PARAMTYPE_VT = 0x2000,              /* (typed_value_t<type> *) */
}; 

struct _nsmod_t {
    const nscmd_t *cmds;
    int ncmds;
    const char *help;
    const char *version;
}; 

#define NSDRV_CONSOLE       0
#define NSDRV_SIO           1
#define NSDRV_MAX           1

#define NSMOD_CORE          (1L << 0)
#define NSMOD_FS            (1L << 1)
#define NSMOD_HACK          (1L << 2)

nssvc_t *nsnew(const char *name, int builtin_drv, u32_t builtin_mods); 
nssvc_t *nsfree(nssvc_t *svc);
void nsinsmod(nssvc_t *svc, nsmod_t *mod);
void nsrmmod(nssvc_t *svc, nsmod_t *mod);
