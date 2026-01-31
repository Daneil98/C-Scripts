#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include "kalman.hpp" 

using namespace cv;
using namespace std;
using namespace Eigen;

// GLOBAL VARIABLE for mouse tracking
Point mouse_info = Point(0, 0);

void mouse_callback(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_MOUSEMOVE) {
        mouse_info.x = x;
        mouse_info.y = y;
    }
}

int main() {
    // 1. Setup the Screen
    Mat img(800, 800, CV_8UC3);
    namedWindow("Drone Tracking Test");
    setMouseCallback("Drone Tracking Test", mouse_callback, NULL);

    // 2. Initialize Filter
    int n = 4; // States: x, y, vx, vy
    int m = 2; // Measurements: x, y
    double dt = 1.0 / 30.0; // Assume 30 FPS

    MatrixXd A(n, n); // Physics: Pos = Pos + Vel*dt
    A << 1, 0, dt, 0,
        0, 1, 0, dt,
        0, 0, 1, 0,
        0, 0, 0, 1;

    MatrixXd C(m, n); // Measurement: We only see Pos
    C << 1, 0, 0, 0,
        0, 1, 0, 0;

    MatrixXd Q(n, n); // Process Noise (Physics uncertainty)
    Q.setIdentity();
    Q *= 0.1;

    MatrixXd R(m, m); // Sensor Noise (Measurement uncertainty)
    R.setIdentity();
    R *= 10;

    MatrixXd P(n, n); // Initial Uncertainty
    P.setIdentity();
    P *= 1000;

    // RENAMED CLASS HERE TO AVOID CONFLICT
    DroneKalmanFilter kf(dt, A, C, Q, R, P);

    VectorXd x0(n);
    x0 << 0, 0, 0, 0;
    kf.init(0, x0);

    // 3. Loop
    while (true) {
        img = Scalar(10, 10, 10); // Clear background

        // Get Input + Add Noise
        double noisyX = mouse_info.x + (rand() % 100 - 50);
        double noisyY = mouse_info.y + (rand() % 100 - 50);

        VectorXd y(m);
        y << noisyX, noisyY;

        // Kalman Update
        kf.update(y);

        VectorXd estimate = kf.state();
        Point estimatedPos(static_cast<int>(estimate(0)), static_cast<int>(estimate(1)));

        // Draw
        circle(img, mouse_info, 5, Scalar(0, 255, 0), -1); // Green (Truth)
        circle(img, Point(noisyX, noisyY), 3, Scalar(0, 0, 255), -1); // Red (Noise)
        circle(img, estimatedPos, 8, Scalar(255, 255, 0), 2); // Blue (Filter)

        // HUD
        putText(img, "Green: Mouse (Truth)", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0));
        putText(img, "Red: Sensor Noise", Point(10, 50), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255));
        putText(img, "Blue: Kalman Prediction", Point(10, 70), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 0));

        imshow("Drone Tracking Test", img);
        if (waitKey(30) == 27) break; // ESC to exit
    }
    return 0;
}