#pragma once
#include <Eigen/Dense>

class DroneKalmanFilter {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        // Constructor
        DroneKalmanFilter(
            double dt,
            const Eigen::MatrixXd& A,
            const Eigen::MatrixXd& C,
            const Eigen::MatrixXd& Q,
            const Eigen::MatrixXd& R,
            const Eigen::MatrixXd& P
        );

    DroneKalmanFilter();

    void init(double t0, const Eigen::VectorXd& x0);

    // --- NEW: Separate Predict Function ---
    void predict();

    // Update now ONLY corrects the state, it doesn't move time forward
    void update(const Eigen::VectorXd& y);

    Eigen::VectorXd state() { return x_hat; };

private:
    Eigen::MatrixXd A, C, Q, R, P, K, P0;
    int m, n;
    double t0, t, dt;
    bool initialized;
    Eigen::MatrixXd I;
    Eigen::VectorXd x_hat;
};