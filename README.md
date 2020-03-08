# Tweet

The CSV extension is unnecessary it's basically one tweet per line, I've removed
the extra clutter from the original dataset

Which included 1.6 Million tweets from 2009

## Summary of the Project

This program gets the words from the file and checks if that word is longer than
9 characters
or that the word is not in the stop words list, which includes the most common
words on the internet.

In which case the word is discarded

If the word is not found in the stop words and if it's shorter than 9 characters,
it's stored in a [Trie](https://en.wikipedia.org/wiki/Trie)
data structure which is good for storing the words of a language.

Searching for a word in a trie takes O(L) where L is the length of the word
being queried.

Inserting a word is O(L) as well, which is far more efficient that just storing
them in an array-like
structure causing us to search the whole container

The Trie implementation I have can be improved upon by using a smart hashed
version but this was for a school project and
the original code, this is the refactored one, did the task (1.6M Lines, Top 10
most frequent words) in around 8 seconds.

The refactored version you see here finishes in around 3-4 seconds, but the
input file is cleaner and shorter, so not a fair test

## Data

The data can be found [here](https://drive.google.com/drive/folders/1XMjqF_4nJLeOEIshZgkRqz0AAJTnRvZH?usp=sharing).

