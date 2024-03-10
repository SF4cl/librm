
/***
 * @file  components/c_motor.h
 * @brief Motor driver classes
 */

#pragma once

#include "hal_wrapper/hal_config.h"

#ifdef HAL_CAN_MODULE_ENABLED

    #ifndef EC_FRAMEWORK_DJI_MOTOR_H
    #define EC_FRAMEWORK_DJI_MOTOR_H

    #include <cstdint>

    #include "hal_wrapper/hal_can.h"


    namespace components::motor {


        /***
         * @brief DJI motor base class
         * @note This class is pure virtual, its inheritance class must implement
         * @note setCurrent() to control the motor
         */
        class DJIMotorBase : public hal::can::CANDeviceBase {
        public:
            DJIMotorBase() = delete;

            virtual void setCurrent(int16_t current) = 0;

            [[nodiscard]] uint16_t getEncoder() const;
            [[nodiscard]] uint16_t getRPM() const;
            [[nodiscard]] uint16_t getCurrent() const;
            [[nodiscard]] uint16_t getTemperature() const;

        protected:
            DJIMotorBase(CAN_HandleTypeDef *hcan, uint16_t id);

            void rxCallback(hal::can::can_rx_msg_t *msg) override;

            uint16_t id_{};
            /** MOTOR FEEDBACK DATA **/
            uint16_t ecd_{};
            uint16_t rpm_{};
            uint16_t current_{};
            uint16_t temperature_{};
            /*************************/

        };


        /***
         * @brief DJI GM6020 motor
         * @note Feedback message stdID:    0x205 + ID
         * @note Control message stdID:     0x1ff(1234), 0x2ff(567)
         * @note Voltage range:             -30000 ~ 30000, big-endian
         * @note STD, DATA, DLC=8
         * @note https://www.robomaster.com/zh-CN/products/components/general/GM6020
         */
        class GM6020 : public DJIMotorBase {
        public:
            GM6020() = delete;

            GM6020(CAN_HandleTypeDef *hcan, uint16_t id);

            void setCurrent(int16_t current) override;      // For GM6020, this function is actually setting the voltage
        protected:
            static uint8_t tx_buffer_[8];
        };


        /***
         * @brief DJI M2006 Motor/C610 ESC
         * @note Feedback message stdID:    0x200 + ID
         * @note Control message stdID:     0x200(1234), 0x1ff(5678)
         * @note Current range:             -10000 ~ 10000(-10A ~ 10A), big-endian
         * @note STD, DATA, DLC=8
         * @note https://www.robomaster.com/zh-CN/products/components/general/M2006
         */
        class M2006 : public DJIMotorBase {
        public:
            M2006() = delete;

            M2006(CAN_HandleTypeDef *hcan, uint16_t id);

            void setCurrent(int16_t current) override;

        protected:
            static uint8_t tx_buffer_[8];
        };


        /***
         * @brief DJI M3508 Motor/C620 ESC
         * @note Feedback message stdID:    0x201 + ID
         * @note Control message stdID:     0x200(1234), 0x1ff(5678)
         * @note Current range:             -16384 ~ 16384(-20A ~ 20A), big-endian
         * @note STD, DATA, DLC=8
         * @note https://www.robomaster.com/zh-CN/products/components/general/M3508
         */
        class M3508 : public DJIMotorBase {
        public:
            M3508() = delete;

            M3508(CAN_HandleTypeDef *hcan, uint16_t id);

            void setCurrent(int16_t current) override;

        protected:
            static uint8_t tx_buffer_[8];
        };

    }   // namespace Components::Motor

    #endif

#endif

/* EOF */