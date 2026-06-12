#ifndef ACTIONS_H
#define ACTIONS_H

// Examples
void test_runes();
void test_pages();
void test_processed_text();
void test_transformer();
void test_latin();
void test_math();

// Single and Multithread test
void test_speed();
void test_singlethread();
void test_multithread();
void test_sequence();

/*
	Sequence Bruteforce

	Uses oeis sequences and decrypt it with transformer::Sequence.
	It has multithread support that split appart the work in chunks.
	Second it has interupter indices generater that takes all interrupters for each page and iterate all combinations that can exist.
	This way we can decrypt with high confidence words more perfect.
*/
void sequence_bruteforce();

#endif // ACTIONS_H