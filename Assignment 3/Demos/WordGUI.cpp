#include "SpeakingRecursian.h"
#include "GUI/MiniGUI.h"
#include "GUI/Color.h"
#include "ginteractors.h"
#include <iomanip>
using namespace std;
using namespace MiniGUI;

namespace {
    /* How long a line of text can get before word-wrapping. */
    const int kMaxLineLength = 100;

    /* Maximum number of syllables where we'll list everything. */
    const int kMaxAllSyllables = 5;

    const Color kErrorColor = Color::fromHex(0x800000);

    class GUI: public ProblemHandler {
    public:
        GUI(GWindow& window) : ProblemHandler(window) {
            add(console = new GColorConsole(), "CENTER");
            add(new GLabel("Number of syllables: "));
            add(syllableSlider = new GSlider(0, kMaxAllSyllables, 3));
            add(sliderLabel = new GLabel(""));
            add(allWordsButton = new GButton("Generate All Words"));
            add(clearButton = new GButton("Clear Console"));
            changeOccurredIn(syllableSlider);
        }

        void actionPerformed(GObservable* source) override {
            int syllables = syllableSlider->getValue();
            if (source == allWordsButton) {
                listAllWords(syllables);
            } else if (source == clearButton) {
                console->clearDisplay();
                flush(*console);
            }
        }

        void listAllWords(int numSyllables) {
            *console << "Generating... " << flush;
            auto result = allRecursianWords(numSyllables);
            *console << "done! Number of words: " << addCommasTo(result.size()) << endl;

            int length = 0;
            for (const auto& word: result) {
                *console << setw(numSyllables * 2) << word << " ";

                /* Word-wrap. */
                length += numSyllables * 2 + 1;
                if (length >= kMaxLineLength) {
                    *console << '\n';
                    length = 0;
                }
            }

            *console << '\n' << endl;
        }

        void changeOccurredIn(GObservable* source) {
            if (source == syllableSlider) {
                sliderLabel->setText(pluralize(syllableSlider->getValue(), "syllable"));
            }
        }

    private:
        GColorConsole* console;
        GSlider*       syllableSlider;
        GButton*       allWordsButton;
        GButton*       clearButton;
        GLabel*        sliderLabel;
    };
}

GRAPHICS_HANDLER("Speaking Recursian", GWindow& window) {
    return make_shared<GUI>(window);
}
