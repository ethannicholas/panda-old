// This file was automatically generated by the Panda compiler
#ifndef panda$parser$GLRParser_H
#define panda$parser$GLRParser_H
extern panda$core$Class panda$parser$GLRParser_class;
#ifndef CLASS_panda$parser$GLRParser
#define CLASS_panda$parser$GLRParser
struct panda$parser$GLRParser {
    panda$core$Class* cl;
    panda$collections$ImmutableArray$LTpanda$core$Int64$GT* productionIds;
    panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT* actions;
    panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT* gotos;
    panda$parser$GLRParser$Reducer* reducer;
    panda$collections$ImmutableArray$LTpanda$core$String$Z$GT* errors;
};

#define panda$parser$GLRParser$errorText_panda$parser$GLRParser$State_$Rpanda$core$String_INDEX 4
typedef panda$core$String*(panda$parser$GLRParser$errorText_panda$parser$GLRParser$State_$Rpanda$core$String_TYPE)(panda$parser$GLRParser* self, panda$parser$GLRParser$State*);
#define panda$parser$GLRParser$parse_panda$core$String_Int64_panda$core$Object$Z_$R$LPpanda$core$Object$Z$Cpanda$collections$ListView$LTpanda$parser$GLRParser$ParseError$GT$RP_INDEX 5
typedef $LPpanda$core$Object$Z$Cpanda$collections$ListView$LTpanda$parser$GLRParser$ParseError$GT$RP*(panda$parser$GLRParser$parse_panda$core$String_Int64_panda$core$Object$Z_$R$LPpanda$core$Object$Z$Cpanda$collections$ListView$LTpanda$parser$GLRParser$ParseError$GT$RP_TYPE)(panda$parser$GLRParser* self, panda$core$String*, Int64, panda$core$Object*);
#define panda$parser$GLRParser$action_panda$parser$GLRParser$Action_panda$core$String_panda$parser$GLRParser$State_panda$collections$Stack$LTpanda$parser$GLRParser$State$GT_INDEX 6
typedef void(panda$parser$GLRParser$action_panda$parser$GLRParser$Action_panda$core$String_panda$parser$GLRParser$State_panda$collections$Stack$LTpanda$parser$GLRParser$State$GT_TYPE)(panda$parser$GLRParser* self, panda$parser$GLRParser$Action*, panda$core$String*, panda$parser$GLRParser$State*, panda$collections$Stack*);
#define panda$parser$GLRParser$partialParse_panda$core$String_Int64_$Rpanda$core$Int64_INDEX 7
typedef Int64(panda$parser$GLRParser$partialParse_panda$core$String_Int64_$Rpanda$core$Int64_TYPE)(panda$parser$GLRParser* self, panda$core$String*, Int64);
void panda$parser$GLRParser$init_panda$collections$ImmutableArray$LTpanda$core$Int64$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT_panda$parser$GLRParser$Reducer(panda$parser$GLRParser* self, panda$collections$ImmutableArray$LTpanda$core$Int64$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT*, panda$parser$GLRParser$Reducer*);
panda$parser$GLRParser* new_panda$parser$GLRParser$init_panda$collections$ImmutableArray$LTpanda$core$Int64$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT_panda$parser$GLRParser$Reducer(panda$collections$ImmutableArray$LTpanda$core$Int64$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT*, panda$parser$GLRParser$Reducer*);
void panda$parser$GLRParser$init_panda$collections$ImmutableArray$LTpanda$core$Int64$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT_panda$collections$ImmutableArray$LTpanda$core$String$Z$GT_panda$parser$GLRParser$Reducer(panda$parser$GLRParser* self, panda$collections$ImmutableArray$LTpanda$core$Int64$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT*, panda$collections$ImmutableArray$LTpanda$core$String$Z$GT*, panda$parser$GLRParser$Reducer*);
panda$parser$GLRParser* new_panda$parser$GLRParser$init_panda$collections$ImmutableArray$LTpanda$core$Int64$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT_panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT_panda$collections$ImmutableArray$LTpanda$core$String$Z$GT_panda$parser$GLRParser$Reducer(panda$collections$ImmutableArray$LTpanda$core$Int64$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$parser$GLRParser$Action$Z$GT$GT*, panda$collections$ImmutableArray$LTpanda$collections$ImmutableArray$LTpanda$core$Int64Wrapper$Z$GT$GT*, panda$collections$ImmutableArray$LTpanda$core$String$Z$GT*, panda$parser$GLRParser$Reducer*);
void panda$parser$GLRParser$$classInit_class();
extern Char class_panda$parser$GLRParser$EOF;
extern panda$parser$GLRParser$ParseError* class_panda$parser$GLRParser$DIE;
extern Bit class_panda$parser$GLRParser$$classInited;
#endif
#endif