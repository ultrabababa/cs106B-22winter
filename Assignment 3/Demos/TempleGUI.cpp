#include "GUI/MiniGUI.h"
#include "TempleOfRecursia.h"
#include "MountainsOfRecursia.h"
#include "GUI/Color.h"
#include "ginteractors.h"
#include <functional>
using namespace std;
using MiniGUI::Color;

namespace {
    /* Function that takes in a slider value and updates temple parameters. */
    using Setter = function<void(TempleParameters&, int)>;

    Setter zeroOneSetter(double TempleParameters::* field) {
        return [=](TempleParameters& params, int value) {
            params.*field = double(value) / 100;
        };
    }

    template <typename T> Setter directSetter(T TempleParameters::* field) {
        return [=](TempleParameters& params, int value) {
            params.*field = value;
        };
    }

    GContainer* boxUp(const string& label, GInteractor* interactor) {
        GContainer* result = new GContainer;
        result->add(new GLabel(label));
        result->add(interactor);
        return result;
    }

    class GUI: public ProblemHandler {
    public:
        GUI(GWindow& window): ProblemHandler(window) {
            GContainer* panel = new GContainer(GContainer::LAYOUT_GRID);

            panel->addToGrid(boxUp("Order", newSetter(directSetter(&TempleParameters::order), 0, 7, params.order)), 0, 0);
            panel->addToGrid(boxUp("# Small Towers", newSetter(directSetter(&TempleParameters::numSmallTemples), 2, 6, 4)), 0, 1);
            panel->addToGrid(boxUp("Base Height", newZeroOneSetter(&TempleParameters::baseHeight)), 0, 2);
            panel->addToGrid(boxUp("Base Width", newZeroOneSetter(&TempleParameters::baseWidth)), 1, 0);
            panel->addToGrid(boxUp("Column Height", newZeroOneSetter(&TempleParameters::columnHeight)), 1, 1);
            panel->addToGrid(boxUp("Column Width", newZeroOneSetter(&TempleParameters::columnWidth)), 1, 2);
            panel->addToGrid(boxUp("Upper Temple Height", newZeroOneSetter(&TempleParameters::upperTempleHeight)), 2, 0);
            panel->addToGrid(boxUp("Small Tower Width", newZeroOneSetter(&TempleParameters::smallTempleWidth)), 2, 1);
            panel->addToGrid(boxUp("Small Tower Height", newZeroOneSetter(&TempleParameters::smallTempleHeight)), 2, 2);

            add(panel);
        }

        void changeOccurredIn(GObservable* source) override {
            auto* slider = dynamic_cast<GSlider*>(source);
            if (slider && setters.containsKey(slider)) {
                setters[slider](params, slider->getValue());
                requestRepaint();
            }
        }

        void repaint() override {
            window().clearCanvas();

            GRectangle realBounds = canvasBounds();
            Rectangle bounds;
            bounds.x = realBounds.x;
            bounds.y = realBounds.y;
            bounds.width = realBounds.width;
            bounds.height = realBounds.height;

            for (const auto& rect: makeTemple(bounds, params)) {
                window().setColor(0);
                window().drawRect(rect.x, rect.y, rect.width, rect.height);
            }
        }

    private:
        TempleParameters params;

        /* All setters. */
        Map<GSlider*, Setter> setters;
        GSlider* newSetter(Setter setter, int min, int max, int def) {
            GSlider* result = new GSlider(min, max, def);
            setters[result] = setter;
            return result;
        }

        GSlider* newZeroOneSetter(double TempleParameters::* field) {
            return newSetter(zeroOneSetter(field), 0, 100, 100 * params.*field);
        }
    };
}

GRAPHICS_HANDLER("Temple", GWindow& window) {
    return make_shared<GUI>(window);
}
