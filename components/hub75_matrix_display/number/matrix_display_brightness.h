#pragma once

#include <cmath>

#include "esphome/core/component.h"
#include "esphome/core/preferences.h"
#include "esphome/components/number/number.h"
#include "../matrix_display.h"

namespace esphome::matrix_display::matrix_display_brightness
{
    static const char *TAG = "matrix_display.number";
    class MatrixDisplayBrightness : public number::Number, public Component
    {
    public:
        void setup() override;

        /**
         * Set the display brightness and update all brightness number entities
         *
         * @param value value to set
         */
        void control(float value);

        void dump_config() override;

        void set_restore_value(bool restore_value)
        {
            this->restore_value_ = restore_value;
        }

        void set_initial_value(float initial_value)
        {
            this->initial_value_ = initial_value;
        }

        /**
         * Sets the reference to the display component to which this brightness number belongs.
         *
         * @param display Matrix display component reference
         */
        void set_display(MatrixDisplay *display)
        {
            this->display_ = display;
        }

    protected:
        /// @brief display component to which this switch belongs
        MatrixDisplay *display_;

        /// @brief whether this number should persist the last value
        bool restore_value_{false};

        /// @brief storage for persisting the brightness value when restore_value_ is enabled
        ESPPreferenceObject pref_;

        /// @brief optional user provided initial value used when restore is disabled or unset
        float initial_value_{NAN};
    };

    /**
     * Sets the reference to the display component to which this brightness number belongs.
     *
     * @param brightness brightness for which the reference should be set
     * @param display Matrix display component reference
     */
    static void set_reference(MatrixDisplayBrightness *brightness, MatrixDisplay *display)
    {
        brightness->set_display(display);
    }

    /**
     * Publishes the provide brightness value for a given brightness number entity.
     *
     * @param brightness brightness for which the state should be published
     * @param value value to publish
     */
    static void publish_state(MatrixDisplayBrightness *brightness, int value)
    {
        brightness->publish_state(value);
    }
} // namespace esphome::matrix_display::matrix_display_brightness