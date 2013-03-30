#ifndef NODE_PRINT_H
#define NODE_PRINT_H

#define MAX_FLD_N            6
#define NFLD_N(...)          MAX_FLD_N, __VA_ARGS__
#define MAX_REC_LEN          MAXNAME
#define NFLD_VAL(...)        MAX_REC_LEN, __VA_ARGS__
#define NODF(...)            stdout, "%*s:%*s\n"
#define NANE(...)            fprintf(NODF, NFLD_N(str(Name)), NFLD_VAL(__VA_ARGS__->name))
#define PHON(...)            fprintf(NODF, NFLD_N(str(Phon)), NFLD_VAL(__VA_ARGS__->phon))
#define LAST(...)            fprintf(NODF, NFLD_N(str(Last)), NFLD_VAL(__VA_ARGS__->last))

#endif
