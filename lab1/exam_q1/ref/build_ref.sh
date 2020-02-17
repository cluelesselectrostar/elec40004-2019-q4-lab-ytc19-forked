g++ -Os -DNDEBUG=1 -s -I.. canonical_sentences.cpp sentence_reader.cpp -o canonical_sentences_ref
g++ -Os -DNDEBUG=1 -s -I.. find_close_words.cpp sentence_reader.cpp lower_case.cpp -o find_close_words_ref

