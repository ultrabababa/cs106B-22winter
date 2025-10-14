#include "GUI/MiniGUI.h"
#include "TempleOfRecursia.h"
#include "MountainsOfRecursia.h"
#include "GUI/Color.h"
#include "ginteractors.h"
#include <functional>
using namespace std;
using MiniGUI::Color;

namespace {
    const double kGrassHeight = 0.85;
    const Color kGrassColor(0, 80, 0);

    class GUI: public ProblemHandler {
    public:
        GUI(GWindow& window): ProblemHandler(window) {
            makeMountains();
        }

        void repaint() override {
            window().setColor(0x91e0ff);
            window().fillRect(canvasBounds());

            for (auto polygon: mountains) {
                window().draw(polygon);
            }

            Rectangle bounds;
            bounds.x = 0;
            bounds.y = 0;
            bounds.width = window().getCanvasWidth();
            bounds.height = window().getCanvasHeight() * kGrassHeight;

            window().setColor(kGrassColor.toRGB());
            window().fillRect(0, bounds.height, bounds.width, window().getCanvasHeight() * (1 - kGrassHeight));

            auto temple = makeTemple(bounds, params);
            for (int i = 0; i < temple.size(); i++) {
                double alpha = (1.0 * i) / temple.size();

                window().setColor(Color::fromHSV(53 / 360.0, 0.32, 0.6 + 0.4 * alpha).toRGB());
                window().fillRect(temple[i].x, temple[i].y, temple[i].width, temple[i].height);
                window().setColor(Color::fromHSV(53 / 360.0, 0.32, 0.4 + 0.2 * alpha).toRGB());
                window().drawRect(temple[i].x, temple[i].y, temple[i].width, temple[i].height);
            }
        }

    private:
        TempleParameters params;
        Vector<GPolygon*> mountains;

        void makeMountains() {
            const int height = window().getCanvasHeight();
            const int width  = window().getCanvasWidth();

            /* Actual mountain ranges. */
            for (int i = 0; i < 3; i++) {
                Point p0;
                p0.x = 0;
                p0.y = randomInteger(height * (0.1 + 0.2 * i), height * (0.4 + 0.15 * i));

                Point p1;
                p1.x = width;
                p1.y = randomInteger(height * (0.1 + 0.2 * i), height * (0.4 + 0.15 * i));

                Color color = Color::fromHSV(0, 0.01, 0.2 + 0.2 * i);
                addMountain(makeMountainRange(p0, p1, height / (i + 2), 0.5), color);
            }

            /* Grassy hill. */
            Point p0 = { 0, int(height * (kGrassHeight - 0.05)) };
            Point p1 = { width, int(height * (kGrassHeight - 0.05))};
            addMountain(makeMountainRange(p0, p1, int(height * (1.0 - kGrassHeight)), 0.2), kGrassColor);
        }

        void addMountain(const Vector<Point>& mountain, Color color) {
            GPolygon* p = new GPolygon;
            for (auto point: mountain) {
                p->addVertex(point.x, point.y);
            }

            p->addVertex(mountain[mountain.size() - 1].x, window().getCanvasHeight());
            p->addVertex(mountain[0].x, window().getCanvasHeight());

            p->setFilled(true);

            p->setColor(color.toRGB());
            p->setFillColor(color.toRGB());

            mountains += p;
        }
    };
}

GRAPHICS_HANDLER("Grand View", GWindow& window) {
    return make_shared<GUI>(window);
}
