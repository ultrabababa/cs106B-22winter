#include "SpeakingRecursian.h"
using namespace std;

Vector<string> allRecursianWords(int numSyllables) {
    /* TODO: Delete this comment and the next few lines, then implement
     * this function.
     */
    (void) numSyllables;
    return { };
}


/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"
#include "GUI/TextUtils.h"
#include "set.h"

PROVIDED_TEST("allRecursianWords works in simple cases.") {
    EXPECT_EQUAL(allRecursianWords(0), {""});
    EXPECT_ERROR(allRecursianWords(-1));
    EXPECT_ERROR(allRecursianWords(-137));
}

PROVIDED_TEST("allRecursianWords works for length 1.") {
    auto wordsUnsorted = allRecursianWords(1);

    /* Sort the words using a set. This will also eliminate duplicates. */
    Set<string> words;
    for (string word: wordsUnsorted) {
        /* All one-syllable words have length one or two. */
        EXPECT(word.length() == 1 || word.length() == 2);

        words += word;
    }

    /* Should be the same number of words once we sort them. */
    EXPECT_EQUAL(wordsUnsorted.size(), words.size());

    Set<string> expected = {
        "'e", "'i", "'u", "be", "bi", "bu", "e", "i",
        "ke", "ki", "ku", "ne", "ni", "nu", "re", "ri",
        "ru", "se", "si", "su", "u"
    };

    EXPECT_EQUAL(words, expected);
}

PROVIDED_TEST("allRecursianWords has the right quantities of words.") {
    EXPECT_EQUAL(allRecursianWords(0).size(), 1);
    EXPECT_EQUAL(allRecursianWords(1).size(), 21);
    EXPECT_EQUAL(allRecursianWords(2).size(), 378);
    EXPECT_EQUAL(allRecursianWords(3).size(), 6804);
    EXPECT_EQUAL(allRecursianWords(4).size(), 122472);
}

namespace {
    bool isConsonant(char ch) {
        return ch == 'b' || ch == 'k' || ch == 'n' || ch == 'r' || ch == 's' || ch == '\'';
    }
    bool isVowel(char ch) {
        return ch == 'e' || ch == 'i' || ch == 'u';
    }
}

PROVIDED_TEST("allRecursianWords produces words consisting of consonants and vowels.") {
    /* There are too many words here to check the answer against a reference - and it's
     * infeasible to manually create a reference. Instead, we will generate a list of
     * words and confirm that each one is either a consonant or a vowel. If we see
     * anything else, we know the answer is wrong.
     *
     * This won't catch everything, though. It's entirely possible to have a word made
     * entirely of vowels pass, or a word of way too many consonants pass. You will
     * need to write your own test cases to cover cases not detected here.
     */
    auto words = allRecursianWords(4);
    EXPECT_NOT_EQUAL(words.size(), 0);

    for (string word: words) {
        for (char ch: word) {
            EXPECT(isConsonant(ch) || isVowel(ch));
        }
    }
}
