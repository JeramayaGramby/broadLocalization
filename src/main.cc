#include "broadLocalization.h"
#include <iostream>
#include <string>
#include <iomanip>

int main() {
    int shapeInput = 0;
    double latitude = 0.0;
    double longitude = 0.0;
    std::string dimensionType;
    float dimensionValue = 0.0f;
    float orientationAngle = 0.0f;

    std::cout << "Select shape type:" << std::endl;
    std::cout << "0=Circle, 1=Square, 2=Triangle, 3=Hexagon, 4=Rhombus, 5=Octagon, 6=Trapezoid, 7=Pentagon, 8=Rectangle: ";
    std::cin >> shapeInput;

    Localization::BoundaryShape shape = static_cast<Localization::BoundaryShape>(shapeInput);
    
    // This ensures the precision of floating-point output
    // and allows for 6 decimal places in the input.
    std::cout << std::fixed << std::setprecision(6);
    
    std::cout << "Enter the latitude of the center of the shape to 6 decimals" << std::endl;
    std::cin >> latitude;
    
    assert(latitude >= -90.0 && latitude <= 90.0 && "Latitude must be between -90 and 90 degrees");
    assert(std::to_string(latitude).find('.') != std::string::npos && 
        std::to_string(latitude).substr(std::to_string(latitude).find('.') + 1).size() == 6 &&
        "Latitude must have at least 6 decimal places");

    std::cout << "Enter the longitude of the center of the shape" << std::endl;
    std::cin >> longitude;
    
    assert(longitude >= -180.0 && longitude <= 180.0 && "Longitude must be between -180 and 180 degrees");
    assert(std::to_string(longitude).find('.') != std::string::npos && 
        std::to_string(longitude).substr(std::to_string(longitude).find('.') + 1).size() == 6 &&
        "Longitude must have at least 6 decimal places");

    Localization::Coordinate center(latitude, longitude);

    std::cout << "Type r for radius or s for side length (r/s): ";
    std::cin >> dimensionType;
    assert(dimensionType == "r" || dimensionType == "s" && "Invalid dimension type. Use 'r' for radius or 's' for side length.");

    std::cout << "Enter the " << (dimensionType == "r" ? "radius" : "side length") << " in units: ";
    std::cin >> dimensionValue;

    std::cout << "Enter orientation angle (degrees): ";
    std::cin >> orientationAngle;

    Localization::Boundary boundary = Localization::broadLocalization::generateBoundary(
        shape, center, dimensionValue, orientationAngle
    );

    std::cout << "\nGenerated boundary details:\n";
    std::cout << "Shape has " << boundary.vertices.size() << " vertices.\n";
    for (const Localization::Coordinate& v : boundary.vertices) {
        std::cout << "  Vertex at (" << v.latitude << ", " << v.longitude << ")\n";
    }

    return 0;
}
