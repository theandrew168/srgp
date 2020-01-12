/** MEMORY ALLOCATION MACROS
Handles differences between Macintosh and UNIX.
**/

#ifdef THINK_C
#define MALLOCARGTYPE   size_t
#else
#define MALLOCARGTYPE   unsigned
#endif
#define REALLOCARGTYPE  char *
#define MALLOCFUNC	malloc
#define REALLOCFUNC	realloc
#define FREEFUNC	free

#define ALLOC_RECORDS(PTR,TYPE,NUM) 				      \
   if ((PTR = (TYPE *)						      \
	MALLOCFUNC ((MALLOCARGTYPE) ((NUM) * sizeof(TYPE)))) == NULL) \
      REPORT_ERROR (ERR_MALLOC); else

#define ALLOC(PTR,TYPE,NUM) 				     	\
   (PTR = (TYPE *) MALLOCFUNC ((MALLOCARGTYPE) ((NUM) * sizeof(TYPE))))

#define REALLOC(NEWPTR, OLDPTR, TYPE, NUM)    			\
   (NEWPTR = (TYPE *) REALLOCFUNC ((REALLOCARGTYPE) OLDPTR,	\
				   (MALLOCARGTYPE) ((NUM) * sizeof(TYPE))))

#define FREE(PTR)		(FREEFUNC ((REALLOCARGTYPE) (PTR)))


/** TRANSLATING BSD TO SYSTEM V **/

/*#if defined(THINK_C) || defined(__MSDOS__)*/
#define bzero(PTR,NUMBYTES)       memset(PTR,0,(size_t)NUMBYTES)
#define bcopy(SRC,DEST,NUMBYTES)  memcpy(DEST,SRC,(size_t)NUMBYTES)
#define bcmp(B1,B2,NUMBYTES)      memcmp(B1,B2,(size_t)NUMBYTES)
#define irint                     /* nothing: very risky! */
/*#endif*/
