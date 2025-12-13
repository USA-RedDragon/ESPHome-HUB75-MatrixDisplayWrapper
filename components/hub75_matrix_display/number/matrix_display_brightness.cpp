#include "matrix_display_brightness.h"

#include <cmath>

namespace esphome::matrix_display::matrix_display_brightness
{

    void MatrixDisplayBrightness::setup()
    {
        float target_brightness = this->display_->get_initial_brightness();

        if (this->restore_value_)
        {
            this->pref_ = global_preferences->make_preference<float>(this->get_preference_hash());

            float restored_value;
            if (this->pref_.load(&restored_value))
            {
                target_brightness = restored_value;
            }
            else if (!std::isnan(this->initial_value_))
            {
                target_brightness = this->initial_value_;
            }
        }
        else if (!std::isnan(this->initial_value_))
        {
            target_brightness = this->initial_value_;
        }

        // Apply the initial brightness to the display (and broadcast to other number entities)
        this->control(target_brightness);
    }

    void MatrixDisplayBrightness::control(float value)
    {
        // Update the display brightness and forward state to all number entities
        display_->set_brightness((int)value);
        for (MatrixDisplayBrightness *brightness_value : display_->get_brightness_values())
        {
            brightness_value->publish_state(value);
        }

        if (this->restore_value_)
        {
            this->pref_.save(&value);
        }
    }

    void MatrixDisplayBrightness::dump_config()
    {
        ESP_LOGCONFIG(TAG, "MatrixDisplayBrightness");
    }

} // namespace esphome::matrix_display::matrix_display_brightness