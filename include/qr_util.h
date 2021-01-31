#pragma once

template<typename T, size_t NUM_LEDS>
using array_t = T[NUM_LEDS];

using millis_t = decltype(millis());
