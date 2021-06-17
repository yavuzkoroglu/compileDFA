/** \file xml.c
 ** \brief Implements all the member functions of Xml
 **/
#include <ctype.h>
#include <stdio.h>
#include "constants.h"
#include "debug.h"
#include "list.h"
#include "stdioplus.h"
#include "unless.h"
#include "until.h"
#include "xml.h"

DECLARE_SOURCE("XML");

/** \brief Converts an ordinary string to an Xml string.
 ** \param xmlstr The Xml string
 ** \param str The ordinary string
 ** \returns A pointer to the Xml string.
 ** \related Xml
 **/
char* private_toXmlString(char* xmlstr, const char* str)
{
	DECLARE_FUNCTION(private_toXmlString);

	/* Variable declarations. */
	unsigned int len;
	const char* ptr;
	char* xmlptr;

	/* Check. */
	ASSERT_NOT_NULL(str);

	unless (xmlstr)
		SAFE_MALLOC(xmlstr, char, BUFFER_SIZE);
	xmlstr[0] = '\0';

	for (ptr = str, xmlptr = xmlstr; (*ptr); ptr++, xmlptr += strlen(xmlptr))
	{
		if (*ptr == XML_NODE_BEGIN_SYMBOL)
			xmlptr = fromPattern(xmlptr, BUFFER_SIZE, "%s", XML_LT);
		else if (*ptr == XML_NODE_END_SYMBOL)
			xmlptr = fromPattern(xmlptr, BUFFER_SIZE, "%s", XML_GT);
		else if (*ptr == XML_QUOTE_SYMBOL)
			xmlptr = fromPattern(xmlptr, BUFFER_SIZE, "%s", XML_QUOTE);
		else if (*ptr == XML_APOSTROPHE_SYMBOL)
			xmlptr = fromPattern(xmlptr, BUFFER_SIZE, "%s", XML_APOSTROPHE);
		else if (*ptr == XML_AMP_SYMBOL)
			xmlptr = fromPattern(xmlptr, BUFFER_SIZE, "%s", XML_AMP);
		else
			xmlptr = fromPattern(xmlptr, BUFFER_SIZE, "%c", *ptr);
		ASSERT_NOT_NULL(xmlptr);
		ASSERT_NOT_EMPTY(xmlptr);
	}

	len = xmlptr - xmlstr;
	ASSERT_FITS_IN_BOUND(len, BUFFER_SIZE);

	return xmlstr;
}

/** \brief Converts an Xml string to an ordinary string.
 ** \param str The ordinary string
 ** \param xmlstr The Xml string
 ** \returns A pointer to the ordinary string.
 ** \related Xml
 **/
char* private_fromXmlString(char* str, const char* xmlstr)
{
	DECLARE_FUNCTION(private_fromXmlString);

	/* Variable declarations. */
	unsigned int len;
	unsigned int xml_lt_len;
	unsigned int xml_gt_len;
	unsigned int xml_quote_len;
	unsigned int xml_apostrophe_len;
	unsigned int xml_amp_len;
	char* ptr;
	const char* xmlptr;

	/* Checks. */
	ASSERT_NOT_NULL(xmlstr);
	ASSERT_NOT_TOO_LONG(xmlstr, BUFFER_SIZE);

	unless (str)
		SAFE_MALLOC(str, char, BUFFER_SIZE);
	str[0] = '\0';

	xml_lt_len = strlen(XML_LT);
	xml_gt_len = strlen(XML_GT);
	xml_quote_len = strlen(XML_QUOTE);
	xml_apostrophe_len = strlen(XML_APOSTROPHE);
	xml_amp_len = strlen(XML_AMP);
	for (xmlptr = xmlstr, ptr = str; (*xmlptr); ptr++)
	{
		if (!strncmp(xmlptr, XML_LT, xml_lt_len)) {
			ptr = fromPattern(ptr, BUFFER_SIZE, "%c", XML_NODE_BEGIN_SYMBOL);
			xmlptr += xml_lt_len;
		} else if (!strncmp(xmlptr, XML_GT, xml_gt_len)) {
			ptr = fromPattern(ptr, BUFFER_SIZE, "%c", XML_NODE_END_SYMBOL);
			xmlptr += xml_gt_len;
		} else if (!strncmp(xmlptr, XML_QUOTE, xml_quote_len)) {
			ptr = fromPattern(ptr, BUFFER_SIZE, "%c", XML_QUOTE_SYMBOL);
			xmlptr += xml_quote_len;
		} else if (!strncmp(xmlptr, XML_APOSTROPHE, xml_apostrophe_len)) {
			ptr = fromPattern(ptr, BUFFER_SIZE, "%c", XML_APOSTROPHE_SYMBOL);
			xmlptr += xml_apostrophe_len;
		} else if (!strncmp(xmlptr, XML_AMP, xml_amp_len)) {
			ptr = fromPattern(ptr, BUFFER_SIZE, "%c", XML_AMP_SYMBOL);
			xmlptr += xml_amp_len;
		} else {
			ptr = fromPattern(ptr, BUFFER_SIZE, "%c", *(xmlptr++));
		}
		ASSERT_NOT_NULL(ptr);
		ASSERT_NOT_EMPTY(ptr);
	}

	len = ptr - str;
	ASSERT_FITS_IN_BOUND(len, XML_MAX_CONTENT_SIZE);

	return str;
}

/** \brief Initializes an XmlAttribute.
 ** \param attribute The XmlAttribute
 ** \param name The attribute name
 ** \param value The attribute value as XmlString
 ** \returns A pointer to the XmlAttribute.
 ** \memberof XmlAttribute
 **/
XmlAttribute* initialize_xattr(XmlAttribute* attribute, const char* name, const char* value)
{
	DECLARE_FUNCTION(initialize_xattr);

	/* Variable declaration. */
	char* check;

	/* Checks. */
	ASSERT_NOT_NULL(name);
	ASSERT_NOT_EMPTY(name);
	ASSERT_NOT_TOO_LONG(name, XML_MAX_ATTRIBUTE_NAME_SIZE);
	ASSERT_NOT_NULL(value);
	ASSERT_NOT_EMPTY(value);
	ASSERT_NOT_TOO_LONG(value, BUFFER_SIZE);

	unless (attribute)
		SAFE_MALLOC(attribute, XmlAttribute, 1);

	check = fromPattern(
		attribute->name,
		XML_MAX_ATTRIBUTE_NAME_SIZE,
		"%s",
		name
	);
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);

	check = private_fromXmlString(attribute->value, value);
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);
	ASSERT_NOT_TOO_LONG(check, XML_MAX_ATTRIBUTE_VAL_SIZE);

	return attribute;
}

/** \brief Returns the string representation of an XmlAttribute.
 ** \param str The string.
 ** \param attribute The XmlAttribute
 ** \returns A pointer to the string.
 ** \memberof XmlAttribute
 **/
char* toString_xattr(char* str, const XmlAttribute* attribute)
{
	DECLARE_FUNCTION(toString_xattr);

	/* Variable declarations. */
	const char* name;
	char buffer[BUFFER_SIZE], *value = buffer;

	/* Check. */
	ASSERT_XMLATTRIBUTE(attribute);

	name = attribute->name;
	value = private_toXmlString(buffer, attribute->value);
	ASSERT_NOT_NULL(value);

	str = fromPattern(str, BUFFER_SIZE, XML_ATTRIBUTE(name,value));
	ASSERT_NOT_NULL(str);
	ASSERT_NOT_EMPTY(str);

	return str;
}

IMPLEMENT_ARRAY_FUNCTIONS_OF(XmlAttribute,XML_MAX_ATTRIBUTES,size,array,xattra,xattr)
IMPLEMENT_LIST_FUNCTIONS_OF(XmlAttribute,XML_MAX_ATTRIBUTES,size,list,array,xattrl,xattr)

/** \brief Initalizes an XmlNode.
 ** \param node The XmlNode
 ** \param parent The parent id
 ** \returns A pointer to the XmlNode.
 ** \memberof XmlNode
 **/
XmlNode* initialize_xmln(XmlNode* node, XmlNode* parent)
{
	DECLARE_FUNCTION(initialize_xmln);

	/* Variable declarations. */
	unsigned int i;
	XmlAttributeArray* check;

	unless (node)
		SAFE_MALLOC(node, XmlNode, 1);

	/* NULL parent means there is no parent. */
	node->parent = parent;
	if (parent) {
		/* Register the child to the parent. */
		parent->children[parent->nChildren++] = node;
		ASSERT_XMLNODE(parent);
	}

	/* Empty tag. */
	node->tag[0] = '\0';

	/* Empty contents. */
	for (i = 0; i < XML_MAX_CHILDREN; i++)
		node->content[i][0] = '\0';

	/* No children. */
	node->nChildren = 0;

	/* Initialize attributes. */
	check = initialize_xattra(node->attributes);
	ASSERT_XMLATTRIBUTEARRAY(check);

	/* Return the node. */
	return node;
}

/** \brief Returns a string representation of a given XmlNode.
 ** \param str The string
 ** \param xml The Xml
 ** \param node The XmlNode
 ** \returns A pointer to the string.
 ** \memberof XmlNode
 **/
char* toString_xmln(char* str, const XmlNode* node)
{
	DECLARE_FUNCTION(toString_xmln);

	/* Variable declarations. */
	unsigned int len, i;
	char* ptr;
	const XmlAttribute* attribute;
	const XmlNode* child;

	/* Checks. */
	ASSERT_XMLNODE(node);

	/* Start the node. */
	ptr = fromPattern(
		str,
		BUFFER_LARGE_SIZE,
		"%c%s",
		XML_NODE_BEGIN_SYMBOL,
		node->tag
	);
	ASSERT_NOT_NULL(ptr);
	ASSERT_NOT_EMPTY(ptr);
	ptr += strlen(ptr);

	/* Write attributes. */
	for (
		attribute = node->attributes->array;
		attribute < node->attributes->array + node->attributes->size;
		attribute++
	) {
		ASSERT_XMLATTRIBUTE(attribute);

		/* Put a space. */
		*(ptr++) = ' ';
		ptr = toString_xattr(ptr, attribute);
		ASSERT_NOT_NULL(ptr);
		ASSERT_NOT_EMPTY(ptr);

		ptr += strlen(ptr);
	}

	ptr = fromPattern(ptr, BUFFER_SIZE, "%c", XML_NODE_END_SYMBOL);
	ASSERT_NOT_NULL(ptr);
	ASSERT_NOT_EMPTY(ptr);
	ptr++;

	/* Write the content. */
	for (i = 0; i < node->nChildren; i++) {
		ptr = private_toXmlString(ptr, node->content[i]);
		ASSERT_NOT_NULL(ptr);
		ptr += strlen(ptr);

		child = node->children[i];
		ASSERT_XMLNODE(child);

		ptr = toString_xmln(ptr, child);
		ASSERT_NOT_NULL(ptr);
		ASSERT_NOT_EMPTY(ptr);

		ptr += strlen(ptr);
	}
	ptr = private_toXmlString(ptr, node->content[i]);
	ASSERT_NOT_NULL(ptr);
	ptr += strlen(ptr);

	/* Finalize the node. */
	ptr = fromPattern(
		ptr,
		BUFFER_SIZE,
		"%c%c%s%c",
		XML_NODE_BEGIN_SYMBOL,
		XML_NODE_STOP_SYMBOL,
		node->tag,
		XML_NODE_END_SYMBOL
	);
	ASSERT_NOT_NULL(ptr);
	ASSERT_NOT_EMPTY(ptr);

	/* Final check. */
	len = ptr - str;
	ASSERT_FITS_IN_BOUND(len, BUFFER_LARGE_SIZE);

	/* Return the string. */
	return str;
}

/** \brief Parses an XmlNode as the root of an abstract syntax tree.
 ** \param str The parsed string
 ** \param node The XmlNode
 ** \returns A pointer to the parsed string.
 ** \memberof XmlNode
 **/
char* toContent_xmln(char* str, const XmlNode* node)
{
	DECLARE_FUNCTION(toContent_xmln);

	/* Variable declaration. */
	unsigned int i;
	char* ptr;

	/* Check. */
	ASSERT_XMLNODE(node);

	ptr = fromPattern(str, BUFFER_SIZE, "%s", node->content[0]);
	ASSERT_NOT_NULL(ptr);
	for (i = 0; i < node->nChildren; i++) {
		ptr += strlen(ptr);
		ptr = toContent_xmln(ptr, node->children[i]);
		ASSERT_NOT_NULL(ptr);
		ptr += strlen(ptr);
		ptr = fromPattern(ptr, BUFFER_SIZE, "%s", node->content[i+1]);
		ASSERT_NOT_NULL(ptr);
	}

	ASSERT_NOT_TOO_LONG(str, DOT_MAX_LABEL_SIZE);
	return str;
}

IMPLEMENT_ARRAY_FUNCTIONS_OF(XmlNode,XML_MAX_NODES,size,nodes,xmlna,xmln)
IMPLEMENT_LIST_FUNCTIONS_OF(XmlNode,XML_MAX_NODES,size,nodes,nodes,xmlnl,xmln)

/** \brief Initializes an Xml object.
 ** \param xml The Xml
 ** \returns A pointer to the Xml.
 ** \memberof Xml
 **/
Xml* initialize_xml(Xml* xml)
{
	DECLARE_FUNCTION(initialize_xml);

	/* Variable declaration. */
	char* check;
	XmlNodeArray* check2;

	unless (xml)
		SAFE_MALLOC(xml, Xml, 1);

	check = fromPattern(xml->meta, XML_META_MAX_SIZE, "%s", XML_DEFAULT_META);
	ASSERT_NOT_NULL(check);
	ASSERT_NOT_EMPTY(check);

	check2 = initialize_xmlna(xml->tree);
	ASSERT_XMLNODEARRAY(check2);

	return xml;
}

/** \brief Creates an Xml from an Xml string.
 ** \param xml The Xml
 ** \param xmlstr The Xml string
 ** \returns A pointer to the Xml.
 ** \memberof Xml
 **/
Xml* fromString_xml(Xml* xml, const char* xmlstr)
{
	DECLARE_FUNCTION(fromString_xml);

	/* Variable declarations. */
	unsigned int i, len;
	char xmlContent[BUFFER_SIZE];
	char xmlValue[BUFFER_SIZE];
	char begin_quote;
	const char* ptr;
	XmlNode* node;
	XmlNode* parent;
	XmlAttribute* attribute;

	/* Checks. */
	ASSERT_NOT_NULL(xmlstr);
	ASSERT_NOT_EMPTY(xmlstr);
	ASSERT_NOT_TOO_LONG(xmlstr, BUFFER_LARGE_SIZE);

	xml = initialize_xml(xml);
	ASSERT_XML(xml);

	/* Skip spaces. */
	for (ptr = xmlstr; (*ptr) && isspace(*ptr); ptr++);
	ASSERT_NOT_EMPTY(ptr);

	/* Must begin with XML_NODE_BEGIN. */
	errorUnless(
		*ptr == XML_NODE_BEGIN_SYMBOL,
		MSG_ERROR_SYNTAX("Expected 'XML_NODE_BEGIN'")
	);

	/* Skip the XML_NODE_BEGIN_SYMBOL. */
	ptr++;
	ASSERT_NOT_EMPTY(ptr);

	/* Skip all the meta nodes. */
	until (*ptr != XML_META_SYMBOL) {
		xml->meta[0] = XML_NODE_BEGIN_SYMBOL;

		/* Skip everything until XML_NODE_END. */
		for (i = 1; (*ptr) && *ptr != XML_NODE_END_SYMBOL; i++, ptr++)
			xml->meta[i] = *ptr;
		ASSERT_NOT_EMPTY(ptr);
		xml->meta[i++] = *ptr;
		ASSERT_NOT_EMPTY(ptr);
		xml->meta[i] = '\0';
		ASSERT_NOT_TOO_LONG(xml->meta, XML_META_MAX_SIZE);

		/* Skip the node end. */
		ptr++;
		ASSERT_NOT_EMPTY(ptr);

		/* Skip spaces. */
    	for (; (*ptr) && isspace(*ptr); ptr++);
		ASSERT_NOT_EMPTY(ptr);

		/* Must begin with XML_NODE_BEGIN. */
		errorUnless(
			*ptr == XML_NODE_BEGIN_SYMBOL,
			MSG_ERROR_SYNTAX("Expected 'XML_NODE_BEGIN'")
		);

		/* Skip the XML_NODE_BEGIN_SYMBOL. */
		ptr++;
		ASSERT_NOT_EMPTY(ptr);
	}

	node = xml->tree->nodes;
	parent = NULL;
	while (node) {
		/* Allocate a node from the Xml tree. */
		node = getNew_xmlna(xml->tree);
		ASSERT_XMLNODEARRAY(xml->tree);

		/* Initialize the node. */
		node = initialize_xmln(node, parent);
		ASSERT_NOT_NULL(node);

		/* Fill the tag information. */
		i = 0;
		while ((*ptr) && !isspace(*ptr) && *ptr != XML_NODE_END_SYMBOL && *ptr != XML_NODE_STOP_SYMBOL)
			node->tag[i++] = *(ptr++);
		node->tag[i] = '\0';
		ASSERT_FITS_IN_BOUND(i, XML_MAX_TAG_SIZE);
		ASSERT_NOT_EMPTY(ptr);

		/* Skip spaces. */
		for (; (*ptr) && isspace(*ptr); ptr++);
		ASSERT_NOT_EMPTY(ptr);

		/* Fill the attributes. */
		until (*ptr == XML_NODE_STOP_SYMBOL || *ptr == XML_NODE_END_SYMBOL) {
			attribute = getNew_xattra(node->attributes);
			ASSERT_XMLATTRIBUTEARRAY(node->attributes);

			/* Fill the attribute name. */
			i = 0;
			while ((*ptr) && *ptr != XML_EQUAL_SYMBOL)
				attribute->name[i++] = *(ptr++);
			attribute->name[i] = '\0';
			ASSERT_FITS_IN_BOUND(i, XML_MAX_ATTRIBUTE_NAME_SIZE);
			ASSERT_NOT_EMPTY(ptr);

			/* Skip the equal sign. */
			ptr++;
			ASSERT_NOT_EMPTY(ptr);

			/* Must begin with a quote. */
			begin_quote = *ptr;
			errorUnless(
				begin_quote == XML_QUOTE_SYMBOL || begin_quote == XML_APOSTROPHE_SYMBOL,
				MSG_ERROR_SYNTAX("Expected 'QUOTE'")
			);

			/* Skip the quote. */
			ptr++;
			ASSERT_NOT_EMPTY(ptr);

			/* Fill the attribute value. */
			i = 0;
			while ((*ptr) && *ptr != begin_quote)
				xmlValue[i++] = *(ptr++);
			xmlValue[i] = '\0';
			ASSERT_NOT_EMPTY(ptr);
			private_fromXmlString(attribute->value, xmlValue);
			ASSERT_XMLATTRIBUTE(attribute);

			/* Skip the quote. */
			ptr++;
			ASSERT_NOT_EMPTY(ptr);

			/* Skip spaces. */
    		for (; (*ptr) && isspace(*ptr); ptr++);
			ASSERT_NOT_EMPTY(ptr);
		}

		if (*ptr == XML_NODE_STOP_SYMBOL) {
			/* Skip the stop symbol. */
			ptr++;
			ASSERT_NOT_EMPTY(ptr);

			/* Go back a step. */
			node = parent;
			unless (node)
				break;
			parent = node->parent;
		}

		ASSERT_NOT_EMPTY(ptr);
		errorUnless(*ptr == XML_NODE_END_SYMBOL, MSG_ERROR_SYNTAX("Expected 'XML_NODE_END'"));

		/* Skip the end symbol. */
		ptr++;
		ASSERT_NOT_EMPTY(ptr);

		while (node) {
			/* Fill the content. */
			i = 0;
			while ((*ptr) && *ptr != XML_NODE_BEGIN_SYMBOL)
				xmlContent[i++] = *(ptr++);
			xmlContent[i] = '\0';
			ASSERT_NOT_EMPTY(ptr);
			/* Append the content string! */
			private_fromXmlString(node->content[node->nChildren], xmlContent);

			/* Skip the node begin symbol. */
			ptr++;
			ASSERT_NOT_EMPTY(ptr);

			unless (*ptr == XML_NODE_STOP_SYMBOL)
				break;

			/* Skip the node stop. */
			ptr++;
			ASSERT_NOT_EMPTY(ptr);

			len = strlen(node->tag);
			errorUnless(!strncmp(node->tag, ptr, len), MSG_ERROR_SYNTAX("Tag Mismatch"));

			/* Skip the end_tag. */
			ptr += len;
			ASSERT_NOT_EMPTY(ptr);

			/* Skip spaces. */
			for (; (*ptr) && isspace(*ptr); ptr++);
			ASSERT_NOT_EMPTY(ptr);

			/* Must encounter an end symbol. */
			errorUnless(
				*ptr == XML_NODE_END_SYMBOL,
				MSG_ERROR_SYNTAX("Expected 'XML_NODE_END'")
			);

			/* Skip the end symbol. */
			ptr++;

			/* No children. */
			/* Go back a step. */
			node = parent;
			unless (node)
				break;
			parent = node->parent;

			ASSERT_NOT_EMPTY(ptr);
		}

		if (node)
			parent = node;
	}

	/* Skip spaces. */
	for (; (*ptr) && isspace(*ptr); ptr++);

	ASSERT_EMPTY(ptr);
	return xml;
}

/** \brief Creates an Xml from a FILE stream.
 ** \param xml The Xml
 ** \param steram The stream
 ** \returns A pointer to the Xml.
 ** \memberof Xml
 **/
Xml* fromStream_xml(Xml* xml, FILE* stream)
{
	DECLARE_FUNCTION(fromStream_xml);

	/* Variable declarations. */
	int check;
	unsigned long len, size;
	char buffer[BUFFER_LARGE_SIZE];

	/* Check. */
	ASSERT_NOT_NULL(stream);

	/* Calculate file length. */
	check = fseek(stream, 0, SEEK_END);
	ASSERT_ZERO(check);

	len = ftell(stream);
	ASSERT_FITS_IN_BOUND(len, BUFFER_LARGE_SIZE);

	/* Rewind everything. */
	check = fseek(stream, 0, SEEK_SET);
	ASSERT_ZERO(check);

	/* Read the file. */
	size = fread(buffer, 1, len, stream);
	errorUnless(size == len, MSG_ERROR_UNKNOWN);
	buffer[len] = '\0';

	return fromString_xml(xml, buffer);
}

/** \brief Creates an Xml from a file.
 ** \param xml The Xml
 ** \param filename The filename
 ** \returns A pointer to the Xml.
 ** \memberof Xml
 **/
Xml* fromFile_xml(Xml* xml, const char* filename)
{
	DECLARE_FUNCTION(fromFile_xml);

	/* Variable declaration. */
	FILE* fp;

	/* Checks. */
	ASSERT_NOT_NULL(filename);
	ASSERT_NOT_EMPTY(filename);
	ASSERT_NOT_TOO_LONG(filename, BUFFER_SIZE);

	SAFE_FOPEN(fp,filename,"r");
	xml = fromStream_xml(xml, fp);
	fclose(fp);

	return xml;
}

/** \brief Writes an Xml to an Xml string.
 ** \param xmlstr The Xml string
 ** \param xml The Xml
 ** \returns A pointer to the Xml string.
 ** \memberof Xml
 **/
char* toString_xml(char* xmlstr, const Xml* xml)
{
	DECLARE_FUNCTION(toString_xml);

	/* Check. */
	ASSERT_XML(xml);

	xmlstr = fromPattern(xmlstr, BUFFER_LARGE_SIZE, "%s", xml->meta);
	ASSERT_NOT_NULL(xmlstr);

	if (xml->tree->size)
		toString_xmln(xmlstr + strlen(xmlstr), xml->tree->nodes);

	return xmlstr;
}
