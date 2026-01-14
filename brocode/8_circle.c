/* giving a radius, calculate circle area, sphere surface area, sphere volume */
#include <stdio.h>
#include <math.h>

int main()
{
    const double PI = 3.14159;
    double radius = 0.0;
    double circle_area = 0.0;
    double sphere_surface_area = 0.0;
    double sphere_volume = 0.0;

    printf("Enter the radius: ");
    scanf("%lf", &radius);

    circle_area = PI * pow(radius, 2);
    sphere_surface_area = 4 * PI * pow(radius, 2);
    sphere_volume = (4.0 / 3.0) * PI * pow(radius, 3);

    printf("Circle Area = %lf\n", circle_area);
    printf("Sphere Surface Area = %lf\n", sphere_surface_area);
    printf("Sphere Volume = %lf\n", sphere_volume);

    return 0;
}
