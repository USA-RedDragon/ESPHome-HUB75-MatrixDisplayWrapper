import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import CONF_MODE, CONF_RESTORE_VALUE, CONF_INITIAL_VALUE

from ..display import MATRIX_ID, MatrixDisplay

matrix_display_brightness_ns = cg.esphome_ns.namespace(
    "matrix_display::matrix_display_brightness"
)
MatrixDisplayBrightness = matrix_display_brightness_ns.class_(
    "MatrixDisplayBrightness", number.Number, cg.Component
)

CONFIG_SCHEMA = (
    number.number_schema(MatrixDisplayBrightness)
    .extend(
        {
            cv.Optional(CONF_MODE, default="SLIDER"): cv.enum(
                number.NUMBER_MODES, upper=True
            ),
            cv.Optional(CONF_RESTORE_VALUE, default=True): cv.boolean,
            cv.Optional(CONF_INITIAL_VALUE): cv.float_,
            cv.Required(MATRIX_ID): cv.use_id(MatrixDisplay),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


def to_code(config):
    var = yield number.new_number(config, min_value=0, max_value=255, step=1)
    yield cg.register_component(var, config)

    cg.add(var.set_restore_value(config[CONF_RESTORE_VALUE]))
    if CONF_INITIAL_VALUE in config:
        cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))

    matrix = yield cg.get_variable(config[MATRIX_ID])
    cg.add(matrix.register_brightness(var))
