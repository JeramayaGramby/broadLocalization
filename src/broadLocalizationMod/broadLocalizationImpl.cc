// Header file imports
#include "broadLocalization.h"
#include <iostream>

namespace Localization {
    /* 
        Remember that in implementation files, it's a best practice to use anonymous namespaces
        when defining utility functions 
        or constants that should stay private to the translation unit.
    */
    namespace {
        constexpr double DEG_TO_RAD = M_PI / 180.0;

        int getNumSides(BoundaryShape shape) {
            switch (shape) {
                case BoundaryShape::Triangle: return 3;
                case BoundaryShape::Square: return 4;
                case BoundaryShape::Pentagon: return 5;
                case BoundaryShape::Hexagon: return 6;
                case BoundaryShape::Octagon: return 8;
                default: return 0; // Circle or irregular
            }
        }
    }

    Boundary broadLocalization::generateBoundary(BoundaryShape shape,
                                                 const Coordinate& center,
                                                 float dimension,
                                                 float orientationAngle) {
        assert(dimension > 0.0f);
        static_assert(sizeof(BoundaryShape) == sizeof(int),
                      "BoundaryShape size mismatch");

        constexpr double METERS_PER_DEGREE_LAT = 111000.0;
        double latRad = center.latitude * DEG_TO_RAD;

        Boundary boundary(shape, center, dimension, orientationAngle);

        int sides = getNumSides(shape);
        if (sides == 0) {
            int samples = 32;
            boundary.vertices.reserve(samples);

            for (int i = 0; i < samples; ++i) {
                double theta = 2 * M_PI * i / samples;
                double deltaNorth = dimension * std::cos(theta);
                double deltaEast  = dimension * std::sin(theta);

                double deltaLat = deltaNorth / METERS_PER_DEGREE_LAT;
                double deltaLon = deltaEast / (METERS_PER_DEGREE_LAT * std::cos(center.latitude * DEG_TO_RAD));

                double lat = center.latitude + deltaLat;
                double lon = center.longitude + deltaLon;
                boundary.vertices.push_back({lat, lon});
            }

            std::cout << "Generated circle boundary with " << samples << " vertices.\n";
            return boundary;
        }

        double angleRad = orientationAngle * DEG_TO_RAD;
        boundary.vertices.reserve(sides);

        for (int i = 0; i < sides; ++i) {
            double theta = angleRad + (2 * M_PI * i / sides);
            double deltaNorth = dimension * std::cos(theta); // meters
            double deltaEast  = dimension * std::sin(theta); // meters

            double deltaLat = deltaNorth / METERS_PER_DEGREE_LAT;
            double deltaLon = deltaEast / (METERS_PER_DEGREE_LAT * std::cos(latRad));

            double lat = center.latitude + deltaLat;
            double lon = center.longitude + deltaLon;
            boundary.vertices.push_back({lat, lon});
        }

        assert(boundary.vertices.size() == static_cast<size_t>(sides));
        return boundary;
    }

    bool broadLocalization::isPointInsideBoundary(const Coordinate& point, const Boundary& boundary) {
        if (boundary.shape == BoundaryShape::Circle) {
            double dx = point.latitude - boundary.center.latitude;
            double dy = point.longitude - boundary.center.longitude;
            double distance = std::sqrt(dx * dx + dy * dy);
            return distance <= boundary.dimension;
        }

        const auto& vertices = boundary.vertices;
        int crossings = 0;
        size_t count = vertices.size();
        for (size_t i = 0; i < count; ++i) {
            const Coordinate& a = vertices[i];
            const Coordinate& b = vertices[(i + 1) % count];

            if (((a.longitude > point.longitude) != (b.longitude > point.longitude)) &&
                (point.latitude < (b.latitude - a.latitude) * (point.longitude - a.longitude) / (b.longitude - a.longitude) + a.latitude)) {
                ++crossings;
            }
        }

        return (crossings % 2) == 1; // Inside if odd crossings
    }

} 
