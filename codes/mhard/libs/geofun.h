double calculateAngle(double a, double b, double c) {
    return acos((b * b + c * c - a * a) / (2 * b * c));
}
