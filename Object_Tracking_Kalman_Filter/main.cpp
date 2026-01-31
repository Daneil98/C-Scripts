#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include "kalman.hpp" 

using namespace cv;
using namespace std;
using namespace Eigen;

int main() {
    // 1. INITIALIZE CAMERA (The "Eyes")
    // 0 is the default webcam. Change to 1 if you have a USB camera plugged in.
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open camera" << endl;
        return -1;
    }

    // 2. SETUP KALMAN FILTER (The "Brain")
    int n = 4; // State: [x, y, vx, vy]
    int m = 2; // Measurement: [x, y]
    double dt = 1.0 / 30.0; // Assume 30 FPS

    MatrixXd A(n, n);
    A << 1, 0, dt, 0,
        0, 1, 0, dt,
        0, 0, 1, 0,
        0, 0, 0, 1;

    MatrixXd C(m, n);
    C << 1, 0, 0, 0,
        0, 1, 0, 0;

    MatrixXd Q(n, n);
    Q.setIdentity();
    Q *= 0.3; // Process Noise

    MatrixXd R(m, m);
    R.setIdentity();
    R *= 10; // Measurement Noise

    MatrixXd P(n, n);
    P.setIdentity();
    P *= 1000; // Initial Uncertainty

    DroneKalmanFilter kf(dt, A, C, Q, R, P);

    // Initialize state (we assume starting at 0,0 until we see something)
    VectorXd x0(n);
    x0 << 0, 0, 0, 0;
    kf.init(0, x0);

    // 3. THE LOOP
    Mat frame, hsv, mask, mask1, mask2;

    while (true) {
        // A. CAPTURE IMAGE
        cap >> frame;
        if (frame.empty()) break;

        kf.predict();

        // C. COMPUTER VISION (Find the Red Object)
        // Convert BGR to HSV
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // Threshold Red (Red wraps around 0-180, so we need two ranges)
        // Range 1: 0-10
        inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), mask1);
        // Range 2: 170-180
        inRange(hsv, Scalar(170, 120, 70), Scalar(180, 255, 255), mask2);

        // Combine masks (Bitwise OR)
        bitwise_or(mask1, mask2, mask);

        // Find Contours
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // D. IF OBJECT FOUND -> UPDATE STEP
        if (contours.size() > 0) {
            // Find the largest contour (The biggest red blob)
            // We use a lambda function to find the max area
            auto largest_contour = max_element(contours.begin(), contours.end(),
                [](const vector<Point>& a, const vector<Point>& b) {
                    return contourArea(a) < contourArea(b);
                });

            // Calculate Center (Moments)
            Moments mu = moments(*largest_contour);
            if (mu.m00 > 0) {
                int cx = static_cast<int>(mu.m10 / mu.m00);
                int cy = static_cast<int>(mu.m01 / mu.m00);

                // Update Kalman Filter with "Real" Data
                VectorXd z(m);
                z << cx, cy;
                kf.update(z);

                // VISUALIZATION: Draw Red Circle (The Sensor)
                Point2f center;
                float radius;
                minEnclosingCircle(*largest_contour, center, radius);
                circle(frame, center, static_cast<int>(radius), Scalar(0, 0, 255), 2);

                kf.update(z);
            }
        }

        // E. DRAW PREDICTION (The "Missile Lock")
        // Get the Kalman estimate (Smooth Blue Circle)
        VectorXd hat = kf.state();
        Point estimatedPos(static_cast<int>(hat(0)), static_cast<int>(hat(1)));

        circle(frame, estimatedPos, 15, Scalar(255, 255, 0), 2); // Blue
        putText(frame, "Tracking", Point(estimatedPos.x + 20, estimatedPos.y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0));

        // Show Result
        imshow("Drone Tracking Test", frame);
        // imshow("Mask Debug", mask); // Uncomment to see what the camera sees

        if (waitKey(30) == 27) break; // ESC to exit
    }

    return 0;
}