#include "Plotter.h"
#include "vector.h"
#include "strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    // Initialize plotter state
    double currentX = 0.0;
    double currentY = 0.0;
    bool penIsDown = false;
    PenStyle currentStyle = { 1.0, "black" };

    // Read and process each line of the script
    for (string line; getline(input, line); ) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Split the line into tokens
        Vector<string> tokens = stringSplit(line, ' ');

        if (tokens.isEmpty()) {
            continue;
        }

        // Get the command (case-insensitive)
        string command = toLowerCase(tokens[0]);

        // Process the command
        if (command == "pendown") {
            penIsDown = true;
        }
        else if (command == "penup") {
            penIsDown = false;
        }
        else if (command == "moveabs") {
            // Move to absolute position
            if (tokens.size() >= 3) {
                double newX = stringToReal(tokens[1]);
                double newY = stringToReal(tokens[2]);

                // Draw a line if pen is down
                if (penIsDown) {
                    drawLine(currentX, currentY, newX, newY, currentStyle);
                }

                // Update current position
                currentX = newX;
                currentY = newY;
            }
        }
        else if (command == "moverel") {
            // Move relative to current position
            if (tokens.size() >= 3) {
                double dx = stringToReal(tokens[1]);
                double dy = stringToReal(tokens[2]);
                double newX = currentX + dx;
                double newY = currentY + dy;

                // Draw a line if pen is down
                if (penIsDown) {
                    drawLine(currentX, currentY, newX, newY, currentStyle);
                }

                // Update current position
                currentX = newX;
                currentY = newY;
            }
        }
        else if (command == "pencolor") {
            // Change pen color
            if (tokens.size() >= 2) {
                currentStyle.color = tokens[1];
            }
        }
        else if (command == "penwidth") {
            // Change pen width
            if (tokens.size() >= 2) {
                currentStyle.width = stringToReal(tokens[1]);
            }
        }
    }


}
