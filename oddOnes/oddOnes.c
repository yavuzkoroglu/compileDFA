int oddOnes(const char* str)
{
	char c;
	if (!str)
		return 0;
	goto sEven;
sOdd: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == '1') {
		goto sEven;
	} else {
		return 0;
	}
sEven: c = *str++;
	if (c == '\0') {
		return 0;
	} else if (c == '1') {
		goto sOdd;
	} else {
		return 0;
	}
}