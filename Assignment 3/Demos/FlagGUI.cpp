#include "GUI/MiniGUI.h"
#include "FlagOfRecursia.h"
#include "gcanvas.h"
#include "gobjects.h"
#include "ginteractors.h"
using namespace std;
using namespace MiniGUI;

/* One of these functions launches the flag-drawing. But which one is it?
 * Use the debugger to find out!
 */
void makeTheMagicHappen(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void abracadabra(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void itsFlagTime(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void doTheThing(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void loAndBehold(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void reticulateSplines(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void standAndSalute(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void zoomAndEnhance(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void raiseTheStandard(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

void oohOohPickMePickMe(const Rectangle& bounds) {
    drawFlagOfRecursia(bounds);
}

/* A list of all the above functions. Each one could in
 * principle draw the Flag of Recursia. But which one
 * actually does? Use the debugger to find out!
 */
Vector<void (*) (const Rectangle& bounds)> kFunctions = {
    makeTheMagicHappen,
    abracadabra,
    itsFlagTime,
    doTheThing,
    loAndBehold,
    reticulateSplines,
    standAndSalute,
    zoomAndEnhance,
    raiseTheStandard,
    oohOohPickMePickMe
};

namespace {
    static GCanvas* theCanvas = nullptr;

    /* Backgroudn color for the flag. */
    const Color kBackground = Color( 40,  40, 120);

    /* Padding from window bounds. */
    const double kPadding = 10;

    /* Flag's aspect ratio. */
    const double kFlagAspectRatio = 5.0 / 3.0; // Standard for standards

    /* Message warning about resizing the window first. */
    const string kResizeMessage =
        "Don't forget to resize this window so that you can see both the graphics display "
        "and the Qt Creator debugger before hitting the \"Go!\" button. Once the debugger "
        "engages, you may not be able to resize or move this window.";

    /* Font info for that message. */
    const Font kResizeMessageFont(FontFamily::SERIF, FontStyle::ITALIC, 24, Color::fromHex(0x80FFFF));

    /* This is a function called xorshift that takes in an integer, scrambles it, and returns another
     * integer. We use it to derive different values as the story unfolds so that the story isn't
     * too predictable.
     */
    int scramble(int value) {
        uint32_t uValue = value;

        /* These values are here for a specific reason. For more details, see
         *
         * https://stackoverflow.com/questions/71522815/why-xorshift-random-number-generator-uses-the-same-amount-of-sbr-sbl-in-all-ex
         */
        uValue ^= uValue << 13;
        uValue ^= uValue >> 17;
        uValue ^= uValue << 5;
        return uValue & 0x7FFFFFFF;
    }

    class GUI: public ProblemHandler {
    public:
        GUI(GWindow& window) : ProblemHandler(window) {
            theCanvas = window.getCanvas();

            add(goButton = new GButton("Go!"));
        }

        ~GUI() {
            theCanvas = nullptr;
        }

        void actionPerformed(GObservable* source) override {
            if (haveStarted == false) {
                if (source == goButton) {
                    haveStarted = true;
                    goButton->setEnabled(false);
                    drawFlag();
                }
            }
        }

        void repaint() override {
            if (!haveStarted) {
                drawMessage();
            }
        }

    private:
        void drawFlag() {
            window().clearCanvas();
            window().setColor(Color::BLACK().toRGB());
            window().fillRect(canvasBounds());

            /* Pull full bounds inwards a bit. */
            GRectangle fullBounds = canvasBounds();
            fullBounds.x      += kPadding;
            fullBounds.y      += kPadding;
            fullBounds.width  -= 2 * kPadding;
            fullBounds.height -= 2 * kPadding;

            /* Get to the correct aspect ratio. */
            GRectangle truncatedBounds = fitToBounds(fullBounds, kFlagAspectRatio);

            /* Nothing to do if we can't fit everything on-screen. */
            if (truncatedBounds.width <= 0 || truncatedBounds.height <= 0) return;

            /* Convert from GRectangle to Rectangle. */
            Rectangle bounds;
            bounds.x      = truncatedBounds.x;
            bounds.y      = truncatedBounds.y;
            bounds.width  = truncatedBounds.width;
            bounds.height = truncatedBounds.height;

            /* Draw the flag background. */
            window().setColor(kBackground.toRGB());
            window().fillRect(bounds.x, bounds.y, bounds.width, bounds.height);

            /* Draw a one-pixel border around the flag. */
            window().setColor(Color::YELLOW().toRGB());
            window().drawRect(bounds.x - 1, bounds.y - 1, bounds.width + 2, bounds.height + 2);

            /* So it isn't surprising when suddenly the background changes. */
            window().repaint();

            /* Choose one of the ten functions listed above to actually draw
             * the flag. Which one? Walk the call stack to see!
             */
            kFunctions[scramble(scramble(scramble(scramble(scramble(137))))) % kFunctions.size()](bounds);
        }

        void drawMessage() {
            window().setColor("black");
            window().fillRect(canvasBounds());

            auto render = TextRender::construct(kResizeMessage, canvasBounds(), kResizeMessageFont);
            render->alignCenterVertically();
            render->alignCenterHorizontally();
            render->draw(window());
        }

        GButton* goButton;
        bool haveStarted = false;
    };
}

void drawTriangle(const Point& p0, const Point& p1, const Point& p2, Color c) {
    if (theCanvas == nullptr) {
        error("Called drawTriangle() without the Flag of Recursia demo running.");
    }

    GPolygon triangle;
    triangle.addVertex(p0.x, p0.y);
    triangle.addVertex(p1.x, p1.y);
    triangle.addVertex(p2.x, p2.y);

    triangle.setFilled(true);
    triangle.setFillColor(c.toRGB());
    triangle.setColor(c.toRGB());

    theCanvas->draw(&triangle);
    theCanvas->repaint();
}

GRAPHICS_HANDLER("Flag of Recursia", GWindow& window) {
    return make_shared<GUI>(window);
}
