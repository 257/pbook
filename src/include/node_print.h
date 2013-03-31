#ifndef NODE_PRINT_H
#define NODE_PRINT_H

#include "debug.h"
#include "pb_limits.h"

#define MAX_FLD_N        6
#define MAX_REC_LEN      MAXNAME
#define MAX_PHON_LEN     15
#define NFLD_N(...)      MAX_FLD_N   , __VA_ARGS__
#define NFLD_VAL(...)    MAX_REC_LEN , __VA_ARGS__
#define NFLD_VALd(...)   MAX_PHON_LEN, __VA_ARGS__
#define PFs              stdout, "%*s:%*s\n"
#define PFlld            stdout, "%*s:%*lld\n"
#define PPHON(...)       fprintf(PFlld, NFLD_N(str(Phon)), NFLD_VALd(__VA_ARGS__->phon))
#define PNANE(...)       fprintf(PFs  , NFLD_N(str(Name)), NFLD_VAL(__VA_ARGS__->name))
#define PLAST(...)       fprintf(PFs  , NFLD_N(str(Last)), NFLD_VAL(__VA_ARGS__->last))

#define dPFs              stderr, "%*s:%*s\n"
#define dPFlld            stderr, "%*s:%*lld\n"
#define dPPHON(...)       (DEBUGh, fprintf(dPFlld, NFLD_N(str(Phon)), NFLD_VALd(__VA_ARGS__->phon)))
#define dPNANE(...)       (DEBUGh, fprintf(dPFs  , NFLD_N(str(Name)), NFLD_VAL(__VA_ARGS__->name)))
#define dPLAST(...)       (DEBUGh, fprintf(dPFs  , NFLD_N(str(Last)), NFLD_VAL(__VA_ARGS__->last)))

#endif
