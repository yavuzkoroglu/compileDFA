/** \file compileDFA.c
 **/
#include "constants.h"
#include "debug.h"
#include "dfa.h"
#include "dot.h"
#include "hashtable.h"
#include "logging.h"
#include "stdioplus.h"
#include "stringplus.h"
#include "xml.h"

DECLARE_SOURCE("compileDFA");

int main(int argc, char* argv[])
{
	DECLARE_FUNCTION(main);

	char buffer[BUFFER_LARGE_SIZE], *str = buffer;
	Graph gBuffer, *G = &gBuffer;
	DeterministicFiniteAutomaton dBuffer, *dfa = &dBuffer;
	FILE* fp;

	start_logging();

	say(MSG_REPORT_VAR("sizeof(DeterministicFiniteAutomaton)", "%luK", sizeof(DeterministicFiniteAutomaton)/1024));
	say(MSG_REPORT_VAR("sizeof(Graph)", "%luK", sizeof(Graph)/1024));
	say(MSG_REPORT_VAR("sizeof(HashTable)", "%luM", sizeof(HashTable)/1024/1024));
	say(MSG_REPORT_VAR("sizeof(Xml)", "%luM", sizeof(Xml)/1024/1024));

	if (argc < 3) {
		say(MSG_REPORT("Usage: compileDFA.out <input>.xml <output>.[dot|c]"));
		exit(1);
	}

	dfa = fromFile_dfa(dfa, argv[1]);
	ASSERT_DFA(dfa);

	if (argv[2][strlen(argv[2])-1] == 'c') {
		str = toC_dfa(buffer, dfa);
		ASSERT_NOT_NULL(str);
		ASSERT_NOT_EMPTY(str);
		SAFE_FOPEN(fp, argv[2], "w");
		fprintf(fp, "%s", str);
		fclose(fp);
	} else {
		G = toDot_dfa(G, dfa);
		ASSERT_GRAPH(G);
		toFile_dot(G, argv[2]);
	}

	stop_logging();

	return 0;
}
