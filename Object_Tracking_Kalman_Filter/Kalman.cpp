#include "kalman.hpp"
#include <iostream>

// Constructor
DroneKalmanFilter::DroneKalmanFilter(
    double dt,
    const Eigen::MatrixXd& A,
    const Eigen::MatrixXd& C,
    const Eigen::MatrixXd& Q,
    const Eigen::MatrixXd& R,
    const Eigen::MatrixXd& P
) : A(A), C(C), Q(Q), R(R), P0(P),
m(static_cast<int>(C.rows())), n(static_cast<int>(A.rows())),
dt(dt), initialized(false),
I(n, n), x_hat(n)
{
    I.setIdentity();
}

DroneKalmanFilter::DroneKalmanFilter() {}

void DroneKalmanFilter::init(double t0, const Eigen::VectorXd& x0) {
    this->x_hat = x0;
    this->P = P0;
    this->t0 = t0;
    this->t = t0;
    initialized = true;
}

// --- NEW: PREDICT STEP (Physics Only) ---
void DroneKalmanFilter::predict() {
    if (!initialized) return;

    // 1. Project State Ahead (x = A * x)
    x_hat = A * x_hat;

    // 2. Project Error Covariance Ahead (P = A * P * A' + Q)
    P = A * P * A.transpose() + Q;

    // 3. Advance Time
    t += dt;
}

// --- UPDATED: CORRECT STEP (Measurement Only) ---
void DroneKalmanFilter::update(const Eigen::VectorXd& y) {
    if (!initialized) return;

    // 1. Calculate Kalman Gain (K)
    // K = P * C' * inv(C * P * C' + R)
    K = P * C.transpose() * (C * P * C.transpose() + R).inverse();

    // 2. Update Estimate with Measurement (x = x + K * (y - C * x))
    x_hat += K * (y - C * x_hat);

    // 3. Update Error Covariance (P = (I - K * C) * P)
    P = (I - K * C) * P;
}