int isRomanNumeral(const char* str)
{
	char c;
	if (!str)
		return 0;
	goto sInit;
sFirstM: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sFirstC;
	} else if (c == 'D') {
		goto sD;
	} else if (c == 'M') {
		goto sSecondM;
	} else {
		return 0;
	}
sSecondM: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sFirstC;
	} else if (c == 'D') {
		goto sD;
	} else if (c == 'M') {
		goto sThirdM;
	} else {
		return 0;
	}
sThirdM: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sFirstC;
	} else if (c == 'D') {
		goto sD;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sD: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sPostFirstC;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sFirstC: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sSecondC;
	} else if (c == 'D') {
		goto sPostDMThirdC;
	} else if (c == 'M') {
		goto sPostDMThirdC;
	} else {
		return 0;
	}
sSecondC: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sPostDMThirdC;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sPostDMThirdC: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sPostFirstC: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sSecondC;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sPostFirstX: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sSecondX;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sL: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sPostFirstX;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sFirstX: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sSecondX;
	} else if (c == 'L') {
		goto sPostLCThirdX;
	} else if (c == 'C') {
		goto sPostLCThirdX;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sSecondX: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sPostLCThirdX;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sPostLCThirdX: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sReject;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sV: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sPostFirstI;
	} else if (c == 'V') {
		goto sReject;
	} else if (c == 'X') {
		goto sReject;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sPostFirstI: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sSecondI;
	} else if (c == 'V') {
		goto sReject;
	} else if (c == 'X') {
		goto sReject;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sFirstI: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sSecondI;
	} else if (c == 'V') {
		goto sNoMoreSymbols;
	} else if (c == 'X') {
		goto sNoMoreSymbols;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sSecondI: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sNoMoreSymbols;
	} else if (c == 'V') {
		goto sReject;
	} else if (c == 'X') {
		goto sReject;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sNoMoreSymbols: c = *str++;
	if (c == '\0') {
		return 1;
	} else if (c == 'I') {
		goto sReject;
	} else if (c == 'V') {
		goto sReject;
	} else if (c == 'X') {
		goto sReject;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
sInit: c = *str++;
	if (c == '\0') {
		return 0;
	} else if (c == 'I') {
		goto sFirstI;
	} else if (c == 'V') {
		goto sV;
	} else if (c == 'X') {
		goto sFirstX;
	} else if (c == 'L') {
		goto sL;
	} else if (c == 'C') {
		goto sFirstC;
	} else if (c == 'D') {
		goto sD;
	} else if (c == 'M') {
		goto sFirstM;
	} else {
		return 0;
	}
sReject: c = *str++;
	if (c == '\0') {
		return 0;
	} else if (c == 'I') {
		goto sReject;
	} else if (c == 'V') {
		goto sReject;
	} else if (c == 'X') {
		goto sReject;
	} else if (c == 'L') {
		goto sReject;
	} else if (c == 'C') {
		goto sReject;
	} else if (c == 'D') {
		goto sReject;
	} else if (c == 'M') {
		goto sReject;
	} else {
		return 0;
	}
}