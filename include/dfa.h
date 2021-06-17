/** \file dfa.h
 ** \brief Defines DeterministicFiniteAutomaton and declares its member functions.
 **/
#ifndef DFA_H
	#define DFA_H
	#include "constants.h"
	#include "dot.h"
	#include "list.h"
	#include "xml.h"

	typedef unsigned int DFAStateId;

	#ifndef DFA_MAX_NAME_SIZE
		#define DFA_MAX_NAME_SIZE 30
	#endif
	#ifndef DFA_MAX_STATES
		#define DFA_MAX_STATES 100
	#endif
	#ifndef DFA_MAX_SYMBOLS
		#define DFA_MAX_SYMBOLS 256
	#endif
	#ifndef DFA_DEFAULT_NAME
		#define DFA_DEFAULT_NAME "DFA"
	#endif
	#ifndef DFA_DEFAULT_ACCEPT
		#define DFA_DEFAULT_ACCEPT 0
	#endif
	#ifndef DFA_DEFAULT_ALPHABET
		#define DFA_DEFAULT_ALPHABET "ABC"
	#endif
	#ifndef DFA_DEFAULT_INITIAL_STATE_ID
		#define DFA_DEFAULT_INITIAL_STATE_ID 0
	#endif
	#ifndef DFA_DEFAULT_STATE_NAME
		#define DFA_DEFAULT_STATE_NAME(id) "s%u",id
	#endif

	typedef struct DFAStateBody {
		DFAStateId id;
		char name[DFA_MAX_NAME_SIZE];
		int isAccept;
	} DFAState;
	#define ASSERT_DFASTATE(state)								\
		ASSERT_NOT_NULL(state);									\
		ASSERT_NOT_EMPTY(state->name);							\
		ASSERT_NOT_TOO_LONG(state->name, DFA_MAX_NAME_SIZE);	\
		ASSERT_FITS_IN_BOUND(state->id, DFA_MAX_STATES)

	char* toString_dfas(char*, const DFAState*);

	DECLARE_ARRAY_OF(DFAState,DFA_MAX_STATES,nStates,array,dfasa);
	DECLARE_LIST_OF(DFAState,DFA_MAX_STATES,nStates,list,dfasl);
	#define ASSERT_DFASTATEARRAY(array) ASSERT_ARRAY(array,nStates,DFA_MAX_STATES)
	#define ASSERT_DFASTATELIST(list) ASSERT_LIST(list,nStates,DFA_MAX_STATES)

	typedef struct DeterministicFiniteAutomatonBody {
		char name[DFA_MAX_NAME_SIZE];
		char alphabet[DFA_MAX_SYMBOLS];
		DFAStateArray states[1];
		DFAStateId initialStateId;
		DFAStateId transitions[DFA_MAX_STATES][DFA_MAX_SYMBOLS];
	} DeterministicFiniteAutomaton;
	#define ASSERT_DFA(dfa)												\
		ASSERT_NOT_NULL(dfa);											\
		ASSERT_NOT_EMPTY(dfa->name);									\
		ASSERT_NOT_TOO_LONG(dfa->name, DFA_MAX_NAME_SIZE);				\
		ASSERT_NOT_EMPTY(dfa->alphabet);								\
		ASSERT_NOT_TOO_LONG(dfa->alphabet, DFA_MAX_SYMBOLS);			\
		ASSERT_DFASTATEARRAY(dfa->states);								\
		ASSERT_FITS_IN_BOUND(dfa->initialStateId, DFA_MAX_STATES)

	DeterministicFiniteAutomaton* initialize_dfa(DeterministicFiniteAutomaton*);
	DFAState* insertState_dfa(DeterministicFiniteAutomaton*);
	int insertTransition_dfa(DeterministicFiniteAutomaton*, const DFAStateId, const DFAStateId, const char);
	DeterministicFiniteAutomaton* fromXml_dfa(DeterministicFiniteAutomaton*, const Xml*);
	DeterministicFiniteAutomaton* fromFile_dfa(DeterministicFiniteAutomaton*, const char*);
	Graph* toDot_dfa(Graph*, const DeterministicFiniteAutomaton*);
	char* toC_dfa(char*, const DeterministicFiniteAutomaton*);
#endif
