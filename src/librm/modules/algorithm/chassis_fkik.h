/*
  Copyright (c) 2024 XDU-IRobot

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/**
 * @file  librm/modules/algorithm/chassis_fkik.h
 * @brief 各种常见底盘构型的正逆运动学解算
 */

#ifndef LIBRM_MODULES_ALGORITHM_CHASSIS_FKIK_H
#define LIBRM_MODULES_ALGORITHM_CHASSIS_FKIK_H

#include "librm/core/typedefs.h"

namespace rm::modules::algorithm {

class ChassisInterface {
 public:
  virtual ~ChassisInterface() = default;
  virtual void Forward(f32 vx, f32 vy, f32 wz) = 0;
};

/**
 * @brief 麦轮底盘
 */
class MecanumChassis : public ChassisInterface {
 public:
  MecanumChassis() = delete;
  ~MecanumChassis() override = default;
  MecanumChassis(f32 wheel_base, f32 wheel_track);

  void Forward(f32 vx, f32 vy, f32 wz) override;
  // TODO: ik

  f32 speeds_[4]{};

 private:
  f32 wheel_base_{};   // 轮子间距
  f32 wheel_track_{};  // 轮子轴距
};

/**
 * @brief 四舵轮底盘
 */
class SteeringChassis : public ChassisInterface {
 public:
  explicit SteeringChassis(f32 chassis_radius);
  void Forward(f32 vx, f32 vy, f32 w);
  void Forward(f32 vx, f32 vy, f32 w, f32 current_lf_angle, f32 current_rf_angle, f32 current_lr_angle,
               f32 current_rr_angle);

 public:
  double lf_steer_position, rf_steer_position, lr_steer_position, rr_steer_position;
  double lf_wheel_speed, rf_wheel_speed, lr_wheel_speed, rr_wheel_speed;

 private:
  double chassis_radius_;
};

/**
 * @brief 四全向轮底盘
 */
class QuadOmniChassis : public ChassisInterface {
 public:
  QuadOmniChassis() = default;
  ~QuadOmniChassis() override = default;

  void Forward(f32 vx, f32 vy, f32 wz) override;
  void Inverse(f32 front_wheel_speed, f32 back_wheel_speed, f32 left_wheel_speed, f32 right_wheel_speed);

  f32 vx_{}, vy_{}, wz_{};
  f32 front_wheel_speed_{}, back_wheel_speed_{}, left_wheel_speed_{}, right_wheel_speed_{};
};

}  // namespace rm::modules::algorithm

#endif  // LIBRM_MODULES_ALGORITHM_CHASSIS_FKIK_H
