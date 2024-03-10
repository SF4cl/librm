
#ifndef EC_FRAMEWORK_BSP_BUZZER_H
#define EC_FRAMEWORK_BSP_BUZZER_H

    #ifdef TIM_MODULE_ENABLED


    #include "tim.h"


    namespace bsp::buzzer {

        class Buzzer {
        public:
            Buzzer(TIM_HandleTypeDef htim);
            Buzzer()  = delete;
            ~Buzzer() = default;

            void on();
            void off();
        private:


            TIM_HandleTypeDef htim;
        };

    }   // namespace bsp::buzzer


    #endif

#endif