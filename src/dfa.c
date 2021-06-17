/** \file dfa.c
 ** \brief Implements the member functions of DeterministicFiniteAutomaton
 **/
#include "constants.h"
#include "debug.h"
#include "dfa.h"
#include "hashtable.h"
#include "stringplus.h"
#include "xml.h"

DECLARE_SOURCE("DFA");

char* toString_dfas(char* str, const DFAState* state)
{
	DECLARE_FUNCTION(toString_dfas);

	ASSERT_DFASTATE(state);

	str = fromPattern(str, BUFFER_SIZE, "%s", state->name);
	ASSERT_NOT_NULL(str);
	ASSERT_NOT_EMPTY(str);
	ASSERT_NOT_TOO_LONG(str, DFA_MAX_NAME_SIZE);

	return str;
}

IMPLEMENT_ARRAY_FUNCTIONS_OF(DFAState,DFA_MAX_STATES,nStates,array,dfasa,dfas)
IMPLEMENT_LIST_FUNCTIONS_OF(DFAState,DFA_MAX_STATES,nStates,list,array,dfasl,dfas)

DeterministicFiniteAutomaton* initialize_dfa(DeterministicFiniteAutomaton* dfa)
{
	DECLARE_FUNCTION(initialize_dfa);

	char* check;

	unless (dfa)
		SAFE_MALLOC(dfa, DeterministicFiniteAutomaton, 1);

	check = fromPattern(dfa->name, DFA_MAX_NAME_SIZE, DFA_DEFAULT_NAME);
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);
	check = fromPattern(dfa->alphabet, DFA_MAX_SYMBOLS, DFA_DEFAULT_ALPHABET);
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);

	initialize_dfasa(dfa->states);
	ASSERT_DFASTATEARRAY(dfa->states);

	dfa->initialStateId = DFA_DEFAULT_INITIAL_STATE_ID;

	ASSERT_DFA(dfa);
	return dfa;
}

DFAState* insertState_dfa(DeterministicFiniteAutomaton* dfa)
{
	DECLARE_FUNCTION(insertState_dfa);

	char* check;
	DFAState* s;

	ASSERT_DFA(dfa);

	s = getNew_dfasa(dfa->states);
	ASSERT_NOT_NULL(s);
	ASSERT_DFA(dfa);
	s->id = dfa->states->nStates - 1;

	s->isAccept = DFA_DEFAULT_ACCEPT;

	check = fromPattern(s->name, DFA_MAX_NAME_SIZE, DFA_DEFAULT_STATE_NAME(s->id));
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);

	ASSERT_DFASTATE(s);
	return s;
}

int insertTransition_dfa(DeterministicFiniteAutomaton* dfa, const DFAStateId sourceId, const DFAStateId sinkId, const char with)
{
	DECLARE_FUNCTION(insertTransition_dfa);

	DFAState* from;
	DFAState* to;

	ASSERT_DFA(dfa);
	ASSERT_FITS_IN_BOUND(sourceId, dfa->states->nStates);
	ASSERT_FITS_IN_BOUND(sinkId, dfa->states->nStates);
	ASSERT_NOT_ZERO(with);

	from = dfa->states->array + sourceId;
	to = dfa->states->array + sinkId;
	ASSERT_DFASTATE(from);
	ASSERT_DFASTATE(to);

	if (strchr(dfa->alphabet, with)) {
		dfa->transitions[sourceId][(int)with] = sinkId;
		return 1;
	} else {
		return 0;
	}
}

DeterministicFiniteAutomaton* fromXml_dfa(DeterministicFiniteAutomaton* dfa, const Xml* xml)
{
	DECLARE_FUNCTION(fromXml_dfa);

	unsigned int i, j;
	int isAlphabetPredefined, result, isAccept, isReject;
	const char* with;
	char* check;
	char* alphabetEnd;
	DFAState* s;
	DFAStateId sourceId, sinkId;
	const Object* obj;
	const XmlNode* root;
	const XmlNode* node;
	const XmlNode* from;
	const XmlNode* to;
	const XmlNode* states;
	const XmlNode* state;
	const XmlNode* initialState;
	const XmlNode* transitions;
	const XmlAttribute* attribute;
	HashTable* ht;

	ASSERT_XML(xml);

	dfa = initialize_dfa(dfa);
	ASSERT_DFA(dfa);

	ht = initialize_ht(NULL);
	ASSERT_HASHTABLE(ht);

	/* Clear the alphabet. */
	dfa->alphabet[0] = '\0';
	alphabetEnd = dfa->alphabet;

	root = xml->tree->nodes;
	ASSERT_EQUAL_STR(root->tag, "dfa");

	isAlphabetPredefined = 0;
	for (attribute = root->attributes->array; attribute < root->attributes->array + root->attributes->size; attribute++)
	{
		ASSERT_XMLATTRIBUTE(attribute);
		say(MSG_REPORT_VAR(attribute->name, "%s", attribute->value));
		if (!strcmp(attribute->name, "name")) {
			check = fromPattern(dfa->name, DFA_MAX_NAME_SIZE, "%s", attribute->value);
			ASSERT_NOT_NULL(check);
			ASSERT_NOT_EMPTY(check);
		} else if (!strcmp(attribute->name, "alphabet")) {
			isAlphabetPredefined = 1;
			check = fromPattern(dfa->alphabet, DFA_MAX_SYMBOLS, "%s", attribute->value);
			ASSERT_NOT_NULL(check);
			ASSERT_NOT_EMPTY(check);
			alphabetEnd += strlen(dfa->alphabet);
		}
	}

	errorUnless(root->nChildren == 3, MSG_ERROR_SYNTAX("DFA must have exactly 3 children, <states>, <initialState>, <transitions>"));

	states = NULL;
	initialState = NULL;
	transitions = NULL;
	for (i = 0; i < root->nChildren; i++)
	{
		node = root->children[i];
		ASSERT_XMLNODE(node);
		if (!strcmp(node->tag, "states"))
			states = node;
		else if (!strcmp(node->tag, "initialState"))
			initialState = node;
		else if (!strcmp(node->tag, "transitions"))
			transitions = node;
		else
			warning(MSG_REPORT_VAR("Unrecognized DFA Child", "%s", node->tag));
	}

	ASSERT_XMLNODE(states);
	ASSERT_FITS_IN_BOUND(states->nChildren, 3);
	for (i = 0; i < states->nChildren; i++)
	{
		node = states->children[i];
		ASSERT_XMLNODE(node);
		isAccept = !strcmp(node->tag, "accept");
		isReject = !strcmp(node->tag, "reject");

		unless (isAccept || isReject) {
			warning(MSG_REPORT_VAR("Skipping unrecognized State Type (accept/reject)", "%s", node->tag));
			continue;
		}

		for (j = 0; j < node->nChildren; j++) {
			state = node->children[j];
			ASSERT_XMLNODE(state);
			s = insertState_dfa(dfa);
			ASSERT_DFASTATE(s);
			s->isAccept = isAccept;
			check = fromPattern(s->name, DFA_MAX_NAME_SIZE, "%s", state->tag);
			ASSERT_NOT_NULL(check);
			ASSERT_NOT_EMPTY(check);
			if (isAccept)
				say(MSG_REPORT_VAR("Accept State", "%s", s->name));
			else
				say(MSG_REPORT_VAR("Reject State", "%s", s->name));

			/* Map the state name to the state index. */
			insert_ht(ht, s->name, fromUInt_obj(s->id));
			ASSERT_HASHTABLE(ht);
		}
	}

	ASSERT_XMLNODE(initialState);
	errorUnless(initialState->nChildren == 1, MSG_ERROR_SYNTAX("There has to be EXACTLY one initial state!"));
	node = initialState->children[0];
	ASSERT_XMLNODE(node);
	obj = get_ht(ht, node->tag);
	ASSERT_NOT_NULL(obj);
	dfa->initialStateId = obj->asUInt;
	ASSERT_FITS_IN_BOUND(dfa->initialStateId, dfa->states->nStates);

	ASSERT_XMLNODE(transitions);
	say(MSG_REPORT("Processing transitions..."));
	for (i = 0; i < transitions->nChildren; i++)
	{
		from = transitions->children[i];
		ASSERT_XMLNODE(from);
		obj = get_ht(ht, from->tag);
		ASSERT_NOT_NULL(obj);
		sourceId = obj->asUInt;
		ASSERT_FITS_IN_BOUND(sourceId, dfa->states->nStates);

		for (j = 0; j < from->nChildren; j++)
		{
			to = from->children[j];
			ASSERT_XMLNODE(to);
			obj = get_ht(ht, to->tag);
			ASSERT_NOT_NULL(obj);
			sinkId = obj->asUInt;
			ASSERT_FITS_IN_BOUND(sinkId, dfa->states->nStates);

			for (with = to->content[0]; (*with); with++) {
				unless (strchr(dfa->alphabet, *with)) {
					/* The alphabet must NOT be predefined. */
					errorIf(isAlphabetPredefined, MSG_ERROR_SYNTAX("Encountered symbol outside the alphabet!"));

					/* Append the new symbol to the alphabet. */
					alphabetEnd = fromPattern(alphabetEnd, 2, "%c", *with);
					ASSERT_NOT_NULL(alphabetEnd);
					ASSERT_NOT_EMPTY(alphabetEnd);
					alphabetEnd++;
				}
				result = insertTransition_dfa(dfa, sourceId, sinkId, *with);
				ASSERT_NOT_ZERO(result);
			}
		}
	}

	/* Free the Hashtable. */
	free(ht);

	return dfa;
}

DeterministicFiniteAutomaton* fromFile_dfa(DeterministicFiniteAutomaton* dfa, const char* filename)
{
	DECLARE_FUNCTION(fromFile_dfa);

	Xml* xml;

	ASSERT_NOT_NULL(filename);
	ASSERT_NOT_EMPTY(filename);
	ASSERT_NOT_TOO_LONG(filename, BUFFER_SIZE);

	xml = fromFile_xml(NULL, filename);
	ASSERT_XML(xml);

	dfa = fromXml_dfa(dfa, xml);
	ASSERT_DFA(dfa);

	free(xml);

	return dfa;
}

Graph* toDot_dfa(Graph* G, const DeterministicFiniteAutomaton* dfa)
{
	DECLARE_FUNCTION(toDot_dfa);

	unsigned int i, j;
	char* check;
	const char* start;
	const char* end;
	const char* with;
	const DFAState* state;
	Node* node;
	Edge* edge;

	ASSERT_DFA(dfa);

	G = initialize_dot(G);
	ASSERT_GRAPH(G);

	/* DFA name. */
	check = fromPattern(G->name, DOT_MAX_NAME_SIZE, "%s", dfa->name);
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);

	/* Insert nodes. */
	for (state = dfa->states->array; state < dfa->states->array + dfa->states->nStates; state++)
	{
		say(MSG_REPORT_VAR("Inserting DOT Node", "%s", state->name));
		ASSERT_DFASTATE(state);
		node = insertNode_dot(G, -1);
		ASSERT_NODE(node);
		ASSERT_GRAPH(G);
		check = fromPattern(node->name, DOT_MAX_NAME_SIZE, "%s", state->name);
		ASSERT_NOT_NULL(check);
		ASSERT_NOT_EMPTY(check);
		check = fromPattern(node->label, 1, "");
		ASSERT_NOT_NULL(check);
		ASSERT_EMPTY(check);
		check = fromPattern(node->shape, DOT_MAX_STYLE_SIZE, "circle");
		ASSERT_NOT_NULL(check);
		ASSERT_NOT_EMPTY(check);
		if (state->isAccept)
			node->peripheries = 2;
	}

	/* Mark the initial state. */
	say(MSG_REPORT("Marking the initial state..."));
	node = insertNode_dot(G, -1);
	ASSERT_NODE(node);
	ASSERT_GRAPH(G);
	check = fromPattern(node->name, DOT_MAX_NAME_SIZE, "reset");
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);
	check = fromPattern(node->label, 1, "");
	ASSERT_NOT_NULL(check);
	ASSERT_EMPTY(check);
	check = fromPattern(node->style, DOT_MAX_STYLE_SIZE, "invis");
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);
	check = fromPattern(node->shape, DOT_MAX_STYLE_SIZE, "point");
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);
	edge = insertEdge_dot(G, G->size-1, dfa->initialStateId);

	/* Insert transitions. */
	say(MSG_REPORT("Inserting transitions..."));
	start = dfa->alphabet;
	end = dfa->alphabet + strlen(dfa->alphabet);
	for (i = 0; i < dfa->states->nStates; i++)
	{
		for (with = start; with < end; with++)
		{
			j = dfa->transitions[i][(int)*with];
			edge = getEdge_dot(G, i, j);
			if (edge) {
				ASSERT_EDGE(edge);
				check = fromPattern(edge->label+strlen(edge->label), 3, ",%c", *with);
				ASSERT_NOT_NULL(check);
				ASSERT_NOT_EMPTY(check);
			} else {
				edge = insertEdge_dot(G, i, j);
				ASSERT_EDGE(edge);
				check = fromPattern(edge->label, 2, "%c", *with);
				ASSERT_NOT_NULL(check);
				ASSERT_NOT_EMPTY(check);
			}
			ASSERT_EDGE(edge);
		}
	}

	return G;
}

char* toC_dfa(char* str, const DeterministicFiniteAutomaton* dfa)
{
	DECLARE_FUNCTION(toC_dfa);

	DFAStateId sourceId, sinkId;
	char* ptr;
	const char* start;
	const char* end;
	const char* with;
	const DFAState* from;
	const DFAState* to;

	ASSERT_DFA(dfa);

	start = dfa->alphabet;
	end = dfa->alphabet + strlen(dfa->alphabet);

	say(MSG_REPORT_VAR("Function", "%s", dfa->name));
	ptr = fromPattern(str, BUFFER_LARGE_SIZE, "int %s(const char* str)\n{\n\tchar c;\n\tif (!str)\n\t\treturn 0;\n", dfa->name);
	ASSERT_NOT_NULL(ptr);
	ASSERT_NOT_EMPTY(ptr);
	ptr += strlen(ptr);

	/* Go to the initial state. */
	to = dfa->states->array + dfa->initialStateId;
	ASSERT_DFASTATE(to);
	ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, "\tgoto %s;\n", to->name);
	ASSERT_NOT_NULL(ptr);
	ASSERT_NOT_EMPTY(ptr);
	ptr += strlen(ptr);

	/* Insert every state. */
	for (from = dfa->states->array; from < dfa->states->array + dfa->states->nStates; from++)
	{
		ASSERT_DFASTATE(from);
		sourceId = from->id;
		ASSERT_FITS_IN_BOUND(sourceId, dfa->states->nStates);

		/* Mark the beginning of the state. */
		say(MSG_REPORT_VAR("Implementing", "%s", from->name));
		ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, "%s: c = *str++;\n", from->name);
		ASSERT_NOT_NULL(ptr);
		ASSERT_NOT_EMPTY(ptr);
		ptr += strlen(ptr);

		/* Insert accept/reject. */
		ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, "\tif (c == '\\0') {\n");
		ASSERT_NOT_NULL(ptr);
		ASSERT_NOT_EMPTY(ptr);
		ptr += strlen(ptr);

		ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, "\t\treturn %d;\n\t}", from->isAccept);
		ASSERT_NOT_NULL(ptr);
		ASSERT_NOT_EMPTY(ptr);
		ptr += strlen(ptr);

		/* Insert every transition. */
		for (with = start; with < end; with++)
		{
			ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, " else if (c == '%c') {\n", *with);
			ASSERT_NOT_NULL(ptr);
			ASSERT_NOT_EMPTY(ptr);
			ptr += strlen(ptr);

			sinkId = dfa->transitions[sourceId][(int)*with];
			ASSERT_FITS_IN_BOUND(sinkId, DFA_MAX_STATES);

			to = dfa->states->array + sinkId;
			ASSERT_DFASTATE(to);

			ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, "\t\tgoto %s;\n\t}", to->name);
			ASSERT_NOT_NULL(ptr);
			ASSERT_NOT_EMPTY(ptr);
			ptr += strlen(ptr);
		}

		ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, " else {\n\t\treturn 0;\n\t}\n");
		ASSERT_NOT_NULL(ptr);
		ASSERT_NOT_EMPTY(ptr);
		ptr += strlen(ptr);
	}

	/* Finalize the function. */
	ptr = fromPattern(ptr, BUFFER_LARGE_SIZE, "}");
	ASSERT_NOT_NULL(ptr);
	ASSERT_NOT_EMPTY(ptr);
	ptr += strlen(ptr);

	ASSERT_NOT_NULL(str);
	ASSERT_NOT_EMPTY(str);
	ASSERT_NOT_TOO_LONG(str, BUFFER_LARGE_SIZE);

	return str;
}
