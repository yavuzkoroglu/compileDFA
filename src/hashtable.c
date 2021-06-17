/** \file hashtable.c
 ** \brief Implements all functions related to HashTable.
 ** \related HashTable
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "hash.h"
#include "hashtable.h"
#include "logging.h"
#include "mapping.h"
#include "object.h"
#include "stdlibplus.h"
#include "stringplus.h"
#include "constants.h"
#include "unless.h"

DECLARE_SOURCE("HASHTABLE");

/** \brief Initializes or creates an empty HashTable.
 ** \returns A pointer to the HashTable.
 ** \memberof HashTable
 **/
HashTable* initialize_ht(HashTable* ht)
{
	DECLARE_FUNCTION(initialize_ht);

	/* Variable declaration */
	unsigned int* ptr;

	unless (ht)
		SAFE_MALLOC(ht, HashTable, 1);

	/* Initialize all counts to zero. */
	ht->nKeys = 0;
	for (ptr = ht->nSameHashes; ptr < ht->nSameHashes + HT_ROW_COUNT; ptr++)
		*ptr = 0;

	return ht;
}

/** \brief Inserts a key-value pair into the given HashTable
 ** \param ht A pointer to the HashTable
 ** \param key The key as a constant string
 ** \param value The value as an Object
 ** \memberof HashTable
 **
 ** HashTable duplicates the original key-value, so if the originals
 ** are allocated using malloc(), they can be freed after the insertion.
 **/
void insert_ht(HashTable* ht, const char* key, const Object value)
{
	DECLARE_FUNCTION(insert_ht);

	/* Variable declarations. */
	unsigned int hashValue;
	Mapping* mapping;

	/* Checks. */
	ASSERT_HASHTABLE(ht);
	ASSERT_NOT_NULL(key);
	ASSERT_NOT_TOO_LONG(key, HT_MAX_KEY_SIZE);

	/* Calculate the hash value. */
	hashValue = hash(key) % HT_ROW_COUNT;

	for
	(
		mapping = ht->map[hashValue];
		mapping < ht->map[hashValue] + ht->nSameHashes[hashValue];
		mapping++
	) {
		ASSERT_MAPPING(mapping);
		if (!strcmp(mapping->key, key)) {
			/* The key exists, just replace the value. */
			mapping->value = value;
			return;
		}
	}
	/* The key does NOT exist. */

	/* Get a pointer to the mapping. */
	mapping = ht->map[hashValue] + ht->nSameHashes[hashValue]++;
	ASSERT_FITS_IN_BOUND(ht->nSameHashes[hashValue], HT_MAX_SAME_HASHES);

	/* Insert the key. */
	mapping->key = fromPattern(ht->keys[ht->nKeys++], HT_MAX_KEY_SIZE, "%s", key);
	ASSERT_MAPPING(mapping);
	ASSERT_HASHTABLE(ht);

	/* Insert the value. */
	mapping->value = value;
}

/** \brief Returns the value of a given key in a HashTable
 ** \param ht A pointer to the HashTable
 ** \param key The key as a constant string
 ** \returns A pointer to the value, NULL if key does NOT exist.
 ** \memberof HashTable
 **/
const Object* get_ht(const HashTable* ht, const char* key)
{
	DECLARE_FUNCTION(get_ht);

	/* Variable declarations. */
	unsigned int hashValue;
	const Mapping* mapping;

	/* Checks. */
	ASSERT_HASHTABLE(ht);
	ASSERT_NOT_NULL(key);
	ASSERT_NOT_TOO_LONG(key, HT_MAX_KEY_SIZE);

	hashValue = hash(key) % HT_ROW_COUNT;

	for
	(
		mapping = ht->map[hashValue];
		mapping < ht->map[hashValue] + ht->nSameHashes[hashValue];
		mapping++
	) {
		ASSERT_MAPPING(mapping);
		if (!strcmp(mapping->key, key)) {
			/* Found the key, return a pointer to the value. */
			return &(mapping->value);
		}
	}

	/* Could NOT find the key! */
	return NULL;
}

/** \brief Empties the given HashTable.
 ** \param ht A pointer to the HashTable
 ** \memberof HashTable
 **/
void empty_ht(HashTable* ht)
{
	DECLARE_FUNCTION(empty_ht);

	/* Checks. */
	ASSERT_HASHTABLE(ht);
	ht = initialize_ht(ht);
	ASSERT_HASHTABLE(ht);
}
