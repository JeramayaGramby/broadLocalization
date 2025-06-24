#ifndef BROADLOCALIZATION_H
#define BROADLOCALIZATION_H

#include <vector>
#include <string>
#include <cmath>
#include <cassert>

namespace Localization {

    enum class BoundaryShape {
        Circle, Square, Triangle, Hexagon,
        Rhombus, Octagon, Trapezoid,
        Pentagon, Rectangle
    };

    struct Coordinate {
        double latitude;
        double longitude;

        Coordinate(double lat = 0.0, double lon = 0.0)
            : latitude(lat), longitude(lon) {}
    };

    struct Boundary {
        BoundaryShape shape;
        Coordinate center;
        float dimension;           // Radius or side length (anchor-based)
        float orientationAngle;    // In degrees
        std::vector<Coordinate> vertices;

        Boundary(BoundaryShape s, const Coordinate& c, float d, float angle)
            : shape(s), center(c), dimension(d), orientationAngle(angle) {}
    };

    class broadLocalization {
    public:
        static Boundary generateBoundary(BoundaryShape shape,
                                         const Coordinate& center,
                                         float dimension,
                                         float orientationAngle = 0.0f);

        static bool isPointInsideBoundary(const Coordinate& point, const Boundary& boundary);
    };

} // namespace Localization

#endif // BROADLOCALIZATION_H
