#include "MountainsOfRecursia.h"
#include "GUI/MiniGUI.h"
#include "ginteractors.h"
#include <sstream>
#include <iomanip>
using namespace std;

namespace {
    const double kRadius = 10.0; // Radius of control circle
    const double kInset  = 20;   // Initial amount to inset them from window sides

    double distanceFrom(double x0, double y0, double x1, double y1) {
        return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    }

    class GUI: public ProblemHandler {
    public:
        GUI(GWindow& window) : ProblemHandler(window) {
            add(new GLabel("Amplitude: "));
            add(amplitudeSlider = new GSlider(0, 200, 50));
            add(amplitudeLabel = new GLabel());

            add(new GLabel("Decay Rate: "));
            add(decaySlider = new GSlider(0, 100, 50));
            add(decayLabel = new GLabel());

            add(goButton = new GButton("Generate Mountains"));

            changeOccurredIn(amplitudeSlider);

            /* Position control points. */
            left.x = kInset;
            right.x = window.getCanvasWidth() - kInset;
            left.y = right.y = window.getCanvasHeight() / 2;
        }

        void changeOccurredIn(GObservable *) override {
            amplitudeLabel->setText(to_string(amplitudeSlider->getValue()));

            ostringstream builder;
            builder << fixed << setprecision(2) << (decaySlider->getValue() / 100.0);
            decayLabel->setText(builder.str());

            range.clear();
            requestRepaint();
        }

        void mousePressed(double x, double y) override {
            if (distanceFrom(x, y, left.x, left.y) <= kRadius) {
                dragged = &left;
            } else if (distanceFrom(x, y, right.x, right.y) <= kRadius) {
                dragged = &right;
            } else {
                dragged = nullptr;
            }

            lastX = x;
            lastY = y;
        }

        void mouseDragged(double x, double y) override {
            if (dragged != nullptr) {
                dragged->x += (x - lastX);
                dragged->y += (y - lastY);
            }

            lastX = x;
            lastY = y;

            range.clear();
            requestRepaint();
        }

        void mouseReleased(double, double) override {
            dragged = nullptr;
        }

        void actionPerformed(GObservable* source) {
            if (source == goButton) {
                Point from, to;
                from.x = left.x;
                from.y = left.y;
                to.x   = right.x;
                to.y   = right.y;

                int amplitude = amplitudeSlider->getValue();
                double decay  = decaySlider->getValue() / 100.0;

                if (from.x > to.x) {
                    swap(from, to);
                }

                range = makeMountainRange(from, to, amplitude, decay);
                requestRepaint();
            }
        }

        void repaint() override {
            window().clearCanvas();

            drawCenteredCircle(left.x,  left.y);
            drawCenteredCircle(right.x, right.y);

            window().setColor(0);
            for (int i = 0; i + 1 < range.size(); i++) {
                window().drawLine(range[i].x, range[i].y, range[i+1].x, range[i+1].y);
            }
        }

    private:
        GLabel*  amplitudeLabel;
        GLabel*  decayLabel;
        GSlider* amplitudeSlider;
        GSlider* decaySlider;
        GButton* goButton;

        GPoint left, right;

        double lastX, lastY;
        GPoint*   dragged = nullptr;
        Vector<Point> range;

        void drawCenteredCircle(double x, double y) {
            window().setColor("blue");
            window().fillOval(x - kRadius, y - kRadius, 2 * kRadius, 2 * kRadius);
        }
    };
}

GRAPHICS_HANDLER("Mountains", GWindow& window) {
    return make_shared<GUI>(window);
}
